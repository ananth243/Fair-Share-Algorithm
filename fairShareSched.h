#ifndef _SCHED_FAIR_SHARE
#define _SCHED_FAIR_SHARE

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define INT_MAX 2147483647
#define INT_MIN -2147483648
#define forn(k, n) for (int i = k; i < n; i++)
#define UPPER 100
#define LOWER 60

// Job definiton
typedef struct
{
    int jid; // Job ID
    int gid; // Group ID
    int arrivalTime;
    int basePriority;
    int calculatedPriority;
    int cpuIndex;
    int ioIndex;
    int bursts; // The number of CPU bursts for this job
    int *cpu;
    int *io;
    int cpuCount;
    int groupCount;
    bool wentForIO;
} Job;

// Queue implementation
struct ReadyQueue
{
    Job *job;
    struct ReadyQueue *next;
};

typedef struct ReadyQueue QNode;

QNode *initQueue(Job *job);

void insertQueue(QNode *head, Job *job);

void printQueue(QNode *q);

// Deletes a node "node" from the queue. Returns head of queue after deletion
QNode *deleteQueue(QNode *head, QNode *node);

// Job executions

// Function picks next job to execute
QNode *pickAJobToExecute(QNode *q, int currentTime);

// Returns head of queue after executing the job
QNode *executeJob(QNode *q, QNode *node, int *currentTime, int timeSlice, int prevDecisionPoint);

// Calculates priorities for all processes after execution of a job
void calculatePriority(QNode *node, int groups);

// Function finds next job to execute when CPU becomes idle and returns the arrival time of the next job
int findNextJob(QNode *q);

// Function increases group count of any newly arrived processes
void increaseGroupCount(QNode *q, int gid, int execution, int currentTime);

// Function returns the number of groups present for execution for calculating priority
int getNumberOfGroups(QNode *q, int currentTime);

// Function equates the group count of all members of the current executed process
void equateGroupCount(QNode *q, QNode *node);

// Function adds group count for any newly arrived processes
void groupCountFunction(QNode *q, int currentTime);

// Set declarations
struct Group
{
    int gid;
    struct Group *next;
};

typedef struct
{
    int size;
    struct Group *next;
} Set;

Set *initSet();

void insertInSet(Set *set, int gid);

void printSet(Set *set);

void freeSet(Set *set);

#endif