//============================================================================
// Name        : scheduler.cpp
// Author      : Benjamin James Muthig
// Version     : final final final
// Copyright   : Credit author
// Description : Scheduler in C++
//============================================================================

#include "head.h"
using namespace std;

pid_t pid1, pid2, pid3;

int main()
{
    
	double time, old_time;
	scheduler p1;
	scheduler p2;
	scheduler p3;

	pid1 = fork();
	if (pid1)
		pid2 = fork();
	if (pid1 && pid2)
		pid3 = fork();

	if (pid1 && pid2 && pid3){

		kill(pid1, SIGSTOP);
		kill(pid2, SIGSTOP);
		kill(pid3, SIGSTOP);

		while(true){

			time = clock();		//set clock value here to avoid triggering time check on first run
			cout << "Brake check" << endl;

			while(true){

				old_time = time;
				kill(pid1, SIGSTOP);
				usleep(1000000);
				kill(pid1, SIGCONT);

				time = clock();
				cout << (time - old_time) / CLOCKS_PER_SEC << endl;
				if ((time - old_time) / CLOCKS_PER_SEC > 0.1)
					break;

				usleep(1000000);
			}
		}
	}

}
