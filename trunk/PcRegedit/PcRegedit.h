// PcRegedit.h : PcRegedit Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CPcRegeditApp:
// �йش����ʵ�֣������ PcRegedit.cpp
//

class CPcRegeditApp : public CWinApp
{
public:
	CPcRegeditApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPcRegeditApp theApp;
