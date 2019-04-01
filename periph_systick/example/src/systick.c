/*
 * @brief Blinky example using sysTick
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"
#include <stdio.h>

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
#define TICKRATE_10HZ (10)				/* 10 ticks per second */
#define TICKRATE_100HZ (100)			/* 100 ticks per second */
#define TICKRATE_1000HZ (1000)			/* 1000 ticks per second */
#define TICKRATE_HZ1 (TICKRATE_1000HZ)

#define LED_TOGGLE_250MS (250)
#define LED_TOGGLE_500MS (500)
#define LED_TOGGLE_MS1 (LED_TOGGLE_500MS)


#define TP1_1 (1)	/* Test periph_systick */
#define TP1_2 (2)	/* Test LED */
#define TP1_3 (3)	/* Test RGB */
#define TP1_4 (4)	/* Test Push Buttons */
#define TP1_5 (5)	/* Test Joystick Switch */
#define TP1_6 (6)	/* Test State Machine */
#define TP1_7 (7)	/* Test State Machine */

#define TEST (TP1_3)

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
volatile bool msLED_Flag = false;
volatile uint32_t msLED_Toggle = 0;

volatile bool BUTTON1_Flag = false;
volatile bool msBUTTON1_Flag = false;
volatile bool msBUTTON1_Debounce = 0;

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/
#if (TEST == TP1_1)
/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */
void SysTick_Handler(void)
{
	Board_LED_Toggle(0);
}

/**
 * @brief	main routine for systick example
 * @return	Function should not exit.
 */
int main(void)
{
	/* Generic Initialization */
	SystemCoreClockUpdate();
	Board_Init();

	/* Enable and setup SysTick Timer at a periodic rate */
	SysTick_Config(SystemCoreClock / TICKRATE_HZ1);

	/* LEDs toggle in interrupt handlers */
	while (1) {
		__WFI();
	}

	return 0;
}
#endif


#if (TEST == TP1_2)
/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */
void SysTick_Handler(void)
{
	if (msLED_Toggle != 0)
		msLED_Toggle--;
	else {
		msLED_Toggle = LED_TOGGLE_MS1;
		msLED_Flag = true;
	}
}

/**
 * @brief	main routine for systick example
 * @return	Function should not exit.
 */
int main(void)
{
	/* Generic Initialization */
	SystemCoreClockUpdate();
	Board_Init();
	Board_LED_Set(LED, LED_ON);

	/* Enable and setup SysTick Timer at a periodic rate */
	SysTick_Config(SystemCoreClock / TICKRATE_HZ1);

	/* LEDs toggle in main */
	while (1) {
		__WFI();

		if (msLED_Flag == true) {
			msLED_Flag = false;
			Board_LED_Toggle(LED);
		}
	}

	return 0;
}
#endif


#if (TEST == TP1_3)
/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */
void SysTick_Handler(void)
{
	if (msLED_Toggle != 0)
		msLED_Toggle--;
	else {
		msLED_Toggle = LED_TOGGLE_250MS;
		msLED_Flag = true;
	}
}

/**
 * @brief	main routine for systick example
 * @return	Function should not exit.
 */
int main(void)
{
	/* Generic Initialization */
	SystemCoreClockUpdate();
	Board_Init();
	Board_LED_Set(LED, LED_ON);
	Board_LED_Set(RED, LED_ON);
	Board_LED_Set(GREEN, LED_OFF);

	/* Enable and setup SysTick Timer at a periodic rate */
	SysTick_Config(SystemCoreClock / TICKRATE_HZ1);

	/* LEDs toggle in main */
	while (1) {
		__WFI();

		if (msLED_Flag == true) {
			msLED_Flag = false;
			Board_LED_Toggle(LED);
			Board_LED_Toggle(RED);
			Board_LED_Toggle(GREEN);
		}
	}

	return 0;
}
#endif


#if (TEST == TP1_4)
/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */
void SysTick_Handler(void)
{
	if (msLED_Toggle != 0)
		msLED_Toggle--;
	else {
		msLED_Toggle = LED_TOGGLE_250MS;
		msLED_Flag = true;
	}

	if (Buttons_GetStatus() == SW3)
		BUTTON1_Flag = true;
	else
		BUTTON1_Flag = false;
}

/**
 * @brief	main routine for systick example
 * @return	Function should not exit.
 */
int main(void)
{
	/* Generic Initialization */
	SystemCoreClockUpdate();
	Board_Init();
	Board_LED_Set(LED, LED_ON);
	Board_LED_Set(RED, LED_ON);
	Board_LED_Set(GREEN, LED_OFF);

	/* Enable and setup SysTick Timer at a periodic rate */
	SysTick_Config(SystemCoreClock / TICKRATE_HZ1);

	/* LEDs toggle in main */
	while (1) {
		__WFI();

		if (msLED_Flag == true) {
			msLED_Flag = false;
			Board_LED_Toggle(LED);
		}

		if (BUTTON1_Flag == true) {
			BUTTON1_Flag = false;
			Board_LED_Toggle(GREEN);
			Board_LED_Toggle(RED);
		}
	}

	return 0;
}
#endif

#if (TEST == TP1_6)
/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */
void SysTick_Handler(void)
{
	if (msLED_Toggle != 0)
		msLED_Toggle--;
	else {
		msLED_Toggle = LED_TOGGLE_250MS;
		msLED_Flag = true;
	}

	msBUTTON1_Flag = true;

	if (Buttons_GetStatus() == SW3)
		BUTTON1_Flag = true;
	else
		BUTTON1_Flag = false;

}

/**
 * @brief	main routine for systick example
 * @return	Function should not exit.
 */
int main(void)
{
	uint32_t BUTTON1_State = 0;

	/* Generic Initialization */
	SystemCoreClockUpdate();
	Board_Init();
	Board_LED_Set(LED, LED_ON);
	Board_LED_Set(RED, LED_ON);
	Board_LED_Set(GREEN, LED_OFF);

	/* Enable and setup SysTick Timer at a periodic rate */
	SysTick_Config(SystemCoreClock / TICKRATE_HZ1);

	/* LEDs toggle in main */
	while (1) {
		__WFI();

		if (msLED_Flag == true) {
			msLED_Flag = false;

			Board_LED_Toggle(LED);
		}

		/* BUTTON1 State Machine */
		if (msBUTTON1_Flag == true) {
			msBUTTON1_Flag = false;

			switch (BUTTON1_State) {
				case 0:
					if (BUTTON1_Flag == true) {
						msBUTTON1_Debounce = 20;
						BUTTON1_State = 1;
					}
					break;

				case 1:
					if (msBUTTON1_Debounce != 0)
						msBUTTON1_Debounce--;
					else {
						if (BUTTON1_Flag == false) {
							BUTTON1_State = 0;
						}
						else {
							BUTTON1_Flag = false;
							BUTTON1_State = 2;
							Board_LED_Toggle(GREEN);
							Board_LED_Toggle(RED);
						}
					}
					break;

				case 2:
					if (BUTTON1_Flag == false) {
						BUTTON1_State = 0;
					}
					break;
			}
		}
	}

	return 0;
}
#endif

#if (TEST == TP1_7)
/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */
void SysTick_Handler(void)
{
	if (msLED_Toggle != 0)
		msLED_Toggle--;
	else {
		msLED_Toggle = LED_TOGGLE_250MS;
		msLED_Flag = true;
	}

	msBUTTON1_Flag = true;

	if (Buttons_GetStatus() == SW3)
		BUTTON1_Flag = true;
	else
		BUTTON1_Flag = false;

}

/**
 * @brief	main routine for systick example
 * @return	Function should not exit.
 */
int main(void)
{
	uint32_t BUTTON1_State = 0;
	uint32_t LED_State = 0;
	bool LED_Toggle_Flag = false;

	/* Generic Initialization */
	SystemCoreClockUpdate();
	Board_Init();
	Board_LED_Set(LED, LED_ON);
	Board_LED_Set(RED, LED_ON);
	Board_LED_Set(GREEN, LED_OFF);

	/* Enable and setup SysTick Timer at a periodic rate */
	SysTick_Config(SystemCoreClock / TICKRATE_HZ1);

	/* LEDs toggle in main */
	while (1) {
		__WFI();

		/* LED State Machine */
		if (msLED_Flag == true) {
			msLED_Flag = false;

			switch (LED_State) {
				case 0:
					if (LED_Toggle_Flag == true) {
						LED_Toggle_Flag = false;
						LED_State = 1;
					}
					break;

				case 1:
					Board_LED_Toggle(LED);
					if (LED_Toggle_Flag == true) {
						LED_Toggle_Flag = false;
						LED_State = 0;
					}
					break;
			}
		}

		/* BUTTON1 State Machine */
		if (msBUTTON1_Flag == true) {
			msBUTTON1_Flag = false;

			switch (BUTTON1_State) {
				case 0:
					if (BUTTON1_Flag == true) {
						msBUTTON1_Debounce = 20;
						BUTTON1_State = 1;
					}
					break;

				case 1:
					if (msBUTTON1_Debounce != 0)
						msBUTTON1_Debounce--;
					else {
						if (BUTTON1_Flag == false) {
							BUTTON1_State = 0;
						}
						else {
							BUTTON1_Flag = false;
							BUTTON1_State = 2;
							Board_LED_Toggle(GREEN);
							Board_LED_Toggle(RED);
							LED_Toggle_Flag = true;
						}
					}
					break;

				case 2:
					if (BUTTON1_Flag == false) {
						BUTTON1_State = 0;
					}
					break;
			}
		}
	}

	return 0;
}
#endif
