#pragma once
#include <cassert>
#include <iostream>
#include "config.h"

//#define NDEBUG

#ifndef NDEBUG
#define assert_ex(condition, statement) \
	do{ \
		if (!(condition)) {statement; assert(condition);} \
	}while(false)
#else
#define assert_ex(condition, statement) ((void)0)
#endif