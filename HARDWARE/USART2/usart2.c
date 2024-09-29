#include "stm32f10x.h"  //包含需要的头文件
#include "usart2.h"     //包含需要的头文件
#include "esp.h"     //包含需要的头文件
#if  USART2_RX_ENABLE             

uint8_t USART2_RX_BUF[USART2_REC_LEN];	//接收缓冲,最大UART4_REC_LEN个字节

//接收状态
uint16_t USART2_RX_COUNT=0;	//接收到的有效字节数目，最大USART1_REC_LEN字节
uint8_t F_USART2_RX_FINISH=0;//接收状态标记,1:UART4接收完成，0：UART4接收未完成
uint8_t F_USART2_RX_RECEIVING=0;//串口接收正在进行中标记,1:进行中，0：暂停或结束
uint8_t USART2_RX_TIMEOUT_COUNT=0;	//串口接收超时计数。串口超过3ms未接收到数据，视为超时。单位：ms
u32		USART2_RX_STA=0;
u8  RECS[]; 			//发送缓冲,最大USART3_MAX_SEND_LEN字节 
extern int NetWorkStatu;
int USART2_receive_ok;

#endif

/*-------------------------------------------------*/
/*函数名：初始化串口2发送功能                      */
/*参  数：bound：波特率                            */
/*返回值：无                                       */
/*-------------------------------------------------*/
void USART2_Init(unsigned int bound)
{  	 	
    GPIO_InitTypeDef GPIO_InitStructure;     //定义一个设置GPIO功能的变量
	USART_InitTypeDef USART_InitStructure;   //定义一个设置串口功能的变量
#if USART2_RX_ENABLE                         //如果使能接收功能
	NVIC_InitTypeDef NVIC_InitStructure;     //如果使能接收功能，定义一个设置中断的变量
#endif

#if USART2_RX_ENABLE                                 //如果使能接收功能
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //设置中断向量分组：第2组 抢先优先级：0 1 2 3 子优先级：0 1 2 3
#endif	
      
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);  //使能串口2时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //使能GPIOA时钟
	USART_DeInit(USART2);                                  //串口2寄存器重新设置为默认值
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;              //准备设置PA2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      //IO速率50M
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	       //复用推挽输出，用于串口2的发送
    GPIO_Init(GPIOA, &GPIO_InitStructure);                 //设置PA2
   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;              //准备设置PA3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入，用于串口2的接收
    GPIO_Init(GPIOA, &GPIO_InitStructure);                 //设置PA3
	
	USART_InitStructure.USART_BaudRate = bound;                                    //波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                    //8个数据位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                         //1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;                            //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
#if USART2_RX_ENABLE               												   //如果使能接收模式
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	               //收发模式
#else                                                                              //如果不使能接收模式
	USART_InitStructure.USART_Mode = USART_Mode_Tx ;	                           //只发模式
#endif        
    USART_Init(USART2, &USART_InitStructure);                                      //设置串口2	

#if USART2_RX_ENABLE  	

//如果使能接收模式
 
 
 
	USART_ClearFlag(USART2, USART_FLAG_RXNE);	            //清除接收标志位
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);          //开启接收中断
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;       //设置串口2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//中断通道使能
	NVIC_Init(&NVIC_InitStructure);	                        //设置串口2中断
#endif  

	

	USART_Cmd(USART2, ENABLE);                              //使能串口2
}

/*-------------------------------------------------*/
/*函数名：串口2 printf函数                         */
/*参  数：char* fmt,...  格式化输出字符串和参数    */
/*返回值：无                                       */
/*-------------------------------------------------*/

__align(8) char USART2_TxBuff[USART2_TXBUFF_SIZE];  

void u2_printf(char* fmt,...) 
{  
	unsigned int i,length;
	
	va_list ap;
	va_start(ap,fmt);
	vsprintf(USART2_TxBuff,fmt,ap);
	va_end(ap);	
	
	length=strlen((const char*)USART2_TxBuff);		
	while((USART2->SR&0X40)==0);
	for(i = 0;i < length;i ++)
	{			
		USART2->DR = USART2_TxBuff[i];
		while((USART2->SR&0X40)==0);	
	}	
}

/*-------------------------------------------------*/
/*函数名：串口2发送缓冲区中的数据                  */
/*参  数：data：数据                               */
/*返回值：无                                       */
/*-------------------------------------------------*/
void u2_TxData(unsigned char *data)
{
	int	i;	
	while((USART2->SR&0X40)==0);
	for(i = 1;i <= (data[0]*256+data[1]);i ++){			
		USART2->DR = data[i+1];
		while((USART2->SR&0X40)==0);	
	}
}

/******************************************************************************
* Function Name --> 串口4发送一个字节数据
* Description   --> nonevoid USART1_SendData(uint16_t Data)
* Input         --> bound：波特率	
* Output        --> none
* Reaturn       --> none 
******************************************************************************/
void USART2_SendData(uint16_t Data)
{
	while((USART2->SR & 0x40) == 0);	//等待发送完毕
	USART_SendData(USART2, Data);
}

/******************************************************************************
* Function Name --> 串口4发送一串数据，指定数据长度
* Description   --> none
* Input         --> *Data:字符串，len长度	
* Output        --> none
* Reaturn       --> none 
******************************************************************************/
void USART2_SendStrlen(uint8_t *Data, uint8_t len)//Data： AT+CIPSTART=\"TCP\",\"120.77.58.34"\",8700
{
	while(len--)
	{
		USART2_SendData((uint16_t )(*Data));
		Data++;
	}
}


/*******************************************************************
*函数：void SendAtCmd(uint8_t *string)
*功能：发送AT指令字符串
*输入：
		uint8_t *string 待发送的AT指令
		uint8_t len 长度
*输出：无
*特殊说明：无
*******************************************************************/
void SendAtCmd(uint8_t *string, uint8_t len)
{
	USART2_SendStrlen(string, len);
	USART2_SendStrlen((uint8_t *)"\r\n", 2);
}

void USART2_RX_Data(void);
/*-------------------------------------------------*/
/*函数名：串口2接收中断函数                        */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
//void USART2_IRQHandler(void)                	//串口1中断服务程序
//	{
//	u8 Res;
//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
//		{
//			
//			USART_ClearITPendingBit(USART2,USART_IT_RXNE);
//			
//			Res =USART_ReceiveData(USART2);	//读取接收到的数据
//		
//		if((USART2_RX_STA&0x8000)==0)//接收未完成
//			{
//			if(USART2_RX_STA&0x4000)//接收到了0x0d
//				{
//					if(Res!=0x0a)USART2_RX_STA=0;//接收错误,重新开始
//					else 
//					{
//						USART2_RX_STA|=0x8000;	//接收完成了 
//						F_USART2_RX_FINISH=1;
//					}
//				}
//			else //还没收到0X0D
//				{	
//					if(Res==0x0d)USART2_RX_STA|=0x4000;
//					else
//						{
//							USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
//							USART2_RX_STA++;
//							if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//接收数据错误,重新开始接收	  
//						}		 
//				}
//			}   		 
//     } 
//	USART2_RX_Data();
//	

//} 
	
void USART2_RX_Data(void)
{
	u8 len=0;
	u8 i=0;
	if(USART2_RX_STA&0x8000)
		{	
							   
			len=USART2_RX_STA&0X7FFF;//得到此次接收到的数据长度
			USART2_RX_BUF[len]=0;	 	//加入结束符
			
			if(len>USART2_REC_LEN-2)
			{
				len=USART2_REC_LEN-1;
				USART2_RX_BUF[len]=0;	 	//加入结束符
			}
			
			USART2_RX_BUF[USART2_REC_LEN-1]=0x01;
		for(i=0;i<USART2_REC_LEN;i++)
			{
				RECS[i]=USART2_RX_BUF[i];
			}
			
			printf("USART2接收到RECS：%s\r\n",RECS);
			if(substringMatch((char *)RECS,"items")==1)USART2_receive_ok=1;		//接收完成
			
			//T1=analy("led");
			if(substringMatch((char *)RECS,"WIFI DISCONNECT")==1)NetWorkStatu=0;	//离线检测		
			USART2_RX_STA=0;
		}
 
}


