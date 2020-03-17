#include "rtthread.h"
#include "rtdevice.h"

#define HWTIMER_DEV_NAME   "tim2"       /* 定时器名称 */
rt_device_t hw_dev;                     /* 定时器设备句柄 */
rt_uint32_t freq = 10000;               /* 计数频率 */
rt_hwtimerval_t timeout_s;              /* 定时器超时值 */
rt_hwtimer_mode_t mode;                 /* 定时器模式 */

/* 定时器超时回调函数 */
static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
{
    rt_kprintf("this is hwtimer timeout callback fucntion!\n");
    rt_kprintf("tick is :%d !\n", rt_tick_get());

    return 0;
}

static int hwtimer_test(int argc, char *argv[])
{
    /* 查找定时器设备 */
    hw_dev = rt_device_find(HWTIMER_DEV_NAME);
    /* 以读写方式打开设备 */
    rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    /* 设置超时回调函数 */
    rt_device_set_rx_indicate(hw_dev, timeout_cb);

    rt_device_control(hw_dev, HWTIMER_CTRL_FREQ_SET, &freq);

    mode = HWTIMER_MODE_PERIOD;
    rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, &mode);

    /* 设置定时器超时值为5s并启动定时器 */
    timeout_s.sec = 5;      /* 秒 */
    timeout_s.usec = 0;     /* 微秒 */
    rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s));
}
MSH_CMD_EXPORT(hwtimer_test, hwtimer_test);
