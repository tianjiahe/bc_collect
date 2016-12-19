//-----------------------------------------------------------------------------------//
//			��Ȩ����(C) : ������Ϣ�Ƽ���ѧ���������������������޹�˾				 //
// 			˵��		: WPZϵ�ж��դ��ɫ�ǿ���ɨ�趯̬���ӿ�						 //
// 			�汾		: V2.0														 //
//-----------------------------------------------------------------------------------//
//WPZ ϵ�й�դ��ɫ����ʹ��ǰ�������Ӻ�USB�ӿڣ�Ȼ������������¶�λ�������դ���㺯����
//ʹ��ɫ�����¶�λ����ʼλ�ã��˹��̿�����Ҫ�ȴ��ϳ���ʱ�䣬��ʹ�ö��̻߳�ʱ���ȴ���
//λ�������Է�ֹ���ֳ��������ּ�������
//
#ifndef __CSP_H__
#define __CSP_H__

// 0x10-0x1FΪ��դ��������
#define GRID_INIT		0x10  //��դת̨���
#define GRID_STOP		0x11  //��դתֹ̨ͣ 
#define GRID_GOTO		0x12  //��դת̨���Զ�λ 
#define GRID_SPEED		0x13  //��դת̨�ٶ�
#define GRID_ASK		0x14  //��ѯ��դת̨λ��

#define GRID_SET1		0x18  //��դ1ת̨�㼶��
#define GRID_SET2		0x19  //��դ2ת̨�㼶��
#define GRID_SET3		0x1a  //��դ3ת̨�㼶��

// 0x20-0x28Ϊ��ɫƬ�ֵ���Ŀ�������
#define FLITER_INIT		0x20
#define FLITER_GOTO		0x21  //��ɫƬ�־��Զ�λ 0 - Init; 1-6 Win Pos 

// 0x29-0x2FΪ���⾵����Ŀ�������
#define MIRROR_INIT		0x29
#define	MIRROR_GOTO		0x2A  //���⾵���Զ�λ   0 -MIRROR1���� ; 1 - MIRROR2����

// 0x30-0x3FΪ���ݲɼ���������
#define ADC_DATA        0x30  //��ѯ���ݲɼ�����
#define ADC_CHN	        0x31  //�������ݲɼ�ͨ��	   0-Aͨ��  1-Bͨ��
#define ADC_PGA	        0x32  //�������ݲɼ�����
#define ADC_IV			0x33  //�������ݲɼ���ѹ/����ģʽ  0-����ģʽ   1-��ѹģʽ
#define ADC_MODE		0x34  //�������ݲɼ����ִ���       0 - 50Hz 1 - norminal
//#define ADC_DATA		0x35  //�������ݲɼ�����

// 0x40-0x4FΪ�������ÿ�������
#define DAC_DATA		0x40  //�������ݲɼ�����
#define DAC_CHN 		0x41  //�������ݲɼ�ͨ��

//��λ�����͸���λ���Ĳ������ͬʱ����һ�����������ݸ���λ������λ���ӵ����������ȡ���󷢸���λ��
#define CMD_TEST		0x60
#define CMD_STOP		0x61  //ִֹͣ��
//------------------------------------------------------------------------------------//
// �������0xC0-0xFF���Ϊ��Ƭ�����������������	
//------------------------------------------------------------------------------------//

// ״̬���0xC0-0xCF���Ϊ��Ƭ�������������״̬����										
#define CMD_OK			0xC0
#define CMD_ERROR		0xC1


// �������0xD0-0xDF���Ϊ��Ƭ���������������������					
#define VAL_ADC 		0xD0
#define VAL_GRID		0xD2

// ������������
// �������Ͷ���
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

	extern CSP_API BOOL UsbInited;							//USB�ӿڳ�ʼ����־��TRUE:�ѳɹ�����USB����ʼ��,FALSE:δ��ʼ��
	extern CSP_API BOOL Busy;								//��ɫ��æ��־λ��TRUE:�豸���������У�FALSE:�豸���ڵȴ�����״̬
	
	extern CSP_API LONG   G1;							//1�Ź�դ�Ŀ���������ñ���Ϊ0��˵����Ӧ��դ������
	extern CSP_API LONG   G2;							//2�Ź�դ�Ŀ���������ñ���Ϊ0��˵����Ӧ��դ������
	extern CSP_API LONG   G3;							//3�Ź�դ�Ŀ���������ñ���Ϊ0��˵����Ӧ��դ������
	extern CSP_API LONG   G1Wave;						//1�Ź�դ����ҫ��������ñ���Ϊ0��˵���ù�դ������
	extern CSP_API LONG   G2Wave;						//2�Ź�դ����ҫ��������ñ���Ϊ0��˵���ù�դ������
	extern CSP_API LONG   G3Wave;						//3�Ź�դ����ҫ��������ñ���Ϊ0��˵���ù�դ������
	extern CSP_API LONG   GridIndex;						//��ǰ����ʹ�õĹ�դ������
	extern CSP_API LONG   InsNo;							//�����������
	extern CSP_API LONG   InsType;							//�����ͺ�
	extern CSP_API LONG   GridSumSteps;						//��դת̨��תһ�ܣ�����������ߵ��ܲ���
	extern CSP_API LONG   FirmVersion;						//�̼��汾��
	extern CSP_API LONG   FilterSumSteps;					//��ɫƬ�ֵ����תһ�ܣ�����������ߵ��ܲ�����Ϊ0˵��û�а�װ��ɫƬ��
	extern CSP_API LONG   MirrorSumSteps;					//���⾵�����תһ�ܣ�����������ߵ��ܲ�����Ϊ0˵��û�а�װ���⾵
	extern CSP_API LONG   AdChs;							//ģ������ͨ����0:û��ģ������1:ֻ��һ��ģ��ͨ��2:������ģ��ͨ��
	extern CSP_API LONG   AdMax;							//ģ������ADת�����ֵ���ֱ�Ϊ8λ=256��12λ=4096��16λ=32768
	extern CSP_API LONG   AdMin;							//ģ������ADת����Сֵ���ֱ�Ϊ8λ��12λ=0��16λ=-32768
	extern CSP_API LONG   AdPga;							//ģ������ɱ�����棬0��2��4��8��16��32��64��256
	extern CSP_API LONG   DaChs;							//ģ�����ͨ����:0-û��ģ�������1-��һ·ģ�������2-����·ģ�����
	extern CSP_API LONG   DaMax;							//ģ��������ֵ:0-û��ģ�������8λ=256 10λ=1024 12λ=4096
	extern CSP_API double AdRef;							//ģ������ο���ѹֵ 2.5V 2.4V
	extern CSP_API double DaRef;							//ģ������ο���ѹֵ 2.5V 2.4V
	extern CSP_API double NowWave;						//������ǰ�Ĳ���ֵ


	extern CSP_API BOOL WINAPI CUsbLinked(void);						//����USB����
	extern CSP_API void WINAPI COpenDev(void);							//���豸
	extern CSP_API void WINAPI CCloseDev(void);							//�ر����豸������
	extern CSP_API void WINAPI CSendCmd(UCHAR cmd);						//���豸�����������cmd:���һ���ֽ�,�޷����ַ���					
	extern CSP_API void WINAPI CSendCmdData(UCHAR cmd, ULONG x);			//���豸������������ݣ�����cmd:���һ���ֽ�,�޷����ַ�����dat:����(4���ֽڣ�������)	
	extern CSP_API BOOL WINAPI CReadCmdData(UCHAR &cmd,LONG &dat) ;		//��ȡ�豸�ϴ�����������ݣ�����cmd:�����ϴ������һ���ֽ�,�޷����ַ�����dat:�����ϴ�������(4���ֽڣ�������)
	extern CSP_API BOOL WINAPI CDevInit(void);							//��ʼ���豸
	extern CSP_API void WINAPI CSetSpeed(ULONG speed);					//���ù�դ�����ٶȣ�0~9���ٶȣ���ֵԽ���ٶ�Խ��
	extern CSP_API void WINAPI CGridInit(void);							//��ʼ����դ
	extern CSP_API void WINAPI CGotoZero(ULONG gindex);				//ʹ��դ��λ���㼶��λ�ã�����GridIndex:ָ����դ��ţ�4���ֽڣ��޷��ų����ͣ�
	extern CSP_API void WINAPI CGotoWave(ULONG gindex,double wave);	//ʹ��դ��λ������waveָ������λ�ã�����GridIndex����դ������wave������
	extern CSP_API void WINAPI CStop(void);								//ֹͣ��դ����
	extern CSP_API void WINAPI CGetCurWave(void);						//����λ������ָ���õ�ǰλ�ò���	
	extern CSP_API void WINAPI CSetAdChannel(ULONG ch);					//ѡ��ADת��ͨ��������ch:ͨ���ţ�4���ֽڣ��޷��ų�����)0:ͨ��1��1:ͨ��2
	extern CSP_API void WINAPI CSetAdPGA(ULONG pga);						//���÷Ŵ���0-1��1-2��3-4��4-8��5-16��6-32��7-64��8-128��9-256��
	extern CSP_API void WINAPI CSetAd50Hz(ULONG hz);						//�����Ƿ����50Hz�������˲�������hz��4���ֽڣ��޷��ų����ͣ��˲����ã�0:���˲���1:50Hz�˲�
	
	extern CSP_API BOOL WINAPI CIfUsbinited(void);
	extern CSP_API BOOL WINAPI CfBusy(void);
	
	extern CSP_API LONG WINAPI CGetGrid1(void);					//1�Ź�դ�Ŀ���������ñ���Ϊ0��˵����Ӧ��դ������
	extern CSP_API LONG WINAPI CGetGrid2(void);							//2�Ź�դ�Ŀ���������ñ���Ϊ0��˵����Ӧ��դ������
	extern CSP_API LONG WINAPI CGetGrid3(void);							//3�Ź�դ�Ŀ���������ñ���Ϊ0��˵����Ӧ��դ������
	extern CSP_API LONG WINAPI CGetGrid1Wave(void);						//1�Ź�դ����ҫ��������ñ���Ϊ0��˵���ù�դ������
	extern CSP_API LONG WINAPI CGetGrid2Wave(void);						//2�Ź�դ����ҫ��������ñ���Ϊ0��˵���ù�դ������
	extern CSP_API LONG WINAPI CGetGrid3Wave(void);						//3�Ź�դ����ҫ��������ñ���Ϊ0��˵���ù�դ������
	extern CSP_API LONG WINAPI CGetGridIndex(void);						//��ǰ����ʹ�õĹ�դ������
	extern CSP_API LONG WINAPI CGetInsNo(void);							//�����������
	extern CSP_API LONG WINAPI CGetFirmVersion(void);						//�̼��汾��
	extern CSP_API LONG WINAPI CGetInsType(void);							//�����ͺ�
	extern CSP_API LONG WINAPI CetGridSumSteps(void);
	extern CSP_API LONG WINAPI CGetFilterSumSteps(void);
	extern CSP_API LONG WINAPI CGetMirrorSumSteps(void);
	extern CSP_API LONG WINAPI CGetAdChs(void);							//ģ������ͨ����0:û��ģ������1:ֻ��һ��ģ��ͨ��2:������ģ��ͨ��
	extern CSP_API LONG WINAPI CGetAdMax(void);							//ģ������ADת�����ֵ���ֱ�Ϊ8λ=256��12λ=4096��16λ=32768
	extern CSP_API LONG WINAPI CGetAdMin(void);							//ģ������ADת����Сֵ���ֱ�Ϊ8λ��12λ=0��16λ=-32768
	extern CSP_API LONG WINAPI CGetAdPga(void);							//ģ������ɱ�����棬0��2��4��8��16��32��64��256
	extern CSP_API LONG WINAPI CGetDaChs(void);							//ģ�����ͨ����:0-û��ģ�������1-��һ·ģ�������2-����·ģ�����
	extern CSP_API LONG WINAPI CGetDaMax(void);							//ģ��������ֵ:0-û��ģ�������8λ=256 10λ=1024 12λ=4096
	extern CSP_API double WINAPI CGetAdRef(void);							//ģ������ο���ѹֵ 2.5V 2.4V
	extern CSP_API double WINAPI CGetDaRef(void);							//ģ������ο���ѹֵ 2.5V 2.4V
	extern CSP_API double WINAPI CGetNowWave(void);						//��õ�ǰλ�õĲ���
	
#ifdef __cplusplus
}
#endif

#endif
