#pragma once
#include "D3D.h"

namespace Gumgine
{
	namespace Util
	{
		class FPSCounter;
	}
	namespace Core
	{
		class Core : public D3D , public IRenderable
		{
		private:
			Util::FPSCounter*	fpsCounter = nullptr;
		//	GumSky		*m_pGumSky;
		public:
			Core();
			virtual ~Core();
		
			//모든 클래스는 반드시 아래의 함수를 정의한다.
			virtual bool	Init() override = 0;
			virtual bool	Frame() override = 0;
			virtual bool	Render() override = 0;
			virtual bool	Release() override = 0;
		
			int				Run();

			virtual bool	SetWin( const std::wstring& _titleName , unsigned int _width = 640 , unsigned int _height = 480 ) override;

		private:
			//초기화
			bool	CoreInit();
			bool	PreCoreInit();
			bool	PostCoreInit();
			//계산
			bool	CoreFrame();
			bool	PreCoreFrame();
			bool	PostCoreFrame();
			//드로우
			bool	CoreRender();
			bool	PreCoreRender();
			bool	PostCoreRender();
			//해제
			bool	CoreRelease();
			bool	PreCoreRelease();
			bool	PostCoreRelease();
		};
	}
}