#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int nchildren=1;
	int pid;
	int x;
	
	if(argc>1){
		nchildren=atoi(argv[1]);
	}

	for (x=0; x<nchildren; x++;){
		if((pid=fork())==0){
			child_func(x+1);
			exit(0);
		}
	}

	wait(NULL);
	return 0;
}
