#pragma once
#include "../GeStd.h"

namespace Gumgine
{
	namespace Util
	{
		class Timer : public IRenderable
		{
		protected:
			__int64 start = 0;
			__int64 end = 0;
			
			double	secondsPerfrequency = 0.0;
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
			void SetTotalTime( const double _sumTime ) { totalTime = _sumTime; }
		};
	}
}