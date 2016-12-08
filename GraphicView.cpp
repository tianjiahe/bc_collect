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
    AfxGetApp()->GetMainWnd()->SetWindowText(_T("样品测试曲线 V1.0"));
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
   GetClientRect( &rect );                                               // 返回客户区尺寸     

   m_hPE = PEcreate(PECONTROL_SGRAPH, WS_VISIBLE, &rect, m_hWnd, 1001);  // 客户区创建图形对象，返回句柄

   PEnset(m_hPE,  PEP_nSUBSETS,     3   );									 // 设置子集的个数，定义对象包含的子集数
   PEnset(m_hPE,  PEP_nPOINTS,      100 );									 // 设置子集点数  

   PEszset(m_hPE, PEP_szMAINTITLE,  "样品检测过程");					// 对象的主标题，
   PEszset(m_hPE, PEP_szSUBTITLE,   "编号00001"   );    				// 子标题，标识对象的字幕，在主标题下
   PEszset(m_hPE, PEP_szYAXISLABEL, "透光率(%)"   );                    // 作为Y轴标签文本
   PEszset(m_hPE, PEP_szXAXISLABEL, "波长(nm)"    );                    // 作为X轴标签文本
   
   PEnset( m_hPE, PEP_nDATASHADOWS,  PEDS_NONE    );                    // 数据曲线显示效果，/无/阴影/3D/ //PEDS_3D//	PEDS_SHADOWS
  
   //PEnset(m_hPE, PEP_nMANUALSCALECONTROLY, PEMSC_MIN);                // Y坐标的标记,PEMSC_MIN-跟踪坐标最小值移动,PEMSC_MAX跟踪最大值
   PEnset(m_hPE, PEP_nMANUALSCALECONTROLY, PEMSC_MINMAX);               // Y坐标的标记,PEMSC_MINMAX-显示Y全量程
   double arg = 0.0F;
   PEvset(m_hPE, PEP_fMANUALMINY,          &arg, 1);                    // 设置Y坐标的起始点 
   arg = 100.0F;
   PEvset(m_hPE, PEP_fMANUALMAXY,          &arg, 1);                    // 设置Y坐标的终止点  
   
   // Set Manual X scale //
   PEnset(m_hPE, PEP_nMANUALSCALECONTROLX, PEMSC_MINMAX);                 // X轴的标记，方式，MINMAX-全量程，MIN跟踪最小值，MAM-跟踪最大值  
   arg = 1.0F;
   PEvset(m_hPE, PEP_fMANUALMINX, &arg, 1);                            // X坐标起点
   arg = 100.0F;
   PEvset(m_hPE, PEP_fMANUALMAXX, &arg, 1);                            // X坐标终点

/*   线型设置，2类设置效果是一样的
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
   DWORD col = RGB(255, 0, 0);                              // 设置不同曲线的颜色
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
   PEvset(m_hPE,PEP_dwaSUBSETCOLORS, col, 3);                  // 设置曲线标题颜色

   //PEvset(m_hPE, PEP_naSUBSETLINETYPES, PELT_THINSOLID, 0);
   
   char szSubsets[] = "上限\t样品\t下限\t";
   PEvset (m_hPE, PEP_szaSUBSETLABELS, szSubsets,3);
   
   // 子集的标识
   //char *pszSubsets[3] ={"样品","上限","下限"};
   //PEvset(m_hPE, PEP_szaSUBSETLABELS, pszSubsets, 3);
   //PEvsetcell( m_hPE, PEP_szaSUBSETLABELS, 0, "样品" );
   //PEvsetcell( m_hPE, PEP_szaSUBSETLABELS, 1, "上限" );
   //PEvsetcell( m_hPE, PEP_szaSUBSETLABELS, 2, "下限" );

   // Set Various Other Properties ///
   PEnset(m_hPE, PEP_bBITMAPGRADIENTMODE,     TRUE );     // 使能背景位图和渐变效果，
   PEnset(m_hPE, PEP_nQUICKSTYLE, PEQS_MEDIUM_INSET);     // predefined viewing styles, enable bitmap,      
 
   PEnset(m_hPE, PEP_bNORANDOMPOINTSTOEXPORT, TRUE );      // 禁用随机点导出
   PEnset(m_hPE, PEP_bFOCALRECT,             FALSE );      // 是否控件有焦点区域，
   PEnset(m_hPE, PEP_bALLOWBAR,               TRUE );      // 用户可否访问绘图栏，Bar Graph is available.
   PEnset(m_hPE, PEP_bALLOWPOPUP,             TRUE );      // 在图形控件上可以右击弹出关联popup菜单
   PEnset(m_hPE, PEP_bPREPAREIMAGES,          TRUE );      // 控制图像输出到内存中或屏幕，一般是TRUE绘制到内存防止闪烁
   PEnset(m_hPE, PEP_bCACHEBMP,               TRUE );      // 是否编写的图形连续存储在内存或发一个wm_paint，仅当时使用大的数据集
   PEnset(m_hPE, PEP_bFIXEDFONTS,             TRUE );      // 图形缩放过程中保存字体大小不变
   PEnset(m_hPE, PEP_bFOCALRECT,              TRUE );	   // 具有焦点矩形，可拥有键盘和鼠标焦点，显示边框
   //PEnset(m_hPE, PEP_bSCROLLINGHORZZOOM,    TRUE );      // 科学图提供垂直滚动条Enable horizontal panning once zoomed.
   
   PEnset(m_hPE, PEP_nPLOTTINGMETHOD, PEGPM_SPLINE );       //  PEGPM_POINTSPLUSSPLINE，点加曲线  
   PEnset(m_hPE, PEP_nALLOWZOOMING,   PEAZ_HORZANDVERT );   // 图像缩放功能，PEAZ_NONE-禁用缩放 
   PEnset(m_hPE, PEP_nZOOMSTYLE,      PEZS_FRAMED_RECT );   // 控制缩放框矩形风格//PEZS_RO2_NOT-反色 
   
   PEnset(m_hPE, PEP_nGRADIENTBARS,      8 );
   PEnset(m_hPE, PEP_nTEXTSHADOWS,    PETS_NO_TEXT);		// PETS_ALL_TEXT//PETS_BOLD_TEXT
   PEnset(m_hPE, PEP_bMAINTITLEBOLD,  TRUE );				// 主标题是否粗体，字体， 
   PEnset(m_hPE, PEP_bSUBTITLEBOLD,   TRUE );				// 子标题是否粗体，字体
   PEnset(m_hPE, PEP_bLABELBOLD,      FALSE);				// 标签是否粗体
   PEnset(m_hPE, PEP_bLINESHADOWS,    FALSE);				// 线是否带阴影
   PEnset(m_hPE, PEP_nFONTSIZE,       PEFS_MEDIUM);			// 字体大小


   PEnset(m_hPE, PEP_nCURSORMODE,     PECM_DATACROSS);     // 创建游标 ,显示鼠标点击位置的游标//
   PEnset(m_hPE, PEP_bMARKDATAPOINTS,     TRUE);	        // 可以方便的查看数据点
   PEnset(m_hPE, PEP_bMOUSECURSORCONTROL, TRUE);	        // 可以点击数据点来移动游标 //
   PEnset(m_hPE, PEP_bALLOWDATAHOTSPOTS,  TRUE);
	
	// Cursor prompting in top left corner //
   PEnset(m_hPE, PEP_bCURSORPROMPTTRACKING,  TRUE);         // 查看坐标点的游标//  
   PEnset(m_hPE, PEP_nCURSORPROMPTSTYLE,     PECPS_XYVALUES);
   PEnset(m_hPE, PEP_nCURSORPROMPTLOCATION,  PECPL_TOP_RIGHT);

   // Clear out default data   //
   // 在坐标点生成拟合曲线的过程中，需要前后连续的若干的点，
   // 所以，实时曲线起始的几个点的拟合需要在前面设置几个虚拟点，用于计算拟合曲线，
   // 若是不设置虚拟点，则起始的曲线会是随机的，出现曲线闪烁。
   float val = 0;
   PEvsetcellEx(m_hPE, PEP_faXDATA, 0, 0, &val);             // 设置第0条曲线，X轴的前0个点的值为0
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
   
// 虚拟参考线
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

   PEreinitialize(m_hPE);                             // 重置对象新属性和数据，初始化内部变量预备生成新图形
   PEresetimage(m_hPE, 1, 0);                         // 在编码显示图形时，在设置变量属性并传递数据之后，最后调用更新重新绘图
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
		
		PEszset(m_hPE, PEP_szMAINTITLE,  "历史线性统计曲线");
		PEszset(m_hPE, PEP_szSUBTITLE,   "程序设计与实现"); 
		PEszset(m_hPE, PEP_szYAXISLABEL, "最大应用量");
		PEszset(m_hPE, PEP_szXAXISLABEL, "月份");
		PEnset( m_hPE, PEP_bFOCALRECT,		 FALSE  );
		PEnset( m_hPE, PEP_bPREPAREIMAGES,	 TRUE   );
		PEnset( m_hPE, PEP_bCACHEBMP,		 TRUE   );
		PEnset( m_hPE, PEP_nPLOTTINGMETHOD,  PEGPM_POINTSPLUSSPLINE);
		PEnset( m_hPE, PEP_nGRIDLINECONTROL, PEGLC_NONE      );
		PEnset( m_hPE, PEP_nALLOWZOOMING,	 PEAZ_HORZANDVERT);
		PEnset( m_hPE, PEP_nZOOMSTYLE,       PEZS_RO2_NOT    );
		
		// subset labels //
		PEvsetcell( m_hPE, PEP_szaSUBSETLABELS, 0, "长沙" );
		PEvsetcell( m_hPE, PEP_szaSUBSETLABELS, 1, "上海" );
		PEvsetcell( m_hPE, PEP_szaSUBSETLABELS, 2, "北京" );
		PEvsetcell( m_hPE, PEP_szaSUBSETLABELS, 3, "广州" );
		
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
		
		PEszset(m_hPE, PEP_szMAINTITLE,  "历史线性统计曲线");
		PEszset(m_hPE, PEP_szSUBTITLE,   "程序设计与实现"  ); 
		PEszset(m_hPE, PEP_szYAXISLABEL, "最大应用量" );
		PEszset(m_hPE, PEP_szXAXISLABEL, "月份");
		PEnset(m_hPE, PEP_bFOCALRECT,        FALSE      );
		PEnset(m_hPE, PEP_nPLOTTINGMETHOD,   PEGPM_BAR  );   // 现实类型
		PEnset(m_hPE, PEP_nGRIDLINECONTROL,  PEGLC_NONE );   // 是否有X,Y
		PEnset(m_hPE, PEP_bALLOWRIBBON, TRUE);
		PEnset(m_hPE, PEP_nALLOWZOOMING, PEAZ_HORZANDVERT);
		PEnset(m_hPE, PEP_nZOOMSTYLE, PEZS_RO2_NOT);
		
		// subset labels //
		PEvsetcell( m_hPE, PEP_szaSUBSETLABELS, 0, "长沙" );
		PEvsetcell( m_hPE, PEP_szaSUBSETLABELS, 1, "上海" );
		PEvsetcell( m_hPE, PEP_szaSUBSETLABELS, 2, "北京" );
		PEvsetcell( m_hPE, PEP_szaSUBSETLABELS, 3, "广州" );
		
		// point labels //
		PEvsetcell( m_hPE, PEP_szaPOINTLABELS, 0, "一月" );
		PEvsetcell( m_hPE, PEP_szaPOINTLABELS, 1, "二月" );
		PEvsetcell( m_hPE, PEP_szaPOINTLABELS, 2, "三月" );
		PEvsetcell( m_hPE, PEP_szaPOINTLABELS, 3, "四月" );
		PEvsetcell( m_hPE, PEP_szaPOINTLABELS, 4, "五月" );
		PEvsetcell( m_hPE, PEP_szaPOINTLABELS, 5, "六月" );
		PEvsetcell( m_hPE, PEP_szaPOINTLABELS, 6, "七月" );
		PEvsetcell( m_hPE, PEP_szaPOINTLABELS, 7, "八月" );
		PEvsetcell( m_hPE, PEP_szaPOINTLABELS, 8, "九月" );
		PEvsetcell( m_hPE, PEP_szaPOINTLABELS, 9, "十月" );
		PEvsetcell( m_hPE, PEP_szaPOINTLABELS, 10, "十一月" );
		PEvsetcell( m_hPE, PEP_szaPOINTLABELS, 11, "十二月" );
		
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
	MessageBox("mainFrame 再处理！");
}
