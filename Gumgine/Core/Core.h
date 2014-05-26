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
		class Core : public Gumgine::Core::D3D , public Gumgine::GumCore
		{
		private:
			Gumgine::Util::Timer*	coreTimer = nullptr;
		//	GumSky		*m_pGumSky;
		public:
			Core();
			virtual ~Core();
		
			//모든 클래스는 반드시 아래의 함수를 정의한다.
			virtual bool	Init() override;
			virtual bool	Frame() override;
			virtual bool	Render() override;
			virtual bool	Release() override;
		
			int		Run();

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