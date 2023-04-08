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
        printf("%d->",q->job->jid);
        q=q->next;
    }
    printf("\n");
}

QNode* deleteQueue(QNode *head, QNode* node){
    QNode *prev=NULL,*newHead=head;
    while(head){
        if(head==node){
            if(prev==NULL){
                QNode *newHead=head->next;
                return newHead;
            } else{
                prev->next=head->next;
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