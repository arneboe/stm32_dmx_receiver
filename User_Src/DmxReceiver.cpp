#include "DmxReceiver.h"
#include "tim.h"
#include "usart.h"

#define DMX_MIN_BREAK_TIME_US 80
#define DMX_MAX_BREAK_TIME_US 1000

#define DMX_CONNECTED_TIMEOUT_MS 1000

uint8_t DmxReceiver::buffer[DMX_FRAME_SIZE] = {0};
DmxFrameCallback DmxReceiver::callback = nullptr;
uint32_t DmxReceiver::lastReceivedTime = 0;

void DmxReceiver::init(DmxFrameCallback frameReceivedCallback) {
    callback = frameReceivedCallback;
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);
}

void DmxReceiver::signalFrameReceived() {
    DmxReceiver::lastReceivedTime = HAL_GetTick();
    if(nullptr != callback)
        callback(buffer);
}

bool DmxReceiver::connected() {
    return (HAL_GetTick() - lastReceivedTime) < DMX_CONNECTED_TIMEOUT_MS;
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
                HAL_UART_Receive_DMA(&huart3, DmxReceiver::buffer, DMX_FRAME_SIZE);
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
        DmxReceiver::signalFrameReceived();
    }
}

