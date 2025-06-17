/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "NRF24L01.h"
#include "key.h"
#include "led.h"
#include "OLED.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern struct keys key[];

// ������������
uint32_t key1_press_count = 0; // PA0���¼���
uint32_t key2_press_count = 0; // PA1���¼���
uint32_t key3_press_count = 0; // PB10���¼���
char buffer[16];  // ���ڴ洢ת������ַ���

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
//uint8_t Send_Out[33]="������������NRF24L01���Ͷ� ";   //Ҫ���͵�����(�������32���ֽ�)

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_I2C1_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  OLED_Init();
  OLED_Clear();
	OLED_ShowString(4, 15, "OK");  
	
	HAL_TIM_Base_Start_IT(&htim3);
	
  
while(NRF24L01_Check())
    {
        printf("��ⲻ��NRF24L01����ģ�飬����Ӳ������\r\n"); 
        HAL_Delay(1000);
    }
    
    printf("NRF24L01����ģ��Ӳ����������\r\n");
    NRF24L01_TX_Mode();//����Ϊ����ģʽ
    printf("�������ݷ���ģʽ��ÿ1s����һ������\r\n");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
      // ��ⰴ��1�Ƿ񱻰���
//    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_RESET) // ����1�͵�ƽ��Ч
//    {
//        uint8_t Send_Out[2] = "1";  // ׼����������"1"	
//			
//        if (NRF24L01_TxPacket(Send_Out) == TX_OK)
//        {
//            printf("NRF24L01����ģ�����ݷ��ͳɹ���%s\r\n", Send_Out);
//            printf("OK\r\n");
//            OLED_ShowString(8, 2, (char*)Send_Out);  // ��OLED����ʾ���յ�������

//        }
//        else
//        {
//            printf("NRF24L01����ģ�����ݷ���ʧ��\r\n");
//        }

//        HAL_Delay(20);  // ������ʱ
//    }
//    
//     // ��ⰴ��2�Ƿ񱻰���
//    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==GPIO_PIN_RESET) // ����2�͵�ƽ��Ч
//    {
//        uint8_t Send_Out[2] = "2";  // ׼����������"2"

//			 HAL_Delay(20);  // ������ʱ
//			
//        if (NRF24L01_TxPacket(Send_Out) == TX_OK)
//        {
//            printf("NRF24L01����ģ�����ݷ��ͳɹ���%s\r\n", Send_Out);
//            printf("OK\r\n");
//            OLED_ShowString(8, 2, (char*)Send_Out);  // ��OLED����ʾ���յ�������

//        }
//        else
//        {
//            printf("NRF24L01����ģ�����ݷ���ʧ��\r\n");
//        }

//       
//    }

//    // ��ⰴ��3�Ƿ񱻰���
//    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==GPIO_PIN_RESET) // ����3�͵�ƽ��Ч
//    {
//			
//        uint8_t Send_Out[2] = "3";  // ׼����������"3"      
//	       
//        if (NRF24L01_TxPacket(Send_Out) == TX_OK)
//        {
//            printf("NRF24L01����ģ�����ݷ��ͳɹ���%s\r\n", Send_Out);
//            printf("OK\r\n");
//            OLED_ShowString(8, 2, (char*)Send_Out);  // ��OLED����ʾ���յ�������
//            
//        }
//        else
//        {
//            printf("NRF24L01����ģ�����ݷ���ʧ��\r\n");
//        }

//        HAL_Delay(20);  // ������ʱ
//    }
			
			if(key[0].single_flag==1)
			{
				 uint8_t Send_Out[2] = "1";  // ׼����������"1"	
			
				key1_press_count++;
				OLED_ShowString(1, 1, "key1_num:");
    OLED_ShowNum(1, 11, key1_press_count, 2); // ��ʾ����3�����µĴ���

				
        if (NRF24L01_TxPacket(Send_Out) == TX_OK)
        {
            printf("NRF24L01����ģ�����ݷ��ͳɹ���%s\r\n", Send_Out);
            printf("OK\r\n");
            OLED_ShowString(8, 2, (char*)Send_Out);  // ��OLED����ʾ���յ�������

        }
        else
        {
            printf("NRF24L01����ģ�����ݷ���ʧ��\r\n");
        }
				
				key[0].single_flag=0;
			}


			if(key[1].single_flag==1)
			{
				uint8_t Send_Out[2] = "2";  // ׼����������"2"
			
				key2_press_count++;
				OLED_ShowString(2, 1, "key2_num:");
    OLED_ShowNum(2, 11, key2_press_count, 2); // ��ʾ����3�����µĴ���

				
        if (NRF24L01_TxPacket(Send_Out) == TX_OK)
        {
            printf("NRF24L01����ģ�����ݷ��ͳɹ���%s\r\n", Send_Out);
            printf("OK\r\n");
            OLED_ShowString(8, 2, (char*)Send_Out);  // ��OLED����ʾ���յ�������

        }
        else
        {
            printf("NRF24L01����ģ�����ݷ���ʧ��\r\n");
        }

				
				key[1].single_flag=0;
			}

			if(key[2].single_flag==1)
			{
				key3_press_count++;
				OLED_ShowString(3, 1, "key3_num:");
    OLED_ShowNum(3, 11, key3_press_count, 2); // ��ʾ����3�����µĴ���

				 uint8_t Send_Out[2] = "3";  // ׼����������"3"      
	       
        if (NRF24L01_TxPacket(Send_Out) == TX_OK)
        {
            printf("NRF24L01����ģ�����ݷ��ͳɹ���%s\r\n", Send_Out);
            printf("OK\r\n");
            OLED_ShowString(8, 2, (char*)Send_Out);  // ��OLED����ʾ���յ�������
            
        }
        else
        {
            printf("NRF24L01����ģ�����ݷ���ʧ��\r\n");
        }
				
				
				key[2].single_flag=0;
			}
		
  }
  /* USER CODE END 3 */
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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
