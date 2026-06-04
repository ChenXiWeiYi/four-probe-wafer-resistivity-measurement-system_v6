#include <stdbool.h>
#include "sys.h"
#include "GPIO_Define.h"


/** EXTI_Init.c */
void	EXTI_Init(void);


/** EXTI1_Interrupt.c */
void	EXTI1_Interrupt(void);
bool	is_Flag_ADC1_DRDY(void);
void	CLR_Flag_ADC1_DRDY(void);

/** EXTI2_Interrupt.c */
void	EXTI2_Interrupt(void);

/** EXTI4_Interrupt.c */
void	EXTI4_Interrupt(void);
bool	is_Flag_ADC2_DRDY(void);
void	CLR_Flag_ADC2_DRDY(void);

/** EXTI6_Interrupt.c */
void	EXTI6_Interrupt(void);

/** EXTI13_Interrupt.c */
void	EXTI13_Interrupt(void);

/**  EXTI14_Interrupt.c  **/
void	EXTI14_Interrupt(void);
