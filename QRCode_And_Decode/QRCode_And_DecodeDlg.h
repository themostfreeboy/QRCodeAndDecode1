
// QRCode_And_DecodeDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CQRCode_And_DecodeDlg �Ի���
class CQRCode_And_DecodeDlg : public CDialogEx
{
// ����
public:
	CQRCode_And_DecodeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_QRCODE_AND_DECODE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int CodeOrDecode;
	afx_msg void OnBnClickedRcode();
	CComboBox CBModeControl;
	afx_msg void OnBnClickedBchoosefile();
	afx_msg void OnBnClickedBstart();
	afx_msg void OnBnClickedBexit();
	CString EditChoosePath;
	afx_msg void OnEnChangeEfilepath();
	CString EditText;
	afx_msg void OnEnChangeEtext();
	int MyLoadPicture(CString picturename);
	void MyQRCode(CString filename,CString text);
	void MyQRDecode(CString QRpicturefilename,CString outdatafilename);
	int DataFromFileToNumber(CString filename,CString* number);//�����ݴ��ļ��ж�ȡת��Ϊ����
	int DataFromNumberToFile(CString number,CString filename);//�����ݴ�����ת�����ļ���
	int DataFromBufferToFile(CString buffer,CString filename);//�����ݴ��ڴ渴�Ƶ��ļ�
	int DataFromFileToBuffer(CString filename,CString* buffer);//�����ݴ��ļ����Ƶ��ڴ�
};
