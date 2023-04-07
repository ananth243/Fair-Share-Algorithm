#include"fairShareSched.h"

QNode* initQueue(Job *job){
    QNode* head = malloc(sizeof(QNode *));
    head->next=NULL;
    head->job=job;
    return head;
}

void insertQueue(QNode *head, Job *job){
    while (head->next!=NULL) head=head->next;
    head->next = malloc(sizeof(QNode*));
    head=head->next;
    head->job=job;
    head->next=NULL;
}

QNode* deleteQueue(QNode *head, Job *job){
    QNode *prev=NULL,*newHead=head;
    while(head){
        if(head->job == job){
            if(prev==NULL){
                QNode *newHead=head->next;
                //free(head)
                return newHead;
            } else{
                prev->next=head->next;
                // free(head)
                return newHead;
            }
        }
        prev=head;
        head=head->next;
    }
}