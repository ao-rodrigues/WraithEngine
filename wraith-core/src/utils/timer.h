#pragma once

#include <Windows.h>

namespace Wraith {
	class Timer
	{
	private:
		LARGE_INTEGER m_Start;
		double m_Freq;

	public:
		Timer()
		{
			LARGE_INTEGER freq;
			QueryPerformanceFrequency(&freq);
			m_Freq = 1.0 / freq.QuadPart;

			reset();
		}

		void reset()
		{
			QueryPerformanceCounter(&m_Start);
		}

		float elapsed()
		{
			LARGE_INTEGER curr;
			QueryPerformanceCounter(&curr);
			unsigned __int64 cycles = curr.QuadPart - m_Start.QuadPart;

			return (float)(cycles * m_Freq);
		}

	};
}