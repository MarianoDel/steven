
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RPI_H
#define __RPI_H

/* Board Configuration -------------------------------------*/
// Define which Raspberry Pi board are you using. Take care to have defined only one at time.
//#define RPI
//#define RPI2
#define RPI3

//--- Exported types ---//
//--- Exported constants ---//
//--- Exported macro ---//
#ifdef RPI
#define BCM2708_PERI_BASE		0x20000000
#define GPIO_BASE					(BCM2708_PERI_BASE + 0x200000)	// GPIO controller
#define BSC0_BASE					(BCM2708_PERI_BASE + 0x205000)	// I2C controller
#endif

#if defined RPI2 || defined RPI3
#define BCM2708_PERI_BASE		0x3F000000
#define GPIO_BASE					(BCM2708_PERI_BASE + 0x200000)	// GPIO controller. Maybe wrong. Need to be tested.
#define PWM_BASE					(BCM2708_PERI_BASE + 0x20C000)	// PWM controller. Maybe wrong. Need to be tested.
#define CLK_BASE					(BCM2708_PERI_BASE + 0x101000)	// CLK controller. Maybe wrong. Need to be tested.
#define DRIVER_BASE				(BCM2708_PERI_BASE + 0x100000)	// Drive Strenght controller. Maybe wrong. Need to be tested.
#define TIMER_BASE				(BCM2708_PERI_BASE + 0x00B000)	// Timer controller. Maybe wrong. Need to be tested.
#define BSC0_BASE					(BCM2708_PERI_BASE + 0x804000)	// I2C controller
#endif

#define PAGE_SIZE			(4*1024)
#define BLOCK_SIZE		(4*1024)

//----- From WiringPi.c ----//
// BCM Magic
#define	BCM_PASSWORD		0x5A000000

// PWM
//	Word offsets into the PWM control region

#define	PWM_CONTROL 0
#define	PWM_STATUS  1
#define	PWM0_RANGE  4
#define	PWM0_DATA   5
#define	PWM1_RANGE  8
#define	PWM1_DATA   9

//	Clock register offsets

#define	PWMCLK_CNTL	40
#define	PWMCLK_DIV	41

#define	PWM0_MS_MODE    0x0080  // Run in MS mode
#define	PWM0_USEFIFO    0x0020  // Data from FIFO
#define	PWM0_REVPOLAR   0x0010  // Reverse polarity
#define	PWM0_OFFSTATE   0x0008  // Ouput Off state
#define	PWM0_REPEATFF   0x0004  // Repeat last value if FIFO empty
#define	PWM0_SERIAL     0x0002  // Run in serial mode
#define	PWM0_ENABLE     0x0001  // Channel Enable

#define	PWM1_MS_MODE    0x8000  // Run in MS mode
#define	PWM1_USEFIFO    0x2000  // Data from FIFO
#define	PWM1_REVPOLAR   0x1000  // Reverse polarity
#define	PWM1_OFFSTATE   0x0800  // Ouput Off state
#define	PWM1_REPEATFF   0x0400  // Repeat last value if FIFO empty
#define	PWM1_SERIAL     0x0200  // Run in serial mode
#define	PWM1_ENABLE     0x0100  // Channel Enable


// IO Acces
struct bcm2835_peripheral {
    unsigned long addr_p;
    int mem_fd;
    void *map;
    volatile unsigned int *addr;
};

//PINMASK
#define MASK_PIN0			0xFFFFFFF8
#define MASK_PIN1			0xFFFFFFC7
#define MASK_PIN2			0xFFFFFE3F
#define MASK_PIN3			0xFFFFF1FF
#define MASK_PIN4			0xFFFF8FFF
#define MASK_PIN5			0xFFFC7FFF
#define MASK_PIN6			0xFFE3FFFF
#define MASK_PIN7			0xFF1FFFFF
#define MASK_PIN8			0xF8FFFFFF
#define MASK_PIN9			0xC7FFFFFF

//PINMODE INPUT
#define MODE_PIN0_INPUT			0x00000000
#define MODE_PIN1_INPUT			0x00000000
#define MODE_PIN2_INPUT			0x00000000
#define MODE_PIN3_INPUT			0x00000000
#define MODE_PIN4_INPUT			0x00000000
#define MODE_PIN5_INPUT			0x00000000
#define MODE_PIN6_INPUT			0x00000000
#define MODE_PIN7_INPUT			0x00000000
#define MODE_PIN8_INPUT			0x00000000
#define MODE_PIN9_INPUT			0x00000000

//PINMODE OUTPUT
#define MODE_PIN0_OUTPUT			0x00000001
#define MODE_PIN1_OUTPUT			0x00000008
#define MODE_PIN2_OUTPUT			0x00000040
#define MODE_PIN3_OUTPUT			0x00000200
#define MODE_PIN4_OUTPUT			0x00001000
#define MODE_PIN5_OUTPUT			0x00008000
#define MODE_PIN6_OUTPUT			0x00040000
#define MODE_PIN7_OUTPUT			0x00200000
#define MODE_PIN8_OUTPUT			0x01000000
#define MODE_PIN9_OUTPUT			0x08000000

//PINMODE ALTERNATIVE
#define MODE_PIN8_ALT5     0x02000000

//PIN
#define PIN0			0x00000001
#define PIN1			0x00000002
#define PIN2			0x00000004
#define PIN3			0x00000008
#define PIN4			0x00000010
#define PIN5			0x00000020
#define PIN6			0x00000040
#define PIN7			0x00000080

#define PIN8			0x00000100
#define PIN9			0x00000200
#define PIN10			0x00000400
#define PIN11			0x00000800
#define PIN12			0x00001000
#define PIN13			0x00002000
#define PIN14			0x00004000
#define PIN15			0x00008000

#define PIN16			0x00010000
#define PIN17			0x00020000
#define PIN18			0x00040000
#define PIN19			0x00080000
#define PIN20			0x00100000
#define PIN21			0x00200000
#define PIN22			0x00400000
#define PIN23			0x00800000

#define PIN24			0x01000000
#define PIN25			0x02000000
#define PIN26			0x04000000
#define PIN27			0x08000000
#define PIN28			0x10000000
#define PIN29			0x20000000
#define PIN30			0x40000000
#define PIN31			0x80000000


//--- Exported functions ---//
int map_peripheral(struct bcm2835_peripheral *p);
void unmap_peripheral(struct bcm2835_peripheral *p);
int map_all_know_peripheral(void);

void GpioConfig_0_to_9 (unsigned int , unsigned int);
void GpioConfig_10_to_19 (unsigned int , unsigned int);
void GpioConfig_20_to_29 (unsigned int , unsigned int);

void GpioSet (unsigned int);
void GpioClear (unsigned int);

void SetPwm0 (unsigned int, unsigned int, unsigned int);
void Pwm0Data (unsigned int);

#endif
//--- End ---//


//--- END OF FILE ---//
