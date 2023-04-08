#include"fairShareSched.h"

int main(int argc, char *argv[]){
    if(argc==1){
        printf("Invalid Arguments\n");
        return 1;
    }
    if(argc==2){
        printf("Error: Time slice not defined\n");
        return 1;
    }
    int timeSlice = atoi(argv[2]);
    int n;
    FILE* fp = fopen(argv[1],"r");
    fscanf(fp,"%d",&n);
    QNode *q=NULL;
    int totalExecutionTime=0;
    for(int i=0;i<n;i++){
        Job *job = (Job *)malloc(sizeof(Job));
        fscanf(fp,"%d",&job->gid);
        fscanf(fp,"%d",&job->basePriority);
        job->calculatedPriority=job->basePriority;
        job->jid=i+1;
        fscanf(fp,"%d",&job->arrivalTime);
        int bursts;
        fscanf(fp,"%d",&bursts);
        job->bursts=bursts;
        job->ioIndex=0;
        job->cpuIndex=0;
        job->groupCount=0;
        job->cpuCount=0;
        job->cpu = malloc(sizeof(int)*bursts);
        job->io = malloc(sizeof(int)*bursts);
        job->wentForIO=false;
        for(int i=0;i<bursts;i++) fscanf(fp,"%d",&job->cpu[i]);
        for(int i=0;i<bursts;i++) fscanf(fp,"%d",&job->io[i]);
        if(i==0) q = initQueue(job); 
        else insertQueue(q,job);
    }
    int time=0,prevDecisionPoint=0;
    while(q){
        QNode* node = pickAJobToExecute(q, time);
        if(node==NULL){
            // CPU idle for time - nextJobArrivalTime
            int nextJobArrivalTime = findNextJob(q);
            printf("CPU idle from %d to %d\n",time,nextJobArrivalTime);
            time=nextJobArrivalTime;
        }
        else{
            q=executeJob(q,node, &time, timeSlice, prevDecisionPoint);
            printf("Job %d executed from %d to %d\n",node->job->jid,prevDecisionPoint, time);
            prevDecisionPoint=time;
            groupCountFunction(q, time);
        }
    }
    free(q);
    fclose(fp);
    return 0;
}