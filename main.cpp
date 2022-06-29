//============================================================================
// Name        : scheduler.cpp
// Author      : Benjamin James Muthig
// Version     : final final final
// Copyright   : Credit author
// Description : Scheduler in C++
//============================================================================

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
using namespace std;

int main()
{
    timeval start, stop;
	pid_t pid1, pid2, pid3;
	double time, old_time;

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

			while(true){

				gettimeofday(&start, 0);
				//kill(pid1, SIGSTOP);
				usleep(1000000);
				//kill(pid1, SIGCONT);

				gettimeofday(&stop, 0);
				cout << stop.tv_sec - start.tv_sec << "s " << stop.tv_usec - start.tv_usec << "µs" << endl;
				if ((stop.tv_sec - start.tv_sec)*1000000 + stop.tv_usec - start.tv_usec > 100000)
					break;

				usleep(1000000);
			}
            cout << "Brake check" << endl;
		}
	}


	if (pid1 == 0){
		int i = 0;
		while(true){
			//kill(pid2, SIGSTOP);
			cout << i << endl;
			i++;
			usleep(10000);
		}
	}
	if (pid2 == 0){
		int i = 0;
		cout << pid1 << endl;
		while(true){
			//kill(pid1, SIGSTOP);
			cout << i << endl;
			i--;
			if (i == -5)
				kill(pid1, SIGCONT);
			sleep(1);
		}
	}

	return 0;
}