#include "stdafx.h"
#include "Lzw.h"

//===================================================================
// Ŀ��Ϊ8λɫ
void  FCLzw::Decode_WriteString_to8 (WORD Code)
{
	if (Code < m_LZW_CLEAR)
	{
		m_pCurOut[m_dwCurrPixel++] = (BYTE) m_pStrBegin[Code].wSuffix ;
		if (m_dwCurrPixel == m_dwDibWidth) // д��һ��, �л�ֵ����һ��
			this->Decode_SwitchToFollowLine () ;
	}
	else
	{
		this->Decode_WriteString_to8 (m_pStrBegin[Code].wPrefix) ;
		this->Decode_WriteString_to8 (m_pStrBegin[Code].wSuffix) ;
	}
}
//===================================================================
void  FCLzw::LZW_GIF_Decode (BYTE * InBuffer, BYTE * DibBuffer, DWORD dwDibWidth, DWORD dwDibHeight, bool bInterlace)
{
	m_pStrBegin = new LZW_STRING [LZW_MAX_TABLE_SIZE + 32] ;
	if ((m_pStrBegin == NULL) || (InBuffer == NULL) || (DibBuffer == NULL))
		 return ;
	//	��ʼ������-----------------------------------------+
	m_pCurIn = InBuffer + 1 ;
	m_pCurOut = DibBuffer ;
	m_byInBit = 0 ; // �����0��ʼ, ���Ϊ8λɫλͼ
	m_byMinCode = *InBuffer ; // �����С�볤��
	m_LZW_CLEAR = 1 << m_byMinCode ; // clear
	m_LZW_END = m_LZW_CLEAR + 1 ; // end

	m_dwDibWidth = dwDibWidth ; // DIB��
	m_dwCurrPixel = 0 ;
	m_dwPitch = 4 * ((dwDibWidth * 8 + 31) / 32) ;

	m_byInterval = bInterlace ? 0 : 0xFF ; // ���ý�������
	if (m_byInterval == 0) // ����洢
	{
		m_pOrigin = m_pCurOut ;
		m_dwDibHeight = dwDibHeight ; // DIB��
		m_dwCurrHeight = 0 ; // ����п�ʼ
	}
	//	��ʼ���������-------------------------------------+

	WORD		Code, Old ;
	this->Decode_InitStringTable () ;
	while ((Code = this->Decode_GetNextCode ()) != m_LZW_END)
	{
		if (Code == m_LZW_CLEAR)
		{
			this->Decode_InitStringTable () ;
			while ((Code = this->Decode_GetNextCode ()) == m_LZW_CLEAR) ;
		}
		else
			if (this->Decode_IsInTable (Code))
				this->Decode_AddStringToTable (Old, this->Decode_GetFirstChar (Code)) ;
			else
				this->Decode_AddStringToTable (Old, this->Decode_GetFirstChar (Old)) ;

		this->Decode_WriteString_to8 (Code) ;
		Old = Code ;
	}
	delete[] m_pStrBegin ;
}
//===================================================================
DWORD  FCLzw::LZW_GIF_Encode (BYTE * DibBuffer, BYTE * OutBuffer,
							  DWORD dwDibWidth, DWORD dwDibHeight,
							  WORD wColorBit)
{
	//	����׶β���ҪString Table��ֻ��Ҫm_CurrTableIndex����֪дλ��
	m_pHash = new WORD [LZW_MAX_HASH_SIZE] ;
	if ((m_pHash == NULL) || (DibBuffer == NULL) || (OutBuffer == NULL))
		return 0 ;
	//	��ʼ������-----------------------------------------+
	m_byMinCode = (wColorBit == 1) ? 2 : wColorBit ; // 1, 4, 8λɫ(��С�볤��)��1λɫΪ2
	m_LZW_CLEAR = 1 << m_byMinCode ;
	m_LZW_END = m_LZW_CLEAR + 1 ;
	m_pOrigin = m_pCurIn = DibBuffer ;
	m_pCurOut = OutBuffer ;
	m_byInBit = 8 ;
	m_byOutBit = 0 ; // �����0��ʼ

	m_dwDibWidth = dwDibWidth ;		// DIB��
	m_dwDibHeight = dwDibHeight ;	// DIB��
	m_dwCurrPixel = 0 ;
	m_dwCurrHeight = 0 ; // ����п�ʼ
	m_dwPitch = 4 * ((dwDibWidth * m_byMinCode + 31) / 32) ;
	//	��ʼ���������-------------------------------------+

	WORD		Old ;	// �����ִ�
	BYTE		Pixel ;	// ��ǰ�����ַ�
	this->Encode_InitStringTable () ;
	this->Encode_WriteIndex (m_LZW_CLEAR) ; // ����дclear
	Old = this->Encode_GetNextPixel () ;
	// ����
	while (m_dwCurrHeight < m_dwDibHeight)
	{
		Pixel = this->Encode_GetNextPixel () ;
		if (this->Encode_IsInTable (Old, Pixel))
			Old = m_pHash[(Old << 8) | Pixel] ; // ���ڱ���, ȡ������, Hash Table�д�ŵ���String Table��Index
		else
		{
			//	���ڱ���, ��Old + Pixel��ӵ�String Table��
			this->Encode_WriteIndex (Old) ;
			this->Encode_AddStringToTable (Old, Pixel) ;
			Old = Pixel ;
			if (m_CurrTableIndex == LZW_MAX_TABLE_SIZE) // ������
			{
				this->Encode_WriteIndex (Pixel) ;
				this->Encode_WriteIndex (m_LZW_CLEAR) ;
				this->Encode_InitStringTable () ;
				Old = this->Encode_GetNextPixel () ;
			}
		}
	}
	this->Encode_WriteIndex (Old) ;
	this->Encode_WriteIndex (m_LZW_END) ;
	delete[] m_pHash ;
	return (m_pCurOut - OutBuffer + 1) ;
}
//===================================================================
