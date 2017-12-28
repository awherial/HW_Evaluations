/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l1xx_hal.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "EncodeProCmd.h"
#include "HumPro_900MHz.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_NVIC_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
uint8_t     reg_value;
uint8_t     mydsn_byte[4];
uint8_t     f_humpro_print_regs;

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
  ERROR_TYPE_E   result;

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_UART5_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();

  /* USER CODE BEGIN 2 */
    result = humpro_init ();
    HAL_Delay (300);
    //humpro_update_all_regs ();
    humpro_print_regs (VOLATILE);
    humpro_print_regs (NON_VOL);

    humpro_print_version();
    humpro_print_address();
    humpro_print_addrsng_mode ();
    humpro_print_config ();

/*
//    //baud rate changed to 115200 at both sides
//    result = humpro_read_reg_addr    (0x6e, &reg_value);
//    result = humpro_write_reg   (0x6e, 0x01);    // received data will be sent when CMD linw is high, will be bufferred until then
//    result = humpro_read_reg_addr    (0x6e, &reg_value);
//
//    result = humpro_read_reg_addr    (0x34, &reg_value);
//    mydsn_byte[3] = reg_value;
//    result = humpro_read_reg_addr    (0x35, &reg_value);
//    mydsn_byte[2] = reg_value;
//    result = humpro_read_reg_addr    (0x36, &reg_value);
//    mydsn_byte[1] = reg_value;
//    result = humpro_read_reg_addr    (0x37, &reg_value);
//    mydsn_byte[0] = reg_value;
//
//
//        //uint8_t   humpro_read_reg_addr  (uint8_t  reg_addr, uint8_t  * received_bytes)  {
//    result = humpro_read_reg_addr    (0x4e, &reg_value);
//    if (reg_value != 0x05)  {
//        //result = humpro_write_reg   (0x03, 0x01);    //
//        result = humpro_write_reg   (0x4e, 0x05);    //
//        if (result == 0x06)  {
//            MX_UART5_reInit_baudRate    (115200);   //9600);
//        }
//        else    {
//            //MX_UART5_reInit_baudRate    (9600);
//        }
////        result = humpro_read_reg_addr    (0x4e, &reg_value);
//    }
//    result = humpro_read_reg_addr    (0x4e, &reg_value);
*/


    result = humpro_read_reg_id    (CMDHOLD, VOLATILE, &reg_value);
    result = humpro_write_reg_id   (CMDHOLD, VOLATILE, 0x01);    // received data will be sent when CMD linw is high, will be bufferred until then
    result = humpro_read_reg_id    (CMDHOLD, VOLATILE, &reg_value);

        //uint8_t   humpro_read_reg_id  (uint8_t  reg_addr, uint8_t  * received_bytes)  {
    result = humpro_read_reg_id    (UARTBAUD, VOLATILE, &reg_value);
    if (reg_value != 0x05)  {
        //result = humpro_write_reg   (0x03, 0x01);    //
        result = humpro_write_reg_id   (UARTBAUD, VOLATILE, 0x05);    //
        if (result == HUM_PRO_ACK)  {   //0x06)  {
            MX_UART5_reInit_baudRate    (115200);   //9600);
        }
        else    {
            //MX_UART5_reInit_baudRate    (9600);
        }
//        result = humpro_read_reg_id    (UARTBAUD, &reg_value);
    }
    result = humpro_read_reg_id    (UARTBAUD, VOLATILE, &reg_value);

    result = humpro_read_reg_id    (MYDSN3, NON_VOL, &reg_value);
    mydsn_byte[3] = reg_value;
    result = humpro_read_reg_id    (MYDSN2, NON_VOL, &reg_value);
    mydsn_byte[2] = reg_value;
    result = humpro_read_reg_id    (MYDSN1, NON_VOL, &reg_value);
    mydsn_byte[1] = reg_value;
    result = humpro_read_reg_id    (MYDSN0, NON_VOL, &reg_value);
    mydsn_byte[0] = reg_value;



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
      if (f_humpro_print_regs)  {
          f_humpro_print_regs = 0;
          humpro_print_regs(VOLATILE);
      }
  }
  /* USER CODE END 3 */

}












/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage
    */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/** NVIC Configuration
*/
static void MX_NVIC_Init(void)
{
  /* EXTI15_10_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
  /* EXTI9_5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
  /* EXTI4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);
  /* EXTI3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */

/**
  * @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
