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
		
			//��� Ŭ������ �ݵ�� �Ʒ��� �Լ��� �����Ѵ�.
			virtual bool	Init() override;
			virtual bool	Frame() override;
			virtual bool	Render() override;
			virtual bool	Release() override;
		
			int		Run();

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