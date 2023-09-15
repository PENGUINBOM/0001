# 0001
Use microcontroller STM32L152 for learn about configure port, LCD, delay, I/O

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
