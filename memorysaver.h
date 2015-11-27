#ifndef _MEMORYSAVER_
#define _MEMORYSAVER_

#include <stdio.h>

/****************************************************************/
/* define a structure for sensor register initialization values */
/****************************************************************/

struct sensor_reg {
	uint16_t reg;
	uint16_t val;
};

//Uncomment the following definition when you use them
//#define OV7660_CAM
//#define OV7725_CAM
//#define OV7670_CAM
//#define OV7675_CAM
#define OV2640_CAM
//#define OV3640_CAM
#define OV5642_CAM
//#define MT9D111_CAM
//#define MT9M112_CAM
//#define MT9V111_CAM	
//#define OV5640_CAM
//#define MT9M001_CAM	
//#define MT9T112_CAM
#define MT9D112_CAM

#if defined OV7660_CAM	
	#include "_registers/ov7660_regs.h"
#endif

#if defined OV7725_CAM	
	#include "_registers/ov7725_regs.h"
#endif

#if defined OV7670_CAM	
	#include "_registers/ov7670_regs.h"
#endif

#if defined OV7675_CAM
	#include "_registers/ov7675_regs.h"
#endif

#if defined OV5642_CAM	
	#include "_registers/ov5642_regs.h"
#endif

#if defined OV3640_CAM	
	#include "_registers/ov3640_regs.h"
#endif

#if defined OV2640_CAM
	#include "_registers/ov2640_regs.h"
#endif

#if defined MT9D111_CAM	
	#include "_registers/mt9d111_regs.h"
#endif

#if defined MT9M112_CAM	
	#include "_registers/mt9m112_regs.h"
#endif

#if defined MT9V111_CAM	
	#include "_registers/mt9v111_regs.h"
#endif

#if defined OV5640_CAM	
	#include "_registers/ov5640_regs.h"
#endif

#if defined MT9M001_CAM	
	#include "_registers/mt9m001_regs.h"
#endif

#if defined MT9T112_CAM	
	#include "_registers/mt9t112_regs.h"
#endif

#if defined MT9D112_CAM	
	#include "_registers/mt9d112_regs.h"
#endif

#endif	//_MEMORYSAVER_
