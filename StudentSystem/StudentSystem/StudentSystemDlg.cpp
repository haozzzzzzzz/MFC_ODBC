
// StudentSystemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentSystem.h"
#include "StudentSystemDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CStudentSystemDlg 对话框




CStudentSystemDlg::CStudentSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStudentSystemDlg::IDD, pParent)
	, m_Sno(0)
	, m_Sname(_T(""))
	, m_SearchBySno(0)
	, m_SearchBySname(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStudentSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SNO, m_Sno);
	DDX_Text(pDX, IDC_EDIT_SNAME, m_Sname);
	DDX_Text(pDX, IDC_EDIT2, m_SearchBySno);
	DDX_Text(pDX, IDC_EDIT3, m_SearchBySname);
}

BEGIN_MESSAGE_MAP(CStudentSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CStudentSystemDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CStudentSystemDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CStudentSystemDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CStudentSystemDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CStudentSystemDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CStudentSystemDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CStudentSystemDlg 消息处理程序

BOOL CStudentSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
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

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CStudentSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CStudentSystemDlg::OnPaint()
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
HCURSOR CStudentSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStudentSystemDlg::OnBnClickedOk()
{
	UpdateData();
	if (m_Sno!=0&&m_Sname!=_T(""))
	{
		student.Open();
		student.AddNew();
		student.m_Sno=m_Sno;
		student.m_Sname=m_Sname;
		student.Update();
		student.Close();
	}
	UpdateData(0);
}


void CStudentSystemDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (m_SearchBySno!=0)
	{
		m_cstrQuery.Format(_T("SELECT * FROM %s WHERE Sno = %d;"),student.GetDefaultSQL(),m_SearchBySno);
		student.Open(CRecordset::dynaset,m_cstrQuery,CRecordset::none);
		if (student.m_Sname==_T(""))
		{
			MessageBox(_T("没有记录"));
			return;
		}
		CString str;
		str.Format(_T("姓名 : %s 学号 : %d"),student.m_Sname,student.m_Sno);
		MessageBox(str);
		student.Close();
	}
	UpdateData(0);
}


void CStudentSystemDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (m_SearchBySname!=_T(""))
	{
		m_cstrQuery.Format(_T("SELECT * FROM %s WHERE Sname ='%s';"),student.GetDefaultSQL(),m_SearchBySname);
		student.Open(CRecordset::dynaset,m_cstrQuery,CRecordset::none);
		if (student.m_Sname==_T(""))
		{
			MessageBox(_T("没有记录"));
			return;
		}
		while (!student.IsEOF())
		{
			CString str;
			str.Format(_T("姓名 : %s 学号 : %d"),student.m_Sname,student.m_Sno);
			MessageBox(str);
			student.MoveNext();
		}
		student.Close();
	}
	UpdateData(0);
}


void CStudentSystemDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (m_SearchBySno!=0)
	{
		m_cstrQuery.Format(_T("SELECT * FROM %s WHERE Sno=%d;"),student.GetDefaultSQL(),m_SearchBySno);
		student.Open(CRecordset::dynaset,m_cstrQuery,CRecordset::none);
		student.Delete();
		student.Close();
	}
	UpdateData(0);
}


void CStudentSystemDlg::OnBnClickedButton4()
{
	UpdateData();
	if (m_SearchBySname!=_T(""))
	{
		m_cstrQuery.Format(_T("SELECT * FROM %s WHERE Sname='%s';"),student.GetDefaultSQL(),m_SearchBySname);
		student.Open(CRecordset::dynaset,m_cstrQuery,CRecordset::none);
		if (student.m_Sname==_T(""))
		{
			MessageBox(_T("没有记录"));
			return;
		}
		while (!student.IsEOF())
		{
			student.Delete();
			student.MoveNext();
		}
		student.Close();
	}
	UpdateData(0);
}


void CStudentSystemDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_cstrQuery.Format(_T("SELECT * FROM %s WHERE Sno = %d;"),student.GetDefaultSQL(),m_SearchBySno);
	student.Open(CRecordset::dynaset,m_cstrQuery,CRecordset::none);
	student.Edit();
	student.m_Sname=m_SearchBySname;
	student.Update();
	student.Close();
	UpdateData(0);
}
