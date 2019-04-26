
/****************/

#include "adc.h"
#include "delay.h"		 

uint16_t ADC_ConvertedValue[RHEOSTAT_NOFCHANEL]={0}; 
extern u16 ADC_Value[2];
/*
* @file    adc.c
* @author  
* @brief   
* @param   
* @retval None
*/
// void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void MY_ADC_GPIO_Config(uint32_t RCC_GPIOxPeriph, uint32_t GPIO_Pinx)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* GPIO config */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pinx;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

    if (RCC_GPIOxPeriph == RCC_AHB1Periph_GPIOA)
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
    else if (RCC_GPIOxPeriph == RCC_AHB1Periph_GPIOB)
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
    else if (RCC_GPIOxPeriph == RCC_AHB1Periph_GPIOC)
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }
    else if (RCC_GPIOxPeriph == RCC_AHB1Periph_GPIOF)
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); 
        GPIO_Init(GPIOF, &GPIO_InitStructure);
    }
}

void DMA_Configuration(void) 
{   
	DMA_InitTypeDef DMA_InitStructure;  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA2时钟使能 

    DMA_InitStructure.DMA_Channel = DMA_Channel_0;
	DMA_InitStructure.DMA_PeripheralBaseAddr = ((u32)ADC3+0x4c); //DMA外设ADC基地址 
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)ADC_Value; //DMA内存基地址  
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory; // 外设作为数据传输的来源
	DMA_InitStructure.DMA_BufferSize = 2; //DMA通道的DMA缓存的大小  
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址寄存器不变 
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //内存地址寄存器递增 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //数据宽度为16位  
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //数据宽度为16位  
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //工作在循环缓存模式，当传输完一次后，重新接着传送，永不停息。 
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMA通道 x拥有高优先级  
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; 
	DMA_Init(DMA2_Stream0, &DMA_InitStructure); //根据DMA_InitStruct中指定的参数初始化DMA的通道
    DMA_Cmd(DMA2_Stream0, ENABLE);
}

/*
* @file    adc.c
* @author  
* @brief   用于给ADC_CommonInitTypeDef类型结构体赋值
* @param   ADC_Mode              工作模式
*          ADC_TwoSamplingDelay  Configures the Delay between 2 sampling phases
*          ADC_DMAAccessMode     DMA传输模式
*          ADC_Prescaler         分频系数
* @retval None
*/
void MY_ADC_CommonInitTypeDef_Init(uint32_t ADC_Mode, uint32_t ADC_TwoSamplingDelay, uint32_t ADC_DMAAccessMode, uint32_t ADC_Prescaler)
{
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode; 
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler; 
    ADC_CommonInit(&ADC_CommonInitStructure);
}

/*
* @file    adc.c
* @author  
* @brief   用于给ADC_InitTypeDef类型结构体赋值
* @param   RCC_ADCxPeriph
*          ADC_Channel
*          Rank
*          ADC_Resolution
*          ADC_ScanConvMode
*          ADC_ContinuousConvMode
*          ADC_ExternalTrigConvEdge
*          ADC_DataAlign
*          ADC_NbrOfConversion
* @retval None
*/
void MY_ADC_InitTypeDef_Init(uint32_t RCC_ADCxPeriph, uint8_t ADC_Channel, uint8_t Rank, uint32_t ADC_Resolution, 
                            FunctionalState ADC_ScanConvMode, FunctionalState ADC_ContinuousConvMode, 
                            uint32_t ADC_ExternalTrigConvEdge, uint32_t ADC_DataAlign, uint8_t  ADC_NbrOfConversion)
{
    ADC_InitTypeDef       ADC_InitStructure;

    ADC_InitStructure.ADC_Resolution = ADC_Resolution;
    ADC_InitStructure.ADC_ScanConvMode = ADC_ScanConvMode;	
    ADC_InitStructure.ADC_ContinuousConvMode = ADC_ContinuousConvMode;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign;	
    ADC_InitStructure.ADC_NbrOfConversion = ADC_NbrOfConversion; 
    if (RCC_ADCxPeriph == RCC_APB2Periph_ADC1)  
    {
        ADC_Init(ADC1, &ADC_InitStructure);
        ADC_Cmd(ADC1, ENABLE);
        ADC_RegularChannelConfig(ADC1, ADC_Channel, Rank, ADC_SampleTime_480Cycles);
        ADC_Cmd(ADC1, ENABLE);                                                                      
        ADC_SoftwareStartConv(ADC1);   
    }
    else if (RCC_ADCxPeriph == RCC_APB2Periph_ADC2)
    {
        ADC_Init(ADC2, &ADC_InitStructure);
        ADC_Cmd(ADC2, ENABLE);
        ADC_RegularChannelConfig(ADC2, ADC_Channel, Rank, ADC_SampleTime_480Cycles);
        ADC_Cmd(ADC2, ENABLE);                                                                      
        ADC_SoftwareStartConv(ADC2);  
    }
    else if (RCC_ADCxPeriph == RCC_APB2Periph_ADC3)
    {
        ADC_Init(ADC3, &ADC_InitStructure);
        ADC_Cmd(ADC3, ENABLE);
        ADC_RegularChannelConfig(ADC3, ADC_Channel, Rank, ADC_SampleTime_480Cycles);
        ADC_Cmd(ADC3, ENABLE);                                                                      
        ADC_SoftwareStartConv(ADC3); 
    }
}

/*
* @file   adc.c 
* @author  
* @brief  ADCx规则组配置
*         单次，非连续转换模式，软件触发
* @param  RCC_GPIOxPeriph  RCC_AHB1Periph_GPIOA 
*                          RCC_AHB1Periph_GPIOB 
*                          RCC_AHB1Periph_GPIOC 
*                          RCC_AHB1Periph_GPIOF
*         GPIO_Pinx        adc通道对应的管脚
*         RCC_ADCxPeriph   RCC_APB2Periph_ADC1 
*                          RCC_APB2Periph_ADC2
*                          RCC_APB2Periph_ADC3
*         ADC_Channel      ADC_Channel_0 ~ ADC_Channel_18
* @retval None
*/
void  MY_ADCx_Regular_Init(uint32_t RCC_GPIOxPeriph, uint32_t GPIO_Pinx, uint32_t RCC_ADCxPeriph, uint8_t ADC_Channel)
{    

    /* GPIO config*/ 
    MY_ADC_GPIO_Config(RCC_GPIOxPeriph, GPIO_Pinx);

    /* ADC config */
    RCC_APB2PeriphClockCmd(RCC_ADCxPeriph, ENABLE); 
    RCC_APB2PeriphResetCmd(RCC_ADCxPeriph, ENABLE);	
    RCC_APB2PeriphResetCmd(RCC_ADCxPeriph,DISABLE);

	MY_ADC_CommonInitTypeDef_Init(ADC_Mode_Independent, ADC_TwoSamplingDelay_5Cycles, ADC_DMAAccessMode_Disabled, ADC_Prescaler_Div4);

    MY_ADC_InitTypeDef_Init(RCC_ADCxPeriph, ADC_Channel, 1, ADC_Resolution_12b, DISABLE, DISABLE, ADC_ExternalTrigConvEdge_None, ADC_DataAlign_Right, 1);
}				  

/*
* @file    adc.c
* @author  
* @brief   ADC 规则双通道转换  软件触发
* @param   RCC_GPIOxPeriph RCC_AHB1Periph_GPIOA 
*                          RCC_AHB1Periph_GPIOB 
*                          RCC_AHB1Periph_GPIOC 
*                          RCC_AHB1Periph_GPIOF
*          GPIO_Pinx1      adc通道1对应的管脚
*          GPIO_Pinx2      adc通道2对应的管脚
*          RCC_ADCxPeriph  RCC_APB2Periph_ADC1 
*                          RCC_APB2Periph_ADC2
*                          RCC_APB2Periph_ADC3
*          ADC_Channel1    ADC_Channel_0 ~ ADC_Channel_18
*          ADC_Channel2    ADC_Channel_0 ~ ADC_Channel_18
* @retval None
*/
void MY_ADCx_Regular_Double_Channel_Init(uint32_t RCC_GPIOxPeriph, uint32_t GPIO_Pinx1, uint32_t GPIO_Pinx2, uint32_t RCC_ADCxPeriph, uint8_t ADC_Channel1, uint8_t ADC_Channel2)
{ 
    /* GPIO Config */
    MY_ADC_GPIO_Config(RCC_GPIOxPeriph, GPIO_Pinx1);
    MY_ADC_GPIO_Config(RCC_GPIOxPeriph, GPIO_Pinx2);

    /* ADC config */
    RCC_APB2PeriphClockCmd(RCC_ADCxPeriph, ENABLE); 
    RCC_APB2PeriphResetCmd(RCC_ADCxPeriph, ENABLE);	
    RCC_APB2PeriphResetCmd(RCC_ADCxPeriph,DISABLE);

	MY_ADC_CommonInitTypeDef_Init(ADC_Mode_Independent, ADC_TwoSamplingDelay_5Cycles, ADC_DMAAccessMode_Disabled, ADC_Prescaler_Div4);

    MY_ADC_InitTypeDef_Init(RCC_ADCxPeriph, ADC_Channel1, 1, ADC_Resolution_12b, ENABLE, ENABLE, ADC_ExternalTrigConvEdge_None, ADC_DataAlign_Right, 2);
    MY_ADC_InitTypeDef_Init(RCC_ADCxPeriph, ADC_Channel2, 2, ADC_Resolution_12b, ENABLE, ENABLE, ADC_ExternalTrigConvEdge_None, ADC_DataAlign_Right, 2);
}


/*
* @file    adc.c
* @author  
* @brief   获取ADCx值
* @param   ADCx : ADC1 ADC2 ADC3
* @retval  ADCx转换值 
*/
u16 Get_ADC_Value(ADC_TypeDef* ADCx)
{
    ADC_SoftwareStartConv(ADCx);                               
    while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC ));     //等待转换结束
	return ADC_GetConversionValue(ADCx);	
}

/*
* @file    adc.c
* @author  
* @brief   获取ADC的平均采样值
* @param   ADCx : ADC1 ADC2 ADC3
*          times 采样次数
* @retval  ADC的平均采样值
*/
u16 Get_ADC_Average(ADC_TypeDef* ADCx, u8 times)
{
	u32 temp_val = 0;
	u8 t;
	for(t = 0; t < times; t++)
	{
		temp_val += Get_ADC_Value(ADCx);
		delay_ms(1);
	}
	return temp_val/times;
} 

/********************************************************************************/

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