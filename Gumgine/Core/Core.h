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
		
			//��� Ŭ������ �ݵ�� �Ʒ��� �Լ��� �����Ѵ�.
			virtual bool	Init() = 0;
			virtual bool	Frame() = 0;
			virtual bool	Render() = 0;
			virtual bool	Release() = 0;
		
			int				Run();

			virtual bool	SetWin( const std::wstring& titleName , unsigned int width = 640 , unsigned int height = 480 ) override;

		private:
			//���
			bool	CoreInit();
			bool	PreCoreInit();
			bool	PostCoreInit();
			//��ο�
			bool	CoreRender();
			virtual bool	PreCoreRender();
			bool	PostCoreRender();
			//���
			bool	CoreFrame();
			bool	PreCoreFrame();
			bool	PostCoreFrame();
			//����
			bool	CoreRelease();
			bool	PreCoreRelease();
			bool	PostCoreRelease();
		};
	}
}