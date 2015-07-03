#pragma once
#include "../GeStd.h"

namespace Gumgine
{
	namespace Singleton
	{
		template< class T > class BasicSingleton;

		template < class T >
		class Factory : public BasicSingleton< Gumgine::Singleton::Factory< T > >
		{
		private:
			friend class BasicSingleton< Gumgine::Singleton::Factory< T > >;

		private:
			Factory() {};
			virtual ~Factory() {};

		public:
			//< 力前 殿废
			void Register( const std::wstring& productName, std::function< T* () > Func )
			{
				assert( Products.find( productName ) == Products.end() ); //"Already registered product."
				Products[ productName ] = Func;
			}
			//< 力前 林巩
			virtual T* Create( const std::wstring& productName )
			{
				if ( Products.find( productName ) == Products.end() )
				{
					return nullptr;
				}
				return Products[ productName ]();
			}
		private:
			std::map < std::wstring , std::function< T* () > > Products;
		};

		template < typename Parents, typename Child >
		Parents* CreateFunc()
		{
			return ( Parents* ) new Child;
		}
	}
}