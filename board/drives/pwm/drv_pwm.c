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

#include "drv_pwm.h"

#define DBG_ENABLE
#define DBG_SECTION_NAME    "drv.pwm"
#define DBG_COLOR
#define DBG_LEVEL           DBG_LOG
#include <rtdbg.h>

static struct stm32_pwm
{
    struct rt_device_pwm pwm_device;
    TIM_HandleTypeDef tim_handle;
    rt_uint8_t channel;
    char *name;
};

static struct stm32_pwm pwm = {0};

static rt_err_t drv_pwm_enable(TIM_HandleTypeDef *htim, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    
}

static rt_err_t drv_pwm_set(TIM_HandleTypeDef *htim, struct rt_pwm_configuration *configuration)
{
    rt_uint64_t tim_clock;
    TIM_OC_InitTypeDef oc_config = {0};
    GPIO_InitTypeDef   gpio_initstruct;

    // TIM3_CH1,  PA6   PC6  PB4
    // TIM3_CH2,  PA7   PC7  PB5   
    // TIM3_CH3,  PB0   PC8  
    // TIM3_CH4,  PB1   PC9  

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_TIM3_CLK_ENABLE();
	gpio_initstruct.Mode = GPIO_MODE_AF_PP;
	gpio_initstruct.Pull = GPIO_PULLUP;
	gpio_initstruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	gpio_initstruct.Alternate = GPIO_AF2_TIM3;
	gpio_initstruct.Pin = GPIO_PIN_6;
	HAL_GPIO_Init(GPIOA, &gpio_initstruct);

    tim_clock = SystemCoreClock / 2;

    htim->Init.Prescaler = tim_clock / (1000000000 / configuration->period);
    htim->Init.Period = tim_clock / htim->Init.Prescaler / (1000000000 / configuration->period);
    htim->Init.ClockDivision = 0;
    htim->Init.CounterMode = TIM_COUNTERMODE_UP;
	htim->Init.RepetitionCounter = 0;
	htim->Init.AutoReloadPreload = 0;

    HAL_TIM_PWM_Init(htim);

	oc_config.OCMode       = TIM_OCMODE_PWM1;
	oc_config.OCPolarity   = TIM_OCPOLARITY_HIGH;
	oc_config.OCFastMode   = TIM_OCFAST_DISABLE;
	oc_config.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
	oc_config.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	oc_config.OCIdleState  = TIM_OCIDLESTATE_RESET;

    oc_config.Pulse = htim->Init.Period / (configuration->period / configuration->pulse);
    HAL_TIM_PWM_ConfigChannel(htim, &oc_config, configuration->channel);
    HAL_TIM_PWM_Start(htim, configuration->channel);

}

static rt_err_t drv_pwm_get(TIM_HandleTypeDef *htim, struct rt_pwm_configuration *configuration)
{

}

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;
    TIM_HandleTypeDef *htim = (TIM_HandleTypeDef *)device->parent.user_data;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return drv_pwm_enable(htim, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return drv_pwm_enable(htim, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return drv_pwm_set(htim, configuration);
    case PWM_CMD_GET:
        return drv_pwm_get(htim, configuration);
    default:
        return RT_EINVAL;
    }
}

static struct rt_pwm_ops drv_ops = 
{
    drv_pwm_control
};

static int stm32_pwm_init(void)
{
    pwm.name = "pwm3";
    pwm.channel = TIM_CHANNEL_1;
    
    if(rt_device_pwm_register(&pwm.pwm_device, "pwm3", &drv_ops, &pwm.tim_handle) == RT_EOK)
    {
        LOG_D("%s register success", pwm.name);
    }
    else
    {
        LOG_E("%s register success", pwm.name);
    }
    
    return RT_EOK;
}
INIT_DEVICE_EXPORT(stm32_pwm_init);
