// PcService.h : PcService Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CPcServiceApp:
// �йش����ʵ�֣������ PcService.cpp
//

class CPcServiceApp : public CWinApp
{
public:
	CPcServiceApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPcServiceApp theApp;
