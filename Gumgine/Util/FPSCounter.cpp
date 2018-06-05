#include "FPSCounter.h"

namespace Gumgine
{
	namespace Util
	{
		FPSCounter::FPSCounter()
		{}

		FPSCounter::~FPSCounter()
		{}

		bool FPSCounter::Init()
		{
			point = std::chrono::steady_clock::now();
			second = 0.0;
			fps = 0;
			count = 0;
			return true;
		}

		bool FPSCounter::Frame()
		{
			++count;

			auto old = point;
			point = std::chrono::steady_clock::now();
			second += std::chrono::duration< double >( point - old ).count();
			
			if ( second > 1.0 )
			{
				second -= 1.0;
				fps = count;
				count = 0;
			}
			return true;
		}

		bool FPSCounter::Render()
		{
			return true;
		}

		bool FPSCounter::Release()
		{
			return true;
		}
	}
}