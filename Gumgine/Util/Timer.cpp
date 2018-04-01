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
			isStop = false;
			return true;
		}

		bool Timer::Frame()
		{
			QueryPerformanceCounter( ( LARGE_INTEGER* ) &end );
			if ( isStop )
			{
				start = end;
				return true;
			}
			deltaTime = ( end - start ) / ( float ) ( frequency );
			totalTime += deltaTime;
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

		void Timer::Stop( bool _isStop /*= true*/ )
		{
			isStop = _isStop;
			if ( isStop )
			{
				deltaTime = 0.0f;
			}
			return;
		}
	}
}