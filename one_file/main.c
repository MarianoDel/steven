// Direct register access
//  How to access GPIO registers from C-code on the Raspberry-Pi
//  Example program

// Access from ARM Running Linux
#include <stdio.h>
// #include <stdlib.h>
// #include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

// Externals ----
// int  mem_fd;
// void *gpio_map;
// struct bcm2835_peripheral gpio = {GPIO_BASE};	//old

volatile unsigned int *pgpio ;
volatile unsigned int *pgpio;
volatile unsigned int *ppwm;
volatile unsigned int *pclk;
volatile unsigned int *ppads;


// Typedef and Macros ----------
#define BLOCK_SIZE	   (4*1024)
#define BCM2708_PERI_BASE   0x3F000000
#define GPIO_BASE          (BCM2708_PERI_BASE + 0x200000)

// PWM
//	Word offsets into the PWM control region
#define	PWM_CONTROL 0
#define	PWM_STATUS  1
#define	PWM0_RANGE  4
#define	PWM0_DATA   5
#define	PWM1_RANGE  8
#define	PWM1_DATA   9

#define	PWM0_MS_MODE    0x0080  // Run in MS mode
#define	PWM1_MS_MODE    0x8000  // Run in MS mode

//PINMODE ALTERNATIVE
#define MODE_PIN8_ALT5      0x02000000

#define PIN8                0x00000100
#define MASK_PIN9           0xC7FFFFFF
#define MODE_PIN9_OUTPUT    0x08000000

// Globals ------
// struct bcm2835_peripheral bsc0 = {BSC0_BASE};

// Module Function Declaration ----------
void GpioConfig_0_to_9 (unsigned int, unsigned int);
void GpioSet (unsigned int);
void GpioClear (unsigned int);
unsigned int GpioIsSet (unsigned int);


int main(int argc, char **argv)
{
    int i;
    unsigned int fd;

    // Set up gpio pointer for direct register access
    printf("setting up...\n");
    
    // Open /dev/mem
    if ((fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0)
    {
        printf("Failed to open /dev/mem, try checking permissions.\n");
        return -1;
    }

   //MAPING GPIOs
    pgpio = mmap (NULL, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);

    if (pgpio == MAP_FAILED)
    {
        perror("mmap on gpio");
        return -1;
    }

    //CONFIG GPIOs
    GpioConfig_0_to_9 (MASK_PIN9, MODE_PIN9_OUTPUT);

    //if its all ok, go to application
    printf("setup done!\n");

    while (1)
    {
        if (GpioIsSet(PIN9))
            GpioClear (PIN9);
        else
            GpioSet (PIN9);
        
        usleep(1000);
        // GpioSet (PIN9);
        // usleep(1000);
        // GpioClear (PIN9);
        // usleep(1000);
    }

    return 0;
}

void GpioConfig_0_to_9 (unsigned int pinmask, unsigned int mode)
{
    *pgpio &= pinmask;
    *pgpio |= mode;
}

void GpioConfig_10_to_19 (unsigned int pinmask, unsigned int mode)
{
  *(pgpio + 1) &= pinmask;
  *(pgpio + 1) |= mode;
}

void GpioSet (unsigned int pin)
{
    *(pgpio + 7) |= pin;
}

void GpioClear (unsigned int pin)
{
    *(pgpio + 10) |= pin;
}

unsigned int GpioIsSet (unsigned int pin)
{
    return (*(pgpio + 13) & pin);
}

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
