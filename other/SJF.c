#include<stdio.h>
#include<stdlib.h>

struct process {
    int pid, at, bt, ct, wt, tat, flag;
} p[10];

struct process temp;

void main() {
    int np;
    printf("Enter number of processes: ");
    scanf("%d", &np);

    for(int i = 0; i < np; i++) {
        p[i].pid = i;
        p[i].flag = 0;
        printf("Enter process %d arrival time: ", i);
        scanf("%d", &p[i].at);
        printf("Enter process %d burst time: ", i);
        scanf("%d", &p[i].bt);
    }

    // Sorting the processes based on their burst times
    for(int i = 0; i < np; i++) {
        for(int j = i + 1; j < np; j++) {
            if(p[i].bt > p[j].bt) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int t = 0, twt = 0, ttat = 0, flag = 0;
    while(flag != 1) {
        flag = 1;
        int min_bt = INT_MAX;
        int min_idx = -1;

        for(int i = 0; i < np; i++) {
            if(p[i].at <= t && p[i].flag == 0 && p[i].bt < min_bt) {
                min_idx = i;
                min_bt = p[i].bt;
                flag = 0;
            }
        }

        if(min_idx == -1)
            t++;
        else {
            p[min_idx].ct = t + p[min_idx].bt;
            p[min_idx].tat = p[min_idx].ct - p[min_idx].at;
            p[min_idx].wt = p[min_idx].tat - p[min_idx].bt;
            p[min_idx].flag = 1;
            t = p[min_idx].ct;
            ttat += p[min_idx].tat;
            twt += p[min_idx].wt;
        }
    }

    for(int i = 0; i < np; i++) {
        for(int j = i + 1; j < np; j++) {
            if(p[i].pid > p[j].pid) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    printf("\n PID \t AT \t BT \t CT \t TAT \t WT \n");
    for(int i = 0; i < np; i++) {
        printf("\n %d \t %d \t %d \t %d \t %d \t %d \n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("Total waiting time: %d\n", twt);
    printf("Total turnaround time: %d\n", ttat);
}
