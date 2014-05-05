/*
  Project : 
    Cube LED
  Module :
    Communication module
  Description : 
    This module implement how to communicate between Cube LED and external device.
    
Version 0.1 :
  2014/03/27 -[Alen Chen] - Initial

*/

int CM_checkCommand(uint8_t data)
{
	int ret = CMD_NULL;

	switch(data)
	{
	case COM_TAG_CHECK_DEVICE:
		ret = CMD_CHECK_DEVICE;
		break;
	case COM_TAG_CHECK_TO_SEND:
		ret = CMD_CHECK_TO_SEND;
		break;
	case COM_TAG_SEND_DATA:
		ret = CMD_SEND_DATA;
		break;
	}

	return ret;
}
