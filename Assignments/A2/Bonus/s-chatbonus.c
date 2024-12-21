/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210

   CMPT 332 Term 1 2024

   Assignment 2
*/

#include <stdio.h>
#include <string.h>
#include <rtthreads.h>
#include <sys/time.h>
#include <list.h>
#include <RttCommon.h>
#include <s-chatbonus.h>

#define STKSIZE 65536
#define OK "OK"
#define FAIL "FAIL"
#define KEYBOARD 0
#define PRINT 1
#define SEND 2
#define RECEIVE 3
#define EXITINSTRUCTION "exit+5\n"

/*Threads ID for all the threads*/
RttThreadId *serverPid, *keyboardPid, *printPid, *sendPid, *receivePid;
/*Lists to handle incomming/send messages*/
LIST *to_send_messages, *received_messages, *my_messages, *peer_list;

RttSchAttr nowAttr;

/*Messages*/
int *reply_message_pl;
unsigned int *reply_message_len_pl;

/*Message for s-chat*/
/*typedef struct MessageSchat {
	char origin[256];
	char content[256];
	long seconds;
	long microseconds;
} MessageSchat;*/

/*Message structure for the IPC communication*/
typedef struct MessageT{
	int request; /*KEYBOARD, PRINT, SEND, RECEIVE*/
	char content[256];
	MessageSchat *schat;
	int finish_session;
} MessageT;

typedef struct peer{
	int socket_send;
	struct sockaddr_in send_addr;
	char *host_name;
	char *ip;
	int port;
} peer;

/*Control*/
int local_port;
char *local_host_name;
char *local_host_ip;
char *remote_host_name;
char *remote_host_ip;
int remote_port;
int number_peers;

int *sock_read;

int finished[4] = {0,0,0,0};

/*----------------------------------------------------------------*/

void myerror(const char *msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

MessageSchat *copySchat(MessageSchat *sChat1){
    MessageSchat *newSchat = (MessageSchat *)
    RttMalloc(sizeof(MessageSchat));
    strcpy(newSchat->origin, sChat1->origin);
    strcpy(newSchat->content, sChat1->content);
    newSchat->seconds = sChat1->seconds;
    newSchat->microseconds = sChat1->microseconds;
    return newSchat;
}

RTTTHREAD thr_keyboard(){
	/*Sends MessageT, receives an int*/
	char buffer_reading[256];
	int temp = 0;
    RttTimeValue *tv;
	MessageSchat *cur_message_chat;
	MessageT *cur_message;
	int* cur_message_received;
	unsigned int *len_received;

	nonblock_keyboard();

	while(1){
        memset(buffer_reading, 0, sizeof(buffer_reading));

		temp = read_keyboard(buffer_reading, 255);

		if (temp == -1) perror("READ_KEYBOARD");
		cur_message_received = (int *)RttMalloc(sizeof(int));
		len_received = (unsigned int *)RttMalloc(sizeof(unsigned int));

		if (buffer_reading[0] != '\0'){

			if(strcmp(buffer_reading, EXITINSTRUCTION) == 0){
				cur_message = (MessageT *)RttMalloc(sizeof(MessageT));
				cur_message -> request = KEYBOARD;
				strcpy(cur_message -> content, "KEYBOARD");
				cur_message -> finish_session = 1;

				RttSend(*serverPid, cur_message, sizeof(MessageT), 
				cur_message_received, len_received);	
				if (*cur_message_received != 0) perror("KEYBOARD_SEND");

				break;
			}
			
			cur_message_chat = (MessageSchat *)
			RttMalloc(sizeof(MessageSchat));
			strcpy(cur_message_chat -> origin, local_host_name);
			strcpy(cur_message_chat -> content, buffer_reading);
            tv = (RttTimeValue *)RttMalloc(sizeof(RttTimeValue));
            temp = RttGetTimeOfDay(tv);
			cur_message_chat -> seconds = tv->seconds;
			cur_message_chat -> microseconds = tv->microseconds;
			
			cur_message = (MessageT *)RttMalloc(sizeof(MessageT));
			cur_message -> request = KEYBOARD;
			strcpy(cur_message -> content, "KEYBOARD");
			cur_message -> schat = cur_message_chat;
			cur_message -> finish_session = 0;
			
			len_received = (unsigned int *)
			RttMalloc(sizeof(unsigned int));

			temp = RttSend(*serverPid, cur_message, 
			sizeof(MessageT), cur_message_received, len_received);	
			if (temp != RTTOK) perror("KEYBOARD_SEND");


		}

		temp =  RttSleep(1.5);
		if (temp == RTTFAILED) perror("SLEEP");
	}


	block_keyboard();

	
	finished[KEYBOARD] = 1;
}

RTTTHREAD thr_print(){
	int temp;
	unsigned int *len_received;
	MessageSchat *cur_message_chat;
	MessageT *cur_message;
	
	while(1){
        temp =  RttSleep(1);
        if (temp == RTTFAILED) perror("SLEEP");

		cur_message = (MessageT *)RttMalloc(sizeof(MessageT));
		cur_message -> request = PRINT;
		strcpy(cur_message -> content, "PRINT");
		cur_message -> finish_session = 0;
		
		cur_message_chat = (MessageSchat *)RttMalloc(sizeof(MessageSchat));
		
		len_received = (unsigned int *)RttMalloc(sizeof(unsigned int));

		temp = RttSend(*serverPid, cur_message, sizeof(MessageT), 
		cur_message_chat, len_received);	
		if (temp != RTTOK) perror("PRINT_SEND");


		if (cur_message_chat -> content[0] == '\0'){

			temp = RttSleep(1);
			if (temp != RTTOK) perror("PRINT_SLEEP");			
		} else {
			printf("Origin: %s | Time Sent from origin: %ld s, "
			"%ld us\n\t%s\n\n",
				cur_message_chat->origin, cur_message_chat->seconds,
				cur_message_chat->microseconds, cur_message_chat->content);
		}

	}
	
	finished[PRINT] = 1;

}

RTTTHREAD thr_send(){
	int temp, i;
	unsigned int *len_received;
	MessageSchat *cur_message_chat;
	MessageT *cur_message;
	peer *cur_peer;

	
	while(1){

		cur_message = (MessageT *)RttMalloc(sizeof(MessageT));
		cur_message -> request = SEND;
		strcpy(cur_message -> content, "SEND");
		cur_message -> finish_session = 0;
		
		cur_message_chat = (MessageSchat *)RttMalloc(sizeof(MessageSchat));
		
		len_received = (unsigned int *)RttMalloc(sizeof(unsigned int));
		
		temp = RttSend(*serverPid, cur_message, sizeof(MessageT), 
		cur_message_chat, len_received);	
		if (temp != RTTOK) {
            myerror("SEND_SEND");
        }


		if (cur_message_chat -> content[0] != '\0'){
			
			/*printf("Send: Origin: %s | Time: %ld s, %ld us\n\t%s\n\n",
				cur_message_chat->origin, cur_message_chat->seconds,
				cur_message_chat->microseconds, cur_message_chat->content);*/
			
			ListFirst(peer_list);
			for (i=0; i<number_peers; i++){
				cur_peer = ListCurr(peer_list);
				if (i<number_peers-1) ListNext(peer_list);
				
				temp = udp_send(cur_peer->socket_send,
					cur_message_chat, cur_peer->send_addr);
				/*if (temp != 0) myerror("UDP_SEND");*/
			}
			
	
			if (strcmp(cur_message_chat -> content, EXITINSTRUCTION) == 0){
				break;
			}
			
		}

		temp =  RttSleep(1);
		if (temp == RTTFAILED) perror("SLEEP");
	}
	/*When sneding if fail, interrupr connection because
	 * there is no way to estaclis it. Try 4 times
	 * 
	 * Receives exit instruction, to finish execution*/

	ListFirst(peer_list);
	for (i=0; i<number_peers; i++){
		cur_peer = ListCurr(peer_list);
		if (i<number_peers-1) ListNext(peer_list);
		
		block_udp(cur_peer->socket_send);
	}
	finished[SEND] = 1;

}



RTTTHREAD thr_receive(){
	int temp;
	MessageSchat *messageSchatReceived;
	int* cur_message_received;
	unsigned int *len_received;
	MessageT *cur_message;

	
	while(1){
		temp =  RttSleep(1);
		if (temp == RTTFAILED) myerror("SLEEP");
		

		messageSchatReceived = (MessageSchat *)RttMalloc(sizeof(MessageSchat));

        temp = udp_read(*sock_read, messageSchatReceived);
		if (temp != 0) myerror("UDP_READ");
		
		cur_message_received = (int *)RttMalloc(sizeof(int));
		len_received = (unsigned int *)RttMalloc(sizeof(unsigned int));

	
		if (messageSchatReceived->content[0] != '\0'){
			
			if(strcmp(messageSchatReceived->content, EXITINSTRUCTION) == 0){
				cur_message = (MessageT *)RttMalloc(sizeof(MessageT));
				cur_message -> request = RECEIVE;
				strcpy(cur_message -> content, "RECEIVE");
				cur_message -> finish_session = 1;

				RttSend(*serverPid, cur_message, sizeof(MessageT), 
				cur_message_received, len_received);	
				if (*cur_message_received != 0) perror("RECEIVE_SEND");

				break;
			}
			
			cur_message = (MessageT *)RttMalloc(sizeof(MessageT));
			cur_message -> request = RECEIVE;
			strcpy(cur_message -> content, "RECEIVE");
			cur_message -> schat = messageSchatReceived;
			cur_message -> finish_session = 0;
			

			temp = RttSend(*serverPid, cur_message, sizeof(MessageT), 
			cur_message_received, len_received);	
			if (temp != RTTOK) perror("RECEIVE_SEND");

				
		}
				
        /*Include when the message is EXITINSTRUCTION*/
	}

    block_udp(*sock_read);
    finished[RECEIVE] = 1;

}


RTTTHREAD thr_server() {
    /*Variable Declarations*/
    int temp, who, i; /*temp for checking errors, who
	for control*/
	char bufclose[1];
    /*For Server Loop*/
    RttThreadId *requestPID, *requestPIDEXIT;
    MessageT *message_request, *message_requestEXIT;
    unsigned int *message_request_len, *message_request_lenEXIT;
    MessageSchat *cur_message1PRI, *cur_message2PRI; /*s-chat messages for
	analyze*/
    MessageSchat *cur_messageSEND, *cur_messageEXIT, *cur_messageKEYBOARD;
    RttTimeValue *tv;
    peer *cur_peer;
    int *sock_send;
	struct sockaddr_in *send_addr;

	/*Threads Allocation*/
	keyboardPid = (RttThreadId *)RttMalloc(sizeof(RttThreadId));
	if (keyboardPid == NULL) perror("RTTMALLOC");
	printPid = (RttThreadId *)RttMalloc(sizeof(RttThreadId));
	if (printPid == NULL) perror("RTTMALLOC");
	sendPid = (RttThreadId *)RttMalloc(sizeof(RttThreadId));
	if (sendPid == NULL) perror("RTTMALLOC");
	receivePid = (RttThreadId *)RttMalloc(sizeof(RttThreadId));
	if (receivePid == NULL) perror("RTTMALLOC");

    /*Base (simple) message, for replies*/
	reply_message_pl = (int *)RttMalloc(sizeof(int));
	*reply_message_pl = 0;
	reply_message_len_pl = (unsigned int *)RttMalloc
	(sizeof(unsigned int));
	*reply_message_len_pl = sizeof(int);

	/*Create lists*/
	to_send_messages = ListCreate();
	my_messages = ListCreate();
	received_messages = ListCreate();

	/*Configure UDP*/
	sock_read = (int *)RttMalloc(sizeof(int));
	temp = configure_udp_sock_receive(local_port, sock_read);
	if(temp != 0) myerror("SOCKET_CONFIGURE_READ");

	if (nonblock_udp(*sock_read) < 0){
        close(*sock_read);
        myerror("NON_BLOCKSOCKET_READ");
    }

	ListFirst(peer_list);
	for (i=0; i<number_peers; i++){
		
		cur_peer = ListCurr(peer_list);
		if (i<number_peers-1) ListNext(peer_list);
		
		sock_send = (int *)RttMalloc(sizeof(int));
		send_addr = (struct sockaddr_in *)
		RttMalloc(sizeof(struct sockaddr_in));
		memset(send_addr, 0, sizeof(struct sockaddr_in));

		temp = configure_udp_sock_send(cur_peer->port, 
			cur_peer->host_name, sock_send, 
			send_addr);
		if(temp != 0) myerror("SOCKET_CONFIGURE_SEND");
		
		cur_peer->socket_send = *sock_send;
		cur_peer->send_addr = *send_addr;
		
		if (nonblock_udp(*sock_send) < 0){
			close(*sock_send);
			myerror("NON_BLOCKSOCKET_SEND");
		}
	}

	/*Threads Creation*/
	temp = RttCreate(keyboardPid, thr_keyboard, STKSIZE, "keyboard", 
	NULL, nowAttr, RTTUSR);
	if(temp == RTTFAILED) perror("RTTCREATE");
	
	temp = RttCreate(printPid, thr_print, STKSIZE, "print", NULL, 
	nowAttr, RTTUSR);
	if(temp == RTTFAILED) perror("RTTCREATE");
	
	temp = RttCreate(sendPid, thr_send, STKSIZE, "send", NULL, nowAttr, 
	RTTUSR);
	if(temp == RTTFAILED) perror("RTTCREATE");
	
	temp = RttCreate(receivePid, thr_receive, STKSIZE, "receive",
	NULL, nowAttr, RTTUSR);
	if(temp == RTTFAILED) perror("RTTCREATE");

	/*Server Actions*/
	while(1){
				
		/*Variable Allocation In Loop*/		
		requestPID = (RttThreadId *)RttMalloc(sizeof(RttThreadId));
		
		message_request = (MessageT *) 
		RttMalloc(sizeof(MessageT));
		
		message_request_len = (unsigned int *)RttMalloc
		(sizeof(unsigned int));
		*message_request_len = sizeof(MessageT);


		/*Wait until a message is received*/
		RttReceive(requestPID, message_request, 
			message_request_len);
		
		/*If request is to finish a session*/	
		if (message_request -> finish_session == 1){
			if (message_request -> request == KEYBOARD){
				printf("Server finish by keyboard\n");
				temp = RttReply(*requestPID, reply_message_pl, 
				*reply_message_len_pl);
				if (temp == RTTFAILED) perror("RTTReply");
				
				temp = RttKill (*printPid);
				if (temp == RTTFAILED) perror("RTTKill");
				finished[PRINT] = 1;
				
				printf("S-chat finished by typing exit instruction "
				"on keyboard\n");
				
				temp = RttKill (*receivePid);
				if (temp == RTTFAILED) perror("RTTKill");
                temp = block_udp(*sock_read);
                if (temp != 0) myerror("CLOSED_READ_UDP");
				finished[RECEIVE] = 1;
				
				/*Block UDP*/
				
				/*----------------------*/

				requestPIDEXIT = (RttThreadId *)RttMalloc(sizeof(RttThreadId));

				message_requestEXIT = (MessageT *)
				RttMalloc(sizeof(MessageT));
				
				message_request_lenEXIT = (unsigned int *)RttMalloc
				(sizeof(unsigned int));
				*message_request_lenEXIT = sizeof(MessageT);


				RttReceive(requestPIDEXIT, message_requestEXIT,
				message_request_lenEXIT);


				/*If there are other requests in queue...*/
				while (message_requestEXIT->request != SEND){
					requestPIDEXIT = (RttThreadId *)
					RttMalloc(sizeof(RttThreadId));
					message_requestEXIT = (MessageT *)
					RttMalloc(sizeof(MessageT));
					
					message_request_lenEXIT = (unsigned int *)RttMalloc
					(sizeof(unsigned int));
					*message_request_lenEXIT = sizeof(MessageT);
					
					RttReceive(requestPIDEXIT, message_requestEXIT,
					message_request_lenEXIT);
				}

				cur_messageEXIT = (MessageSchat *)RttMalloc(sizeof(MessageSchat));
                strcpy(cur_messageEXIT -> origin, local_host_name);
				strcpy(cur_messageEXIT -> content, EXITINSTRUCTION);
                tv = (RttTimeValue *)RttMalloc(sizeof(RttTimeValue));
                temp = RttGetTimeOfDay(tv);
                if (temp == RTTFAILED) perror("RTTTIMEVALUE");
                cur_messageEXIT -> seconds = tv->seconds;
                cur_messageEXIT -> microseconds = tv->microseconds;
				
				temp = RttReply(*requestPIDEXIT, cur_messageEXIT, 
				sizeof(MessageSchat));
				if (temp == RTTFAILED) perror("RTTReply");
				
			/* reply keyboard with okey
			 * kill print, print finish execution
			 * kill receive, block de udp socket related
			 
			 If there are still messages to be received (if no wait), 
			 it must be from send,
			 then, receive the message and reply to finish execution.
							Send:
							  send exit message to other machine
							  exit
			 * */	
			}
			if (message_request -> request == RECEIVE){
				printf("Server finished by receive\n");

                temp = RttKill (*sendPid);
                if (temp == RTTFAILED) perror("RTTKill");
                finished[SEND] = 1;

				ListFirst(peer_list);
				for (i=0; i<number_peers; i++){
					cur_peer = ListCurr(peer_list);
					if (i<number_peers-1) ListNext(peer_list);
					
					temp = block_udp(cur_peer->socket_send);
					if (temp == RTTFAILED) perror("BLOCK_UDP");
				}

                temp = RttKill (*keyboardPid);
                if (temp == RTTFAILED) perror("RTTKill");
                block_keyboard();
                finished[KEYBOARD] = 1;

                temp = RttKill (*printPid);
                if (temp == RTTFAILED) perror("RTTKill");
                finished[PRINT] = 1;

                printf("S-chat finished by typing exit instruction "
                       "on receive\n");

                temp = RttReply(*requestPID, reply_message_pl, 
                *reply_message_len_pl);
				if (temp == RTTFAILED) perror("RTTReply");
				

			/* reply receive with okey
			 * kill print, print finish execution, 
			 * kill keyboard, block keyboard,
			 * kill send, block de udp socket related
			 * */	
			}
			break;
		}
			
		if (message_request -> request == KEYBOARD){

			temp = ListPrepend(to_send_messages, message_request -> schat);
			if (temp == -1) perror("LISTPREPEND");

            cur_messageKEYBOARD = copySchat(message_request->schat);
			temp = ListPrepend(my_messages, cur_messageKEYBOARD);
			if (temp == -1) perror("LISTPREPEND");
			
			temp = RttReply(*requestPID, reply_message_pl, 
			*reply_message_len_pl);
			if (temp == RTTFAILED) perror("RTTReply");

			/* Keyboard has a message, so i receive the message,
			 * I store it in the "to_send_messages" and "my_messages" 
			 * list, and I reply
			 * keyboard thread to continue
			 * */
		} else if (message_request -> request == PRINT){

			who = 0; /*who is used to know the chosen list of the 
			message to sent*/
			if (ListCount(received_messages) > 0){
				cur_message1PRI = ListLast(received_messages);
				who = 1;
			}
			if (ListCount(my_messages) > 0){
				cur_message2PRI = ListLast(my_messages);
				if (who == 1){
					
					if (cur_message1PRI -> seconds > 
					cur_message2PRI -> seconds){
						who = 2;
					} else if (cur_message1PRI -> seconds == 
					cur_message2PRI -> seconds){
						if (cur_message1PRI -> microseconds > 
						cur_message2PRI -> microseconds){
							who = 2;
						}
					}
					
				} else {
					who = 2;
				}
			}

		
			if (who != 0){

                if (who == 1){
                    ListTrim(received_messages);
					temp = RttReply(*requestPID, cur_message1PRI, 
					sizeof(MessageSchat));
					if (temp == RTTFAILED) perror("RTTReply");
                } else if (who == 2){
                    ListTrim(my_messages);
					temp = RttReply(*requestPID, cur_message2PRI, 
					sizeof(MessageSchat));
					if (temp == RTTFAILED) perror("RTTReply");
                }
				
			} else {


                RttFree(cur_message1PRI);
				cur_message1PRI = (MessageSchat *)
				RttMalloc(sizeof(MessageSchat));
                cur_message1PRI -> content[0] = '\0';
				
				temp = RttReply(*requestPID, cur_message1PRI, 
				sizeof(MessageSchat));
				if (temp == RTTFAILED) perror("RTTReply");				
			}
			
			who = 0;
			/* PRINT thread is ready to print, so i check if there 
			 * are messages
			 * in "received_messages" or "my_messages" list.
			 * 		If they are, I reply to the thread with the 
			 * message with erliest time
			 * 			I delete the message from the list
			 * 		If they are not, I reply with null
			 * */
		} else if (message_request -> request == SEND){

			if (ListCount(to_send_messages) > 0){
				cur_messageSEND = ListLast(to_send_messages);

                temp = RttReply(*requestPID, cur_messageSEND, 
                sizeof(MessageSchat));
                if (temp == RTTFAILED) perror("RTTReply");

                ListTrim(to_send_messages);
			} else {

                RttFree(cur_messageSEND);
                cur_messageSEND = (MessageSchat *)
                RttMalloc(sizeof(MessageSchat));
                cur_messageSEND -> content[0] = '\0';

                temp = RttReply(*requestPID, 
                cur_messageSEND, sizeof(MessageSchat));
                if (temp == RTTFAILED) perror("RTTReply");

            }
			/* SEND message is ready to send, so I check
			 * if therea are messages in "to_send_messages".
			 * 		If there are, I reply the thread with the 
			 * earliest s-chat message
			 * 			I delete the message from the list
			 * 		If they are not, I reply with null and continue
			 * */
		} else if (message_request -> request == RECEIVE){

			temp = ListPrepend(received_messages, message_request -> schat);
			if (temp == -1) perror("LISTPREPEND");
			
			temp = RttReply(*requestPID, reply_message_pl, *reply_message_len_pl);
			if (temp == RTTFAILED) perror("RTTReply");
			
			/* receive thread has a message, so I receive the message,
			 * I store it in the "received_messages" list, and I reply
			 * thread thread to continue
			 * */
		}
	}

	/*Check if ports have not been closed*/
	ListFirst(peer_list);
	for (i=0; i<number_peers; i++){
		cur_peer = ListCurr(peer_list);
		if (i<number_peers-1) ListNext(peer_list);
		
		temp = recv(cur_peer->socket_send, bufclose, 
		sizeof(bufclose), MSG_PEEK);
		if (temp != 0) block_udp(cur_peer->socket_send);
	}

	temp = recv(*sock_read, bufclose, sizeof(bufclose), MSG_PEEK);
	if (temp != 0) block_udp(*sock_read);
	
    RttExit();
}


int mainp(int argc, char *argv[]) {
	/*Variable Declarations*/
	int temp, i;
	RttSchAttr 	attr_srv;
	peer *cur_peer;

    if (argc < 3){
        printf("Use the func like: %s <localPort> <number_of_peers>"
			"<peer1Name> <remotePort1>... \n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
	serverPid = (RttThreadId *)RttMalloc(sizeof(RttThreadId));
	
	local_port = atoi(argv[1]);
	number_peers = atoi(argv[2]);
	
	local_host_name = GetHostName();
	local_host_ip = GetIP(local_host_name);
    
    peer_list = ListCreate();
    
    for (i = 0; i < number_peers; i++) {
		cur_peer = (peer *)RttMalloc(sizeof(peer));
        printf("Received peer %d", i+1);
        cur_peer->host_name = argv[(2*i)+3];
        cur_peer->port = atoi(argv[(2*i)+4]);
        cur_peer->ip = GetIP(cur_peer->host_name);
        ListAdd(peer_list, cur_peer);
    }
    

	/*Define RTT Time atribute for server*/
	attr_srv.startingtime = RTTZEROTIME;
	attr_srv.priority = RTTHIGH;
	attr_srv.deadline = RTTNODEADLINE;

	nowAttr.startingtime = RTTZEROTIME;
	nowAttr.priority = RTTNORM;
	nowAttr.deadline = RTTNODEADLINE;

	/*output everything immediately (no buffer) 
	- Useful for Real Time Processes*/
	setbuf(stdout, 0);

	/*Create Server Thread*/
	temp = RttCreate(serverPid, (void(*)()) thr_server,STKSIZE,"Server", 
	NULL, attr_srv, RTTUSR);
	if (temp == RTTFAILED) perror("RttCreate");
	
	printf("S-Chat Started\n");

	return 0;
}
