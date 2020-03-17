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


#include "drv_hwtimer.h"

#define DBG_ENABLE
#define DBG_SECTION_NAME    "drv.hwtimer"
#define DBG_COLOR
#define DBG_LEVEL           DBG_LOG
#include <rtdbg.h>

static struct stm32_hwtimer
{
    rt_hwtimer_t time_device;
    TIM_HandleTypeDef tim_handle;
    IRQn_Type tim_irqn;
    char *name;
};

static struct stm32_hwtimer hwtimer = {0};

void TIM2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&hwtimer.tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2)
    {
        rt_device_hwtimer_isr(&hwtimer.time_device);
    }
}

static void timer_init(struct rt_hwtimer_device *timer, rt_uint32_t state)
{
    uint32_t prescaler_value = 0;
    struct stm32_hwtimer *tim_device = RT_NULL;
    TIM_HandleTypeDef *tim = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    __HAL_RCC_TIM2_CLK_ENABLE();
    if(state)
    {
        tim = timer->parent.user_data;
        tim_device = (struct stm32_hwtimer *)timer;
        tim->Init.Prescaler         = 1;
        tim->Init.Period            = 10000 - 1;
        tim->Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
        if(timer->info->cntmode == HWTIMER_CNTMODE_UP)
        {
            tim->Init.CounterMode   = TIM_COUNTERMODE_UP;
        }
        else
        {
            tim->Init.CounterMode   = TIM_COUNTERMODE_DOWN;
        }
        tim->Init.RepetitionCounter = 0;
        tim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    }
}

static rt_err_t timer_start(rt_hwtimer_t *timer, rt_uint32_t t, rt_hwtimer_mode_t opmode)
{
    rt_err_t result = RT_EOK;
    TIM_HandleTypeDef *tim = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    tim = (TIM_HandleTypeDef *)timer->parent.user_data;

    /* set tim cnt */
    __HAL_TIM_SET_COUNTER(tim, 0);
    /* set tim arr */
    __HAL_TIM_SET_AUTORELOAD(tim, t - 1);

    if (opmode == HWTIMER_MODE_ONESHOT)
    {
        /* set timer to single mode */
        tim->Instance->CR1 |= TIM_OPMODE_SINGLE;
    }
    else
    {
        tim->Instance->CR1 &= (~TIM_OPMODE_SINGLE);
    }

    HAL_NVIC_SetPriority(TIM2_IRQn, 15, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);	
    /* start timer */
    if (HAL_TIM_Base_Start_IT(tim) != HAL_OK)
    {
        LOG_E("TIM start failed");
        result = -RT_ERROR;
    }
    else
    {
        LOG_I("TIM start success");
    }
    
    return result;
}

static void timer_stop(rt_hwtimer_t *timer)
{
    TIM_HandleTypeDef *tim = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    tim = (TIM_HandleTypeDef *)timer->parent.user_data;

    /* stop timer */
    HAL_TIM_Base_Stop_IT(tim);

    /* set tim cnt */
    __HAL_TIM_SET_COUNTER(tim, 0);
}

static rt_err_t timer_ctrl(rt_hwtimer_t *timer, rt_uint32_t cmd, void *arg)
{
    TIM_HandleTypeDef *tim = RT_NULL;
    rt_err_t result = RT_EOK;

    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(arg != RT_NULL);

    tim = (TIM_HandleTypeDef *)timer->parent.user_data;

    switch (cmd)
    {
        case HWTIMER_CTRL_FREQ_SET:
        {
            rt_uint32_t freq;
            rt_uint16_t val;

            freq = *((rt_uint32_t *)arg);
            val = SystemCoreClock / 2 / freq;
           
            __HAL_TIM_SET_PRESCALER(tim, val - 1);

            /* Update frequency value */
            tim->Instance->EGR |= TIM_EVENTSOURCE_UPDATE;
        }
        break;
        default:
        {
            result = -RT_ENOSYS;
        }
        break;
    }
    return result;
}

static rt_uint32_t timer_counter_get(rt_hwtimer_t *timer)
{
    TIM_HandleTypeDef *tim = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    tim = (TIM_HandleTypeDef *)timer->parent.user_data;

    return tim->Instance->CNT;
}

static const struct rt_hwtimer_ops ops = 
{
    .init = timer_init,
    .start = timer_start,
    .stop = timer_stop,
    .count_get = timer_counter_get,
    .control = timer_ctrl
};

#define TIM_DEV_INFO_CONFIG                     \
    {                                           \
        .maxfreq = 1000000,                     \
        .minfreq = 3000,                        \
        .maxcnt  = 0xFFFF,                      \
        .cntmode = HWTIMER_CNTMODE_UP,          \
    }

static const struct rt_hwtimer_info _info = TIM_DEV_INFO_CONFIG;

static int stm32_hwtimer_init(void)
{
    hwtimer.tim_handle.Instance = TIM2;
    hwtimer.tim_irqn = TIM2_IRQn;
    hwtimer.name = "tim2";
    hwtimer.time_device.ops = &ops;
    hwtimer.time_device.info = &_info;
    
    if(rt_device_hwtimer_register(&hwtimer.time_device, hwtimer.name, &hwtimer.tim_handle))
    {
        LOG_D("%s register success", hwtimer.name);
    }
    else
    {
        LOG_E("%s register success", hwtimer.name);

        return -RT_ERROR;
    }

    return RT_EOK;
    
}
INIT_BOARD_EXPORT(stm32_hwtimer_init);
