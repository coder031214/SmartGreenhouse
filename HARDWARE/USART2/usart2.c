#include "stm32f10x.h"  //������Ҫ��ͷ�ļ�
#include "usart2.h"     //������Ҫ��ͷ�ļ�
#include "esp.h"     //������Ҫ��ͷ�ļ�
#if  USART2_RX_ENABLE             

uint8_t USART2_RX_BUF[USART2_REC_LEN];	//���ջ���,���UART4_REC_LEN���ֽ�

//����״̬
uint16_t USART2_RX_COUNT=0;	//���յ�����Ч�ֽ���Ŀ�����USART1_REC_LEN�ֽ�
uint8_t F_USART2_RX_FINISH=0;//����״̬���,1:UART4������ɣ�0��UART4����δ���
uint8_t F_USART2_RX_RECEIVING=0;//���ڽ������ڽ����б��,1:�����У�0����ͣ�����
uint8_t USART2_RX_TIMEOUT_COUNT=0;	//���ڽ��ճ�ʱ���������ڳ���3msδ���յ����ݣ���Ϊ��ʱ����λ��ms
u32		USART2_RX_STA=0;
u8  RECS[]; 			//���ͻ���,���USART3_MAX_SEND_LEN�ֽ� 
extern int NetWorkStatu;
int USART2_receive_ok;

#endif

/*-------------------------------------------------*/
/*����������ʼ������2���͹���                      */
/*��  ����bound��������                            */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void USART2_Init(unsigned int bound)
{  	 	
    GPIO_InitTypeDef GPIO_InitStructure;     //����һ������GPIO���ܵı���
	USART_InitTypeDef USART_InitStructure;   //����һ�����ô��ڹ��ܵı���
#if USART2_RX_ENABLE                         //���ʹ�ܽ��չ���
	NVIC_InitTypeDef NVIC_InitStructure;     //���ʹ�ܽ��չ��ܣ�����һ�������жϵı���
#endif

#if USART2_RX_ENABLE                                 //���ʹ�ܽ��չ���
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�����ж��������飺��2�� �������ȼ���0 1 2 3 �����ȼ���0 1 2 3
#endif	
      
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);  //ʹ�ܴ���2ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //ʹ��GPIOAʱ��
	USART_DeInit(USART2);                                  //����2�Ĵ�����������ΪĬ��ֵ
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;              //׼������PA2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      //IO����50M
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	       //����������������ڴ���2�ķ���
    GPIO_Init(GPIOA, &GPIO_InitStructure);                 //����PA2
   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;              //׼������PA3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //�������룬���ڴ���2�Ľ���
    GPIO_Init(GPIOA, &GPIO_InitStructure);                 //����PA3
	
	USART_InitStructure.USART_BaudRate = bound;                                    //����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                    //8������λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                         //1��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;                            //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
#if USART2_RX_ENABLE               												   //���ʹ�ܽ���ģʽ
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	               //�շ�ģʽ
#else                                                                              //�����ʹ�ܽ���ģʽ
	USART_InitStructure.USART_Mode = USART_Mode_Tx ;	                           //ֻ��ģʽ
#endif        
    USART_Init(USART2, &USART_InitStructure);                                      //���ô���2	

#if USART2_RX_ENABLE  	

//���ʹ�ܽ���ģʽ
 
 
 
	USART_ClearFlag(USART2, USART_FLAG_RXNE);	            //������ձ�־λ
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);          //���������ж�
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;       //���ô���2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//�ж�ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	                        //���ô���2�ж�
#endif  

	

	USART_Cmd(USART2, ENABLE);                              //ʹ�ܴ���2
}

/*-------------------------------------------------*/
/*������������2 printf����                         */
/*��  ����char* fmt,...  ��ʽ������ַ����Ͳ���    */
/*����ֵ����                                       */
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
/*������������2���ͻ������е�����                  */
/*��  ����data������                               */
/*����ֵ����                                       */
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
* Function Name --> ����4����һ���ֽ�����
* Description   --> nonevoid USART1_SendData(uint16_t Data)
* Input         --> bound��������	
* Output        --> none
* Reaturn       --> none 
******************************************************************************/
void USART2_SendData(uint16_t Data)
{
	while((USART2->SR & 0x40) == 0);	//�ȴ��������
	USART_SendData(USART2, Data);
}

/******************************************************************************
* Function Name --> ����4����һ�����ݣ�ָ�����ݳ���
* Description   --> none
* Input         --> *Data:�ַ�����len����	
* Output        --> none
* Reaturn       --> none 
******************************************************************************/
void USART2_SendStrlen(uint8_t *Data, uint8_t len)//Data�� AT+CIPSTART=\"TCP\",\"120.77.58.34"\",8700
{
	while(len--)
	{
		USART2_SendData((uint16_t )(*Data));
		Data++;
	}
}


/*******************************************************************
*������void SendAtCmd(uint8_t *string)
*���ܣ�����ATָ���ַ���
*���룺
		uint8_t *string �����͵�ATָ��
		uint8_t len ����
*�������
*����˵������
*******************************************************************/
void SendAtCmd(uint8_t *string, uint8_t len)
{
	USART2_SendStrlen(string, len);
	USART2_SendStrlen((uint8_t *)"\r\n", 2);
}

void USART2_RX_Data(void);
/*-------------------------------------------------*/
/*������������2�����жϺ���                        */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
//void USART2_IRQHandler(void)                	//����1�жϷ������
//	{
//	u8 Res;
//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
//		{
//			
//			USART_ClearITPendingBit(USART2,USART_IT_RXNE);
//			
//			Res =USART_ReceiveData(USART2);	//��ȡ���յ�������
//		
//		if((USART2_RX_STA&0x8000)==0)//����δ���
//			{
//			if(USART2_RX_STA&0x4000)//���յ���0x0d
//				{
//					if(Res!=0x0a)USART2_RX_STA=0;//���մ���,���¿�ʼ
//					else 
//					{
//						USART2_RX_STA|=0x8000;	//��������� 
//						F_USART2_RX_FINISH=1;
//					}
//				}
//			else //��û�յ�0X0D
//				{	
//					if(Res==0x0d)USART2_RX_STA|=0x4000;
//					else
//						{
//							USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
//							USART2_RX_STA++;
//							if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
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
							   
			len=USART2_RX_STA&0X7FFF;//�õ��˴ν��յ������ݳ���
			USART2_RX_BUF[len]=0;	 	//���������
			
			if(len>USART2_REC_LEN-2)
			{
				len=USART2_REC_LEN-1;
				USART2_RX_BUF[len]=0;	 	//���������
			}
			
			USART2_RX_BUF[USART2_REC_LEN-1]=0x01;
		for(i=0;i<USART2_REC_LEN;i++)
			{
				RECS[i]=USART2_RX_BUF[i];
			}
			
			printf("USART2���յ�RECS��%s\r\n",RECS);
			if(substringMatch((char *)RECS,"items")==1)USART2_receive_ok=1;		//�������
			
			//T1=analy("led");
			if(substringMatch((char *)RECS,"WIFI DISCONNECT")==1)NetWorkStatu=0;	//���߼��		
			USART2_RX_STA=0;
		}
 
}


