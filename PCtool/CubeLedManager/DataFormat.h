#ifndef DATAFORMAT_H
#define DATAFORMAT_H
//	Package head :
//	Byte		Byte	Byte		Byte			NUM Bytes
//	[ HEAD ]	[ NUM ]	[ Offset ] [ Offset ] ...[]

//	Element :
//	Single LED :
//  Byte		Byte	 2 Byte	 	 Byte	Byte	 n Bytes (HEX)
//	[ START]	[ TAG ]	[ Time ]	[ NUM ]	[ POS ]	...]
//	[ POS ] = Layer[7:5] Pos[4:0]

//	Cube LED :
//	Byte		Byte	 2 Byte		8 Bytes(Bit)
//	[ START ]	[ TAG ]	[ Time ]	[ POS ]

#define PACKAGE_HEAD_POS		0
#define PACKAGE_HEAD_NUM_POS	1
#define PACKAGE_HEAD_OFFSET_POS	2

#define PACKAGE_START_POS	0
#define PACKAGE_TAG_POS		1
#define PACKAGE_TIME_POS	2
#define PACKAGE_DATA_POS	4
#define PACKAGE_TIME_SIZE	2
#define PACKAGE_TAG_CUBE_SIZE	8
#define PACKAGE_TAG_SINGLE_SIZE	1

#define PACKAGE_TAG_SINGLE_LAYER_MASK	0xC0
#define PACKAGE_TAG_SINGLE_LAYER_POS	6

#define PACKAGE_TAG_SINGLE_LED_MASK		0x0F

#define PACKAGE_HEAD_START			0xCC
#define PACKAGE_ELEMENT_START		0xAA

enum
{
    TAG_SINGLE_LED = (int)0,
    TAG_CUBE_LED,

    TAG_TOTAL_NUM
};

#define LAYER_NUM   4
#define LED_NUM     16

#define SINGAL_LED_PACKAGE_SIZE 8

#endif // DATAFORMAT_H
