#include  <errno.h>
#include  <sys/unistd.h> //for STDOUT_FILENO, STDERR_FILENO
#include "stm32f1xx_hal.h"
#include "usart.h"


int _write(int file, char *data, int len)
{
    if ((file != STDOUT_FILENO) && (file != STDERR_FILENO))
    {
        errno = EBADF;
        return -1;
    }
    HAL_StatusTypeDef status = HAL_UART_Transmit(&huart1, (uint8_t*)data, len, 2000);
    switch(status)
    {
        case HAL_OK:
            return len;
        case HAL_BUSY:
            errno = EBUSY;
            return -1;
        case HAL_TIMEOUT:
            errno = ETIMEDOUT;
            return -1;
        case HAL_ERROR:
            errno = EFAULT;
            return -1;
        default:
            errno = EFAULT;
            return -1;
    }
}
