#pragma once

#include "ContainerDefines.h"

namespace Wraith
{
#if !WR_USE_WRAITH_VECTOR

#include <vector>
	template<typename T>
	using Vector = std::vector<T>;

#endif
}
