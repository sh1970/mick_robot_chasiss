#ifndef __NRF_24l01_H
#define __NRF_24l01_H


#include "stm32f10x.h"

//��Ƭ��Ϊ���� 24l01Ϊ�ӻ�    ����MISO�Ӵӻ�MISO
//****************************************NRF24L01�˿ڶ���***************************************

#define 	MOSI_Out_H	     GPIO_SetBits(GPIOA,GPIO_Pin_7) //��Ϊ����   
#define 	MOSI_Out_L	     GPIO_ResetBits(GPIOA,GPIO_Pin_7)//����

 
#define 	MISO	          GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//����������

#define		SCK_Out_H	      GPIO_SetBits(GPIOA,GPIO_Pin_5) //��Ϊ����   
#define		SCK_Out_L       GPIO_ResetBits(GPIOA,GPIO_Pin_5)//���� 

#define		CE_Out_H	      GPIO_SetBits(GPIOG,GPIO_Pin_8) //��Ϊ����   
#define		CE_Out_L	      GPIO_ResetBits(GPIOG,GPIO_Pin_8)//����

#define		CSN_Out_H	      GPIO_SetBits(GPIOG,GPIO_Pin_15) //��Ϊ����   
#define		CSN_Out_L       GPIO_ResetBits(GPIOG,GPIO_Pin_15)//����

 
	//  IRQ ===  GPIOC,  GPIO_Pin_4 
 




//*********************************************NRF24L01*************************************
#define 		TX_ADR_WIDTH    5   	// 5 uints TX address width
#define 		RX_ADR_WIDTH    5   	// 5 uints RX address width
#define 		TX_PLOAD_WIDTH  32  	// 20 uints TX payload �����ݳ��ȣ�
#define 		RX_PLOAD_WIDTH  32  	// 20 uints TX payload


//*************NRF24L01�Ĵ���ָ��*******************************************************//

#define NRF_24l01_READ_REG        0x00  	// ���Ĵ���ָ��
#define NRF_24l01_WRITE_REG       0x20 	// д�Ĵ���ָ��
#define NRF_24l01_RD_RX_PLOAD     0x61  	// ��ȡ��������ָ��
#define NRF_24l01_WR_TX_PLOAD     0xA0  	// д��������ָ��
#define NRF_24l01_FLUSH_TX        0xE1 	 // ��ϴ���� FIFOָ��
#define NRF_24l01_FLUSH_RX        0xE2  	// ��ϴ���� FIFOָ��
#define NRF_24l01_REUSE_TX_PL     0xE3  	// �����ظ�װ������ָ��
#define NRF_24l01_NOP             0xFF  	// ����

//*************SPI(nRF24L01)�Ĵ�����ַ****************************************************//

#define CONFIG          0x00  // �����շ�״̬��CRCУ��ģʽ�Լ��շ�״̬��Ӧ��ʽ
#define EN_AA           0x01  // �Զ�Ӧ��������
#define EN_RXADDR       0x02  // �����ŵ�����
#define SETUP_AW        0x03  // �շ���ַ��������
#define SETUP_RETR      0x04  // �Զ��ط���������
#define RF_CH           0x05  // ����Ƶ������
#define RF_SETUP        0x06  // �������ʡ����Ĺ�������
#define STATUS          0x07  // ״̬�Ĵ���
#define OBSERVE_TX      0x08  // ���ͼ�⹦��
#define CD              0x09  // ��ַ���           
#define RX_ADDR_P0      0x0A  // Ƶ��0�������ݵ�ַ
#define RX_ADDR_P1      0x0B  // Ƶ��1�������ݵ�ַ
#define RX_ADDR_P2      0x0C  // Ƶ��2�������ݵ�ַ
#define RX_ADDR_P3      0x0D  // Ƶ��3�������ݵ�ַ
#define RX_ADDR_P4      0x0E  // Ƶ��4�������ݵ�ַ
#define RX_ADDR_P5      0x0F  // Ƶ��5�������ݵ�ַ
#define TX_ADDR         0x10  // ���͵�ַ�Ĵ���
#define RX_PW_P0        0x11  // ����Ƶ��0�������ݳ���
#define RX_PW_P1        0x12  // ����Ƶ��0�������ݳ���
#define RX_PW_P2        0x13  // ����Ƶ��0�������ݳ���
#define RX_PW_P3        0x14  // ����Ƶ��0�������ݳ���
#define RX_PW_P4        0x15  // ����Ƶ��0�������ݳ���
#define RX_PW_P5        0x16  // ����Ƶ��0�������ݳ���
#define FIFO_STATUS     0x17  // FIFOջ��ջ��״̬�Ĵ�������
//*****************************************************************************

void init_NRF24L01(void);//��ʼ������ͨ�ź���
void SwitchToTxMode(void);//�л�������ģʽ
void SwitchToRxMode(void);//�л�������ģʽ
void Transmit_Tx_bufferdata(unsigned char *pBuf);//��txbuff �е����ݷ��ͳ�ȥ
 
unsigned char SPI_Read_Buf(unsigned char reg, unsigned char *pBuf, unsigned char uchars);
unsigned char SPI_Write_Buf(unsigned char reg, unsigned char *pBuf, unsigned char uchars);
unsigned char SPI_RW_Reg(unsigned char reg, unsigned char value);
unsigned char SPI_Read(unsigned char reg);
unsigned char SPI_RW(unsigned char dat);

void NRF24L01_Delayus(unsigned int n);

unsigned char NRF24l01_Interrupt_Handle(void);//���ӷ���ֵ��Ҫ�Ƿ����жϺ�������;

#endif
 

/****************************�жϷ�����************************************************
void IRS_ET0() interrupt 0
{		 
	 EX0=0;  
	 sta=0;
	 sta = SPI_Read(STATUS);	  // ��״̬�Ĵ���
	  if(sta&0x40)  //�����ж�
		{
			SPI_Read_Buf(RD_RX_PLOAD,RxBuf,TX_PLOAD_WIDTH);// read receive payload from RX_FIFO buffer	
			led0=~led0;	   
			flag=1;		  
		}
		else if(sta&0x20)  //�����ж�
		{
			led1=~led1;
			flag=2;
      SPI_RW_Reg(FLUSH_TX,0xff); 			
		}
		//else if(sta & 0x10)  //����ط����
		//{
		//	led2=~led2;
		//	flag=3;	
		//}
		else ;
	 SPI_RW_Reg(WRITE_REG + STATUS, 0xff); //��������жϱ�־λ 
		EX0=1;
}

*****************************************************************************************/