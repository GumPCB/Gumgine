#pragma once

namespace Gumgine
{
	namespace Singleton
	{
		template< class T > class BasicSingleton
		{
		public:
			static T& GetInstance()
			{
				static T theSingleInstance;
				return theSingleInstance;
			}
		};
	}
}