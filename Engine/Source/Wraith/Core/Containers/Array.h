#pragma once

#include "ContainerDefines.h"

namespace Wraith
{
#if !WR_USE_WRAITH_ARRAY

#include <array>
	template<typename T>
	using Array = std::array<T>;

#endif
}
