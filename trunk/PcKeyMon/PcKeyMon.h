// PcKeyMon.h : PcKeyMon Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CPcKeyMonApp:
// �йش����ʵ�֣������ PcKeyMon.cpp
//

class CPcKeyMonApp : public CWinApp
{
public:
	CPcKeyMonApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPcKeyMonApp theApp;
