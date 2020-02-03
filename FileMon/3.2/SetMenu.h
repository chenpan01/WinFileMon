#pragma once
#include "ShowPathListCtrl.h"

// CSetMenu 对话框

class CSetMenu : public CDialogEx
{
	DECLARE_DYNAMIC(CSetMenu)

public:
	CSetMenu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetMenu();

// 对话框数据
	enum { IDD = IDD_SETMENU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();

public:
	CShowPathListCtrl m_listctrlShowPath;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton5();

	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
