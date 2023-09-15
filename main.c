#include "stm32l1xx.h"
#include "stm32l1xx_ll_system.h"
#include "stm32l1xx_ll_rcc.h"
#include "stm32l1xx_ll_gpio.h"
#include "stm32l1xx_ll_rcc.h"
#include "stm32l1xx_ll_pwr.h"
#include "stm32l1xx_ll_utils.h"
#include "stm32l1xx_ll_bus.h"
#include "stm32l1xx_ll_lcd.h"
#include "stm32l1xx_ll_tim.h"
#include "stm32l152_glass_lcd.h"
#include "stdio.h"

void SystemClock_Config(void);
void TIMBase_Config(void);
void TIMBase_Config2(void);
void GPIO_Config(void);
void Display_Button(int a);

char disp2_str[] ="CLEAR "; // declare string LD : CLEAR
char disp_str[10];// declare count down
char *disp_strE[4] = { "SMOKE ", "CO2  ", "LPG  "};

int main()
{      
    SystemClock_Config();//Max-performance configure
	  LCD_GLASS_Init(); //LCD low-level init
	  TIMBase_Config();//delay 1 seccond
	  TIMBase_Config2();//delay 3 second
	  GPIO_Config();
    
    while(1) {
      if(LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_0))
      {
	 LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_3);// User button pressed turn on LEDS
         LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_0);// User button pressed turn off LEDS						    
         Display_Button(2);//Display button 
      }
			
      else if(LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_4))
      {			
	 LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_3);// User button pressed turn on LEDS
         LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_0);// User button pressed turn off LEDS								    
         Display_Button(1);//Display button 
      }
			
      else if(LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_5))
      {
				LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_3);// User button pressed turn on LEDS
        LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_0);// User button pressed turn off LEDS						   
        Display_Button(0);//Display button 
      }
			
      else
      {
	 LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_3);;// User button pressed turn off LEDS	
	 LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_0);// User button pressed turn on LEDS	
	 LCD_GLASS_DisplayString((uint8_t*)disp2_str);//display string LD : CLEAR
      }	
    }
}

void Display_Button(int a)
{
	 int seconds = 10;
	 int seconds2 = 10;
	 
   while (seconds > 0) {
               // Check if the timer has reached 3 seconds
               if (LL_TIM_IsActiveFlag_UPDATE(TIM3) != RESET) {
                   // Display "SMOKE" for 3 seconds
                   LCD_GLASS_DisplayString((uint8_t*)disp_strE[a]);  
                   // Reset the timer flag and counter
                   LL_TIM_ClearFlag_UPDATE(TIM3);
                   seconds--; // Reduce the countdown by 1 second
                }
		}
				     
             // Clear the LCD
             LCD_GLASS_Clear();
						 
		while (seconds2 > 0) {
			 if (LL_TIM_IsActiveFlag_UPDATE(TIM2) != RESET) {
			     // Print the countdown value on the LCD for 10 seconds
			     if (seconds2 < 10) {
			         sprintf(disp_str, "0%d", seconds2);
			     }
			     else {
				  sprintf(disp_str, "%d", seconds2);
			     }
			     LCD_GLASS_DisplayString((uint8_t*)disp_str);					
			     seconds2--; // Reduce the countdown by 1 second
			     LL_TIM_ClearFlag_UPDATE(TIM2);
                         }
                }
}		

void GPIO_Config(void)
{
	  // Declare struct for GPIO
    LL_GPIO_InitTypeDef GPIO_InitStruct;

    // Enable GPIOA clock
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	
	  // Enable GPIOC clock
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);

    // Config GPIOA using struct
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
    GPIO_InitStruct.Pin = LL_GPIO_PIN_4;
    GPIO_InitStruct.Pin = LL_GPIO_PIN_5;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		
		// Config GPIOC using struct 
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Pin = LL_GPIO_PIN_0 | LL_GPIO_PIN_3 ; 
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(GPIOC, &GPIO_InitStruct); 
}



void TIMBase_Config(void)
{
    LL_TIM_InitTypeDef timbase_initstructure;
   
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);

    timbase_initstructure.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    timbase_initstructure.CounterMode = LL_TIM_COUNTERDIRECTION_UP;
    timbase_initstructure.Autoreload = 1000 - 1;  
    timbase_initstructure.Prescaler = 32000 - 1;  

    LL_TIM_Init(TIM2, &timbase_initstructure);
    LL_TIM_EnableCounter(TIM2);
}

void TIMBase_Config2(void)
{
    LL_TIM_InitTypeDef timbase_initstructure;
   
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);

    timbase_initstructure.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    timbase_initstructure.CounterMode = LL_TIM_COUNTERDIRECTION_UP;
    timbase_initstructure.Autoreload = 3000 - 1;  
    timbase_initstructure.Prescaler = 1000 - 1;  

    LL_TIM_Init(TIM3, &timbase_initstructure);
    LL_TIM_EnableCounter(TIM3);
}

void SystemClock_Config(void)
{
  /* Enable ACC64 access and set FLASH latency */
  LL_FLASH_Enable64bitAccess();;
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);

  /* Set Voltage scale1 as MCU will run at 32MHz */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
 
  /* Poll VOSF bit of in PWR_CSR. Wait until it is reset to 0 */
  while (LL_PWR_IsActiveFlag_VOSF() != 0)
  {
  };
 
  /* Enable HSI if not already activated*/
  if (LL_RCC_HSI_IsReady() == 0)
  {
    /* HSI configuration and activation */
    LL_RCC_HSI_Enable();
    while(LL_RCC_HSI_IsReady() != 1)
    {
    };
  }
 

  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLL_MUL_6, LL_RCC_PLL_DIV_3);

  LL_RCC_PLL_Enable();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  };
 
  /* Sysclk activation on the main PLL */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  };
 
  /* Set APB1 & APB2 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  /* Set systick to 1ms in using frequency set to 32MHz                             */
  /* This frequency can be calculated through LL RCC macro                          */
  /* ex: __LL_RCC_CALC_PLLCLK_FREQ (HSI_VALUE, LL_RCC_PLL_MUL_6, LL_RCC_PLL_DIV_3); */
  LL_Init1msTick(32000000);
 
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(32000000);
}
