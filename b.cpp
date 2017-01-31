#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "shared_info.h"

int main(int argc, char *argv[])
{  
    int  i=0, id=0;
    struct info *ctrl=NULL;
    
    if ( (id = shmget( KEY, SEGSIZE,IPC_CREAT | 0666) ) < 0 )
    	return 1;
    if ( (ctrl = (struct info *) shmat( id, 0, 0)) <= (struct info *) (0) ) 
    	return 1;

    while(ctrl->flag > -1)
    {
    	if(ctrl->flag == 1)
    	{
	    	ctrl->sum = ctrl->num1 + ctrl->num2;
	    	ctrl->flag = 0;
	    	std::cout << "Process 2 Sum: " << ctrl->sum << std::flush << std::endl;
    	}
    }
    std::cout << "Process 1 sent kill sig." << std::endl;
    return 0;
}
