#include "scheduler.h"

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
