
// QRCode_And_DecodeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QRCode_And_Decode.h"
#include "QRCode_And_DecodeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CQRCode_And_DecodeDlg �Ի���




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


// CQRCode_And_DecodeDlg ��Ϣ�������

BOOL CQRCode_And_DecodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CComboBox *pBox = (CComboBox *)GetDlgItem(IDC_CBMODE);
	pBox->ResetContent();
	pBox->AddString(_T("ģʽһ"));//RSA����+zlibѹ��
	pBox->AddString(_T("ģʽ��"));//DES����+7zѹ��
	pBox->SetCurSel(0);//���õ�0��Ϊ��ʾ������
	SetDlgItemText(IDC_BSTART,_T("��ʼ���ɶ�ά��"));

	CEdit *edit = (CEdit*)GetDlgItem(IDC_STEXTTIP);
	edit->ShowWindow(TRUE);//�����ɶ�ά����ʾ�ɼ�
	edit = (CEdit*)GetDlgItem(IDC_ETEXT);
	edit->ShowWindow(TRUE);//�����ɶ�ά�����ݿɼ�

	edit = (CEdit*)GetDlgItem(IDC_SFILEPATHTIP);
	edit->ShowWindow(FALSE);//��������ά���ļ�·����ʾ���ɼ�
	edit = (CEdit*)GetDlgItem(IDC_EFILEPATH);
	edit->ShowWindow(FALSE);//��������ά���ļ�·�����ɼ�
	edit = (CEdit*)GetDlgItem(IDC_BCHOOSEFILE);
	edit->ShowWindow(FALSE);//ѡ���ļ���ť���ɼ�

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CQRCode_And_DecodeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CQRCode_And_DecodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CQRCode_And_DecodeDlg::OnBnClickedRcode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(CodeOrDecode==0)//����
	{
		CBModeControl.ResetContent();
		CBModeControl.AddString(_T("ģʽһ"));//RSA����+zlibѹ��
		CBModeControl.AddString(_T("ģʽ��"));//DES����+zlibѹ��
		CBModeControl.SetCurSel(0);//���õ�0��Ϊ��ʾ������
		SetDlgItemText(IDC_BSTART,_T("��ʼ���ɶ�ά��"));

		CEdit *edit = (CEdit*)GetDlgItem(IDC_STEXTTIP);
		edit->ShowWindow(TRUE);//�����ɶ�ά����ʾ�ɼ�
		edit = (CEdit*)GetDlgItem(IDC_ETEXT);
		edit->ShowWindow(TRUE);//�����ɶ�ά�����ݿɼ�

		edit = (CEdit*)GetDlgItem(IDC_SFILEPATHTIP);
		edit->ShowWindow(FALSE);//��������ά���ļ�·����ʾ���ɼ�
		edit = (CEdit*)GetDlgItem(IDC_EFILEPATH);
		edit->ShowWindow(FALSE);//��������ά���ļ�·�����ɼ�
		edit = (CEdit*)GetDlgItem(IDC_BCHOOSEFILE);
		edit->ShowWindow(FALSE);//ѡ���ļ���ť���ɼ�
	}
	else if(CodeOrDecode==1)//����
	{
		CBModeControl.ResetContent();
		CBModeControl.AddString(_T("(�Զ�ƥ��ģʽ)"));//�Զ�ƥ��ģʽ
		CBModeControl.AddString(_T("ģʽһ"));//RSA����+zlib��ѹ��
		CBModeControl.AddString(_T("ģʽ��"));//DES����+zlib��ѹ��
		CBModeControl.SetCurSel(0);//���õ�0��Ϊ��ʾ������
		SetDlgItemText(IDC_BSTART,_T("��ʼ������ά��"));

		CEdit *edit = (CEdit*)GetDlgItem(IDC_STEXTTIP);
		edit->ShowWindow(FALSE);//�����ɶ�ά����ʾ���ɼ�
		edit = (CEdit*)GetDlgItem(IDC_ETEXT);
		edit->ShowWindow(FALSE);//�����ɶ�ά�����ݲ��ɼ�

		edit = (CEdit*)GetDlgItem(IDC_SFILEPATHTIP);
		edit->ShowWindow(TRUE);//��������ά���ļ�·����ʾ�ɼ�
		edit = (CEdit*)GetDlgItem(IDC_EFILEPATH);
		edit->ShowWindow(TRUE);//��������ά���ļ�·���ɼ�
		edit = (CEdit*)GetDlgItem(IDC_BCHOOSEFILE);
		edit->ShowWindow(TRUE);//ѡ���ļ���ť�ɼ�

		
	}
}


void CQRCode_And_DecodeDlg::OnBnClickedBchoosefile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString szPath = _T("");

	//CFileDialog::CFileDialog( BOOL bOpenFileDialog, LPCTSTR lpszDefExt = NULL, LPCTSTR lpszFileName = NULL, DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, LPCTSTR lpszFilter = NULL, CWnd* pParentWnd = NULL);
    //�����������£�
    //bOpenFileDialog��ΪTRUE����ʾ�򿪶Ի���ΪFALSE����ʾ����Ի��ļ��Ի��� 
    //lpszDefExt��ָ��Ĭ�ϵ��ļ���չ���� 
    //lpszFileName��ָ��Ĭ�ϵ��ļ����� 
    //dwFlags��ָ��һЩ�ض���� 
    //lpszFilter��������Ҫ��һ����������ָ���ɹ�ѡ����ļ����ͺ���Ӧ����չ����

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
        //AfxMessageBox(_T("��Ч���ļ���������ѡ��"),MB_OK,NULL);
	}
}


void CQRCode_And_DecodeDlg::OnBnClickedBstart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(CodeOrDecode==0)//�������ɶ�ά��
	{
		if(EditText.IsEmpty())
	    {
		    SetDlgItemText(IDC_SSTATE,_T("�����ɶ�ά�����ݲ���Ϊ��"));
		    AfxMessageBox(_T("�����ɶ�ά�����ݲ���Ϊ��"),MB_OK,NULL);
		    return;
	    }

		int nIndex = CBModeControl.GetCurSel();
		if(nIndex==0)//ģʽһ��RSA����+zlibѹ��
		{
			SetDlgItemText(IDC_SSTATE,_T("�������ɶ�ά����..."));
			DeleteFile(_T("D:\\QRtemp.png"));
			char Origin_path_name[100];
			char RSA_Coded_path_name[100];
			char Zlib_Compress_path_name[100];
			char Flag_path_name[100];
			MyCreatDirectory(_T(".\\QRCode_And_Decode_Cache"));//�ڵ�ǰĿ¼���½�һ����ʱ�ļ���QRCode_And_Decode_Cache
			strcpy(Origin_path_name,".\\QRCode_And_Decode_Cache\\tempfile.txt");
			strcpy(RSA_Coded_path_name,".\\QRCode_And_Decode_Cache\\tempfile(�������ʱ�ļ�1).txt");
			strcpy(Zlib_Compress_path_name,".\\QRCode_And_Decode_Cache\\tempfile(�������ʱ�ļ�2).txt");
			strcpy(Flag_path_name,".\\QRCode_And_Decode_Cache\\tempfile(�Ѽ���).txt");
			DataFromBufferToFile(EditText,MyCharToCString(Origin_path_name));//�������ɶ�ά�����ݱ༭���ڵ�����д���ı��ļ�
			RSA_File_Code(Origin_path_name,RSA_Coded_path_name,133,29213);//RSA�㷨���� e=133 n=29213 (p=131,q=223,n=29213,e=133,d=217)
			Zlib_File_Compress(RSA_Coded_path_name,Zlib_Compress_path_name);//zlib�㷨ѹ��
			WriteFlag_Three_ASC(Zlib_Compress_path_name,Flag_path_name,'R','z','C');//RSA+zlib+Code
			DeleteFile(MyCharToLPCTSTR(Origin_path_name));//ɾ���������ɶ�ά�����ݱ༭���ڵ�����д�����ɵ��ļ�
			DeleteFile(MyCharToLPCTSTR(RSA_Coded_path_name));//ɾ��RSA���ܺ�δ����zlibѹ��ʱ��������ʱ�ļ�
			DeleteFile(MyCharToLPCTSTR(Zlib_Compress_path_name));//ɾ��zlib��δд���ǵ���ʱ�ļ�
			CString number;
		    DataFromFileToNumber(MyCharToCString(Flag_path_name),&number);//�������ɶ�ά������ݸ��Ƶ��ڴ���
			MyQRCode(_T("D:\\QRtemp.png"),number);
			DeleteFile(MyCharToLPCTSTR(Flag_path_name));//ɾ���������ά�����ʱ�ı��ļ�
			RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//ɾ����������ʱ�ļ���QRCode_And_Decode_Cache
			for(int i=0;i<5;i++)
			{
				Sleep(200);
				if(MyLoadPicture(_T("D:\\QRtemp.png"))==1)//�ɹ�����λͼ
				{
					break;
				}
				if(i==4)//����5����δ�ɹ�
				{
					SetDlgItemText(IDC_SSTATE,_T("��ά������ʧ�ܣ������³���"));
			        AfxMessageBox(_T("��ά������ʧ�ܣ������³���"),MB_OK,NULL);
					return;
				}
			}
			SetDlgItemText(IDC_SSTATE,_T("��ά��ɹ����ɣ����ɵĶ�ά��ͼƬ�ѱ��浽D:\\QRtemp.png�ļ���"));
			AfxMessageBox(_T("��ά��ɹ����ɣ����ɵĶ�ά��ͼƬ�ѱ��浽D:\\QRtemp.png�ļ���"),MB_OK,NULL);
			ShellExecute(NULL, _T("open"), _T("D:\\QRtemp.png"), NULL, NULL, SW_SHOW);
		}
		else if(nIndex==1)//ģʽ����DES����+zlibѹ��
		{
			SetDlgItemText(IDC_SSTATE,_T("�������ɶ�ά����..."));
			DeleteFile(_T("D:\\QRtemp.png"));
			char Origin_path_name[100];
			char DES_Coded_path_name[100];
			char Zlib_Compress_path_name[100];
			char Flag_path_name[100];
			MyCreatDirectory(_T(".\\QRCode_And_Decode_Cache"));//�ڵ�ǰĿ¼���½�һ����ʱ�ļ���QRCode_And_Decode_Cache
			strcpy(Origin_path_name,".\\QRCode_And_Decode_Cache\\tempfile.txt");
			strcpy(DES_Coded_path_name,".\\QRCode_And_Decode_Cache\\tempfile(�������ʱ�ļ�1).txt");
			strcpy(Zlib_Compress_path_name,".\\QRCode_And_Decode_Cache\\tempfile(�������ʱ�ļ�2).txt");
			strcpy(Flag_path_name,".\\QRCode_And_Decode_Cache\\tempfile(�Ѽ���).txt");
			DataFromBufferToFile(EditText,MyCharToCString(Origin_path_name));//�������ɶ�ά�����ݱ༭���ڵ�����д���ı��ļ�
			const char DES_Key[]="abcdefghijklmnopqrstuvwxyz";
			des_code_forallfile(Origin_path_name,(const unsigned char*)DES_Key,strlen(DES_Key),DES_Coded_path_name);//DES�㷨����
			Zlib_File_Compress(DES_Coded_path_name,Zlib_Compress_path_name);//zlib�㷨ѹ��
			WriteFlag_Three_ASC(Zlib_Compress_path_name,Flag_path_name,'D','z','C');//DES+zlib+Code
			DeleteFile(MyCharToLPCTSTR(Origin_path_name));//ɾ���������ɶ�ά�����ݱ༭���ڵ�����д�����ɵ��ļ�
			DeleteFile(MyCharToLPCTSTR(DES_Coded_path_name));//ɾ��DES���ܺ�δ����zlibѹ��ʱ��������ʱ�ļ�
			DeleteFile(MyCharToLPCTSTR(Zlib_Compress_path_name));//ɾ��zlib��δд���ǵ���ʱ�ļ�
			CString number;
		    DataFromFileToNumber(MyCharToCString(Flag_path_name),&number);//�������ɶ�ά������ݸ��Ƶ��ڴ���
			MyQRCode(_T("D:\\QRtemp.png"),number);
			DeleteFile(MyCharToLPCTSTR(Flag_path_name));//ɾ���������ά�����ʱ�ı��ļ�
			RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//ɾ����������ʱ�ļ���QRCode_And_Decode_Cache
		    for(int i=0;i<5;i++)
			{
				Sleep(200);
				if(MyLoadPicture(_T("D:\\QRtemp.png"))==1)//�ɹ�����λͼ
				{
					break;
				}
				if(i==4)//����5����δ�ɹ�
				{
					SetDlgItemText(IDC_SSTATE,_T("��ά������ʧ�ܣ������³���"));
			        AfxMessageBox(_T("��ά������ʧ�ܣ������³���"),MB_OK,NULL);
					return;
				}
			}
			SetDlgItemText(IDC_SSTATE,_T("��ά��ɹ����ɣ����ɵĶ�ά��ͼƬ�ѱ��浽D:\\QRtemp.png�ļ���"));
			AfxMessageBox(_T("��ά��ɹ����ɣ����ɵĶ�ά��ͼƬ�ѱ��浽D:\\QRtemp.png�ļ���"),MB_OK,NULL);
			ShellExecute(NULL, _T("open"), _T("D:\\QRtemp.png"), NULL, NULL, SW_SHOW);
		}
		else//���ɶ�ά��ģʽѡ������
		{
			SetDlgItemText(IDC_SSTATE,_T("���ɶ�ά��ģʽѡ������"));
			AfxMessageBox(_T("���ɶ�ά��ģʽѡ������"),MB_OK,NULL);
		    return;
		}
	}
	else if(CodeOrDecode==1)//���ܽ�����ά��
	{
	    if(EditChoosePath.IsEmpty())
	    {
		    SetDlgItemText(IDC_SSTATE,_T("��������ά���ļ�·������Ϊ��"));
		    AfxMessageBox(_T("��������ά���ļ�·������Ϊ��"),MB_OK,NULL);
		    return;
	    }
		errno_t err_read;
		FILE *fp_read = NULL;
	    err_read = fopen_s(&fp_read, MyCStringToConstChar(EditChoosePath), "rb");
	    if (err_read != 0)
	    {
			SetDlgItemText(IDC_SSTATE,_T("�������ļ���ʧ��"));
			AfxMessageBox(_T("�������ļ���ʧ��"),MB_OK,NULL);
		    return;//�ļ���ʧ��
	    }
		fclose(fp_read);

		int nIndex = CBModeControl.GetCurSel();
		if(nIndex==0)//(�Զ�ƥ��ģʽ)���Զ�ƥ��ģʽ
		{
			SetDlgItemText(IDC_SSTATE,_T("���ڽ�����ά����..."));
			DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile1.txt"));
			DeleteFile(_T("D:\\QRtemp.txt"));
			for(int i=0;i<5;i++)
			{
				if(MyLoadPicture(EditChoosePath)==1)//�ɹ�����λͼ
				{
					break;
				}
				if(i==4)//����5����δ�ɹ�
				{
					SetDlgItemText(IDC_SSTATE,_T("��ά�����ʧ�ܣ������³���"));
			        AfxMessageBox(_T("��ά�����ʧ�ܣ������³���"),MB_OK,NULL);
					return;
				}
				Sleep(200);
			}
			char Origin_path_name[100];
			char Zlib_Uncompress_path_name[100];
			char RSAOrDES_Decoded_path_name[100];
			char NoFLag_path_name[100];
			MyCreatDirectory(".\\QRCode_And_Decode_Cache");//�ڵ�ǰĿ¼���½�һ����ʱ�ļ���QRCode_And_Decode_Cache
			MyQRDecode(EditChoosePath,_T(".\\QRCode_And_Decode_Cache\\tempfile1.txt"));
			for(int i=0;i<5;i++)
			{
				Sleep(200);
				//�ж�".\\QRCode_And_Decode_Cache\\tempfile1.txt"�ļ��Ƿ����
				errno_t err_read;
	            FILE *fp_read = NULL;
	            err_read = fopen_s(&fp_read, ".\\QRCode_And_Decode_Cache\\tempfile1.txt", "rb");
	            if(err_read==0)
				{
					fclose(fp_read);
					break;
				}
				if(i==4)//�ȴ�5���ļ���δ�ɹ�����
				{
					SetDlgItemText(IDC_SSTATE,_T("��ά�����ʧ�ܣ������³���"));
			        AfxMessageBox(_T("��ά�����ʧ�ܣ������³���"),MB_OK,NULL);
					return;
				}
			}
			CString buffer;
			DataFromFileToBuffer(_T(".\\QRCode_And_Decode_Cache\\tempfile1.txt"),&buffer);
			strcpy(Origin_path_name,".\\QRCode_And_Decode_Cache\\tempfile2.txt");
			DataFromNumberToFile(buffer,MyCharToCString(Origin_path_name));
			DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile1.txt"));
			strcpy(NoFLag_path_name,".\\QRCode_And_Decode_Cache\\tempfile2(�������ʱ�ļ�1).txt");
			strcpy(Zlib_Uncompress_path_name,".\\QRCode_And_Decode_Cache\\tempfile2(�������ʱ�ļ�2).txt");
			strcpy(RSAOrDES_Decoded_path_name,"D:\\QRtemp.txt");
			int flag_1=CheckFlag_Three_ASC(Origin_path_name,NoFLag_path_name,'R','z','C');//RSA+zlib+Code
			if(flag_1==1)
			{
				Zlib_File_Uncompress(NoFLag_path_name,Zlib_Uncompress_path_name);//zlib�㷨��ѹ��
			    RSA_File_Decode(Zlib_Uncompress_path_name,RSAOrDES_Decoded_path_name,217,29213);//RSA�㷨���� d=217 n=29213 (p=131,q=223,n=29213,e=133,d=217)
			    DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
				DeleteFile(MyCharToLPCTSTR(NoFLag_path_name));//ɾ��ȥ����־��δ����RSA���ܵ���ʱ�ļ�
			    DeleteFile(MyCharToLPCTSTR(Zlib_Uncompress_path_name));//ɾ��RSA���ܺ�δ����zlibѹ��ʱ��������ʱ�ļ�
			    RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//ɾ����������ʱ�ļ���QRCode_And_Decode_Cache
			    SetDlgItemText(IDC_SSTATE,_T("��ά��ɹ������������������ѱ��浽D:\\QRtemp.txt�ļ���"));
			    AfxMessageBox(_T("��ά��ɹ������������������ѱ��浽D:\\QRtemp.txt�ļ���"),MB_OK,NULL);
				ShellExecute(NULL, _T("open"), _T("notepad.exe"), _T("D:\\QRtemp.txt"), NULL, SW_SHOW);
				return;
			}
			else if(flag_1==-2)
			{
				DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
				RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//ɾ����������ʱ�ļ���QRCode_And_Decode_Cache
				SetDlgItemText(IDC_SSTATE,_T("�޷��򿪴������ļ���������ļ���ʽ����ȷ������ʧ�ܣ�"));
			    AfxMessageBox(_T("�޷��򿪴������ļ���������ļ���ʽ����ȷ������ʧ�ܣ�"),MB_OK,NULL);
				return;
			}
			else if(flag_1==-3)
			{
				DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
				RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//ɾ����������ʱ�ļ���QRCode_And_Decode_Cache
				SetDlgItemText(IDC_SSTATE,_T("�޷�д���ѽ����ļ�������ʧ�ܣ�"));
			    AfxMessageBox(_T("�޷�д���ѽ����ļ�������ʧ�ܣ�"),MB_OK,NULL);
				return;
			}
			else if(flag_1==-1)
			{
				int flag_2=CheckFlag_Three_ASC(Origin_path_name,NoFLag_path_name,'D','z','C');//DES+zlib+Code
			    if(flag_2==-2)
			    {
					DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
					RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//ɾ����������ʱ�ļ���QRCode_And_Decode_Cache
				    SetDlgItemText(IDC_SSTATE,_T("�޷��򿪴������ļ���������ļ���ʽ����ȷ������ʧ�ܣ�"));
			        AfxMessageBox(_T("�޷��򿪴������ļ���������ļ���ʽ����ȷ������ʧ�ܣ�"),MB_OK,NULL);
				    return;
			    }
			    else if(flag_2==-3)
			    {
					DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
					RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//ɾ����������ʱ�ļ���QRCode_And_Decode_Cache
				    SetDlgItemText(IDC_SSTATE,_T("�޷�д���ѽ����ļ�������ʧ�ܣ�"));
			        AfxMessageBox(_T("�޷�д���ѽ����ļ�������ʧ�ܣ�"),MB_OK,NULL);
				    return;
			    }
				else if(flag_2==-1)
			    {
					DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
					RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//ɾ����������ʱ�ļ���QRCode_And_Decode_Cache
				    SetDlgItemText(IDC_SSTATE,_T("��������ά���ļ������ɴ˳����ģʽһ��ģʽ�����ɵģ�����ʧ�ܣ�"));
			        AfxMessageBox(_T("��������ά���ļ������ɴ˳����ģʽһ��ģʽ�����ɵģ�����ʧ�ܣ�"),MB_OK,NULL);
				    return;
			    }
			    Zlib_File_Uncompress(NoFLag_path_name,Zlib_Uncompress_path_name);//zlib�㷨��ѹ��
			    const char DES_Key[]="abcdefghijklmnopqrstuvwxyz";
			    des_decode_forallfile(Zlib_Uncompress_path_name,(const unsigned char*)DES_Key,strlen(DES_Key),RSAOrDES_Decoded_path_name);//DES�㷨����
				DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
			    DeleteFile(MyCharToLPCTSTR(NoFLag_path_name));//ɾ��ȥ����־��δ����DES���ܵ���ʱ�ļ�
			    DeleteFile(MyCharToLPCTSTR(Zlib_Uncompress_path_name));//ɾ��DES���ܺ�δ����zlibѹ��ʱ��������ʱ�ļ�
			    RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//ɾ����������ʱ�ļ���Code_And_Decode_Cache
			    SetDlgItemText(IDC_SSTATE,_T("��ά��ɹ������������������ѱ��浽D:\\QRtemp.txt�ļ���"));
			    AfxMessageBox(_T("��ά��ɹ������������������ѱ��浽D:\\QRtemp.txt�ļ���"),MB_OK,NULL);
				ShellExecute(NULL, _T("open"), _T("notepad.exe"), _T("D:\\QRtemp.txt"), NULL, SW_SHOW);
			    }
		}
		else if(nIndex==1)//ģʽһ��RSA����+zlib��ѹ��
		{
			SetDlgItemText(IDC_SSTATE,_T("���ڽ�����ά����..."));
			DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile1.txt"));
			DeleteFile(_T("D:\\QRtemp.txt"));
			for(int i=0;i<5;i++)
			{
				if(MyLoadPicture(EditChoosePath)==1)//�ɹ�����λͼ
				{
					break;
				}
				if(i==4)//����5����δ�ɹ�
				{
					SetDlgItemText(IDC_SSTATE,_T("��ά�����ʧ�ܣ������³���"));
			        AfxMessageBox(_T("��ά�����ʧ�ܣ������³���"),MB_OK,NULL);
					return;
				}
				Sleep(200);
			}
			char Origin_path_name[100];
			char Zlib_Uncompress_path_name[100];
			char RSA_Decoded_path_name[100];
			char NoFLag_path_name[100];
			MyCreatDirectory(".\\QRCode_And_Decode_Cache");//�ڵ�ǰĿ¼���½�һ����ʱ�ļ���QRCode_And_Decode_Cache
			MyQRDecode(EditChoosePath,_T(".\\QRCode_And_Decode_Cache\\tempfile1.txt"));
			for(int i=0;i<5;i++)
			{
				Sleep(200);
				//�ж�".\\QRCode_And_Decode_Cache\\tempfile1.txt"�ļ��Ƿ����
				errno_t err_read;
	            FILE *fp_read = NULL;
	            err_read = fopen_s(&fp_read, ".\\QRCode_And_Decode_Cache\\tempfile1.txt", "rb");
	            if(err_read==0)
				{
					fclose(fp_read);
					break;
				}
				if(i==4)//�ȴ�5���ļ���δ�ɹ�����
				{
					SetDlgItemText(IDC_SSTATE,_T("��ά�����ʧ�ܣ������³���"));
			        AfxMessageBox(_T("��ά�����ʧ�ܣ������³���"),MB_OK,NULL);
					return;
				}
			}
			CString buffer;
			DataFromFileToBuffer(_T(".\\QRCode_And_Decode_Cache\\tempfile1.txt"),&buffer);
			strcpy(Origin_path_name,".\\QRCode_And_Decode_Cache\\tempfile2.txt");
			DataFromNumberToFile(buffer,MyCharToCString(Origin_path_name));
			DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile1.txt"));
			strcpy(NoFLag_path_name,".\\QRCode_And_Decode_Cache\\tempfile2(�������ʱ�ļ�1).txt");
			strcpy(Zlib_Uncompress_path_name,".\\QRCode_And_Decode_Cache\\tempfile2(�������ʱ�ļ�2).txt");
			strcpy(RSA_Decoded_path_name,"D:\\QRtemp.txt");
			int flag=CheckFlag_Three_ASC(Origin_path_name,NoFLag_path_name,'R','z','C');//RSA+zlib+Code
			if(flag==-1)
			{
				DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
				RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//ɾ����������ʱ�ļ���QRCode_And_Decode_Cache
				SetDlgItemText(IDC_SSTATE,_T("��������ά���ļ������ɴ˳����ģʽһ���ɵģ�����ʧ�ܣ�"));
			    AfxMessageBox(_T("��������ά���ļ������ɴ˳����ģʽһ���ɵģ�����ʧ�ܣ�"),MB_OK,NULL);
				return;
			}
			else if(flag==-2)
			{
				DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
				RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//ɾ����������ʱ�ļ���QRCode_And_Decode_Cache
				SetDlgItemText(IDC_SSTATE,_T("�޷��򿪴������ļ���������ļ���ʽ����ȷ������ʧ�ܣ�"));
			    AfxMessageBox(_T("�޷��򿪴������ļ���������ļ���ʽ����ȷ������ʧ�ܣ�"),MB_OK,NULL);
				return;
			}
			else if(flag==-3)
			{
				DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
				RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//ɾ����������ʱ�ļ���QRCode_And_Decode_Cache
				SetDlgItemText(IDC_SSTATE,_T("�޷�д���ѽ����ļ�������ʧ�ܣ�"));
			    AfxMessageBox(_T("�޷�д���ѽ����ļ�������ʧ�ܣ�"),MB_OK,NULL);
				return;
			}
			Zlib_File_Uncompress(NoFLag_path_name,Zlib_Uncompress_path_name);//zlib�㷨��ѹ��
			RSA_File_Decode(Zlib_Uncompress_path_name,RSA_Decoded_path_name,217,29213);//RSA�㷨���� d=217 n=29213 (p=131,q=223,n=29213,e=133,d=217)
			DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
			DeleteFile(MyCharToLPCTSTR(NoFLag_path_name));//ɾ��ȥ����־��δ����RSA���ܵ���ʱ�ļ�
			DeleteFile(MyCharToLPCTSTR(Zlib_Uncompress_path_name));//ɾ��RSA���ܺ�δ����zlibѹ��ʱ��������ʱ�ļ�
			RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//ɾ����������ʱ�ļ���QRCode_And_Decode_Cache
			SetDlgItemText(IDC_SSTATE,_T("��ά��ɹ������������������ѱ��浽D:\\QRtemp.txt�ļ���"));
			AfxMessageBox(_T("��ά��ɹ������������������ѱ��浽D:\\QRtemp.txt�ļ���"),MB_OK,NULL);
			ShellExecute(NULL, _T("open"), _T("notepad.exe"), _T("D:\\QRtemp.txt"), NULL, SW_SHOW);
		}
		else if(nIndex==2)//ģʽ����DES����+zlib��ѹ��
		{
			SetDlgItemText(IDC_SSTATE,_T("���ڽ�����ά����..."));
			DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile1.txt"));
			DeleteFile(_T("D:\\QRtemp.txt"));
			for(int i=0;i<5;i++)
			{
				if(MyLoadPicture(EditChoosePath)==1)//�ɹ�����λͼ
				{
					break;
				}
				if(i==4)//����5����δ�ɹ�
				{
					SetDlgItemText(IDC_SSTATE,_T("��ά�����ʧ�ܣ������³���"));
			        AfxMessageBox(_T("��ά�����ʧ�ܣ������³���"),MB_OK,NULL);
					return;
				}
				Sleep(200);
			}
			char Origin_path_name[100];
			char Zlib_Uncompress_path_name[100];
			char DES_Decoded_path_name[100];
			char NoFLag_path_name[100];
			MyCreatDirectory(".\\QRCode_And_Decode_Cache");//�ڵ�ǰĿ¼���½�һ����ʱ�ļ���QRCode_And_Decode_Cache
			MyQRDecode(EditChoosePath,_T(".\\QRCode_And_Decode_Cache\\tempfile1.txt"));
			for(int i=0;i<5;i++)
			{
				Sleep(200);
				//�ж�".\\QRCode_And_Decode_Cache\\tempfile1.txt"�ļ��Ƿ����
				errno_t err_read;
	            FILE *fp_read = NULL;
	            err_read = fopen_s(&fp_read, ".\\QRCode_And_Decode_Cache\\tempfile1.txt", "rb");
	            if(err_read==0)
				{
					fclose(fp_read);
					break;
				}
				if(i==4)//�ȴ�5���ļ���δ�ɹ�����
				{
					SetDlgItemText(IDC_SSTATE,_T("��ά�����ʧ�ܣ������³���"));
			        AfxMessageBox(_T("��ά�����ʧ�ܣ������³���"),MB_OK,NULL);
					return;
				}
			}
			CString buffer;
			DataFromFileToBuffer(_T(".\\QRCode_And_Decode_Cache\\tempfile1.txt"),&buffer);
			strcpy(Origin_path_name,".\\QRCode_And_Decode_Cache\\tempfile2.txt");
			DataFromNumberToFile(buffer,MyCharToCString(Origin_path_name));
			DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile1.txt"));
			strcpy(NoFLag_path_name,".\\QRCode_And_Decode_Cache\\tempfile2(�������ʱ�ļ�1).txt");
			strcpy(Zlib_Uncompress_path_name,".\\QRCode_And_Decode_Cache\\tempfile2(�������ʱ�ļ�2).txt");
			strcpy(DES_Decoded_path_name,"D:\\QRtemp.txt");
			int flag=CheckFlag_Three_ASC(Origin_path_name,NoFLag_path_name,'D','z','C');//DES+zlib+Code
			if(flag==-1)
			{
				DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
				RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//ɾ����������ʱ�ļ���QRCode_And_Decode_Cache
				SetDlgItemText(IDC_SSTATE,_T("��������ά���ļ������ɴ˳����ģʽ�����ɵģ�����ʧ�ܣ�"));
			    AfxMessageBox(_T("��������ά���ļ������ɴ˳����ģʽ�����ɵģ�����ʧ�ܣ�"),MB_OK,NULL);
				return;
			}
			else if(flag==-2)
			{
				DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
				RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//ɾ����������ʱ�ļ���QRCode_And_Decode_Cache
				SetDlgItemText(IDC_SSTATE,_T("�޷��򿪴������ļ���������ļ���ʽ����ȷ������ʧ�ܣ�"));
			    AfxMessageBox(_T("�޷��򿪴������ļ���������ļ���ʽ����ȷ������ʧ�ܣ�"),MB_OK,NULL);
				return;
			}
			else if(flag==-3)
			{
				DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
				RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//ɾ����������ʱ�ļ���QRCode_And_Decode_Cache
				SetDlgItemText(IDC_SSTATE,_T("�޷�д���ѽ����ļ�������ʧ�ܣ�"));
			    AfxMessageBox(_T("�޷�д���ѽ����ļ�������ʧ�ܣ�"),MB_OK,NULL);
				return;
			}
			Zlib_File_Uncompress(NoFLag_path_name,Zlib_Uncompress_path_name);//zlib�㷨��ѹ��
			const char DES_Key[]="abcdefghijklmnopqrstuvwxyz";
			des_decode_forallfile(Zlib_Uncompress_path_name,(const unsigned char*)DES_Key,strlen(DES_Key),DES_Decoded_path_name);//DES�㷨����
			DeleteFile(_T(".\\QRCode_And_Decode_Cache\\tempfile2.txt"));
			DeleteFile(MyCharToLPCTSTR(NoFLag_path_name));//ɾ��ȥ����־��δ����DES���ܵ���ʱ�ļ�
			DeleteFile(MyCharToLPCTSTR(Zlib_Uncompress_path_name));//ɾ��DES���ܺ�δ����zlibѹ��ʱ��������ʱ�ļ�
			RemoveDirectory(_T(".\\QRCode_And_Decode_Cache"));//ɾ����������ʱ�ļ���QRCode_And_Decode_Cache
			SetDlgItemText(IDC_SSTATE,_T("��ά��ɹ������������������ѱ��浽D:\\QRtemp.txt�ļ���"));
			AfxMessageBox(_T("��ά��ɹ������������������ѱ��浽D:\\QRtemp.txt�ļ���"),MB_OK,NULL);
			ShellExecute(NULL, _T("open"), _T("notepad.exe"), _T("D:\\QRtemp.txt"), NULL, SW_SHOW);
		}
		else//������ά��ģʽѡ������
		{
			SetDlgItemText(IDC_SSTATE,_T("������ά��ģʽѡ������"));
			AfxMessageBox(_T("������ά��ģʽѡ������"),MB_OK,NULL);
		    return;
		}
	}
	else//���ɽ�����ά��ѡ��ѡ������
	{
		SetDlgItemText(IDC_SSTATE,_T("���ɽ�����ά��ѡ��ѡ������"));
		AfxMessageBox(_T("���ɽ�����ά��ѡ��ѡ������"),MB_OK,NULL);
	}
}


void CQRCode_And_DecodeDlg::OnBnClickedBexit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}


void CQRCode_And_DecodeDlg::OnEnChangeEfilepath()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}

void CQRCode_And_DecodeDlg::OnEnChangeEtext()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}


int CQRCode_And_DecodeDlg::MyLoadPicture(CString picturename)
{
	//�ж�picturename�ļ��Ƿ����
	errno_t err_read;
	FILE *fp_read = NULL;
	err_read = fopen_s(&fp_read, MyCStringToConstChar(picturename), "rb");
	if (err_read != 0)
	{
		  return -1;//�ļ���ʧ��
	}
	fclose(fp_read);

	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_SQRPICTURE);//�õ�Picture Control���  
    CImage image; 
    image.Load(picturename);
    HBITMAP hBmp = image.Detach();
    pWnd->SetBitmap(hBmp);
	if(hBmp)
	{
		DeleteObject(hBmp);
	}
	return 1;//�ɹ�
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


int CQRCode_And_DecodeDlg::DataFromFileToNumber(CString filename,CString* number)//�����ݴ��ļ��ж�ȡת��Ϊ����
{
	errno_t err_read;
	FILE *fp_read = NULL;
	err_read = fopen_s(&fp_read, MyCStringToConstChar(filename), "rb");
	if (err_read != 0)
	{
		  return -1;//�ļ���ʧ��
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
			return -2;//���ݹ���
		}
	}
	data[3*i]='\0';

	CString numbertemp(data);
	number->Format(_T("%s"),numbertemp);

	fclose(fp_read);
	return 1;//�ɹ�
}



int CQRCode_And_DecodeDlg::DataFromNumberToFile(CString number,CString filename)//�����ݴ�����ת�����ļ���
{
	const char* data=MyCStringToConstChar(number);

	if(strlen(data)%3!=1)
	{
		return -3;//��������
	}

	errno_t err_write;
	FILE *fp_write = NULL;
	err_write = fopen_s(&fp_write, MyCStringToConstChar(filename), "wb");
	if (err_write != 0)
	{
		  return -1;//�ļ���ʧ��
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
			return -2;//���ݹ���
		}
	}

	fclose(fp_write);
	return 1;//�ɹ�
}

int CQRCode_And_DecodeDlg::DataFromBufferToFile(CString buffer,CString filename)//�����ݴ��ڴ渴�Ƶ��ļ�
{
	errno_t err_write;
	FILE *fp_write = NULL;
	err_write = fopen_s(&fp_write, MyCStringToConstChar(filename), "wb");
	if (err_write != 0)
	{
		  return -1;//�ļ���ʧ��
	}

	const char* charbuffer=MyCStringToConstChar(buffer);

	int i=0;
	while(charbuffer[i]!='\0')
	{
		fprintf(fp_write,"%c",charbuffer[i]);
		i++;
	}

	fclose(fp_write);
	return 1;//�ɹ�
}


int CQRCode_And_DecodeDlg::DataFromFileToBuffer(CString filename,CString* buffer)//�����ݴ��ļ����Ƶ��ڴ�
{
	errno_t err_read;
	FILE *fp_read = NULL;
	err_read = fopen_s(&fp_read, MyCStringToConstChar(filename), "rb");
	if (err_read != 0)
	{
		  return -1;//�ļ���ʧ��
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
	return 1;//�ɹ�
}


/*
����˵����
���������˴��������´����жϴ���ȡ�ļ��Ƿ���ڣ�

errno_t err_read;
FILE *fp_read = NULL;
err_read = fopen_s(&fp_read, filename, "rb");
if (err_read != 0)
{
    return -1;//�ļ���ʧ��
}
fclose(fp_read);

��û��ʹ�����º�����������жϣ�

if(!PathFileExists(filename))
{
    return -1;//�ļ�������
}

����Ϊ�ڴ�����Թ����з���PathFileExists����ʹ�õ��Ƕ��̻߳��ƣ��ᵼ��ִ�д˺���ʱ����ִ������Ĵ��룬���˺�����һ���½����߳������ڷ���filename�ļ���δ�ͷŴ��ļ�ʱ��
�������Ĵ���ʹ����err_read = fopen_s(&fp_read, filename, "rb")ȥ��������ͬһ���ļ��������err_read=13(Permission deniedû��Ȩ��)�Ĵ���
*/


/*
bug˵����
�����������ά����Ϣ�����˹��󣬷������zlibѹ�����ѹ���׶εĶ�̬����������ڴ洦�����쳣�����¶ѱ��ƻ�����bug��δ�޸���
*/