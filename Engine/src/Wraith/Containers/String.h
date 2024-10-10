#pragma once

#include "ContainerDefines.h"

namespace Wraith
{
#if !WR_USE_WRAITH_STRING

#include <string>
	using String = std::string;

#endif
}
