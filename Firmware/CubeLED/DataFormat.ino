/*
  Project : 
    Cube LED
  Module :
    Data format module
  Description : 
    This module implement how to transfer data package to Cube LED.
    
Version 0.1 :
  2013/11/03 -[Alen Chen] - Initial

*/

int DF_handlePackage(uint8_t * ledBuffer, uint8_t ledSize, uint8_t * packageBuff, uint8_t packageSize, int * timeValue, uint8_t * elementIndex)
{
	uint32_t time = 0;
	uint8_t	* elementBuffer = packageBuff;
	uint8_t elementNum;
        
	if(ledSize < LED_CUBE_SIZE)
		return false;
		
	if(*(packageBuff + PACKAGE_HEAD_POS) != PACKAGE_HEAD_START)
		return false;

	elementNum = *(packageBuff + PACKAGE_HEAD_NUM_POS);

	if((* elementIndex) >= elementNum)
		(* elementIndex) = 0;
	
	for(int offsetIndex = 0; offsetIndex <= (* elementIndex); offsetIndex++)
	{
		elementBuffer += *(packageBuff + PACKAGE_HEAD_OFFSET_POS + offsetIndex);
	}
	
	if(*(elementBuffer + PACKAGE_START_POS) != PACKAGE_ELEMENT_START)
		return false;
	
	memset(ledBuffer, 0x00, ledSize);

	for(int timeIndex = 0; timeIndex < PACKAGE_TIME_SIZE; timeIndex++)
	{
		time = ((time) << 8) + (*(elementBuffer + PACKAGE_TIME_POS + timeIndex));
	}

    *timeValue = time;
        
	switch((int)*(elementBuffer + PACKAGE_TAG_POS))
	{
	case TAG_SINGLE_LED:
		return DF_handleSingle(ledBuffer, ledSize, elementBuffer, packageSize);
		break;
	case TAG_CUBE_LED:
		return DF_handleCube(ledBuffer, ledSize, elementBuffer, packageSize);
		break;
	default:
		return false;
	}
}

int DF_handleSingle(uint8_t * ledBuffer, uint8_t ledSize, uint8_t * packageBuff, uint8_t packageSize)
{
	int ledNum = *(packageBuff + PACKAGE_DATA_POS);
	uint8_t *data = packageBuff + PACKAGE_DATA_POS + 1;
	
	for(int ledIndex = 0; ledIndex < ledNum; ledIndex++)
	{
		int layer = ((*(data + ledIndex )) & PACKAGE_TAG_SINGLE_LAYER_MASK) >> PACKAGE_TAG_SINGLE_LAYER_POS;
		int led = (*(data + ledIndex )) & PACKAGE_TAG_SINGLE_LED_MASK;
		
		if(layer >= LED_LAYER_NUM)
			return false;

		uint32_t bitLed = (uint32_t) 1 << led;
		
		*(ledBuffer + (layer * LED_FLAT_NUM)) = bitLed & 0x00FF;
		*(ledBuffer + (layer * LED_FLAT_NUM) + 1) = (bitLed & 0xFF00) >> 8;
		 	
	}

	return true;
}

int DF_handleCube(uint8_t * ledBuffer, uint8_t ledSize, uint8_t * packageBuff, uint8_t packageSize)
{
	uint8_t *data = packageBuff + PACKAGE_DATA_POS;
	
	memcpy(ledBuffer, data, ledSize);
	
	return true;
}

