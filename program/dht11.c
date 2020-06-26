#include<reg52.h>
#include<intrins.h>
sbit DHT_DATA = P3^0;
bit DHT_Start();
bit DHT_ByteRead(unsigned char *dat);

void DHT11_delay_ms(unsigned char x)   //Îó²î -0.651041666667us
{
    unsigned char a,b,c;
	for(c=x;c>0;c--)
    {
		for(b=102;b>0;b--)
        for(a=3;a>0;a--);
	}
}

void delay_30us(void)   //Îó²î -0.703125us
{
    unsigned char a;
    for(a=12;a>0;a--);
}

void delay_40us(void)   //Îó²î -0.703125us
{
    unsigned char a,b;
    for(b=3;b>0;b--)
        for(a=4;a>0;a--);
}

bit DHT_Start()
{	
	unsigned char m=0;
	DHT_DATA=1;
	DHT_DATA=0;	
	DHT11_delay_ms(20);
	DHT_DATA=1;
	delay_40us();
	if(DHT_DATA == 1)
		return 0;
	else 
		while((DHT_DATA==0)&&(m<200))m++;
	delay_40us();
	delay_40us();
	return 1;				
}

bit DHT_ByteRead(unsigned char *dat)
{	unsigned char temp=0;
	unsigned char x,y;
	unsigned char m=0;
	unsigned char n=0;
	unsigned char mask=0x01;
	unsigned char sum=0;
	for(y=0;y<5;y++)
	{
		for(mask=0x80;mask!=0;mask>>=1)
		{	
			while(DHT_DATA==0&&m<200)m++;
			delay_30us();
			if(DHT_DATA)
				temp|=mask;
			else
				temp&=(~mask);
			while(DHT_DATA==1&&n<200)n++;
		}
		*(dat+y)=temp;
		temp=0;
	}
	for(x=0;x<4;x++)
		sum+=*(dat+x);	
	if((sum&=0xff)==*(dat+4))
		return 1;
	else 
		return 0;
}