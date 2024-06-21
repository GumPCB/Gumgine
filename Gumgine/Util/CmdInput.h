#pragma once

namespace Gumgine
{
	namespace Util
	{
		class CmdInput
		{
		public:
			static inline int Number(int min, int max)
			{
				std::wcout << L"( " << min << L" ~ " << max << L" ) = ";
				int result = max + 1;
				std::wstring inputLine;
				while (result < min || result > max)
				{
					std::wcin >> inputLine;

					result = 0;
					int temp = 0;
					for (const wchar_t& ch : inputLine)
					{
						temp = CharToInt(ch);
						if (temp == -1)
							continue;
						result = (result * 10) + temp;
					}
				}
				return result;
			}

		private:
			static inline int CharToInt(wchar_t ch) noexcept
			{
				switch (ch)
				{
				case L'0': return 0;
				case L'1': return 1;
				case L'2': return 2;
				case L'3': return 3;
				case L'4': return 4;
				case L'5': return 5;
				case L'6': return 6;
				case L'7': return 7;
				case L'8': return 8;
				case L'9': return 9;
				default:
					break;
				}
				return -1;
			}
		};
	}
}