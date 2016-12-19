//-----------------------------------------------------------------------------------//
//			版权所有(C) : 北京信息科技大学，北京北光世纪仪器有限公司				 //
// 			说明		: WPZ系列多光栅单色仪控制扫描动态链接库						 //
// 			版本		: V2.0														 //
//-----------------------------------------------------------------------------------//
//WPZ 系列光栅单色仪在使用前请先连接号USB接口，然后软件调用重新定位函数或光栅归零函数，
//使单色仪重新定位至初始位置，此过程可能需要等待较长的时间，请使用多线程或定时器等待定
//位结束，以防止出现程序界面出现假死现象。
//
#ifndef __CSP_H__
#define __CSP_H__

// 0x10-0x1F为光栅控制命令
#define GRID_INIT		0x10  //光栅转台零点
#define GRID_STOP		0x11  //光栅转台停止 
#define GRID_GOTO		0x12  //光栅转台绝对定位 
#define GRID_SPEED		0x13  //光栅转台速度
#define GRID_ASK		0x14  //查询光栅转台位置

#define GRID_SET1		0x18  //光栅1转台零级光
#define GRID_SET2		0x19  //光栅2转台零级光
#define GRID_SET3		0x1a  //光栅3转台零级光

// 0x20-0x28为滤色片轮电机的控制命令
#define FLITER_INIT		0x20
#define FLITER_GOTO		0x21  //滤色片轮绝对定位 0 - Init; 1-6 Win Pos 

// 0x29-0x2F为反光镜电机的控制命令
#define MIRROR_INIT		0x29
#define	MIRROR_GOTO		0x2A  //反光镜绝对定位   0 -MIRROR1控制 ; 1 - MIRROR2控制

// 0x30-0x3F为数据采集控制命令
#define ADC_DATA        0x30  //查询数据采集参数
#define ADC_CHN	        0x31  //设置数据采集通道	   0-A通道  1-B通道
#define ADC_PGA	        0x32  //设置数据采集增益
#define ADC_IV			0x33  //设置数据采集电压/电流模式  0-电流模式   1-电压模式
#define ADC_MODE		0x34  //设置数据采集积分次数       0 - 50Hz 1 - norminal
//#define ADC_DATA		0x35  //设置数据采集参数

// 0x40-0x4F为参数设置控制命令
#define DAC_DATA		0x40  //设置数据采集参数
#define DAC_CHN 		0x41  //设置数据采集通道

//上位机发送给下位机的测试命令，同时发送一个长整型数据给下位机，下位机接到命令后将数据取反后发给上位机
#define CMD_TEST		0x60
#define CMD_STOP		0x61  //停止执行
//------------------------------------------------------------------------------------//
// 上行命令：0xC0-0xFF这段为单片机发给计算机的命令	
//------------------------------------------------------------------------------------//

// 状态命令：0xC0-0xCF这段为单片机发给计算机的状态命令										
#define CMD_OK			0xC0
#define CMD_ERROR		0xC1


// 数据命令：0xD0-0xDF这段为单片机发给计算机的数据命令					
#define VAL_ADC 		0xD0
#define VAL_GRID		0xD2

// 仪器参数定义
// 仪器类型定义
#define INS_TYPE_F060HID   101
#define INS_TYPE_F020HID   201
#define INS_TYPE_F320HID   301
#define INS_TYPE_F326HID   401
#define INS_TYPE_F060JC372 501
#define INS_TYPE_STC58C372 601 

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CSP_EXPORTS
#define CSP_API __declspec(dllexport)
#else
#define CSP_API __declspec(dllimport)
#endif

	extern CSP_API BOOL UsbInited;							//USB接口初始化标志，TRUE:已成功连接USB并初始化,FALSE:未初始化
	extern CSP_API BOOL Busy;								//单色仪忙标志位，TRUE:设备正在运行中，FALSE:设备处于等待命令状态
	
	extern CSP_API LONG   G1;							//1号光栅的刻线数，如该变量为0，说明相应光栅不存在
	extern CSP_API LONG   G2;							//2号光栅的刻线数，如该变量为0，说明相应光栅不存在
	extern CSP_API LONG   G3;							//3号光栅的刻线数，如该变量为0，说明相应光栅不存在
	extern CSP_API LONG   G1Wave;						//1号光栅的闪耀波长，如该变量为0，说明该光栅不存在
	extern CSP_API LONG   G2Wave;						//2号光栅的闪耀波长，如该变量为0，说明该光栅不存在
	extern CSP_API LONG   G3Wave;						//3号光栅的闪耀波长，如该变量为0，说明该光栅不存在
	extern CSP_API LONG   GridIndex;						//当前正在使用的光栅索引号
	extern CSP_API LONG   InsNo;							//仪器出厂编号
	extern CSP_API LONG   InsType;							//仪器型号
	extern CSP_API LONG   GridSumSteps;						//光栅转台旋转一周，步进电机所走的总步数
	extern CSP_API LONG   FirmVersion;						//固件版本号
	extern CSP_API LONG   FilterSumSteps;					//滤色片轮电机旋转一周，步进电机所走的总步数，为0说明没有安装滤色片轮
	extern CSP_API LONG   MirrorSumSteps;					//反光镜电机旋转一周，步进电机所走的总步数，为0说明没有安装反光镜
	extern CSP_API LONG   AdChs;							//模拟输入通道数0:没有模拟输入1:只有一个模拟通道2:有两个模拟通道
	extern CSP_API LONG   AdMax;							//模拟输入AD转换最大值，分别为8位=256，12位=4096或16位=32768
	extern CSP_API LONG   AdMin;							//模拟输入AD转换最小值，分别为8位或12位=0，16位=-32768
	extern CSP_API LONG   AdPga;							//模拟输入可编程增益，0，2，4，8，16，32，64，256
	extern CSP_API LONG   DaChs;							//模拟输出通道数:0-没有模拟输出；1-有一路模拟输出；2-有两路模拟输出
	extern CSP_API LONG   DaMax;							//模拟输出最大值:0-没有模拟输出；8位=256 10位=1024 12位=4096
	extern CSP_API double AdRef;							//模拟输入参考电压值 2.5V 2.4V
	extern CSP_API double DaRef;							//模拟输出参考电压值 2.5V 2.4V
	extern CSP_API double NowWave;						//仪器当前的波长值


	extern CSP_API BOOL WINAPI CUsbLinked(void);						//建立USB连接
	extern CSP_API void WINAPI COpenDev(void);							//打开设备
	extern CSP_API void WINAPI CCloseDev(void);							//关闭与设备的连接
	extern CSP_API void WINAPI CSendCmd(UCHAR cmd);						//向设备发送命令，参数cmd:命令（一个字节,无符号字符）					
	extern CSP_API void WINAPI CSendCmdData(UCHAR cmd, ULONG x);			//向设备发送命令和数据，参数cmd:命令（一个字节,无符号字符），dat:数据(4个字节，长整型)	
	extern CSP_API BOOL WINAPI CReadCmdData(UCHAR &cmd,LONG &dat) ;		//读取设备上传的命令和数据，参数cmd:返回上传的命令（一个字节,无符号字符），dat:返回上传的数据(4个字节，长整型)
	extern CSP_API BOOL WINAPI CDevInit(void);							//初始化设备
	extern CSP_API void WINAPI CSetSpeed(ULONG speed);					//设置光栅运行速度，0~9中速度，数值越大，速度越慢
	extern CSP_API void WINAPI CGridInit(void);							//初始化光栅
	extern CSP_API void WINAPI CGotoZero(ULONG gindex);				//使光栅定位至零级光位置，参数GridIndex:指定光栅编号（4个字节，无符号长整型）
	extern CSP_API void WINAPI CGotoWave(ULONG gindex,double wave);	//使光栅定位至参数wave指定波长位置，参数GridIndex：光栅索引，wave：波长
	extern CSP_API void WINAPI CStop(void);								//停止光栅运行
	extern CSP_API void WINAPI CGetCurWave(void);						//向下位机发送指令，获得当前位置波长	
	extern CSP_API void WINAPI CSetAdChannel(ULONG ch);					//选择AD转换通道，参数ch:通道号（4个字节，无符号长整型)0:通道1，1:通道2
	extern CSP_API void WINAPI CSetAdPGA(ULONG pga);						//设置放大倍数0-1倍1-2倍3-4倍4-8倍5-16倍6-32倍7-64倍8-128倍9-256倍
	extern CSP_API void WINAPI CSetAd50Hz(ULONG hz);						//设置是否采用50Hz抗干扰滤波，参数hz（4个字节，无符号长整型，滤波设置，0:不滤波，1:50Hz滤波
	
	extern CSP_API BOOL WINAPI CIfUsbinited(void);
	extern CSP_API BOOL WINAPI CfBusy(void);
	
	extern CSP_API LONG WINAPI CGetGrid1(void);					//1号光栅的刻线数，如该变量为0，说明相应光栅不存在
	extern CSP_API LONG WINAPI CGetGrid2(void);							//2号光栅的刻线数，如该变量为0，说明相应光栅不存在
	extern CSP_API LONG WINAPI CGetGrid3(void);							//3号光栅的刻线数，如该变量为0，说明相应光栅不存在
	extern CSP_API LONG WINAPI CGetGrid1Wave(void);						//1号光栅的闪耀波长，如该变量为0，说明该光栅不存在
	extern CSP_API LONG WINAPI CGetGrid2Wave(void);						//2号光栅的闪耀波长，如该变量为0，说明该光栅不存在
	extern CSP_API LONG WINAPI CGetGrid3Wave(void);						//3号光栅的闪耀波长，如该变量为0，说明该光栅不存在
	extern CSP_API LONG WINAPI CGetGridIndex(void);						//当前正在使用的光栅索引号
	extern CSP_API LONG WINAPI CGetInsNo(void);							//仪器出厂编号
	extern CSP_API LONG WINAPI CGetFirmVersion(void);						//固件版本号
	extern CSP_API LONG WINAPI CGetInsType(void);							//仪器型号
	extern CSP_API LONG WINAPI CetGridSumSteps(void);
	extern CSP_API LONG WINAPI CGetFilterSumSteps(void);
	extern CSP_API LONG WINAPI CGetMirrorSumSteps(void);
	extern CSP_API LONG WINAPI CGetAdChs(void);							//模拟输入通道数0:没有模拟输入1:只有一个模拟通道2:有两个模拟通道
	extern CSP_API LONG WINAPI CGetAdMax(void);							//模拟输入AD转换最大值，分别为8位=256，12位=4096或16位=32768
	extern CSP_API LONG WINAPI CGetAdMin(void);							//模拟输入AD转换最小值，分别为8位或12位=0，16位=-32768
	extern CSP_API LONG WINAPI CGetAdPga(void);							//模拟输入可编程增益，0，2，4，8，16，32，64，256
	extern CSP_API LONG WINAPI CGetDaChs(void);							//模拟输出通道数:0-没有模拟输出；1-有一路模拟输出；2-有两路模拟输出
	extern CSP_API LONG WINAPI CGetDaMax(void);							//模拟输出最大值:0-没有模拟输出；8位=256 10位=1024 12位=4096
	extern CSP_API double WINAPI CGetAdRef(void);							//模拟输入参考电压值 2.5V 2.4V
	extern CSP_API double WINAPI CGetDaRef(void);							//模拟输出参考电压值 2.5V 2.4V
	extern CSP_API double WINAPI CGetNowWave(void);						//获得当前位置的波长
	
#ifdef __cplusplus
}
#endif

#endif
