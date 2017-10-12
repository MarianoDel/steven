#include "rpi.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

//Externals
extern struct bcm2835_peripheral gpio;
extern struct bcm2835_peripheral pwm;
extern struct bcm2835_peripheral clk;


extern volatile unsigned int *pgpio;
extern volatile unsigned int *ppwm;
extern volatile unsigned int *pclk;
extern volatile unsigned int *ppads;


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

// Exposes the physical address defined in the passed structure using mmap on /dev/mem
//int map_all_know_peripheral(unsigned int *p_gpio, unsigned int *p_pwm, unsigned int *p_driver, unsigned int *p_timer)
int map_all_know_peripheral(void)
{
	unsigned int fd;
   // Open /dev/mem
   if ((fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
      printf("Failed to open /dev/mem, try checking permissions.\n");
      return -1;
   }

   //MAPING GPIOs
   //p_gpio = (volatile unsigned int *) mmap (NULL, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);
	pgpio = mmap (NULL, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);


   if (pgpio == MAP_FAILED)
   {
     perror("mmap on gpio");
      return -1;
   }

   //MAPING PWM
      ppwm = mmap (NULL, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, PWM_BASE);

      if (ppwm == MAP_FAILED)
   {
     perror("mmap on pwm");
      return -1;
   }

   //MAPING CLK FOR PWM
   pclk = mmap (NULL, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, CLK_BASE);

   if (pclk == MAP_FAILED)
   {
     perror("mmap on clk");
      return -1;
   }

   //MAPING DRIVER PADS
   ppads = mmap (NULL, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, DRIVER_BASE);

   if (ppads == MAP_FAILED)
   {
     perror("mmap on driver pads");
      return -1;
   }


   return 0;
}

//void unmap_all_know_peripheral(struct bcm2835_peripheral *p)
//{
//	munmap(p->map, BLOCK_SIZE);
//	close(p->mem_fd);
//}

void unmap_peripheral(struct bcm2835_peripheral *p)
{
	munmap(p->map, BLOCK_SIZE);
	close(p->mem_fd);
}

void GpioConfig_0_to_9 (unsigned int pinmask, unsigned int mode)
{
	// *(gpio.addr) &= pinmask;
	// *(gpio.addr) |= mode;

	*pgpio &= pinmask;
	*pgpio |= mode;

}

void GpioConfig_10_to_19 (unsigned int pinmask, unsigned int mode)
{

  *(pgpio + 1) &= pinmask;
  *(pgpio + 1) |= mode;

}

void GpioConfig_20_to_29 (unsigned int pinmask, unsigned int mode)
{
	*(gpio.addr + 2) &= pinmask;
	*(gpio.addr + 2) |= mode;
}

void GpioSet (unsigned int pin)
{
	*(pgpio + 7) |= pin;
}

void GpioClear (unsigned int pin)
{
	*(pgpio + 10) |= pin;
}

//----- From WiringPi.c -----//
void SetPwm0 (unsigned int mode, unsigned int range, unsigned int clk_div)
{
  u_int32_t pwm_control;
  clk_div &= 4095 ;
  
  GpioConfig_10_to_19 (MASK_PIN8, MODE_PIN8_ALT5);    //PIN18 to PWM0

  //TODO: agregar mapeo a pines alternativos tipo wiring line 544
  usleep(110);      //    delayMicroseconds (110) ;		// See comments in pwmSetClockWPi

  *(ppwm + PWM_CONTROL) = PWM0_ENABLE | PWM0_MS_MODE;
  usleep(10);

  *(ppwm + PWM0_RANGE) = range;
  usleep(10);

  pwm_control = *(ppwm + PWM_CONTROL);		// preserve PWM_CONTROL

// We need to stop PWM prior to stopping PWM clock in MS mode otherwise BUSY
// stays high.

  *(ppwm + PWM_CONTROL) = 0;				// Stop PWM

// Stop PWM clock before changing divisor. The delay after this does need to
// this big (95uS occasionally fails, 100uS OK), it's almost as though the BUSY
// flag is not working properly in balanced mode. Without the delay when DIV is
// adjusted the clock sometimes switches to very slow, once slow further DIV
// adjustments do nothing and it's difficult to get out of this mode.

  *(pclk + PWMCLK_CNTL) = BCM_PASSWORD | 0x01 ;	// Stop PWM Clock
  usleep(110);			// prevents clock going sloooow

    while ((*(pclk + PWMCLK_CNTL) & 0x80) != 0)	// Wait for clock to be !BUSY
      usleep (1) ;

    *(pclk + PWMCLK_DIV)  = BCM_PASSWORD | (clk_div << 12) ;

    *(pclk + PWMCLK_CNTL) = BCM_PASSWORD | 0x11 ;	// Start PWM clock
    *(ppwm + PWM_CONTROL) = pwm_control ;		// restore PWM_CONTROL

    usleep(10);
  
}

void Pwm0Data (unsigned int value)
{
  *(ppwm + PWM0_DATA) = value;	  //cargo valor al pwm
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
