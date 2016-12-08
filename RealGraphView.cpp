// RealGraphView.cpp : implementation file
//

#include "stdafx.h"
#include "collect.h"
#include "RealGraphView.h"

#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib,"PEGRP32C.lib")

#define GetRandom(min,max) ((rand()%(int)(((max)+1)-(min)))+(min))

/////////////////////////////////////////////////////////////////////////////
// CRealGraphView

IMPLEMENT_DYNCREATE(CRealGraphView, CView)

CRealGraphView::CRealGraphView(){}

CRealGraphView::~CRealGraphView(){}

BEGIN_MESSAGE_MAP(CRealGraphView, CView)
	//{{AFX_MSG_MAP(CRealGraphView)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRealGraphView drawing

void CRealGraphView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CRealGraphView diagnostics

#ifdef _DEBUG
void CRealGraphView::AssertValid() const
{
	CView::AssertValid();
}

void CRealGraphView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRealGraphView message handlers

BOOL CRealGraphView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
//	return CView::OnEraseBkgnd(pDC);
	return TRUE;
}

void CRealGraphView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(m_hPE)	{			PEdestroy(m_hPE);	}
	drawRealCur();
		
}

void CRealGraphView::drawRealCur()
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

   PEnset(m_hPE,  PEP_nSUBSETS,     1   );									 // �����Ӽ��ĸ������������������Ӽ���
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

   //DWORD dwArray[3] = { RGB(198,0,0), RGB( 0, 198, 198 ), RGB( 198,198,0 ) };
   //PEvsetEx( m_hPE, PEP_dwaSUBSETCOLORS, 0, 3, dwArray, 0 );//���������п��Ƶ���ɫ���������ֶ����Ϣ�Ӽ�֮��������ͼ��
   
   //int nLineTypes[] = { PELT_MEDIUMSOLID, PELT_MEDIUMSOLID, PELT_MEDIUMSOLID};
   //PEvset(m_hPE, PEP_naSUBSETLINETYPES, nLineTypes, 4);   //���������п����������������ֶ����Ϣ�Ӽ�֮��������ͼ��
  
   //int nPointTypes[] = { PEPT_DOTSOLID, PEPT_UPTRIANGLESOLID, PEPT_SQUARESOLID};//PEPT_DOWNTRIANGLESOLID };
   //PEvset(m_hPE, PEP_naSUBSETPOINTTYPES, nPointTypes,4);//���������п��Ƶ������������ֶ����Ϣ�Ӽ�֮��������ͼ��

   
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
   PEnset(m_hPE, PEP_bFIXEDFONTS,             TRUE );      // ʹ���屣�����óߴ�ʱ�ĳߴ�仯ͼ��
   PEnset(m_hPE, PEP_bFOCALRECT,              TRUE );	   // ���н�����Σ���ӵ�м��̺���꽹�㣬��ʾ�߿�
   //PEnset(m_hPE, PEP_bSCROLLINGHORZZOOM,    TRUE );      // ��ѧͼ�ṩ��ֱ������Enable horizontal panning once zoomed.

   PEnset(m_hPE, PEP_bSIMPLEPOINTLEGEND,      TRUE );      // �����Կ��Կ��Ƶ��ͼ��������ʽ
   PEnset(m_hPE, PEP_bSIMPLELINELEGEND,       TRUE );      // �����Կ��Կ�����·ͼ��������ʽ��

   PEnset(m_hPE, PEP_nGRIDLINECONTROL,  PEGLC_BOTH );        // ���Ƶ������ˮƽ�ʹ�ֱ�ߣ�PEGLC_NONE-

   PEnset(m_hPE, PEP_nPLOTTINGMETHOD,  PEGPM_POINTSPLUSSPLINE ); // ���������ķ�ʽ  ��+���ߣ�PEGPM_SPLINE-������ʽ ��

   PEnset(m_hPE, PEP_nALLOWZOOMING,   PEAZ_HORZANDVERT );   // ͼ�����Ź��ܣ�PEAZ_NONE-�������� 
   PEnset(m_hPE, PEP_nZOOMSTYLE,      PEZS_FRAMED_RECT );   // �������ſ���η��//PEZS_RO2_NOT-��ɫ 
   
   PEnset(m_hPE, PEP_nGRADIENTBARS,      8 );
   PEnset(m_hPE, PEP_nTEXTSHADOWS,    PETS_NO_TEXT);		// PETS_ALL_TEXT//PETS_BOLD_TEXT
   PEnset(m_hPE, PEP_bMAINTITLEBOLD,  TRUE );				// �������Ƿ���壬���壬 
   PEnset(m_hPE, PEP_bSUBTITLEBOLD,   TRUE );				// �ӱ����Ƿ���壬����
   PEnset(m_hPE, PEP_bLABELBOLD,      FALSE);				// ��ǩ�Ƿ����
   PEnset(m_hPE, PEP_bLINESHADOWS,    FALSE);				// ���Ƿ����Ӱ
   PEnset(m_hPE, PEP_nFONTSIZE,       PEFS_MEDIUM);			// �����С


//   PEnset(m_hPE, PEP_nCURSORMODE,     PECM_DATACROSS);     // �����α� ,��ʾ�����λ�õ��α�//
//   PEnset(m_hPE, PEP_bMARKDATAPOINTS,     TRUE);	        // ���Է���Ĳ鿴���ݵ�
//   PEnset(m_hPE, PEP_bMOUSECURSORCONTROL, TRUE);	        // ���Ե�����ݵ����ƶ��α� //
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
 /*
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
   PEvsetcellEx(m_hPE, PEP_faYDATA, 2, 3, &val);   */ 
  
   
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

   
   //SetTimer( 1, 100, NULL );
 
   //m_Real = FALSE;
   
}

void CRealGraphView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CString ttext;  
	double  newx2;
	float   YData[250];
	double  XData[250]; 
	double  dx; 
	CTime   t;
	TM      petm; 

	if(nIDEvent==1)
	{   
			// ����ģ��ʵʱ����
 		float newy = 50.0F + float(sin((double) m_nSinCounter * 0.075F) * 25.0F) + GetRandom(1, 10);
		float newx = (float)m_nRealTimeCounter; 

		PEvset(m_hPE, PEP_faAPPENDYDATA, &newy, 1);        // ׷���µ����ݣ��������췽ʽ 0-������1-���ԣ�2 ָ��
		PEvset(m_hPE, PEP_faAPPENDXDATA, &newx, 1);        
		//PEvset(m_hPE, PEP_faAPPENDYDATA, &maxy, 1);      // ׷���µ���������
		//PEvset(m_hPE, PEP_faAPPENDXDATA, &newx, 1); 
		//PEvset(m_hPE, PEP_faAPPENDYDATA, &miny, 1);      // ׷���µ���������
		//PEvset(m_hPE, PEP_faAPPENDXDATA, &newx, 1); 

		// Update new data at current index //
//				PEvsetcellEx(m_hPE, PEP_faYDATA, 0, m_nRealTimeCounter, &newy);
//				PEvsetcellEx(m_hPE, PEP_faXDATA, 0, m_nRealTimeCounter, &newx);
//				PEvsetcellEx(m_hPE, PEP_faYDATA, 1, m_nRealTimeCounter, &maxy);
//				PEvsetcellEx(m_hPE, PEP_faXDATA, 1, m_nRealTimeCounter, &newx);
//				PEvsetcellEx(m_hPE, PEP_faYDATA, 2, m_nRealTimeCounter, &miny);
// 				PEvsetcellEx(m_hPE, PEP_faXDATA, 2, m_nRealTimeCounter, &newx);
           
	     	m_nRealTimeCounter = m_nRealTimeCounter + 1;
			
			// Switch to AutoScaling x axis after receiving 100 data points //
			if (m_nRealTimeCounter == 100)
			{
				PEnset(m_hPE, PEP_nMANUALSCALECONTROLX, PEMSC_NONE);  // X�ᶯ̬��������㡣Automatic Scale Control
			}
			// SinCounter is only to produce sin wave data //
			m_nSinCounter = m_nSinCounter + 1;
			if (m_nSinCounter > 2000) 				
			{
				m_nSinCounter = 1;
				KillTimer(1);
			}
			
			// Update image and force paint //
			PEreinitialize( m_hPE );
			PEresetimage( m_hPE, 1, 0 );
			::InvalidateRect(m_hPE, NULL, FALSE);    // ֪ͨ�ػ�
		}
		else
		{
			////**********************************************
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
			
			// Update image and force paint //
			PEreinitialize( m_hPE );		//	PEresetimage( m_hPE, 0, 0 );
			PEresetimage( m_hPE, 1, 0 );    // Relative width,Relative height,
			::InvalidateRect(m_hPE, NULL, FALSE);
			
	}


	CView::OnTimer(nIDEvent);
}

