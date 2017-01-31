#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "shared_info.h"

int main(int argc, char *argv[])
{  
    int  i, id  ;
    struct info *ctrl;
    
    if ( (id = shmget( KEY, SEGSIZE,IPC_CREAT | 0666) ) < 0 )
    	return 1;
    if ( (ctrl = (struct info *) shmat( id, 0, 0)) <= (struct info *) (0) ) 
    	return 1;
   
	ctrl->num1 = 1;
	ctrl->num2 = 2;

	while (ctrl->flag > -1){
		std::cout << "Process 1 Sum: " << ctrl->sum << std::flush << std::endl;
		sleep(4); // sleep for 5 seconds.
	 }
    return 0;
}
