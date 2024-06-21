#pragma once

namespace Gumgine
{
	namespace Util
	{
		class FPSCounter : public Core::IRenderable
		{
		private:
			std::chrono::steady_clock::time_point point;
			double	second = 0.0;
			int		fps = 0;
			int		count = 0;

		public:
			FPSCounter() noexcept {};
			virtual ~FPSCounter() {};

			virtual bool Init() noexcept override
			{
				point = std::chrono::steady_clock::now();
				second = 0.0;
				fps = 0;
				count = 0;
				return true;
			}

			virtual bool Frame() noexcept override
			{
				++count;

				const auto old = point;
				point = std::chrono::steady_clock::now();
				second += std::chrono::duration< double >(point - old).count();

				if (second > 1.0)
				{
					second -= 1.0;
					fps = count;
					count = 0;
				}
				return true;
			}

			virtual bool Render() noexcept override { return true; }
			virtual bool Release() noexcept override { return true; }

			int GetFPS() const noexcept { return fps; }
		};
	}
}