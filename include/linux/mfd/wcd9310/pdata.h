/* Copyright (c) 2011, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __MFD_TABLA_PDATA_H__

#define __MFD_TABLA_PDATA_H__

#include <linux/slimbus/slimbus.h>

#define TABLA_LDOH_1P95_V 0x0
#define TABLA_LDOH_2P35_V 0x1
#define TABLA_LDOH_2P75_V 0x2
#define TABLA_LDOH_2P85_V 0x3

#define TABLA_CFILT1_SEL 0x0
#define TABLA_CFILT2_SEL 0x1
#define TABLA_CFILT3_SEL 0x2

#define MAX_AMIC_CHANNEL 7

struct tabla_amic {
	/*legacy mode, txfe_enable and txfe_buff take 7 input
	 * each bit represent the channel / TXFE number
	 * and numbered as below
	 * bit 0 = channel 1 / TXFE1_ENABLE / TXFE1_BUFF
	 * bit 1 = channel 2 / TXFE2_ENABLE / TXFE2_BUFF
	 * ...
	 * bit 7 = channel 7 / TXFE7_ENABLE / TXFE7_BUFF
	 */
	u8 legacy_mode:MAX_AMIC_CHANNEL;
	u8 txfe_enable:MAX_AMIC_CHANNEL;
	u8 txfe_buff:MAX_AMIC_CHANNEL;
	u8 use_pdata:MAX_AMIC_CHANNEL;
};

/* Each micbias can be assigned to one of three cfilters
 * Vbatt_min >= .15V + ldoh_v
 * ldoh_v >= .15v + cfiltx_mv
 * If ldoh_v = 1.95 160 mv < cfiltx_mv < 1800 mv
 * If ldoh_v = 2.35 200 mv < cfiltx_mv < 2200 mv
 * If ldoh_v = 2.75 240 mv < cfiltx_mv < 2600 mv
 * If ldoh_v = 2.85 250 mv < cfiltx_mv < 2700 mv
 */

struct tabla_micbias_setting {
	u8 ldoh_v;
	u32 cfilt1_mv; /* in mv */
	u32 cfilt2_mv; /* in mv */
	u32 cfilt3_mv; /* in mv */
	u8 bias1_cfilt_sel;
	u8 bias2_cfilt_sel;
	u8 bias3_cfilt_sel;
	u8 bias4_cfilt_sel;
};

struct tabla_pdata {
	int irq;
	int irq_base;
	int num_irqs;
	int reset_gpio;
	struct tabla_amic amic_settings;
	struct slim_device slimbus_slave_device;
	struct tabla_micbias_setting micbias;
};

#endif