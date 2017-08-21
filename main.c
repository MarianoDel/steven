// Direct register access
//  How to access GPIO registers from C-code on the Raspberry-Pi
//  Example program
//  15-January-2012
//  Dom and Gert
//  Revised: 15-Feb-2013


// Access from ARM Running Linux
#include <stdio.h>
// #include <stdlib.h>
// #include <fcntl.h>
// #include <sys/mman.h>
#include <unistd.h>
#include "rpi.h"

// Externals ----
// int  mem_fd;
// void *gpio_map;
struct bcm2835_peripheral gpio = {GPIO_BASE};	//old

volatile unsigned int *pgpio ;			//new ones
volatile unsigned int *pwm ;
volatile unsigned int *clk ;
volatile unsigned int *pads ;



// Globals ------
struct bcm2835_peripheral bsc0 = {BSC0_BASE};


// // I/O access
// volatile unsigned *gpio;
//

//--- Module Function ---//
// void setup_io();
// void UDelay (void);


// void printButton(int g)
// {
//   if (GET_GPIO(g)) // !=0 <-> bit is 1 <- port is HIGH=3.3V
//     printf("Button pressed!\n");
//   else // port is LOW=0V
//     printf("Button released!\n");
// }

int main(int argc, char **argv)
{
  int i;

  // Set up gpi pointer for direct register access
  printf("setting up...\n");

//  if(map_peripheral(&gpio) == -1)  //ONLY AS ROOT
  if(map_all_know_peripheral(pgpio, pwm, pads, clk) == -1)  //ONLY AS ROOT
  {
	  printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
	  return -1;
  }

  // Configuratin of pins IO
  printf("configuring IOs...\n");

  GpioConfig_0_to_9 (MASK_PIN9, MODE_PIN9_OUTPUT);

  printf("toggling leds...\n");

  for (i=0; i<10000; i++)
  {
	  GpioSet (PIN9);
	  usleep(1000);

	  GpioClear (PIN9);
     usleep(1000);
  }

  printf("setting down...\n");


  //No need /dev/mem anymore
<<<<<<< HEAD
  //  unmap_peripheral(&gpio);
=======
//  unmap_peripheral(&pgpio);
>>>>>>> origin/master

  return 0;

} // main

// void UDelay (void)
// {
//   long int i;
//
//   for (i=0; i<20000; i++)
//     {
//       asm volatile (
//                     " nop\n "
//                     " nop\n "
//                     " nop ");
//     }
//
// }
//
// //
// // Set up a memory regions to access GPIO
// // ONLY AS ROOT
// void setup_io()
// {
//    /* open /dev/mem */
//    if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
//       printf("can't open /dev/mem \n");
//       exit(-1);
//    }
//
//    /* mmap GPIO */
//    gpio_map = mmap(
//       NULL,             //Any adddress in our space will do
//       BLOCK_SIZE,       //Map length
//       PROT_READ|PROT_WRITE,// Enable reading & writting to mapped memory
//       MAP_SHARED,       //Shared with other processes
//       mem_fd,           //File to map
//       GPIO_BASE         //Offset to GPIO peripheral
//    );
//
//    close(mem_fd); //No need to keep mem_fd open after mmap
//
//    if (gpio_map == MAP_FAILED) {
//       printf("mmap error %d\n", (int)gpio_map);//errno also set!
//       exit(-1);
//    }
//
//    // Always use volatile pointer!
//    gpio = (volatile unsigned *)gpio_map;
//
//
// } // setup_io

// GPIO Pull Up/Pull Down Register Example
//
//    // enable pull-up on GPIO24&25
//    GPIO_PULL = 2;
//    short_wait();
//    // clock on GPIO 24 & 25 (bit 24 & 25 set)
//    GPIO_PULLCLK0 = 0x03000000;
//    short_wait();
//    GPIO_PULL = 0;
//    GPIO_PULLCLK0 = 0;
