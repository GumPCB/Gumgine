#include <iostream>
#include <fstream>
#include <vector>
#include "DeviceSample.h"
#include "../Gumgine/Util/Converter.h"
#include "../Gumgine/Util/Timer.h"
#include "oldToString.h"

void ConverterSample()
{
	// ToString
	auto intToStringConverterSample = Converter::ToString( int( -123123 ) );
	std::cout << intToStringConverterSample << std::endl;

	intToStringConverterSample = Converter::ToString( char( 10 ) );
	std::cout << intToStringConverterSample << std::endl;

	intToStringConverterSample = Converter::ToString( wchar_t( 65432 ) );
	std::cout << intToStringConverterSample << std::endl;

	intToStringConverterSample = Converter::ToString( intToStringConverterSample );
	std::cout << intToStringConverterSample << std::endl;

	intToStringConverterSample = Converter::ToString( 0 );
	std::cout << intToStringConverterSample << std::endl;

	intToStringConverterSample = Converter::ToString( float( 555.55f ) );
	std::cout << intToStringConverterSample << std::endl;

	intToStringConverterSample = Converter::ToString( -40404040404040LL );
	std::cout << intToStringConverterSample << std::endl;

	intToStringConverterSample = Converter::ToString( 40404040404040ULL );
	std::cout << intToStringConverterSample << std::endl;


	// ToWString
	auto intToWStringConverterSample = Converter::ToWString( int( -123123 ) );
	std::wcout << intToWStringConverterSample << std::endl;

	intToWStringConverterSample = Converter::ToWString( char( 10 ) );
	std::wcout << intToWStringConverterSample << std::endl;

	intToWStringConverterSample = Converter::ToWString( wchar_t( 65432 ) );
	std::wcout << intToWStringConverterSample << std::endl;

	intToWStringConverterSample = Converter::ToWString( intToWStringConverterSample );
	std::wcout << intToWStringConverterSample << std::endl;

	intToWStringConverterSample = Converter::ToWString( 0 );
	std::wcout << intToWStringConverterSample << std::endl;

	//intToWStringConverterSample = Converter::ToWString( float( 555.55f ) );
	//std::wcout << intToWStringConverterSample << std::endl;

	intToWStringConverterSample = Converter::ToWString( -40404040404040LL );
	std::wcout << intToWStringConverterSample << std::endl;

	intToWStringConverterSample = Converter::ToWString( 40404040404040ULL );
	std::wcout << intToWStringConverterSample << std::endl;
}

void GumgineConverterTest( __int64 maxNum )
{
	auto str = Converter::ToString( __int64( -123123123132123LL ) );

	for ( __int64 i = maxNum * -1LL; i < maxNum; ++i )
	{
		str = Converter::ToString( i );
	}
}

void StdConverterTest( __int64 maxNum )
{
	auto str = std::to_string( __int64( -123123123132123LL ) );

	for ( __int64 i = maxNum * -1LL; i < maxNum; ++i )
	{
		str = std::to_string( i );
	}
}

std::string StdTostringTest( __int64 MAX , __int64 FOR_MAX )
{
	Gumgine::Util::Timer timer;
	timer.Init();

	timer.Frame();
	for ( __int64 i = 0LL; i < FOR_MAX; ++i )
	{
		StdConverterTest( MAX );
	}
	timer.Frame();

	double time1 = timer.GetDeltaTime();

	return "std result = count : " + std::to_string( FOR_MAX ) + ", Total seconds : " + std::to_string( time1 ) + ", Average seconds : " + std::to_string( time1 / static_cast< double >( FOR_MAX ) ) + ", range : -" + std::to_string( MAX ) + " ~ " + std::to_string( MAX );
}

std::string GumTostringTest( __int64 MAX , __int64 FOR_MAX )
{
	Gumgine::Util::Timer timer;
	timer.Init();

	timer.Frame();
	for ( __int64 i = 0LL; i < FOR_MAX; ++i )
	{
		GumgineConverterTest( MAX );
	}
	timer.Frame();

	double time1 = timer.GetDeltaTime();

	return "Gum result = count : " + std::to_string( FOR_MAX ) + ", Total seconds : " + std::to_string( time1 ) + ", Average seconds : " + std::to_string( time1 / static_cast< double >( FOR_MAX ) ) + ", range : -" + std::to_string( MAX ) + " ~ " + std::to_string( MAX );
}


int WINAPI wWinMain( HINSTANCE /*hInst*/ , HINSTANCE /*hPrevInstance*/ , LPWSTR /*lpCmdLine*/ , int /*nShowCmd*/ )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); //검출 소스
	//_CrtSetBreakAlloc( 319 );

	//ConverterSample();

	std::vector< std::string > stdResult;
	std::vector< std::string > gumResult;

	__int64 MAX = 1000000LL;
	__int64 MAX_COUNT = 10LL;

	for ( __int64 i = 9LL; i <= MAX; i = i * 10LL + 9LL )
	{
		stdResult.push_back( StdTostringTest( i , MAX_COUNT ) );
		gumResult.push_back( GumTostringTest( i , MAX_COUNT ) );
	}

	// SAVE
	{
		std::fstream stream;
		stream.open( "ToStringTestResult.txt" , std::ios_base::out );

		stream << "ToString Test" << std::endl;

		for ( auto & str : stdResult )
		{
			stream << str << std::endl;
		}

		stream << std::endl;

		for ( auto & str : gumResult )
		{
			stream << str << std::endl;
		}

		stream.close();
	}
	//system( "pause" );

	


	//const int maxThreadNum = 1;
	//std::vector< std::thread > threadPool;
	//for ( int i = 1; i <= maxThreadNum; ++i )
	//{
	//	threadPool.push_back( std::thread( [ = ]()
	//	{
	//		std::wstring threadName = L"T" + std::to_wstring( i );
	//		std::wcout << threadName << L", pid = " << std::this_thread::get_id() << std::endl;
	//		DeviceSample aaa;
	//		aaa.SetWin( threadName , 800 , 600 );
	//		aaa.Run();
	//	} ) );
	//}

	//for ( auto &thread : threadPool )
	//{
	//	thread.join();
	//}
	//threadPool.clear();

	return 0;
}