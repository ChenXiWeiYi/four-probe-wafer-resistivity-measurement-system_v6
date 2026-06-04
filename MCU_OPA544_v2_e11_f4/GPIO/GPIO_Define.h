#ifndef GPIO_Define_H
#define GPIO_Define_H


// 用于恒流源通道切换的74HC595
// @date 2025.08.29
#define DS_595		PCout(2)
#define MR_595		PAout(2)	// 低电平有效
#define OE_595		PFout(9)	// 低电平有效
#define SHCP_595	PAout(1)
#define STCP_595	PFout(7)


// 核心板LED
// @date 2025.08.29
#define	LED1	PFout(8)
#define	LED2	PFout(6)
#define LED3	PFout(4)
#define LED4	PFout(2)
#define LED5	PFout(0)


// CCS2GND
// @date 2025.08.29
#define CCS_GND		PBout(0)


// LTC6373_1
// @date 2025.08.29
#define A0_LTC6373_1	PGout(0)
#define A1_LTC6373_1	PFout(14)
#define A2_LTC6373_1	PFout(11)


// LTC6373_2
// @date 2025.08.29
#define A0_LTC6373_2	PGout(8)
#define A1_LTC6373_2	PCout(7)
#define A2_LTC6373_2	PCout(8)


// LTC6373_3
// @date 2025.10.24
#define A0_LTC6373_3	PCout(0)
#define A1_LTC6373_3	PCout(3)
#define A2_LTC6373_3	PCout(1)


#define CS_DAC		PEout(8)





/**   ADC1   **/
// 2025.10.28
// ADC1 DRDY:PB1 CS:PA3 DSYNC:PA4
#define GPIO_DRDY_ADC1	GPIOB
#define PIN_DRDY_ADC1	GPIO_PIN_1
#define CS_ADC1			PAout(3)
#define DSYNC_ADC1		PAout(4)
#define DRDY_ADC1		PBin(1)

/**   ADC2   **/
// 2025.10.28 
// ADC2 DRDY:PD4 CS:PD1 DSYNC:PD0
#define GPIO_DRDY_ADC2	GPIOD
#define PIN_DRDY_ADC2	GPIO_PIN_4
#define CS_ADC2			PDout(1)
#define DSYNC_ADC2		PDout(0)
#define DRDY_ADC2		PDin(4)

// 2026.01.30
#define SW_Probe_1 PBout(11)

#endif // GPIO_Define_H
