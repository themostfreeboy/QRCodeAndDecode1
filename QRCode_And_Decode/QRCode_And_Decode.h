
// QRCode_And_Decode.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CQRCode_And_DecodeApp:
// �йش����ʵ�֣������ QRCode_And_Decode.cpp
//

class CQRCode_And_DecodeApp : public CWinApp
{
public:
	CQRCode_And_DecodeApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CQRCode_And_DecodeApp theApp;