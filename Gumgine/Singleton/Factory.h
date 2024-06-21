#pragma once

namespace Gumgine
{
	namespace Singleton
	{
		template < class T >
		class Factory
		{
		public:
			Factory() {};
			virtual ~Factory() {};

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
		class SharedFactory
		{
		public:
			SharedFactory() {};
			virtual ~SharedFactory() {};

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