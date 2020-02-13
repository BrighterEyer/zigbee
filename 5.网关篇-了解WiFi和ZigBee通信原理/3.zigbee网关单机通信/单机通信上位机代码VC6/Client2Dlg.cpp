// Client2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client2.h"
#include "Client2Dlg.h"
#include "Picture.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib,"Ws2_32")

CClient2Dlg *pDlg=NULL;
#define  IPDATA  "192.168.4.1" 
#define  IPPOART 5000
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClient2Dlg dialog

CClient2Dlg::CClient2Dlg(CWnd* pParent /*=NULL*/)
: CDialog(CClient2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClient2Dlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClient2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClient2Dlg)
	DDX_Control(pDX, IDC_STATIC_IMAGE, m_cImage);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClient2Dlg, CDialog)
//{{AFX_MSG_MAP(CClient2Dlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_QUIT, OnQuit)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_LED, OnLed)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_BN_CLICKED(IDC_LED2, OnLed2)
	ON_BN_CLICKED(IDC_LED3, OnLed3)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClient2Dlg message handlers

BOOL CClient2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	
	m_Bitmap[0].LoadBitmap(IDB_BITMAP_START);                //�����ʼ��
    m_Bitmap[1].LoadBitmap(IDB_BITMAP_STOP);
    m_Bitmap[2].LoadBitmap(IDB_BITMAP_LEDON);
    m_Bitmap[3].LoadBitmap(IDB_BITMAP_LEDOFF);
    m_Bitmap[4].LoadBitmap(IDB_BITMAP_OFF);

	CButton* pBtn0 =  (CButton*)GetDlgItem(IDC_PLAY);
	//pBtn0->SetBitmap(m_Bitmap[0]);
	CEdit*pEdt=(CEdit*)GetDlgItem(IDC_EDIT1);//IDC_EDIT1Ϊ��ĿID

	GetDlgItem(IDC_EDIT1)->SetWindowText(_T(IPDATA));
	GetDlgItem(IDC_EDIT2)->SetWindowText(_T("5000"));
    GetDlgItem(IDC_STATIC_CTRL)->SetWindowText(_T("�밴�����Ӱ�ť"));
	CStatic *pp = (CStatic *)GetDlgItem(IDC_QUIT);
	pp->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);
	pp->ShowWindow(SW_HIDE);
	
	WSADATA wsaData;                                         //ϵͳ��ʼ��
	WORD version=MAKEWORD(2,0);
	
	int ret=WSAStartup(version,&wsaData);
	if(ret!=0) 
	{
		MessageBox("Init  Error");
		return FALSE;
	}

	m_hSocket=NULL;
	m_IsConnected = FALSE;
	m_IsPlay = FALSE;
	m_IsTCPIPRUN = TRUE;
	m_Led1_IsOn = FALSE;  //Ĭ��LED����
	m_Led2_IsOn = FALSE;  //Ĭ��LED����
	m_Led3_IsOn = FALSE;  //Ĭ��LED����
	m_Led_IsChange = TRUE;//��һ��״̬�Ͱ��Ӳ�һ�£�����Ҫͳһ�ı�LED״̬
	m_Tcpip_Start = FALSE;//����һ�ε��߳�

	return TRUE;  
}

void CClient2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClient2Dlg::OnPaint() 
{
	CPaintDC dc0(this); 
	CBitmap m_bmpBK; 
	m_bmpBK.LoadBitmap(IDB_BITMAP_MAIN);                //����ͼƬ
	CRect rect; 
	GetClientRect(&rect);
	BITMAP  bitMap;
	m_bmpBK.GetBitmap(&bitMap);
	CDC  	dcMem; 
	dcMem.CreateCompatibleDC(&dc0); 
	dcMem.SelectObject(&m_bmpBK);
	dc0.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,bitMap.bmWidth,bitMap.bmHeight,SRCCOPY); 

	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else{
		CDialog::OnPaint();
	}


}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClient2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


/*********************
*   ��˼ͨ�� 
*********************/


UINT DealReceiveBUFF(char *str)
{

  return 0;
}

UINT LoadTCPIP(void *p)
{
		int error=0;
		CString strError;
		int ret=0;
		int rcv=0; 
		long iTemp =0;
		int TimeOut=250;                                  //���ý��ճ�ʱ

		
		char buffer[50];                                //���ջ���
		char bufferSize[50];                               //���ͼ���С
		char g_data[50];

		CString str_revdata="GETDATA\n";         
        CString str_link ="LINK\n";     
		CString str_led1g="ESPGLED1#";                    //����LED1                       
		CString str_led1k="ESPKLED1#";              
		CString str_led2g="ESPGLED2#";                    //����LED2    
		CString str_led2k="ESPKLED2#";    
		CString str_led3g="ESPGLED3#";                    //����LED3       
		CString str_led3k="ESPKLED3#";    


		BOOL LED_flag = TRUE;                  
		
		CClient2Dlg *pDlg = (CClient2Dlg*)p;              //����ָ��
		//char name1[8];
		int pic_num = 0;
	
reset:  iTemp=0;
		rcv=0; 
	    pDlg->m_hSocket = NULL;                                      //�����׽���
		pDlg->m_hSocket=socket(AF_INET,SOCK_STREAM,0);                    
		ASSERT(pDlg->m_hSocket!=NULL);     


		sockaddr_in addr;                                           //����tcp������
		addr.sin_family=AF_INET;
		addr.sin_addr.S_un.S_addr=inet_addr(IPDATA);
		addr.sin_port=htons(IPPOART);	

		
	    ret=connect(pDlg->m_hSocket,(LPSOCKADDR)&addr,sizeof(addr));
		if(ret==SOCKET_ERROR)   //���Ӵ���� 1�������
		{                                   
			strError.Format("connect error:%d",error=WSAGetLastError());
		//	AfxMessageBox(strError);
			closesocket(pDlg->m_hSocket);
			Sleep(100);
			goto reset; 
		}
		
		ret=send(pDlg->m_hSocket, str_link, 5, 0);	       
		if (ret==SOCKET_ERROR)
		{
			closesocket(pDlg->m_hSocket);
			Sleep(100);
		  	goto reset;
		}

		while(1)
		{
			memset(buffer,0,50);
			strcat(buffer,"data:");
			memset(g_data,0,50);
			if(pDlg->m_Tcpip_Start)
			{
				if(1)
				{	
					pDlg->m_Led_IsChange = FALSE;

					if(pDlg->m_Led1_IsOn)			
					{		
						strcat(g_data,str_led1k);
					}
					else								
					{
						strcat(g_data,str_led1g);   

					}
				
					if(pDlg->m_Led2_IsOn)			
					{								//������� �ı�Ƶ�״̬
						strcat(g_data,str_led2k);
					}
					else							
					{
						strcat(g_data,str_led2g);
					}

					if(pDlg->m_Led3_IsOn)			
					{								//������� �ı�Ƶ�״̬
						strcat(g_data,str_led3k);
					}
					else                  
					{
						strcat(g_data,str_led3g);
					}

					ret=send(pDlg->m_hSocket, g_data, strlen(g_data), 0);	       
					if (ret==SOCKET_ERROR)
					{
						closesocket(pDlg->m_hSocket);
						Sleep(300);
		  				goto reset;
					}
					Sleep(300);	
					iTemp++;
				}

				if(pDlg->m_IsPlay&&iTemp>10)						//�������ݲɼ� ��ŵȼ����Ӳɼ�һ��
				{   
					iTemp = 0;
					Sleep(1200);    	
					ret=send(pDlg->m_hSocket, str_revdata, 8, 0);	//���Ͳɼ�����
					if (ret==SOCKET_ERROR)
					{
						closesocket(pDlg->m_hSocket);
						Sleep(300);
						goto reset;
					}
					Sleep(1200);	
					
					setsockopt(pDlg->m_hSocket,SOL_SOCKET,SO_RCVTIMEO,(char *)&TimeOut,sizeof(TimeOut));   //���ý��ճ�ʱ
					Sleep(300);
					memset(bufferSize,0,50);									//�ɼ�����׼����
					rcv= recv(pDlg->m_hSocket, bufferSize, 50, 0);              //���ӷ�����������,������50��
					sprintf(buffer,"#%d",rcv);									//�յ��ַ�����
					strcat(buffer,bufferSize);									//buffer�ں������вɼ���Ϣ
					if(rcv>1)
					{
						sprintf(bufferSize,"tem:%s",strrchr(buffer,'#')+1);
						pDlg->GetDlgItem(IDC_STATIC_TEMP)->SetWindowText(_T(bufferSize));
						pDlg->GetDlgItem(IDC_STATIC_TEMP2)->SetWindowText(_T(bufferSize));
						pDlg->GetDlgItem(IDC_STATIC_TEMP3)->SetWindowText(_T(bufferSize));
   
					  if(strstr(buffer,"D1H")!=NULL) //���WIFIģ�鸴λ�ܽ�
					  {
						pDlg->GetDlgItem(IDC_STATIC_LED1)->SetWindowText(_T("����1��[��]"));
					  }
					  if(strstr(buffer,"D1L")!=NULL)
					  {
						pDlg->GetDlgItem(IDC_STATIC_LED1)->SetWindowText(_T("����1��[��]"));
					  }
      
					  if(strstr(buffer,"D2H")!=NULL) //���WIFIģ�鸴λ�ܽ�
					  {
						pDlg->GetDlgItem(IDC_STATIC_LED2)->SetWindowText(_T("����2��[��]"));
					  }
					  if(strstr(buffer,"D2L")!=NULL)
					  {
						pDlg->GetDlgItem(IDC_STATIC_LED2)->SetWindowText(_T("����2��[��]"));
					  }
      
					  if(strstr(buffer,"D3H")!=NULL) //���WIFIģ�鸴λ�ܽ�
					  {
						pDlg->GetDlgItem(IDC_STATIC_LED3)->SetWindowText(_T("����3��[��]"));
					  }
					  if(strstr(buffer,"D3L")!=NULL)
					  {
						pDlg->GetDlgItem(IDC_STATIC_LED3)->SetWindowText(_T("����3��[��]"));
					  }  
  
					}
				}
			}
		}					  		  
	 return 0;					  
}


/*****************************
*		��ʾͼƬ
*******************************/
BOOL CClient2Dlg::LoadBufferPic(char *pBuffer, int nSize)
{
	
	BOOL bResult = FALSE;


	
	return(bResult);
}


void CClient2Dlg::OnCancel() 
{

	if(m_hSocket)
	{
		closesocket(m_hSocket);
	}
	WSACleanup();
	CDialog::OnCancel();
}

void CClient2Dlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	CDialog::OnLButtonDown(nFlags, point);
}



/*****************************
*		�˳�
******************************/
void CClient2Dlg::OnQuit() 
{
	CString str_unlink ="UNLINX\n";  
	int ret;
	m_IsPlay=FALSE;
	m_Tcpip_Start = FALSE;
	CStatic *p = (CStatic *)GetDlgItem(IDC_QUIT);
	p->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);

	if(m_IsPlay == FALSE){
		HBITMAP hBitmap =::LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_OFF));
		p->SetBitmap(hBitmap);
	}else{
		HBITMAP hBitmap =::LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_OFF));
		p->SetBitmap(hBitmap);
		
	}
	p->ShowWindow(SW_HIDE);
	CStatic *pp = (CStatic *)GetDlgItem(IDC_PLAY);
	pp->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);
	pp->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATIC_CTRL)->SetWindowText(_T("�밴�����Ӱ�ť"));

	if(m_hSocket){
		
		ret=send(m_hSocket, str_unlink, 7, 0);	       
		if (ret==SOCKET_ERROR)
		{
			closesocket(m_hSocket);
			Sleep(100);
		}
		Sleep(300);	
		closesocket(m_hSocket);
	}

	//WSACleanup();
	//CDialog::OnCancel();
}

void CClient2Dlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

}



/*********************
*         ����
**********************/
void CClient2Dlg::OnPlay() 
{
 
    m_IsPlay=TRUE;
    m_Tcpip_Start = TRUE;
	CStatic *p = (CStatic *)GetDlgItem(IDC_PLAY);
	p->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);

	if(m_IsPlay == FALSE){
		HBITMAP hBitmap =::LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_PLAY));
		p->SetBitmap(hBitmap);

	}else{
		HBITMAP hBitmap =::LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_PLAY));
		p->SetBitmap(hBitmap);

	}

	p->ShowWindow(SW_HIDE);
	CStatic *pp = (CStatic *)GetDlgItem(IDC_QUIT);
	pp->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);
	pp->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATIC_CTRL)->SetWindowText(_T("�Ѿ�������״̬"));

    if(m_IsTCPIPRUN)
	{
		m_IsTCPIPRUN=FALSE;
		pThread=AfxBeginThread(LoadTCPIP, this);                        //�������̣߳������������
	}
		
}


/**************************
*		���ص�
***************************/
void CClient2Dlg::OnLed() 
{
    m_Led1_IsOn=!m_Led1_IsOn;
	m_Led_IsChange = TRUE;
	CStatic *p = (CStatic *)GetDlgItem(IDC_LED);
	p->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);
	if(m_Led1_IsOn == TRUE){
		HBITMAP hBitmap =::LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_LEDON));
		p->SetBitmap(hBitmap);
	}else{
		HBITMAP hBitmap =::LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_LEDOFF));
		p->SetBitmap(hBitmap);
	}
}

void CClient2Dlg::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CClient2Dlg::OnLed2() 
{
	// TODO: Add your control notification handler code here
	m_Led2_IsOn=!m_Led2_IsOn;
	m_Led_IsChange = TRUE;
	CStatic *p = (CStatic *)GetDlgItem(IDC_LED2);
	p->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);
	if(m_Led2_IsOn == TRUE){
		HBITMAP hBitmap =::LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_LEDON));
		p->SetBitmap(hBitmap);
	}else{
		HBITMAP hBitmap =::LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_LEDOFF));
		p->SetBitmap(hBitmap);
	}
}

void CClient2Dlg::OnLed3() 
{
	// TODO: Add your control notification handler code here
	m_Led3_IsOn=!m_Led3_IsOn;
	m_Led_IsChange = TRUE;
	CStatic *p = (CStatic *)GetDlgItem(IDC_LED3);
	p->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);
	if(m_Led3_IsOn == TRUE){
		HBITMAP hBitmap =::LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_LEDON));
		p->SetBitmap(hBitmap);
	}else{
		HBITMAP hBitmap =::LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_LEDOFF));
		p->SetBitmap(hBitmap);
	}
}

HBRUSH CClient2Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here

	 if (pWnd->GetDlgCtrlID() == IDC_STATIC_TEMP || pWnd->GetDlgCtrlID() == IDC_STATIC_TEMP2 || pWnd->GetDlgCtrlID() == IDC_STATIC_TEMP3)
     {
         pDC->SetTextColor(RGB(0,255,0));

		 pDC->SetBkColor(RGB(0,0,0));
		 HBRUSH b=CreateSolidBrush(RGB(0,0,0));
		 return b;
     } 
	 if(pWnd->GetDlgCtrlID() == IDC_STATIC_LED1 || pWnd->GetDlgCtrlID() == IDC_STATIC_LED2 || pWnd->GetDlgCtrlID() == IDC_STATIC_LED3 )
	 {
		 //pDC-> SetBkMode(TRANSPARENT);
		 pDC->SetTextColor(RGB(0,255,0));
		 pDC->SetBkColor(RGB(0,0,255));
		 HBRUSH b=CreateSolidBrush(RGB(0,0,255));
		 return b;
	 }
	 if( pWnd->GetDlgCtrlID() == IDC_STATIC_CTRL)
	 {
		 pDC->SetTextColor(RGB(255,0,0));
		 pDC->SetBkColor(RGB(0,0,0));
		 HBRUSH b=CreateSolidBrush(RGB(0,0,0));
		 return b;
	 }
	 return   (HBRUSH)GetStockObject(NULL_BRUSH); 
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
