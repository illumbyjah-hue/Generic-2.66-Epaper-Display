#include "delay.h"
#include "usart.h"
#include "EPD_GUI.h"
#include "Pic.h"


u8 ImageBW[5624];
u8 ImageR[5624];
int main()
{
	float num=12.05;
	u8 dat=0;
	delay_init();
	uart_init(115200);
	EPD_GPIOInit();
	/************************全刷************************/
	EPD_Init();
	printf("OK\r\n");
	Paint_NewImage(ImageBW,EPD_W,EPD_H,0,WHITE);		//创建画布
  Paint_Clear(WHITE);															//清空画布缓存
  Paint_NewImage(ImageR,EPD_W,EPD_H,0,WHITE);			//创建画布
  Paint_Clear(WHITE);															//清空画布缓存
	EPD_Display(ImageBW,ImageR);
	EPD_Update();
	printf("WHITE\r\n");
	EPD_Display(ImageBW,gImage_1);
	EPD_Update();
	EPD_DeepSleep();
	printf("gImage_1_OK\r\n");
	delay_ms(1000);	delay_ms(1000);
	Paint_Clear(WHITE);	
	EPD_Init();
	EPD_Display(gImage_3,ImageR);
	EPD_Update();
	EPD_DeepSleep();
	printf("gImage_3_OK\r\n");
	delay_ms(1000);	delay_ms(1000);
	Paint_Clear(WHITE);
	while(1)
	{
		EPD_Init();
		Paint_SelectImage(ImageR);
		EPD_ShowPicture(40,0,216,112,gImage_2,RED);
		Paint_SelectImage(ImageBW);
		EPD_ShowString(36,130,"2.66inch",16,BLACK);
		EPD_ShowChinese(100,130,"电子墨水屏断电可显示",16,BLACK);
		EPD_Display(ImageBW,ImageR);
		EPD_Update();
		EPD_DeepSleep();
		delay_ms(1000);	delay_ms(1000);
		EPD_Init();
		EPD_Display_Clear();
		EPD_Update();
		EPD_DeepSleep();delay_ms(1000);	delay_ms(1000);delay_ms(1000);	delay_ms(1000);delay_ms(1000);	delay_ms(1000);
		Paint_SelectImage(ImageR);
		Paint_Clear(WHITE);
		EPD_ShowString(33,0,"Welcome to 2.66-inch E-paper",16,BLACK);		
		EPD_ShowString(49,20,"with 296 x 152 resolution",16,BLACK);	
		EPD_DrawRectangle(0,0,295,151,BLACK,0);
		EPD_DrawRectangle(4,78,44,118,BLACK,0);
	  EPD_DrawCircle(265,100,25,BLACK,1);
		Paint_SelectImage(ImageBW);
		Paint_Clear(WHITE);
		EPD_ShowWatch(88,74,num,4,2,48,BLACK);
		EPD_DrawCircle(245,100,25,BLACK,0);
		EPD_DrawRectangle(48,78,88,119,BLACK,1);
		EPD_DrawLine(0,60,295,60,BLACK);
		EPD_ShowChinese(44,136,"郑州中景园电子科技有限公司",16,BLACK);
		EPD_Display(ImageBW,ImageR);
		EPD_Update();
		EPD_DeepSleep();
		delay_ms(1000);	delay_ms(1000);delay_ms(1000);	delay_ms(1000);
	}
}


