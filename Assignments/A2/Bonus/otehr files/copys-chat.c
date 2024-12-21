/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210

   CMPT 332 Term 1 2024

   Assignment 2
*/

#include <stdio.h>
#include <string.h>
# include <rtthreads.h>
#include <s-chat.h>
#include <sys/time.h>
#include <list.h>
#include <RttCommon.h>

#define STKSIZE 65536
#define OK "OK"
#define FAIL "FAIL"
#define KEYBOARD 0
#define PRINT 1
#define SEND 2
#define RECEIVE 3
#define EXITINSTRUCTION "exit+5\n"
#define SIZEOFBUFFERUDP 1025

/*Threads ID for all the threads*/
RttThreadId *serverPid, *keyboardPid, *printPid, *sendPid, *receivePid;
/*Lists to handle incomming/send messages*/
LIST *to_send_messages, *received_messages, *my_messages;

RttSchAttr futuretimeAttr, nowAttr;

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

/*Control*/
int local_port;
char *local_host_name;
char *local_host_ip;
char *remote_host_name;
char *remote_host_ip;
int remote_port;

int *sock_send, *sock_read;
struct sockaddr_in *send_addr;

int finished[4] = {0,0,0,0};

/*----------------------------------------------------------------*/

void myerror(const char *msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

MessageSchat *copySchat(MessageSchat *sChat1){
    MessageSchat *newSchat = (MessageSchat *)RttMalloc(sizeof(MessageSchat));
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
	printf("Keyboard thread created successfully\n");

	while(1){
		printf("In THR KEYBOARD\n");
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
				printf("KEYBOARD message to server exit\n");
				RttSend(*serverPid, cur_message, sizeof(MessageT), cur_message_received, len_received);	
				if (*cur_message_received != 0) perror("KEYBOARD_SEND");
				printf("Keyboard received server replied exit\n");
				break;
			}
			
			cur_message_chat = (MessageSchat *)RttMalloc(sizeof(MessageSchat));
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
			
			len_received = (unsigned int *)RttMalloc(sizeof(unsigned int));
			printf("KEYBOARD message to server\n");
			temp = RttSend(*serverPid, cur_message, sizeof(MessageT), cur_message_received, len_received);	
			if (temp != RTTOK) perror("KEYBOARD_SEND");
			printf("Keyboard receives message reply\n");

		}

		temp =  RttSleep(1.5);
		if (temp == RTTFAILED) perror("SLEEP");
	}

    printf("Bloqueooo el keyb 1\n");
	block_keyboard();
    printf("Bloqueooo el keyb 2\n");
	
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

		printf("In print\n");

		cur_message = (MessageT *)RttMalloc(sizeof(MessageT));
		cur_message -> request = PRINT;
		strcpy(cur_message -> content, "PRINT");
		cur_message -> finish_session = 0;
		
		cur_message_chat = (MessageSchat *)RttMalloc(sizeof(MessageSchat));
		
		len_received = (unsigned int *)RttMalloc(sizeof(unsigned int));
		printf("print message server\n");
		temp = RttSend(*serverPid, cur_message, sizeof(MessageT), cur_message_chat, len_received);	
		if (temp != RTTOK) perror("PRINT_SEND");

		printf("server replied print with %c\n", cur_message_chat -> content[0]);
		if (cur_message_chat -> content[0] == '\0'){
            printf("No hay char!!!!!!!!!---------\n");

			temp = RttSleep(1);
			if (temp != RTTOK) perror("PRINT_SLEEP");			
		} else {
			printf("Origin: %s | Time Sent from origin: %ld s, %ld us\n\t%s\n\n",
				cur_message_chat->origin, cur_message_chat->seconds,
				cur_message_chat->microseconds, cur_message_chat->content);
		}

	}
	
	finished[PRINT] = 1;

}

RTTTHREAD thr_send(){
	int temp;
	unsigned int *len_received;
	MessageSchat *cur_message_chat;
	MessageT *cur_message;

	printf("Send Process created successfully\n");
	
	while(1){
		printf("In send\n");

		cur_message = (MessageT *)RttMalloc(sizeof(MessageT));
		cur_message -> request = SEND;
		strcpy(cur_message -> content, "SEND");
		cur_message -> finish_session = 0;
		
		cur_message_chat = (MessageSchat *)RttMalloc(sizeof(MessageSchat));
		
		len_received = (unsigned int *)RttMalloc(sizeof(unsigned int));
		
		printf("Send message server\n");
		temp = RttSend(*serverPid, cur_message, sizeof(MessageT), cur_message_chat, len_received);	
		if (temp != RTTOK) {
           block_udp(*sock_send);
            myerror("SEND_SEND");
            RttExit();
        }
		printf("server replied send\n");


		if (cur_message_chat -> content[0] != '\0'){
			
			printf("Send: Origin: %s | Time: %ld s, %ld us\n\t%s\n\n",
				cur_message_chat->origin, cur_message_chat->seconds,
				cur_message_chat->microseconds, cur_message_chat->content);
			
			temp = udp_send(*sock_send, cur_message_chat, *send_addr);
			if (temp != 0) myerror("UDP_SEND");
			
			printf("Successfully SENT!!!!!!!!!!!!!!!!!!\n");
			
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

    block_udp(*sock_send);
	finished[SEND] = 1;

}



RTTTHREAD thr_receive(){
	int temp;
	MessageSchat *messageSchatReceived;
	int* cur_message_received;
	unsigned int *len_received;
	MessageT *cur_message;

	printf("Receive Process created successfully\n");
	
	while(1){
		temp =  RttSleep(1);
		if (temp == RTTFAILED) myerror("SLEEP");
		
		printf("In THR RECEIVE\n");

		messageSchatReceived = (MessageSchat *)RttMalloc(sizeof(MessageSchat));

        temp = udp_read(*sock_read, messageSchatReceived);
		if (temp != 0) myerror("UDP_READ");
		
		cur_message_received = (int *)RttMalloc(sizeof(int));
		len_received = (unsigned int *)RttMalloc(sizeof(unsigned int));

        printf("RECEIVED FROM THREAD RECEIVE:_%s|||\n", messageSchatReceived->content);
		
		if (messageSchatReceived->content[0] != '\0'){
			printf("MESSAGE RECEIVED!!!!!!!!!!!!!!!!!!!!\n");
			
			if(strcmp(messageSchatReceived->content, EXITINSTRUCTION) == 0){
				cur_message = (MessageT *)RttMalloc(sizeof(MessageT));
				cur_message -> request = RECEIVE;
				strcpy(cur_message -> content, "RECEIVE");
				cur_message -> finish_session = 1;
				printf("RECEIVE message to server exit\n");
				RttSend(*serverPid, cur_message, sizeof(MessageT), cur_message_received, len_received);	
				if (*cur_message_received != 0) perror("RECEIVE_SEND");
				printf("RECEIVE received server replied exit\n");
				break;
			}
			
			cur_message = (MessageT *)RttMalloc(sizeof(MessageT));
			cur_message -> request = RECEIVE;
			strcpy(cur_message -> content, "RECEIVE");
			cur_message -> schat = messageSchatReceived;
			cur_message -> finish_session = 0;
			
			printf("RECEIVE message to server\n");
			temp = RttSend(*serverPid, cur_message, sizeof(MessageT), cur_message_received, len_received);	
			if (temp != RTTOK) perror("RECEIVE_SEND");
			printf("RECEIVE receives message reply\n");
				
		}
				
        /*Include when the message is EXITINSTRUCTION*/
	}

    block_udp(*sock_read);
    finished[RECEIVE] = 1;

}


RTTTHREAD thr_server() {
    /*Variable Declarations*/
    int temp, who; /*temp for checking errors, who
	for control*/
    /*For Server Loop*/
    RttThreadId *requestPID, *requestPIDEXIT;
    MessageT *message_request, *message_requestEXIT;
    unsigned int *message_request_len, *message_request_lenEXIT;
    MessageSchat *cur_message1PRI, *cur_message2PRI; /*s-chat messages for
	analyze*/
    MessageSchat *cur_messageSEND, *cur_messageEXIT, *cur_messageKEYBOARD;
    RttTimeValue *tv;
	
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
    sock_send = (int *)RttMalloc(sizeof(int));
    sock_read = (int *)RttMalloc(sizeof(int));
    send_addr = (struct sockaddr_in *)RttMalloc(sizeof(struct sockaddr_in));
	memset(send_addr, 0, sizeof(struct sockaddr_in));

    temp = configure_udp_sock(local_port, remote_port, remote_host_name, sock_send, sock_read, send_addr);
    if(temp != 0) myerror("SOCKET_CONFIGURE");
	
	if (nonblock_udp(*sock_send) < 0){
		close(*sock_send);
		myerror("NON_BLOCKSOCKET");
	}

    if (nonblock_udp(*sock_read) < 0){
        close(*sock_read);
        myerror("NON_BLOCKSOCKET");
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

		printf("Server Waiting\n");
		/*Wait until a message is received*/
		RttReceive(requestPID, message_request, 
			message_request_len);
		
		/*If request is to finish a session*/	
		if (message_request -> finish_session == 1){
			if (message_request -> request == KEYBOARD){
				printf("Server finish by keyboard\n");
				temp = RttReply(*requestPID, reply_message_pl, *reply_message_len_pl);
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
					requestPIDEXIT = (RttThreadId *)RttMalloc(sizeof(RttThreadId));
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
				
				temp = RttReply(*requestPIDEXIT, cur_messageEXIT, sizeof(MessageSchat));
				if (temp == RTTFAILED) perror("RTTReply");
				
			/* reply keyboard with okey
			 * kill print, print finish execution
			 * kill receive, block de udp socket related
			 
			 If there are still messages to be received (if no wait), it must be from send,
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
                
                temp = block_udp(*sock_send);
                if (temp == RTTFAILED) perror("BLOCK_UDP");

                temp = RttKill (*keyboardPid);
                if (temp == RTTFAILED) perror("RTTKill");
                block_keyboard();
                finished[KEYBOARD] = 1;

                temp = RttKill (*printPid);
                if (temp == RTTFAILED) perror("RTTKill");
                finished[PRINT] = 1;

                printf("S-chat finished by typing exit instruction "
                       "on receive\n");

                temp = RttReply(*requestPID, reply_message_pl, *reply_message_len_pl);
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
			printf("Server get message from keyboard\n");
			temp = ListPrepend(to_send_messages, message_request -> schat);
			if (temp == -1) perror("LISTPREPEND");

            cur_messageKEYBOARD = copySchat(message_request->schat);
			temp = ListPrepend(my_messages, cur_messageKEYBOARD);
			if (temp == -1) perror("LISTPREPEND");
			
			temp = RttReply(*requestPID, reply_message_pl, *reply_message_len_pl);
			if (temp == RTTFAILED) perror("RTTReply");

			/* Keyboard has a message, so i receive the message,
			 * I store it in the "to_send_messages" and "my_messages" list, and I reply
			 * keyboard thread to continue
			 * */
		} else if (message_request -> request == PRINT){
			printf("Server to print\n");

            printf("------------------------------------------------------------ En la lista 1tengo: %d y en la 2 %d\n", ListCount(received_messages), ListCount(my_messages));

			who = 0; /*who is used to know the chosen list of the message to sent*/
			if (ListCount(received_messages) > 0){
				cur_message1PRI = ListLast(received_messages);
				who = 1;
			}
			if (ListCount(my_messages) > 0){
				cur_message2PRI = ListLast(my_messages);
				if (who == 1){
					
					if (cur_message1PRI -> seconds > cur_message2PRI -> seconds){
						who = 2;
					} else if (cur_message1PRI -> seconds == cur_message2PRI -> seconds){
						if (cur_message1PRI -> microseconds > cur_message2PRI -> microseconds){
							who = 2;
						}
					}
					
				} else {
					who = 2;
				}
			}

            printf("WHO IS ---------------------> %d\n\n", who);
			
			if (who != 0){

                printf("IMRPIMEEEEEEEEEEEE POR AAAAAAAAAAAAAAAAA\n");

                if (who == 1){
                    ListTrim(received_messages);
					temp = RttReply(*requestPID, cur_message1PRI, sizeof(MessageSchat));
					if (temp == RTTFAILED) perror("RTTReply");
                } else if (who == 2){
                    ListTrim(my_messages);
					temp = RttReply(*requestPID, cur_message2PRI, sizeof(MessageSchat));
					if (temp == RTTFAILED) perror("RTTReply");
                }
				
			} else {

                printf("IMRPIMEEEEEEEEEEEE POR BBBBBBBBBBBBBBBBBBBBBB\n");

                RttFree(cur_message1PRI);
				cur_message1PRI = (MessageSchat *)RttMalloc(sizeof(MessageSchat));
                cur_message1PRI -> content[0] = '\0';
				
				temp = RttReply(*requestPID, cur_message1PRI, sizeof(MessageSchat));
				if (temp == RTTFAILED) perror("RTTReply");				
			}
			
			who = 0;
			/* PRINT thread is ready to print, so i check if there are messages
			 * in "received_messages" or "my_messages" list.
			 * 		If they are, I reply to the thread with the message with erliest time
			 * 			I delete the message from the list
			 * 		If they are not, I reply with null
			 * */
		} else if (message_request -> request == SEND){
			printf("Server to send\n");
			if (ListCount(to_send_messages) > 0){
				cur_messageSEND = ListLast(to_send_messages);

                temp = RttReply(*requestPID, cur_messageSEND, sizeof(MessageSchat));
                if (temp == RTTFAILED) perror("RTTReply");

                ListTrim(to_send_messages);
			} else {

                RttFree(cur_messageSEND);
                cur_messageSEND = (MessageSchat *)RttMalloc(sizeof(MessageSchat));
                cur_messageSEND -> content[0] = '\0';

                temp = RttReply(*requestPID, cur_messageSEND, sizeof(MessageSchat));
                if (temp == RTTFAILED) perror("RTTReply");

            }
			/* SEND message is ready to send, so I check
			 * if therea are messages in "to_send_messages".
			 * 		If there are, I reply the thread with the earliest s-chat message
			 * 			I delete the message from the list
			 * 		If they are not, I reply with null and continue
			 * */
		} else if (message_request -> request == RECEIVE){
			printf("Server to receive\n");
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

    block_udp(*sock_send);
    block_udp(*sock_read);
    RttExit();
}



int mainp(int argc, char *argv[]) {
	/*Variable Declarations*/
	int temp;
	RttSchAttr 	attr_srv;
	serverPid = (RttThreadId *)RttMalloc(sizeof(RttThreadId));

    if (argc != 4){
        printf("Use the func like: %s <localPort> <hostName> <remotePort>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    local_port = atoi(argv[1]);
    remote_host_name = argv[2];
    remote_port = atoi(argv[3]);
    local_host_name = GetHostName();

    local_host_ip = GetIP(local_host_name);
    remote_host_ip = GetIP(remote_host_name);

    printf("INput is: %d %s:%s %d %s:%s\n", local_port, remote_host_name, remote_host_ip, remote_port, local_host_name, local_host_ip);

	/*Define RTT Time atribute for server*/
	attr_srv.startingtime = RTTZEROTIME;
	attr_srv.priority = RTTHIGH;
	attr_srv.deadline = RTTNODEADLINE;

	futuretimeAttr.startingtime = RTTINFINITE;
	futuretimeAttr.priority = RTTNORM;
	futuretimeAttr.deadline = RTTNODEADLINE;

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
