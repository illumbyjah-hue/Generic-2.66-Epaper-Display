#ifndef _EPD_H_
#define _EPD_H_

#include "SPI_Init.h"

#define EPD_W	152 
#define EPD_H	296

#define WHITE 0xFF
#define BLACK 0x00
#define RED   BLACK


void EPD_READBUSY(void);
void EPD_HW_RESET(void);
void EPD_Update(void);
void EPD_DeepSleep(void);
void EPD_Init(void);
void EPD_Display_Clear(void);
void EPD_Display(const u8 *BWImage,const u8 *RImage);
#endif




