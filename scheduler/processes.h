#pragma once

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
using namespace std;

//Process function that counts from "start", up or down, with step size "stepsize"
void pid_do(int start, bool upDown, int stepsize);