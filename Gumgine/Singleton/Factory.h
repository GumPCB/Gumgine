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
			void RegisterType( const std::wstring& typeName, std::function< T* () > createFunc )
			{
				assert( Products.find( typeName ) == Products.end() ); //"Already registered product."
				Products[ typeName ] = createFunc;
			}
			//< 力前 林巩
			virtual T* Create( const std::wstring& typeName )
			{
				if ( Products.find( typeName ) == Products.end() )
				{
					return nullptr;
				}
				return Products[ typeName ]();
			}
		private:
			std::map< std::wstring , std::function< T* () > > Products;
		};



		template < class T >
		class SharedFactory : public BasicSingleton< Gumgine::Singleton::SharedFactory< T > >
		{
		private:
			friend class BasicSingleton< Gumgine::Singleton::SharedFactory< T > >;

		private:
			SharedFactory() {};
			virtual ~SharedFactory() {};

		public:
			//< 力前 殿废
			void RegisterType( const std::wstring& typeName , std::function< std::shared_ptr< T >( ) > createFunc )
			{
				assert( Products.find( typeName ) == Products.end() ); //"Already registered product."
				Products[ typeName ] = createFunc;
			}
			//< 力前 林巩
			virtual std::shared_ptr< T > Create( const std::wstring& typeName )
			{
				if( Products.find( typeName ) == Products.end() )
				{
					return nullptr;
				}
				return Products[ typeName ]();
			}
		private:
			std::map< std::wstring , std::function< std::shared_ptr< T >( ) > > Products;
		};

		template < typename Parents >
		Parents* CreatePtrFunc()
		{
			return new Parents;
		}

		template < typename Parents , typename Child >
		Parents* CreatePtrFunc()
		{
			return ( Parents* ) new Child;
		}

		template < typename Parents >
		std::shared_ptr< Parents > CreateSharedPtrFunc()
		{
			return std::make_shared< Parents >();
		}
	}
}