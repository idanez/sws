/******************************************************************************
/ Prompt.cpp
/
/ Copyright (c) 2009 Tim Payne (SWS)
/ http://www.standingwaterstudios.com/reaper
/
/ Permission is hereby granted, free of charge, to any person obtaining a copy
/ of this software and associated documentation files (the "Software"), to deal
/ in the Software without restriction, including without limitation the rights to
/ use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
/ of the Software, and to permit persons to whom the Software is furnished to
/ do so, subject to the following conditions:
/ 
/ The above copyright notice and this permission notice shall be included in all
/ copies or substantial portions of the Software.
/ 
/ THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
/ EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
/ OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
/ NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
/ HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
/ WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
/ FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
/ OTHER DEALINGS IN THE SOFTWARE.
/
******************************************************************************/

#include "stdafx.h"
#include "Prompt.h"

#define PROMPTWND_KEY "PromptWindowPos"

static const char* g_cTitle;
static char* g_cString;
static int g_iMax;
static bool g_bOK = false;

INT_PTR WINAPI doPromptDialog(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			SetWindowText(hwndDlg, g_cTitle);
			HWND hEdit = GetDlgItem(hwndDlg, IDC_EDIT);
			SetWindowText(hEdit, g_cString);
			RestoreWindowPos(hwndDlg, PROMPTWND_KEY);
			return 0;
		}
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDOK:
					GetDlgItemText(hwndDlg, IDC_EDIT, g_cString, g_iMax);
					g_bOK = true;
				// Fall through to cancel to save/end
				case IDCANCEL:
					SaveWindowPos(hwndDlg, PROMPTWND_KEY);
					EndDialog(hwndDlg, 0);
					break;
			}
			break;
	}
	return 0;
}

bool PromptUserForString(const char* cTitle, char* cString, int iMaxChars)
{
	g_cTitle = cTitle;
	g_cString = cString;
	g_iMax = iMaxChars;
	g_bOK = false;
	DialogBox(g_hInst,MAKEINTRESOURCE(IDD_PROMPT), g_hwndParent, doPromptDialog);
	return g_bOK;
}