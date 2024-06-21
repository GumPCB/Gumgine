#pragma once

namespace
{
	inline char IntToChar( int num )
	{
		switch ( num )
		{
			case 0:	return '0';
			case 1:	return '1';
			case 2:	return '2';
			case 3:	return '3';
			case 4:	return '4';
			case 5:	return '5';
			case 6:	return '6';
			case 7:	return '7';
			case 8:	return '8';
			case 9:	return '9';
			default:
			{
				//assert( true ); // num is not 0 to 9
			}
			break;
		}
		return '0';
	}

	inline wchar_t IntToWChar( int num )
	{
		switch ( num )
		{
			case 0:	return L'0';
			case 1:	return L'1';
			case 2:	return L'2';
			case 3:	return L'3';
			case 4:	return L'4';
			case 5:	return L'5';
			case 6:	return L'6';
			case 7:	return L'7';
			case 8:	return L'8';
			case 9:	return L'9';
			default:
			{
				//assert( true ); // num is not 0 to 9
			}
			break;
		}
		return L'0';
	}
}

namespace Converter
{
	// ToString ////////////////////////////////////////////////////////
	template < typename T >
	inline std::string ToString( T input );

	template <>
	inline std::string ToString( std::string input )
	{
		return input;
	}

	template <>
	inline std::string ToString( unsigned __int64 input )
	{
		std::string result;
		do
		{
			result = IntToChar( input % 10ULL ) + result;
			input /= 10ULL;
		} while ( input != 0ULL );
		return result;
	}

	template <>
	inline std::string ToString( __int64 input )
	{
		bool isMinus = ( input < 0LL );
		if ( isMinus )
		{
			input *= -1LL;
		}
		return ( isMinus ? "-" : "" ) + ToString< unsigned __int64 >( input );
	}

	//template <>
	//inline std::string ToString( double input )
	//{
	//	bool isMinus = ( input < 0. );
	//	if ( isMinus )
	//	{
	//		input *= -1.;
	//	}
	//	return ( isMinus ? "-" : "" ) + ToString< unsigned __int64 >( input );
	//}

	template < typename T >
	inline std::string ToString( T input )
	{
		return ToString< __int64 >( static_cast<__int64>( input ) );
	}
	//////////////////////////////////////////////////////// ToString //

	// ToWString ////////////////////////////////////////////////////////
	template < typename T >
	inline std::wstring ToWString( T input );

	template <>
	inline std::wstring ToWString( std::wstring input )
	{
		return input;
	}

	template <>
	inline std::wstring ToWString( unsigned __int64 input )
	{
		std::wstring result;
		do
		{
			result = IntToWChar( input % 10ULL ) + result;
			input /= 10ULL;
		} while ( input != 0ULL );
		return result;
	}

	template <>
	inline std::wstring ToWString( __int64 input )
	{
		std::wstring result;
		bool isMinus = ( input < 0LL );
		if ( isMinus )
		{
			input *= -1LL;
		}
		return ( isMinus ? L"-" : L"" ) + ToWString< unsigned __int64 >( input );
	}

	template < typename T >
	inline std::wstring ToWString( T input )
	{
		return ToWString< __int64 >( input );
	}
	//////////////////////////////////////////////////////// ToWString //
}