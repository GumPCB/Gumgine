#pragma once
#include "../GeStd.h"

namespace Gumgine
{
	namespace Util
	{
		class FPSCounter : public IRenderable
		{
		private:
			std::chrono::steady_clock::time_point point;
			double	second = 0.0;
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