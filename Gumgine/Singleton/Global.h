#pragma once
#include "../pch.h"

namespace Gumgine
{
	namespace Core
	{
		class Window;
	}
	namespace Singleton
	{
		template< class T > class BasicSingleton;

		//< 쓰레드 번호를 기준으로 포인터를 하나씩 가지고 있는 싱글턴
		//< thread_local 을 쓰면 되는데 필요한가?
		template < class T > class ThreadSingleton : public BasicSingleton< ThreadSingleton< T > >
		{
		private:
			friend class BasicSingleton< ThreadSingleton< T > >;
			std::map< std::thread::id , T* > ptrList;
			std::shared_timed_mutex mutex;
		public:
			void SetPtr( T* ptr )
			{
				std::lock_guard< std::shared_timed_mutex > lock( mutex );
				if ( ptrList.find( std::this_thread::get_id() ) != ptrList.end() )
				{
					MessageBox( nullptr , L"already have a this pointer." , nullptr , 0 );
				}
				ptrList[ std::this_thread::get_id() ] = ptr;
			};
			T* GetPtr()
			{
				std::shared_lock< std::shared_timed_mutex > lock( mutex );
				auto&& result = ptrList.find( std::this_thread::get_id() );
				if ( result != ptrList.end() )
				{
					return result->second;
				}
				return nullptr;
			};
			void Clear()
			{
				std::lock_guard< std::shared_timed_mutex > lock( mutex );
				ptrList[ std::this_thread::get_id() ] = nullptr;
				ptrList.erase( std::this_thread::get_id() );
			}
		private:
			ThreadSingleton() {};
			virtual ~ThreadSingleton() { ptrList.clear(); };
		};
	}
}