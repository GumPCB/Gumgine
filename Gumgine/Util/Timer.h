#pragma once

namespace Gumgine
{
	namespace Util
	{
		class Timer
		{
		public:
			void Init() noexcept
			{
				start = std::chrono::steady_clock::now();
				end = start;
				isStop = false;
			}

			void Frame() noexcept
			{
				end = std::chrono::steady_clock::now();
				if (isStop)
				{
					start = end;
					return;
				}
				deltaTime = std::chrono::duration< double >(end - start).count();
				totalTime += deltaTime;
				start = end;
			}

			void Stop( bool _isStop = true ) noexcept
			{
				isStop = _isStop;
				if (isStop)
				{
					deltaTime = 0.0;
				}
			}

			void ResetDeltaTime() noexcept { deltaTime = 0.0; }
			void ResetTotalTime() noexcept { totalTime = 0.0; }
			double GetDeltaTime() const noexcept { return deltaTime; }
			double GetTotalTime() const noexcept { return totalTime; }

		private:
			std::chrono::steady_clock::time_point start;
			std::chrono::steady_clock::time_point end;

			double	deltaTime = 0.0;
			double	totalTime = 0.0;

			bool	isStop = false;
		};


		class ProgressPercentage
		{
		public:
			void Init(unsigned __int64 _max, unsigned __int64 printInterval = 10Ui64) noexcept
			{
				if (_max == 0)
					_max = 1;

				if (printInterval == 0)
					printInterval = 1;

				max = _max;
				current = 0;
				lastPrint = 0;
				intervalPrint = printInterval;
				timer.Init();
			}
			void Add(unsigned __int64 add) noexcept { current += add; }
			unsigned __int64 GetPercentage() const noexcept { return (current * 100Ui64) / max; }
			void Print()
			{
				const unsigned __int64 currentPercentage = GetPercentage();
				if (currentPercentage < (lastPrint + intervalPrint))
					return;

				lastPrint = currentPercentage;
				timer.Frame();
				std::wcout << lastPrint << L"% (" << current << L"/" << max << L") " << timer.GetDeltaTime() << L" second, Total : " << timer.GetTotalTime() << L" second" << std::endl;
			}

		private:
			std::atomic<unsigned __int64> max = 1;
			std::atomic<unsigned __int64> current = 0;
			std::atomic<unsigned __int64> lastPrint = 0;
			std::atomic<unsigned __int64> intervalPrint = 1;
			Timer timer;
		};
	}
}