# 0001

char disp2_str[] ="CLEAR "; // declare string LD : CLEAR
char disp_str[10];// declare count down
char *disp_strE[4] = { "SMOKE ", "CO2  ", "LPG  "};

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
