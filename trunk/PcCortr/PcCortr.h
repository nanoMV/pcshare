// PcCortr.h : main header file for the PCCORTR DLL
//

#if !defined(AFX_PCCORTR_H__7EB1461A_1CE5_46AE_BD95_4CD85D2F60F8__INCLUDED_)
#define AFX_PCCORTR_H__7EB1461A_1CE5_46AE_BD95_4CD85D2F60F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPcCortrApp
// See PcCortr.cpp for the implementation of this class
//

#define CONN_MAIN				3000				//��������
#define CONN_FILE_UP			3004				//�ϴ��ļ�
#define CONN_FILE_DL			3005				//�����ļ�

#define CONN_FILE_MANA_SEND		4001				//�ļ������͹ܵ�
#define CONN_FILE_MANA_RECV		4002				//�ļ�������չܵ�
#define CONN_FILE_FRAM_SEND		4003				//��Ļ��ط��͹ܵ�
#define CONN_FILE_FRAM_RECV		4004				//��Ļ��ؽ��չܵ�
#define CONN_FILE_TLNT_SEND		4005				//�����ն˷��͹ܵ�
#define CONN_FILE_TLNT_RECV		4006				//�����ն˽��չܵ�
#define CONN_FILE_REGD_SEND		4007				//ע���༭���͹ܵ�
#define CONN_FILE_REGD_RECV		4008				//ע���༭���չܵ�
#define CONN_FILE_PROC_SEND		4009				//���̹����͹ܵ�
#define CONN_FILE_PROC_RECV		4010				//���̹�����չܵ�
#define CONN_FILE_SERV_SEND		4011				//��������͹ܵ�
#define CONN_FILE_SERV_RECV		4012				//���������չܵ�
#define CONN_FILE_KEYM_SEND		4013				//���̼�ط��͹ܵ�
#define CONN_FILE_KEYM_RECV		4014				//���̼�ؽ��չܵ�
#define CONN_FILE_MULT_SEND		4015				//��Ƶ��ط��͹ܵ�
#define CONN_FILE_MULT_RECV		4016				//��Ƶ��ؽ��չܵ�

class CPcCortrApp : public CWinApp
{
public:
	CPcCortrApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPcCortrApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CPcCortrApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PCCORTR_H__7EB1461A_1CE5_46AE_BD95_4CD85D2F60F8__INCLUDED_)
