//
// Assert.h
// WraithSandbox
//
// Created by Andre Rodrigues on 08/12/2022.
//

#pragma once

#include "Wraith/Logger.h"

#ifdef WR_CONFIG_DEBUG

#define WR_ASSERT(x)                                \
    if (!(x)) {                                     \
        WR_LOG_FATAL("Assert {} failed!", #x);      \
        abort();                                    \
    }                                               \

#define WR_ASSERT_MSG(x, msg)                                                           \
    if (!(x)) {                                                                         \
        WR_LOG_FATAL("[{}:{}] Assert {} failed: {}", __FILE__, __LINE__, #x, msg);      \
        abort();                                                                        \
    }                                                                                   \

#else

#define WR_ASSERT(x)
#define WR_ASSERT_MSG(x, msg)

#endif