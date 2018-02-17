/*
 Program that prints CPU usage and the idle CPU time.
 It measure the delta between two samples that are acquired between
 1 second interval.
 */
#include <stdio.h>
#include <sys/sysctl.h>
#include <sys/types.h>
#include <mach/mach.h>
#include <mach/processor_info.h>
#include <mach/mach_host.h>

struct CPUSample {
    int totalSystemTime;
    int totalUserTime;
    int totalIdleTime;
};

void get_cpusample(struct CPUSample *sample)
{
    mach_msg_type_number_t count;
    host_cpu_load_info_data_t r_load;
        
    count = HOST_CPU_LOAD_INFO_COUNT;
    if (host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, (int *)&r_load, &count) != KERN_SUCCESS) {
        printf("Error sampling.\n");
        sample->totalIdleTime = sample->totalSystemTime = sample->totalUserTime = 0;
        return;
    }
    
    sample->totalSystemTime = r_load.cpu_ticks[CPU_STATE_SYSTEM];
    sample->totalUserTime   = r_load.cpu_ticks[CPU_STATE_USER] + r_load.cpu_ticks[CPU_STATE_NICE];
    sample->totalIdleTime   = r_load.cpu_ticks[CPU_STATE_IDLE];
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
