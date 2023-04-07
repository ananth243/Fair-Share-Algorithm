#include"fairShareSched.h"

void freeMem(QNode *q){
    while(q){
        free(q->job);
        q=q->next;
    }
    while(q){
        QNode* next=q->next;
        free(q);
        q=next;
    }
}