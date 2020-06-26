#include "OLED.h"
bit DHT_Start();	
bit DHT_ByteRead(unsigned char *dat);
int x;
//延时子程序
void delay ()
{
 x=99999;
 while(x--);
}
void main()
{
	u8 t;
	bit tmp;
	unsigned char DHT[5];
	unsigned char str[12];
	OLED_Init();			//初始化OLED 
	OLED_Clear();
	OLED_ShowCHinese(0,0,0);
	OLED_ShowCHinese(18,0,1);
	OLED_ShowChar(34,0,':');//显示ASCII字符 
	
	OLED_ShowCHinese(0,2,2);
	OLED_ShowCHinese(18,2,3);
	OLED_ShowChar(34,2,':');//显示ASCII字符 
	
	
	DHT_Start();
	delay();
  delay();
  delay();
  delay();
	while(1)
	{
		delay();
		DHT_Start();
		tmp = DHT_ByteRead(&DHT);
		if(tmp==1)
		  {
				 str[0] = (DHT[0]/10)%10 + '0';  //十位转为ASCII码
				 OLED_ShowChar(42,0,str[0]);//显示ASCII字符	
				
				 str[1] = (DHT[0]%10) + '0';  //个位转为ASCII
				 OLED_ShowChar(50,0,str[1]);//显示ASCII字符 
					OLED_ShowChar(58,0,'%');
					OLED_ShowChar(66,0,'R');
					OLED_ShowChar(74,0,'H');
				
				 str[0] = (DHT[2]/10)%10 + '0';  //十位转为ASCII码
				 OLED_ShowChar(42,2,str[0]);//显示ASCII字符	
				
				 str[1] = (DHT[2]%10) + '0';  //个位转为ASCII
				 OLED_ShowChar(50,2,str[1]);//显示ASCII字符	
				OLED_ShowCHinese(58,2,4); //℃
				
				 str[2] = '\0';
				
		   }
	}
}