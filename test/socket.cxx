#include <Flek/FSocket.H>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define HDR_SIZE  16
#define BODY_SIZE 240
#define N_LOOPS   1000000

int main(int argc, char* argv[]) 
{
    char errbuf[256];
    char buf[HDR_SIZE+BODY_SIZE];	
    FSocket* sock;
    int server = 0;
    int i;
  //task::initialize(task::normal_stack);

    if (argc < 3) { 
     	printf("Socket test program\n"
	  "Usage: testsock [(local-server|global-server)|client] host:port\n");
	return EXIT_FAILURE;
    }

    if (*argv[1] == 'l' || *argv[1] == 'L') { // local server
	FSocket* gate = FSocket::create_local(argv[2]); 
	if (!gate->valid()) { 
	    gate->get_error_text(errbuf, sizeof errbuf);
	  printf("Failed to create local socket: %s\n", errbuf);
	}
	sock = gate->accept();
	if (sock == NULL) { 
	    gate->get_error_text(errbuf, sizeof errbuf);
	    printf("Failed to accept socket: %s\n", errbuf);
	}
	delete gate;
	server = 1;
    } else if (*argv[1] == 'g' || *argv[1] == 'G') { // global server
	FSocket* gate = FSocket::create_global(argv[2]); 
	if (!gate->valid()) { 
	    gate->get_error_text(errbuf, sizeof errbuf);
	    delete gate;
	    printf("Failed to create global socket: %s\n", errbuf);
	}
	sock = gate->accept();
	if (sock == NULL) { 
	    gate->get_error_text(errbuf, sizeof errbuf);
	    delete gate;
	    printf("Failed to accept socket: %s\n", errbuf);
	}
	delete gate;
	server = 1;
    } else { // client
	sock = FSocket::connect(argv[2]); 
	if (sock == NULL) { 
	    printf("Failed to connect to server\n");
	} else if (!sock->valid()) { 
	    sock->get_error_text(errbuf, sizeof errbuf);
	    printf("Connection to server failed: %s\n", errbuf);
	}
	server = 0;
    }
    time_t start_time = time(NULL);

    if (server) { 
	i = 0;
	while (sock->read(buf, HDR_SIZE) && 
	       sock->read(buf, sizeof(buf) - HDR_SIZE)) 
        {
	    i += 1;
	    if (!sock->write(buf, sizeof buf)) { 
	    	sock->get_error_text(errbuf, sizeof errbuf);
		printf("Write to socket failed: %s\n", errbuf);
	    }
	} 	
	printf("Handle %d requests\n", i);
    } else { 
	for (i = 0; i < N_LOOPS; i++) { 
	    if (!sock->write(buf, sizeof buf) ||
		!sock->read(buf, HDR_SIZE) ||
		!sock->read(buf, sizeof(buf) - HDR_SIZE))
            {
	    	sock->get_error_text(errbuf, sizeof errbuf);
		printf("Write to socket failed: %s\n", errbuf);
	    }
	}
    } 
   printf("Elapsed time %d seconds\n", (int)(time(NULL) - start_time));
    return EXIT_SUCCESS;
}


