/*#NAME: Javier Andres Tarazona Jimenez
#NSID: elr490
#Student Number: 11411898

#CMPT 332 Term 1 2024

#Lab 6*/


# include <rtthreads.h>
#include <RttMutex.h>
#include <string.h>

#include <list.h>

#define MONINIT 0
#define MONENTER 1
#define MONLEAVE 2
#define MONWAIT 3
#define MONSIGNAL 4


LIST *cv_queues, *urgentQueue, *entranceQueue;

RttThreadId *MonServer_thread;

int monitor_busy;

typedef struct MessageThreadCV{
	RttThreadId id;
	int cv;
	int monCode; /*0 init, 1 enter, 2 leave, 3 wait, 4 signal */
} MessageThreadCV;

void *Get_Item(LIST* big_list, int index){
	int i;
	
	if ((index < 0) || (index == ListCount(big_list))){
		return NULL;
	} else {
		ListFirst(big_list);
		for (i=1; i<(index+1); i++){
			ListNext(big_list);
		}
		return ListCurr(big_list);
	}
}

RTTTHREAD MonServer(){
	
    while(1){		
		int rest;
		RttThreadId *thread_sender, *thread_to_signal;
		MessageThreadCV *message_received;
		unsigned int *len_message_received;
		
		int *reply_message;
		unsigned int *len_reply_message;
		
		LIST *current_queue;
		
		thread_sender = (RttThreadId *)RttMalloc(sizeof(RttThreadId));
		thread_to_signal = (RttThreadId *)RttMalloc(sizeof(RttThreadId));
		
		message_received = (MessageThreadCV *)
		RttMalloc(sizeof(MessageThreadCV));
		
		reply_message = (int *)RttMalloc(sizeof(int));
		*reply_message = 1;
		len_reply_message = (unsigned int *)RttMalloc
		(sizeof(unsigned int));
		*len_reply_message = sizeof(reply_message);
		
		len_message_received = (unsigned int *)RttMalloc
		(sizeof(MessageThreadCV));
		*len_message_received = sizeof(MessageThreadCV);
		
		RttReceive(thread_sender, message_received, 
        len_message_received);
        
        if (message_received -> monCode == MONENTER){
		
			if (monitor_busy){
				ListAppend(entranceQueue, thread_sender);
			} else {
				monitor_busy = 1;
				rest = RttReply(*thread_sender, 
				reply_message, *len_reply_message);
				if (rest == RTTFAILED) perror("RTTReply");
			}
			
		} else if (message_received -> monCode == MONLEAVE){
			
			if (ListCount(urgentQueue) > 0){
				
				thread_to_signal = (RttThreadId *) 
				ListFirst(urgentQueue);
				ListRemove(urgentQueue);
				
				rest = RttReply(*thread_to_signal, reply_message, 
				*len_reply_message);
				if (rest == RTTFAILED) perror("RTTReply");
				
			} else if (ListCount(entranceQueue) > 0){
				
				thread_to_signal = (RttThreadId *) 
				ListFirst(entranceQueue);
				ListRemove(entranceQueue);
				
				rest = RttReply(*thread_to_signal, 
				reply_message, *len_reply_message);
				if (rest == RTTFAILED) perror("RTTReply");
				
			} else {
				
				monitor_busy = 0;
				
			}
			
			rest = RttReply(*thread_sender, reply_message, 
			*len_reply_message);
			if (rest == RTTFAILED) perror("RTTReply");				
			
		} else if (message_received -> monCode == MONWAIT){
			
			rest = ListAppend(Get_Item(cv_queues, 
			message_received -> cv), 
			thread_sender);
			if (rest == -1) perror("ListAppend");
			
			if (ListCount(urgentQueue) > 0){
				
				thread_to_signal = (RttThreadId *) 
				ListFirst(urgentQueue);
				ListRemove(urgentQueue);
				
				rest = RttReply(*thread_to_signal, 
				reply_message, *len_reply_message);
				if (rest == RTTFAILED) perror("RTTReply");
				
			} else if (ListCount(entranceQueue) > 0){
				
				thread_to_signal = (RttThreadId *) 
				ListFirst(entranceQueue);
				ListRemove(entranceQueue);
				
				rest = RttReply(*thread_to_signal, 
				reply_message, *len_reply_message);
				if (rest == RTTFAILED) perror("RTTReply");
				
			} else {
				
				monitor_busy = 0;
				
			}

		} else if (message_received -> monCode == MONSIGNAL){
			
			/*Take item from CV list*/
			current_queue = Get_Item(cv_queues, 
			message_received -> cv);
			
			if (ListCount(current_queue) > 0){
				thread_to_signal = (RttThreadId *) 
				ListFirst(current_queue);
				ListRemove(current_queue);
				
				/*Add to urgent list*/
				ListAppend(urgentQueue, thread_sender);
				
				rest = RttReply(*thread_to_signal, 
				reply_message, *len_reply_message);
				if (rest == RTTFAILED) perror("RTTReply");	
				
			} else {
				rest = RttReply(*thread_sender, 
				reply_message, *len_reply_message);
				if (rest == RTTFAILED) perror("RTTReply");	
			}			
		}
    }   

}


void RttMonInit(int numConds){
    int i, rest;
    LIST *new_queue;
    RttSchAttr attr;
    
    MonServer_thread = (RttThreadId *)RttMalloc(sizeof(RttThreadId));


    urgentQueue = ListCreate();
    entranceQueue = ListCreate();
    cv_queues = ListCreate();

    for (i=0; i<numConds; i++){
        new_queue = ListCreate();
        ListAppend(cv_queues, new_queue);
    }

    attr.startingtime = RTTZEROTIME;
    attr.priority = RTTHIGH;
    attr.deadline = RTTNODEADLINE;
    
    monitor_busy = 0;

    rest = RttCreate(MonServer_thread, (void(*)()) 
    MonServer, 65536, "MonServer", NULL, attr, RTTUSR);
    if (rest == RTTFAILED) perror("RttCreate");
}

void RttMonEnter(){
	MessageThreadCV *message;
	unsigned int *message_size;
	int *message_rcv;
	unsigned int *len_message_rcv;
	

	message_size = (unsigned int *)RttMalloc(sizeof(unsigned int ));
	
	message = (MessageThreadCV *)RttMalloc(sizeof(MessageThreadCV));
	*message_size = sizeof(MessageThreadCV);
	
	message -> id = RttMyThreadId();
	message -> cv = -1;
	message -> monCode = MONENTER;
	
	message_rcv = (int *)RttMalloc(sizeof(int));
	len_message_rcv = (unsigned int *)RttMalloc(sizeof(unsigned int));
	
	RttSend(*MonServer_thread, message, *message_size,
			message_rcv, len_message_rcv);
}

void RttMonLeave(){
	MessageThreadCV *message;
	unsigned int *message_size;
	int *message_rcv;
	unsigned int *len_message_rcv;
	
	message_size = (unsigned int *)RttMalloc(sizeof(unsigned int ));
	
	*message_size = sizeof(MessageThreadCV);
	message = (MessageThreadCV *)RttMalloc(sizeof(MessageThreadCV));	
	
	message -> id = RttMyThreadId();
	message -> cv = -1;
	message -> monCode = MONLEAVE;
	
	message_rcv = (int *)RttMalloc(sizeof(int));
	len_message_rcv = (unsigned int *)RttMalloc(sizeof(unsigned int));	
		
	RttSend(*MonServer_thread, message, *message_size,
		message_rcv, len_message_rcv);
}

void RttMonWait(int cv){
    /* Possible values for cv is 0 read, 1 write*/
  
	MessageThreadCV *message;
	unsigned int *message_size;
	int *message_rcv;
	unsigned int *len_message_rcv;
	
	message_size = (unsigned int *)RttMalloc(sizeof(unsigned int ));
	
	*message_size = sizeof(MessageThreadCV);
	message = (MessageThreadCV *)RttMalloc(sizeof(MessageThreadCV));
	
	message -> id = RttMyThreadId();
	message -> cv = cv;
	message -> monCode = MONWAIT;
	
	message_rcv = (int *)RttMalloc(sizeof(int));
	len_message_rcv = (unsigned int *)RttMalloc(sizeof(unsigned int));	
		
	RttSend(*MonServer_thread, message, *message_size,
		message_rcv, len_message_rcv);
    
}

void RttMonSignal(int cv){
    /* Possible values for cv is 0 read, 1 write*/

	MessageThreadCV *message;
	unsigned int *message_size;
	int *message_rcv;
	unsigned int *len_message_rcv;
	
	message_size = (unsigned int *)RttMalloc(sizeof(unsigned int ));
	
	*message_size = sizeof(MessageThreadCV);
	message = (MessageThreadCV *)RttMalloc(sizeof(MessageThreadCV));
	
	message -> id = RttMyThreadId();
	message -> cv = cv;
	message -> monCode = MONSIGNAL;
	
	message_rcv = (int *)RttMalloc(sizeof(int));
	len_message_rcv = (unsigned int *)RttMalloc(sizeof(unsigned int));
	
	RttSend(*MonServer_thread, message, *message_size,
		message_rcv, len_message_rcv);	
}
