// Client2Dlg.h : header file
//

#if !defined(AFX_CLIENT2DLG_H__49558BA4_82B3_48BF_9458_CFCF4836DA96__INCLUDED_)
#define AFX_CLIENT2DLG_H__49558BA4_82B3_48BF_9458_CFCF4836DA96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <Winsock2.h>
/////////////////////////////////////////////////////////////////////////////
// CClient2Dlg dialog

class CClient2Dlg : public CDialog
{
// Construction
public:
	BOOL LoadBufferPic(char *pBuffer, int nSize);
	CClient2Dlg(CWnd* pParent = NULL);	// standard constructor
    CBitmap m_Bitmap[6];
	SOCKET  m_hSocket;
	IPicture *m_picture;
	OLE_XSIZE_HIMETRIC m_width;
	OLE_YSIZE_HIMETRIC m_height;
	BOOL m_IsShow;
	BOOL m_IsConnected;
	BOOL m_IsPlay;
	BOOL m_IsTCPIPRUN;
	BOOL m_Led1_IsOn;	//LED1灯是否打开
	BOOL m_Led2_IsOn;	//LED2灯是否打开
	BOOL m_Led3_IsOn;	//LED3灯是否打开
	BOOL m_Led_IsChange;


	BOOL m_Tcpip_Start; //开启网络监听
    CWinThread* pThread;

// Dialog Data
	//{{AFX_DATA(CClient2Dlg)
	enum { IDD = IDD_CLIENT2_DIALOG };
	CButton	m_cImage;
	int		m_edit1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClient2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClient2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnQuit();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPlay();
	afx_msg void OnLed();
	afx_msg void OnChangeEdit1();
	afx_msg void OnLed2();
	afx_msg void OnLed3();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENT2DLG_H__49558BA4_82B3_48BF_9458_CFCF4836DA96__INCLUDED_)
