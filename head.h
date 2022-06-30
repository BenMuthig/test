#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

class scheduler{
    public:
        void pid1_do();
        void pid2_do();
        void pid3_do();
        scheduler();

    private:
        pid_t pid1,pid2,pid3;
};
