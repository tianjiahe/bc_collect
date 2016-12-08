// GraphicView.cpp : implementation file
//

#include "stdafx.h"
#include "collect.h"
#include "GraphicView.h"


#pragma comment(lib,"PEGRP32C.lib")

#define GetRandom(min,max) ((rand()%(int)(((max)+1)-(min)))+(min))

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphicView

IMPLEMENT_DYNCREATE(CGraphicView, CView)

CGraphicView::CGraphicView()
{
}

CGraphicView::~CGraphicView()
{
}


BEGIN_MESSAGE_MAP(CGraphicView, CView)
	//{{AFX_MSG_MAP(CGraphicView)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_COMMAND(ID_TEST, OnTest)
	ON_BN_CLICKED(IDC_BUTTON_DATA_SAVE, OnButtonDataSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicView drawing

void CGraphicView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicView diagnostics

#ifdef _DEBUG
void CGraphicView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphicView message handlers

void CGraphicView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
    AfxGetApp()->GetMainWnd()->SetWindowText(_T("��Ʒ�������� V1.0"));
}

BOOL CGraphicView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	//return CView::OnEraseBkgnd(pDC);
	return TRUE;
}

void CGraphicView::OnSize(UINT nType, int cx, int cy) 
{

	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(m_hPE)
	{	
		PEdestroy(m_hPE);
	}

	//CreateSimpleGraph(); 	//CreateSimpleSGraph();	
	OnDrawgraph();
}

void CGraphicView::OnDrawgraph() 
{  
	if(m_hPE)
	{
		PEdestroy(m_hPE);
		Invalidate();
	}

   //! Chart fills 100 points but x axis is initially
   //! manually scaled.  Once 100 point have been passed,
   //! the chart switches to autoscaling the x axis.

   RECT rect;
   GetClientRect( &rect );                                               // ���ؿͻ����ߴ�     

   m_hPE = PEcreate(PECONTROL_SGRAPH, WS_VISIBLE, &rect, m_hWnd, 1001);  // �ͻ�������ͼ�ζ��󣬷��ؾ��

   PEnset(m_hPE,  PEP_nSUBSETS,     3   );									 // �����Ӽ��ĸ������������������Ӽ���
   PEnset(m_hPE,  PEP_nPOINTS,      100 );									 // �����Ӽ�����  

   PEszset(m_hPE, PEP_szMAINTITLE,  "��Ʒ������");					// ����������⣬
   PEszset(m_hPE, PEP_szSUBTITLE,   "���00001"   );    				// �ӱ��⣬��ʶ�������Ļ������������
   PEszset(m_hPE, PEP_szYAXISLABEL, "͸����(%)"   );                    // ��ΪY���ǩ�ı�
   PEszset(m_hPE, PEP_szXAXISLABEL, "����(nm)"    );                    // ��ΪX���ǩ�ı�
   
   PEnset( m_hPE, PEP_nDATASHADOWS,  PEDS_NONE    );                    // ����������ʾЧ����/��/��Ӱ/3D/ //PEDS_3D//	PEDS_SHADOWS
  
   //PEnset(m_hPE, PEP_nMANUALSCALECONTROLY, PEMSC_MIN);                // Y����ı��,PEMSC_MIN-����������Сֵ�ƶ�,PEMSC_MAX�������ֵ
   PEnset(m_hPE, PEP_nMANUALSCALECONTROLY, PEMSC_MINMAX);               // Y����ı��,PEMSC_MINMAX-��ʾYȫ����
   double arg = 0.0F;
   PEvset(m_hPE, PEP_fMANUALMINY,          &arg, 1);                    // ����Y�������ʼ�� 
   arg = 100.0F;
   PEvset(m_hPE, PEP_fMANUALMAXY,          &arg, 1);                    // ����Y�������ֹ��  
   
   // Set Manual X scale //
   PEnset(m_hPE, PEP_nMANUALSCALECONTROLX, PEMSC_MINMAX);                 // X��ı�ǣ���ʽ��MINMAX-ȫ���̣�MIN������Сֵ��MAM-�������ֵ  
   arg = 1.0F;
   PEvset(m_hPE, PEP_fMANUALMINX, &arg, 1);                            // X�������
   arg = 100.0F;
   PEvset(m_hPE, PEP_fMANUALMAXX, &arg, 1);                            // X�����յ�

/*   �������ã�2������Ч����һ����
   int nTmpStyle;
   nTmpStyle = PELT_THINSOLID;
   PEvsetcell(m_hPE, PEP_naSUBSETLINETYPES, 0, &nTmpStyle); 
   nTmpStyle = PELT_DASH;
   PEvsetcell(m_hPE, PEP_naSUBSETLINETYPES, 1, &nTmpStyle); 
   nTmpStyle = PELT_DOT;
   PEvsetcell(m_hPE, PEP_naSUBSETLINETYPES, 2, &nTmpStyle);
*/
   int nTmpStyle[3];
   nTmpStyle[0] = PELT_THINSOLID;
   nTmpStyle[1] = PELT_DOT;//PELT_DASH
   nTmpStyle[2] = PELT_DOT;//PELT_DASH;//;
   PEvset( m_hPE,PEP_naSUBSETLINETYPES,nTmpStyle,3);

/*
   DWORD col = RGB(255, 0, 0);                              // ���ò�ͬ���ߵ���ɫ
   PEvsetcell(m_hPE, PEP_dwaSUBSETCOLORS, 0, &col); 
   col = RGB( 0, 255, 0 );
   PEvsetcell(m_hPE, PEP_dwaSUBSETCOLORS, 1, &col);
   col = RGB( 0, 0, 255 );
   PEvsetcell(m_hPE, PEP_dwaSUBSETCOLORS, 2, &col);
*/
   DWORD col[3];
   col[0] = RGB(255, 255,   0   );
   col[1] = RGB(255, 255,   255 );
   col[2] = RGB(255,   0,   0   ); 
   PEvset(m_hPE,PEP_dwaSUBSETCOLORS, col, 3);                  // �������߱�����ɫ

   //PEvset(m_hPE, PEP_naSUBSETLINETYPES, PELT_THINSOLID, 0);
   
   char szSubsets[] = "����\t��Ʒ\t����\t";
   PEvset (m_hPE, PEP_szaSUBSETLABELS, szSubsets,3);
   
   // �Ӽ��ı�ʶ
   //char *pszSubsets[3] ={"��Ʒ","����","����"};
   //PEvset(m_hPE, PEP_szaSUBSETLABELS, pszSubsets, 3);
   //PEvsetcell( m_hPE, PEP_szaSUBSETLABELS, 0, "��Ʒ" );
   //PEvsetcell( m_hPE, PEP_szaSUBSETLABELS, 1, "����" );
   //PEvsetcell( m_hPE, PEP_szaSUBSETLABELS, 2, "����" );

   // Set Various Other Properties ///
   PEnset(m_hPE, PEP_bBITMAPGRADIENTMODE,     TRUE );     // ʹ�ܱ���λͼ�ͽ���Ч����
   PEnset(m_hPE, PEP_nQUICKSTYLE, PEQS_MEDIUM_INSET);     // predefined viewing styles, enable bitmap,      
 
   PEnset(m_hPE, PEP_bNORANDOMPOINTSTOEXPORT, TRUE );      // ��������㵼��
   PEnset(m_hPE, PEP_bFOCALRECT,             FALSE );      // �Ƿ�ؼ��н�������
   PEnset(m_hPE, PEP_bALLOWBAR,               TRUE );      // �û��ɷ���ʻ�ͼ����Bar Graph is available.
   PEnset(m_hPE, PEP_bALLOWPOPUP,             TRUE );      // ��ͼ�οؼ��Ͽ����һ���������popup�˵�
   PEnset(m_hPE, PEP_bPREPAREIMAGES,          TRUE );      // ����ͼ��������ڴ��л���Ļ��һ����TRUE���Ƶ��ڴ��ֹ��˸
   PEnset(m_hPE, PEP_bCACHEBMP,               TRUE );      // �Ƿ��д��ͼ�������洢���ڴ��һ��wm_paint������ʱʹ�ô�����ݼ�
   PEnset(m_hPE, PEP_bFIXEDFONTS,             TRUE );      // ͼ�����Ź����б��������С����
   PEnset(m_hPE, PEP_bFOCALRECT,              TRUE );	   // ���н�����Σ���ӵ�м��̺���꽹�㣬��ʾ�߿�
   //PEnset(m_hPE, PEP_bSCROLLINGHORZZOOM,    TRUE );      // ��ѧͼ�ṩ��ֱ������Enable horizontal panning once zoomed.
   
   PEnset(m_hPE, PEP_nPLOTTINGMETHOD, PEGPM_SPLINE );       //  PEGPM_POINTSPLUSSPLINE���������  
   PEnset(m_hPE, PEP_nALLOWZOOMING,   PEAZ_HORZANDVERT );   // ͼ�����Ź��ܣ�PEAZ_NONE-�������� 
   PEnset(m_hPE, PEP_nZOOMSTYLE,      PEZS_FRAMED_RECT );   // �������ſ���η��//PEZS_RO2_NOT-��ɫ 
   
   PEnset(m_hPE, PEP_nGRADIENTBARS,      8 );
   PEnset(m_hPE, PEP_nTEXTSHADOWS,    PETS_NO_TEXT);		// PETS_ALL_TEXT//PETS_BOLD_TEXT
   PEnset(m_hPE, PEP_bMAINTITLEBOLD,  TRUE );				// �������Ƿ���壬���壬 
   PEnset(m_hPE, PEP_bSUBTITLEBOLD,   TRUE );				// �ӱ����Ƿ���壬����
   PEnset(m_hPE, PEP_bLABELBOLD,      FALSE);				// ��ǩ�Ƿ����
   PEnset(m_hPE, PEP_bLINESHADOWS,    FALSE);				// ���Ƿ����Ӱ
   PEnset(m_hPE, PEP_nFONTSIZE,       PEFS_MEDIUM);			// �����С


   PEnset(m_hPE, PEP_nCURSORMODE,     PECM_DATACROSS);     // �����α� ,��ʾ�����λ�õ��α�//
   PEnset(m_hPE, PEP_bMARKDATAPOINTS,     TRUE);	        // ���Է���Ĳ鿴���ݵ�
   PEnset(m_hPE, PEP_bMOUSECURSORCONTROL, TRUE);	        // ���Ե�����ݵ����ƶ��α� //
   PEnset(m_hPE, PEP_bALLOWDATAHOTSPOTS,  TRUE);
	
	// Cursor prompting in top left corner //
   PEnset(m_hPE, PEP_bCURSORPROMPTTRACKING,  TRUE);         // �鿴�������α�//  
   PEnset(m_hPE, PEP_nCURSORPROMPTSTYLE,     PECPS_XYVALUES);
   PEnset(m_hPE, PEP_nCURSORPROMPTLOCATION,  PECPL_TOP_RIGHT);

   // Clear out default data   //
   // �����������������ߵĹ����У���Ҫǰ�����������ɵĵ㣬
   // ���ԣ�ʵʱ������ʼ�ļ�����������Ҫ��ǰ�����ü�������㣬���ڼ���������ߣ�
   // ���ǲ���������㣬����ʼ�����߻�������ģ�����������˸��
   float val = 0;
   PEvsetcellEx(m_hPE, PEP_faXDATA, 0, 0, &val);             // ���õ�0�����ߣ�X���ǰ0�����ֵΪ0
   PEvsetcellEx(m_hPE, PEP_faXDATA, 0, 1, &val);
   PEvsetcellEx(m_hPE, PEP_faXDATA, 0, 2, &val);
   PEvsetcellEx(m_hPE, PEP_faXDATA, 0, 3, &val);

   PEvsetcellEx(m_hPE, PEP_faYDATA, 0, 0, &val);
   PEvsetcellEx(m_hPE, PEP_faYDATA, 0, 1, &val);
   PEvsetcellEx(m_hPE, PEP_faYDATA, 0, 2, &val);
   PEvsetcellEx(m_hPE, PEP_faYDATA, 0, 3, &val);
 
   PEvsetcellEx(m_hPE, PEP_faXDATA, 1, 0, &val);
   PEvsetcellEx(m_hPE, PEP_faXDATA, 1, 1, &val);
   PEvsetcellEx(m_hPE, PEP_faXDATA, 1, 2, &val);
   PEvsetcellEx(m_hPE, PEP_faXDATA, 1, 3, &val);

   PEvsetcellEx(m_hPE, PEP_faYDATA, 1, 0, &val);
   PEvsetcellEx(m_hPE, PEP_faYDATA, 1, 1, &val);
   PEvsetcellEx(m_hPE, PEP_faYDATA, 1, 2, &val);
   PEvsetcellEx(m_hPE, PEP_faYDATA, 1, 3, &val);
 
   PEvsetcellEx(m_hPE, PEP_faXDATA, 2, 0, &val);
   PEvsetcellEx(m_hPE, PEP_faXDATA, 2, 1, &val);
   PEvsetcellEx(m_hPE, PEP_faXDATA, 2, 2, &val);
   PEvsetcellEx(m_hPE, PEP_faXDATA, 2, 3, &val);

   PEvsetcellEx(m_hPE, PEP_faYDATA, 2, 0, &val);    
   PEvsetcellEx(m_hPE, PEP_faYDATA, 2, 1, &val);
   PEvsetcellEx(m_hPE, PEP_faYDATA, 2, 2, &val);
   PEvsetcellEx(m_hPE, PEP_faYDATA, 2, 3, &val);  /* */ 
  
   
//   for (int index=0;index<3;index++)
//   {   for (int s = 0; s < 4; s++)
//	   {
//		   PEvsetcellEx(m_hPE, PEP_faXDATA, index, s, &val);
//           PEvsetcellEx(m_hPE, PEP_faYDATA, index, s, &val);   
//	   }
//  }
   
// ����ο���
//   val = 50;
//   for (int xpos = 0; xpos < 100; xpos++ )
//   {
//       PEvsetcellEx(m_hPE, PEP_faXDATA, 1, xpos, &val);
//       PEvsetcellEx(m_hPE, PEP_faYDATA, 1, xpos, &val);
//       PEvsetcellEx(m_hPE, PEP_faXDATA, 2, xpos, &val);
//       PEvsetcellEx(m_hPE, PEP_faYDATA, 2, xpos, &val);
//  }

   //float fData[4][20];                           /* first place data into fData */
   //PEvset (m_hPE, PEP_faYDATA, fData, 80);       /* set data, 4 subsets * 20 points = 80 elements */

   PEreinitialize(m_hPE);                             // ���ö��������Ժ����ݣ���ʼ���ڲ�����Ԥ��������ͼ��
   PEresetimage(m_hPE, 1, 0);                         // �ڱ�����ʾͼ��ʱ�������ñ������Բ���������֮�������ø������»�ͼ
   ::InvalidateRect(m_hPE, NULL, FALSE);
   
   m_nRealTimeCounter = 1;                                 // Initialize Counters and Timer 
   m_nSinCounter      = 1;

 

////**********************************************
   for(int m_nSinCounter =0;m_nSinCounter<1000;m_nSinCounter++)
   {
			float newy,newx;
			newy = 50.0F + float(sin((double) m_nSinCounter * 0.075F) * 30.0F) + GetRandom(1, 15);
			newx = float(m_nRealTimeCounter);
			
			// Update new data at current index //
			PEvsetcellEx(m_hPE, PEP_faYDATA, 0, m_nRealTimeCounter, &newy);
			PEvsetcellEx(m_hPE, PEP_faXDATA, 0, m_nRealTimeCounter, &newx);
			newy = 50.0F - float(sin((double) m_nSinCounter * 0.075F) * 30.0F) + GetRandom(1, 15);
			newx = float(m_nRealTimeCounter);
			PEvsetcellEx(m_hPE, PEP_faYDATA, 1, m_nRealTimeCounter, &newy);
			PEvsetcellEx(m_hPE, PEP_faXDATA, 1, m_nRealTimeCounter, &newx);
			newy = 50.0F + float(sin((double) m_nSinCounter * 0.075F) * 12.0F) - GetRandom(1, 15);
			newx = float(m_nRealTimeCounter);
			PEvsetcellEx(m_hPE, PEP_faYDATA, 2, m_nRealTimeCounter, &newy);
			PEvsetcellEx(m_hPE, PEP_faXDATA, 2, m_nRealTimeCounter, &newx);
			
			double dx;
			dx = (double) newx;
			PEvsetcell(m_hPE, PEP_faVERTLINEANNOTATION, 0, &dx);
			PEvsetcell(m_hPE, PEP_faVERTLINEANNOTATION, 2, &dx);
			PEvsetcell(m_hPE, PEP_faVERTLINEANNOTATION, 3, &dx);
			int lt = PELT_MEDIUMSOLID;
			PEvsetcell(m_hPE, PEP_naVERTLINEANNOTATIONTYPE, 0, &lt);
			
			COLORREF col;
			col = RGB(  0,  0, 198);
			PEvsetcell(m_hPE, PEP_dwaVERTLINEANNOTATIONCOLOR, 0, &col);				col = RGB(  0, 198, 0 );
			PEvsetcell(m_hPE, PEP_dwaVERTLINEANNOTATIONCOLOR, 1, &col);				col = RGB( 255,198, 0 );
			PEvsetcell(m_hPE, PEP_dwaVERTLINEANNOTATIONCOLOR, 2, &col);

			// Increment counter //
			m_nRealTimeCounter = m_nRealTimeCounter + 1;
			
			// Reset counter at end of data //
			if (m_nRealTimeCounter == 100)
				m_nRealTimeCounter = 0;
			
			// SinCounter is only to produce sin wave data //
			m_nSinCounter = m_nSinCounter + 1;
			if (m_nSinCounter > 30000) 
				m_nSinCounter = 1;
			


   }
			// Update image and force paint //
			PEreinitialize( m_hPE );		//	PEresetimage( m_hPE, 0, 0 );
			PEresetimage( m_hPE, 1, 0 );    // Relative width,Relative height,
			::InvalidateRect(m_hPE, NULL, FALSE);

   //SetTimer( 1, 100, NULL );


 
}
 
void CGraphicView::CreateSimpleSGraph()
{
	
	if(m_hPE)
		PEdestroy(m_hPE);

	//! Right button click to show popup menu. //
	//! Double Click to show customization dialog. //
	//! Left-Click and drag to draw zoom box. Use popup memu or 'z' to undo zoom. // 
	
	// Simple example show the basics of a scientific graph object. //
	// Scientific Graph's contain both YData and XData and thus data
	// is not plotted equally spaced as the graph object does.
	
	RECT rect;
	GetClientRect( &rect );
	m_hPE = PEcreate(PECONTROL_SGRAPH, WS_VISIBLE, &rect, m_hWnd, 1001);
	if( m_hPE )
	{
		float fY;
		float fX;
		
		// Set number of Subsets and Points //
		PEnset(m_hPE, PEP_nSUBSETS, 4);	
		PEnset(m_hPE, PEP_nPOINTS, 12);	
		
		for( int s=0; s<=3; s++ )
		{
			for( int p=0; p<=11; p++ )
			{										  
				fX = ((float) (p+1)) * 100.0F;
				PEvsetcellEx (m_hPE, PEP_faXDATA, s, p, &fX);
				fY = ((float) (p+1) * 1.0F) + GetRandom(1, 250);
				PEvsetcellEx (m_hPE, PEP_faYDATA, s, p, &fY);
			}
		}
		
		// Set DataShadows to show shadows
		PEnset(m_hPE, PEP_nDATASHADOWS, PEDS_SHADOWS);
		
		PEszset(m_hPE, PEP_szMAINTITLE,  "��ʷ����ͳ������");
		PEszset(m_hPE, PEP_szSUBTITLE,   "���������ʵ��"); 
		PEszset(m_hPE, PEP_szYAXISLABEL, "���Ӧ����");
		PEszset(m_hPE, PEP_szXAXISLABEL, "�·�");
		PEnset( m_hPE, PEP_bFOCALRECT,		 FALSE  );
		PEnset( m_hPE, PEP_bPREPAREIMAGES,	 TRUE   );
		PEnset( m_hPE, PEP_bCACHEBMP,		 TRUE   );
		PEnset( m_hPE, PEP_nPLOTTINGMETHOD,  PEGPM_POINTSPLUSSPLINE);
		PEnset( m_hPE, PEP_nGRIDLINECONTROL, PEGLC_NONE      );
		PEnset( m_hPE, PEP_nALLOWZOOMING,	 PEAZ_HORZANDVERT);
		PEnset( m_hPE, PEP_nZOOMSTYLE,       PEZS_RO2_NOT    );
		
		// subset labels //
		PEvsetcell( m_hPE, PEP_szaSUBSETLABELS, 0, "��ɳ" );
		PEvsetcell( m_hPE, PEP_szaSUBSETLABELS, 1, "�Ϻ�" );
		PEvsetcell( m_hPE, PEP_szaSUBSETLABELS, 2, "����" );
		PEvsetcell( m_hPE, PEP_szaSUBSETLABELS, 3, "����" );
		
		// subset colors
		DWORD dwArray[4] = { RGB(198,0,0), RGB( 0, 198, 198 ), RGB( 198,198,0 ), RGB( 0,198,0 ) };
		PEvsetEx( m_hPE, PEP_dwaSUBSETCOLORS, 0, 4, dwArray, 0 );
		
		// subset line types
		int nLineTypes[] = { PELT_MEDIUMSOLID, PELT_MEDIUMSOLID, PELT_MEDIUMSOLID, PELT_MEDIUMSOLID };
		PEvset(m_hPE, PEP_naSUBSETLINETYPES, nLineTypes, 4);
		
		// subset point types
		int nPointTypes[] = { PEPT_DOTSOLID, PEPT_UPTRIANGLESOLID, PEPT_SQUARESOLID, PEPT_DOWNTRIANGLESOLID };
		PEvset(m_hPE, PEP_naSUBSETPOINTTYPES, nPointTypes, 4);
		
		// Version 4.0 Features //
		PEnset(m_hPE, PEP_bFIXEDFONTS,			TRUE);
		PEnset(m_hPE, PEP_bSIMPLEPOINTLEGEND,	TRUE);
		PEnset(m_hPE, PEP_bSIMPLELINELEGEND,	TRUE);
		PEnset(m_hPE, PEP_nLEGENDSTYLE, PELS_1_LINE);
		PEnset(m_hPE, PEP_nMULTIAXISSTYLE, PEMAS_SEPARATE_AXES);
		
		// Set Various Other Properties //
		PEnset(m_hPE, PEP_bBITMAPGRADIENTMODE, TRUE);
		PEnset(m_hPE, PEP_nQUICKSTYLE, PEQS_MEDIUM_NO_BORDER);
		
		PEnset(m_hPE, PEP_nGRADIENTBARS,	8);
		PEnset(m_hPE, PEP_nTEXTSHADOWS,		PETS_BOLD_TEXT);
		PEnset(m_hPE, PEP_bMAINTITLEBOLD,   TRUE);
		PEnset(m_hPE, PEP_bSUBTITLEBOLD,    TRUE);
		PEnset(m_hPE, PEP_bLABELBOLD,		TRUE);
		PEnset(m_hPE, PEP_bLINESHADOWS,		TRUE);
		PEnset(m_hPE, PEP_nFONTSIZE, PEFS_LARGE);
		PEnset(m_hPE, PEP_bSCROLLINGHORZZOOM, TRUE);
		
		
	}
}

void CGraphicView::CreateSimpleGraph()
{ 
	//! Right button click to show popup menu. //
	//! Double Click to show customization dialog. //
	//! Left-Click and drag to draw zoom box. Use popup memu or 'z' to undo zoom. // 
	
	// Simple example show the basics of a graph object. //
	// Graph's generally only contain YData because we assume
	// data is plotted equally spaced left to right.
	CRect rect;
	GetClientRect( rect ); 
	m_hPE = PEcreate(PECONTROL_GRAPH, WS_CHILD|WS_VISIBLE, &rect, m_hWnd, 1001);
	if (m_hPE) 
	{
		// Prepare images in memory //
		PEnset(m_hPE, PEP_bPREPAREIMAGES, TRUE);
		
		// Pass Data //
		PEnset(m_hPE, PEP_nSUBSETS, 4);
		PEnset(m_hPE, PEP_nPOINTS, 12);
		
		float fY;
		for (int s=0; s<=3; s++)
		{
			for (int p=0; p<=11; p++)
			{
				fY = float((p + 1) * 50) + GetRandom(2, 250);
				PEvsetcellEx(m_hPE, PEP_faYDATA, s, p, &fY);
			}
		}
		
		// Set DataShadows to show 3D //
		PEnset(m_hPE, PEP_nDATASHADOWS, PEDS_SHADOWS);
		PEnset(m_hPE, PEP_nBORDERTYPES, PETAB_DROP_SHADOW);
		
		PEszset(m_hPE, PEP_szMAINTITLE,  "��ʷ����ͳ������");
		PEszset(m_hPE, PEP_szSUBTITLE,   "���������ʵ��"  ); 
		PEszset(m_hPE, PEP_szYAXISLABEL, "���Ӧ����" );
		PEszset(m_hPE, PEP_szXAXISLABEL, "�·�");
		PEnset(m_hPE, PEP_bFOCALRECT,        FALSE      );
		PEnset(m_hPE, PEP_nPLOTTINGMETHOD,   PEGPM_BAR  );   // ��ʵ����
		PEnset(m_hPE, PEP_nGRIDLINECONTROL,  PEGLC_NONE );   // �Ƿ���X,Y
		PEnset(m_hPE, PEP_bALLOWRIBBON, TRUE);
		PEnset(m_hPE, PEP_nALLOWZOOMING, PEAZ_HORZANDVERT);
		PEnset(m_hPE, PEP_nZOOMSTYLE, PEZS_RO2_NOT);
		
		// subset labels //
		PEvsetcell( m_hPE, PEP_szaSUBSETLABELS, 0, "��ɳ" );
		PEvsetcell( m_hPE, PEP_szaSUBSETLABELS, 1, "�Ϻ�" );
		PEvsetcell( m_hPE, PEP_szaSUBSETLABELS, 2, "����" );
		PEvsetcell( m_hPE, PEP_szaSUBSETLABELS, 3, "����" );
		
		// point labels //
		PEvsetcell( m_hPE, PEP_szaPOINTLABELS, 0, "һ��" );
		PEvsetcell( m_hPE, PEP_szaPOINTLABELS, 1, "����" );
		PEvsetcell( m_hPE, PEP_szaPOINTLABELS, 2, "����" );
		PEvsetcell( m_hPE, PEP_szaPOINTLABELS, 3, "����" );
		PEvsetcell( m_hPE, PEP_szaPOINTLABELS, 4, "����" );
		PEvsetcell( m_hPE, PEP_szaPOINTLABELS, 5, "����" );
		PEvsetcell( m_hPE, PEP_szaPOINTLABELS, 6, "����" );
		PEvsetcell( m_hPE, PEP_szaPOINTLABELS, 7, "����" );
		PEvsetcell( m_hPE, PEP_szaPOINTLABELS, 8, "����" );
		PEvsetcell( m_hPE, PEP_szaPOINTLABELS, 9, "ʮ��" );
		PEvsetcell( m_hPE, PEP_szaPOINTLABELS, 10, "ʮһ��" );
		PEvsetcell( m_hPE, PEP_szaPOINTLABELS, 11, "ʮ����" );
		
		// subset colors //
		DWORD dwArray[4] = { RGB(198,0,0), RGB( 0, 198, 198 ), RGB( 198,198,0 ), RGB( 0,198,0 ) };
		PEvsetEx(m_hPE, PEP_dwaSUBSETCOLORS, 0, 4, dwArray, 0);
		
		// subset line types //
		int nLineTypes[] = { PELT_MEDIUMSOLID, PELT_MEDIUMSOLID, 
			PELT_MEDIUMSOLID, PELT_MEDIUMSOLID, PELT_MEDIUMSOLID, 
			PELT_MEDIUMSOLID, PELT_MEDIUMSOLID, PELT_MEDIUMSOLID};
		PEvset(m_hPE, PEP_naSUBSETLINETYPES, nLineTypes, 8);
		
		// subset point types //
		int nPointTypes[] = { PEPT_DOTSOLID, PEPT_UPTRIANGLESOLID, 
			PEPT_SQUARESOLID, PEPT_DOWNTRIANGLESOLID, PEPT_DOT, 
			PEPT_UPTRIANGLE, PEPT_SQUARE, PEPT_DOWNTRIANGLE };
		PEvset(m_hPE, PEP_naSUBSETPOINTTYPES, nPointTypes, 8);
		
		// Allow stacked type graphs //
		PEnset(m_hPE, PEP_bNOSTACKEDDATA, FALSE);
		
		// Various other features //
		PEnset(m_hPE, PEP_bFIXEDFONTS, TRUE);
		PEnset(m_hPE, PEP_bBITMAPGRADIENTMODE, TRUE);
		PEnset(m_hPE, PEP_nQUICKSTYLE, PEQS_MEDIUM_LINE);
		PEnset(m_hPE, PEP_bSIMPLEPOINTLEGEND, TRUE);
		PEnset(m_hPE, PEP_bSIMPLELINELEGEND, TRUE);
		PEnset(m_hPE, PEP_nLEGENDSTYLE, PELS_1_LINE);
		PEnset(m_hPE, PEP_nGRAPHPLUSTABLE, PEGPT_BOTH);
		
		PEnset(m_hPE, PEP_nGRADIENTBARS, 8);
		PEnset(m_hPE, PEP_nTEXTSHADOWS, PETS_BOLD_TEXT);
		PEnset(m_hPE, PEP_bMAINTITLEBOLD, TRUE);
		PEnset(m_hPE, PEP_bSUBTITLEBOLD, TRUE);
		PEnset(m_hPE, PEP_bLABELBOLD, TRUE);
		PEnset(m_hPE, PEP_bLINESHADOWS, TRUE);
		PEnset(m_hPE, PEP_nFONTSIZE, PEFS_LARGE);
		
	}
}


void CGraphicView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CString ttext;  
	double  newx2;
	float   YData[250];
	double  XData[250]; 
	double  dx; 
	CTime   t;
	TM      petm; 

	if (nIDEvent = 2)
	{
		;
	}

	CView::OnTimer(nIDEvent);

}



void CGraphicView::OnTest() 
{
	// TODO: Add your command handler code here
	MessageBox("asdf");
}

void CGraphicView::OnButtonDataSave() 
{
	// TODO: Add your control notification handler code here
	MessageBox("mainFrame �ٴ���");
}
