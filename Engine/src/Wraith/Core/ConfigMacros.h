#pragma once

#ifdef WR_CONFIG_DEBUG
#define WR_CONFIG_DEBUG 1
#else
#define WR_CONFIG_DEBUG 0
#endif

#ifdef WR_CONFIG_DEVELOPMENT
#define WR_CONFIG_DEVELOPMENT 1
#else
#define WR_CONFIG_DEVELOPMENT 0
#endif

#ifdef WR_CONFIG_SHIPPING
#define WR_CONFIG_SHIPPING 1
#else
#define WR_CONFIG_SHIPPING 0
#endif