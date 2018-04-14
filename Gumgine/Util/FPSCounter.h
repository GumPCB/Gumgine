#pragma once
#include "../GeStd.h"

namespace Gumgine
{
	namespace Util
	{
		class Timer;
		class FPSCounter : public IRenderable
		{
		private:
			Timer* timer = nullptr;
			int		fps = 0;
			int		count = 0;

		public:
			FPSCounter();
			virtual ~FPSCounter();

			virtual bool Init() override;
			virtual bool Frame() override;
			virtual bool Render() override;
			virtual bool Release() override;

			int GetFPS() const { return fps; }
		};
	}
}