#pragma once

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
using namespace std;

timeval start;
timeval stop;
const int tick = 1000000;

//2D array containing pIDs and schedule durations
const int size = 10;
int schedule[2][size] = {0};

//Adds process to schedule for defined time in µs. Process can be added multiple times.
int sched_add(pid_t pid, int time);

//Runs scheduled process for specified time.
void run_sched();