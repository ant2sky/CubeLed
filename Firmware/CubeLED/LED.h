/*
  Project : 
    Cube LED
  Module :
    LED Head File
  Description : 
    This head file for LED module.
    
Version 0.1 :
  2013/11/03 -[Alen Chen] - Initial

*/

#ifndef __LED_H__
#define __LED_H__

#define LED_DATA_PIN	2
#define LED_LATCH_PIN	3
#define LED_CLOCK_PIN	4

#define LED_ENABLE		7
#define LED_ALL_CLEAR	8

#define LED_DISPLAY_ON	digitalWrite(LED_ENABLE, LOW);
#define LED_DISPLAY_OFF	digitalWrite(LED_ENABLE, HIGH);


#define LED_MAX_NUM 24
#define LED_SHIFT_WIDTH	3		// 2^x
#define LED_SET_ONE_BIT(data,index) (data |= ((uint32_t)1 << index))

//  0       7 8       15        23
// |---- ----|---- ----|---- ----|

// [ 01 | 02 | 03 | 04 ]
// [ 05 | 06 | 07 | 08 ]
// [ 09 | 10 | 11 | 12 ]
// [ 13 | 14 | 15 | 16 ]

#define LED_FALT_MASE	0x00FFFF
#define LED_FLAT_CLEAR(x) (x &= ~LED_FALT_MASE)


// Layer  [High -> Low] : [ 1 | 2 | 3 | 4]
#define LED_LAYER_MASK	0x0F0000
#define LED_LAYER_CLEAR(x) (x &= ~LED_LAYER_MASK)
#define LED_LAYER_1_BIT		16
#define LED_LAYER_2_BIT		17
#define LED_LAYER_3_BIT		18
#define LED_LAYER_4_BIT		19

#define LED_LAYER_NUM	4

#define LED_FLAT_NUM	2 // 16/8

#define LED_CUBE_SIZE		LED_LAYER_NUM * LED_FLAT_NUM
#define LED_TOTAL_NUM	LED_LAYER_NUM * LED_FLAT_NUM * 8

#define LED_DELAY_TIME 100

#define LED_LIGHT_LEVEL_RANGE  50

#endif
