#include <stdio.h>
#include <stdlib.h>
struct process{
    int pid;
    int at;
    int bt;
    int ct;
    int wt;
    int tat;
}p[10];
struct process temp;
void main(){
    int np;
printf("Enter number of process:");
scanf("%d",&np);
for(int i=0;i<np;i++){
    p[i].pid=i;
    printf("Enter process %d arrival time",i);
    scanf("%d",&p[i].at);
    printf("Enter process %d burst time",i);
    scanf("%d",&p[i].bt);
}
//sorting the processes based on their arrival times
for(int i=0;i<np;i++){
    for(int j=i+1;j<np;j++){
        if(p[i].at>p[j].at){
            temp=p[i];
            p[i]=p[j];
            p[j]=temp;
        }
    }
}
//calculating waiting time and turnaround time
float twt=0,ttat=0;

int t=0;
for(int i=0;i<np;i++){
    p[i].ct=t+p[i].bt;
    p[i].tat=p[i].ct-p[i].at;
    p[i].wt=p[i].tat-p[i].bt;
    twt+=p[i].wt;
    ttat+=p[i].tat;
    t=p[i].ct;
}
for(int i=0;i<np;i++){
    for(int j=i+1;j<np;j++){
        if(p[i].pid>p[j].pid){
            temp=p[i];
            p[i]=p[j];
            p[j]=temp;
        }
    }
}
printf("\n PID \t AT \t BT \t CT \t TAT \t WT \n");
for(int i=0;i<np;i++){
printf("\n %d \t %d \t %d \t %d \t %d \t %d \n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
}
printf("Total waiting time :%f",twt);
printf("Total turn around time :%f",ttat);
}