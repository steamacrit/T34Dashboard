#pragma once

#include "Log.h"

typedef uint32_t WID;

#ifdef T34_ENABLE_ASSERTS
    #define T34_ASSERT(x, ...) { if(!(x)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } } 
#else
    #define T34_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)