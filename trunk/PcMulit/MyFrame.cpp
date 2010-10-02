// MyFrame.cpp : implementation file
//

#include "stdafx.h"
#include "PcMulit.h"
#include "MyFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFrame

CMyFrame::CMyFrame()
{
	hBitmap = NULL;
}

CMyFrame::~CMyFrame()
{
	if(hBitmap != NULL)
		DeleteObject(hBitmap);
}


BEGIN_MESSAGE_MAP(CMyFrame, CStatic)
	//{{AFX_MSG_MAP(CMyFrame)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyFrame message handlers

void CMyFrame::DrawOneFrame(LPBITMAPINFO pInfo, LPVOID pData)
{
	if(hBitmap != NULL)
		DeleteObject(hBitmap);

	//����ͼ��
	CDC *pDC = GetDC();

	//����λͼ
	hBitmap = CreateDIBitmap(pDC->GetSafeHdc(),
		&pInfo->bmiHeader,CBM_INIT, pData,pInfo, 
		DIB_RGB_COLORS);
	
	//��ͼ
	CDC m_SrcDC;
	m_SrcDC.CreateCompatibleDC(pDC);
	CBitmap *pOldSrcBitmap = 
		m_SrcDC.SelectObject(CBitmap::FromHandle(hBitmap));
	pDC->BitBlt(0,0,IMAGE_WIDTH,IMAGE_HEIGHT,&m_SrcDC,0,0,SRCCOPY);
	m_SrcDC.SelectObject(pOldSrcBitmap);
	ReleaseDC(pDC);
}

void CMyFrame::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if(hBitmap == NULL) return;

	//��ͼ
	CDC m_SrcDC;
	m_SrcDC.CreateCompatibleDC(&dc);
	CBitmap *pOldSrcBitmap = 
		m_SrcDC.SelectObject(CBitmap::FromHandle(hBitmap));
	dc.BitBlt(0,0,IMAGE_WIDTH,IMAGE_HEIGHT,&m_SrcDC,0,0,SRCCOPY);
	m_SrcDC.SelectObject(pOldSrcBitmap);
}

BOOL CMyFrame::OnEraseBkgnd(CDC* pDC) 
{
	if(hBitmap == NULL)
		return CStatic::OnEraseBkgnd(pDC);

	//��ͼ
	CDC m_SrcDC;
	m_SrcDC.CreateCompatibleDC(pDC);
	CBitmap *pOldSrcBitmap = 
		m_SrcDC.SelectObject(CBitmap::FromHandle(hBitmap));
	pDC->BitBlt(0,0,IMAGE_WIDTH,IMAGE_HEIGHT,&m_SrcDC,0,0,SRCCOPY);
	m_SrcDC.SelectObject(pOldSrcBitmap);
	return TRUE;
}


BOOL CMyFrame::SaveBitmapToFile(HBITMAP hBitmap , CString lpFileName) 
{    	 
	HDC				hDC;							//�豸������  
    int				iBits;							//��ǰ��ʾ�ֱ�����ÿ��������ռ�ֽ���
	WORD            wBitCount;						//λͼ��ÿ��������ռ�ֽ���
	DWORD           dwPaletteSize=0,				//�����ɫ���С�� λͼ�������ֽڴ�С ��λͼ�ļ���С �� д���ļ��ֽ���
					dwBmBitsSize,
					dwDIBSize, dwWritten;
	BITMAP          Bitmap;        
	BITMAPFILEHEADER   bmfHdr;						//λͼ���Խṹ    
    BITMAPINFOHEADER   bi;							//λͼ�ļ�ͷ�ṹ       
	LPBITMAPINFOHEADER lpbi;						//λͼ��Ϣͷ�ṹ     
    HANDLE          fh, hDib, hPal,hOldPal=NULL;	//ָ��λͼ��Ϣͷ�ṹ,�����ļ��������ڴ�������ɫ����
  
   //����λͼ�ļ�ÿ��������ռ�ֽ���
   hDC = CreateDC("DISPLAY",NULL,NULL,NULL);
   iBits = GetDeviceCaps(hDC, BITSPIXEL) * 
   GetDeviceCaps(hDC, PLANES);
   DeleteDC(hDC);
   if (iBits <= 1)
      wBitCount = 1;
   else if (iBits <= 4)
      wBitCount = 4;
   else if (iBits <= 8)
      wBitCount = 8;
   else 
      wBitCount = 24;
   //�����ɫ���С
   if (wBitCount <= 8)
      dwPaletteSize = (1 << wBitCount) *sizeof(RGBQUAD);
   
   //����λͼ��Ϣͷ�ṹ
   GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
   bi.biSize            = sizeof(BITMAPINFOHEADER);
   bi.biWidth           = Bitmap.bmWidth;
   bi.biHeight          = Bitmap.bmHeight;
   bi.biPlanes          = 1;
   bi.biBitCount         = wBitCount;
   bi.biCompression      = BI_RGB;
   bi.biSizeImage        = 0;
   bi.biXPelsPerMeter     = 0;
   bi.biYPelsPerMeter     = 0;
   bi.biClrUsed         = 0;
   bi.biClrImportant      = 0;

   dwBmBitsSize = ((Bitmap.bmWidth *
    wBitCount+31)/32)* 4
	 *Bitmap.bmHeight ;

   //Ϊλͼ���ݷ����ڴ�
   hDib  = GlobalAlloc(GHND,dwBmBitsSize+
	dwPaletteSize+sizeof(BITMAPINFOHEADER));
   lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
   *lpbi = bi;

   // �����ɫ��   
   hPal = GetStockObject(DEFAULT_PALETTE);
   if (hPal)
   {
	   hDC  = ::GetDC(NULL);
	   hOldPal = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
       RealizePalette(hDC);
   }

   // ��ȡ�õ�ɫ�����µ�����ֵ
   GetDIBits(hDC, hBitmap, 0, (UINT) Bitmap.bmHeight,
	 (LPSTR)lpbi + sizeof(BITMAPINFOHEADER)+dwPaletteSize,
	 (LPBITMAPINFO)lpbi, DIB_RGB_COLORS);

   //�ָ���ɫ��   
   if (hOldPal)
   {
      SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
      RealizePalette(hDC);
      ::ReleaseDC(NULL, hDC);
   }

   //����λͼ�ļ�    
	fh = CreateFile(lpFileName, GENERIC_WRITE, 
		 0, NULL, CREATE_ALWAYS,
         FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

   if (fh == INVALID_HANDLE_VALUE)
      return FALSE;

   // ����λͼ�ļ�ͷ
   bmfHdr.bfType = 0x4D42;  // "BM"
   dwDIBSize    = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;  
   bmfHdr.bfSize = dwDIBSize;
   bmfHdr.bfReserved1 = 0;
   bmfHdr.bfReserved2 = 0;
   bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) 
      + (DWORD)sizeof(BITMAPINFOHEADER)
     + dwPaletteSize;

   // д��λͼ�ļ�ͷ
   WriteFile(fh, (LPSTR)&bmfHdr, sizeof
	(BITMAPFILEHEADER), &dwWritten, NULL);
   // д��λͼ�ļ���������
   WriteFile(fh, (LPSTR)lpbi, dwDIBSize, 
   &dwWritten, NULL);

   //�����ڴ����  
   GlobalUnlock(hDib);
   GlobalFree(hDib);
   CloseHandle(fh);

   return TRUE;
}

void CMyFrame::SaveFrame()
{
	//����ͼƬ
	if(hBitmap == NULL)	return;
	HBITMAP hCurBitmap = (HBITMAP)
		CopyImage(hBitmap,IMAGE_BITMAP,0,0,LR_COPYRETURNORG);

	//�ļ�·��
	char OldDir[256] = {0};
	GetCurrentDirectory(256,OldDir);
	CString szFilter = "λͼ�ļ�(*.bmp)|*.bmp|";
	CFileDialog m_filedialog(FALSE,NULL,"Frame.bmp",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,this);
	if(m_filedialog.DoModal()!=IDOK)
	{
		DeleteObject(hCurBitmap);
		return;
	}

	//���浽�ļ�
	SaveBitmapToFile(hCurBitmap, m_filedialog.GetPathName());
	DeleteObject(hCurBitmap);
}

void CMyFrame::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CStatic::OnLButtonDblClk(nFlags, point);
	SaveFrame();
}
