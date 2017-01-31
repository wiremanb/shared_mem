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

    // if(argc != 3)
    // {
    // 	std::cout << "[!] -> Need two integers.. suggested use: ./a <int> <int>" << std::endl;
    // 	return 1;
    // }
    
    if ( (id = shmget( KEY, SEGSIZE, IPC_CREAT | 0666) ) < 0 )
    	return 1;
    if ( (ctrl = (struct info *) shmat( id, 0, 0)) <= (struct info *) (0) ) 
    	return 1;

    ctrl->flag = 0;
	while (ctrl->flag > -1) {
		if(ctrl->flag == 0)
		{
			std::cout << "Enter two numbers: " << std::flush;
			std::cin >> ctrl->num1 >> ctrl->num2;
			if(ctrl->num1 == -9999 && ctrl->num2 == -9999)
				ctrl->flag = -1;
			else
				ctrl->flag = 1; // Set values.
		}
		else 
			std::cout << std::endl << "Process 1 Sum: " << ctrl->sum << std::flush << std::endl;
	}
    return 0;
}
