// MyFrameView.cpp : implementation file
//

#include "stdafx.h"
#include "MyFrameView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFrameView

IMPLEMENT_DYNCREATE(CMyFrameView, CScrollView)

CMyFrameView::CMyFrameView()
{
	m_MouseSocket = 0;
	pBitHeadInfo = new char[65535];
	bIsInit = FALSE;
	lpbi = NULL;
}

CMyFrameView::~CMyFrameView()
{
	delete [] pBitHeadInfo;
}

BEGIN_MESSAGE_MAP(CMyFrameView, CScrollView)
	//{{AFX_MSG_MAP(CMyFrameView)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_SYSKEYDOWN()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_ONEFRAME,OnOneFrame)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyFrameView drawing

void CMyFrameView::OnDraw(CDC* pDC)
{
	
}

/////////////////////////////////////////////////////////////////////////////
// CMyFrameView diagnostics

#ifdef _DEBUG
void CMyFrameView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMyFrameView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyFrameView message handlers

void CMyFrameView::OnPaint() 
{
	CPaintDC dc(this); 
	MakeBitmap(&dc);
}

void CMyFrameView::GetSize(char* pText)
{
	CSize m_Size = GetTotalSize();
	if(m_Size.cx == 0 || m_Size.cy == 0)
		sprintf(pText,"�� : %d �� : %d",0,0);
	else
		sprintf(pText,"�� : %d �� : %d",m_Size.cx + 1,m_Size.cy + 1);
}

void CMyFrameView::InitMyData(CSize m_Size)
{
	if(m_MainBitmap.GetSafeHandle()) 
		m_MainBitmap.DeleteObject();
	SetScrollSizes(MM_TEXT,CSize(m_Size.cx -1,m_Size.cy - 1));
	ScrollToPosition(CPoint(0,0));
	CDC *pDC = GetDC();
	m_MainBitmap.CreateCompatibleBitmap(pDC,m_Size.cx,m_Size.cy);
	CDC m_SrcDC;
	m_SrcDC.CreateCompatibleDC(pDC);
	CBitmap *pOldSrcBitmap = m_SrcDC.SelectObject(&m_MainBitmap);
	m_SrcDC.FillSolidRect(0,0,m_Size.cx,m_Size.cy,RGB(0,0,0));
	m_SrcDC.SelectObject(pOldSrcBitmap);
	ReleaseDC(pDC);
}

BOOL CMyFrameView::OnEraseBkgnd(CDC* pDC) 
{
	MakeBitmap(pDC);
	return TRUE;
}

void CMyFrameView::MakeBitmap(CDC *pDC)
{
	CDC m_SrcDC,m_DesDC;
	CBitmap m_DesBitmap,*pOldDesBitmap,*pOldSrcBitmap;

	CRect rect;
	GetClientRect(&rect);

	m_SrcDC.CreateCompatibleDC(pDC);
	m_DesDC.CreateCompatibleDC(pDC);

	if(!m_MainBitmap.GetSafeHandle())
	{
		m_MainBitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
		pOldSrcBitmap = m_SrcDC.SelectObject(&m_MainBitmap);
		m_SrcDC.FillSolidRect(&rect,RGB(0,0,0));
		m_SrcDC.SelectObject(pOldSrcBitmap);
	}
	
	m_DesBitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	pOldDesBitmap = m_DesDC.SelectObject(&m_DesBitmap);
	
	BITMAP bitmap;
	m_MainBitmap.GetBitmap(&bitmap);
	pOldSrcBitmap = m_SrcDC.SelectObject(&m_MainBitmap);

	if(bitmap.bmWidth <= rect.Width()
		&& bitmap.bmHeight <= rect.Height())
	{
		m_DesDC.FillSolidRect(&rect,RGB(0,0,0));
		m_DesDC.BitBlt((rect.Width() - bitmap.bmWidth)/2
			,(rect.Height() - bitmap.bmHeight)/2,
				bitmap.bmWidth,bitmap.bmHeight,
					&m_SrcDC,0,0,SRCCOPY);
	}
	else
	{
		CPoint m_Point = GetDeviceScrollPosition();
		m_DesDC.BitBlt(0,0,bitmap.bmWidth,
			bitmap.bmHeight,&m_SrcDC,
				m_Point.x,m_Point.y,SRCCOPY);
	}
	m_SrcDC.SelectObject(pOldSrcBitmap);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&m_DesDC,0,0,SRCCOPY);
	m_DesDC.SelectObject(pOldSrcBitmap);
}

BOOL CMyFrameView::ExecCmd(LPMOUSEINFO pInfo)
{
	if(m_MouseSocket == 0) return FALSE;
	return SendData(m_MouseSocket,(char*) pInfo,sizeof(MOUSEINFO));
}

LRESULT CMyFrameView::OnOneFrame(WPARAM wParam,LPARAM lParam)
{
	if(lParam == 1)
	{
		//��ʼ���ṹ
		DWORD m_FrameLen = 
			(1 << 8) * sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);
		memcpy(pBitHeadInfo, (char*) wParam, m_FrameLen);
		LPBITMAPINFOHEADER pInfo = (LPBITMAPINFOHEADER) pBitHeadInfo;
		InitMyData(CSize(pInfo->biWidth,pInfo->biHeight));
		lpbi = (LPBITMAPINFOHEADER) pBitHeadInfo;
		bIsInit = TRUE;
		return TRUE;
	}

	if(!bIsInit) return FALSE;

	//ȡλͼ��Ϣ
	BYTE *pStart = (BYTE*) wParam;
	BYTE *pMask = pStart;
	pStart += lpbi->biHeight;
	BYTE * pBitData = pStart;
	DWORD m_LineBitmapSize = 
		((lpbi->biWidth* lpbi->biBitCount + 31)/32)* 4 ;
	
	//����ͼ����
	DWORD nHeight = lpbi->biHeight;
	lpbi->biHeight = 1;

	//����ͼ��
	CDC *pDC = GetDC();
	for(DWORD i = 0; i < nHeight; i++)
	{
		//�鿴�Ƿ���ʾ
		if(pMask[i] == 1)
		{
			//����λͼ
			HBITMAP hBitmap = 
				CreateDIBitmap(pDC->GetSafeHdc(),lpbi,
				CBM_INIT, pBitData,(LPBITMAPINFO)lpbi, 
				DIB_RGB_COLORS);
			
			//��һ��ͼ
			CDC m_SrcDC,m_DesDC;
			m_SrcDC.CreateCompatibleDC(pDC);
			m_DesDC.CreateCompatibleDC(pDC);
			CBitmap *pOldSrcBitmap = 
				m_SrcDC.SelectObject(CBitmap::FromHandle(hBitmap));
			CBitmap *pOldDesBitmap = 
				m_DesDC.SelectObject(&m_MainBitmap);
			m_DesDC.BitBlt(0,nHeight - i - 1,
				lpbi->biWidth,1,&m_SrcDC,0,0,SRCCOPY);
			m_SrcDC.SelectObject(pOldSrcBitmap);
			m_DesDC.SelectObject(pOldDesBitmap);
			DeleteObject(hBitmap);
			pBitData += m_LineBitmapSize;
		}
	}

	lpbi->biHeight = nHeight;

	//��ͼ
	MakeBitmap(pDC);
	ReleaseDC(pDC);
	return TRUE;
}

void CMyFrameView::SaveFrame()
{
	if(!m_MainBitmap.GetSafeHandle())
		return;

	char OldDir[256] = {0};
	GetCurrentDirectory(256,OldDir);
	CString szFilter = "λͼ�ļ�(*.bmp)|*.bmp|";
	CFileDialog m_filedialog(FALSE,NULL,"Frame.bmp",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,this);
	if(m_filedialog.DoModal()!=IDOK)
		return;

	BITMAPFILEHEADER	bmfHdr;			//λͼ���Խṹ    
	BITMAPINFOHEADER	bi;				//λͼ�ļ�ͷ�ṹ       
	LPBITMAPINFOHEADER	lpbi;			//λͼ��Ϣͷ�ṹ   
	BITMAP				Bitmap;			//ָ��λͼ��Ϣͷ�ṹ
	LPBYTE				pBitData;		//λͼ����
	DWORD				dwBmBitsSize;	//λͼ�ļ���С
	HDC					hScrDC;			//�豸������
	HANDLE				hPal = NULL;	//��ɫ����
	HANDLE				hOldPal=NULL;	//�ɵ�ɫ��
	DWORD				dwPaletteSize;	//��ɫ

	m_MainBitmap.GetBitmap(&Bitmap);
	bi.biSize				= sizeof(BITMAPINFOHEADER);
	bi.biWidth				= Bitmap.bmWidth;
	bi.biHeight				= Bitmap.bmHeight;
	bi.biPlanes				= 1;
	bi.biBitCount			= 8;
	bi.biCompression		= BI_RGB;
	bi.biSizeImage			= 0;
	bi.biXPelsPerMeter		= 0;
	bi.biYPelsPerMeter		= 0;
	bi.biClrUsed			= 0;
	bi.biClrImportant		= 0;

	dwBmBitsSize = ((Bitmap.bmWidth *
		8+31)/32)* 4*Bitmap.bmHeight ;

	dwPaletteSize = (1 << 8) *sizeof(RGBQUAD);

	//Ϊλͼ���ݷ����ڴ�
	pBitData  = new BYTE[sizeof(BITMAPINFOHEADER) 
		+ dwBmBitsSize + dwPaletteSize];
	lpbi = (LPBITMAPINFOHEADER) pBitData;
	*lpbi = bi;

	// �����ɫ��   
	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hScrDC  = ::GetDC(NULL);
		hOldPal = SelectPalette(hScrDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hScrDC);
	}

	// ��ȡ�õ�ɫ�����µ�����ֵ
	GetDIBits(hScrDC, (HBITMAP) m_MainBitmap.GetSafeHandle(), 0, 
		(UINT) Bitmap.bmHeight,(LPSTR)lpbi + 
			sizeof(BITMAPINFOHEADER) + dwPaletteSize,
				(LPBITMAPINFO)lpbi, DIB_RGB_COLORS);

	//�ָ���ɫ��   
	if (hOldPal)
	{
		SelectPalette(hScrDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hScrDC);
		::ReleaseDC(NULL, hScrDC);
	}
	
	// ����λͼ�ļ�ͷ
	bmfHdr.bfType = 0x4D42;  // "BM"
	bmfHdr.bfSize = sizeof(BITMAPFILEHEADER) 
		+ sizeof(BITMAPINFOHEADER) + dwBmBitsSize + dwPaletteSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) 
		+ (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;

	CFile m_File;
	if(!m_File.Open(m_filedialog.GetPathName(),
		CFile::modeCreate|CFile::modeWrite))
	{
		MessageBox("�޷�����ͼ���ļ�","����");
		delete [] pBitData;
		return;
	}

	m_File.Write(&bmfHdr,sizeof(BITMAPFILEHEADER));
	m_File.Write(pBitData,
		sizeof(BITMAPINFOHEADER) + dwBmBitsSize + dwPaletteSize);
	m_File.Close();
	delete [] pBitData;
}

void CMyFrameView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CScrollView::OnLButtonDown(nFlags, point);

	if(!bIsInit) return;

	MOUSEINFO m_MouseInfo = {0};
	m_MouseInfo.cmd = CMD_FRAME_MOUSE_STATE;
	CPoint m_Point = GetDeviceScrollPosition();
	CRect rcClient;
	GetClientRect(&rcClient);
	if(rcClient.Width() > lpbi->biWidth)
	{
		//��Ļ�ȿͻ���С
		m_MouseInfo.x = point.x - (rcClient.Width() - lpbi->biWidth)/2;
		m_MouseInfo.y = point.y - (rcClient.Height() - lpbi->biHeight)/2;
	}
	else
	{
		m_MouseInfo.x = (WORD) (point.x + m_Point.x);
		m_MouseInfo.y = (WORD) (point.y + m_Point.y);
	}
	m_MouseInfo.state = MOUSEEVENTF_LEFTDOWN;
	ExecCmd(&m_MouseInfo);
}

void CMyFrameView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CScrollView::OnLButtonUp(nFlags, point);

	if(!bIsInit) return;

	MOUSEINFO m_MouseInfo = {0};
	m_MouseInfo.cmd = CMD_FRAME_MOUSE_STATE;
	CPoint m_Point = GetDeviceScrollPosition();
	CRect rcClient;
	GetClientRect(&rcClient);
	if(rcClient.Width() > lpbi->biWidth)
	{
		//��Ļ�ȿͻ���С
		m_MouseInfo.x = point.x - (rcClient.Width() - lpbi->biWidth)/2;
		m_MouseInfo.y = point.y - (rcClient.Height() - lpbi->biHeight)/2;
	}
	else
	{
		m_MouseInfo.x = (WORD) (point.x + m_Point.x);
		m_MouseInfo.y = (WORD) (point.y + m_Point.y);
	}
	m_MouseInfo.state = MOUSEEVENTF_LEFTUP;
	ExecCmd(&m_MouseInfo);
}

void CMyFrameView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CScrollView::OnRButtonDown(nFlags, point);

	if(!bIsInit) return;

	MOUSEINFO m_MouseInfo = {0};
	m_MouseInfo.cmd = CMD_FRAME_MOUSE_STATE;
	CPoint m_Point = GetDeviceScrollPosition();
	CRect rcClient;
	GetClientRect(&rcClient);
	if(rcClient.Width() > lpbi->biWidth)
	{
		//��Ļ�ȿͻ���С
		m_MouseInfo.x = point.x - (rcClient.Width() - lpbi->biWidth)/2;
		m_MouseInfo.y = point.y - (rcClient.Height() - lpbi->biHeight)/2;
	}
	else
	{
		m_MouseInfo.x = (WORD) (point.x + m_Point.x);
		m_MouseInfo.y = (WORD) (point.y + m_Point.y);
	}
	m_MouseInfo.state = MOUSEEVENTF_RIGHTDOWN;
	ExecCmd(&m_MouseInfo);
}

void CMyFrameView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CScrollView::OnRButtonUp(nFlags, point);

	if(!bIsInit) return;

	MOUSEINFO m_MouseInfo = {0};
	m_MouseInfo.cmd = CMD_FRAME_MOUSE_STATE;
	CPoint m_Point = GetDeviceScrollPosition();
	CRect rcClient;
	GetClientRect(&rcClient);
	if(rcClient.Width() > lpbi->biWidth)
	{
		//��Ļ�ȿͻ���С
		m_MouseInfo.x = point.x - (rcClient.Width() - lpbi->biWidth)/2;
		m_MouseInfo.y = point.y - (rcClient.Height() - lpbi->biHeight)/2;
	}
	else
	{
		m_MouseInfo.x = (WORD) (point.x + m_Point.x);
		m_MouseInfo.y = (WORD) (point.y + m_Point.y);
	}
	m_MouseInfo.state = MOUSEEVENTF_RIGHTUP;
	ExecCmd(&m_MouseInfo);
}

void CMyFrameView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CScrollView::OnLButtonDblClk(nFlags, point);

	if(!bIsInit) return;

	MOUSEINFO m_MouseInfo = {0};
	m_MouseInfo.cmd = CMD_FRAME_MOUSE_STATE;
	CPoint m_Point = GetDeviceScrollPosition();
	CRect rcClient;
	GetClientRect(&rcClient);
	if(rcClient.Width() > lpbi->biWidth)
	{
		//��Ļ�ȿͻ���С
		m_MouseInfo.x = point.x - (rcClient.Width() - lpbi->biWidth)/2;
		m_MouseInfo.y = point.y - (rcClient.Height() - lpbi->biHeight)/2;
	}
	else
	{
		m_MouseInfo.x = (WORD) (point.x + m_Point.x);
		m_MouseInfo.y = (WORD) (point.y + m_Point.y);
	}
	m_MouseInfo.state = MOUSEEVENTF_LEFTDOWN;
	ExecCmd(&m_MouseInfo);

	m_MouseInfo.state = MOUSEEVENTF_LEFTUP;
	ExecCmd(&m_MouseInfo);

	m_MouseInfo.state = MOUSEEVENTF_LEFTDOWN;
	ExecCmd(&m_MouseInfo);

	m_MouseInfo.state = MOUSEEVENTF_LEFTUP;
	ExecCmd(&m_MouseInfo);
}

void CMyFrameView::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	CScrollView::OnRButtonDblClk(nFlags, point);

	if(!bIsInit) return;

	MOUSEINFO m_MouseInfo = {0};
	m_MouseInfo.cmd = CMD_FRAME_MOUSE_STATE;
	CPoint m_Point = GetDeviceScrollPosition();
	CRect rcClient;
	GetClientRect(&rcClient);
	if(rcClient.Width() > lpbi->biWidth)
	{
		//��Ļ�ȿͻ���С
		m_MouseInfo.x = point.x - (rcClient.Width() - lpbi->biWidth)/2;
		m_MouseInfo.y = point.y - (rcClient.Height() - lpbi->biHeight)/2;
	}
	else
	{
		m_MouseInfo.x = (WORD) (point.x + m_Point.x);
		m_MouseInfo.y = (WORD) (point.y + m_Point.y);
	}
	m_MouseInfo.state = MOUSEEVENTF_RIGHTDOWN;
	ExecCmd(&m_MouseInfo);
	
	m_MouseInfo.state = MOUSEEVENTF_RIGHTUP;
	ExecCmd(&m_MouseInfo);

	m_MouseInfo.state = MOUSEEVENTF_RIGHTDOWN;
	ExecCmd(&m_MouseInfo);

	m_MouseInfo.state = MOUSEEVENTF_RIGHTUP;
	ExecCmd(&m_MouseInfo);
}

BOOL CMyFrameView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	MOUSEINFO m_MouseInfo = {0};
	m_MouseInfo.cmd = CMD_FRAME_MOUSE_STATE;
	m_MouseInfo.x = (zDelta > 0) ? 1 : 0;
	m_MouseInfo.y = abs(zDelta);
	m_MouseInfo.state = MOUSEEVENTF_WHEEL;
	ExecCmd(&m_MouseInfo);
	return TRUE;
}

void CMyFrameView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CScrollView::OnMouseMove(nFlags, point);
	if(!bIsInit) return;

	MOUSEINFO m_MouseInfo = {0};
	m_MouseInfo.cmd = CMD_FRAME_MOUSE_STATE;
	CPoint m_Point = GetDeviceScrollPosition();
	CRect rcClient;
	GetClientRect(&rcClient);
	if(rcClient.Width() > lpbi->biWidth)
	{
		//��Ļ�ȿͻ���С
		m_MouseInfo.x = point.x - (rcClient.Width() - lpbi->biWidth)/2;
		m_MouseInfo.y = point.y - (rcClient.Height() - lpbi->biHeight)/2;
	}
	else
	{
		m_MouseInfo.x = (WORD) (point.x + m_Point.x);
		m_MouseInfo.y = (WORD) (point.y + m_Point.y);
	}
	m_MouseInfo.state = 0;
	ExecCmd(&m_MouseInfo);
}

void CMyFrameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);

	MOUSEINFO m_MouseInfo = {0};
	m_MouseInfo.cmd = CMD_FRAME_KEY_STATE;
	SHORT ch = 0;
	ch = GetKeyState(VK_SHIFT);
	m_MouseInfo.x = HIBYTE(ch);
	ch = GetKeyState(VK_CONTROL);
	m_MouseInfo.y = HIBYTE(ch);
	ch = GetKeyState(VK_MENU );
	m_MouseInfo.state = HIBYTE(ch);
	m_MouseInfo.ch = nChar;
	for(UINT i = 0; i < nRepCnt; i++)
		ExecCmd(&m_MouseInfo);
}

void CMyFrameView::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CScrollView::OnSysKeyDown(nChar, nRepCnt, nFlags);

	MOUSEINFO m_MouseInfo = {0};
	m_MouseInfo.cmd = CMD_FRAME_KEY_STATE;
	SHORT ch = 0;
	ch = GetKeyState(VK_SHIFT);
	m_MouseInfo.x = HIBYTE(ch);
	ch = GetKeyState(VK_CONTROL);
	m_MouseInfo.y = HIBYTE(ch);
	ch = GetKeyState(VK_MENU );
	m_MouseInfo.state = HIBYTE(ch);
	m_MouseInfo.ch = nChar;
	for(UINT i = 0; i < nRepCnt; i++)
		ExecCmd(&m_MouseInfo);
}


