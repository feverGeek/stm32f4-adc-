
/****************/

#include "adc.h"
#include "delay.h"		 

uint16_t ADC_ConvertedValue[RHEOSTAT_NOFCHANEL]={0}; 
extern u16 ADC_Value[2];		  

void Lsens_Init(void)  
{  
  GPIO_InitTypeDef  GPIO_InitStructure;  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);  //使能GPIOF时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入  
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉  
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化  
}  

                                                      
void  Adc3_Init(void)  
{      
    DMA_InitTypeDef DMA_InitStructure;  
    ADC_CommonInitTypeDef ADC_CommonInitStructure;  
    ADC_InitTypeDef       ADC_InitStructure;      
    //使能DMA对应的时钟   
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);   
      
    DMA_DeInit(DMA2_Stream0);   
    //选择DMA通道，通道存在于数据流中  
    DMA_InitStructure.DMA_Channel = RHEOSTAT_ADC_DMA_CHANNEL;   
    //外设的基地址  
    DMA_InitStructure.DMA_PeripheralBaseAddr = RHEOSTAT_ADC_DR_ADDR;      
    //存储器地址，实际是一个定义好的数组  
    DMA_InitStructure.DMA_Memory0BaseAddr = (u32)ADC_ConvertedValue;     
    //传输方向为从外设到内存  
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;   
    //缓冲区大小，指的是一次传输的数据量  
    DMA_InitStructure.DMA_BufferSize = RHEOSTAT_NOFCHANEL;     
    //外设寄存器只有一个，地址不需要自增  
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
       //存储器地址自增  
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;   
        //  外设数据大小为半字，即两个字节  
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;   
       //存储器大小也为半字  ´  
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;   
    //循环传输模式  
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  
        //DMA传输通道优先级为最高  
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;  
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;    
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;  
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;  
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;    
      
    DMA_Init(RHEOSTAT_ADC_DMA_STREAM, &DMA_InitStructure);  
    DMA_Cmd(RHEOSTAT_ADC_DMA_STREAM, ENABLE);  
  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);          
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;  
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;  
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;   
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;  
    ADC_CommonInit(&ADC_CommonInitStructure);  
  
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;  
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;  
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;  
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;      
    ADC_InitStructure.ADC_NbrOfConversion = RHEOSTAT_NOFCHANEL;      
    ADC_Init(ADC3, &ADC_InitStructure);  
   
   //设置转换通道的顺序  
    ADC_RegularChannelConfig(RHEOSTAT_ADC, ADC_Channel_9, 1, ADC_SampleTime_15Cycles);  
    ADC_RegularChannelConfig(RHEOSTAT_ADC, ADC_Channel_14, 2, ADC_SampleTime_15Cycles);   
    ADC_RegularChannelConfig(RHEOSTAT_ADC, ADC_Channel_15, 3,  ADC_SampleTime_15Cycles);   
    ADC_RegularChannelConfig(RHEOSTAT_ADC, ADC_Channel_4, 4,  ADC_SampleTime_15Cycles);   
    ADC_DMARequestAfterLastTransferCmd(RHEOSTAT_ADC, ENABLE);   
    ADC_DMACmd(RHEOSTAT_ADC, ENABLE);  
      
    ADC_Cmd(ADC3, ENABLE);    
    ADC_SoftwareStartConv(RHEOSTAT_ADC);    
} 