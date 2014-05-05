#ifndef COMMUNICATION_H
#define COMMUNICATION_H
/*

                            Host	<--------------->	Cube Led
    - Check Device			0xCA
    - Response											0xCA + [DEVICE_ID]

    - Check to Send Data	0xCB + [DATA_SIZE]
    - Ready to Receive									0xCB + [DATA_SIZE]

    - Send Data				0xCC + [PACKAGE_DATA] + [CHECKSUM]
    - Success											0xCC + [DATA_SIZE]
    - Fail												0xCC + [0x00]


    DEVICE_ID : 1 Byte
    DATA_SIZE : 2 Bytes

*/

#define COM_RECEIVE_BUFFER_SIZE		512

#define COM_TAG_CHECK_DEVICE		0xCA
#define COM_TAG_CHECK_TO_SEND		0xCB
#define COM_TAG_SEND_DATA			0xCC

#define COM_FAIL					0x00

#define DEVICE_ID_4x4x4_CUBE_LED	0x10

#define DATA_SIZE_LEN				2

#define TAG_SIZE				1
#define CHECKSUM_SIZE			1

enum
{
    CMD_CHECK_DEVICE = 0,
    CMD_CHECK_TO_SEND,
    CMD_SEND_DATA,

    TOTAL_CMD_NUMBER,

    CMD_NULL
};


#endif // COMMUNICATION_H
