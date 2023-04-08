#include"fairShareSched.h"

int getNumberOfGroups(QNode* q, int currentTime){
    Set *set = initSet();
    while (q)
    {
        // printf("%d, %d\n",q->job->jid,q->job->arrivalTime);
        if(q->job->arrivalTime<=currentTime){
            insertInSet(set,q->job->gid);
            // printf("%d %d\n",set->size,q->job->gid);
        }
        q=q->next;
    }
    int ans = set->size;
    // printf("Size: %d, Time: %d\n\n",ans,currentTime);
    freeSet(set);
    return ans;
}

QNode* pickAJobToExecute(QNode* q, int currentTime){
    QNode* ans=NULL;
    int priority=INT_MAX;
    while(q){
        if(q->job->arrivalTime<=currentTime && q->job->calculatedPriority < priority){
            priority=q->job->calculatedPriority;
            ans=q;
        }
        q=q->next;
    }
    return ans;
}

void calculatePriority(QNode *node, int groups){
    // printf("JID: %d,GID:%d, CPU: %d, Group: %d, Priority: %d\n",node->job->jid,node->job->gid,node->job->cpuCount,node->job->groupCount, node->job->calculatedPriority);
    node->job->cpuCount/=2;
    node->job->groupCount/=2;
    node->job->calculatedPriority = node->job->basePriority + (int)(node->job->cpuCount/2) + (int)(node->job->groupCount*groups/4);
    // printf("JID: %d, CPU: %d, Group: %d, Priority: %d\n",node->job->jid,node->job->cpuCount,node->job->groupCount, node->job->calculatedPriority);
    // printf("\n");
}

void increaseGroupCount(QNode *q, int gid, int execution, int currentTime){
    while(q){
        if(q->job->gid==gid && q->job->arrivalTime<=currentTime) q->job->groupCount+=execution;
        q=q->next;
    }
}

QNode*executeJob(QNode *q, QNode* node, int *currentTime, int timeSlice, int prevDecisionPoint){
    int execution = node->job->cpu[node->job->cpuIndex]; //!TODO Should be 60-100 % of this value
    if(execution <= timeSlice){
        node->job->cpu[node->job->cpuIndex]=0;
        node->job->cpuIndex++;
        increaseGroupCount(q, node->job->gid, execution, *currentTime);
        *currentTime+=execution;
        if(node->job->cpuIndex==node->job->bursts) q=deleteQueue(q,node->job);
        else{
            node->job->arrivalTime = *currentTime+ node->job->io[node->job->ioIndex];
            node->job->calculatedPriority=node->job->basePriority;
            node->job->ioIndex++;
            node->job->cpuCount=0;
            node->job->groupCount=0;
            node->job->wentForIO=true;
        }
    }
    else{
        execution=timeSlice;
        node->job->cpu[node->job->cpuIndex]-=timeSlice;
        increaseGroupCount(q, node->job->gid, execution, *currentTime);
        *currentTime+=execution;
        // node->job->arrivalTime = *currentTime;
        node->job->cpuCount+=execution;
    }
    // Calculate Priority for each job
    int groups = getNumberOfGroups(q,prevDecisionPoint);
    QNode* temp=q;
    while(q){
        if(q->job->arrivalTime<=prevDecisionPoint) calculatePriority(q,groups);
        q=q->next;
    }
    return temp;
}

int findNextJob(QNode* q){
    int minTime=INT_MAX;
    while(q){
        if(q->job->arrivalTime<minTime) minTime=q->job->arrivalTime;
        q=q->next;
    }
    return minTime;
}

void equateGroupCount(QNode *q, QNode* node){
    while(q){
        if(q->job->gid==node->job->gid && q->job->wentForIO==false){
            node->job->groupCount=q->job->groupCount;
            return;
        }
        q=q->next;
    }
}

void groupCountFunction(QNode *q, int currentTime){
    QNode *temp=q;
    while(q){
        if(q->job->wentForIO && q->job->arrivalTime<=currentTime){
            // Find other process that hasn't gone and equate group count
            // Else it's group count is 0
            q->job->groupCount=0;
            equateGroupCount(temp,q);
            q->job->wentForIO=false;
        }
        q=q->next;
    }
}
