#pragma once
#include <limits.h>
#include <stdio.h>
#include <stdarg.h>

typedef __int32 data_type;
//typedef int data_type;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
//#define MINKEY 0UL
//#define MAXKEY 4294967295UL
#define MINKEY _I32_MIN
#define MAXKEY _I32_MAX
/* k·�鲢 */
#define k 64
#define gen_ptr_part 1600000
#define split_part gen_ptr_part
#define num k*split_part
	
