#ifndef _SCHED_FAIR_SHARE
#define _SCHED_FAIR_SHARE

#include<stdlib.h>
#include<stdio.h>

typedef struct{
    int gid;
    int arrivalTime;
    int basePriority;
    int *cpu;
    int *io;
} Job;

struct ReadyQueue{
    Job *job;
    struct ReadyQueue *next;
};

typedef struct ReadyQueue QNode;

QNode* initQueue(Job *job);

void insertQueue(QNode *head, Job *job);

QNode* deleteQueue(QNode *head, Job *job);

void freeMem(QNode *q);

#endif