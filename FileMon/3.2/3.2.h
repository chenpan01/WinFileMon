
// 3.2.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CMy32App:
// 有关此类的实现，请参阅 3.2.cpp
//

class CMy32App : public CWinApp
{
public:
	CMy32App();

// 重写
public:
	virtual BOOL InitInstance();
public:
	static CString GetBrowseFolderSelectPath(CWnd* pWnd); //获取 浏览对话框的选择的路径

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CMy32App theApp;