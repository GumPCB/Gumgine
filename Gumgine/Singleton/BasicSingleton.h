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

		template< class manager , class managed > class ManagerSingleton
		{
		public:
			static manager& GetInstance()
			{
				static manager theSingleInstance;
				return theSingleInstance;
			}
		};
	}
}