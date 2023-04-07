#include"fairShareSched.h"

int main(int argc, char *argv[]){
    if(argc==1){
        printf("Error: Time slice not defined\n");
        return 1;
    }
    int timeSlice = atoi(argv[1]);
    printf("Entered Quantum time: %d\n", timeSlice);
    int n;
    FILE* fp = fopen("input.txt","r");
    fscanf(fp,"%d",&n);
    Job *jobs = (Job*) malloc(sizeof(Job *)*n);
    QNode *q;
    for(int i=0;i<n;i++){
        Job *job = malloc(sizeof(Job *));
        fscanf(fp,"%d",&job->gid);
        fscanf(fp,"%d",&job->basePriority);
        fscanf(fp,"%d",&job->arrivalTime);
        int bursts;
        fscanf(fp,"%d",&bursts);
        job->cpu = (int *) malloc(sizeof(int *)*bursts);
        job->io = (int *) malloc(sizeof(int *)*bursts);
        for(int i=0;i<bursts;i++) fscanf(fp,"%d",&job->cpu[i]);
        for(int i=0;i<bursts;i++) fscanf(fp,"%d",&job->io[i]);
        if(i==0) q = initQueue(job); 
        else insertQueue(q,job);
    }
    int time=0;
    freeMem(q);
    fclose(fp);
    return 0;
}