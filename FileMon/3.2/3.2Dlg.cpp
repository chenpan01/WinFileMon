// 3.2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "3.2.h"
#include "3.2Dlg.h"
#include "afxdialogex.h"
#include <ctime>
#include <list>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CRITICAL_SECTION cs;
int num = 0;
int j;


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()

public:
	
};
	


CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
	
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy32Dlg 对话框



CMy32Dlg::CMy32Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy32Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	DWORD dwExStyle = ListView_GetExtendedListViewStyle(m_showlistctrl); 
	dwExStyle |= LVS_EX_HIDELABELS; 
	ListView_SetExtendedListViewStyle(m_showlistctrl, dwExStyle);
}

void CMy32Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LIST2,m_showlistctrl);
}

BEGIN_MESSAGE_MAP(CMy32Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON4, &CMy32Dlg::OnBnClickedButton4)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CMy32Dlg::OnLvnItemchangedList2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMy32Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy32Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy32Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CMy32Dlg::OnBnClickedButton5)
END_MESSAGE_MAP()

typedef struct thread_parameter
{
	CShowListCtrl *p_show;
	//CString lPath[50];
	TCHAR       szbuf[260];
	
}TP;
TP *tp_all[50];

// CMy32Dlg 消息处理程序

BOOL CMy32Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	m_showlistctrl.InsertColumn( 0, _T(""), LVCFMT_LEFT, 940);

	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);

	// TODO: 在此添加额外的初始化代码



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy32Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy32Dlg::OnPaint()
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
HCURSOR CMy32Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMy32Dlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// TODO: 在此添加控件通知处理程序代码

	//m_showlistctrl.ShowScrollBar(SB_HORZ, FALSE);
	*pResult = 0;
}



void CMy32Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);

	//输出系统时间
	CString str;   //获取系统时间
	CTime tm;
	tm=CTime::GetCurrentTime();
	str=tm.Format("%Y年%m月%d日 %X");
	//MessageBox(str,NULL,MB_OK);
	CString str1 = L"============================== 监控已停止 "+ str + L"==============================";
	m_showlistctrl.InsertItem(m_showlistctrl.GetItemCount(),str1);
	//::WaitForSingleObject(hThread, INFINITE);
	//PostNcDestroy();
	::DestroyThreadpoolEnvironment((PTP_CALLBACK_ENVIRON)ThreadProc);
	for(int i =1;i<num;i++){
	TerminateThread(hThread[i],-1);
	::CloseHandle(hThread[i]);
	delete(tp_all[i]);
	}
	
    //DeleteCriticalSection(&cs);
}


void CMy32Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
			BYTE Buffer[1024] = {0};
			BOOL bRet = FALSE;
			char szFileName[MAX_PATH] = {0};
		FILE_NOTIFY_INFORMATION *pBuffer = (FILE_NOTIFY_INFORMATION *)Buffer;
		CStdioFile sf;
		//static int nNum = 0;
		int i;
		CString str2;
		//输出系统时间
	CString str;   //获取系统时间
	CTime tm;
	tm=CTime::GetCurrentTime();
	//str=tm.Format("%Y年%m月%d日_%X");
	str=tm.Format("%Y-%m-%d ");
	str2 = tm.Format("%X");
	str2.Replace(':','.');

	//str =_T(str);
	CString str1 = _T(".\\log\\") ;
	str1 += _T("文件监控日志");
	str1 += str + str2;
	str1 += _T(".txt");
	
CString csPath(_T(".\\log"));
 
if (!PathIsDirectory(csPath))
 
{
 
CreateDirectory(csPath, 0);//不存在则创建
 
}
 
else{
	if(sf.Open(str1,CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite|CFile::typeBinary))
	//if(sf.Open(_T(".\\log\\Log.txt"),CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite|CFile::typeBinary))
	{



		//int bufSize = WideCharToMultiByte(CP_ACP, NULL, ws, -1, NULL, 0, NULL, FALSE);
		//char *sp = new char[bufSize];
		// WideCharToMultiByte(CP_ACP, NULL, ws, -1, sp, bufSize, NULL, FALSE);


		for(i=0;i<m_showlistctrl.GetItemCount();i++)
		{
			CString strShowNum;
			strShowNum.Format(_T("第%d条记录："),i);
			CString strOut=m_showlistctrl.GetItemText(i,0)+_T("\r\n");
			int bufSize = WideCharToMultiByte(CP_ACP, NULL, strOut, -1, NULL, 0, NULL, FALSE);
			char *sp = new char[bufSize];
			 WideCharToMultiByte(CP_ACP, NULL, strOut, -1, sp, bufSize, NULL, FALSE);


			 sf.Write(sp,bufSize);
		}
		//nNum = nNum + i;
		sf.Close();
	
		MessageBox(_T("保存成功!"),_T("提示"),MB_ICONINFORMATION);
		m_showlistctrl.DeleteAllItems();
	}
		
	else
		MessageBox(_T("保存失败!"),_T("提示"),MB_ICONINFORMATION);

}
}


void CMy32Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_setmenu.DoModal();

	//把 m_dlgShow 窗口相对于 标签 向下移动30
	
	
}

void CMy32Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_showlistctrl.DeleteAllItems();
}


void CMy32Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码


	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
	CStdioFile sf;
	CString content1;
	CString *IsNull = new CString[50];
	int line = 0;
	int line1 = 0;
	if(sf.Open(_T("AppName.txt"),CFile::modeCreate | CFile::modeNoTruncate | CFile::typeBinary|CFile::modeRead))
	{
		
		long lFileLength = sf.GetLength();
		
		//TRACE("%d",lFileLength);
		if(lFileLength == 0 )
		{
			MessageBox(_T("监控项为空，请设置监控项"),_T("提示"),MB_ICONINFORMATION);
			GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
			return;
		}

		while(sf.ReadString(content1))
			{
				line1++;
				if(content1 == L"\r")
					continue;

				*IsNull = content1;
				//m_showlistctrl.InsertItem(m_showlistctrl.GetItemCount(),content1);
				//TRACE(content);
			}
		if(*IsNull == L"")
		{
			MessageBox(_T("监控项为空，请设置监控项"),_T("提示"),MB_ICONINFORMATION);
			GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
			return;
		}

		sf.Close();

	}
	

 DWORD ThreadID;
	int i =0;

	//输出系统时间
	CString str;   //获取系统时间
	CTime tm;
	tm=CTime::GetCurrentTime();
	str=tm.Format("%Y年%m月%d日 %X");
	//MessageBox(str,NULL,MB_OK);
	CString str1 = L"============================== 监控已开启 "+ str + L"==============================";
	//  m_showlistctrl.SetImageList(&m_showlistctrl,LVSIL_SMALL);//设置ImageList
	//	m_showlistctrl.InsertColumn(0,"Col 1",LVCFMT_LEFT,300,0);//设置列
		 
	m_showlistctrl.InsertItem(m_showlistctrl.GetItemCount(),str1);

	//CStdioFile sf;
			line = 0;
		    line1 = 0;
		CString content;
			//CString str1 = L"正在监控的目录为";
	m_showlistctrl.InsertItem(m_showlistctrl.GetItemCount(),L"正在监控的目录为");
	if(sf.Open(_T("AppName.txt"),CFile::modeRead|CFile::typeBinary))
	{
		

			while(sf.ReadString(content))
			{
				//line1++;
				if(content == L"\r")
					continue;
				m_showlistctrl.InsertItem(m_showlistctrl.GetItemCount(),content);
				//TRACE(content);
				
			}
			//TRACE("%d\n",line1);		
		sf.Close();
	}	

	//将路径添加到数组上
	CString cPath[50];
	if(sf.Open(_T("AppName.txt"),CFile::modeRead|CFile::typeBinary))
	{

			while(sf.ReadString(content))
			{
				line1++;
				cPath[i] = content;
				i++;
				//TRACE(content);
				
			}
			//TRACE("%d\n",line1);		
		sf.Close();
		num = i;
		i = 0;
	}	

	for(i = 1;i<num;i++)
	{
		TP* tp = new TP;
		tp_all[i] = tp;
     	tp->p_show = &m_showlistctrl;
		cPath[i].Replace('\r','\0'); 
		if(cPath[i]== L"")
			continue;

		wcscpy_s(tp->szbuf,sizeof(tp->szbuf)/sizeof(TCHAR),cPath[i]);
		//tp->lPath = (LPCWSTR)L"C:\\Users\\fa1lr4in\\Desktop";
		hThread[i] = ::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadProc,(LPVOID)tp,0,&ThreadID);
		TRACE("%d\n",ThreadID);
		//delete(tp);
	}
	
	//hThread[0] = ::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadProc,(LPVOID)tp,0,NULL);
	return ;

}

DWORD WINAPI CMy32Dlg::ThreadProc(LPVOID lParam)
{
	TP* tp1 = (TP*) lParam;
	CShowListCtrl *p_showlistctrl = tp1->p_show; 
	
	BOOL bRet = FALSE;
	BYTE Buffer[1024] = {0};
	int line = 0;
	CStdioFile sf;
	CString content;

	FILE_NOTIFY_INFORMATION *pBuffer = (FILE_NOTIFY_INFORMATION *)Buffer;
	DWORD dwByteReturn = 0;

	CString Add_Time;
	CString Modefi_Time;
	
	
	HANDLE hFile = ::CreateFile(/*L"E:\\"*/
		tp1->szbuf, FILE_LIST_DIRECTORY, 
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, 
		NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
	if(INVALID_HANDLE_VALUE == hFile)
	{
		int n = GetLastError();
		TRACE("CreateFile Error!\n");
		return 1;
	}
	
	TRACE("monitoring...\r\n");
	//p_showlistctrl->InsertItem(p_showlistctrl->GetItemCount(),L"monitoring...\r\n");
	while(TRUE)
	{
		::ZeroMemory(Buffer, sizeof(Buffer));
		bRet = ::ReadDirectoryChangesW(hFile, 
			&Buffer,
			sizeof(Buffer),
			TRUE,
			FILE_NOTIFY_CHANGE_FILE_NAME |			// 修改文件名
			FILE_NOTIFY_CHANGE_DIR_NAME  |          // 修改目录名
			FILE_NOTIFY_CHANGE_ATTRIBUTES |			// 修改文件属性
			FILE_NOTIFY_CHANGE_LAST_WRITE,			// 最后一次写入
			&dwByteReturn, NULL, NULL);				
		if(TRUE == bRet)
		{
				//输出系统时间
				CString str;   //获取系统时间
				CTime tm;
				tm=CTime::GetCurrentTime();
				str=tm.Format("%Y年%m月%d日 %X");
			char szFileName[MAX_PATH] = {0};

			// 宽字符转换为多字节
			::WideCharToMultiByte(CP_ACP,
				0,
				pBuffer->FileName,
				(pBuffer->FileNameLength / 2),
				szFileName,
				MAX_PATH,
				NULL,
				NULL);
			
			switch(pBuffer->Action)
			{
			case FILE_ACTION_ADDED:
				{
					//TRACE("添加: %s\r\n", szFileName);
					Add_Time = str;
					if(szFileName[0] != '$')
					p_showlistctrl->InsertItem(p_showlistctrl->GetItemCount(),str + L"添加:" + tp1->szbuf +(CString)szFileName);
					break;
				}
			case FILE_ACTION_REMOVED:
				{
					//TRACE("删除:%s\r\n", szFileName);
					p_showlistctrl->InsertItem(p_showlistctrl->GetItemCount(),str + L"删除:"+tp1->szbuf + (CString)szFileName);
					break;
				}
			case FILE_ACTION_MODIFIED:
				{
					//TRACE("修改:%s\r\n", szFileName);
					if(Modefi_Time == str)
						break;
					Modefi_Time = str;
					if(Add_Time == Modefi_Time)
						break;
					p_showlistctrl->InsertItem(p_showlistctrl->GetItemCount(),str + L"修改:"+tp1->szbuf + (CString)szFileName);
					break;
				}
			case FILE_ACTION_RENAMED_OLD_NAME:
				{
					//TRACE("重命名:%s", szFileName);
					CString old_name = (CString)szFileName;
					if(0 != pBuffer->NextEntryOffset)
					{
						FILE_NOTIFY_INFORMATION *tmpBuffer = (FILE_NOTIFY_INFORMATION *)
							((DWORD)pBuffer + pBuffer->NextEntryOffset);
						switch(tmpBuffer->Action)
						{
						case FILE_ACTION_RENAMED_NEW_NAME:
							{
								::ZeroMemory(szFileName, MAX_PATH);
								::WideCharToMultiByte(CP_ACP,
									0,
									tmpBuffer->FileName,
									(tmpBuffer->FileNameLength / 2),
									szFileName,
									MAX_PATH,
									NULL,
									NULL);
								//TRACE(" -> %s\r\n", szFileName);
								p_showlistctrl->InsertItem(p_showlistctrl->GetItemCount(),str + L"重命名:"+tp1->szbuf + old_name+ L"->"+(CString)szFileName);
								break;
							}
						}
					}
					break;
				}
			case FILE_ACTION_RENAMED_NEW_NAME:
				{
					//TRACE("重命名(new):%s\r\n", szFileName);
					p_showlistctrl->InsertItem(p_showlistctrl->GetItemCount(),str + L"重命名(new):" + tp1->szbuf +(CString)szFileName);
					break;
				}
			}         
		}
	}
	
	::CloseHandle(hFile);
	//LeaveCriticalSection(&cs);
	return 0;
}


