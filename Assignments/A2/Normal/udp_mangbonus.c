/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin 
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210

   CMPT 332 Term 1 2024

   Assignment 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /*getHostName*/
#include <limits.h> /*max Host Name*/
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h> /*Get IP*/
#include <fcntl.h>

# include <rtthreads.h>
#include <s-chatbonus.h>

#define BUFFER_SIZE 1025

void myerror_u(const char *msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

char *GetHostName(){
    char *hostName = (char *)RttMalloc((size_t)HOST_NAME_MAX);
    if (gethostname(hostName, (size_t)HOST_NAME_MAX) != 0){
        myerror_u("HOSTNAME");
    }
    return hostName;
}

char *GetIP(char *hostName){
    struct hostent *host_entry;
    char *getIP;
    char *IPstr = (char *)RttMalloc(50);

    host_entry = gethostbyname(hostName);
    if (host_entry == NULL){
        myerror_u("GETHOSTENTRY_HostName no Found");
        exit(EXIT_FAILURE);
    }

    getIP = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0]));
    strcpy(IPstr, getIP);
    IPstr[49] = '\0';

    return IPstr;
}

int configure_udp_sock_send(int remote_port, const char* 
remote_host_name, int *tosock_send, struct sockaddr_in *tosend_addr){
	int sock_send;
	struct sockaddr_in send_addr;
	struct hostent *he;
	
	int broadcast = 1;

    /*-------SEND------------*/
	
    if ((he = gethostbyname(remote_host_name)) == NULL) {  
		/*get the host info*/
        myerror_u("gethostbyname");
    }
	
    if ((sock_send = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        myerror_u("socket");
    }
	
	if (setsockopt(sock_send, SOL_SOCKET, SO_BROADCAST, &broadcast,
		sizeof(broadcast)) == -1) {
		close(sock_send);
		myerror_u("setsockopt (SO_BROADCAST)");
	}
	
    send_addr.sin_family = AF_INET;
    send_addr.sin_port = htons(remote_port);
    send_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(send_addr.sin_zero, '\0', sizeof send_addr.sin_zero);

    *tosock_send = sock_send;
    *tosend_addr = send_addr;
    return 0;
}

int configure_udp_sock_receive(int local_port, int *tosock_read){
    int sock_read;
    struct sockaddr_in rcv_addr;
    
    /*-----------READ-----------*/

    if ((sock_read = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        myerror_u("socket_READ");
    }

    memset(&rcv_addr, 0, sizeof(rcv_addr));
    rcv_addr.sin_family = AF_INET;
    rcv_addr.sin_port = htons(local_port);
    rcv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock_read, (struct sockaddr*)&rcv_addr, 
    sizeof(rcv_addr)) < 0) {
        close(sock_read);
        myerror_u("BIND_ERROR");
        return -1;
    }

    *tosock_read = sock_read;
    return 0;
}


int nonblock_udp(int sock_fd){
    int flags_fd;

    flags_fd = fcntl(sock_fd, F_GETFL, 0);
    if (flags_fd == -1){
        perror("FLAGSNONBLOCKUDP");
        return -1;
    }

    if (fcntl(sock_fd, F_SETFL, flags_fd | O_NONBLOCK) == -1) {
        perror("fcntl");
        return -1;
    }
    
    return 0;
}

int udp_read(int sock_fd, MessageSchat *buffer_reading){
    int sz;

    struct sockaddr_in sender_addr;
    socklen_t sender_len = sizeof(sender_addr);

    sz = recvfrom(sock_fd, buffer_reading, sizeof(MessageSchat), 0,
    (struct sockaddr*)&sender_addr, &sender_len);

    if (sz == -1){
        if (errno == EAGAIN || errno == EWOULDBLOCK){
            /*There is no available input*/
            return 0;
        } else {
            myerror_u("read_udp");
            return -1;
        }
    }

    return 0;
}

int udp_send(int sock_fd, MessageSchat *message,
 struct sockaddr_in send_addr){
    ssize_t sent_bytes;
    int chances = 4;

    while (chances > 0){
        sent_bytes = sendto(sock_fd, message, sizeof(MessageSchat), 0,
                            (struct sockaddr*)&send_addr, sizeof(send_addr));

        if (sent_bytes == -1){
			chances--;
			if (chances == 0){
				myerror_u("SENDTO_FAILED");
			}
            return -1;
        } else {
			chances = 0;
		}
    }

    return 0;
}


int block_udp(int sock_fd){
    int flags_fd;

    flags_fd = fcntl(sock_fd, F_GETFL, 0);
    if(flags_fd == -1) {
        /*perror("FCNTL_BLOCKUDP");*/
        return -1;
    }

    if (fcntl(sock_fd, F_SETFL, flags_fd & ~O_NONBLOCK) == -1){
        perror("FCNTL_FLBLOCKUDP");
        return -1;
    }

    close(sock_fd);

    return 0;
}
