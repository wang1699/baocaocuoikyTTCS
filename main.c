/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
int LED[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
int count = 0;
int c = 0;
int time = 9;

void resett(){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_7
	                          |GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
	                          |GPIO_PIN_11|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
	                          |GPIO_PIN_6, GPIO_PIN_RESET);
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_pin){

		if(GPIO_pin == GPIO_PIN_10){
			NVIC_SystemReset();	//reset lai he thong
		}else if(GPIO_pin == GPIO_PIN_11) {
			resett();
			c =1;
		}
		else if(GPIO_pin == GPIO_PIN_12) {
			resett();
			c = 2;

		}else if(GPIO_pin == GPIO_PIN_6){
			time =7;
		}
}
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int main(void)
{
  HAL_Init();
  MX_GPIO_Init();
  while (1)
  {

	  while(c>0){
		  if(c==1){
			  	  //Đèn xanh cột 1,3 sáng, đèn đỏ cột 2,4 sáng
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 0);
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);

		  }else if(c==2){
			  	  //Đèn xanh cột 2,4 sáng, đèn đỏ cột 1,3 sáng
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 1);
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
		  }
	  }
	  int i;
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
	  for(i = time; i>0; i--){
		  if(c!=0)continue;
		  GPIOB->ODR = LED[i];
		  HAL_Delay(1000);
		  if (i == time/2-1){
			HAL_Delay(1);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 1);
		  }
	  }
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 0);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 1);
	  for(i = time; i>0 ; i--){if(c!=0)continue;
		  GPIOB->ODR = LED[i];
		  HAL_Delay(1000);
		  if (i ==time/2-1){
			HAL_Delay(1);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 1);
		  }
	  }
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 0);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 0);
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA2 PA7
                           PA8 PA9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA6 PA10 PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB10
                           PB11 PB3 PB4 PB5
                           PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
