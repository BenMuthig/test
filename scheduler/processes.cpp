#include "processes.h"

//Process function that counts from "start", up (true) or down (false), with step size "stepsize"
void pid_do(int start, bool upDown, int stepsize){

    int i = start;

    if (upDown){
        while(true){
            i += stepsize;
            cout << i << endl;
        }
    }
    else{
        while(true){
            i -= stepsize;
            cout << i << endl;
        }
    }
}