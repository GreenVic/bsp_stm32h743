/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */
 
#include "board.h" 

int main(void)
{      
	while(1)
	{
		rt_thread_delay(1000);
		// rt_kprintf("RT-Thread\n");
	}
    return 0; 
}
