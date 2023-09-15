# 0001

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
    GPIO_InitStruct.Pin = LL_GPIO_PIN_0 | LL_GPIO_PIN_3 | LL_GPIO_PIN_10; 
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(GPIOC, &GPIO_InitStruct); 
}
