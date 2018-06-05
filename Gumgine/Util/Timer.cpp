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
			start = std::chrono::steady_clock::now();
			end = start;
			isStop = false;
			return true;
		}

		bool Timer::Frame()
		{
			end = std::chrono::steady_clock::now();
			if ( isStop )
			{
				start = end;
				return true;
			}
			deltaTime = std::chrono::duration< double >( end - start ).count();
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
				deltaTime = 0.0;
			}
			return;
		}
	}
}