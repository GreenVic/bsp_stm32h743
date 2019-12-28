
 /*
 * File      : drv_gpio.c
 * 
 * This file is auto generate from cubemx xml for STM32H743XIHx 
 *
 * Change Logs:
 * Date           Author            Notes
 * 2019-12-28     ZYH            auto generated
 */

#include <rthw.h>
#include <rtdevice.h>
#include <board.h>
#include <drv_gpio.h>

#ifdef RT_USING_PIN
#define __STM32_PIN(index, gpio, gpio_index) (gpio | gpio_index)
#define __STM32_PIN_DEFAULT 0

#define A   (1U << 8)
#define B   (2U << 8)
#define C   (3U << 8)
#define D   (4U << 8)
#define E   (5U << 8)
#define F   (6U << 8)
#define G   (7U << 8)
#define H   (8U << 8)
#define I   (9U << 8)
#define J   (10U << 8)
#define K   (11U << 8)

static GPIO_TypeDef * get_st_gpio(rt_uint16_t gpio_pin)
{
    switch(gpio_pin & 0xFF00)
    {
    case A:
        #ifdef GPIOA
        return GPIOA;
        #endif
    case B:
        #ifdef GPIOB
        return GPIOB;
        #endif
    case C:
        #ifdef GPIOC
        return GPIOC;
        #endif
    case D:
        #ifdef GPIOD
        return GPIOD;
        #endif
    case E:
        #ifdef GPIOE
        return GPIOE;
        #endif
    case F:
        #ifdef GPIOF
        return GPIOF;
        #endif
    case G:
        #ifdef GPIOG
        return GPIOG;
        #endif
    case H:
        #ifdef GPIOH
        return GPIOH;
        #endif
    case I:
        #ifdef GPIOI
        return GPIOI;
        #endif
    case J:
        #ifdef GPIOJ
        return GPIOJ;
        #endif
    case K:
        #ifdef GPIOK
        return GPIOK;
        #endif
    default:
        return RT_NULL;
    }
}

#define get_st_pin(gpio_pin) (0x01 << (gpio_pin&0xFF))

static void drv_clock_enable(rt_uint16_t gpio_pin)
{
    switch(gpio_pin & 0xFF00)
    {
    case A:
        #ifdef __HAL_RCC_GPIOA_CLK_ENABLE
        __HAL_RCC_GPIOA_CLK_ENABLE();
        #endif
        break;
    case B:
        #ifdef __HAL_RCC_GPIOB_CLK_ENABLE
        __HAL_RCC_GPIOB_CLK_ENABLE();
        #endif
        break;
    case C:
        #ifdef __HAL_RCC_GPIOC_CLK_ENABLE
        __HAL_RCC_GPIOC_CLK_ENABLE();
        #endif
        break;
    case D:
        #ifdef __HAL_RCC_GPIOD_CLK_ENABLE
        __HAL_RCC_GPIOD_CLK_ENABLE();
        #endif
        break;
    case E:
        #ifdef __HAL_RCC_GPIOE_CLK_ENABLE
        __HAL_RCC_GPIOE_CLK_ENABLE();
        #endif
        break;
    case F:
        #ifdef __HAL_RCC_GPIOF_CLK_ENABLE
        __HAL_RCC_GPIOF_CLK_ENABLE();
        #endif
        break;
    case G:
        #ifdef __HAL_RCC_GPIOG_CLK_ENABLE
        __HAL_RCC_GPIOG_CLK_ENABLE();
        #endif
        break;
    case H:
        #ifdef __HAL_RCC_GPIOH_CLK_ENABLE
        __HAL_RCC_GPIOH_CLK_ENABLE();
        #endif
        break;
    case I:
        #ifdef __HAL_RCC_GPIOI_CLK_ENABLE
        __HAL_RCC_GPIOI_CLK_ENABLE();
        #endif
        break;
    case J:
        #ifdef __HAL_RCC_GPIOJ_CLK_ENABLE
        __HAL_RCC_GPIOJ_CLK_ENABLE();
        #endif
        break;
    case K:
        #ifdef __HAL_RCC_GPIOK_CLK_ENABLE
        __HAL_RCC_GPIOK_CLK_ENABLE();
        #endif
        break;
    default:
        break;
    }
}

/* STM32 GPIO driver */
static const rt_uint16_t pins[] =
{
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(A2, I, 6),
    __STM32_PIN(A3, I, 5),
    __STM32_PIN(A4, I, 4),
    __STM32_PIN(A5, B, 5),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(A8, K, 5),
    __STM32_PIN(A9, G, 10),
    __STM32_PIN(A10, G, 9),
    __STM32_PIN(A11, D, 5),
    __STM32_PIN(A12, D, 4),
    __STM32_PIN(A13, C, 10),
    __STM32_PIN(A14, A, 15),
    __STM32_PIN(A15, I, 1),
    __STM32_PIN(A16, I, 0),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(B3, I, 7),
    __STM32_PIN(B4, E, 1),
    __STM32_PIN(B5, B, 6),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(B7, B, 4),
    __STM32_PIN(B8, K, 4),
    __STM32_PIN(B9, G, 11),
    __STM32_PIN(B10, J, 15),
    __STM32_PIN(B11, D, 6),
    __STM32_PIN(B12, D, 3),
    __STM32_PIN(B13, C, 11),
    __STM32_PIN(B14, A, 14),
    __STM32_PIN(B15, I, 2),
    __STM32_PIN(B16, H, 15),
    __STM32_PIN(B17, H, 14),
    __STM32_PIN(C1, C, 15),
    __STM32_PIN(C2, C, 14),
    __STM32_PIN(C3, E, 2),
    __STM32_PIN(C4, E, 0),
    __STM32_PIN(C5, B, 7),
    __STM32_PIN(C6, B, 3),
    __STM32_PIN(C7, K, 6),
    __STM32_PIN(C8, K, 3),
    __STM32_PIN(C9, G, 12),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(C11, D, 7),
    __STM32_PIN(C12, C, 12),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(C14, I, 3),
    __STM32_PIN(C15, A, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(D1, E, 5),
    __STM32_PIN(D2, E, 4),
    __STM32_PIN(D3, E, 3),
    __STM32_PIN(D4, B, 9),
    __STM32_PIN(D5, B, 8),
    __STM32_PIN(D6, G, 15),
    __STM32_PIN(D7, K, 7),
    __STM32_PIN(D8, G, 14),
    __STM32_PIN(D9, G, 13),
    __STM32_PIN(D10, J, 14),
    __STM32_PIN(D11, J, 12),
    __STM32_PIN(D12, D, 2),
    __STM32_PIN(D13, D, 0),
    __STM32_PIN(D14, A, 10),
    __STM32_PIN(D15, A, 9),
    __STM32_PIN(D16, H, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(E2, I, 9),
    __STM32_PIN(E3, C, 13),
    __STM32_PIN(E4, I, 8),
    __STM32_PIN(E5, E, 6),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(E10, J, 13),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(E12, D, 1),
    __STM32_PIN(E13, C, 8),
    __STM32_PIN(E14, C, 9),
    __STM32_PIN(E15, A, 8),
    __STM32_PIN(E16, A, 12),
    __STM32_PIN(E17, A, 11),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(F3, I, 10),
    __STM32_PIN(F4, I, 11),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(F13, C, 7),
    __STM32_PIN(F14, C, 6),
    __STM32_PIN(F15, G, 8),
    __STM32_PIN(F16, G, 7),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(G1, F, 2),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(G3, F, 1),
    __STM32_PIN(G4, F, 0),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(G14, G, 5),
    __STM32_PIN(G15, G, 6),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(H1, I, 12),
    __STM32_PIN(H2, I, 13),
    __STM32_PIN(H3, I, 14),
    __STM32_PIN(H4, F, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(H14, G, 4),
    __STM32_PIN(H15, G, 3),
    __STM32_PIN(H16, G, 2),
    __STM32_PIN(H17, K, 2),
    __STM32_PIN(J1, H, 1),
    __STM32_PIN(J2, H, 0),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(J4, F, 5),
    __STM32_PIN(J5, F, 4),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(J14, K, 0),
    __STM32_PIN(J15, K, 1),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(K2, F, 6),
    __STM32_PIN(K3, F, 7),
    __STM32_PIN(K4, F, 8),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(K14, J, 11),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(L2, C, 0),
    __STM32_PIN(L3, F, 10),
    __STM32_PIN(L4, F, 9),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(L14, J, 10),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(M2, C, 1),
    __STM32_PIN(M3, C, 2),
    __STM32_PIN(M4, C, 3),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(M14, J, 9),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(N2, H, 2),
    __STM32_PIN(N3, A, 2),
    __STM32_PIN(N4, A, 1),
    __STM32_PIN(N5, A, 0),
    __STM32_PIN(N6, J, 0),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(N9, E, 10),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(N13, J, 8),
    __STM32_PIN(N14, J, 7),
    __STM32_PIN(N15, J, 6),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(P2, H, 3),
    __STM32_PIN(P3, H, 4),
    __STM32_PIN(P4, H, 5),
    __STM32_PIN(P5, I, 15),
    __STM32_PIN(P6, J, 1),
    __STM32_PIN(P7, F, 13),
    __STM32_PIN(P8, F, 14),
    __STM32_PIN(P9, E, 9),
    __STM32_PIN(P10, E, 11),
    __STM32_PIN(P11, B, 10),
    __STM32_PIN(P12, B, 11),
    __STM32_PIN(P13, H, 10),
    __STM32_PIN(P14, H, 11),
    __STM32_PIN(P15, D, 15),
    __STM32_PIN(P16, D, 14),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(R1, C, 2),
    __STM32_PIN(R2, C, 3),
    __STM32_PIN(R3, A, 6),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(R5, A, 7),
    __STM32_PIN(R6, B, 2),
    __STM32_PIN(R7, F, 12),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(R9, F, 15),
    __STM32_PIN(R10, E, 12),
    __STM32_PIN(R11, E, 15),
    __STM32_PIN(R12, J, 5),
    __STM32_PIN(R13, H, 9),
    __STM32_PIN(R14, H, 12),
    __STM32_PIN(R15, D, 11),
    __STM32_PIN(R16, D, 12),
    __STM32_PIN(R17, D, 13),
    __STM32_PIN(T1, A, 0),
    __STM32_PIN(T2, A, 1),
    __STM32_PIN(T3, A, 5),
    __STM32_PIN(T4, C, 4),
    __STM32_PIN(T5, B, 1),
    __STM32_PIN(T6, J, 2),
    __STM32_PIN(T7, F, 11),
    __STM32_PIN(T8, G, 0),
    __STM32_PIN(T9, E, 8),
    __STM32_PIN(T10, E, 13),
    __STM32_PIN(T11, H, 6),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(T13, H, 8),
    __STM32_PIN(T14, B, 12),
    __STM32_PIN(T15, B, 15),
    __STM32_PIN(T16, D, 10),
    __STM32_PIN(T17, D, 9),
    __STM32_PIN_DEFAULT,
    __STM32_PIN(U2, A, 3),
    __STM32_PIN(U3, A, 4),
    __STM32_PIN(U4, C, 5),
    __STM32_PIN(U5, B, 0),
    __STM32_PIN(U6, J, 3),
    __STM32_PIN(U7, J, 4),
    __STM32_PIN(U8, G, 1),
    __STM32_PIN(U9, E, 7),
    __STM32_PIN(U10, E, 14),
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(U13, H, 7),
    __STM32_PIN(U14, B, 13),
    __STM32_PIN(U15, B, 14),
    __STM32_PIN(U16, D, 8),
    __STM32_PIN_DEFAULT,

};

struct pin_irq_map
{
    rt_uint16_t irq_stat;
    const rt_uint16_t pinbit;
    const IRQn_Type irqno;
};

static struct pin_irq_map pin_irq_map[] =
{
    {0, GPIO_PIN_0, EXTI0_IRQn},
    {0, GPIO_PIN_1, EXTI1_IRQn},
    {0, GPIO_PIN_2, EXTI2_IRQn},
    {0, GPIO_PIN_3, EXTI3_IRQn},
    {0, GPIO_PIN_4, EXTI4_IRQn},
    {0, GPIO_PIN_5, EXTI9_5_IRQn},
    {0, GPIO_PIN_6, EXTI9_5_IRQn},
    {0, GPIO_PIN_7, EXTI9_5_IRQn},
    {0, GPIO_PIN_8, EXTI9_5_IRQn},
    {0, GPIO_PIN_9, EXTI9_5_IRQn},
    {0, GPIO_PIN_10, EXTI15_10_IRQn},
    {0, GPIO_PIN_11, EXTI15_10_IRQn},
    {0, GPIO_PIN_12, EXTI15_10_IRQn},
    {0, GPIO_PIN_13, EXTI15_10_IRQn},
    {0, GPIO_PIN_14, EXTI15_10_IRQn},
    {0, GPIO_PIN_15, EXTI15_10_IRQn},
};

struct rt_pin_irq_hdr pin_irq_hdr_tab[] =
{
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
};

#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])
static rt_uint16_t get_pin(uint8_t pin)
{
    rt_uint16_t gpio_pin = __STM32_PIN_DEFAULT;
    if (pin < ITEM_NUM(pins))
    {
        gpio_pin = pins[pin];
    }
    return gpio_pin;
};

static void stm32_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    rt_uint16_t gpio_pin;
    gpio_pin = get_pin(pin);
    if (get_st_gpio(gpio_pin) == RT_NULL)
    {
        return;
    }
    HAL_GPIO_WritePin(get_st_gpio(gpio_pin), get_st_pin(gpio_pin), (GPIO_PinState)value);
}

static int stm32_pin_read(rt_device_t dev, rt_base_t pin)
{
    rt_uint16_t gpio_pin;
    gpio_pin = get_pin(pin);
    if (get_st_gpio(gpio_pin) == RT_NULL)
    {
        return PIN_LOW;
    }
    return HAL_GPIO_ReadPin(get_st_gpio(gpio_pin), get_st_pin(gpio_pin));
}

static void stm32_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    rt_uint16_t gpio_pin;
    GPIO_InitTypeDef GPIO_InitStruct;
    gpio_pin = get_pin(pin);
    if (get_st_gpio(gpio_pin) == RT_NULL)
    {
        return;
    }
    /* GPIO Periph clock enable */
    drv_clock_enable(gpio_pin);
    /* Configure GPIO_InitStructure */
    GPIO_InitStruct.Pin = get_st_pin(gpio_pin);
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    }
    HAL_GPIO_Init(get_st_gpio(gpio_pin), &GPIO_InitStruct);
}

static rt_err_t stm32_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                              rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    rt_uint16_t gpio_pin;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    GPIO_InitTypeDef GPIO_InitStruct;
    gpio_pin = get_pin(pin);
    if (get_st_gpio(gpio_pin) == RT_NULL)
    {
        return RT_ENOSYS;
    }
    irqindex = gpio_pin&0xFF;
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
    {
        return RT_ENOSYS;
    }
    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[irqindex].pin == pin &&
            pin_irq_hdr_tab[irqindex].hdr == hdr &&
            pin_irq_hdr_tab[irqindex].mode == mode &&
            pin_irq_hdr_tab[irqindex].args == args)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    if (pin_irq_hdr_tab[irqindex].pin != -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EBUSY;
    }
    pin_irq_hdr_tab[irqindex].pin = pin;
    pin_irq_hdr_tab[irqindex].hdr = hdr;
    pin_irq_hdr_tab[irqindex].mode = mode;
    pin_irq_hdr_tab[irqindex].args = args;
    rt_hw_interrupt_enable(level);
    
    /* GPIO Periph clock enable */
    drv_clock_enable(gpio_pin);
    /* Configure GPIO_InitStructure */
    GPIO_InitStruct.Pin = get_st_pin(gpio_pin);
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    switch (pin_irq_hdr_tab[irqindex].mode)
    {
    case PIN_IRQ_MODE_RISING:
        GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
        break;
    case PIN_IRQ_MODE_FALLING:
        GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
        break;
    case PIN_IRQ_MODE_RISING_FALLING:
        GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
        break;
    }
    HAL_GPIO_Init(get_st_gpio(gpio_pin), &GPIO_InitStruct);
    
    return RT_EOK;
}

static rt_err_t stm32_pin_detach_irq(struct rt_device *device, rt_int32_t pin)
{
    rt_uint16_t gpio_pin;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    gpio_pin = get_pin(pin);
    if (get_st_gpio(gpio_pin) == RT_NULL)
    {
        return RT_ENOSYS;
    }
    irqindex = gpio_pin&0xFF;
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
    {
        return RT_ENOSYS;
    }
    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[irqindex].pin == -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    pin_irq_hdr_tab[irqindex].pin = -1;
    pin_irq_hdr_tab[irqindex].hdr = RT_NULL;
    pin_irq_hdr_tab[irqindex].mode = 0;
    pin_irq_hdr_tab[irqindex].args = RT_NULL;
    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

static rt_err_t stm32_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                              rt_uint32_t enabled)
{
    rt_uint16_t gpio_pin;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    
    gpio_pin = get_pin(pin);
    if (get_st_gpio(gpio_pin) == RT_NULL)
    {
        return RT_ENOSYS;
    }
    irqindex = gpio_pin&0xFF;
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
    {
        return RT_ENOSYS;
    }
    if (pin_irq_hdr_tab[irqindex].pin == -1)
    {
        return RT_ENOSYS;
    }
    if (enabled == PIN_IRQ_ENABLE)
    {
        level = rt_hw_interrupt_disable();
        
        HAL_NVIC_ClearPendingIRQ(pin_irq_map[irqindex].irqno);
        __HAL_GPIO_EXTI_CLEAR_IT(irqindex);
        __HAL_GPIO_EXTI_CLEAR_FLAG(irqindex);
        HAL_NVIC_SetPriority(pin_irq_map[irqindex].irqno, 5, 0);
        HAL_NVIC_EnableIRQ(pin_irq_map[irqindex].irqno);
        pin_irq_map[irqindex].irq_stat = 1;
        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        pin_irq_map[irqindex].irq_stat = 0;
        if(irqindex <= 9 && irqindex >= 5)
        {
            if(pin_irq_map[5].irq_stat == 0 && pin_irq_map[6].irq_stat == 0 &&
               pin_irq_map[7].irq_stat == 0 && pin_irq_map[8].irq_stat == 0 && 
               pin_irq_map[9].irq_stat == 0)
            {
                HAL_NVIC_DisableIRQ(pin_irq_map[irqindex].irqno);
                HAL_NVIC_ClearPendingIRQ(pin_irq_map[irqindex].irqno);
            }
        }
        else if(irqindex >= 10)
        {
            if(pin_irq_map[10].irq_stat == 0 && pin_irq_map[11].irq_stat == 0 &&
               pin_irq_map[12].irq_stat == 0 && pin_irq_map[13].irq_stat == 0 && 
               pin_irq_map[14].irq_stat == 0 && pin_irq_map[15].irq_stat == 0)
            {
                HAL_NVIC_DisableIRQ(pin_irq_map[irqindex].irqno);
                HAL_NVIC_ClearPendingIRQ(pin_irq_map[irqindex].irqno);
            }
        }
        else
        {
            HAL_NVIC_DisableIRQ(pin_irq_map[irqindex].irqno);
            HAL_NVIC_ClearPendingIRQ(pin_irq_map[irqindex].irqno);
        }
       
    }
    else
    {
        return RT_ENOSYS;
    }
    return RT_EOK;
}

const static struct rt_pin_ops _stm32_pin_ops =
{
    stm32_pin_mode,
    stm32_pin_write,
    stm32_pin_read,
    stm32_pin_attach_irq,
    stm32_pin_detach_irq,
    stm32_pin_irq_enable,
};

int rt_hw_pin_init(void)
{
    int result;
    result = rt_device_pin_register("pin", &_stm32_pin_ops, RT_NULL);
    return result;
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

static void pin_irq_hdr(uint16_t GPIO_Pin)
{
    int irqno = 0;
    for(irqno = 0; irqno < 16; irqno ++)
    {
        if((0x01 << irqno) == GPIO_Pin)
        {
            break;
        }
    }
    if(irqno == 16)return;

    if (pin_irq_map[irqno].irq_stat && pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    pin_irq_hdr(GPIO_Pin);
}

void EXTI0_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
    rt_interrupt_leave();
}

void EXTI1_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
    rt_interrupt_leave();
}

void EXTI2_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
    rt_interrupt_leave();
}

void EXTI3_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
    rt_interrupt_leave();
}

void EXTI4_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
    rt_interrupt_leave();
}

void EXTI9_5_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
    rt_interrupt_leave();
}

void EXTI15_10_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
    rt_interrupt_leave();
}
#endif
