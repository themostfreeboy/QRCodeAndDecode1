
// QRCode_And_DecodeDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CQRCode_And_DecodeDlg 对话框
class CQRCode_And_DecodeDlg : public CDialogEx
{
// 构造
public:
	CQRCode_And_DecodeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_QRCODE_AND_DECODE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	int DataFromFileToNumber(CString filename,CString* number);//将数据从文件中读取转化为数字
	int DataFromNumberToFile(CString number,CString filename);//将数据从数字转化到文件中
	int DataFromBufferToFile(CString buffer,CString filename);//将数据从内存复制到文件
	int DataFromFileToBuffer(CString filename,CString* buffer);//将数据从文件复制到内存
};
