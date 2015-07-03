#pragma once
#include "../GeStd.h"



namespace Gumgine
{
	namespace Util
	{
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
			inline std::string ToString( float input )
			{
				return std::to_string( input );
			}

			template <>
			inline std::string ToString( double input )
			{
				return std::to_string( input );
			}

			template <>
			inline std::string ToString( long double input )
			{
				return std::to_string( input );
			}

			template <>
			inline std::string ToString( unsigned __int64 input )
			{
				return std::to_string( input );
			}

			template <>
			inline std::string ToString( __int64 input )
			{
				return std::to_string( input );
			}

			template <>
			inline std::string ToString( unsigned long input )
			{
				return std::to_string( input );
			}

			template <>
			inline std::string ToString( long input )
			{
				return std::to_string( input );
			}

			template <>
			inline std::string ToString( unsigned int input )
			{
				return std::to_string( input );
			}

			template <>
			inline std::string ToString( int input )
			{
				return std::to_string( input );
			}

			//////////////////////////////////////////////////////// ToString //

			// ToWString ////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////// ToWString //
		}
	}
}