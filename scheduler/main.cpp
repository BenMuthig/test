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
//#include "scheduler.h"
#include "processes.h"
using namespace std;

pid_t pid1, pid2, pid3;

timeval start;
timeval stop;
const int tick = 10000000;

//2D array containing pIDs and schedule durations
const int size = 10;
int schedule[2][size] = {0};

//Adds process to schedule for defined time in µs. Process can be added multiple times.
int sched_add(pid_t pid, int time);

//Runs scheduled process for specified time.
void run_sched();

int main()
{
	pid1 = fork();
	if (pid1)
		pid2 = fork();
	if (pid1 && pid2)
		pid3 = fork();

	if (pid1 && pid2 && pid3){

		kill(pid1, SIGSTOP);
		kill(pid2, SIGSTOP);
		kill(pid3, SIGSTOP);
        cout << "STOP" << endl;

        sched_add(pid1, 10000000);
        sched_add(pid2, 10000000);
        sched_add(pid3, 10000000);

        for (int pos = 0; pos < size; pos++){
            cout << schedule[0][pos] << endl;
        }

		while(true){
            run_sched();
		}
	}


	if (pid1 == 0){
		int i = 0;
		while(true){
			cout << i << endl;
			i++;
			usleep(1000000);
		}
	}
	if (pid2 == 0){
		int i = 0;
		cout << pid1 << endl;
		while(true){
			cout << i << endl;
			i--;
            usleep(1000000);
		}
	}
    if (pid3 == 0){
		int i = 0;
		while(true){
			cout << i << endl;
			i += 100;
			usleep(1000000);
		}
	}

	return 0;
}

//Adds process to schedule for defined time in µs. Process can be added multiple times.
int sched_add(pid_t pid, int time){

    for (int pos = 0; pos < size; pos++){

        if (schedule[0][pos] == 0){            
            schedule[0][pos] = pid;
            schedule[1][pos] = time;
            return 0;
        }
    }
    return -1;
}

//Runs scheduled process for specified time.
void run_sched(){

    gettimeofday(&start, 0);

    for (int pos = 0; pos < size; pos++){

        cout << "Position: " << pos << endl;

        if (schedule[0][pos]){

            kill(schedule[0][pos], SIGCONT);
            cout << schedule[0][pos] << " Started" << endl;
            usleep(schedule[1][pos]);
            kill(schedule[0][pos], SIGSTOP);
            cout << schedule[0][pos] << " Stopped" << endl;
        }

        gettimeofday(&stop, 0);
        if ((stop.tv_sec - start.tv_sec)/1000000 + stop.tv_usec - start.tv_usec > tick){
            cout << "Time exceeded!" << endl;
            return;
        }
    }

    usleep(tick - (stop.tv_sec - start.tv_sec)/1000000 + stop.tv_usec - start.tv_usec);
}
