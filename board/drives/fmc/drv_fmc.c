/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date          Author         
    Notes
 * 2018-08-14    flybreak           the first version
 * 2018-09-18    balanceTWK         add sleep mode function
 * 2018-09-27    ZYLX               optimized display speed
 * 2019-03-03    liu2guang          adapter RTTGameBoard
 */
#include "rtthread.h"
#include <rtdevice.h>
#include <board.h>


#include "drv_fmc.h"

#define DBG_ENABLE
#define DBG_SECTION_NAME    "drv.fmc"
#define DBG_COLOR
#define DBG_LEVEL           DBG_LOG
#include <rtdbg.h>

/*
	安富莱STM32-H7 开发板扩展口线分配: FMC总线地址 = 0x64001000
		
	D0  - GPRS_RERM_ON
	D1  - GPRS_RESET
	D2  - NRF24L01_CE
	D3  - NRF905_TX_EN
	D4  - NRF905_TRX_CE/VS1053_XDCS
	D5  - NRF905_PWR_UP
	D6  - ESP8266_G0
	D7  - ESP8266_G2
	
	D8  - LED1
	D9  - LED2
	D10 - LED3
	D11 - LED4
	D12 - TP_NRST	(缺省由硬件NRST复位触摸屏，软件控制触屏复位未启用）
	D13 - AD7606_OS0
	D14 - AD7606_OS1
	D15 - AD7606_OS2
	
	预留的8个5V输出IO: Y50_0 - Y50_1
	D16  - Y50_0
	D17  - Y50_1
	D18  - Y50_2
	D19  - Y50_3
	D20  - Y50_4
	D21  - Y50_5
	D22  - Y50_6
	D23  - Y50_7	

	预留的8个3.3V输出IO: Y33_0 - Y33_1
	D24  - AD7606_RESET
	D25  - AD7606_RAGE
	D26  - Y33_2
	D27  - Y33_3
	D28  - Y33_4
	D29  - Y33_5
	D30  - Y33_6
	D31  - Y33_7				
*/

#define  HC574_PORT	 *(uint32_t *)0x60001000

void hc574_gpio_config(void)
{
/*
	安富莱STM32-H7开发板接线方法：4片74HC574挂在FMC 32位总线上。1个地址端口可以扩展出32个IO
	PD0/FMC_D2
	PD1/FMC_D3
	PD4/FMC_NOE		---- 读控制信号，OE = Output Enable ， N 表示低有效
	PD5/FMC_NWE		-XX- 写控制信号，AD7606 只有读，无写信号
	PD8/FMC_D13
	PD9/FMC_D14
	PD10/FMC_D15
	PD14/FMC_D0
	PD15/FMC_D1

	PE7/FMC_D4
	PE8/FMC_D5
	PE9/FMC_D6
	PE10/FMC_D7
	PE11/FMC_D8
	PE12/FMC_D9
	PE13/FMC_D10
	PE14/FMC_D11
	PE15/FMC_D12
	
	PG0/FMC_A10		--- 和主片选FMC_NE2一起译码
	PG1/FMC_A11		--- 和主片选FMC_NE2一起译码
	XX --- PG9/FMC_NE2		--- 主片选（OLED, 74HC574, DM9000, AD7606）	
	 --- PD7/FMC_NE1		--- 主片选（OLED, 74HC574, DM9000, AD7606）	
	
	 +-------------------+------------------+
	 +   32-bits Mode: D31-D16              +
	 +-------------------+------------------+
	 | PH8 <-> FMC_D16   | PI0 <-> FMC_D24  |
	 | PH9 <-> FMC_D17   | PI1 <-> FMC_D25  |
	 | PH10 <-> FMC_D18  | PI2 <-> FMC_D26  |
	 | PH11 <-> FMC_D19  | PI3 <-> FMC_D27  |
	 | PH12 <-> FMC_D20  | PI6 <-> FMC_D28  |
	 | PH13 <-> FMC_D21  | PI7 <-> FMC_D29  |
	 | PH14 <-> FMC_D22  | PI9 <-> FMC_D30  |
	 | PH15 <-> FMC_D23  | PI10 <-> FMC_D31 |
	 +------------------+-------------------+	
*/	

    GPIO_InitTypeDef gpio_init_struct;

    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOI_CLK_ENABLE();

	__HAL_RCC_FMC_CLK_ENABLE();

    gpio_init_struct.Mode = GPIO_MODE_AF_PP;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio_init_struct.Alternate = GPIO_AF12_FMC;

	/* 配置GPIOD */
	gpio_init_struct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7 |
	                            GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 |
	                            GPIO_PIN_15;
	HAL_GPIO_Init(GPIOD, &gpio_init_struct);

	/* 配置GPIOE */
	gpio_init_struct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |
	                            GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |
	                            GPIO_PIN_15;
	HAL_GPIO_Init(GPIOE, &gpio_init_struct);

	/* 配置GPIOG */
	gpio_init_struct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
	HAL_GPIO_Init(GPIOG, &gpio_init_struct);
	
	/* 配置GPIOH */
	gpio_init_struct.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12
						| GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	HAL_GPIO_Init(GPIOH, &gpio_init_struct);

	/* 配置GPIOI */
	gpio_init_struct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_6
						| GPIO_PIN_7 | GPIO_PIN_9 | GPIO_PIN_10;
	HAL_GPIO_Init(GPIOI, &gpio_init_struct);
}

void hc574_config_fmc(void)
{
    SRAM_HandleTypeDef hsram = {0};
    FMC_NORSRAM_TimingTypeDef SRAM_Timing = {0};

    hsram.Instance = FMC_NORSRAM_DEVICE;
    hsram.Extended = FMC_NORSRAM_EXTENDED_DEVICE;

    /* FMC使用的HCLK3，主频200MHz，1个FMC时钟周期就是5ns */
	/* SRAM 总线时序配置 4-1-2-1-2-2 不稳定，5-2-2-1-2-2 稳定 */  
	SRAM_Timing.AddressSetupTime       = 5;  /* 5*5ns=25ns，地址建立时间，范围0 -15个FMC时钟周期个数 */
	SRAM_Timing.AddressHoldTime        = 2;  /* 地址保持时间，配置为模式A时，用不到此参数 范围1 -15个时钟周期个数 */
	SRAM_Timing.DataSetupTime          = 2;  /* 2*5ns=10ns，数据保持时间，范围1 -255个时钟周期个数 */
	SRAM_Timing.BusTurnAroundDuration  = 1;  /* 此配置用不到这个参数 */
	SRAM_Timing.CLKDivision            = 2;  /* 此配置用不到这个参数 */
	SRAM_Timing.DataLatency            = 2;  /* 此配置用不到这个参数 */
	SRAM_Timing.AccessMode             = FMC_ACCESS_MODE_A; /* 配置为模式A */

    /* FMC使用的HCLK3，主频200MHz，1个FMC时钟周期就是5ns */
	/* SRAM 总线时序配置 4-1-2-1-2-2 不稳定，5-2-2-1-2-2 稳定 */  
	SRAM_Timing.AddressSetupTime       = 5;  /* 5*5ns=25ns，地址建立时间，范围0 -15个FMC时钟周期个数 */
	SRAM_Timing.AddressHoldTime        = 2;  /* 地址保持时间，配置为模式A时，用不到此参数 范围1 -15个时钟周期个数 */
	SRAM_Timing.DataSetupTime          = 2;  /* 2*5ns=10ns，数据保持时间，范围1 -255个时钟周期个数 */
	SRAM_Timing.BusTurnAroundDuration  = 1;  /* 此配置用不到这个参数 */
	SRAM_Timing.CLKDivision            = 2;  /* 此配置用不到这个参数 */
	SRAM_Timing.DataLatency            = 2;  /* 此配置用不到这个参数 */
	SRAM_Timing.AccessMode             = FMC_ACCESS_MODE_A; /* 配置为模式A */

	hsram.Init.NSBank             = FMC_NORSRAM_BANK1;              /* 使用的BANK1，即使用的片选FMC_NE1 */
	hsram.Init.DataAddressMux     = FMC_DATA_ADDRESS_MUX_DISABLE;   /* 禁止地址数据复用 */
	hsram.Init.MemoryType         = FMC_MEMORY_TYPE_SRAM;           /* 存储器类型SRAM */
	hsram.Init.MemoryDataWidth    = FMC_NORSRAM_MEM_BUS_WIDTH_32;	/* 32位总线宽度 */
	hsram.Init.BurstAccessMode    = FMC_BURST_ACCESS_MODE_DISABLE;  /* 关闭突发模式 */
	hsram.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;   /* 用于设置等待信号的极性，关闭突发模式，此参数无效 */
	hsram.Init.WaitSignalActive   = FMC_WAIT_TIMING_BEFORE_WS;      /* 关闭突发模式，此参数无效 */
	hsram.Init.WriteOperation     = FMC_WRITE_OPERATION_ENABLE;     /* 用于使能或者禁止写保护 */
	hsram.Init.WaitSignal         = FMC_WAIT_SIGNAL_DISABLE;        /* 关闭突发模式，此参数无效 */
	hsram.Init.ExtendedMode       = FMC_EXTENDED_MODE_DISABLE;      /* 禁止扩展模式 */
	hsram.Init.AsynchronousWait   = FMC_ASYNCHRONOUS_WAIT_DISABLE;  /* 用于异步传输期间，使能或者禁止等待信号，这里选择关闭 */
	hsram.Init.WriteBurst         = FMC_WRITE_BURST_DISABLE;        /* 禁止写突发 */
	hsram.Init.ContinuousClock    = FMC_CONTINUOUS_CLOCK_SYNC_ONLY; /* 仅同步模式才做时钟输出 */
    hsram.Init.WriteFifo          = FMC_WRITE_FIFO_ENABLE;          /* 使能写FIFO */

	/* 初始化SRAM控制器 */
	if (HAL_SRAM_Init(&hsram, &SRAM_Timing, &SRAM_Timing) != HAL_OK)
	{
		/* 初始化错误 */
		LOG_E("sram init failed");
        return;
	}

}

void hc574_set_pin(rt_base_t pin, rt_base_t value)
{
    if(value == 0)
    {
        HC574_PORT &= (~pin);
    }
    else if(value == 1)
    {
        HC574_PORT |= pin;
    }
    
}

uint8_t hc574_get_pin(rt_base_t pin)
{
    if(HC574_PORT & pin)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}

static rt_err_t hc574_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t result = RT_EOK;
    struct hc574_pin_status *pin;

    pin = (struct hc574_pin_status *)args;

    if(dev != RT_NULL)
    {
        switch(cmd)
        {
        case HC574_SET_PIN:
            hc574_set_pin(pin->pin_num, pin->pin_status);
            break;
        
        case HC574_GET_PIN:
            
            break;

        default:
            break;
        }
    }
	return result;
}

const static struct rt_device_ops ops = 
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    hc574_control
};

static void rt_hw_fmc_init(void)
{
    rt_device_t dev = RT_NULL;

	dev = (struct rt_device *)rt_malloc(sizeof(struct rt_device));
    hc574_gpio_config();
    hc574_config_fmc();

	dev->type = RT_Device_Class_Miscellaneous;
    dev->ops = &ops;
    rt_device_register(dev, "fmc", RT_DEVICE_FLAG_RDWR);

	return;
}
INIT_APP_EXPORT(rt_hw_fmc_init);
