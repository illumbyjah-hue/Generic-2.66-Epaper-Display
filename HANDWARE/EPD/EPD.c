#include "EPD.h"
#include "delay.h"

/*******************************************************************
		函数说明:判忙函数
		入口参数:无
		说明:忙状态为1		
*******************************************************************/
void EPD_READBUSY(void)
{
	while(1)
	{
		if(EPD_ReadBusy==0)
		{
			break;
		}
	}
}

/*******************************************************************
		函数说明:硬件复位函数
		入口参数:无
		说明:在E-Paper进入Deepsleep状态后需要硬件复位	
*******************************************************************/
void EPD_HW_RESET(void)
{
	delay_ms(100);
	EPD_RES_Clr();
	delay_ms(10);
	EPD_RES_Set();
	delay_ms(10);
	EPD_READBUSY();
}

/*******************************************************************
		函数说明:更新函数
		入口参数:无	
		说明:更新显示内容到E-Paper		
*******************************************************************/
void EPD_Update(void)
{
	EPD_WR_REG(0x22);
	EPD_WR_DATA8(0xF4);
	EPD_WR_REG(0x20);
	EPD_READBUSY();
}
/*******************************************************************
		函数说明:休眠函数
		入口参数:无
		说明:屏幕进入低功耗模式		
*******************************************************************/
void EPD_DeepSleep(void)
{
	EPD_WR_REG(0x10);
	EPD_WR_DATA8(0x01);
	delay_ms(200);
}


void EPD_Init(void)
{
	EPD_HW_RESET();
	EPD_READBUSY();   
	EPD_WR_REG(0x12);  //SWRESET
	EPD_READBUSY();   
	
	EPD_WR_REG(0x3C); //BorderWavefrom
	EPD_WR_DATA8(0x05);
	
	EPD_WR_REG(0x01); //Driver output control      
	EPD_WR_DATA8((EPD_H-1)%256);    
	EPD_WR_DATA8((EPD_H-1)/256);
	EPD_WR_DATA8(0x00); 

	EPD_WR_REG(0x11); //data entry mode       
	EPD_WR_DATA8(0x02);
	EPD_WR_REG(0x44); //set Ram-X address start/end position   
	EPD_WR_DATA8(EPD_W/8-1);    
	EPD_WR_DATA8(0x00);  
	EPD_WR_REG(0x45); //set Ram-Y address start/end position          
	EPD_WR_DATA8(0x00);
	EPD_WR_DATA8(0x00); 
  EPD_WR_DATA8((EPD_H-1)%256); 
	EPD_WR_DATA8((EPD_H-1)/256);
	EPD_WR_REG(0x21); //  Display update control
	EPD_WR_DATA8(0x00);		
  EPD_WR_DATA8(0x80);	
  EPD_WR_REG(0x18); //Read built-in temperature sensor
	EPD_WR_DATA8(0x80);	
	EPD_WR_REG(0x4E);   // set RAM x address count to 0;
	EPD_WR_DATA8(EPD_W/8-1);    
	EPD_WR_REG(0x4F);   // set RAM y address count to 0X199;    
	EPD_WR_DATA8(0x00);
	EPD_WR_DATA8(0x00);
  EPD_READBUSY();
}

/*******************************************************************
		函数说明:清屏函数
		入口参数:无
		说明:E-Paper刷白屏
*******************************************************************/
void EPD_Display_Clear(void)
{
  u16 i;
	EPD_WR_REG(0x3C);
	EPD_WR_DATA8(0x01);
	EPD_WR_REG(0x24);
	for(i=0;i<5624;i++)
	{
		EPD_WR_DATA8(0xFF);
	}	
	EPD_WR_REG(0x26);
	for(i=0;i<5624;i++)
	{
		EPD_WR_DATA8(0xFF);
	}	
}



void EPD_Display(const u8 *BWImage,const u8 *RImage)
{
	u16 i,j,Width,Height;
	Width = (EPD_W%8==0)?(EPD_W/8):(EPD_W/8+1);
	Height = EPD_H;
	EPD_WR_REG(0x24);
	for (j=0;j<Height;j++) 
	{
		for (i=0;i<Width;i++) 
		{
			EPD_WR_DATA8(BWImage[i+j*Width]);
		}
	}
	EPD_WR_REG(0x26);
	for (j=0;j<Height;j++) 
	{
		for (i=0;i<Width;i++) 
		{
			EPD_WR_DATA8(~RImage[i+j*Width]);
		}
	}
	EPD_Update();	
}


