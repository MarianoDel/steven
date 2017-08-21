#include "rpi.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

//Externals
extern struct bcm2835_peripheral gpio;

// Exposes the physical address defined in the passed structure using mmap on /dev/mem
int map_peripheral(struct bcm2835_peripheral *p)
{
   // Open /dev/mem
   if ((p->mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
      printf("Failed to open /dev/mem, try checking permissions.\n");
      return -1;
   }

   p->map = mmap(
      NULL,
      BLOCK_SIZE,
      PROT_READ|PROT_WRITE,
      MAP_SHARED,
      p->mem_fd,  // File descriptor to physical memory virtual file '/dev/mem'
      p->addr_p      // Address in physical map that we want this memory block to expose
   );

   if (p->map == MAP_FAILED) {
        perror("mmap");
        return -1;
   }

   p->addr = (volatile unsigned int *)p->map;


   return 0;
}

void unmap_peripheral(struct bcm2835_peripheral *p)
{
	munmap(p->map, BLOCK_SIZE);
	close(p->mem_fd);
}

void GpioConfig_0_to_9 (unsigned int pinmask, unsigned int mode)
{
	*(gpio.addr) &= pinmask;
	*(gpio.addr) |= mode;
}

void GpioConfig_10_to_19 (unsigned int pinmask, unsigned int mode)
{
	*(gpio.addr + 1) &= pinmask;
	*(gpio.addr + 1) |= mode;
}

void GpioConfig_20_to_29 (unsigned int pinmask, unsigned int mode)
{
	*(gpio.addr + 2) &= pinmask;
	*(gpio.addr + 2) |= mode;
}

void GpioSet (unsigned int pin)
{
	*(gpio.addr + 7) |= pin;
}

void GpioClear (unsigned int pin)
{
	*(gpio.addr + 10) |= pin;
}

// void dump_bsc_status() {
//
//     unsigned int s = BSC0_S;
//
//     printf("BSC0_S: ERR=%d  RXF=%d  TXE=%d  RXD=%d  TXD=%d  RXR=%d  TXW=%d  DONE=%d  TA=%d\n",
//         (s & BSC_S_ERR) != 0,
//         (s & BSC_S_RXF) != 0,
//         (s & BSC_S_TXE) != 0,
//         (s & BSC_S_RXD) != 0,
//         (s & BSC_S_TXD) != 0,
//         (s & BSC_S_RXR) != 0,
//         (s & BSC_S_TXW) != 0,
//         (s & BSC_S_DONE) != 0,
//         (s & BSC_S_TA) != 0 );
// }
//
// // Function to wait for the I2C transaction to complete
// void wait_i2c_done() {
//         //Wait till done, let's use a timeout just in case
//         int timeout = 50;
//         while((!((BSC0_S) & BSC_S_DONE)) && --timeout) {
//             usleep(1000);
//         }
//         if(timeout == 0)
//             printf("wait_i2c_done() timeout. Something went wrong.\n");
// }
//
// void i2c_init()
// {
//     INP_GPIO(0);
//     SET_GPIO_ALT(0, 0);
//     INP_GPIO(1);
//     SET_GPIO_ALT(1, 0);
// }
//
// // Priority
//
// int SetProgramPriority(int priorityLevel)
// {
//     struct sched_param sched;
//
//     memset (&sched, 0, sizeof(sched));
//
//     if (priorityLevel > sched_get_priority_max (SCHED_RR))
//         priorityLevel = sched_get_priority_max (SCHED_RR);
//
//     sched.sched_priority = priorityLevel;
//
//     return sched_setscheduler (0, SCHED_RR, &sched);
// }
