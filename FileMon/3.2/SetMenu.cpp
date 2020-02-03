// SetMenu.cpp : 实现文件
//

#include "stdafx.h"
#include "3.2.h"
#include "SetMenu.h"
#include "afxdialogex.h"


// CSetMenu 对话框

IMPLEMENT_DYNAMIC(CSetMenu, CDialogEx)

CSetMenu::CSetMenu(CWnd* pParent /*=NULL*/)
    : CDialogEx(CSetMenu::IDD, pParent)
{

}

CSetMenu::~CSetMenu()
{
}

void CSetMenu::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX,IDC_LIST1,m_listctrlShowPath);
}


BEGIN_MESSAGE_MAP(CSetMenu, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON3, &CSetMenu::OnBnClickedButton3)

    ON_BN_CLICKED(IDC_BUTTON5, &CSetMenu::OnBnClickedButton5)
    ON_BN_CLICKED(IDC_BUTTON6, &CSetMenu::OnBnClickedButton6)
    ON_BN_CLICKED(IDC_BUTTON7, &CSetMenu::OnBnClickedButton7)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CSetMenu::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CSetMenu 消息处理程序




void CSetMenu::OnBnClickedButton3()
{
    // TODO: 在此添加控件通知处理程序代码
    CString strPath = CMy32App::GetBrowseFolderSelectPath(this);
    if(strPath != L"")
    {
        //在列表上插入
        m_listctrlShowPath.InsertItem(m_listctrlShowPath.GetItemCount(),strPath);
    }
}


BOOL CSetMenu::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    m_listctrlShowPath.SetExtendedStyle(LVS_EX_CHECKBOXES); //添加复选按钮

    CStdioFile sf;
    int line = 0;
    int line1 = 0;
    CString content;
    //CString str1 = L"正在监控的目录为";
    //m_listctrlShowPath.InsertItem(m_listctrlShowPath.GetItemCount(),L"正在监控的目录为");
    if(sf.Open(_T("AppName.txt"),CFile::modeRead|CFile::typeBinary))
    {


        while(sf.ReadString(content))
        {
            line1++;
            if(content == L"\r")
                continue;
            m_listctrlShowPath.InsertItem(m_listctrlShowPath.GetItemCount(),content);
            //TRACE(content);

        }
        //TRACE("%d\n",line1);
        sf.Close();
    }



    return TRUE; // return TRUE unless you set the focus to a control

}


void CSetMenu::OnBnClickedButton5()
{
    // TODO: 在此添加控件通知处理程序代码
    for(int i = 0; i<m_listctrlShowPath.GetItemCount(); i++)
    {
        //判断i 这一项是否选中
        if(m_listctrlShowPath.GetCheck(i) == TRUE)
            //删除这一项
            m_listctrlShowPath.DeleteItem(i);
    }

}


void CSetMenu::OnBnClickedButton6()
{
    // TODO: 在此添加控件通知处理程序代码
    int nHeadNum = m_listctrlShowPath.GetItemCount();
    TRACE("%d\n",nHeadNum);


    CStdioFile sf;
    if(sf.Open(_T("AppName.txt"),CFile::modeCreate | CFile::modeWrite|CFile::typeBinary))
    {
        sf.WriteString(L"\r\n");
        for(int i=0; i<m_listctrlShowPath.GetItemCount(); i++)
        {
            CString strShowNum;
            strShowNum.Format(_T("第%d条记录："),i);
            //CString strOut=strShowNum+_T("\t\t")+m_listctrlShowPath.GetItemText(i,0) + _T("      \t\t")+m_listctrlShowPath.GetItemText(i,1)+_T("\r\n");
            CString strOut=m_listctrlShowPath.GetItemText(i,0)+L"\r\n";

            sf.WriteString(strOut);
        }
        sf.Close();
        MessageBox(_T("保存成功!"),_T("提示"),MB_ICONINFORMATION);
    }

    else
        MessageBox(_T("保存失败!"),_T("提示"),MB_ICONINFORMATION);


}


void CSetMenu::OnBnClickedButton7()
{
    // TODO: 在此添加控件通知处理程序代码
    EndDialog(0);
}


void CSetMenu::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    *pResult = 0;
    // TODO: 在此添加控件通知处理程序代码



    *pResult = 0;
}
