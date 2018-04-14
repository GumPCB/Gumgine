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
		
			//��� Ŭ������ �ݵ�� �Ʒ��� �Լ��� �����Ѵ�.
			virtual bool	Init() override = 0;
			virtual bool	Frame() override = 0;
			virtual bool	Render() override = 0;
			virtual bool	Release() override = 0;
		
			int				Run();

			virtual bool	SetWin( const std::wstring& _titleName , unsigned int _width = 640 , unsigned int _height = 480 ) override;

		private:
			//�ʱ�ȭ
			bool	CoreInit();
			bool	PreCoreInit();
			bool	PostCoreInit();
			//���
			bool	CoreFrame();
			bool	PreCoreFrame();
			bool	PostCoreFrame();
			//��ο�
			bool	CoreRender();
			bool	PreCoreRender();
			bool	PostCoreRender();
			//����
			bool	CoreRelease();
			bool	PreCoreRelease();
			bool	PostCoreRelease();
		};
	}
}