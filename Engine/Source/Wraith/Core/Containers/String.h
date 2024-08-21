#pragma once

#define WR_USE_WRAITH_STRING 0

namespace Wraith
{
#if !WR_USE_WRAITH_STRING

#include <string>
	using String = std::string;

#endif
}
