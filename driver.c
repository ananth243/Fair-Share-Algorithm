#include<stdio.h>
#include<stdlib.h>
#include"fairShareSched.h"

int main(int argc, char *argv[]){
    printf("Entry point\n");
    if(argc==1){
        printf("Error: Time slice not defined\n");
        return 1;
    }
    int qt = atoi(argv[1]);
    printf("Entered Quantum time: %d\n", qt);
    int n;
    FILE* fp = fopen("input.txt","r");
    fscanf(fp,"%d",&n);
    Job jobs = (Job) malloc(sizeof(Job)*n);
    for(int i=0;i<n;i++){
        Job job;
        fscanf(fp,"%d",&job.gid);
        fscanf(fp,"%d",&job.basePriority);
        fscanf(fp,"%d",&job.arrivalTime);
        int bursts;
        fscanf(fp,"%d",&bursts);
        job.cpu = (int *) malloc(sizeof(int *)*bursts);
        job.io = (int *) malloc(sizeof(int *)*bursts);
        for(int i=0;i<bursts;i++) fscanf(fp,"%d",&job.cpu[i]);
        for(int i=0;i<bursts;i++) fscanf(fp,"%d",&job.io[i]);
    }
    fclose(fp);
    // cleanup_function(jobs,n);
    return 0;
}