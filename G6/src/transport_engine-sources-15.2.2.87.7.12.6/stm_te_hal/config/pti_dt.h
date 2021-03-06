/************************************************************************
Copyright (C) 2013 STMicroelectronics. All Rights Reserved.

This file is part of the Transport Engine Library.

The Transport Engine is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.

Transport Engine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with Transport Engine; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
USA.

The Transport Engine Library may alternatively be licensed under a
proprietary license from ST.

************************************************************************/
/**
   @file   pti_dt.h
   @brief  Declares pti driver device tree functions and constants
 */
#ifndef _PTI_DT_H
#define _PTI_DT_H

#if defined(CONFIG_OF)
#include <linux/of.h>
#endif

extern struct of_device_id stpti_tp_match[];
extern struct of_device_id stpti_stfe_match[];
extern struct of_device_id stpti_tango_lite_match[];
extern struct of_device_id stpti_all_match[];

void stptiDriver_dt_dump(void);

int stptiDriver_dt_check(void);

int stpti_dt_get_tp_pdata(struct platform_device *pdev);
int stpti_dt_put_tp_pdata(struct platform_device *pdev);

int stpti_dt_get_stfe_pdata(struct platform_device *pdev);
int stpti_dt_put_stfe_pdata(struct platform_device *pdev);
#endif
