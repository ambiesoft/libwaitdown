#include "StdAfx.h"

#include "FormWD.h"

namespace libwaitdown {
	struct EWPROCST
	{
		std::vector<HWND> vHwnds;
		DWORD dwPID;
	};
	BOOL CALLBACK ecwproc(HWND hwnd, LPARAM lParam)
	{
		int& count = *((int*)lParam);
		++count;
		return TRUE;
	}

	int GetChildWindowCount(HWND hwnd)
	{
		int count = 0;
		EnumChildWindows(hwnd, ecwproc, (LPARAM)&count);
		return count;
	}
	BOOL CALLBACK ewproc(HWND hwnd,  LPARAM lParam)
	{
		if(!IsWindowVisible(hwnd))
			return TRUE;

		EWPROCST& ewst = *((EWPROCST*)lParam);

		DWORD dwPIDwin = 0;
		GetWindowThreadProcessId(hwnd, &dwPIDwin);
		
		if(ewst.dwPID==dwPIDwin)
		{
			TCHAR szT[256];
			szT[0]=0;
			if(0!=GetClassName(hwnd, szT, sizeof(szT)/sizeof(szT[0])))
			{
				_tcslwr_s(szT);
				// if(lstrcmpi("Internet Explorer_Hidden", szT)!=0)
				if (_tcspbrk(szT, _T("hidden")) == NULL)
				{
					// if(lstrcmp("#32770",szT)==0)
					int ccount = GetChildWindowCount(hwnd);
					if(ccount >= 3)  // assuming hidden windows does not have child windows.
					{
						ewst.vHwnds.push_back(hwnd);
					}
				}
			}
		}
		return TRUE;
	}

	void FormWD::WaitDownloadWindow()
	{
		//TCHAR szThis[MAX_PATH];
		//GetModuleFileName(NULL, szThis, sizeof(szThis));
		//strlwr(szThis);

		EWPROCST ewst;
		ewst.dwPID = GetCurrentProcessId();

		if(!EnumWindows(ewproc, (LPARAM)&ewst))
		{
			return;
		}

		if(ewst.vHwnds.size()==0)
		{
			return;
		}

		FormWD dlgWD;
		dlgWD.vWins_ = &ewst.vHwnds;

		// dlgWD.ShowDialog();
		Application::Run(%dlgWD);

	}
}