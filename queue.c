#include"fairShareSched.h"

QNode* initQueue(Job *job){
    QNode* head = (QNode*) malloc(sizeof(QNode));
    head->next=NULL;
    head->job=job;
    return head;
}

void insertQueue(QNode *head, Job *job){
    while (head->next!=NULL)
        head=head->next;
    head->next = (QNode*) malloc(sizeof(QNode));
    head=head->next;
    head->job=job;
    head->next=NULL;
}

void printQueue(QNode* q){
    while(q){
        // printf("Job ID: %d, Group ID: %d, Base Priority: %d, Arrival Time: %d\n",q->job->jid,q->job->gid, q->job->basePriority, q->job->arrivalTime);
        // printf("Priority: %d, CPU Count:%d, Group Count:%d\n",q->job->calculatedPriority,q->job->cpuCount, q->job->groupCount);
        // for(int i=0;i<q->job->bursts;i++) printf("%d ",q->job->cpu[i]);
        // printf("\n");
        // for(int i=0;i<q->job->bursts;i++) printf("%d ",q->job->io[i]);
        // printf("\n");
        // printf("\n");
        printf("%d->",q->job->jid);
        q=q->next;
    }
        printf("\n");
}
QNode* deleteQueue(QNode *head, Job *job){
    QNode *prev=NULL,*newHead=head;
    while(head){
        if(head->job == job){
            if(prev==NULL){
                QNode *newHead=head->next;
                // free(head);
                return newHead;
            } else{
                prev->next=head->next;
                // free(head);
                return newHead;
            }
        }
        prev=head;
        head=head->next;
    }
}

bool isEmptyQueue(QNode *q){
    return q==NULL;
}