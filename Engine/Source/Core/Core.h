#pragma once

#include "Logger.h"
#include "Utils.h"

#ifdef WR_CONFIG_DEBUG

// TODO break at the line when the assert happens
#define WR_ASSERT(x, msg) if (!(x)) { WR_LOG_FATAL("[{}:{}] Assert {} failed: {}", __FILE__, __LINE__, #x, msg) }

#else

#define WR_ASSERT(x, msg)

#endif

