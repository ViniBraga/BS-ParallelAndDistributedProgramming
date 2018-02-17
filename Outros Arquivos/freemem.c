/*
 Program that prints the available memory in kilobytes.
 */

#import <sys/sysctl.h>
#import <mach/host_info.h>
#import <mach/mach_host.h>
#import <mach/task_info.h>
#import <mach/task.h>

#include <stdio.h>
#include <stdlib.h>

void print_freemem() {
    int mib[6];
    mib[0] = CTL_HW;
    mib[1] = HW_PAGESIZE;

    int pagesize;
    size_t length;
    
    length = sizeof (pagesize);
    
    if (sysctl (mib, 2, &pagesize, &length, NULL, 0) < 0) {
        printf ("Error getting page size.\n");
        exit(1);
    }

    mach_msg_type_number_t count = HOST_VM_INFO_COUNT;
    vm_statistics_data_t vmstat;
    
    if (host_statistics (mach_host_self (), HOST_VM_INFO, (host_info_t) &vmstat, &count) != KERN_SUCCESS) {
        printf ("Error getting VM statistics.\n");
        exit(1);
    }

    double unit = 1024;
    printf("Total free memory: %3.1f KB\n",vmstat.free_count * pagesize / unit);

}

int main() {

  print_freemem();

}