#include "Global.h"

namespace Gumgine
{
	namespace Singleton
	{
		void GlobalVariables::SetWindow( Gumgine::Core::Window* window )
		{
			windowList[ std::this_thread::get_id() ] = window;
		}

		Gumgine::Core::Window* GlobalVariables::GetWindow()
		{
			auto&& result = windowList.find( std::this_thread::get_id() );
			if ( result != windowList.end() )
			{
				return result->second;
			}
			return nullptr;
		}
	}
}