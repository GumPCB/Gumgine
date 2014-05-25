#pragma once
#include "../GeStd.h"

namespace Gumgine
{
	namespace Core
	{
		class Window;
	}
	namespace Singleton
	{
		class GlobalVariables : public Gumgine::GeSingleton< Gumgine::Singleton::GlobalVariables >
		{
		private:
			friend class Gumgine::GeSingleton< Gumgine::Singleton::GlobalVariables >;
			std::map< std::thread::id , Gumgine::Core::Window* > windowList;
		public:
			void SetWindow( Gumgine::Core::Window* window );
			Gumgine::Core::Window* GetWindow();
		private:
			GlobalVariables() {};
			~GlobalVariables() {};
		};
	}
}