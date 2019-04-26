#ifndef __ADC_H
#define __ADC_H	

#include "sys.h" 
 							   

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















