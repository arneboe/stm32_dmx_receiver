#pragma once
#include <cstdint>

#define DMX_FRAME_SIZE 513

/**The @p buffer remain valid forever, no need to copy anything! */
typedef void (*DmxFrameCallback)(const uint8_t* buffer);

/** A simple dmx receiver that uses TIM3 channel 1 and channel 2 and USART 3 */
class DmxReceiver {
private:
    static DmxFrameCallback callback;
    static uint32_t lastReceivedTime;

public:
    static void init(DmxFrameCallback frameReceivedCallback);
    static bool connected();


    //should be private
    static uint8_t buffer[DMX_FRAME_SIZE];
    static void signalFrameReceived();

};

