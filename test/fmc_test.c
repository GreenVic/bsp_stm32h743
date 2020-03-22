#include "rtthread.h"
#include "rtdevice.h"

#include "drv_fmc.h"

static void fmc_test(void)
{
    rt_device_t device;
    struct hc574_pin_status pin = {0};

    device = rt_device_find("fmc");

    if(device == RT_NULL)
    {
        rt_kprintf("device fmc not found\n");
        return;
    }

    pin.pin_num = LED1;
    while(1)
    {
        pin.pin_status = 1;
        rt_device_control(device, HC574_SET_PIN, &pin);
        rt_thread_delay(1000);
        pin.pin_status = 0;
        rt_device_control(device, HC574_SET_PIN, &pin);
        rt_thread_delay(1000);        
    }

}
MSH_CMD_EXPORT(fmc_test, fmc_test);
