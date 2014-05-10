#pragma once
#include "GeStd.h"

namespace Gumgine
{
	class GeWindow
	{
	public:
		GeWindow();
		virtual ~GeWindow();

	public:
		bool	SetWin(HINSTANCE hInst, TCHAR* pTitleName);
		virtual LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		void	SetWindowRect(DWORD _dwWidth, DWORD _dwHeight);

	public:
		HWND	m_hWnd;
	};

}