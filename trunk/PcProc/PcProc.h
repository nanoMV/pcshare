// PcProc.h : PcProc Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CPcProcApp:
// �йش����ʵ�֣������ PcProc.cpp
//

class CPcProcApp : public CWinApp
{
public:
	CPcProcApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPcProcApp theApp;
