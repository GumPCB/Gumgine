#include "FPSCounter.h"
#include "Timer.h"

namespace Gumgine
{
	namespace Util
	{
		FPSCounter::FPSCounter()
		{
			SAFE_NEW( timer, Timer );
		}

		FPSCounter::~FPSCounter()
		{
			SAFE_DEL( timer );
		}

		bool FPSCounter::Init()
		{
			timer->Init();
			fps = 0;
			count = 0;
			return true;
		}

		bool FPSCounter::Frame()
		{
			timer->Frame();
			++count;
			if ( timer->GetTotalTime() > 1.0f )
			{
				timer->SetTotalTime( timer->GetTotalTime() - 1.0f );
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