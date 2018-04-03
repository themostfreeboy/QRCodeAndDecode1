
// QRCode_And_DecodeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QRCode_And_Decode.h"
#include "QRCode_And_DecodeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CQRCode_And_DecodeDlg 对话框




CQRCode_And_DecodeDlg::CQRCode_And_DecodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQRCode_And_DecodeDlg::IDD, pParent)
	, CodeOrDecode(0)
	, EditChoosePath(_T(""))
	, EditText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQRCode_And_DecodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RCODE, CodeOrDecode);
	DDX_Control(pDX, IDC_CBMODE, CBModeControl);
	DDX_Text(pDX, IDC_EFILEPATH, EditChoosePath);
	DDX_Text(pDX, IDC_ETEXT, EditText);
}

BEGIN_MESSAGE_MAP(CQRCode_And_DecodeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RCODE, &CQRCode_And_DecodeDlg::OnBnClickedRcode)
	ON_BN_CLICKED(IDC_RDECODE, &CQRCode_And_DecodeDlg::OnBnClickedRcode)
	ON_BN_CLICKED(IDC_BCHOOSEFILE, &CQRCode_And_DecodeDlg::OnBnClickedBchoosefile)
	ON_BN_CLICKED(IDC_BSTART, &CQRCode_And_DecodeDlg::OnBnClickedBstart)
	ON_BN_CLICKED(IDC_BEXIT, &CQRCode_And_DecodeDlg::OnBnClickedBexit)
	ON_EN_CHANGE(IDC_EFILEPATH, &CQRCode_And_DecodeDlg::OnEnChangeEfilepath)
	ON_EN_CHANGE(IDC_ETEXT, &CQRCode_And_DecodeDlg::OnEnChangeEtext)
END_MESSAGE_MAP()


// CQRCode_And_DecodeDlg 消息处理程序

BOOL CQRCode_And_DecodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CComboBox *pBox = (CComboBox *)GetDlgItem(IDC_CBMODE);
	pBox->ResetContent();
	pBox->AddString(_T("模式一"));//RSA加密+zlib压缩
	pBox->AddString(_T("模式二"));//DES加密+7z压缩
	pBox->SetCurSel(0);//设置第0项为显示的内容
	SetDlgItemText(IDC_BSTART,_T("开始生成二维码"));

	CEdit *edit = (CEdit*)GetDlgItem(IDC_STEXTTIP);
	edit->ShowWindow(TRUE);//待生成二维码提示可见
	edit = (CEdit*)GetDlgItem(IDC_ETEXT);
	edit->ShowWindow(TRUE);//待生成二维码内容可见

	edit = (CEdit*)GetDlgItem(IDC_SFILEPATHTIP);
	edit->ShowWindow(FALSE);//待解析二维码文件路径提示不可见
	edit = (CEdit*)GetDlgItem(IDC_EFILEPATH);
	edit->ShowWindow(FALSE);//待解析二维码文件路径不可见
	edit = (CEdit*)GetDlgItem(IDC_BCHOOSEFILE);
	edit->ShowWindow(FALSE);//选择文件按钮不可见

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CQRCode_And_DecodeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CQRCode_And_DecodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CQRCode_And_DecodeDlg::OnBnClickedRcode()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(CodeOrDecode==0)//加密
	{
		CBModeControl.ResetContent();
		CBModeControl.AddString(_T("模式一"));//RSA加密+zlib压缩
		CBModeControl.AddString(_T("模式二"));//DES加密+zlib压缩
		CBModeControl.SetCurSel(0);//设置第0项为显示的内容
		SetDlgItemText(IDC_BSTART,_T("开始生成二维码"));

		CEdit *edit = (CEdit*)GetDlgItem(IDC_STEXTTIP);
		edit->ShowWindow(TRUE);//待生成二维码提示可见
		edit = (CEdit*)GetDlgItem(IDC_ETEXT);
		edit->ShowWindow(TRUE);//待生成二维码内容可见

		edit = (CEdit*)GetDlgItem(IDC_SFILEPATHTIP);
		edit->ShowWindow(FALSE);//待解析二维码文件路径提示不可见
		edit = (CEdit*)GetDlgItem(IDC_EFILEPATH);
		edit->ShowWindow(FALSE);//待解析二维码文件路径不可见
		edit = (CEdit*)GetDlgItem(IDC_BCHOOSEFILE);
		edit->ShowWindow(FALSE);//选择文件按钮不可见
	}
	else if(CodeOrDecode==1)//解密
	{
		CBModeControl.ResetContent();
		CBModeControl.AddString(_T("(自动匹配模式)"));//自动匹配模式
		CBModeControl.AddString(_T("模式一"));//RSA解密+zlib解压缩
		CBModeControl.AddString(_T("模式二"));//DES解密+zlib解压缩
		CBModeControl.SetCurSel(0);//设置第0项为显示的内容
		SetDlgItemText(IDC_BSTART,_T("开始解析二维码"));

		CEdit *edit = (CEdit*)GetDlgItem(IDC_STEXTTIP);
		edit->ShowWindow(FALSE);//待生成二维码提示不可见
		edit = (CEdit*)GetDlgItem(IDC_ETEXT);
		edit->ShowWindow(FALSE);//待生成二维码内容不可见

		edit = (CEdit*)GetDlgItem(IDC_SFILEPATHTIP);
		edit->ShowWindow(TRUE);//待解析二维码文件路径提示可见
		edit = (CEdit*)GetDlgItem(IDC_EFILEPATH);
		edit->ShowWindow(TRUE);//待解析二维码文件路径可见
		edit = (CEdit*)GetDlgItem(IDC_BCHOOSEFILE);
		edit->ShowWindow(TRUE);//选择文件按钮可见

		
	}
}


void CQRCode_And_DecodeDlg::OnBnClickedBchoosefile()
{
	// TODO: 在此添加控件通知处理程序代码
	CString szPath = _T("");

	//CFileDialog::CFileDialog( BOOL bOpenFileDialog, LPCTSTR lpszDefExt = NULL, LPCTSTR lpszFileName = NULL, DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, LPCTSTR lpszFilter = NULL, CWnd* pParentWnd = NULL);
    //参数意义如下：
    //bOpenFileDialog：为TRUE则显示打开对话框，为FALSE则显示保存对话文件对话框。 
    //lpszDefExt：指定默认的文件扩展名。 
    //lpszFileName：指定默认的文件名。 
    //dwFlags：指明一些特定风格。 
    //lpszFilter：是最重要的一个参数，它指明可供选择的文件类型和相应的扩展名。

    CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("png Files (*.png)|*.png||"), NULL);

    if (dlgFile.DoModal())
    {
        szPath = dlgFile.GetPathName();
    }
	if(!szPath.IsEmpty())
	{
	    SetDlgItemText(IDC_EFILEPATH,szPath);
	}
	else
	{
		//SetDlgItemText(IDC_EFILEPATH,_T(""));
        //AfxMessageBox(_T("无效的文件，请重新选择"),MB_OK,NULL);
	}
}


void CQRCode_And_DecodeDlg::OnBnClickedBstart()
{
	// TODO: 在此添加控件通知处理程序代码
	if(CodeOrDecode==0)//加密生成二维码
	{
		if(EditText.IsEmpty())
	    {
		    SetDlgItemText(IDC_SSTATE,_T("待生成二维码内容不能为空"));
		    AfxMessageBox(_T("待生成二维码内容不能为空"),MB_OK,NULL);
		    return;
	    }

		int nIndex = CBModeControl.GetCurSel();
		if(nIndex==0)//模式一：RSA加密+zlib压缩
		{
			SetDlgItemText(IDC_SSTATE,_T("正在生成二维码中..."));
			DeleteFile(_T("D:\\QRtemp.png"));
			char Origin_path_name[100];
			char RSA_Coded_path_name[100];
			char Zlib_Compress_path_name[100];
			char Flag_path_name[100];
			MyCreatDirectory(_T(".\\QRCode_And_Decode_Cache"));//在当前目录下新建一个临时文件夹QRCode_And_Decode_Cache
			strcpy(Origin_path_name,".\\QRCode_And_Decode_Cache\\tempfile.txt");
			strcpy(RSA_Coded_path_name,".\\QRCode_And_Decode_Cache\\tempfile(半加密临时文件1).txt");
			strcpy(Zlib_Compress_path_name,".\\QRCode_And_Decode_Cache\\tempfile(半加密临时文件2).txt");
			strcpy(Flag_path_name,".\\QRCode_And_Decode_Cache\\tempfile(已加密).txt");
			DataFromBufferToFile(EditText,MyCharToCString(Origin_path_name));//将待生成二维码内容编辑框内的内容写入文本文件
			RSA_File_Code(Origin_path_name,RSA_Coded_path_name,133,29213);//RSA算法加密 e=133 n=29213 (p=131,q=223,n=29213,e=133,d=217)
			Zlib_File_Compress(RSA_Coded_path_name,Zlib_Compress_path_name);//zlib算法压缩
			WriteFlag_Three_ASC(Zlib_Compress_path_name,Flag_path_name,'R','z','C');//RSA+zlib+Code
			DeleteFile(MyCharToLPCTSTR(Origin_path_name));//删除将待生成二维码内容编辑框内的内容写入生成的文件
			DeleteFile(MyCharToLPCTSTR(RSA_Coded_path_name));//删除RSA加密后但未进行zlib压缩时产生的临时文件
			DeleteFile(MyCharToLPCTSTR(Zlib_Compress_path_name));//删除zlib后但未写入标记的临时文件
			CString number;
		    DataFromFileToNumber(MyCharToCString(Flag_path_name),&number);//将待生成二维码的数据复制到内存中
			MyQRCode(_T("D:\\QRtemp.png"),number);
			DeleteFile(MyCharToLPCTSTR(Flag_path_name));//删除待编码二维码的临时文本文件
			RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//删除产生的临时文件夹QRCode_And_Decode_Cache
			for(int i=0;i<5;i++)
			{
				Sleep(200);
				if(MyLoadPicture(_T("D:\\QRtemp.png"))==1)//成功载入位图
				{
					break;
				}
				if(i==4)//载入5次仍未成功
				{
					SetDlgItemText(IDC_SSTATE,_T("二维码生成失败！请重新尝试"));
			        AfxMessageBox(_T("二维码生成失败！请重新尝试"),MB_OK,NULL);
					return;
				}
			}
			SetDlgItemText(IDC_SSTATE,_T("二维码成功生成！生成的二维码图片已保存到D:\\QRtemp.png文件中"));
			AfxMessageBox(_T("二维码成功生成！生成的二维码图片已保存到D:\\QRtemp.png文件中"),MB_OK,NULL);
			ShellExecute(NULL, _T("open"), _T("D:\\QRtemp.png"), NULL, NULL, SW_SHOW);
		}
		else if(nIndex==1)//模式二：DES加密+zlib压缩
		{
			SetDlgItemText(IDC_SSTATE,_T("正在生成二维码中..."));
			DeleteFile(_T("D:\\QRtemp.png"));
			char Origin_path_name[100];
			char DES_Coded_path_name[100];
			char Zlib_Compress_path_name[100];
			char Flag_path_name[100];
			MyCreatDirectory(_T(".\\QRCode_And_Decode_Cache"));//在当前目录下新建一个临时文件夹QRCode_And_Decode_Cache
			strcpy(Origin_path_name,".\\QRCode_And_Decode_Cache\\tempfile.txt");
			strcpy(DES_Coded_path_name,".\\QRCode_And_Decode_Cache\\tempfile(半加密临时文件1).txt");
			strcpy(Zlib_Compress_path_name,".\\QRCode_And_Decode_Cache\\tempfile(半加密临时文件2).txt");
			strcpy(Flag_path_name,".\\QRCode_And_Decode_Cache\\tempfile(已加密).txt");
			DataFromBufferToFile(EditText,MyCharToCString(Origin_path_name));//将待生成二维码内容编辑框内的内容写入文本文件
			const char DES_Key[]="abcdefghijklmnopqrstuvwxyz";
			des_code_forallfile(Origin_path_name,(const unsigned char*)DES_Key,strlen(DES_Key),DES_Coded_path_name);//DES算法加密
			Zlib_File_Compress(DES_Coded_path_name,Zlib_Compress_path_name);//zlib算法压缩
			WriteFlag_Three_ASC(Zlib_Compress_path_name,Flag_path_name,'D','z','C');//DES+zlib+Code
			DeleteFile(MyCharToLPCTSTR(Origin_path_name));//删除将待生成二维码内容编辑框内的内容写入生成的文件
			DeleteFile(MyCharToLPCTSTR(DES_Coded_path_name));//删除DES加密后但未进行zlib压缩时产生的临时文件
			DeleteFile(MyCharToLPCTSTR(Zlib_Compress_path_name));//删除zlib后但未写入标记的临时文件
			CString number;
		    DataFromFileToNumber(MyCharToCString(Flag_path_name),&number);//将待生成二维码的数据复制到内存中
			MyQRCode(_T("D:\\QRtemp.png"),number);
			DeleteFile(MyCharToLPCTSTR(Flag_path_name));//删除待编码二维码的临时文本文件
			RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//删除产生的临时文件夹QRCode_And_Decode_Cache
		    for(int i=0;i<5;i++)
			{
				Sleep(200);
				if(MyLoadPicture(_T("D:\\QRtemp.png"))==1)//成功载入位图
				{
					break;
				}
				if(i==4)//载入5次仍未成功
				{
					SetDlgItemText(IDC_SSTATE,_T("二维码生成失败！请重新尝试"));
			        AfxMessageBox(_T("二维码生成失败！请重新尝试"),MB_OK,NULL);
					return;
				}
			}
			SetDlgItemText(IDC_SSTATE,_T("二维码成功生成！生成的二维码图片已保存到D:\\QRtemp.png文件中"));
			AfxMessageBox(_T("二维码成功生成！生成的二维码图片已保存到D:\\QRtemp.png文件中"),MB_OK,NULL);
			ShellExecute(NULL, _T("open"), _T("D:\\QRtemp.png"), NULL, NULL, SW_SHOW);
		}
		else//生成二维码模式选择有误
		{
			SetDlgItemText(IDC_SSTATE,_T("生成二维码模式选择有误"));
			AfxMessageBox(_T("生成二维码模式选择有误"),MB_OK,NULL);
		    return;
		}
	}
	else if(CodeOrDecode==1)//解密解析二维码
	{
	    if(EditChoosePath.IsEmpty())
	    {
		    SetDlgItemText(IDC_SSTATE,_T("待解析二维码文件路径不能为空"));
		    AfxMessageBox(_T("待解析二维码文件路径不能为空"),MB_OK,NULL);
		    return;
	    }
		errno_t err_read;
		FILE *fp_read = NULL;
	    err_read = fopen_s(&fp_read, MyCStringToConstChar(EditChoosePath), "rb");
	    if (err_read != 0)
	    {
			SetDlgItemText(IDC_SSTATE,_T("待解析文件打开失败"));
			AfxMessageBox(_T("待解析文件打开失败"),MB_OK,NULL);
		    return;//文件打开失败
	    }
		fclose(fp_read);

		int nIndex = CBModeControl.GetCurSel();
		if(nIndex==0)//(自动匹配模式)：自动匹配模式
		{
			SetDlgItemText(IDC_SSTATE,_T("正在解析二维码中..."));
			DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile1.txt"));
			DeleteFile(_T("D:\\QRtemp.txt"));
			for(int i=0;i<5;i++)
			{
				if(MyLoadPicture(EditChoosePath)==1)//成功载入位图
				{
					break;
				}
				if(i==4)//载入5次仍未成功
				{
					SetDlgItemText(IDC_SSTATE,_T("二维码解析失败！请重新尝试"));
			        AfxMessageBox(_T("二维码解析失败！请重新尝试"),MB_OK,NULL);
					return;
				}
				Sleep(200);
			}
			char Origin_path_name[100];
			char Zlib_Uncompress_path_name[100];
			char RSAOrDES_Decoded_path_name[100];
			char NoFLag_path_name[100];
			MyCreatDirectory(".\\QRCode_And_Decode_Cache");//在当前目录下新建一个临时文件夹QRCode_And_Decode_Cache
			MyQRDecode(EditChoosePath,_T(".\\QRCode_And_Decode_Cache\\tempfile1.txt"));
			for(int i=0;i<5;i++)
			{
				Sleep(200);
				//判断".\\QRCode_And_Decode_Cache\\tempfile1.txt"文件是否存在
				errno_t err_read;
	            FILE *fp_read = NULL;
	            err_read = fopen_s(&fp_read, ".\\QRCode_And_Decode_Cache\\tempfile1.txt", "rb");
	            if(err_read==0)
				{
					fclose(fp_read);
					break;
				}
				if(i==4)//等待5次文件仍未成功生成
				{
					SetDlgItemText(IDC_SSTATE,_T("二维码解析失败！请重新尝试"));
			        AfxMessageBox(_T("二维码解析失败！请重新尝试"),MB_OK,NULL);
					return;
				}
			}
			CString buffer;
			DataFromFileToBuffer(_T(".\\QRCode_And_Decode_Cache\\tempfile1.txt"),&buffer);
			strcpy(Origin_path_name,".\\QRCode_And_Decode_Cache\\tempfile2.txt");
			DataFromNumberToFile(buffer,MyCharToCString(Origin_path_name));
			DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile1.txt"));
			strcpy(NoFLag_path_name,".\\QRCode_And_Decode_Cache\\tempfile2(半解密临时文件1).txt");
			strcpy(Zlib_Uncompress_path_name,".\\QRCode_And_Decode_Cache\\tempfile2(半解密临时文件2).txt");
			strcpy(RSAOrDES_Decoded_path_name,"D:\\QRtemp.txt");
			int flag_1=CheckFlag_Three_ASC(Origin_path_name,NoFLag_path_name,'R','z','C');//RSA+zlib+Code
			if(flag_1==1)
			{
				Zlib_File_Uncompress(NoFLag_path_name,Zlib_Uncompress_path_name);//zlib算法解压缩
			    RSA_File_Decode(Zlib_Uncompress_path_name,RSAOrDES_Decoded_path_name,217,29213);//RSA算法解密 d=217 n=29213 (p=131,q=223,n=29213,e=133,d=217)
			    DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
				DeleteFile(MyCharToLPCTSTR(NoFLag_path_name));//删除去除标志后但未进行RSA解密的临时文件
			    DeleteFile(MyCharToLPCTSTR(Zlib_Uncompress_path_name));//删除RSA解密后但未进行zlib压缩时产生的临时文件
			    RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//删除产生的临时文件夹QRCode_And_Decode_Cache
			    SetDlgItemText(IDC_SSTATE,_T("二维码成功解析！解析的内容已保存到D:\\QRtemp.txt文件中"));
			    AfxMessageBox(_T("二维码成功解析！解析的内容已保存到D:\\QRtemp.txt文件中"),MB_OK,NULL);
				ShellExecute(NULL, _T("open"), _T("notepad.exe"), _T("D:\\QRtemp.txt"), NULL, SW_SHOW);
				return;
			}
			else if(flag_1==-2)
			{
				DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
				RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//删除产生的临时文件夹QRCode_And_Decode_Cache
				SetDlgItemText(IDC_SSTATE,_T("无法打开待解析文件或待解析文件格式不正确，解析失败！"));
			    AfxMessageBox(_T("无法打开待解析文件或待解析文件格式不正确，解析失败！"),MB_OK,NULL);
				return;
			}
			else if(flag_1==-3)
			{
				DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
				RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//删除产生的临时文件夹QRCode_And_Decode_Cache
				SetDlgItemText(IDC_SSTATE,_T("无法写入已解析文件，解析失败！"));
			    AfxMessageBox(_T("无法写入已解析文件，解析失败！"),MB_OK,NULL);
				return;
			}
			else if(flag_1==-1)
			{
				int flag_2=CheckFlag_Three_ASC(Origin_path_name,NoFLag_path_name,'D','z','C');//DES+zlib+Code
			    if(flag_2==-2)
			    {
					DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
					RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//删除产生的临时文件夹QRCode_And_Decode_Cache
				    SetDlgItemText(IDC_SSTATE,_T("无法打开待解析文件或待解析文件格式不正确，解析失败！"));
			        AfxMessageBox(_T("无法打开待解析文件或待解析文件格式不正确，解析失败！"),MB_OK,NULL);
				    return;
			    }
			    else if(flag_2==-3)
			    {
					DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
					RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//删除产生的临时文件夹QRCode_And_Decode_Cache
				    SetDlgItemText(IDC_SSTATE,_T("无法写入已解析文件，解析失败！"));
			        AfxMessageBox(_T("无法写入已解析文件，解析失败！"),MB_OK,NULL);
				    return;
			    }
				else if(flag_2==-1)
			    {
					DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
					RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//删除产生的临时文件夹QRCode_And_Decode_Cache
				    SetDlgItemText(IDC_SSTATE,_T("待解析二维码文件不是由此程序的模式一或模式二生成的，解析失败！"));
			        AfxMessageBox(_T("待解析二维码文件不是由此程序的模式一或模式二生成的，解析失败！"),MB_OK,NULL);
				    return;
			    }
			    Zlib_File_Uncompress(NoFLag_path_name,Zlib_Uncompress_path_name);//zlib算法解压缩
			    const char DES_Key[]="abcdefghijklmnopqrstuvwxyz";
			    des_decode_forallfile(Zlib_Uncompress_path_name,(const unsigned char*)DES_Key,strlen(DES_Key),RSAOrDES_Decoded_path_name);//DES算法解密
				DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
			    DeleteFile(MyCharToLPCTSTR(NoFLag_path_name));//删除去除标志后但未进行DES解密的临时文件
			    DeleteFile(MyCharToLPCTSTR(Zlib_Uncompress_path_name));//删除DES解密后但未进行zlib压缩时产生的临时文件
			    RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//删除产生的临时文件夹Code_And_Decode_Cache
			    SetDlgItemText(IDC_SSTATE,_T("二维码成功解析！解析的内容已保存到D:\\QRtemp.txt文件中"));
			    AfxMessageBox(_T("二维码成功解析！解析的内容已保存到D:\\QRtemp.txt文件中"),MB_OK,NULL);
				ShellExecute(NULL, _T("open"), _T("notepad.exe"), _T("D:\\QRtemp.txt"), NULL, SW_SHOW);
			    }
		}
		else if(nIndex==1)//模式一：RSA解密+zlib解压缩
		{
			SetDlgItemText(IDC_SSTATE,_T("正在解析二维码中..."));
			DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile1.txt"));
			DeleteFile(_T("D:\\QRtemp.txt"));
			for(int i=0;i<5;i++)
			{
				if(MyLoadPicture(EditChoosePath)==1)//成功载入位图
				{
					break;
				}
				if(i==4)//载入5次仍未成功
				{
					SetDlgItemText(IDC_SSTATE,_T("二维码解析失败！请重新尝试"));
			        AfxMessageBox(_T("二维码解析失败！请重新尝试"),MB_OK,NULL);
					return;
				}
				Sleep(200);
			}
			char Origin_path_name[100];
			char Zlib_Uncompress_path_name[100];
			char RSA_Decoded_path_name[100];
			char NoFLag_path_name[100];
			MyCreatDirectory(".\\QRCode_And_Decode_Cache");//在当前目录下新建一个临时文件夹QRCode_And_Decode_Cache
			MyQRDecode(EditChoosePath,_T(".\\QRCode_And_Decode_Cache\\tempfile1.txt"));
			for(int i=0;i<5;i++)
			{
				Sleep(200);
				//判断".\\QRCode_And_Decode_Cache\\tempfile1.txt"文件是否存在
				errno_t err_read;
	            FILE *fp_read = NULL;
	            err_read = fopen_s(&fp_read, ".\\QRCode_And_Decode_Cache\\tempfile1.txt", "rb");
	            if(err_read==0)
				{
					fclose(fp_read);
					break;
				}
				if(i==4)//等待5次文件仍未成功生成
				{
					SetDlgItemText(IDC_SSTATE,_T("二维码解析失败！请重新尝试"));
			        AfxMessageBox(_T("二维码解析失败！请重新尝试"),MB_OK,NULL);
					return;
				}
			}
			CString buffer;
			DataFromFileToBuffer(_T(".\\QRCode_And_Decode_Cache\\tempfile1.txt"),&buffer);
			strcpy(Origin_path_name,".\\QRCode_And_Decode_Cache\\tempfile2.txt");
			DataFromNumberToFile(buffer,MyCharToCString(Origin_path_name));
			DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile1.txt"));
			strcpy(NoFLag_path_name,".\\QRCode_And_Decode_Cache\\tempfile2(半解密临时文件1).txt");
			strcpy(Zlib_Uncompress_path_name,".\\QRCode_And_Decode_Cache\\tempfile2(半解密临时文件2).txt");
			strcpy(RSA_Decoded_path_name,"D:\\QRtemp.txt");
			int flag=CheckFlag_Three_ASC(Origin_path_name,NoFLag_path_name,'R','z','C');//RSA+zlib+Code
			if(flag==-1)
			{
				DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
				RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//删除产生的临时文件夹QRCode_And_Decode_Cache
				SetDlgItemText(IDC_SSTATE,_T("待解析二维码文件不是由此程序的模式一生成的，解析失败！"));
			    AfxMessageBox(_T("待解析二维码文件不是由此程序的模式一生成的，解析失败！"),MB_OK,NULL);
				return;
			}
			else if(flag==-2)
			{
				DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
				RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//删除产生的临时文件夹QRCode_And_Decode_Cache
				SetDlgItemText(IDC_SSTATE,_T("无法打开待解析文件或待解析文件格式不正确，解析失败！"));
			    AfxMessageBox(_T("无法打开待解析文件或待解析文件格式不正确，解析失败！"),MB_OK,NULL);
				return;
			}
			else if(flag==-3)
			{
				DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
				RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//删除产生的临时文件夹QRCode_And_Decode_Cache
				SetDlgItemText(IDC_SSTATE,_T("无法写入已解析文件，解析失败！"));
			    AfxMessageBox(_T("无法写入已解析文件，解析失败！"),MB_OK,NULL);
				return;
			}
			Zlib_File_Uncompress(NoFLag_path_name,Zlib_Uncompress_path_name);//zlib算法解压缩
			RSA_File_Decode(Zlib_Uncompress_path_name,RSA_Decoded_path_name,217,29213);//RSA算法解密 d=217 n=29213 (p=131,q=223,n=29213,e=133,d=217)
			DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
			DeleteFile(MyCharToLPCTSTR(NoFLag_path_name));//删除去除标志后但未进行RSA解密的临时文件
			DeleteFile(MyCharToLPCTSTR(Zlib_Uncompress_path_name));//删除RSA解密后但未进行zlib压缩时产生的临时文件
			RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//删除产生的临时文件夹QRCode_And_Decode_Cache
			SetDlgItemText(IDC_SSTATE,_T("二维码成功解析！解析的内容已保存到D:\\QRtemp.txt文件中"));
			AfxMessageBox(_T("二维码成功解析！解析的内容已保存到D:\\QRtemp.txt文件中"),MB_OK,NULL);
			ShellExecute(NULL, _T("open"), _T("notepad.exe"), _T("D:\\QRtemp.txt"), NULL, SW_SHOW);
		}
		else if(nIndex==2)//模式二：DES解密+zlib解压缩
		{
			SetDlgItemText(IDC_SSTATE,_T("正在解析二维码中..."));
			DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile1.txt"));
			DeleteFile(_T("D:\\QRtemp.txt"));
			for(int i=0;i<5;i++)
			{
				if(MyLoadPicture(EditChoosePath)==1)//成功载入位图
				{
					break;
				}
				if(i==4)//载入5次仍未成功
				{
					SetDlgItemText(IDC_SSTATE,_T("二维码解析失败！请重新尝试"));
			        AfxMessageBox(_T("二维码解析失败！请重新尝试"),MB_OK,NULL);
					return;
				}
				Sleep(200);
			}
			char Origin_path_name[100];
			char Zlib_Uncompress_path_name[100];
			char DES_Decoded_path_name[100];
			char NoFLag_path_name[100];
			MyCreatDirectory(".\\QRCode_And_Decode_Cache");//在当前目录下新建一个临时文件夹QRCode_And_Decode_Cache
			MyQRDecode(EditChoosePath,_T(".\\QRCode_And_Decode_Cache\\tempfile1.txt"));
			for(int i=0;i<5;i++)
			{
				Sleep(200);
				//判断".\\QRCode_And_Decode_Cache\\tempfile1.txt"文件是否存在
				errno_t err_read;
	            FILE *fp_read = NULL;
	            err_read = fopen_s(&fp_read, ".\\QRCode_And_Decode_Cache\\tempfile1.txt", "rb");
	            if(err_read==0)
				{
					fclose(fp_read);
					break;
				}
				if(i==4)//等待5次文件仍未成功生成
				{
					SetDlgItemText(IDC_SSTATE,_T("二维码解析失败！请重新尝试"));
			        AfxMessageBox(_T("二维码解析失败！请重新尝试"),MB_OK,NULL);
					return;
				}
			}
			CString buffer;
			DataFromFileToBuffer(_T(".\\QRCode_And_Decode_Cache\\tempfile1.txt"),&buffer);
			strcpy(Origin_path_name,".\\QRCode_And_Decode_Cache\\tempfile2.txt");
			DataFromNumberToFile(buffer,MyCharToCString(Origin_path_name));
			DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile1.txt"));
			strcpy(NoFLag_path_name,".\\QRCode_And_Decode_Cache\\tempfile2(半解密临时文件1).txt");
			strcpy(Zlib_Uncompress_path_name,".\\QRCode_And_Decode_Cache\\tempfile2(半解密临时文件2).txt");
			strcpy(DES_Decoded_path_name,"D:\\QRtemp.txt");
			int flag=CheckFlag_Three_ASC(Origin_path_name,NoFLag_path_name,'D','z','C');//DES+zlib+Code
			if(flag==-1)
			{
				DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
				RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//删除产生的临时文件夹QRCode_And_Decode_Cache
				SetDlgItemText(IDC_SSTATE,_T("待解析二维码文件不是由此程序的模式二生成的，解析失败！"));
			    AfxMessageBox(_T("待解析二维码文件不是由此程序的模式二生成的，解析失败！"),MB_OK,NULL);
				return;
			}
			else if(flag==-2)
			{
				DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
				RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//删除产生的临时文件夹QRCode_And_Decode_Cache
				SetDlgItemText(IDC_SSTATE,_T("无法打开待解析文件或待解析文件格式不正确，解析失败！"));
			    AfxMessageBox(_T("无法打开待解析文件或待解析文件格式不正确，解析失败！"),MB_OK,NULL);
				return;
			}
			else if(flag==-3)
			{
				DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
				RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//删除产生的临时文件夹QRCode_And_Decode_Cache
				SetDlgItemText(IDC_SSTATE,_T("无法写入已解析文件，解析失败！"));
			    AfxMessageBox(_T("无法写入已解析文件，解析失败！"),MB_OK,NULL);
				return;
			}
			Zlib_File_Uncompress(NoFLag_path_name,Zlib_Uncompress_path_name);//zlib算法解压缩
			const char DES_Key[]="abcdefghijklmnopqrstuvwxyz";
			des_decode_forallfile(Zlib_Uncompress_path_name,(const unsigned char*)DES_Key,strlen(DES_Key),DES_Decoded_path_name);//DES算法解密
			DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
			DeleteFile(MyCharToLPCTSTR(NoFLag_path_name));//删除去除标志后但未进行DES解密的临时文件
			DeleteFile(MyCharToLPCTSTR(Zlib_Uncompress_path_name));//删除DES解密后但未进行zlib压缩时产生的临时文件
			RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//删除产生的临时文件夹QRCode_And_Decode_Cache
			SetDlgItemText(IDC_SSTATE,_T("二维码成功解析！解析的内容已保存到D:\\QRtemp.txt文件中"));
			AfxMessageBox(_T("二维码成功解析！解析的内容已保存到D:\\QRtemp.txt文件中"),MB_OK,NULL);
			ShellExecute(NULL, _T("open"), _T("notepad.exe"), _T("D:\\QRtemp.txt"), NULL, SW_SHOW);
		}
		else//解析二维码模式选择有误
		{
			SetDlgItemText(IDC_SSTATE,_T("解析二维码模式选择有误"));
			AfxMessageBox(_T("解析二维码模式选择有误"),MB_OK,NULL);
		    return;
		}
	}
	else//生成解析二维码选项选择有误
	{
		SetDlgItemText(IDC_SSTATE,_T("生成解析二维码选项选择有误"));
		AfxMessageBox(_T("生成解析二维码选项选择有误"),MB_OK,NULL);
	}
}


void CQRCode_And_DecodeDlg::OnBnClickedBexit()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void CQRCode_And_DecodeDlg::OnEnChangeEfilepath()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
}

void CQRCode_And_DecodeDlg::OnEnChangeEtext()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
}


int CQRCode_And_DecodeDlg::MyLoadPicture(CString picturename)
{
	//判断picturename文件是否存在
	errno_t err_read;
	FILE *fp_read = NULL;
	err_read = fopen_s(&fp_read, MyCStringToConstChar(picturename), "rb");
	if (err_read != 0)
	{
		  return -1;//文件打开失败
	}
	fclose(fp_read);

	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_SQRPICTURE);//得到Picture Control句柄  
    CImage image; 
    image.Load(picturename);
    HBITMAP hBmp = image.Detach();
    pWnd->SetBitmap(hBmp);
	if(hBmp)
	{
		DeleteObject(hBmp);
	}
	return 1;//成功
}


void CQRCode_And_DecodeDlg::MyQRCode(CString filename,CString text)
{
	CString cstr=_T("");
	cstr.Format(_T("-o %s %s"),filename,text);
	ShellExecute(NULL, _T("open"), _T("qrcode.exe"), cstr, NULL, SW_HIDE);
}


void CQRCode_And_DecodeDlg::MyQRDecode(CString QRpicturefilename,CString outdatafilename)
{
	CString cstr=_T("");
	cstr.Format(_T("/c zbarimg -q --raw %s >%s"),QRpicturefilename,outdatafilename);
	ShellExecute(NULL, _T("open"), _T("cmd.exe"), cstr, NULL, SW_HIDE);
}


int CQRCode_And_DecodeDlg::DataFromFileToNumber(CString filename,CString* number)//将数据从文件中读取转化为数字
{
	errno_t err_read;
	FILE *fp_read = NULL;
	err_read = fopen_s(&fp_read, MyCStringToConstChar(filename), "rb");
	if (err_read != 0)
	{
		  return -1;//文件打开失败
	}

	unsigned char tempchar=0;
	unsigned char data[10240];
	int i=0;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		data[3*i]=tempchar/100+'0';
		data[3*i+1]=(tempchar/10)%10+'0';
		data[3*i+2]=tempchar%10+'0';
		i++;
		if(i>3000)
		{
			return -2;//数据过大
		}
	}
	data[3*i]='\0';

	CString numbertemp(data);
	number->Format(_T("%s"),numbertemp);

	fclose(fp_read);
	return 1;//成功
}



int CQRCode_And_DecodeDlg::DataFromNumberToFile(CString number,CString filename)//将数据从数字转化到文件中
{
	const char* data=MyCStringToConstChar(number);

	if(strlen(data)%3!=1)
	{
		return -3;//数据有误
	}

	errno_t err_write;
	FILE *fp_write = NULL;
	err_write = fopen_s(&fp_write, MyCStringToConstChar(filename), "wb");
	if (err_write != 0)
	{
		  return -1;//文件打开失败
	}

	unsigned char tempchar=0;
	int i=0;
	while(data[3*i]!='\0'&&data[3*i]!=0x0d&&data[3*i]!=0x0a)
	{
		tempchar=(data[3*i]-'0')*100+(data[3*i+1]-'0')*10+(data[3*i+2]-'0');
		fprintf(fp_write,"%c",tempchar);
		i++;
		if(i>3000)
		{
			return -2;//数据过大
		}
	}

	fclose(fp_write);
	return 1;//成功
}

int CQRCode_And_DecodeDlg::DataFromBufferToFile(CString buffer,CString filename)//将数据从内存复制到文件
{
	errno_t err_write;
	FILE *fp_write = NULL;
	err_write = fopen_s(&fp_write, MyCStringToConstChar(filename), "wb");
	if (err_write != 0)
	{
		  return -1;//文件打开失败
	}

	const char* charbuffer=MyCStringToConstChar(buffer);

	int i=0;
	while(charbuffer[i]!='\0')
	{
		fprintf(fp_write,"%c",charbuffer[i]);
		i++;
	}

	fclose(fp_write);
	return 1;//成功
}


int CQRCode_And_DecodeDlg::DataFromFileToBuffer(CString filename,CString* buffer)//将数据从文件复制到内存
{
	errno_t err_read;
	FILE *fp_read = NULL;
	err_read = fopen_s(&fp_read, MyCStringToConstChar(filename), "rb");
	if (err_read != 0)
	{
		  return -1;//文件打开失败
	}

	int i=0;
	char tempchar=0;
	char charbuffer[10240];
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		charbuffer[i]=tempchar;
		i++;
	}
	charbuffer[i]='\0';

	CString cstrtemp(charbuffer);
	buffer->Format(_T("%s"),cstrtemp);

	fclose(fp_read);
	return 1;//成功
}


/*
代码说明：
代码中用了大量的以下代码判断待读取文件是否存在：

errno_t err_read;
FILE *fp_read = NULL;
err_read = fopen_s(&fp_read, filename, "rb");
if (err_read != 0)
{
    return -1;//文件打开失败
}
fclose(fp_read);

并没有使用以下函数代码进行判断：

if(!PathFileExists(filename))
{
    return -1;//文件不存在
}

是因为在代码调试过程中发现PathFileExists函数使用的是多线程机制，会导致执行此函数时继续执行下面的代码，当此函数在一个新建的线程中正在访问filename文件且未释放此文件时，
如果下面的代码使用了err_read = fopen_s(&fp_read, filename, "rb")去继续访问同一个文件，会出现err_read=13(Permission denied没有权限)的错误。
*/


/*
bug说明：
生成与解析二维码信息量不宜过大，否则会在zlib压缩与解压缩阶段的动态分配与回收内存处出现异常，导致堆被破坏，此bug尚未修复。
*/