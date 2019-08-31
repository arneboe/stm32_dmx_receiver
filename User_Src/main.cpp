#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "usart.h"
#include "tim.h"
#include "dma.h"
#include "DmxReceiver.h"


extern "C" {
void SystemClock_Config();
}

void dmxFrameReceived(const uint8_t* buffer);
void init();

volatile bool frameReceived = false;
const uint8_t* dmxBuffer = nullptr;

int main() {
    init();

    while(true)
    {
        if(frameReceived)
        {
            frameReceived = false;
            for(int i = 0; i < 10; ++i)
            {
                printf("%03d ", dmxBuffer[i]);
            }
            printf("\n");
        }
        if(!DmxReceiver::connected())
            printf("disconnected!\n");
    }
}

void dmxFrameReceived(const uint8_t* buffer)
{
    dmxBuffer = buffer;
    frameReceived = true;
}

void init()
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USART1_UART_Init();
    MX_USART3_UART_Init();
    MX_TIM3_Init();
    DmxReceiver::init(dmxFrameReceived);
    printf("Startup complete\n");
}

