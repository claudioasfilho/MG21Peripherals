/***********************************************************************************************//**
 * \file   peripherals.c
 * \brief  All the Hardware Peripheral Functions
 * \author Claudio Filho
 ***************************************************************************************************
 * <b> (C) Copyright 2017 Silicon Labs, http://www.silabs.com</b>
 ***************************************************************************************************
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 **************************************************************************************************/

/*Application Specific Code*/

#include "em_chip.h"
#include "em_timer.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "native_gecko.h"
#include "peripherals.h"
#include "em_usart.h"
#include "em_iadc.h"
#include "em_ldma.h"
#include "app.h"
#include "sleep.h"
#include <string.h>
#include <stdio.h>
#include "usage_iadc_ldma.h"
#include "em_prs.h"

/* Device initialization header */
#include "hal-config.h"

#if defined(HAL_CONFIG)
#include "bsphalconfig.h"
#else
#include "bspconfig.h"
#endif


OBJFLAGS PWMObj;
OBJFLAGS UARTObj;
OBJFLAGS ADCObj;
GPIOS UserGPIOs;




/**************************************************************************//**
 * @brief GPIO Related Functions  and variables
 *
 *****************************************************************************/
//uint8_t test[256];

void InitGPIO(void) {

	// $[Port A Configuration]

	/*UART Function Related GPIOs*/

	CMU_ClockEnable(cmuClock_GPIO, true);

	/*PWM Function Related GPIOs*/

	//PWM Output - PIN P1 and EXP_HEADER4 on WSTK with BRD4182 Radio Board
	GPIO_PinModeSet(PWM_PORT, PWM_PIN, gpioModePushPull, 0);

	/*General Purpose Function Related GPIOs*/

	//UIF LED0 - PIN P8, UIF_LED0, EXP_HEADER11 on WSTK with BRD4182 Radio Board
	/* Pin PF4 is configured to Push-pull */
	GPIO_PinModeSet(BSP_LED0_PORT, BSP_LED0_PIN, gpioModePushPull, 0);
	UserGPIOs.bits.LED0 = 0;	//Logic Definition

#if BSP_LED_PRESENT >1
	//UIF LED1 - PIN P10, UIF_LED1, EXP_HEADER13 on WSTK with BRD4182 Radio Board
	/* Pin PF5 is configured to Push-pull */
	GPIO_PinModeSet(BSP_LED1_PORT, BSP_LED1_PIN, gpioModePushPull, 0);
	UserGPIOs.bits.LED1 = 0;	//Logic Definition
#endif

	//UIF PB0 - PIN P4, EXP_HEADER7, UIF_BUTTON0 on WSTK with BRD4182 Radio Board
	/* Pin PF6 is configured to Input enabled with filter */

	GPIO_PinModeSet(BSP_BUTTON0_PORT, BSP_BUTTON0_PIN, gpioModeInput, 0);
	UserGPIOs.bits.PB0 = 0;	//Logic Definition

#if BSP_BUTTON_PRESENT >1
	//UIF PB1 - PIN P6, EXP_HEADER9, UIF_BUTTON1 on WSTK with BRD4182 Radio Board
	/* Pin PF7 is configured to Input enabled with filter */
	GPIO_PinModeSet(BSP_BUTTON1_PORT, BSP_BUTTON1_PIN, gpioModeInput, 0);
	UserGPIOs.bits.PB1 = 0;	//Logic Definition
#endif
	// [Port F Configuration]$

	/*Other GPIOs*/


	/* Test GPIO */
//	GPIO_PinModeSet(gpioPortD, 10, gpioModePushPull, 1);

}

void SetLED0(void)
{
	UserGPIOs.bits.LED0=1;
}
void ClearLED0(void)
{
	UserGPIOs.bits.LED0=0;
}
void ToogleLED0(void)
{
	UserGPIOs.bits.LED0^=1;
}
uint8_t GetLED0()
{
	return UserGPIOs.bits.LED0;
}


void SetLED1(void)
{
	UserGPIOs.bits.LED1=1;
}
void ClearLED1(void)
{
	UserGPIOs.bits.LED1=0;
}
void ToogleLED1(void)
{
	UserGPIOs.bits.LED1^=1;
}

uint8_t GetLED1()
{
	return UserGPIOs.bits.LED1;
}

uint8_t GetPB0()
{
	return UserGPIOs.bits.PB0;
}

uint8_t GetPB1()
{
	return UserGPIOs.bits.PB1;
}

void GPIOHandler(void)
{
	if (UserGPIOs.bits.LED0 != GPIO_PinOutGet(BSP_LED0_PORT, BSP_LED0_PIN))
		{
			if (UserGPIOs.bits.LED0==1)  GPIO_PinOutSet(BSP_LED0_PORT, BSP_LED0_PIN);
			else  GPIO_PinOutClear(BSP_LED0_PORT, BSP_LED0_PIN);
		}
#if BSP_LED_PRESENT >1
	if (UserGPIOs.bits.LED1 != GPIO_PinOutGet(BSP_LED1_PORT, BSP_LED1_PIN))
		{
			if (UserGPIOs.bits.LED1==1)  GPIO_PinOutSet(BSP_LED1_PORT, BSP_LED1_PIN);
			else  GPIO_PinOutClear(BSP_LED1_PORT, BSP_LED1_PIN);
		}
#endif
	if(GPIO_PinInGet(BSP_BUTTON0_PORT, BSP_BUTTON0_PIN)==0) UserGPIOs.bits.PB0=1;
	else UserGPIOs.bits.PB0=0;
#if BSP_BUTTON_PRESENT >1
	if(GPIO_PinInGet(BSP_BUTTON1_PORT, BSP_BUTTON1_PIN)==0) UserGPIOs.bits.PB1=1;
	else UserGPIOs.bits.PB1=0;
#endif

}

/**************************************************************************//**
 * @brief PWM Related Functions  and variables
 *
 *****************************************************************************/
static uint8_t desiredDutyCycle;

#if 0
void InitPRS()
{
	CMU_ClockEnable(cmuClock_PRS, true);
	/* Use ADC SINGLE as an ASYNC PRS producer on CH0 */
	PRS_SourceAsyncSignalSet(0, PRS_CH_CTRL_SOURCESEL_ADC0, PRS_CH_CTRL_SIGSEL_ADC0SINGLE);


	PRS_SourceSignalSet(0,
	                         uint32_t source,
	                         uint32_t signal,
	                         PRS_Edge_TypeDef edge);
}
#endif

#if 0
void InitPWM2()
{

  // Enable clock to GPIO and TIMER0

  CMU_ClockEnable(cmuClock_TIMER0, true);


// $[TIMER0 I/O setup]
/* Set up CC0 */
  // Route TIMER0 CC0 output to PA6
  GPIO->TIMERROUTE[0].ROUTEEN  = GPIO_TIMER_ROUTEEN_CC0PEN;
  GPIO->TIMERROUTE[0].CC0ROUTE = (PWM2_PORT << _GPIO_TIMER_CC0ROUTE_PORT_SHIFT)
					| (PWM2_PIN << _GPIO_TIMER_CC0ROUTE_PIN_SHIFT);

	TIMER_Init_TypeDef init = TIMER_INIT_DEFAULT;

	init.enable = 0;
	init.debugRun = 1;
	init.dmaClrAct = 0;
	init.sync = 0;
	init.clkSel = timerClkSelHFPerClk;
	init.prescale = timerPrescale1;
	init.fallAction = timerInputActionNone;
	init.riseAction = timerInputActionNone;
	init.mode = timerModeUp;
	init.quadModeX4 = 0;
	init.oneShot = 0;
	init.count2x = 0;
	init.ati = 0;
	TIMER_Init(TIMER0, &init);
	// [TIMER0 initialization]$

	// $[TIMER0 CC0 init]
	TIMER_InitCC_TypeDef initCC0 = TIMER_INITCC_DEFAULT;

	initCC0.prsInput = false;
	initCC0.prsSel = timerPRSSELCh0;
	initCC0.edge = timerEdgeRising;
	initCC0.mode = timerCCModePWM;
	initCC0.eventCtrl = timerEventEveryEdge;
	initCC0.filter = 0;
	initCC0.cofoa = timerOutputActionNone;
	initCC0.cufoa = timerOutputActionNone;
	initCC0.cmoa = timerOutputActionNone;
	initCC0.coist = 0;
	initCC0.outInvert = 0;
	TIMER_InitCC(TIMER0, 0, &initCC0);
	// [TIMER0 CC0 init]$0

	CMU_ClockEnable(cmuClock_PRS, true);

	PRS_SourceSignalSet(1, PRS_SYNC_CH_CTRL_SOURCESEL_TIMER0 , _PRS_SYNC_CH_CTRL_SIGSEL_TIMER0OF, prsEdgePos);

	PWMObj.all=0;
	PWMObj.bits.Enabled=1;

}

void InitPWM1()
{

  // Enable clock to GPIO and TIMER0

  CMU_ClockEnable(cmuClock_TIMER1, true);


// $[TIMER1 I/O setup]
/* Set up CC0 */
  // Route TIMER1 CC0 output to PA6
  GPIO->TIMERROUTE[1].ROUTEEN  = GPIO_TIMER_ROUTEEN_CC0PEN;
  GPIO->TIMERROUTE[1].CC0ROUTE = (PWM_PORT << _GPIO_TIMER_CC0ROUTE_PORT_SHIFT)
					| (PWM_PIN << _GPIO_TIMER_CC0ROUTE_PIN_SHIFT);

	TIMER_Init_TypeDef init = TIMER_INIT_DEFAULT;

	init.enable = 0;
	init.debugRun = 1;
	init.dmaClrAct = 0;
	init.sync = 0;
	init.clkSel = timerClkSelHFPerClk;//timerClkSelHFPerClk;//timerClkSelCascade;
	init.prescale = timerPrescale1;
	init.fallAction = timerInputActionNone;
	init.riseAction =  timerInputActionNone;
	init.mode = timerModeUp;
	init.quadModeX4 = 0;
	init.oneShot = 0;
	init.count2x = 0;
	init.ati = 0;
	TIMER_Init(TIMER1, &init);
	// [TIMER1 initialization]$

	// $[TIMER1 CC0 init]
	TIMER_InitCC_TypeDef initCC0 = TIMER_INITCC_DEFAULT;

	initCC0.prsInput = true;
	initCC0.prsSel = timerPRSSELCh1;
	initCC0.edge = timerEdgeRising;
	initCC0.mode = timerCCModePWM;
	initCC0.eventCtrl = timerEventEveryEdge;
	initCC0.filter = 0;
	initCC0.cofoa = timerOutputActionNone;
	initCC0.cufoa = timerOutputActionNone;
	initCC0.cmoa = timerOutputActionNone;
	initCC0.coist = 0;
	initCC0.outInvert = 0;
	TIMER_InitCC(TIMER1, 0, &initCC0);
	// [TIMER1 CC0 init]$0

	PWMObj.all=0;
	PWMObj.bits.Enabled=1;

}



#else
	/***************************************************************************//**
	 * @brief   PWM_GEN
	 * 		initialize PWM2 using TIMER0 CC0
	 *
	 * 		route out to PA6
	 ******************************************************************************/

/***************************************************************************//**
 * @brief	Global Variables
 ******************************************************************************/
static uint8_t desiredDutyCycle = 50;

/***************************************************************************//**
 * @brief	Initialize PWM_GEN on TIMER0
 *
 * 		TIMER0 in PWM mode on CC0
 * 		TIMER0 will be a prs producer on ch0
 ******************************************************************************/
void InitPWM2(void) {

	/* enable timer0 clock */
	CMU_ClockEnable(cmuClock_TIMER0, true);

	/* route timer0 to gpio */
	GPIO->TIMERROUTE[0].ROUTEEN = GPIO_TIMER_ROUTEEN_CC0PEN;
	GPIO->TIMERROUTE[0].CC0ROUTE = (PWM2_PORT << _GPIO_TIMER_CC0ROUTE_PORT_SHIFT) |
										(PWM2_PIN << _GPIO_TIMER_CC0ROUTE_PIN_SHIFT);

	/***********************************************************************//**
	 * initialize timer
	 * 		don't enable immediately
	 * 		continue running if debug
	 **************************************************************************/
	TIMER_Init_TypeDef initTimer = TIMER_INIT_DEFAULT;
	initTimer.enable = false;
	initTimer.debugRun = true;
	TIMER_Init(TIMER0, &initTimer);


	/***********************************************************************//**
	 * initialize timer compare/capture mode
	 * 		initialize in pwm mode on CC0
	 **************************************************************************/
	TIMER_InitCC_TypeDef initCC = TIMER_INITCC_DEFAULT;
	initCC.mode = timerCCModePWM;
	initCC.prsOutput = timerPrsOutputPulse;
	TIMER_InitCC(TIMER0, 0, &initCC);


	/* set the top value */
	TIMER_TopSet(TIMER0, CMU_ClockFreqGet(cmuClock_TIMER0)/PWM_FREQ);


	/* set the compare value */
	TIMER_CompareSet(TIMER0, 0, (TIMER_TopGet(TIMER0) * 10) / 100);

}


/***************************************************************************//**
 * @brief	Initialize PWM on TIMER1
 *
 * 		TIMER1 in PWM mode on CC0
 * 		TIMER1 will be a prs consumer on ch0
 ******************************************************************************/
void InitPWM1(void) {

	/* enable timer1 clock */
	CMU_ClockEnable(cmuClock_TIMER1, true);

	/* route timer1 to gpio */
	GPIO->TIMERROUTE[1].ROUTEEN = GPIO_TIMER_ROUTEEN_CC0PEN;
	GPIO->TIMERROUTE[1].CC0ROUTE = (PWM_PORT << _GPIO_TIMER_CC0ROUTE_PORT_SHIFT) |
										(PWM_PIN << _GPIO_TIMER_CC0ROUTE_PIN_SHIFT);

	/***********************************************************************//**
	 * initialize timer
	 * 		don't enable immediately
	 * 		continue running if debug
	 * 		reload on falling edge input
	 * 		only once
	 **************************************************************************/
	TIMER_Init_TypeDef initTimer = TIMER_INIT_DEFAULT;
	initTimer.enable = false;
	initTimer.debugRun = true;
	initTimer.fallAction = timerInputActionReloadStart;
	initTimer.oneShot = false;
	TIMER_Init(TIMER1, &initTimer);


	/***********************************************************************//**
	 * initialize timer compare/capture mode
	 * 		initialize in pwm mode on CC0
	 * 		prsInput from ch0
	 **************************************************************************/
	TIMER_InitCC_TypeDef initCC = TIMER_INITCC_DEFAULT;
	initCC.mode = timerCCModePWM;
	initCC.prsInput = true;
	initCC.prsSel = 0;
	initCC.prsInputType = timerPrsInputAsyncPulse;
	//initCC.edge = timerEdgeFalling;
	TIMER_InitCC(TIMER1, 0, &initCC);


	/* set the top value */
	TIMER_TopSet(TIMER1, CMU_ClockFreqGet(cmuClock_TIMER1)/(2*PWM_FREQ));

	/* set the compare value */
	TIMER_CompareSet(TIMER1, 0, (TIMER_TopGet(TIMER1) * desiredDutyCycle * 2) / 100);

}


void InitPRS(void) {
	CMU_ClockEnable(cmuClock_PRS, true);

	/* set the producer */
	PRS_SourceAsyncSignalSet(0, PRS_ASYNC_CH_CTRL_SOURCESEL_TIMER0, PRS_ASYNC_CH_CTRL_SIGSEL_TIMER0CC0);

	/* set the logic */
	//PRS_Combine(0, 0, prsLogic_A_OR_B);

	/* set the consumer */
	// route output to some where.
	//PRS_PinOutput(0, prsTypeAsync, gpioPortA, 7);
	PRS_ConnectConsumer(0, prsTypeAsync, prsConsumerTIMER1_CC0);

}

#endif


/***************************************************************************//**
 * @brief	Initialize PWMs on board
 *
 * 		initialize PWM1 and PWM2
 ******************************************************************************/
void InitPWMs(void) {
	/* ensure clocks for gpio are enabled */
	CMU_ClockEnable(cmuClock_GPIO, true);
	GPIO_PinModeSet(PWM2_PORT, PWM2_PIN, gpioModePushPull, 0);
	GPIO_PinModeSet(PWM_PORT, PWM_PIN, gpioModePushPull, 0);
	GPIO_PinModeSet(gpioPortA, 7, gpioModePushPull, 0);

	/* enable clock for prs */
	InitPRS();

	InitPWM2();		// pwm gen
	InitPWM1();

	TIMER_Enable(TIMER0, true);
	TIMER_Enable(TIMER1, true);
}



void UpdatePWM1(uint8_t DutyCycle) //desiredDutyCycle varies from 0-100;
{
	desiredDutyCycle = DutyCycle;

	if (DutyCycle == 0) //If Duty Cycle is 0 then device can go to EM2 otherwise it disables EM2
	{
		SLEEP_SleepBlockEnd(sleepEM2);
	}
	else
	{
		SLEEP_SleepBlockBegin(sleepEM2);
	}

	PWMObj.bits.Status=1;
}

void ChangePWM2output() //desiredDutyCycle varies from 0-100;
{
	uint32_t PWMFrequency;
	uint32_t CC1DutyCycle;


	PWMFrequency = BSP_CLK_HFXO_FREQ / PWM_FREQ;

	if (desiredDutyCycle>0)
	{

		CC1DutyCycle = (desiredDutyCycle*PWMFrequency)/100;
		CC1DutyCycle =CC1DutyCycle ;

	}
	else  {CC1DutyCycle=0;}
	if (desiredDutyCycle>100) CC1DutyCycle=99;


	TIMER_Enable(TIMER0,0);	//Disables Timer

	/* set PWM period */
	TIMER_TopSet (TIMER0, PWMFrequency);

	/* Set PWM duty cycle to 50% */
	TIMER_CompareSet (TIMER0, 0, CC1DutyCycle);

	CC1DutyCycle = CC1DutyCycle;

	TIMER_Enable(TIMER0,1);

}
void ChangePWMoutput() //desiredDutyCycle varies from 0-100;
{
	uint32_t PWMFrequency;
	uint32_t CC1DutyCycle;


	PWMFrequency = BSP_CLK_HFXO_FREQ / PWM_FREQ;

	if (desiredDutyCycle>0)
	{

		CC1DutyCycle = (desiredDutyCycle*PWMFrequency)/100;
		CC1DutyCycle =CC1DutyCycle ;

	}
	else  {CC1DutyCycle=0;}
	if (desiredDutyCycle>100) CC1DutyCycle=99;


	TIMER_Enable(TIMER1,0);	//Disables Timer

	/* set PWM period */
	TIMER_TopSet (TIMER1, PWMFrequency);

	/* Set PWM duty cycle to 50% */
	TIMER_CompareSet (TIMER1, 0, CC1DutyCycle);

	CC1DutyCycle = CC1DutyCycle;

	TIMER_Enable(TIMER1,1);

}

void PWMHandler(void)
{
	if( (PWMObj.bits.Enabled==1) && (PWMObj.bits.Status==1))
	{
		ChangePWMoutput();
		PWMObj.bits.Status=0;
	}

}

uint8_t GetPWM1()
{
	return desiredDutyCycle;
}


/****************************************************************************
 * @brief ADC0 Related Functions and variables
 *
 *****************************************************************************/
static IADC_Result_t ADCresult;

/**************************************************************************//**
 * @brief  IADC Initializer
 *****************************************************************************/
void initIADC (void)
{
  // Declare init structs
  IADC_Init_t init = IADC_INIT_DEFAULT;
  IADC_AllConfigs_t initAllConfigs = IADC_ALLCONFIGS_DEFAULT;
  IADC_InitSingle_t initSingle = IADC_INITSINGLE_DEFAULT;
  IADC_SingleInput_t initSingleInput = IADC_SINGLEINPUT_DEFAULT;

  // Enable IADC clock
  CMU_ClockEnable(cmuClock_IADC0, true);

  // Reset IADC to reset configuration in case it has been modified
  IADC_reset(IADC0);

  // Configure IADC clock source for use while in EM2
  //CMU_ClockSelectSet(cmuClock_IADCCLK, cmuSelect_FSRCO);
  CMU_ClockSelectSet(cmuClock_IADCCLK, cmuSelect_HFXO);

  // Modify init structs and initialize
  init.warmup = iadcWarmupKeepWarm;

  // Set the HFSCLK prescale value here
  init.srcClkPrescale = IADC_calcSrcClkPrescale(IADC0, CLK_SRC_ADC_FREQ, 0);

  // Configuration 0 is used by both scan and single conversions by default
  // Use unbuffered AVDD as reference
  initAllConfigs.configs[0].reference = iadcCfgReferenceVddx;

  // Divides CLK_SRC_ADC to set the CLK_ADC frequency for desired sample rate
  initAllConfigs.configs[0].adcClkPrescale = IADC_calcAdcClkPrescale(IADC0,
                                                                    CLK_ADC_FREQ,
                                                                    0,
                                                                    iadcCfgModeNormal,
                                                                    init.srcClkPrescale);

  // Single initialization
  initSingle.dataValidLevel = _IADC_SINGLEFIFOCFG_DVL_VALID1;

  // Set conversions to run once
  initSingle.triggerAction = iadcTriggerActionOnce;

  // Configure Input sources for single ended conversion GPIO port C pin 2

  initSingleInput.posInput = iadcPosInputPortCPin2;
  initSingleInput.negInput = iadcNegInputGnd;

  // Initialize IADC
  IADC_init(IADC0, &init, &initAllConfigs);

  // Initialize Scan
  IADC_initSingle(IADC0, &initSingle, &initSingleInput);

  // Allocate the analog bus for ADC0 inputs
  GPIO->IADC_INPUT_BUS |= IADC_INPUT_BUSALLOC;

#if ADCINTENABLED //Not tested
  // Enable interrupts on data valid level
  IADC_enableInt(IADC0, IADC_IF_SINGLEFIFODVL);

  // Enable ADC interrupts
  NVIC_ClearPendingIRQ(IADC_IRQn);
  NVIC_EnableIRQ(IADC_IRQn);

#endif

  ADCObj.bits.ADCSample=0;
}


/**************************************************************************//**
 * @brief  ADC Handler
 *****************************************************************************/
void IADC_IRQHandler(void)
{
	gecko_external_signal(IADC_IRQFlag);
}

void softIADC_IRQHandler(void)
{

  // Read data from the FIFO
	ADCresult = IADC_pullSingleFifoResult(IADC0);

  // For single-ended the result range is 0 to +Vref, i.e., 12 bits for the
  // conversion value.
  //singleResult = sample.data * 3.3 / 0xFFF;

  ADCObj.bits.ADCSample=1;

  IADC_clearInt(IADC0, IADC_IF_SINGLEFIFODVL);

}



void ADCSampleReady()
{
	ADCObj.bits.ADCSample=1;
}

void StartADC0Sample()
{
	IADC_command(IADC0, iadcCmdStartSingle);
}

uint16_t GetADC0()
{
	ADCObj.bits.ADCSample=0;

	return ADCresult.data;
}

void IADCHandler(void)
{

	 StartADC0Sample();

					  if((IADC0->STATUS & (_IADC_STATUS_CONVERTING_MASK | _IADC_STATUS_SINGLEFIFODV_MASK)) == IADC_STATUS_SINGLEFIFODV)
					  {
						  ADCresult = IADC_pullSingleFifoResult(IADC0);
						  ADCSampleReady();
					  }
}


void InitPeripherals()
{



	  InitGPIO();
	 // InitPWM1();
	//  InitPWM2();

	  InitPWMs();

	  UpdatePWM1(50);
	  ChangePWMoutput();

	  UpdatePWM1(10);
	  ChangePWM2output();

	 //   initSingleIADC();

	   // initLdmaPingPong();

	    // Start scan

	   // IADC_command(IADC0, iadcCmdStartSingle);

	  //  printf("Init Peripherals\r\n");
}





/** @} (end addtogroup app) */
/** @} (end addtogroup Application) */
