#include "Timer.h"

namespace Gumgine
{
	namespace Util
	{
		Timer::Timer()
		{}

		Timer::~Timer()
		{}

		bool Timer::Init()
		{
			// 주파수 변동폭
			QueryPerformanceFrequency( ( LARGE_INTEGER* ) &frequency );
			QueryPerformanceCounter( ( LARGE_INTEGER* ) &start );
			end = start;
			fps = 0;
			isStop = false;
			return true;
		}

		bool Timer::Frame()
		{
			if ( isStop )
			{
				deltaTime = 0.0f;
				return true;
			}
			QueryPerformanceCounter( ( LARGE_INTEGER* ) &end );
			deltaTime = ( end - start ) / ( float ) ( frequency );
			sumTime += deltaTime;
			if ( sumTime > 1.0f )
			{
				sumTime = 0.0f;
				fps = fpsCount;
				fpsCount = 0;
			}
			++fpsCount;
			start = end;
			return true;
		}

		bool Timer::Render()
		{
			return true;
		}

		bool Timer::Release()
		{
			return true;
		}
	}
}