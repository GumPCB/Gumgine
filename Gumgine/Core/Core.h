#pragma once
#include "D3D.h"

namespace Gumgine
{
	namespace Util
	{
		class Timer;
	}
	namespace Core
	{
		class Core : public Gumgine::Core::D3D
		{
		private:
			Gumgine::Util::Timer*	coreTimer = nullptr;
		//	GumSky		*m_pGumSky;
		public:
			Core();
			virtual ~Core();
		
			//모든 클래스는 반드시 아래의 함수를 정의한다.
			virtual bool	Init() = 0;
			virtual bool	Frame() = 0;
			virtual bool	Render() = 0;
			virtual bool	Release() = 0;
		
			int				Run();

			virtual bool	SetWin( const std::wstring& titleName , unsigned int width = 640 , unsigned int height = 480 ) override;

		private:
			//계산
			bool	CoreInit();
			bool	PreCoreInit();
			bool	PostCoreInit();
			//드로우
			bool	CoreRender();
			virtual bool	PreCoreRender();
			bool	PostCoreRender();
			//계산
			bool	CoreFrame();
			bool	PreCoreFrame();
			bool	PostCoreFrame();
			//해제
			bool	CoreRelease();
			bool	PreCoreRelease();
			bool	PostCoreRelease();
		};
	}
}