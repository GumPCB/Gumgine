#pragma once
#include "../Singleton/BasicSingleton.h"

namespace Gumgine
{
	namespace Util
	{
		class Random : public Singleton::BasicSingleton< Random >
		{
		public:
			template < typename T >
			T GetIntRandom(T min, T max)
			{
				std::uniform_int_distribution<T> dist(min, max);
				return dist(randomdevice);
			}
			template < typename T >
			T GetRealRandom(T min, T max)
			{
				std::uniform_real_distribution<T> dist(min, max);
				return dist(randomdevice);
			}

		private:
			std::random_device randomdevice;
		};
	}
}