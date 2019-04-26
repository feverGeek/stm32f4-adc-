#ifndef __ADC_H
#define __ADC_H	

#include "sys.h" 
 							   
void MY_ADCx_Regular_Init(uint32_t RCC_GPIOxPeriph, uint32_t GPIO_Pinx, uint32_t RCC_ADCxPeriph, uint8_t ADC_Channel);
void MY_ADCx_Regular_Double_Channel_Init(uint32_t RCC_GPIOxPeriph, uint32_t GPIO_Pinx1, uint32_t GPIO_Pinx2, uint32_t RCC_ADCxPeriph, uint8_t ADC_Channel1, uint8_t ADC_Channel2);
void DMA_Configuration(void);
u16 Get_ADC_Value(ADC_TypeDef* ADCx);
u16 Get_ADC_Average(ADC_TypeDef* ADCx, u8 times);

//ADC序号的宏定义  
#define RHEOSTAT_ADC              ADC3  
#define RHEOSTAT_ADC_CLK          RCC_APB2Periph_ADC3  
//外设基地址  
#define RHEOSTAT_ADC_DR_ADDR    ((u32)ADC3+0x4c)    
#define RHEOSTAT_NOFCHANEL      4  
//ADC DMA通道宏定义  
#define RHEOSTAT_ADC_DMA_CLK      RCC_AHB1Periph_DMA2  
#define RHEOSTAT_ADC_DMA_CHANNEL  DMA_Channel_2  
#define RHEOSTAT_ADC_DMA_STREAM   DMA2_Stream0  
 

void Lsens_Init(void);
void  Adc3_Init(void);
#endif 















