#include"fairShareSched.h"

void freeMem(QNode *q){
    QNode *temp;
    while(q!=NULL){
        temp=q;
        q=q->next;
        free(temp->job->cpu);
        free(temp->job->io);
        free(temp->job);
        free(temp);
    }
}