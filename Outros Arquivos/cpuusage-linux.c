/*
 Program that prints CPU usage and the idle CPU time.
 It measure the delta between two samples that are acquired between
 1 second interval.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysctl.h>
#include <sys/types.h>

struct CPUSample {
    int totalSystemTime;
    int totalUserTime;
    int totalIdleTime;
};

void get_cpusample(struct CPUSample *sample)
{
    FILE *f;
    int user, nice, system, idle;
    char cpu[16];

    f = fopen("/proc/stat","r");
    if (!f) {
       printf("Error reading file.\n");
       exit(1);
    }

    fscanf(f,"%s %d %d %d %d",cpu,&user,&nice,&system,&idle);
    
    sample->totalSystemTime =  system;
    sample->totalUserTime   =  user;
    sample->totalIdleTime   =  idle;
}

void print_cpuusage(struct CPUSample *sample1, struct CPUSample *sample2)
{
    struct CPUSample delta;
    
    delta.totalSystemTime = sample2->totalSystemTime - sample1->totalSystemTime;
    delta.totalUserTime   = sample2->totalUserTime   - sample1->totalUserTime;
    delta.totalIdleTime   = sample2->totalIdleTime   - sample1->totalIdleTime;
    
    int total = delta.totalSystemTime + delta.totalUserTime + delta.totalIdleTime;

    double onePercent = total/100.0;

    printf("User  : %f ", (double)delta.totalUserTime/(double)onePercent);
    printf("System: %f ", (double)delta.totalSystemTime/(double)onePercent);
    printf("Idle  : %f\r", (double)delta.totalIdleTime/(double)onePercent); fflush(stdout);
}

int main() {
    
    struct CPUSample sample1, sample2;
    
    while (1) {
      get_cpusample(&sample1);
      sleep(1);
      get_cpusample(&sample2);
    
      print_cpuusage(&sample1, &sample2);
    }
    
}
