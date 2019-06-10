#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "usart.h"
#include "tim.h"
#include "dma.h"

#define DMX_MIN_BREAK_TIME_US 80
#define DMX_MAX_BREAK_TIME_US 1000 //FIXME find a good value for this
#define DMX_FRAME_SIZE 513

extern "C" {
void SystemClock_Config();
}

uint8_t buffer[DMX_FRAME_SIZE] = {0};

int main() {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USART1_UART_Init();
    MX_USART3_UART_Init();
    MX_TIM3_Init();

    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);

    printf("Startup complete\n");

    while(true)
    {
        for(int i = 0; i < DMX_FRAME_SIZE; ++i)
        {
            printf("%03d ", buffer[i]);
        }
        printf("\n");
        HAL_Delay(1000);
    }
}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance==TIM3)
    {
        //Falling
        if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
        {
            //start counting on falling edge
            __HAL_TIM_SET_COUNTER(&htim3, 0);
        }
        //Rising
        else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {
            const uint32_t currentTime = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
            if(currentTime > DMX_MIN_BREAK_TIME_US && currentTime < DMX_MAX_BREAK_TIME_US)
            {
                //end of break, start next read
                HAL_UART_Receive_DMA(&huart3, buffer, DMX_FRAME_SIZE);
            }
            else if (currentTime > DMX_MAX_BREAK_TIME_US)
            {
                //signal dmx disconnected or something?
            }
        }
    }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{

    if(huart->Instance == USART3)
    {
        //check if we got any data at all before the error occurred. If yes we got a smaller frame which is also fine.
        //If not dmx has been disconnected
    }


}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART3)
    {
        //signal that we got a new frame or whatever here
    }
}