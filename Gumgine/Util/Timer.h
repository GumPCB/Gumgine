#pragma once
#include "../GeStd.h"

namespace Gumgine
{
	namespace Util
	{
		class Timer : public IRenderable
		{
		protected:
			std::chrono::steady_clock::time_point start;
			std::chrono::steady_clock::time_point end;
			
			double	deltaTime = 0.0;
			double	totalTime = 0.0;

			bool	isStop = false;

		public:
			Timer();
			virtual ~Timer();

			virtual bool Init() override;
			virtual bool Frame() override;
			virtual bool Render() override;
			virtual bool Release() override;

			void Stop( bool _isStop = true );

			void ResetDeltaTime() { deltaTime = 0.0; }
			double GetDeltaTime() const { return deltaTime; }
			double GetTotalTime() const { return totalTime; }
		};
	}
}