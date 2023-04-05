#ifndef _SCHED_FAIR_SHARE
#define _SCHED_FAIR_SHARE

typedef struct{
    int gid;
    int arrivalTime;
    int basePriority;
    int *cpu;
    int *io;
} Job;

// Function to free up all the allocated memory
// extern int cleanup_function(Job jobs);

#endif