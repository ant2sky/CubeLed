/*
  Project : 
    Cube LED
  Module :
    LED module
  Description : 
    This module implement how to display information by led.
    
Version 0.1 :
  2013/10/29 -[Alen Chen] - Initial

*/
#include "LED.h"
#include "TimerOne.h"

#define LED_FLUSH_TIME  500 

uint8_t ledLayerMap[LED_LAYER_NUM] = { LED_LAYER_1_BIT, LED_LAYER_2_BIT, LED_LAYER_3_BIT, LED_LAYER_4_BIT };

uint8_t ledStatus[LED_LAYER_NUM][LED_FLAT_NUM];
uint32_t durationTimer = 0;

uint32_t systemTime = 0;
uint8_t flushLayer = 0;
uint8_t lightLevelValue = 5;

void LED_send_data(uint32_t data)
{
	digitalWrite(LED_LATCH_PIN, LOW);
	for(int index = 0; index < (LED_MAX_NUM >> LED_SHIFT_WIDTH); index++)
	{
		shiftOut(LED_DATA_PIN, LED_CLOCK_PIN, MSBFIRST, (data >> (((LED_MAX_NUM >> LED_SHIFT_WIDTH) - index - 1) << LED_SHIFT_WIDTH)));
	}
	digitalWrite(LED_LATCH_PIN, HIGH);
}

void LED_setup()
{
	pinMode(LED_DATA_PIN, OUTPUT);
	pinMode(LED_LATCH_PIN, OUTPUT);
	pinMode(LED_CLOCK_PIN, OUTPUT);
	pinMode(LED_ENABLE, OUTPUT);
	pinMode(LED_ALL_CLEAR, OUTPUT);

	for(int layer_index = 0; layer_index < LED_LAYER_NUM; layer_index++)
		for(int flat_index = 0; flat_index < LED_FLAT_NUM; flat_index++)
			ledStatus[layer_index][flat_index] = 0;

	LED_reset();

	Timer1.initialize(LED_FLUSH_TIME);
	Timer1.attachInterrupt(LED_flushCube);
}

void LED_reset()
{
	digitalWrite(LED_ALL_CLEAR, LOW);
	delay(10);
	digitalWrite(LED_ALL_CLEAR, HIGH);
}

void LED_setOne(uint8_t layerIndex, uint8_t flatIndex, uint8_t value)
{
	ledStatus[layerIndex][flatIndex] = value;
}

void LED_setFlat(uint8_t layerIndex, uint8_t * value)
{
	for(int index = 0; index < LED_FLAT_NUM; index++)
		LED_setOne(layerIndex, index, value[index]);
}

void LED_setCube(uint8_t * value, uint8_t length)
{
  
    memcpy(ledStatus, value, length);
}

void LED_flushFlat(uint8_t layerIndex)
{
	uint32_t data = 0;

	if((systemTime % lightLevelValue) == 0)	
		data = ((uint32_t)ledStatus[layerIndex][1] << 8) | (uint32_t)ledStatus[layerIndex][0];
	else
		data = 0;
	
	LED_SET_ONE_BIT(data, ledLayerMap[layerIndex]);
	LED_send_data(data);
}

void LED_flushCube()
{
    flushLayer++;
    if(flushLayer >= LED_LAYER_NUM)
    {
      flushLayer = 0;
     systemTime++;
   }
     
	LED_flushFlat(flushLayer);
}

void LED_setLightLevel(int value)
{
    if(value != 0)
        lightLevelValue = value;
    else
        lightLevelValue = 1;
}
