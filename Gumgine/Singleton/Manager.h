#pragma once

namespace Gumgine
{
	namespace Singleton
	{
		template< class T > class BasicSingleton;
		template< class T > class SharedFactory;

		// TODO : ���丮�� Create �Լ� �̸��� �ٸ� ������ �ٲ���
		template< class managed >
		class Manager : public BasicSingleton< Manager< managed > > , Core::IRenderable
		{
		private:
			friend class BasicSingleton< Manager< managed > >;

		public:
			Manager() {};
			virtual ~Manager();

			void RegisterType( const std::wstring& typeName , std::function< std::shared_ptr< managed >() > createFunc );

			//������ �߰�
			unsigned int				Add( const std::wstring& name );
			unsigned int				Add( const std::wstring& name, const std::wstring& typeName );
			//�߰�, �ߺ��Ǹ� �̹� �ִ°��� �ε����� ����
			unsigned int				Create( const std::wstring& name );
			unsigned int				Create( const std::wstring& name, const std::wstring& typeName );

			std::shared_ptr< managed >	GetPtr( const std::wstring& name );
			std::shared_ptr< managed >	GetPtr( unsigned int index );
			unsigned int				GetIndex( const std::wstring& name );
			unsigned int				GetIndex( std::shared_ptr< managed > child );

			unsigned int				GetLastIndex() const { return curIndex; }

			virtual bool				Init() override;	// �ʱ�ȭ
			virtual bool				Frame() override;	// �׸��� ���� ����
			virtual bool				Render() override;	// ȭ�鿡 �׸���
			virtual bool				Release() override;	// �ڿ� ����

		private:
			SharedFactory< managed >						factory;
			std::map< int , std::shared_ptr< managed > >	managedObjects;
			unsigned int									curIndex = 0;
		};

		template< class managed >
		Manager< managed >::~Manager()
		{
			Release();
			managedObjects.clear();
			curIndex = 0;
		}

		template< class managed >
		void Manager< managed >::RegisterType( const std::wstring& typeName , std::function< std::shared_ptr< managed >() > createFunc )
		{
			factory.RegisterType( typeName , createFunc );
		}

		template< class managed >
		unsigned int Manager< managed >::Add( const std::wstring& name )
		{
			auto obj = std::make_shared< managed >();
			obj->Init();
			obj->SetName( name );
			managedObjects.insert( make_pair( ++curIndex , obj ) );

			return curIndex;
		}

		template< class managed >
		unsigned int Manager< managed >::Add( const std::wstring& name , const std::wstring& typeName )
		{
			auto obj = factory.Create( typeName );
			obj->Init();
			obj->SetName( name );
			managedObjects.insert( make_pair( ++curIndex , obj ) );

			return curIndex;
		}

		template< class managed >
		unsigned int Manager< managed >::Create( const std::wstring& name )
		{
			auto index = GetIndex( name );
			if( index != 0 )
			{
				return index;
			}
			return Add( name );
		}

		template< class managed >
		unsigned int Manager< managed >::Create( const std::wstring& name , const std::wstring& typeName )
		{
			auto index = GetIndex( name );
			if( index != 0 )
			{
				return index;
			}
			return Add( name, typeName );
		}

		template< class managed >
		std::shared_ptr< managed > Manager< managed >::GetPtr( const std::wstring& name )
		{
			for( auto iter = managedObjects.begin() ; iter != managedObjects.end() ; ++iter )
			{
				if( iter->second->GetName() == name )
				{
					return iter->second;
				}
			}
			return nullptr;
		}

		template< class managed >
		std::shared_ptr< managed > Manager< managed >::GetPtr( unsigned int index )
		{
			auto iter = managedObjects.find( index );
			if( iter != managedObjects.end() )
			{
				return iter->second;
			}			
			return nullptr;
		}

		template< class managed >
		unsigned int Manager< managed >::GetIndex( const std::wstring& name )
		{
			for( auto iter = managedObjects.cbegin() ; iter != managedObjects.cend() ; ++iter )
			{
				if( iter->second->GetName() == name )
				{
					return iter->first;
				}
			}
			return 0;
		}

		template< class managed >
		unsigned int Manager< managed >::GetIndex( std::shared_ptr< managed > child )
		{
			for( auto iter = managedObjects.cbegin() ; iter != managedObjects.cend() ; ++iter )
			{
				if( iter->second == child )
				{
					return iter->first;
				}
			}
			return 0;
		}

		template< class managed >
		bool Manager< managed >::Init()
		{
			for( auto iter = managedObjects.begin() ; iter != managedObjects.end() ; ++iter )
			{
				iter->second->Init();
			}
			return true;
		}

		template< class managed >
		bool Manager< managed >::Frame()
		{
			for( auto iter = managedObjects.begin() ; iter != managedObjects.end() ; ++iter )
			{
				iter->second->Frame();
			}
			return true;
		}

		template< class managed >
		bool Manager< managed >::Render()
		{
			for( auto iter = managedObjects.begin() ; iter != managedObjects.end() ; ++iter )
			{
				iter->second->Render();
			}
			return true;
		}

		template< class managed >
		bool Manager< managed >::Release()
		{
			for( auto iter = managedObjects.begin() ; iter != managedObjects.end() ; ++iter )
			{
				iter->second->Release();
			}
			return true;
		}
	}
}