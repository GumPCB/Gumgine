#pragma once
#include "../GeStd.h"

namespace Gumgine
{
	namespace Util
	{
		class Timer : public Gumgine::IRenderable
		{
		protected:
			__int64 start = 0;
			__int64 end = 0;
			__int64 frequency = 0;

			float	deltaTime = 0.0f;
			float	totalTime = 0.0f;

			bool	isStop = false;

		public:
			Timer();
			virtual ~Timer();

			virtual bool Init() override;
			virtual bool Frame() override;
			virtual bool Render() override;
			virtual bool Release() override;

			void Stop( bool _isStop = true );

			void ResetDeltaTime() { deltaTime = 0.0f; }
			float GetDeltaTime() const { return deltaTime; }
			float GetTotalTime() const { return totalTime; }
			void SetTotalTime( const float _sumTime ) { totalTime = _sumTime; }
		};
	}
}