#pragma once
#include "../GeStd.h"

namespace Gumgine
{
	namespace Util
	{
		class Timer : public GumCore
		{
		private:
			__int64 start = 0;
			__int64 end = 0;
			__int64 frequency = 0;

			float	deltaTime = 0.0f;
			float	sumTime = 0.0f;
			int		fps = 0;
			int		fpsCount = 0;

			bool	isStop = false;

		public:
			Timer();
			virtual ~Timer();

			virtual bool Init() override;
			virtual bool Frame() override;
			virtual bool Render() override;
			virtual bool Release() override;

			void Stop( bool _isStop = true ) { isStop = _isStop; }

			const float GetDeltaTime() const { return deltaTime; }
			const int GetFPS() const { return fps; }
		};
	}
}