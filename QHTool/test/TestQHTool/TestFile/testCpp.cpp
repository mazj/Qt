// AutoModelStrc.cpp: implementation of the CAutoModelStrc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "csi200emanage.h"
#include "AutoModelStrc.h"
#include "DrawDoc.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CAutoModelStrc, CObject, VERSION_NO)

#define CM3_AR_MUST

#define CM3_AM_LNG	10
static CStringArray locLng[CM3_AM_LNG];

static void initLocLng()
{
	locLng[0].Add(_T("DI"));
	locLng[0].Add(_T("DI"));

	locLng[1].Add(LTR("����ʧ�ܣ�\n�������ļ�·������"));
	locLng[1].Add(_T("Export failed!\nMaybe file path err!"));

	locLng[2].Add(LTR("��Ͷ��"));
	locLng[2].Add(_T("Offline"));

	locLng[3].Add(LTR("����"));
	locLng[3].Add(_T("DO "));

	locLng[4].Add(LTR("����"));
	locLng[4].Add(_T("DI "));

	locLng[5].Add(LTR("ֱ��"));
	locLng[5].Add(_T("DC "));

	locLng[6].Add(LTR("�¶�"));
	locLng[6].Add(_T("T "));

	locLng[7].Add(LTR("��λ"));
	locLng[7].Add(_T("Tap "));

	locLng[8].Add(LTR("GoDI"));
	locLng[8].Add(_T("GoDI"));

}

static CString GetLocLngStr(int nID)
{
	return g_pVcTrlocLng->translate(locLng[nID].GetAt(ELangChinese), g_ctstrLanguage[g_bLng]);
}

void TcharCopy(TCHAR *dest,CString strTmp)
{
	/*USES_CONVERSION;
	LPSTR lpstr = T2A(strTmp.GetBuffer(1));
	int nLen = strlen(lpstr);
	_tcsncpy(dest,strTmp,nLen);
	dest[nLen] = _T('\0');*/
	// tian_wait modify
	LPCTSTR source = strTmp;
	_tcsncpy(dest, source, _tcslen(source));

}
CAutoModelStrc::CAutoModelStrc()
{
	m_pDev = NULL;

 	memset(&m_aDI,0,sizeof(m_aDI));
 	memset(&m_aAI,0,sizeof(m_aAI));
 	memset(&m_aDT,0,sizeof(m_aDT));
	memset(&m_aGO1DI1,0,sizeof(m_aGO1DI1));
	memset(&m_aGO1DI2,0,sizeof(m_aGO1DI2));
	memset(&m_aGO1DI3,0,sizeof(m_aGO1DI3));
	memset(&m_aGO1DT,0,sizeof(m_aGO1DT));
	memset(&m_aGO1Tap,0,sizeof(m_aGO1Tap));
//	memset(&m_aGO1DT2,0,sizeof(m_aGO1DT2));
	memset(&m_aGODO,0,sizeof(m_aGODO));
	memset(&m_aMidRel,0,sizeof(m_aMidRel));
 
 	memset(&m_dtMeas,0,sizeof(CM3_DEV_MEAS_CFG_TYPE));
 
 	memset(&m_lockDev,0,sizeof(m_lockDev));

	m_bakbak1=0;
	m_bakbak2=0;
	memset(m_bakbak3,0,sizeof(m_bakbak3));
	initLocLng();

	/*InitDevStrc2();*/

	m_strIcdName.Empty();
	m_transProAlm = 0;
	m_proSoftConn = 0;
	m_transProEvt = 0;
	int m_InitEnable = 0;
	int	m_GO2DoublePointConfig = -1;
	int m_GO3DoublePointConfig = -1;
}

CAutoModelStrc::~CAutoModelStrc()
{

}
struct Config_Struct
{
	Config_Struct()
		:	configNo(0)
	{
	}
	
	int configNo;
	CString configRight;
	CString configLeft;
};
bool getSectionInf(const CString strInf,Config_Struct & getConfig_Str)
{
	
	CString newTemp = strInf;
	int pos = newTemp.Find(_T("="));
	if(pos<0)
	{
		return false;
	}
	CString strVarName=newTemp.Left(pos);
	getConfig_Str.configLeft = strVarName;
	CString strValue = newTemp.Mid(pos+1);
	int iGet=strVarName.Find(_T("_"));
	CString strNo=strVarName.Mid(iGet+1);
	getConfig_Str.configNo = _ttoi(strNo);
	getConfig_Str.configRight= strValue;
	return true;
}
int CAutoModelStrc::ReadIniFile()
{
	CStdioFile INIFile;
	CString strFileName;
	CString  strSection;
	CSIChar dbPath[256];
	GetModuleFileName(NULL, dbPath, sizeof(dbPath));

	CString sPath = dbPath;
	int nPos;
	nPos=sPath.ReverseFind ('\\');
	strFileName = sPath.Left (nPos);
	strFileName=strFileName +_T("\\CSI200EManage.ini");

	if (strFileName.IsEmpty())
	{
		return 1;
	}
	int iOpen=INIFile.Open(strFileName, CFile::modeRead|CFile::typeText);
	if (iOpen<=0)
	{
		//CString temAZ="���ļ�ʧ�ܣ�"+strFileName;
		//AfxMessageBox(temAZ);
		return 2;
	}
	CString strBuf,temHead,Head;
	int secType=0;
	std::vector<Config_Struct> toolPsdList;
	while(INIFile.ReadString(strBuf))
	{
		Head="";
		if (strBuf.Find(_T(";"))>=0)
		{
			continue;
		}
		
		if (strBuf.Find(_T("[InitGOOSEDouble]"))>=0)
		{
			secType=2;
			continue;
		}
		int pos = strBuf.Find(_T("="));
		if(pos<0)
		{
			continue;
		}
		switch(secType)
		{
		case 2:
			{
				Config_Struct  temConfig_Str;
				getSectionInf(strBuf,temConfig_Str);
				temConfig_Str.configLeft.TrimRight();
				temConfig_Str.configLeft.TrimLeft();
				temConfig_Str.configRight.TrimRight();
				temConfig_Str.configRight.TrimLeft();
				CString str = temConfig_Str.configLeft;
				if (str=="InitEnable")
				{
					m_InitEnable= _ttoi(temConfig_Str.configRight);
				}
				else if (str=="GO2DoublePointConfig")
				{
					m_GO2DoublePointConfig = _ttoi(temConfig_Str.configRight);
				}
				else if (str=="GO3DoublePointConfig")
				{
					m_GO3DoublePointConfig = _ttoi(temConfig_Str.configRight);
				}
				
				strBuf="";
				
			}
			break;
		}
		
	}
	return 0;
	
}

/** ����һ��CAutoModelStrcʵ�����ú���ֻ����һ��
  * ���Ժ��ʹ���У�����ʵ�ʵ����ã���������CAutoModelStrc
  */
void CAutoModelStrc::InitDevStrc2()
{
	int i,j;
	int nTmp;
	CString strDesc;

	m_docIcd.m_pAM = this;
	m_bNoSync =0;
	m_bSVEna = 0;
	m_bHasPrgOp=0;
	m_bMidRelayST=0;
	ReadIniFile();
	memset(&m_aDI,0,sizeof(m_aDI));
	memset(&m_aAI,0,sizeof(m_aAI));
	memset(&m_aDT,0,sizeof(m_aDT));
	//V4.0����Go����
	memset(&m_aGO1DI1,0,sizeof(m_aGO1DI1));
	memset(&m_aGO1DI2,0,sizeof(m_aGO1DI2));
	memset(&m_aGO1DI3,0,sizeof(m_aGO1DI3));
	memset(&m_aGO1DT,0,sizeof(m_aGO1DT));
	memset(&m_aGO1Tap,0,sizeof(m_aGO1Tap));
	memset(&m_aMidRel,0,sizeof(m_aMidRel));
	memset(&m_aGODO,0,sizeof(m_aGODO));
	
	memset(&m_dtMeas,0,sizeof(CM3_DEV_MEAS_CFG_TYPE));
	
	memset(&m_lockDev,0,sizeof(m_lockDev));
	m_strIcdName.Empty();

	m_docIcd.InitStr();
	MEM_0(m_aRC);
	MEM_0(m_aDO);

	//MEM_0(m_aGO1RC);
	//MEM_0(m_aGO1DO);

	CM3_DI_GRP_INFO	*pGrp;
	CM3_DI_INFO		*pInfo;

	for (i=0;i<CM3_DEV_DI_CARD_MAX;++i)
	{
		m_aDI.wFstPos[i] = i*CM3_DEV_DI_GRP_MAX;
	}

	/* װ�����п����� */
	for (i=0;i<CM3_DEV_DI_GRP_ALL_MAX;++i)
	{
		pGrp = &(m_aDI.grp[i]);
		/* ÿ��CPU 8�� */
		pGrp->bCpuIdx = (BYTE)(i/8);
		/* �����Ŵ�0��ʼ����7 */
		pGrp->bIdx = (BYTE)(i%8);
		pGrp->bNum = CM3_GET_DI_NUM_IN_GRP(pGrp->bIdx);
		pGrp->bGlbIdx = i;

		for (j=0;j<CM3_DEV_DI_MAX;++j)
		{
			pInfo = &(pGrp->info[j]);
			pInfo->bCpuIdx = pGrp->bCpuIdx;
			pInfo->bGrpIdx = pGrp->bIdx;
			pInfo->bIdx = j;

			nTmp = pInfo->bCpuIdx*48 +1+j;
			nTmp+= ( (pInfo->bGrpIdx/2)*12 );
			if((pInfo->bGrpIdx%2)==1)	nTmp+=8;

			pInfo->wNo = nTmp;

			strDesc.Format(_T(" %2d"),nTmp);
			strDesc=_T("(")+GetLocLngStr(0)+strDesc+_T(")");
			CM3_CP(pInfo->desc,strDesc);

			pInfo->bGlbIdx = i;
		}
	}

	CM3_AI_INFO	*pAI;

	for (i=0;i<CM3_DEV_AI_CARD_MAX;++i)
	{
		m_aAI.wFstPos[i] = i*CM3_DEV_AI_MAX;
	}

	for (i=0;i<CM3_DEV_AI_ALL_MAX;++i)
	{
		pAI = &(m_aAI.info[i]);

		pAI->bCpuIdx = i/CM3_DEV_AI_MAX;
		pAI->bIdx = i%CM3_DEV_AI_MAX;
		CM3_CP(pAI->desc,pAI->en);
	}


	CM3_DT_INFO	*pDT;
	
	for (i=0;i<CM3_DEV_DT_CARD_MAX;++i)
	{
		m_aDT.wFstPos[i] = i*CM3_DEV_DT_MAX;
	}
	
	for (i=0;i<CM3_DEV_DT_ALL_MAX;++i)
	{
		pDT = &(m_aDT.info[i]);
		
		pDT->bCpuIdx = i/CM3_DEV_DT_MAX;
		pDT->bIdx = i%CM3_DEV_DT_MAX;
		CM3_CP(pDT->desc,pDT->en);
	}
	

	//��ʼ��Go DT cpu
	for (i=0;i<CM4_GO_SUB_DT_CPU_NUM;++i)
	{
		m_aGO1DT.wNum=CM4_GO_SUB_DT_MAX;
		m_aGO1DT.bCPUUsed[i] = 1;
		m_aGO1DT.bCPUNum[i]=CM4_GO_SUB_DT_NUM;
		m_aGO1DT.wFstRow[i]=i*CM4_GO_SUB_DT_NUM+1;
		m_aGO1DT.wFstPos[i] = i*CM4_GO_SUB_DT_NUM;
	}
	for (i=0;i<CM4_GO_SUB_DT_MAX;++i)
	{
		pDT = &(m_aGO1DT.info[i]);
		
		pDT->bCpuIdx = i/CM4_GO_SUB_DT_NUM+2;//goģ��ֱ��cpu����ֱ��cpu����
		pDT->bIdx = i%CM4_GO_SUB_DT_NUM;
		pDT->bType=3;//ͨ������
		pDT->bNo=i;//
		CString strDesc;
		strDesc.Format(_T("GO DT%d"),i+1);
		//strDesc=_T("(")+GetLocLngStr(9)+strDesc+_T(")");
		CM3_CP(pDT->desc,strDesc);
	}

	//��ʼ��Go Tap cpu
	CM4_GO_TAP_INFO	*pTAP;
	for (i=0;i<CM4_GO_SUB_TAP_CPU_NUM;++i)
	{
		m_aGO1Tap.wNumGoTap=CM4_GO_SUB_TAP_MAX;
		m_aGO1Tap.bCPUUsed[i]=0;
		m_aGO1Tap.bCPUNum[i]=CM4_GO_SUB_TAP_NUM;
	}
	for (i=0;i<CM4_GO_SUB_TAP_CPU_NUM;++i)
	{
		pTAP= &(m_aGO1Tap.goInfo[i]);
		pTAP->bCpuIdx=1;
		strDesc.Format(_T("GO TAP%d"),i+1);
		CM3_CP(pTAP->desc,strDesc);
		pTAP->bTapCtrl=FALSE;
		pTAP->bTapMul=FALSE;
	}

	InitGubSubDIStrc(&m_aGO1DI1,CM4_GO_SUB_CPU1_ADDR);//Gooseģ��ڶ���cpu��ַ��3��ʼ
	InitGubSubDIStrc(&m_aGO1DI2,CM4_GO_SUB_CPU1_ADDR+2);//Gooseģ��ڶ���cpu��ַ��5��ʼ
	InitGubSubDIStrc(&m_aGO1DI3,CM4_GO_SUB_CPU1_ADDR+4);//Gooseģ��ڶ���cpu��ַ��7��ʼ
}


//��ʼ��Go����
void CAutoModelStrc::InitGubSubDIStrc(CM3_DI_GRP_ALL_INFO * mGODIGrp,int cpuInitNum)
{
	int i,j;
	int nTmp;
	int bCtrlObj = CM4_GO_SUB_DI_CPU1_CTRLNO;
    int descid = -1;
	CString strDesc;
	
	mGODIGrp->wRows=CM4_GO_SUB_DI_CPU_NUM*CM4_GO_SUB_DI_NUM;
	mGODIGrp->bGrps=CM4_GO_SUB_CARGRP_NUM;
	mGODIGrp->bTapPhase=0;
	mGODIGrp->bTapCtrl=TRUE;
	mGODIGrp->bTapSV=FALSE;
	
	for (i=0;i<CM4_GO_SUB_DI_CPU_NUM;++i)
	{	
		mGODIGrp->bCPUUsed[i]= 1;
		mGODIGrp->bCPUNum[i]= CM4_GO_SUB_DI_NUM;
		mGODIGrp->bGrpNum[i]= CM4_GO_SUB_CPUGRP_NUM;
		mGODIGrp->bRows[i]= CM4_GO_SUB_DI_NUM;
		mGODIGrp->wFstRow[i]= i*CM4_GO_SUB_DI_NUM+1;
		mGODIGrp->wFstPos[i] = i*CM4_GO_SUB_CPUGRP_NUM;
	}
	
	/* GOOSE ���Ŀ���1 */
	for (i=0;i<CM4_GO_SUB_CARGRP_NUM;++i)
	{
		BYTE bCpuIdx,bIdx;

		bCpuIdx=(BYTE)(i/8)+cpuInitNum-1;
		mGODIGrp->grp[i].bCpuIdx = bCpuIdx;

		/* �����Ŵ�0��ʼ����7 */
		bIdx=(BYTE)(i%8);
		mGODIGrp->grp[i].bIdx = bIdx;

		mGODIGrp->grp[i].bNum = CM3_GET_DI_NUM_IN_GRP(bIdx);

		mGODIGrp->grp[i].bGlbIdx = i;

		mGODIGrp->grp[i].bType =0x03;

		for (j=0;j<mGODIGrp->grp[i].bNum;++j)
		{
			mGODIGrp->grp[i].info[j].bCpuIdx=bCpuIdx;
			mGODIGrp->grp[i].info[j].bGrpIdx = bIdx;
			mGODIGrp->grp[i].info[j].bIdx = j;
			
			nTmp = (bCpuIdx-cpuInitNum+1)*48 +1+j;
			nTmp+= ( (bIdx/2)*12 );
			if((bIdx%2)==1)	nTmp+=8;
			
			mGODIGrp->grp[i].info[j].wNo = nTmp;

			int cpuNo;
			switch (cpuInitNum)
			{
			case 3:
			case 5: 
			case 7: 
				{
					//��־��˵�޸�GOOSE�����2��3��1һ��ǰ24������Ĭ��Ϊ˫λ�ÿ���
					if (cpuInitNum==3)
					{
						cpuNo=1;
						SetGoConfigDefault(mGODIGrp,i,j,bCtrlObj);
						break;
					} 
					else if (cpuInitNum==5)
					{
						cpuNo=2;
						if (m_InitEnable==1&&m_GO2DoublePointConfig==1)
						{
							SetGoConfigDefault(mGODIGrp,i,j,bCtrlObj);
						}
						break;
						
					}
					else if (cpuInitNum==7)
					{
						cpuNo=3;
						if (m_InitEnable==1&&m_GO2DoublePointConfig==1)
						{
							SetGoConfigDefault(mGODIGrp,i,j,bCtrlObj);
						}
						break;
					}
					break;
				}
			default: cpuNo=0;break;
			}

			if ((cpuNo == 1)&&(i < 4))//�����1��ǰ24����������������
			{
				if (descid < 12)//˫λ�ã�24�������Ӧ12������
				{
					if (CM3_DI_IDX_DPI(j))
						descid++;
										
					CM3_CP(mGODIGrp->grp[i].info[j].desc, (LPCTSTR)langTrans(GOOSE_SUB_DI1_DESC[descid][ELangChinese]));
				}
			}
			else
			{
				strDesc.Format(_T("GO%d DI%d"),cpuNo,nTmp);
				//strDesc=_T("(")+GetLocLngStr(8)+strDesc+_T(")");
				CM3_CP(mGODIGrp->grp[i].info[j].desc,strDesc);
			}
			mGODIGrp->grp[i].info[j].bGlbIdx = i;			
		}
	}
}

/** �ڵ����Զ���ģ�Ի���ʱ����
  * ��װ�������л�ȡ��Ϣ���Զ���ģ�ṹ
  */
void CAutoModelStrc::GetFromDevCfg(CCSI200EDev *pDev)
{
	if(pDev==NULL)
		return;

	m_pDev = pDev;

	GetDIAll();
	GetAIAll();
	GetDTAll();
	GetRCAll();
	GetGOSubTAP();
}



int CAutoModelStrc::GetAIAll()
{
	int	i,j,nCardIdx;
	int	nSize ;
	int nRet = 0;


	/* ������������
	 * ������������Զ���ģ���ӵ��������ã�������
	 * ��Ҫ����ЩCPUͶ�룬��Щ��Ϣ����
	 */

	memset(m_aAI.bCPUUsed,0,sizeof(m_aAI.bCPUUsed));
	memset(m_aAI.bCPUNum,0,sizeof(m_aAI.bCPUNum));
	memset(m_aAI.bPos,0,sizeof(m_aAI.bPos));
	WORD oldNum=m_aAI.wNum,newNum=0;
	m_aAI.wNum = 0;
	
	nSize = m_pDev->m_aAI.GetSize();
	if(nSize<=0)
		return nRet;

	for (i=0;i<nSize;++i)
	{
		nCardIdx = CM3_GET_AI_CPU_IDX(m_pDev->m_aAI[i].wCpuAddr);
		m_aAI.bCPUUsed[nCardIdx] = 1;
		m_aAI.bCPUNum[nCardIdx] = (BYTE)(m_pDev->m_aAI[i].wCpuGateNum);
		newNum += m_aAI.bCPUNum[nCardIdx];
	}

	nSize = m_pDev->m_aGateAI.GetSize();
	if(nSize<=0)
		return nRet;

	CM3_AI_INFO	*pInfo;
	
	for (i=0;i<nSize;++i)
	{
		nCardIdx = CM3_GET_AI_CPU_IDX(m_pDev->m_aGateAI[i].wCpuAddr);

		j = m_aAI.wFstPos[nCardIdx] + m_aAI.bPos[nCardIdx];

		pInfo = &(m_aAI.info[j]);
		pInfo->bType = m_pDev->m_aGateAI[i].nCardGateType;
		pInfo->bNo = m_pDev->m_aGateAI[i].bCardGateId;
		pInfo->bPhase = m_pDev->m_aGateAI[i].nGatePhase;
		pInfo->nCnID = m_pDev->m_aGateAI[i].bChineseID;
		CString str = m_pDev->m_aGateAI[i].strEnglishName;
		CM3_CP(pInfo->en, str);
		if(newNum!=oldNum || S_LEN_0(pInfo->desc))
			CM3_CP(pInfo->desc,pInfo->en);

		m_aAI.bPos[nCardIdx]++;
	}

	/* ͳ��װ�ý������� */
	for (i=0;i<CM3_DEV_AI_CARD_MAX;++i)
	{
		if(m_aAI.bCPUUsed[i]==1)
		{
			m_aAI.wFstRow[i] = m_aAI.wNum + 1;

			m_aAI.wNum += m_aAI.bCPUNum[i];
		}
	}

	return nRet;
}

int CAutoModelStrc::GetDTAll()
{
	int	i,j,nCardIdx;
	int	nSize ;
	int nRet = 0;

	memset(m_aDT.bCPUUsed,0,sizeof(m_aDT.bCPUUsed));
	memset(m_aDT.bCPUNum,0,sizeof(m_aDT.bCPUNum));
	memset(m_aDT.bPos,0,sizeof(m_aDT.bPos));
	WORD oldNum=m_aDT.wNum,newNum=0;
	m_aDT.wNum = 0;
	
	nSize = m_pDev->m_aDT.GetSize();
	if(nSize<=0)
		return nRet;
	
	for (i=0;i<nSize;++i)
	{
		nCardIdx = CM3_GET_DT_CPU_IDX(m_pDev->m_aDT[i].wCpuAddr);
		m_aDT.bCPUUsed[nCardIdx] = 1;
		m_aDT.bCPUNum[nCardIdx] = (BYTE)(m_pDev->m_aDT[i].wCpuGateNum);
		newNum += m_aDT.bCPUNum[nCardIdx];
	}
	
	nSize = m_pDev->m_aGateDT.GetSize();
	if(nSize<=0)
		return nRet;
	
	CM3_DT_INFO	*pInfo;
	
	for (i=0;i<nSize;++i)
	{
		nCardIdx = CM3_GET_DT_CPU_IDX(m_pDev->m_aGateDT[i].wCpuAddr);
		
		j = m_aDT.wFstPos[nCardIdx] + m_aDT.bPos[nCardIdx];
		
		pInfo = &(m_aDT.info[j]);
		pInfo->bType = m_pDev->m_aGateDT[i].nCardGateType;
		pInfo->bNo = m_pDev->m_aGateDT[i].bCardGateId;
		pInfo->bProption = m_pDev->m_aGateDT[i].bProption;
		pInfo->nCnID = m_pDev->m_aGateDT[i].bChineseID;
		CString str = m_pDev->m_aGateDT[i].strEnglishName;
		CM3_CP(pInfo->en,str);
		if(newNum!=oldNum || S_LEN_0(pInfo->desc))
			CM3_CP(pInfo->desc,pInfo->en);
	
		m_aDT.bPos[nCardIdx]++;
	}
	
	/* ͳ��װ��ֱ������ */
	for (i=0;i<CM3_DEV_DT_CARD_MAX;++i)
	{
		if(m_aDT.bCPUUsed[i]==1)
		{
			m_aDT.wFstRow[i] = m_aDT.wNum + 1;

			m_aDT.wNum += m_aDT.bCPUNum[i];
		}
	}
	
	return nRet;
}
int CAutoModelStrc::GetDIAll()
{
	int	i,j,k,nCardIdx;
	int	nSize ;
	int nRet = 0;
	
	memset(m_aDI.bCPUUsed,0,sizeof(m_aDI.bCPUUsed));
	memset(m_aDI.bCPUNum,0,sizeof(m_aDI.bCPUNum));
	memset(m_aDI.bGrpNum,0,sizeof(m_aDI.bGrpNum));
	memset(m_aDI.bRows,0,sizeof(m_aDI.bRows));
	memset(m_aDI.wFstRow,0,sizeof(m_aDI.wFstRow));

	m_aDI.wRows = 0;
	m_aDI.bGrps = 0;
	m_aDI.bTapPhase = 0;

	nSize = m_pDev->m_aDI.GetSize();
	if(nSize<=0)
		return nRet;

	for (i=0;i<nSize;++i)
	{
		nCardIdx = CM3_GET_DI_CPU_IDX(m_pDev->m_aDI[i].wCpuAddr);
		m_aDI.bCPUUsed[nCardIdx] = 1;
		m_aDI.bCPUNum[nCardIdx] = (BYTE)(m_pDev->m_aDI[i].wCpuGateNum);
		m_aDI.bGrpNum[nCardIdx] = m_aDI.bCPUNum[nCardIdx]/6;
	}

	nSize = m_pDev->m_aGateDI.GetSize();
	if(nSize<=0)
		return nRet;

	CM3_DI_GRP_INFO *pGrp;

	for (i=0;i<nSize;++i)
	{
		nCardIdx = CM3_GET_DI_CPU_IDX(m_pDev->m_aGateDI[i].wCpuAddr);
		j = m_aDI.wFstPos[nCardIdx] + m_pDev->m_aGateDI[i].bGroupId;

		pGrp = &(m_aDI.grp[j]);

		pGrp->bType = m_pDev->m_aGateDI[i].nCardGateType;
	}

	/* ȷ���Ƿ���൵λ */
	if(m_aDI.grp[0].bType == 1 && m_aDI.grp[2].bType == 1)
		m_aDI.bTapPhase = 1;

	if(m_aDI.bTapPhase==0)
		m_aDI.bTapSV = FALSE;

	CM3_DI_INFO	*pInfo;

	for (i=0;i<CM3_DEV_DI_CARD_MAX;++i)
	{
		if(m_aDI.bCPUUsed[i]==0)
			continue;

		/*for (j=0;j<CM3_DEV_DI_GRP_MAX;++j)*/
		for (j=0;j<m_aDI.bGrpNum[i];++j)
		{
			/* ��ǰCPU���ƫ�� */
			nCardIdx = m_aDI.wFstPos[i] + j;
			pGrp = &(m_aDI.grp[nCardIdx]);
			
			if (pGrp->bType==3 || pGrp->bType ==4)
			{
				for (k=0;k<pGrp->bNum;++k)
				{
					/* ˫λ��ֻ��0 2 4 6 */
					if(pGrp->bType==4 && (k%2)==1)
						continue;

					pInfo = &(pGrp->info[k]);

					pInfo->bDPIGrp = (pGrp->bType==4)? 1 : 0;
					
					m_aDI.wRows++;
					m_aDI.bRows[i]++;
				}
			}
			else
			{
				/* ��Ͷ�룬���壬�ֽ�ͷ���ֽ�ͷ����ʱ��ֻ��һ�� */
				if(pGrp->bType==1 && j==2)
					continue;

				m_aDI.wRows++;
				m_aDI.bRows[i]++;
			}
		}
	}

	for (i=0;i<CM3_DEV_DI_CARD_MAX;++i)
	{
		if(m_aDI.bCPUUsed[i]==0)
			continue;

		m_aDI.bGrps += m_aDI.bGrpNum[i];

		if(i==0)	
			m_aDI.wFstRow[i] = 1;
		else
		{
			m_aDI.wFstRow[i] = m_aDI.wFstRow[i-1] + m_aDI.bRows[i-1] ;
		}
	}

	/* �������ԭ�������ý��м�⣬�Ƿ����
	 * �����Ƿ���λ�ý���ʱ��������6�������Ƿ��ڿ�������÷�Χ�����������m_aDI.bGrps
	 * ��������������װ�����û�ȡ�����ܸı�
	 */

	NormalCfg(&m_aDI);

	return nRet;
}

int CAutoModelStrc::GetGOSubTAP()
{
	int nRet = 0;

	if (m_pDev->m_aGoCPUEn.GetSize()<=0) return 0;
	int nTap=m_pDev->m_aGoCPUEn[0].goTapNum;
	if (nTap<=0) 
	{
		m_aGO1Tap.bCPUUsed[0]=0;
		return 0;
	}
	
	if (nTap==1)
	{
		m_aGO1Tap.bCPUUsed[0]=1;
		m_aGO1Tap.bCPUNum[0]=nTap;
		//m_aGO1Tap.wFstPos[0]=1;
		m_aGO1Tap.wFstPos[0]=0;
		m_aGO1Tap.goInfo[0].bTapPhase=0;
		nRet=1;
	}
	else if (nTap==3)
	{
		m_aGO1Tap.bCPUUsed[0]=1;
		m_aGO1Tap.bCPUNum[0]=nTap;
		//m_aGO1Tap.wFstPos[0]=1;
		m_aGO1Tap.wFstPos[0]=0;
		m_aGO1Tap.goInfo[0].bTapPhase=1;
		nRet=1;
	}
	return nRet;
}

BOOL CAutoModelStrc::ExportIcd(CString strFile)
{	
	/* �ȼ���ģ��ģ�� */
	if(m_docIcd.IsValid())
		m_docIcd.Release();

//	if(!m_docIcd.IsValid())
	{
		if(m_docIcd.LoadFromRc()==FALSE)
			return FALSE;
	}

	//�����ļ�����ķ��ʵ� V4.0����
	if (!m_docIcd.SetOutPutAP(CM4_ICD_AP_MMS))
		return FALSE;

	MapCommon();

	MapMeas();

	MapDI();

	//�����������������ģ����û�õģ�V4.0����ɾ�����ʵ�����
	//m_docIcd.ClrDTT();

	if(m_docIcd.SaveAsXmlFile(1,strFile)!=TRUE)
	{
		CString str=strFile+_T("\n\n");
		AfxMessageBox(str+GetLocLngStr(1));

		return FALSE;
	}
	
	//V4.03���Ӽ���ICD�ļ�CRC
	Cal_ModelFile_CRC(strFile);

	return TRUE;
}
BOOL CAutoModelStrc::ExportIcd(CString strFile,int outPutAP,int outPutRef)
{	
	/* �ȼ���ģ��ģ�� */
	if(m_docIcd.IsValid())
		m_docIcd.Release();

	if (outPutAP<0 ||outPutAP>2) return FALSE;
	if (outPutRef<0 ||outPutRef>3) return FALSE;
	
	//	if(!m_docIcd.IsValid())
	{
		if(m_docIcd.LoadFromRc()==FALSE)
			return FALSE;
	}
	
	//�����ļ�����ķ��ʵ� V4.0����
	if (!m_docIcd.SetOutPutAP(outPutAP))
		return FALSE;

	//����MMSģ��
	MapCommon();
	MapMeas();
	MapDI();

	//����GOOSEģ��
	//MapTRIP();
	MapTRIPByConfig();//v4.20

	
	if(m_docIcd.SaveAsXmlFile(2,strFile)!=TRUE)
	{
		CString str=strFile+_T("\n\n");
		AfxMessageBox(str+GetLocLngStr(1));
		
		return FALSE;
	}
	
	//V4.03���Ӽ���ICD�ļ�CRC
	Cal_ModelFile_CRC(strFile);

	return TRUE;
}


typedef signed char				sint8;					// 1 byte 
typedef unsigned char			uint8;					// 1 byte
typedef signed short			sint16;					// 2 byte
typedef unsigned short			uint16;					// 2 byte
typedef signed int				sint32;					// 4 byte
typedef unsigned int			uint32;					// 4 byte
uint16 CalSingleCharCrc_SiFang(uint16 u16crc, uint8 input)
{
    uint8 i;
    uint8 temp;
    temp = input;
    
    for ( i = 0 ; i < 8 ; i ++ )
    {
        if (( temp & 0x80 ) == 0x80 )
        {
            if (( u16crc & 0x8000 ) == 0 )
            {
                u16crc ^= 0x0810 ;
                u16crc = u16crc<<1 ;
                u16crc = u16crc|0x0001 ;
            }
            else
            {
                u16crc = u16crc<<1 ;
                u16crc = u16crc&0xfffe ;                                                                                                                                                                                                                                                                                                                                                                                        
            }                                                                                                                                                                                                                                                                                                                                                                                                       
        }
        else                                                                                                                                                                                                                                                                                                                                                                                                           
        {
            if (( u16crc & 0x8000 ) != 0 )
            {
                u16crc ^= 0x0810 ;
                u16crc = u16crc<<1 ;
                u16crc = u16crc|0x00001 ;
            }                                                                                                                                                                                                                                                                                                                                                                                                      
            else                                                                                                                                                                                                                                                                                                                                                                                                      
            {
                u16crc = u16crc<<1 ;
                u16crc = u16crc&0xfffe ;
            }                                                                                                                                                                                                                                                                                                                                                                                                       
        }                                                                                                                                                                                                                                                                                                                                                                                                            
        temp = temp<<1 ;
    }
    return(u16crc&0xffff);
}  

void CAutoModelStrc::Cal_ModelFile_CRC(CString strFileName)
{
	//���ı��ļ���ʽ��XML�ļ�����UTF-8���밴���봦��
	TRACE("cal CRC st:%s\n",GetTime());
	CFile fr;
	if(fr.Open (strFileName,CFile::modeRead) == FALSE)
	{
		AfxMessageBox(_T("file open error!"));
		return;
	}
	BYTE *pCrc;
	unsigned int crc = 0;
	
	ULONGLONG dwSize = fr.GetLength ();
	pCrc = new BYTE[dwSize];
	fr.Read (pCrc,dwSize);
	fr.Close();
	
	for (ULONGLONG nCrcLoop=1000; nCrcLoop<dwSize; nCrcLoop++)		
		crc =  CalSingleCharCrc_SiFang(crc, pCrc[nCrcLoop]);
	delete []pCrc;
	
	TRACE("cal CRC end:%s\n",GetTime());
	
	CString strCRC;
	strCRC.Format(_T("[CRC=%04x]"),crc);
	strCRC.MakeUpper();	
	m_strIcdFileCRC = strCRC;	
}

CString Cal_ModelFile_CRC_STR(CString strFileName)
{
	//���ı��ļ���ʽ��XML�ļ�����UTF-8���밴���봦��
	TRACE("cal CRC st:%s\n",GetTime());
	CFile fr;
	if(fr.Open (strFileName,CFile::modeRead) == FALSE)
	{
		AfxMessageBox(_T("file open error!"));
		return "";
	}
	BYTE *pCrc;
	unsigned int crc = 0;
	
	ULONGLONG dwSize = fr.GetLength ();
	pCrc = new BYTE[dwSize];
	fr.Read (pCrc,dwSize);
	fr.Close();
	
	for (ULONGLONG nCrcLoop=1000; nCrcLoop<dwSize; nCrcLoop++)		
		crc =  CalSingleCharCrc_SiFang(crc, pCrc[nCrcLoop]);
	delete []pCrc;
	
	TRACE("cal CRC end:%s\n",GetTime());
	
	CString strCRC;
	strCRC.Format(_T("[CRC=%04x]"),crc);
	strCRC.MakeUpper();	
	return strCRC;	
}

void CAutoModelStrc::NormalCfg(CM3_DI_GRP_ALL_INFO *pDI)
{
	int i,j,k,nIdx;
	CM3_DI_GRP_INFO *pGrp;
	CM3_DI_INFO	*pInfo;

	for (i=0;i<CM3_DEV_DI_CARD_MAX;++i)
	{
		if(pDI->bCPUUsed[i]==0)
			continue;

		for (j=0;j<pDI->bGrpNum[i];++j)
		{
			/* ��ǰCPU���ƫ�� */
			nIdx = pDI->wFstPos[i] + j;
			pGrp = &(pDI->grp[nIdx]);

			for (k=0;k<pGrp->bNum;++k)
			{
				pInfo = &(pGrp->info[k]);
				if(_tcslen(pInfo->desc)==0)
				{					
					int nTmp = pInfo->bCpuIdx*48 +1+pInfo->bIdx;
					nTmp+= ( (pInfo->bGrpIdx/2)*12 );
					if((pInfo->bGrpIdx%2)==1)	nTmp+=8;
					
					CString strDesc;
					strDesc.Format(_T(" %2d"),nTmp);
					strDesc=_T("(")+GetLocLngStr(0)+strDesc+_T(")");
					CM3_CP(pInfo->desc,strDesc);
				}

				if(CM3_DI_IDX_DPI(k))
				{
					/* �����A�� */
					if(pInfo->bIsPhase==1 && pInfo->bPhase==1)
					{
						/* ÿ�����ÿ���㣬����Ƿ��࣬������Ч�� */
						Set6DI(pDI,nIdx,k,CM3_PHS_CHK_CLR);					
					}

					/* �������� */
					pInfo->bPair=0;

					if(pInfo->bDPIGrp==1)
						pInfo->bDPI=1;

					if(pInfo->bDPI==1)
					{
						pGrp->info[k+1].bOpen = (pInfo->bOpen==1)? 0 : 1;
					}
				}
				else
				{
					/* ż�����룬����˫λ��λ */
					pInfo->bDPI=0;
				}

				/* ������ǵ�λ�û�˫λ�ã��򿪹ػ�բ������ȡ�� */
				if(!CM3_DI_GRP_SPEC(pGrp))
				{
					if(pInfo->bDPI==1)
					{
						/* �����˫λ�ã������ǵ�բ�򿪹� */
						pInfo->bBS=1;
					}
				}
				else
				{
					pInfo->bBS=0;
					pInfo->bBreak=0;
				}
			}
		}
	}
}

BOOL CAutoModelStrc::Set6DI(CM3_DI_GRP_ALL_INFO *pDI,int nCurGrp,int nCurInfo,BYTE bSet)
{
	/* CM3_PHS_CHK_VALID	׼�����÷��࣬���ӵ�ǰ�㿪ʼ��6�����Ƿ����
	 * CM3_PHS_CHK_EXIST	������з��࣬��ǰ���Ƿ����A��
     */
	if(bSet==CM3_PHS_CHK_VALID || bSet==CM3_PHS_CHK_EXIST)
	{
		int nIdx,nGrp;
		CM3_DI_GRP_INFO	*pGrp;
		CM3_DI_INFO		*pInfo;

		nGrp = nCurGrp;
		nIdx = nCurInfo;
		
		pGrp  = &(pDI->grp[nGrp]);
		pInfo = &(pGrp->info[nIdx]);
		
		/* ��Ͷ�룬���壬��λ�飬������Ϊ����
		 * ��λ�û�˫λ���飬��Ҫ�ж���ʼλ��������6����
		 */
		if(CM3_DI_GRP_SPEC(pGrp))
			return FALSE;

		/* ��ʼ����ż���㣬��1��ʼ�������� */
		if( !CM3_DI_IDX_DPI(nIdx))
			return FALSE;

		/* A�� */
		if(bSet==CM3_PHS_CHK_EXIST && !CM3_CHK_DI_PHASE(pInfo,1))
			return FALSE;

		/* �����׼�����࣬������Ч���������� */
		BYTE bAll = (bSet==CM3_PHS_CHK_VALID)? 0 : 1;

		/* ���B�� */
		pInfo = GetNextDPI(pDI,pInfo,bAll);
		if(pInfo==NULL)
			return FALSE;

		nGrp = pInfo->bGlbIdx;
		nIdx = pInfo->bIdx;
		
		pGrp  = &(pDI->grp[nGrp]);

		if(CM3_DI_GRP_SPEC(pGrp))
			return FALSE;

		/* B�� */
		if(bSet==CM3_PHS_CHK_EXIST && !CM3_CHK_DI_PHASE(pInfo,2))
			return FALSE;

		/* ���C�� */
		pInfo = GetNextDPI(pDI,pInfo,bAll);
		if(pInfo==NULL)
			return FALSE;
		
		nGrp = pInfo->bGlbIdx;
		nIdx = pInfo->bIdx;
		
		pGrp  = &(pDI->grp[nGrp]);
		
		if(CM3_DI_GRP_SPEC(pGrp))
			return FALSE;

		if(bSet==CM3_PHS_CHK_EXIST && !CM3_CHK_DI_PHASE(pInfo,3))
			return FALSE;
			
		return TRUE;
	}
	else if( 
		(bSet==CM3_PHS_CHK_CLR && Set6DI(pDI,nCurGrp,nCurInfo,CM3_PHS_CHK_EXIST)==FALSE) 
		|| bSet==CM3_PHS_CLR)
	{
		int nIdx,nGrp;
		CM3_DI_GRP_INFO	*pGrp;
		CM3_DI_INFO		*pInfo,*pS;
		
		nGrp = nCurGrp;
		nIdx = nCurInfo;
		
		pGrp  = &(pDI->grp[nGrp]);
		pInfo = &(pGrp->info[nIdx]);

		/* ���A�� */
		CM3_CLR_DI_PHASE(pInfo);
		pS = pInfo+1;
		CM3_CLR_DI_PHASE(pS);

		/* ���B�� */
		pInfo = GetNextDPI(pDI,pInfo);
		if(pInfo==NULL)
			return TRUE;
		
		CM3_CLR_DI_PHASE(pInfo);
		pS = pInfo+1;
		CM3_CLR_DI_PHASE(pS);

		/* ���C�� */
		pInfo = GetNextDPI(pDI,pInfo);
		if(pInfo==NULL)
			return TRUE;
		
		CM3_CLR_DI_PHASE(pInfo);
		pS = pInfo+1;
		CM3_CLR_DI_PHASE(pS);
		
		return TRUE;
	}
	else if(bSet==CM3_PHS_CHK_SET)
	{
		if(Set6DI(pDI,nCurGrp,nCurInfo,CM3_PHS_CHK_VALID)==TRUE)
		{
			int nIdx,nGrp;
			CM3_DI_GRP_INFO	*pGrp;
			CM3_DI_INFO		*pA,*pB,*pC;
			
			nGrp = nCurGrp;
			nIdx = nCurInfo;

			pGrp = &(pDI->grp[nGrp]);
			pA   = &(pGrp->info[nIdx]);

			pB = GetBCInfo(2,pDI,pA,0);
			pC = GetBCInfo(3,pDI,pA,0);

			CM3_SET_DI_PHASE(pA,1);
			CM3_SET_DI_PHASE(pB,2);
			CM3_SET_DI_PHASE(pC,3);

			return TRUE;
		}

		return FALSE;
	}

	return TRUE;
}

CM3_DI_INFO *CAutoModelStrc::GetBCInfo(int nBC, CM3_DI_GRP_ALL_INFO *pDI,CM3_DI_INFO *pA,BYTE bAll)
{
	CM3_DI_INFO	*pCur;

	pCur = GetNextDPI(pDI,pA,bAll);

	if(nBC==2 || pCur==NULL)
		return pCur;

	return GetNextDPI(pDI,pCur,bAll);
}

CM3_DI_INFO * CAutoModelStrc::GetNextDPI(CM3_DI_GRP_ALL_INFO *pDI,CM3_DI_INFO *pCur,BYTE bAll)
{
	int nGrp,nIdx;
	CM3_DI_GRP_INFO *pGrp;
	
	nGrp = pCur->bGlbIdx;
	pGrp = &(pDI->grp[nGrp]);

	nIdx = pCur->bIdx;

	/* ȡ��ǰDPI����¸��� */
	nIdx+=2;
	if(nIdx>=pGrp->bNum)
	{
		/* ����CM3_DI_GRP_ALL_INFO�ṹ��װ�õ������4CPU��32�鿼��
		 * ���Կ���ֱ��ȡ�¸���
		 */
		nGrp+=1;
		if(nGrp>=CM3_DEV_DI_GRP_ALL_MAX)
		{
			/* ���Ѿ�������װ�����е��� */
			return NULL;
		}

		/* ���Ѿ�������װ�����õ��� */
		if(bAll==0 && nGrp>=pDI->bGrps)
			return NULL;

		pGrp = &(pDI->grp[nGrp]);

		/* ���µ���ĵ�0���㿪ʼ */
		nIdx = 0;
	}
	
	return &(pGrp->info[nIdx]);
}

BOOL CAutoModelStrc::Set6DICtrl(CM3_DI_GRP_ALL_INFO *pDI,CM3_DI_INFO *pCur,
								BYTE bCtrlObj,BYTE bClose,BYTE bSV,BYTE bCtrl,BYTE bBS,BYTE bBSel)
{
	int nIdx,nGrp;
	CM3_DI_INFO		*pA,*pB,*pC;
	
	pA = pCur;

	nGrp = pA->bGlbIdx;
	nIdx = pA->bIdx;

	if(Set6DI(pDI,nGrp,nIdx,CM3_PHS_CHK_EXIST)==FALSE)
		return FALSE;
	
	pB = GetBCInfo(2,pDI,pA,0);
	pC = GetBCInfo(3,pDI,pA,0);
	
	pA->bCtrl = bCtrl;
	pA->bCtrlObj = (bCtrl==1)? bCtrlObj : 0;
	pA->bOpen = bClose;
	/* 2008-4-23 WZM
	 * DI��ȡ����Ϊȫ�֣����ﱣ��
	 */
	//pA->bSV = bSV;
	pA->bBS = bBS;
	pA->bBreak = bBSel;
	pA++;
	pA->bOpen = (bClose==1)? 0 : 1;

	if(pB!=NULL)
	{
		pB->bCtrl = bCtrl;
		pB->bCtrlObj = (bCtrl==1)? bCtrlObj : 0;
		pB->bOpen = bClose;
		/* 2008-4-23 WZM
		 * DI��ȡ����Ϊȫ�֣����ﱣ��
		 */
		//pB->bSV = bSV;
		pB->bBS = bBS;
		pB->bBreak = bBSel;

		pB++;
		pB->bOpen = (bClose==1)? 0 : 1;
	}

	if(pC!=NULL)
	{
		pC->bCtrl = bCtrl;
		pC->bCtrlObj = (bCtrl==1)? bCtrlObj : 0;
		pC->bOpen = bClose;
		/* 2008-4-23 WZM
		 * DI��ȡ����Ϊȫ�֣����ﱣ��
		 */
		//pC->bSV = bSV;
		pC->bBS = bBS;
		pC->bBreak = bBSel;

		pC++;
		pC->bOpen = (bClose==1)? 0 : 1;
	}

	return TRUE;
}

BOOL CAutoModelStrc::Is6DI(CM3_DI_GRP_ALL_INFO *pDI,CM3_DI_INFO *pCur)
{
	return Set6DI(pDI,pCur->bGlbIdx,pCur->bIdx,CM3_PHS_CHK_EXIST);
}

CString CAutoModelStrc::GetDIType(CM3_DI_GRP_ALL_INFO *pDI,CM3_DI_INFO *pCur,int *nHide)
{
	CString strRet=CM3_STR_EMPTY;
	CString strDI,strTmp;
	CM3_DI_INFO *pF,*pS;

	CM3_DI_GRP_INFO *pGrp;
	CM3_DI_INFO *pFirst;

	*nHide = 0;
	
	pGrp = &(pDI->grp[pCur->bGlbIdx]);
	if(CM3_DI_GRP_SPEC(pGrp))
		return strRet; 

	if(CM3_DI_IDX_DPI(pCur->bIdx))
	{
		pF = pCur;
		pS = pCur+1;
	}
	else
	{
		pS = pCur;
		pF = pCur-1;
	}

	strDI.Format(_T(", %d.%d.%d(%02d)"),
		CM3_GET_DI_CPU_ADDR(pCur->bCpuIdx),pCur->bGrpIdx+1,pCur->bIdx+1,pCur->wNo  );

	if(pF->bDPI!=1 && pF->bDPIGrp!=1)
	{
		strRet = _T("SPI") + strDI;
		if(pCur->bCtrl==1)
		{
			strTmp.Format(_T(", RC%02d"),pCur->bCtrlObj);
			strRet+=strTmp;
		}

		if(pCur->bBS==1)
		{
			strRet+=( (pCur->bBreak==1)?_T(", Breaker"):_T(", Switch") );
		}

		/* 2008-4-23 WZM
		 * DI��ȡ����Ϊȫ�֣����ﱣ��
		 */
		/*
		if(pCur->bSV==1)
		{
			strRet+=_T(", SV");
		}*/
	}
	else
	{
		if(pF->bIsPhase==1)
			strRet = _T("6PI");
		else
			strRet = _T("DPI");

		strRet+=strDI;

		if(pF->bCtrl==1)
		{
			strTmp.Format(_T(", RC%02d"),pF->bCtrlObj);
			strRet+=strTmp;
		}

		if (pF->bIsPhase==1)
		{
			strTmp = (pF->bPhase==2)? _T(", B") : (pF->bPhase==3)? _T(", C") : _T(", A");
			strRet+=strTmp; 
		}

		pFirst = pCur;
		if(!CM3_DI_IDX_DPI(pCur->bIdx))
			pFirst = pCur-1;

		if(pFirst->bBS==1)
		{
			strRet+=( (pFirst->bBreak==1)?_T(", Breaker"):_T(", Switch") );
		}
	
		strTmp = (pCur->bOpen==1)?  _T(", Open") :_T(", Close") ;
		strRet+=strTmp; 

		/* 2008-4-23 WZM
		 * DI��ȡ����Ϊȫ�֣����ﱣ��
		 */
		/*
		if(pCur->bSV==1)
		{
			strRet+=_T(", SV");
		}*/

		if(!CM3_DI_IDX_DPI(pCur->bIdx) || (pF->bIsPhase==1 && pF->bPhase!=1))
			*nHide = 1;
	}
	
	return strRet;
}
CString CAutoModelStrc::GetGoDIType(CM3_DI_GRP_ALL_INFO *pDI,CM3_DI_INFO *pCur,int *nHide,int goCpuNo)
{
	CString strRet=CM3_STR_EMPTY;
	CString strDI,strTmp;
	CM3_DI_INFO *pF,*pS;

	CM3_DI_GRP_INFO *pGrp;
	CM3_DI_INFO *pFirst;

	*nHide = 0;
	
	pGrp = &(pDI->grp[pCur->bGlbIdx]);
	if(CM3_DI_GRP_SPEC(pGrp))
		return strRet; 

	if(CM3_DI_IDX_DPI(pCur->bIdx))
	{
		pF = pCur;
		pS = pCur+1;
	}
	else
	{
		pS = pCur;
		pF = pCur-1;
	}

	strDI.Format(_T(", G%d-%d, %d.%d(%02d)"),goCpuNo,(pCur->bCpuIdx%2+1),pCur->bGrpIdx+1,pCur->bIdx+1,pCur->wNo  );

	if(pF->bDPI!=1 && pF->bDPIGrp!=1)
	{
		strRet = _T("SPI") + strDI;
		if(pCur->bCtrl==1)
		{
			strTmp.Format(_T(", RC%02d"),pCur->bCtrlObj);
			strRet+=strTmp;
		}

		if(pCur->bBS==1)
		{
			strRet+=( (pCur->bBreak==1)?_T(", Breaker"):_T(", Switch") );
		}

		/* 2008-4-23 WZM
		 * DI��ȡ����Ϊȫ�֣����ﱣ��
		 */
		/*
		if(pCur->bSV==1)
		{
			strRet+=_T(", SV");
		}*/
	}
	else
	{
		if(pF->bIsPhase==1)
			strRet = _T("6PI");
		else
			strRet = _T("DPI");

		strRet+=strDI;

		if(pF->bCtrl==1)
		{
			strTmp.Format(_T(", RC%02d"),pF->bCtrlObj);
			strRet+=strTmp;
		}

		if (pF->bIsPhase==1)
		{
			strTmp = (pF->bPhase==2)? _T(", B") : (pF->bPhase==3)? _T(", C") : _T(", A");
			strRet+=strTmp; 
		}

		pFirst = pCur;
		if(!CM3_DI_IDX_DPI(pCur->bIdx))
			pFirst = pCur-1;

		if(pFirst->bBS==1)
		{
			strRet+=( (pFirst->bBreak==1)?_T(", Breaker"):_T(", Switch") );
		}
	
		strTmp = (pCur->bOpen==1)?  _T(", Open") :_T(", Close") ;
		strRet+=strTmp; 

		/* 2008-4-23 WZM
		 * DI��ȡ����Ϊȫ�֣����ﱣ��
		 */
		/*
		if(pCur->bSV==1)
		{
			strRet+=_T(", SV");
		}*/

		if(!CM3_DI_IDX_DPI(pCur->bIdx) || (pF->bIsPhase==1 && pF->bPhase!=1))
			*nHide = 1;
	}
	
	return strRet;
}


/** ֻ���ڵ���ģ��ʱ���ã�����װ��ģ��ģ��֮����� */
BOOL CAutoModelStrc::ParseMeasDataType()
{
	memset(&m_dtMeas,0,sizeof(CM3_DEV_MEAS_CFG_TYPE));
	memset(&m_mmxuTyp,0,sizeof(m_mmxuTyp));
	memset(&m_mmxnTyp,0,sizeof(m_mmxnTyp));
	
	/* �����ʲ����Ϊ�±�
	 * �ȶ����н��������з���
	 */

	int i,j,k,nIdx,nMNo,nMNoMax,nPhase;
	CM3_AI_ALL_INFO *pAll=&(m_aAI);
	CM3_AI_INFO	*pInfo;
	CM3_DEV_MEAS_MMXU	*pMMXU;
	CM3_DEV_MEAS_MMXN	*pMMXN=NULL;
	int nDOIdx;

	nMNoMax = 0;
	BOOL m_bIndon = (m_bMidRelayST & 0x80)>>7;
	for (i=0;i<CM3_DEV_AI_CARD_MAX;++i)
	{
		if(pAll->bCPUUsed[i]==0)
			continue;

		for (j=0;j<pAll->bCPUNum[i];++j)
		{
			nIdx = pAll->wFstPos[i] + j;
			pInfo = &(pAll->info[nIdx]);

			/* ����ǲ�Ͷ�룬����ʸ����򲻿��� */
			//ӡ���
			if(pInfo->bType == 0 || pInfo->bType == 6 || pInfo->bType >7)
			{
				if(pInfo->bType == 6)
				{
					if(1!=m_bIndon)
					{
						continue;
					}
				}
				else
				continue;
			}
			int typeN=pInfo->bType;
			int typeCpuIdx = pInfo->bCpuIdx;
			if(pInfo->bType == 1 || pInfo->bType == 2)
			{
				if(pInfo->bPhase > 6)
					continue;
			}

			nMNo = pInfo->bNo;
			if(nMNo>=CM3_DEV_MEAS_NO_MAX)
				return FALSE;

			/* �������Ĺ��ʲ�� */
			if(nMNoMax<nMNo)
 				nMNoMax = nMNo;

			pMMXU = &(m_dtMeas.mmxu[nMNo]);

			pMMXU->bNo = nMNo+1;
			/* �Ƚ��������ý�����MMXU��
			 * Ȼ���MMXU����MMXN
			 * ��Ͷ�� U  I  F  P  Q  ʸ����  COS
			 */

			/* ����ǵ�ѹ��������Ҫ�ж���� 
			 * A B C AB BC CA 0
			 */
			if(pInfo->bType == 1 || pInfo->bType == 2)
			{
				nPhase = pInfo->bPhase;
				/* A B C ����: 0 1 2 6*/
				if(nPhase<3 || nPhase==6)
				{
					if(nPhase==6)
						nPhase = CM3_M_SUB_0;

					if(pInfo->bType == 1)
						pMMXU->pU[nPhase] = pInfo;
					else
						pMMXU->pI[nPhase] = pInfo;
				}
				/* AB BC CA: 3 4 5 */
				else if(nPhase<6 && nPhase>2 )
				{
					nPhase -= 3;
					pMMXU->pUL[nPhase] = pInfo;
				}
			}
			/* �й����޹���������жϣ��ж��Ƿ���� Grace Du 20100330
			* A B C ��
			*/
			else if (pInfo->bType == 4 || pInfo->bType == 5)
			{
				nPhase = pInfo->bPhase;
				/*Total A B C: -1 0 1 2*/
				if(nPhase<3 && nPhase>-1)
				{
					if(pInfo->bType == 4)
						pMMXU->pPhsP[nPhase] = pInfo;
					else
						pMMXU->pPhsQ[nPhase] = pInfo;
				}
				else
				{
					if(pInfo->bType==4)	nDOIdx=CM3_M_SUB_P;
					else	nDOIdx=CM3_M_SUB_Q;
					pMMXU->pType[nDOIdx] = pInfo;
				}
				
			}

			else
			{
				/* ��ѹ����֮��ģ�ֱ����������Ϊ�±� 
				 * ��Ͷ�� U  I  F  P  Q  ʸ����  COS
				 * ˵����˳��Ҫ��Ϊģ����DO��˳��
				 * ��Ͷ�� I U P Q COS Hz ʸ����
				 */
				nDOIdx=0;
				if(pInfo->bType==1)	nDOIdx=CM3_M_SUB_U;
				else if(pInfo->bType==2)	nDOIdx=CM3_M_SUB_I;
				else if(pInfo->bType==3)	nDOIdx=CM3_M_SUB_F;
				else if(pInfo->bType==4)	nDOIdx=CM3_M_SUB_P;
				else if(pInfo->bType==5)	nDOIdx=CM3_M_SUB_Q;
				else if(pInfo->bType==6)
				{
					nDOIdx=7;
				}
				else if(pInfo->bType==7)	nDOIdx=CM3_M_SUB_PF;

				pMMXU->pType[nDOIdx] = pInfo;
			}
		}
	}

	/* ������������MMXU������ 
	 * nMNoMaxΪ����MMXU�±�
	 */

	nMNoMax+=1;
	WORD	wType;
	int nTmp;
	VOID **pPhs;

	for (i=0;i<nMNoMax;++i)
	{
		pMMXU = &(m_dtMeas.mmxu[i]);

		/* ��ǰ���û�� */
		if(pMMXU->bNo==0)
			continue;

		wType=0;

		/* ����CM3_M_SUB_U������ص㣬����ʹ���±�������͵Ľ��� 
		 * ���pMMXU->pType�е�ĳ��Ϊ�գ����ʾû�иý���
		 * ��Pû�У���CM3_M_SUB_P�±��Ӧ��pMMXU->pType[CM3_M_SUB_P]=NULL
		 * ������Ľ����У�pMMXU->pType[CM3_M_TYP_U]��pMMXU->pType[CM3_M_TYP_I]�ǿյģ���Ϊ
		 * �κ�һ����ѹ����������ҵ���Ӧ����𣬼�����pMMXU->pU��pMMXU->pI��
		 */

		/* CM3_M_SUB_F CM3_M_SUB_P CM3_M_SUB_Q CM3_M_SUB_PF */
		BOOL m_bIndon = (m_bMidRelayST & 0x80)>>7;
		//ӡ�Ȱ�
		int iADoSum = 0;//��Ҫ���ӵ�DO��Ŀ
		if(1==m_bIndon)
		{
			iADoSum = CM3_M_TYP_S;
		}
		else
		{
			iADoSum = CM3_M_TYP_F;
		}
		for (j=CM3_M_TYP_P;j<=iADoSum;++j)
		{
			if(pMMXU->pType[j]!=NULL)
				CM3_WORD_SET(wType,j);
		}

		/* �����ѹ */
		if(pMMXU->pU[CM3_M_SUB_0]!=NULL)
			CM3_WORD_SET(wType,CM3_M_TYP_U0);

		/* ������� */
		if(pMMXU->pI[CM3_M_SUB_0]!=NULL)
			CM3_WORD_SET(wType,CM3_M_TYP_I0);

		/* ����������ѹ�͵�������
		 * ������������࣬���ʾȫ�ࣻ����Ϊ��ȡ��ѹ
		 * ��ͬһ���ʲ�㣬����е��࣬Ҳ����������Ϊȫ�࣬��I1a��I10
		 */
		for (j=CM3_M_TYP_PPV;j<=CM3_M_TYP_PHI;++j)
		{
			nPhase = 0;
			pPhs = (j==CM3_M_TYP_PHV)? pMMXU->pU : (j==CM3_M_TYP_PPV)? pMMXU->pUL : pMMXU->pI ;
			for (k=0;k<4;++k)
			{	
				/* �ߵ�ѹû��0�� */
				if(j==CM3_M_TYP_PPV && k>2)
					continue;

				if(pPhs[k]!=NULL)
					nPhase++;
			}

			/* �������� */
			if(nPhase>=1)
			{
				/* ������࣬����Ӧ�Ľ������ͣ����࣬�ֵ�ѹ�͵��� */
				nTmp = (nPhase>1) ? j : (j==CM3_M_TYP_PHI)? CM3_M_TYP_I : CM3_M_TYP_U;
				CM3_WORD_SET(wType,nTmp);
			}
		}

		//���������й�
		nPhase = 0;
		for (k=0;k<3;k++)
		{	
			if(pMMXU->pPhsP[k]!=NULL)
				nPhase++;
		}
		if (nPhase>=1) CM3_WORD_SET(wType,CM3_M_TYP_PhaP);
		
		//���������޹�
		nPhase = 0;
		for (k=0;k<3;k++)
		{	
			if(pMMXU->pPhsQ[k]!=NULL)
				nPhase++;
		}
		if (nPhase>=1) CM3_WORD_SET(wType,CM3_M_TYP_PhaQ);

		pMMXU->wIncl = wType;

		TRACE(_T("\n mmxu %d %X "),pMMXU->bNo,pMMXU->wIncl);
	}

	/* ������������MMXU�����ͣ�ȷ��MMXU��MMXN������
	 * ȫ�࣬������������Ϊ���������ȫ��
	 * ��������ȫ�࣬����Ϊ���޶�Ӧ��ģ���MMXN
	 * ���࣬����Ϊ���޶�Ӧ��ģ���MMXN
	 * �޵�ѹ���ߵ�������������������Ϊ���޶�Ӧ��ģ���MMXN
	 *
	 * ���ȫ��ֻ���ߵ�ѹ�������
	 */
	for (i=0;i<nMNoMax;++i)
	{
		pMMXU = &(m_dtMeas.mmxu[i]);
		
		/* ��ǰ���û�� */
		if(pMMXU->bNo==0)
			continue;

		nMNo = pMMXU->bNo-1;

		wType = pMMXU->wIncl;

		/* ͬһ����ڣ���ѹֻ���ߵ�ѹ������� */
		if(CM3_WORD_GET(wType,CM3_M_TYP_PPV) 
			&& !CM3_WORD_GET(wType,CM3_M_TYP_PHV) )
		{
			memset(pMMXU,0,sizeof(CM3_DEV_MEAS_MMXU));
			continue;
		}
		
		/* ͬһ����ڣ���ȫ���ѹ��Ҳ��ȫ���������MMXN */
		if(!CM3_WORD_GET(wType,CM3_M_TYP_PHV) 
			&& !CM3_WORD_GET(wType,CM3_M_TYP_PHI) )
		{
			pMMXN = &(m_dtMeas.mmxn[nMNo]);
			pMMXN->bNo = pMMXU->bNo;
			
			/* ����������ѹ�����õ����ѹ������λ�����ѹ */
			if(CM3_WORD_GET(wType,CM3_M_TYP_U0))
			{
				CM3_WORD_RST(wType,CM3_M_TYP_U0);
				CM3_WORD_SET(wType,CM3_M_TYP_U);
			}

			/* �����������������õ������������λ������� */
			if(CM3_WORD_GET(wType,CM3_M_TYP_I0))
			{
				CM3_WORD_RST(wType,CM3_M_TYP_I0);
				CM3_WORD_SET(wType,CM3_M_TYP_I);
			}

			pMMXN->wIncl = wType;

			/* ����MMXN�����н��� */
			memcpy(pMMXN->pType,pMMXU->pType,sizeof(VOID *)*CM3_AI_TYPE_MAX );

			/* �����࣬�������򣬻�ȡ�����ѹ����������������MMXN�ĵ�ѹ�������� */
			for (j=0;j<4;++j)
			{
				if(pMMXU->pU[j]!=NULL)
					pMMXN->pType[CM3_M_SUB_U] = pMMXU->pU[j];
				if(pMMXU->pI[j]!=NULL)
					pMMXN->pType[CM3_M_SUB_I] = pMMXU->pI[j];
			}

			/* ��ǰѭ���Բ�����Ϊ���ޣ�����ÿ�θ������Ĳ����� */
			m_dtMeas.wMMXNMax = pMMXN->bNo;	

			/* ��ȫ���������ѹ��MMXU����MMXN����Ҫ���ԭMMXU */
			memset(pMMXU,0,sizeof(CM3_DEV_MEAS_MMXU));

			TRACE(_T("\n MMXN %d %X "),pMMXN->bNo,pMMXN->wIncl);

			continue;
		}

		/* ���ˣ�Ӧ����ȫ���ѹ����� */

		/* ��ȫ��������е�������������������ֻ���õ�����ΪMMXN */
		if(!CM3_WORD_GET(wType,CM3_M_TYP_PHI)
			&&(CM3_WORD_GET(wType,CM3_M_TYP_I) || CM3_WORD_GET(wType,CM3_M_TYP_I0) ) )
		{
			pMMXN = &(m_dtMeas.mmxn[nMNo]);
			pMMXN->bNo = pMMXU->bNo;
			m_dtMeas.wMMXNMax = pMMXN->bNo;	

			for (j=0;j<4;++j)
			{
				if(pMMXU->pI[j]!=NULL)
				{
					pMMXN->pType[CM3_M_SUB_I] = pMMXU->pI[j];
					/* ��λMMXU�еĵ��� */
					pMMXU->pI[j] = NULL;
				}
			}

			WORD wTmp=0;

			/* ������ߵ��������������һ����������λMMXN�ĵ��� */
			CM3_WORD_SET(wTmp,CM3_M_TYP_I);

			pMMXN->wIncl = wTmp;

			/* ��MMXU�еĵ�����ȥ�� */
			CM3_WORD_RST(wType,CM3_M_TYP_I0);
			CM3_WORD_RST(wType,CM3_M_TYP_I);
			pMMXU->wIncl = wType;

			TRACE(_T("\n MMXU %d %X "),pMMXU->bNo,pMMXU->wIncl);
			TRACE(_T("\n MMXN %d %X "),pMMXN->bNo,pMMXN->wIncl);
			continue;
		}
		
		/* ��ȫ���ѹ���е����ѹ���������ѹ��ֻ���õ�ѹ��Ƶ����ΪMMXN */
		if(!CM3_WORD_GET(wType,CM3_M_TYP_PHV) 
			&&(CM3_WORD_GET(wType,CM3_M_TYP_U) || CM3_WORD_GET(wType,CM3_M_TYP_U0)))
		{
			/*��2012.6.14��ӣ����3�������1�������ѹ��һ������µ����⣬
			3�������Ȼ��ΪMMXU,1�������ѹ�򵥶���ΪMMXN*/
			if (CM3_WORD_GET(wType,CM3_M_TYP_PHI))
			{
				/* ��MMXU�е����ѹ�����ȥ�� */
				CM3_WORD_RST(wType,CM3_M_TYP_U);
				CM3_WORD_RST(wType,CM3_M_TYP_I);
				
				m_dtMeas.wMMXUMax = pMMXU->bNo;	
			}

			pMMXN = &(m_dtMeas.mmxn[nMNo]);
			pMMXN->bNo = pMMXU->bNo;
			m_dtMeas.wMMXNMax = pMMXN->bNo;	
			
			for (j=0;j<4;++j)
			{
				if(pMMXU->pU[j]!=NULL)
				{
					pMMXN->pType[CM3_M_SUB_U] = pMMXU->pU[j];
					pMMXU->pU[j] = NULL;
				}
			}

			for (j=0;j<3;++j)
			{
				if(pMMXU->pUL[j]!=NULL)
				{
					pMMXN->pType[CM3_M_SUB_U] = pMMXU->pUL[j];
					pMMXU->pUL[j] = NULL;
				}
			}

			pMMXN->pType[CM3_M_SUB_F] = pMMXU->pType[CM3_M_SUB_F];
			pMMXU->pType[CM3_M_SUB_F] = NULL;
			
			WORD wTmp=0;
			
			CM3_WORD_SET(wTmp,CM3_M_TYP_U);

			/* ���ܲ�û�ж�Ӧ��Ƶ�ʣ�����Ҫ�ж� */
			if(CM3_WORD_GET(wType,CM3_M_TYP_F))
				CM3_WORD_SET(wTmp,CM3_M_TYP_F);
		
			pMMXN->wIncl = wTmp;

			/* ��MMXU�еĵ�ѹ��Ƶ��ȥ�� */
			CM3_WORD_RST(wType,CM3_M_TYP_U);
			CM3_WORD_RST(wType,CM3_M_TYP_U0);
			CM3_WORD_RST(wType,CM3_M_TYP_F);
			
			pMMXU->wIncl = wType;

			TRACE(_T("\n MMXU %d %X "),pMMXU->bNo,pMMXU->wIncl);
			TRACE(_T("\n MMXN %d %X "),pMMXN->bNo,pMMXN->wIncl);

			continue;
		}
		
		/* ��MMXU�е����ѹ�����ȥ�� */
		CM3_WORD_RST(wType,CM3_M_TYP_U);
		CM3_WORD_RST(wType,CM3_M_TYP_I);

		m_dtMeas.wMMXUMax = pMMXU->bNo;	
		TRACE(_T("\n MMXU %d %X "),pMMXU->bNo,pMMXU->wIncl);
	}

	/* ȷ��MMXU��MMXN������
	 * MMXU����ѹ������������
	 * ���ﲻ����ȡ������Ϊȡ��������ģ���������ԣ����ڴ���LN����ʱʹ��
	 */

	nTmp = 0;

	BOOL bFind;
	for (i=0;i<m_dtMeas.wMMXUMax;++i)
	{
		pMMXU = &(m_dtMeas.mmxu[i]);
		
		/* ��ǰ���û�� */
		if(pMMXU->bNo==0)
			continue;

		wType = pMMXU->wIncl;
		bFind = FALSE;

		/* �ڵ�ǰ���֮ǰ����ͬ��wIncl */
		for(j=0;j<i;++j)
		{
			if(m_dtMeas.mmxu[j].bNo==0)
				continue;

			if(m_dtMeas.mmxu[j].wIncl == wType)
			{
				/* ����ҵ���ͬ���͵ģ���ֱ���� */
				pMMXU->lnType = m_dtMeas.mmxu[j].lnType;
				/* ��ǰ���ͱ�ʹ�õĴ�����ԭ��ȷ��ÿ��LN��ʵ���� */
				m_dtMeas.mmxu[j].wSameTimes++;
				/* ��ǰ���͵ĵ�һ��ʵ������1����֮���ظ���LN��ʹ����ʵ���ż��ظ��Ĵ���ȷ�� */
				pMMXU->lnInst = m_dtMeas.mmxu[j].lnInst+m_dtMeas.mmxu[j].wSameTimes;
				bFind = TRUE;
				break;
			}
		}
		
		if(bFind==FALSE)
		{
			/* û���ҵ����򴴽��µ����ͣ�Ҳ��ʹ�õ�������ű�ʾ */
			pMMXU->lnType = nTmp+1;
			/* ÿ�������͵ĵ�һ��ʵ����Ϊ1 */
			pMMXU->lnInst = 1;
			/* ��ǰ����ʵ�ʰ�����ģ������ͨ��wTypeȷ�� */
			m_mmxuTyp.type[nTmp] = wType;
			nTmp++;
		}

		TRACE(_T("\n MMXU %d %X lnT %d lnI %d"),
			pMMXU->bNo,pMMXU->wIncl,pMMXU->lnType,pMMXU->lnInst);
	}
	/* MMXU��ȫ������ */
	m_mmxuTyp.bNum = nTmp;

	nTmp = 0;
	for (i=0;i<m_dtMeas.wMMXNMax;++i)
	{
		pMMXN = &(m_dtMeas.mmxn[i]);
		
		/* ��ǰ���û�� */
		if(pMMXN->bNo==0)
			continue;
		
		wType = pMMXN->wIncl;
		bFind = FALSE;
		
		/* �ڵ�ǰ���֮ǰ����ͬ��wIncl */
		for(j=0;j<i;++j)
		{
			if(m_dtMeas.mmxn[j].bNo==0)
				continue;
			
			if(m_dtMeas.mmxn[j].wIncl == wType)
			{
				pMMXN->lnType = m_dtMeas.mmxn[j].lnType;
				m_dtMeas.mmxn[j].wSameTimes++;
				pMMXN->lnInst = m_dtMeas.mmxn[j].lnInst+m_dtMeas.mmxn[j].wSameTimes;
				bFind = TRUE;
				break;
			}
		}
		
		if(bFind==FALSE)
		{
			pMMXN->lnType = nTmp+1;
			pMMXN->lnInst = 1;
			m_mmxnTyp.type[nTmp] = wType;
			nTmp++;
		}

		TRACE(_T("\n MMXN %d %X lnT %d lnI %d"),
			pMMXN->bNo,pMMXN->wIncl,pMMXN->lnType,pMMXN->lnInst);
	}

	m_mmxnTyp.bNum = nTmp;

	/* ���ˣ�����������������֪ 
	 * ��ɾ��ԭ����ln���ͣ�MMXU��MMXN
	 * �ٴ����µ�����
	 */


	return TRUE;
}

/** ֻ�ܵ���һ�� */
void CAutoModelStrc::MapMeas()
{
	/* �������ã���ȡ������������ģ�Ͷ�Ӧ��ϵ */
	if(ParseMeasDataType()==FALSE)
		return ;

	/* ɾ������LN���� */
	m_docIcd.DelLnType4AI();

	int i;
	BOOL bIndon = (m_bMidRelayST & 0x80)>>7;
	m_docIcd.setIndon(bIndon);
	/* ����MMXU���� */
	if(m_mmxuTyp.bNum>0)
	{
		for (i=m_mmxuTyp.bNum-1;i>=0;--i)
		{
			m_docIcd.AddLnTypeMeas(i+1,m_mmxuTyp.type[i],0);
		}
	}

	/* ����MMXN���� */
	if(m_mmxnTyp.bNum>0)
	{
		for (i=m_mmxnTyp.bNum-1;i>=0;--i)
		{
			m_docIcd.AddLnTypeMeas(i+1,m_mmxnTyp.type[i],1);
		}
	}

	/* �Ѿ�������˽���LN���͵Ĵ���
	 * ���ţ����ģ�������ݼ���Ȼ��������ý�����������
	 */

	/* ��ʼ��ģ����LD��������ݼ� */
	m_docIcd.InitLDMeas();
	/* ��������������FCDA�����ݼ� */

	/* LLN0 LPHD������LN��3��ʼ��ţ�ģ����ͳһ˳���� */
	m_docIcd.m_nLNMeas=3;
	m_docIcd.MapAI(&m_dtMeas);
	/* ����������ֱ���¶�FCDA�����ݼ� */
	m_docIcd.MapDT(&m_aDT);

	if(m_pDev->m_aGO.GetSize()==1)
	{
		if (m_pDev->m_aGoCPUEn.GetSize()==1)
		{
			int numCpu=m_pDev->m_aGoCPUEn[0].goDTCpuNum;
			m_docIcd.MapGODT(&m_aGO1DT,numCpu);
		}
	}
	/*V4.10:���ݽ������������������ȵĽ�ģ*/
	BOOL bMeter = (m_bMidRelayST & 0x08)>>3;
	if (bMeter)
	{
		m_docIcd.MapMT(&m_aAI);
	}

	// �������жϣ�ģ�������ݼ��Ƿ������ݣ����û�У���ɾ�����ݼ�������
	m_docIcd.InitLDMeas(1);
}

CString CAutoModelStrc::GetAIDesc(WORD wType)
{
	CString strRet=S_EPT;
	CString strTmp;

	int i;

	for (i=CM3_M_SUB_I;i<=CM3_M_TYP_PhaQ;++i)
	{
		if(!CM3_WORD_GET(wType,i))
			continue;

		strTmp = m_docIcd.m_CM3.aiStr[i];

		if(strRet.IsEmpty())
			strRet += strTmp;
		else
			strRet += S_SPACE + strTmp;
		
	//	strRet += strTmp + S_SPACE;
	}
		
	return strRet;
}

CString CAutoModelStrc::GetSAddrAI(CM3_AI_INFO *pInfo,int nSubNo)
{
	CString strRet = S_EPT;

	if(pInfo==NULL)
		return strRet;

	/*strRet.Format(_T("ANA_%d_%d_0"),pInfo->bCpuIdx+1,pInfo->bIdx+1);*/
	strRet.Format(_T("15.%d.%d.%d"),pInfo->bCpuIdx+1,pInfo->bIdx+1,nSubNo);

	return strRet;
}

CString CAutoModelStrc::GetSAddrSVAI(CM3_AI_INFO *pInfo,int nSubNo,int nSVNo)
{
	CString strRet = S_EPT;
	
	if(pInfo==NULL)
		return strRet;
	
	strRet.Format(_T("16.%d.%d.%d.%d"),pInfo->bCpuIdx+1,pInfo->bIdx+1,nSubNo,nSVNo);
	
	return strRet;
}

CString CAutoModelStrc::GetDTDesc(CM3_DT_INFO *pInfo)
{
	CString strRet = S_EPT;

	if(pInfo==NULL)
		return strRet;
	
	strRet = pInfo->en;
	if(pInfo->bType ==0)
	{
		strRet = GetLocLngStr(2);
	}

	return strRet;
}

CString CAutoModelStrc::GetSAddrDT(CM3_DT_INFO *pInfo,int nSubNo)
{
	CString strRet = S_EPT;
	
	if(pInfo==NULL)
		return strRet;
	
	/*strRet.Format(_T("DT_%d_%d_0"),pInfo->bCpuIdx+1,pInfo->bIdx+1);*/
	strRet.Format(_T("65.%d.%d.%d"),pInfo->bCpuIdx+1,pInfo->bIdx+1,nSubNo);
	
	return strRet;
}
CString CAutoModelStrc::GetSAddrDT(int nCPU,int nChn,int nSubNo)
{
	CString strRet = S_EPT;

	if(nCPU<0 || nChn<0 || nSubNo<0)
		return strRet;

	strRet.Format(_T("65.%d.%d.%d"),nCPU,nChn,nSubNo);

	return strRet;
}

CString CAutoModelStrc::GetSAddrSVDT(CM3_DT_INFO *pInfo,int nSubNo,int nSVNo)
{
	CString strRet = S_EPT;
	
	if(pInfo==NULL)
		return strRet;
	
	strRet.Format(_T("66.%d.%d.%d.%d"),pInfo->bCpuIdx+1,pInfo->bIdx+1,nSubNo,nSVNo);
	
	return strRet;
}


CString CAutoModelStrc::GetSAddrSVDT(int nCPU,int nChn,int nSubNo,int nSVNo)
{
	CString strRet = S_EPT;
	
	if(nCPU<0 || nChn<0 || nSubNo<0 ||nSVNo<0)
		return strRet;
	
	strRet.Format(_T("66.%d.%d.%d.%d"),nCPU,nChn,nSubNo,nSVNo);
	
	return strRet;
}

void CAutoModelStrc::MapDI()
{
	/* �ڽ�����������֮ǰ���������ӦLD�����ݼ�
	 * �Լ�LNʵ����LLNO�µ�DOI��
	 */
	m_docIcd.InitLDCtrl();

	m_docIcd.m_nLNCtrl=3;
	m_docIcd.MapDOSoe(&m_aDO);
	if (m_aMidRel.wRows>0)
	{
		m_docIcd.MapMidRelay(&m_aMidRel);		//V4.00����
	}
	else
	{
		m_docIcd.MapMidRelay();		//V4.00����
	}
	m_docIcd.MapRSYN();
	m_docIcd.MapPrgOp();
	m_docIcd.MapDI(&m_aDI);
	
	if (m_pDev->m_aGO.GetSize()==1)
	{
		if (m_pDev->m_aGoCPUEn.GetSize()==1)
		{
			int num=m_pDev->m_aGoCPUEn[0].goDICpuNum;
			switch(num)
			{
			case 1:
				m_docIcd.MapDI(&m_aGO1DI1);
				break;
			case 2:
				m_docIcd.MapDI(&m_aGO1DI1);
				m_docIcd.MapDI(&m_aGO1DI2);
				break;
			case 3:
				m_docIcd.MapDI(&m_aGO1DI1);
				m_docIcd.MapDI(&m_aGO1DI2);
				m_docIcd.MapDI(&m_aGO1DI3);
				break;
			}
			
			num=m_pDev->m_aGoCPUEn[0].goTapNum;
			if (num==1 || num==3)
			{
				m_docIcd.MapGoTap(&m_aGO1Tap);
			}
		}
	}

	m_docIcd.MapRCWithoutPos(&m_aRC);

	//���Ӽ�������GOOSE����
	BOOL bayGoose = (m_bMidRelayST & 0x20)>>5;
	BOOL bNanAo = (m_bMidRelayST & 0x40)>>6;
	BOOL bMidRelay = m_bMidRelayST && 0x01;
	//�����Goose�����������пؿ�����ȫ�����ص�բ��λ���ź���ӵ����ݼ���
	//v4.21������ϰ���Ŀ���������м�̵����������Ӽ̵�������
	m_docIcd.MapGoOutWF(bayGoose,bNanAo && bMidRelay);
	if(bayGoose)
	{
		if(bNanAo)
			m_docIcd.MapGoInNanAo();//v4.21�ϰ���Ŀ
		else
			m_docIcd.MapGoInWF();//�����Goose����		
	}

	m_docIcd.InitLDCtrl(1);
}

CString CAutoModelStrc::GetSAddrTap(CM3_DI_INFO	*pInfo,int nPhs,int nSubNo)
{
	CString strRet = S_EPT;

	if(pInfo==NULL)
		return strRet;
	
	if(nPhs==5)
	{
		/* ��ȡң�� */
		/*strRet.Format(_T("SBO_%d_5_1_1"),1);*/
		strRet.Format(_T("25.%d.5.1.1"),1);
	}
	else
	{
		/*strRet.Format(_T("TAP_%d_%d_1"),1,nPhs);*/
		strRet.Format(_T("30.%d.%d.%d"),1,nPhs,nSubNo);
	}

	return strRet;
}

CString CAutoModelStrc::GetSAddrGoTap(CM4_GO_TAP_INFO	*pInfo,int nPhs,int nSubNo)
{
	CString strRet = S_EPT;
	
	if(pInfo==NULL)
		return strRet;
	
	if(nPhs==5)
	{
		/* ��ȡң�� */
		/*strRet.Format(_T("SBO_%d_5_1_1"),1);*/
		strRet.Format(_T("25.%d.5.1.1"),1);
	}
	else
	{
		/*strRet.Format(_T("TAP_%d_%d_1"),1,nPhs);*/
		strRet.Format(_T("30.%d.%d.%d"),1,nPhs+4,nSubNo);
	}
	
	return strRet;
}

CString CAutoModelStrc::GetSAddrSVTap(int nPhs,int nSubNo,int nSVNo)
{
	CString strRet = S_EPT;
	
	strRet.Format(_T("31.%d.%d.%d.%d"),1,nPhs,nSubNo,nSVNo);
	
	return strRet;
}
CString CAutoModelStrc::GetSAddrSVGoTap(int nPhs,int nSubNo,int nSVNo)
{
	CString strRet = S_EPT;
	
	strRet.Format(_T("31.%d.%d.%d.%d"),1,nPhs+4,nSubNo,nSVNo);
	
	return strRet;
}

CString CAutoModelStrc::GetSAddrDI(CM3_DI_INFO	*pInfo,int nFlag)
{
	CString strRet = S_EPT;
	
	if(pInfo==NULL)
		return strRet;

	int nCLose=nFlag;

	if(nFlag==CM3_SADDR_DI_DPI_C)
		nCLose=(pInfo->bOpen==0)? CM3_SADDR_DI_DPI_C : CM3_SADDR_DI_DPI_O;

	//V4.0����maser��Go����̵�ַbcpuIdx����
	int bcpuIdxTmp= pInfo->bCpuIdx;
	if (bcpuIdxTmp==2||bcpuIdxTmp==3) bcpuIdxTmp=bcpuIdxTmp-2;
	if (bcpuIdxTmp==4||bcpuIdxTmp==5) bcpuIdxTmp=bcpuIdxTmp-4;
	if (bcpuIdxTmp==6||bcpuIdxTmp==7) bcpuIdxTmp=bcpuIdxTmp-6;

	int nNo = pInfo->wNo - bcpuIdxTmp*48;

	//int nNo = pInfo->wNo - pInfo->bCpuIdx*48;
	
	/*strRet.Format(_T("DI_%d_%d_%d"),pInfo->bCpuIdx+1,nNo,nCLose);*/
	if ((pInfo->BBak&1)==1)
	strRet.Format(_T("10.%d.%d.%d.0.0.1"),pInfo->bCpuIdx+1,nNo,nCLose);
	else
	strRet.Format(_T("10.%d.%d.%d"),pInfo->bCpuIdx+1,nNo,nCLose);

	return strRet;
}
CString CAutoModelStrc::GetRepairSAddrDI(CM3_DI_INFO	*pInfo,int nFlag)
{
	CString strRet = S_EPT;
	
	if(pInfo==NULL)
		return strRet;
	
	int nCLose=nFlag;
	
	if(nFlag==CM3_SADDR_DI_DPI_C)
		nCLose=(pInfo->bOpen==0)? CM3_SADDR_DI_DPI_C : CM3_SADDR_DI_DPI_O;
	
	//V4.0����maser��Go����̵�ַbcpuIdx����
	int bcpuIdxTmp= pInfo->bCpuIdx;
	if (bcpuIdxTmp==2||bcpuIdxTmp==3) bcpuIdxTmp=bcpuIdxTmp-2;
	if (bcpuIdxTmp==4||bcpuIdxTmp==5) bcpuIdxTmp=bcpuIdxTmp-4;
	if (bcpuIdxTmp==6||bcpuIdxTmp==7) bcpuIdxTmp=bcpuIdxTmp-6;
	
	int nNo = pInfo->wNo - bcpuIdxTmp*48;
	
	//int nNo = pInfo->wNo - pInfo->bCpuIdx*48;
	
	/*strRet.Format(_T("DI_%d_%d_%d"),pInfo->bCpuIdx+1,nNo,nCLose);*/
	strRet.Format(_T("10.%d.%d.%d.0.0.1"),pInfo->bCpuIdx+1,nNo,nCLose);
	
	return strRet;
}
//����Goose��goose����
CString CAutoModelStrc::GetSAddrDI(int nCpu,int nNo,int nFlag)
{
	CString strRet = S_EPT;
	
	if(nCpu<0 ||nNo<0 ||nFlag<0 ||nFlag>6 )
		return strRet;
	strRet.Format(_T("10.%d.%d.%d"),nCpu,nNo,nFlag);
	
	return strRet;
}

CString CAutoModelStrc::GetSAddrMT(int nCpu,int nNo,int nFlag)
{
	CString strRet = S_EPT;
	
	if(nCpu<0 ||nNo<0 ||nFlag<0 ||nFlag>6 )
		return strRet;
	strRet.Format(_T("15.%d.%d.%d"),nCpu,nNo,nFlag);
	
	return strRet;
}
CString CAutoModelStrc::GetSAddrMTANACntRs(int nCpu,int nNo,int SAddrType,int nFlag)
{
	CString strRet = S_EPT;
	
	if(nCpu<0 ||nNo<0 ||nFlag<0 ||nFlag>8 )
		return strRet;
	if (SAddrType==0)
	{
		strRet.Format(_T("24.%d.%d.%d"),nCpu,nNo,nFlag);
	}
	else
	{
		strRet.Format(_T("%d.%d.%d.%d"),SAddrType,nCpu,nNo,nFlag);
	}
	
	
	return strRet;
}
CString CAutoModelStrc::GetSAddrSixBit(int nCpu,int nNo,int SAddrType,int nFlag,int nType,int nNo1)
{
	CString strRet = S_EPT;
	
	if(nCpu<0 ||nNo<0 ||nFlag<0 ||nFlag>255 )
		return strRet;

	strRet.Format(_T("%d.%d.%d.%d.%d.%d"),SAddrType,nCpu,nNo,nFlag,nType,nNo1);

	return strRet;
}
CString CAutoModelStrc::GetSAddrSevenBit(int nCpu,int nNo,int SAddrType,int nFlag,int nType,int nNo1,int nFlag1)
{
	CString strRet = S_EPT;
	
	if(nCpu<0 ||nNo<0 ||nFlag<0 ||nFlag>8 )
		return strRet;
	
	strRet.Format(_T("%d.%d.%d.%d.%d.%d.%d"),SAddrType,nFlag1,nCpu,nNo,nFlag,nType,nNo1);
	
	return strRet;
}
CString CAutoModelStrc::GetSAddrMTANAClear(int nCpu,int nNo,int nFlag)
{
	CString strRet = S_EPT;
	
	if(nCpu<0 ||nNo<0 ||nFlag<0 ||nFlag>6 )
		return strRet;
	strRet.Format(_T("25.%d.%d.%d"),nCpu,nNo,nFlag);
	
	return strRet;
}
CString CAutoModelStrc::GetSAddrMTANAOp(int nCpu,int nNo,int nType,int nFlag)
{
	CString strRet = S_EPT;
	
// 	if(nCpu<0 ||nNo<0 ||nFlag<0 ||nFlag>6 )
// 		return strRet;
	strRet.Format(_T("18.%d.%d.%d.%d"),nCpu,nNo,nType,nFlag);
	
	return strRet;
}
CString CAutoModelStrc::GetSAddrMTMMTR(int nCpu,int nNo,int nFlag)
{
	CString strRet = S_EPT;
	
	if(nCpu<0 ||nNo<0 ||nFlag<0 ||nFlag>6 )
		return strRet;
	strRet.Format(_T("19.%d.%d.%d"),nCpu,nNo,nFlag);
	
	return strRet;
}
//V4.00���ӻ�ȡGo��������Ӷ̵�ַ
CString CAutoModelStrc::GetSAddrGoDIVirConn(int nCPU,int bNo,int vPort,int nFlag)
{
	CString strRet = S_EPT;
	if (nCPU<0 || nCPU>5) return strRet;
	if (bNo<0 || bNo>47) return strRet;
	strRet.Format(_T("45.0.%d.%d.%d.1.%d.0"),nCPU,bNo,nFlag,vPort);
	return strRet;	
}

//V4.13���ӻ�ȡGo���˫��������Ӷ̵�ַ
CString CAutoModelStrc::GetSAddrWFGoDIVirConn(int nCPU,int bNo,int vPort,int nFlag)
{
	CString strRet = S_EPT;
	strRet.Format(_T("45.0.%d.%d.%d.0.%d.0"),nCPU,bNo,nFlag,vPort);
	return strRet;	
}
//V4.00���ӻ�ȡGoֱ������Ӷ̵�ַ
CString CAutoModelStrc::GetSAddrGoDTVirConn(int nCPU,int bNo,int vPort,int nFlag)
{
	CString strRet = S_EPT;
	if (nCPU<1 || nCPU>2) return strRet;
	if (bNo<1 || bNo>16) return strRet;
	strRet.Format(_T("90.0.%d.%d.%d.255.%d"),nCPU,bNo,nFlag,vPort);
	return strRet;
	
}
//V4.00���ӻ�ȡGo��λ����Ӷ̵�ַ
CString CAutoModelStrc::GetSAddrGoTAPVirConn(int nCPU,int bNo,int vPort,int nFlag)
{
	CString strRet = S_EPT;
	if (nCPU<1) return strRet;
	if (bNo<1 || bNo>3) return strRet;
	strRet.Format(_T("95.0.%d.%d.%d.255.%d"),nCPU,bNo,nFlag,vPort);
	return strRet;
}
CString CAutoModelStrc::GetSAddrGoTraProAlmVirConn(int bNo,int vPort,int nCPU,int nFlag)
{
	CString strRet = S_EPT;
	if (nCPU<1) return strRet;
	strRet.Format(_T("115.0.%d.%d.%d.255.%d"),nCPU,bNo,nFlag,vPort);
	return strRet;
}
CString CAutoModelStrc::GetSAddrGoTraProEvtVirConn(int bNo,int vPort,int nCPU,int nFlag)
{
	CString strRet = S_EPT;
	if (nCPU<1) return strRet;
	strRet.Format(_T("120.0.%d.%d.%d.255.%d"),nCPU,bNo,nFlag,vPort);
	return strRet;
}
CString CAutoModelStrc::GetSAddrSVVirConn(int nCPU,int bNo,int chnlprop,int subNo,int ChnType)
{
	CString strRet = S_EPT;
	if (nCPU<1) return strRet;
	strRet.Format(_T("205.%d.%d.%d.%d.%d"),nCPU,bNo,chnlprop,subNo,ChnType);
	return strRet;
}
CString CAutoModelStrc::GetSAddrSVDelayVirConn(int bNo,int subNo)
{
	CString strRet = S_EPT;
	strRet.Format(_T("206.1.%d.1.%d.0"),bNo,subNo);
	return strRet;
}
CString CAutoModelStrc::GetSAddrSVDI(CM3_DI_INFO	*pInfo,int nFlag,int nSVNo)
{
	CString strRet = S_EPT;
	
	if(pInfo==NULL)
		return strRet;
	
	int nCLose=nFlag;
	
	if(nFlag==CM3_SADDR_DI_DPI_C)
		nCLose=(pInfo->bOpen==0)? CM3_SADDR_DI_DPI_C : CM3_SADDR_DI_DPI_O;

	//V4.0����maser��Go����̵�ַbcpuIdx����
	int bcpuIdxTmp= pInfo->bCpuIdx;
	if (bcpuIdxTmp==2||bcpuIdxTmp==3) bcpuIdxTmp=bcpuIdxTmp-2;
	if (bcpuIdxTmp==4||bcpuIdxTmp==5) bcpuIdxTmp=bcpuIdxTmp-4;
	if (bcpuIdxTmp==6||bcpuIdxTmp==7) bcpuIdxTmp=bcpuIdxTmp-6;

	int nNo = pInfo->wNo - bcpuIdxTmp*48;

	
	//int nNo = pInfo->wNo - pInfo->bCpuIdx*48;
	
	/*strRet.Format(_T("DI_%d_%d_%d"),pInfo->bCpuIdx+1,nNo,nCLose);*/
	strRet.Format(_T("11.%d.%d.%d.%d"),pInfo->bCpuIdx+1,nNo,nCLose,nSVNo);
	
	return strRet;
}

CString CAutoModelStrc::GetSAddrDOSOE(int nNo,int nSubNo)
{
	CString strRet = S_EPT;
	
	if(nNo<0 || nNo>CM3_DOSOE_NUM)
		return strRet;
	
	int nCpu = (nNo-1)/14 + 11;
	int nIdx = (nNo-1)%14 + 1 ;
	
	strRet.Format(_T("10.%d.%d.%d"),nCpu,nIdx,nSubNo);
	
	return strRet;
}

CString CAutoModelStrc::GetSAddrSBO(BYTE bObj,int nFlag,int nTyp,int nCpu)
{
	CString strRet = S_EPT;

	/*strRet.Format(_T("SBO_%d_%d_%d_%d"),1,nTyp,bObj,nFlag);*/
	strRet.Format(_T("25.%d.%d.%d.%d"),nCpu,nTyp,bObj,nFlag);

	return strRet;
}

void CAutoModelStrc::GetRCAll()
{
	CDrawDoc* pDoc=(CDrawDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveDocument();
	if(pDoc==NULL)
		return ;
	
	int i,j;
	BYTE bObj;
	BOOL bFind;

	CDrawObjList *pList=pDoc->GetObjects();
	POSITION pos = pList->GetHeadPosition();
	WORD wProperty;

	i=0;

	while (pos != NULL)
	{
		CDrawObj* pObj = pList->GetNext(pos);
		if(pObj->m_unViewID==VIEW_ID_PLC 
			&&pObj->IsKindOf(RUNTIME_CLASS(CNodeObj)))
		{
			wProperty=((CNodeObj*)pObj)->m_wProperty;
			wProperty&=0x3800;
			wProperty>>=11;
			if(wProperty==4)
			{
				wProperty=((CNodeObj*)pObj)->m_wProperty;
				wProperty&= 0x7F;
				if(wProperty%2)//��բ
					wProperty=(wProperty-1)/2;
				else
					wProperty/=2;
				
				bObj = (BYTE)wProperty;
				/* �ӿ�ͷ�ң��Ƿ�����ͬ��ID */
				bFind = FALSE;
				for (j=0;j<i;++j)
				{
					if(m_aRC.ctl[j].bObj == bObj)
					{
						bFind=TRUE;
						break;
					}
				}
				
				if(bFind==FALSE)
				{
					m_aRC.ctl[i].bObj = bObj;
					m_aRC.ctl[i].bPLC = 1;
					CM3_CP(m_aRC.ctl[i].name,((CNodeObj*)pObj)->m_strName);
					i++;
				}
			}
		}
	}

	m_aRC.nNum = i;

	CM3_RC_NODE ndTmp;

	if(m_aRC.nNum!=0)
	{
		for(i=0;i<m_aRC.nNum;++i)
		{
			bObj=m_aRC.ctl[i].bObj;
			
			for(j=i+1;j<m_aRC.nNum;++j)
			{
				if(bObj>m_aRC.ctl[j].bObj)
				{
					memcpy(&ndTmp,&(m_aRC.ctl[j]),sizeof(CM3_RC_NODE));
					memcpy(&m_aRC.ctl[j],&(m_aRC.ctl[i]),sizeof(CM3_RC_NODE));
					memcpy(&m_aRC.ctl[i],&ndTmp,sizeof(CM3_RC_NODE));
					
					break;
				}
			}
		}
	}

	LoadRCFromDI(&m_aDI);
}

void CAutoModelStrc::LoadRCFromDI(CM3_DI_GRP_ALL_INFO *pDI)
{
	CM3_DI_INFO	*pInfo;
	CM3_DI_GRP_INFO *pGrp;
	int nIdx,k,i,j;
	BYTE bObj;
	/*BOOL bFind;*/

	for (i=0;i<CM3_RC_MAX;++i)
	{
		m_aRC.DI[i].wNo = 0;
		m_aRC.DI[i].bObj=0;
		CM3_CP(m_aRC.DI[i].name,S_EPT);
		m_aRC.nDI=0;
	}

	for (i=0;i<CM3_DEV_DI_CARD_MAX;++i)
	{
		if(pDI->bCPUUsed[i]==0)
			continue;
		
		for (j=0;j<pDI->bGrpNum[i];++j)
		{
			/* ��ǰCPU���ƫ�� */
			nIdx = pDI->wFstPos[i] + j;
			pGrp = &(pDI->grp[nIdx]);
			if (pGrp->bType==3 || pGrp->bType ==4)
			{
				for (k=0;k<pGrp->bNum;++k)
				{
					pInfo = &(pGrp->info[k]);
					if(CM3_DI_IDX_DPI(k))
					{
						if(pInfo->bDPI==1 || pInfo->bDPIGrp==1)
						{
							if(pInfo->bIsPhase ==1 && pInfo->bPhase!=1)
							{
								k++;
								continue;
							}
							if(pInfo->bCtrl==0)
							{
								k++;
								continue;
							}
						}
					}
					
					if(pInfo->bCtrl==0)
						continue;
					
					bObj = pInfo->bCtrlObj;
					
				/*	bFind = FALSE;
					for (nIdx=0;nIdx<m_aRC.nNum;++nIdx)
					{
						if(m_aRC.ctl[nIdx].bObj == bObj)
						{
							bFind=TRUE;
							
							{
								m_aRC.ctl[nIdx].wNo = pInfo->wNo;
								CM3_CP(m_aRC.ctl[nIdx].desc,pInfo->desc);
							}
							break;
						}
					}*/
					
					nIdx = m_aRC.nDI;
					/*if(bFind==FALSE)*/
					{
						/* ��ǰ�������õ�ң�أ���PLC�в����� */
						{
							m_aRC.DI[nIdx].bObj = bObj;
							m_aRC.DI[nIdx].wNo = pInfo->wNo;
							CM3_CP(m_aRC.DI[nIdx].name,pInfo->desc);
							m_aRC.nDI++;
						}
					}
					
					if(CM3_DI_IDX_DPI(k))
					{
						if(pInfo->bDPI==1 || pInfo->bDPIGrp==1)
							k++;
					}
				}
			}
		}
	}

}

CString CAutoModelStrc::GetSAddrEN(int nNo,int nSubNo)
{
	CString strRet = S_EPT;

	/*strRet.Format(_T("EN_1_%d_1"),nNo);*/
	strRet.Format(_T("40.1.%d.%d"),nNo,nSubNo);
	
	return strRet;
}

CString CAutoModelStrc::GetSAddrSet(int nNo,int nSubNo)
{
	CString strRet = S_EPT;
	
	strRet.Format(_T("55.1.%d.%d"),nNo,nSubNo);
	
	return strRet;
}

CString CAutoModelStrc::GetSAddrAlm(int nNo,int nFlag)
{
	CString strRet = S_EPT;
	
	/*strRet.Format(_T("DI_16_%d_%d"),nNo,nFlag);*/
	//V4.00��CM3_DI10_63��ģ������LD�е��м�̵������һ��
	/*if(nNo==CM3_DI10_63)
		strRet.Format(_T("10.10.%d.%d"),nNo,nFlag);
	else*/
		strRet.Format(_T("10.16.%d.%d"),nNo,nFlag);
	
	return strRet;
}

CString CAutoModelStrc::GetSAddrMidRel(int nNo,int nFlag)
{
	CString strRet = S_EPT;

// 	if (nNo>0 && nNo<128/*nNo<64*/)
// 		strRet.Format(_T("10.10.%d.%d"),nNo,nFlag);
 	if (nNo>0 && nNo<81)
		strRet.Format(_T("10.10.%d.%d"),nNo,nFlag);	
	else if(nNo>80 && nNo<128)
		strRet.Format(_T("10.9.%d.%d"),nNo-80,nFlag);	

	return strRet;
}

CString CAutoModelStrc::GetSAddrGooseAlm(int nNo,int nFlag)
{
	CString strRet = S_EPT;
	
	strRet.Format(_T("100.1.%d.%d"),nNo,nFlag);
	
	return strRet;
}

CString CAutoModelStrc::GetSAddrMUAlmMaster(int nNo,int nFlag)
{
	CString strRet = S_EPT;
	
	strRet.Format(_T("190.1.%d.%d"),nNo,nFlag);
	
	return strRet;
}

CString CAutoModelStrc::GetSAddrProGooseAlm(int nNo,int nFlag)
{
	CString strRet = S_EPT;
	
	strRet.Format(_T("140.1.%d.%d"),nNo,nFlag);
	
	return strRet;
}
CString CAutoModelStrc::GetSAddrProAlm(int nNo,int nFlag)
{
	CString strRet = S_EPT;
	
	strRet.Format(_T("105.1.%d.%d"),nNo,nFlag);
	
	return strRet;
}
CString CAutoModelStrc::GetSAddrProEvt(int nNo,int nFlag)
{
	CString strRet = S_EPT;
	
	strRet.Format(_T("110.1.%d.%d"),nNo,nFlag);
	
	return strRet;
}
CString CAutoModelStrc::GetSAddr38(int nNo, int nFlag)
{
	CString strRet = S_EPT;
	
	/*strRet.Format(_T("ALM_1_%d_%d"),nNo,nFlag);*/
	strRet.Format(_T("60.1.%d.%d"),nNo,nFlag);
	
	return strRet;
}

void CAutoModelStrc::MapCommon()
{
	m_docIcd.InitLDCmn();

	m_docIcd.MapEN();

	//v4.21�ϰģ�����״̬��Ϣ�澯
	m_docIcd.MapRunState();	

	m_docIcd.MapAlarm();

//	m_docIcd.MapDOSoe(&m_aDO);
	
//	m_docIcd.MapEvt();
	m_docIcd.MapVolSwitch();
    
	BOOL bPara= (m_transProAlm & 0x20)>>5;//�Ƿ�װ�ò�����ģ
	m_docIcd.MapSetting(bPara);
	
	
	m_docIcd.MapGooseAlm();
	//V4.0��֧��1��goose��
	if (m_pDev->m_aGO.GetSize()==1&&m_pDev->m_aGoCPUEn.GetSize()==1)
	{
		m_docIcd.MapProGooseAlm();
		m_docIcd.MapProAlm();
		m_docIcd.MapProEvt();
	}

	m_docIcd.MapMUMstAlm();
	BOOL bMetering= (m_transProAlm & 8)>>3;//�Ƿ������ģ
	if (bMetering==1)
	{
		m_docIcd.InitLDMetr();
		m_docIcd.MapMTUV();
		m_docIcd.MapMTUC();
		m_docIcd.MapMTOV();
		m_docIcd.MapMTOC();
		
		m_docIcd.MapMETRGGIO();
	    m_docIcd.MapIARC();
		m_docIcd.MapMMTR();
	}
	else
	{
		m_docIcd.DelLD("METR");
	}
	BOOL bTimeManage= (m_transProAlm & 0x10)>>4;//�Ƿ�ʱ�����ģ
	if (bTimeManage==1)
	{
		m_docIcd.MapLTSM();
		m_docIcd.MapLTSMGOOSE(3,1);
		m_docIcd.MapLTSMSV(3,4);
		m_docIcd.MapGGIOTimeGOOSE(3,1);
		m_docIcd.MapGGIOTimeSV(3,4);
	}
	else
	{
        m_docIcd.DelLTSMRCB();
	}
	BOOL bLightPower= (m_transProAlm & 0x40)>>6;//�Ƿ��ǿ��ģ
	if (bLightPower==1)
	{
		m_docIcd.AddDSAin2();
		//m_docIcd.MapSTMP();
		m_docIcd.MapSPVT();
		m_docIcd.MapSCLI();
	} 
	else
	{
		m_docIcd.DelWaring3();
		m_docIcd.DelAin2();
	}
	
	if (bPara==1)
	{
		m_docIcd.MapGDRSYNPara();
		m_docIcd.MapGDDIPara();
		m_docIcd.MapGDCTRLPara();
		m_docIcd.MapGDDCPara();
		
	}
	//else
	//{	
	//	m_docIcd.DelParaRCB();
	//}
	
}

// void CAutoModelStrc::MapTRIP()
// {
// 	m_docIcd.m_nLNTrip=3;
// 	m_docIcd.InitLDTrip();
// 	m_docIcd.InitLDSvld();//by zy
// 
// 	//v4.21���Goose����
// 	if (m_pDev->m_aGO.GetSize()==1)
// 	{
// 		m_docIcd.AddTripGoLN();
// 	}
// 
// 	m_docIcd.AddProGOVirConn(m_docIcd.m_CM3.goSubVirTermn);
// 	m_docIcd.AddTraProVirConn(m_docIcd.m_CM3.goSubVirTermn);
// 
// 	BOOL bDoubleNet = (m_bMidRelayST & 0x02)>>1;
// 	if (bDoubleNet)//B������� 11.5.19
// 	{
// 		m_docIcd.AddProGOVirConn(m_docIcd.m_CM3.goSubVirTermn,FALSE);//V4.05A
// 		BOOL b258Brd = (m_bMidRelayST & 0x10)>>4;//�Ƿ�258��
// 		if(!b258Brd)
// 			m_docIcd.AddTraProVirConn(m_docIcd.m_CM3.goSubVirTermn,FALSE);//V4.10
// 	}
// 
// 	BOOL isSVInput=FALSE;
// 	for (int i=0;i<m_pDev->m_aAI.GetSize();i++)
// 	{
// 		if (m_pDev->m_aAI[i].strSV==1)
// 		{
// 			isSVInput=TRUE;
// 			break;
// 		}
// 	}
// 
// 	//���û��SV��Ϣ���򲻵���M1���ʵ�
// 	m_docIcd.outM1 = isSVInput;
// 	//���GSE��SV��һ���򲻵���M1���ʵ�
// 	m_docIcd.outM1 &= !m_docIcd.m_CM3.multiGOSV;
// 
// 	if (isSVInput)//V4.10:����������ֻ�������GSE��SV�Ƿ��һ������Ҫ����SV�����
// 		m_docIcd.AddProSVVirConn(/*m_docIcd.m_CM3.multiGOSV && */m_docIcd.m_CM3.goSubVirTermn);
// 	
// }

void CAutoModelStrc::MapTRIPByConfig()
{
	m_docIcd.m_nLNTrip=3;
	m_docIcd.InitLDTrip();
	m_docIcd.InitLDSvld();
	
	//v4.20 ����Ӳ�������󻯴��������ݽ����ʵ����������ģ��
	if (m_pDev->m_aGO.GetSize()==1)
	{
		//���Goose����
		m_docIcd.AddTripGoLN();

		if (m_docIcd.m_CM3.goSubVirTermn)
		{
			if (m_pDev->m_aGoCPUEn.GetSize()==1)
			{
				
				
				//GOOSE����
				int num=m_pDev->m_aGoCPUEn[0].goDICpuNum;
				if (num > 0)
					m_docIcd.AddProGOVirLN();//��������ӵ�LN

				//�ȵ���GOOSEֱ��
				int numDT=m_pDev->m_aGoCPUEn[0].goDTCpuNum;
				if (numDT==1 || numDT==2)
				{
					m_docIcd.AddProGODTVirConn(&m_aGO1DT,numDT);
				}
				
				int iSpcTableNo =1;
				int iDpcTableNo =1;
				m_docIcd.ClearDpsNodeType();
				switch(num)
				{
				case 1:
					m_docIcd.AddProGOVirConn(&m_aGO1DI1,iSpcTableNo,iDpcTableNo,1);
					break;
				case 2:
					m_docIcd.AddProGOVirConn(&m_aGO1DI1,iSpcTableNo,iDpcTableNo,1);
					m_docIcd.AddProGOVirConn(&m_aGO1DI2,iSpcTableNo,iDpcTableNo,2);
					break;
				case 3:
					m_docIcd.AddProGOVirConn(&m_aGO1DI1,iSpcTableNo,iDpcTableNo,1);
					m_docIcd.AddProGOVirConn(&m_aGO1DI2,iSpcTableNo,iDpcTableNo,2);
					m_docIcd.AddProGOVirConn(&m_aGO1DI3,iSpcTableNo,iDpcTableNo,3);
					break;
				}
				//m_docIcd.AddProGOVirConn(&m_aGO1DI2,iSpcTableNo,iDpcTableNo);
				m_docIcd.MakeDpsGoVirConn();
				int iVirSpc=1;
				m_docIcd.MakeSpsGOVirConn(&m_aGO1DI2,iVirSpc,iDpcTableNo,2);
				
				//GOOSE��λ
				num=m_pDev->m_aGoCPUEn[0].goTapNum;
				if (num==1 || num==3)
				{
					m_docIcd.AddProGOTAPVirConn(&m_aGO1Tap);
				}
			}
		}

		//�����¼��͸澯
 		m_docIcd.AddTraProVirConn(m_docIcd.m_CM3.goSubVirTermn);
	}
	else
	{
		//���GOOSEѹ��δͶ�룬����SV����һ�����ٱ���G1���ʵ�
		if(!m_docIcd.m_CM3.multiGOSV)
		{
			m_docIcd.outPutIcdAP=CM4_ICD_AP_MMS;						
		}
	}
	//ʱ�����
	BOOL bTimeManage= (m_transProAlm & 0x10)>>4;//�Ƿ�ʱ�����ģ
	if (bTimeManage==1)
	{
		m_docIcd.MapGOTimeRequire();
		//m_docIcd.MapGOTime();//��־��˵ ��T1��T16����ʵ��û��ֱ����  ��ʱ����ģ
		m_docIcd.MapGOTimeManage();
	}
	else
	{
		m_docIcd.DelTimeGCB();
	}
	//����SV�����
	m_docIcd.AddProSVVirConn(&m_aAI);
}

CString CAutoModelStrc::GetSAddrEvt(int nLN, int nDO)
{
	CString strRet = S_EPT;
	
	/*strRet.Format(_T("ACT_1_%d_%d"),nLN,nDO);*/
	strRet.Format(_T("20.1.%d.%d"),nLN,nDO);
	
	return strRet;
}

CString CAutoModelStrc::GetSAddrVolSwitch(int nFlag,int nSub)
{
	CString strRet = S_EPT;
	
	strRet.Format(_T("20.1.%d.%d"),nFlag,nSub);
	
	return strRet;
}

void CAutoModelStrc::Serialize(CArchive &ar)
{
	USES_CONVERSION;
	ar.SerializeClass(RUNTIME_CLASS(CAutoModelStrc));
	CObject::Serialize(ar);

	int i=0,j=0;
	CString strTmp;
	CM3_DI_GRP_INFO *pGrp=NULL;
	CM3_DI_INFO *pInfo=NULL;
	//char charBuff[100];
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		/* �洢������ֻ�б�Ҫ��Ϣ
		 * ģ�������Զ���ģ��ֻ������ȡ��������
		 */
		ar << VERSION_0502 ;

		ar << m_strIcdName;
		ar << m_strGoIcdName;//4.0����
		ar << m_bNoSync;

#ifdef CM3_AR_MUST

		ar << m_docIcd.m_header.nItem;

		for (i=0;i<m_docIcd.m_header.nItem;++i)
		{
			CM3_AR_S_S(ar,m_docIcd.m_header.item[i].version);
			CM3_AR_S_S(ar,m_docIcd.m_header.item[i].revision);
			CM3_AR_S_S(ar,m_docIcd.m_header.item[i].when);
			CM3_AR_S_S(ar,m_docIcd.m_header.item[i].who);
			CM3_AR_S_S(ar,m_docIcd.m_header.item[i].what);
			CM3_AR_S_S(ar,m_docIcd.m_header.item[i].why);
		}

		/* 2008-4-23 WZM
		 * m_aAI.bSV��Ϊȫ��ȡ�����ã��ڼ���ʱ���Ƶ�m_bSVEna
		 */
		ar << m_bSVEna/*m_aAI.bSV*/;
		
		for(i=0;i<CM3_DEV_AI_ALL_MAX;++i)
		{
			CString str = (CString)(m_aAI.info[i].desc);
			//strcpy(charBuff,(_bstr_t)str);
			//ar << charBuff;
			//LPSTR lpstr = T2A(str.GetBuffer(1));
			//ar << lpstr;
			ar << str;
		}

		/* 2008-4-23 WZM
		 * ֱ����ȡ������m_aDT.bSV
		 * 2008-07-08 WZM
		 * ʹ��m_bHasPrgOp��ʾ�Ƿ�֧��˳��
		 */
		ar << m_bHasPrgOp;
		ar << m_bMidRelayST;	//V4.00����
		ar << m_transProAlm;	//V4.00����
		ar << m_transProEvt;	//V4.00����
		ar << m_proSoftConn;	//V4.00����
		
		for(i=0;i<CM3_DEV_DT_ALL_MAX;++i)
		{
			CString str = (CString)(m_aDT.info[i].desc);
			//strcpy(charBuff,(_bstr_t)str);
			//ar << charBuff;
			//LPCTSTR lpstr = T2A(str.GetBuffer(1));
			//ar << lpstr;
           ar << (CString)(m_aDT.info[i].desc);
		}
		
		ar << m_aDI.bTapCtrl;

		/* 2008-4-23 WZM
		 * ��λ��ȡ������1̨���̨��ѹ����λ����ѡ��
		 */
		ar << m_aDI.bTapSV;
		//����
		for(i=0;i<CM3_DEV_DI_GRP_ALL_MAX;++i)
		{
			pGrp = &(m_aDI.grp[i]);
			for (j=0;j<pGrp->bNum;++j)
			{
				pInfo = &(pGrp->info[j]);

				ar << pInfo->bDPI;
				ar << pInfo->bOpen;
				ar << pInfo->bPair;
				ar << pInfo->bCtrl;
				ar << pInfo->bCtrlObj;
				ar << pInfo->bIsPhase;
				ar << pInfo->bPhase;
				/* 2008-4-23 WZM
				 * DI��ȡ������
				 */
				ar << pInfo->bSV;
				ar << pInfo->bBS;
				ar << pInfo->bBreak;
				ar << pInfo->BBak;
				CString str = (CString)(pInfo->desc);
				//strcpy(charBuff,(_bstr_t)str);
				//ar << charBuff;
				//LPSTR lpstr = T2A(str.GetBuffer(1));
				//ar << lpstr;
				ar << (CString)(pInfo->desc);
			}
		}


		ar << m_aRC.nNoPos;
		
		for (i=0;i<m_aRC.nNoPos;++i)
		{
			ar << m_aRC.noPos[i].bObj;
			CString str = (CString)(m_aRC.noPos[i].name);
			//strcpy(charBuff,(_bstr_t)str);
			///ar << charBuff;
			//LPSTR lpstr = T2A(str.GetBuffer(1));
			//ar << str;
			//ar << (CString)(m_aRC.noPos[i].name);
			ar << (CString)(m_aRC.noPos[i].name);
		}

		ar.Write(&(m_aDO),sizeof(CM3_DO_CFG));

		//Goose�����1
		for(i=0;i<CM4_GO_SUB_CARGRP_NUM;++i)
		{
			pGrp = &(m_aGO1DI1.grp[i]);
			for (j=0;j<pGrp->bNum;++j)
			{
				pInfo = &(pGrp->info[j]);

				ar << pInfo->bDPI;
				ar << pInfo->bOpen;
				ar << pInfo->bPair;
				ar << pInfo->bCtrl;
				ar << pInfo->bCtrlObj;
				ar << pInfo->bIsPhase;
				ar << pInfo->bPhase;
				ar << pInfo->bSV;
				ar << pInfo->bBS;
				ar << pInfo->bBreak;
				CString str = (CString)(pInfo->desc);
				//strcpy(charBuff,(_bstr_t)str);
				///ar << charBuff;
				//LPSTR lpstr = T2A(str.GetBuffer(1));
				//ar << str;
				ar << (CString)(pInfo->desc);

			}
		}

		//Goose�����2
		for(i=0;i<CM4_GO_SUB_CARGRP_NUM;++i)
		{
			pGrp = &(m_aGO1DI2.grp[i]);
			for (j=0;j<pGrp->bNum;++j)
			{
				pInfo = &(pGrp->info[j]);
				
				ar << pInfo->bDPI;
				ar << pInfo->bOpen;
				ar << pInfo->bPair;
				ar << pInfo->bCtrl;
				ar << pInfo->bCtrlObj;
				ar << pInfo->bIsPhase;
				ar << pInfo->bPhase;
				ar << pInfo->bSV;
				ar << pInfo->bBS;
				ar << pInfo->bBreak;
   				ar << (CString)(pInfo->desc);
				//ar << (CString)(pInfo->desc);
				CString str = (CString)(pInfo->desc);
				//strcpy(charBuff,(_bstr_t)str);
				///ar << charBuff;
				//LPSTR lpstr = T2A(str.GetBuffer(1));
				//ar << str;
			}
		}

		//Goose�����3
		for(i=0;i<CM4_GO_SUB_CARGRP_NUM;++i)
		{
			pGrp = &(m_aGO1DI3.grp[i]);
			for (j=0;j<pGrp->bNum;++j)
			{
				pInfo = &(pGrp->info[j]);
				
				ar << pInfo->bDPI;
				ar << pInfo->bOpen;
				ar << pInfo->bPair;
				ar << pInfo->bCtrl;
				ar << pInfo->bCtrlObj;
				ar << pInfo->bIsPhase;
				ar << pInfo->bPhase;
				ar << pInfo->bSV;
				ar << pInfo->bBS;
				ar << pInfo->bBreak;
				ar << (CString)(pInfo->desc);
				//ar << (CString)(pInfo->desc);
				CString str = (CString)(pInfo->desc);
				//strcpy(charBuff,(_bstr_t)str);
				///ar << charBuff;
				//LPSTR lpstr = T2A(str.GetBuffer(1));
				//ar << str;
			}
		}

		for(i=0;i<CM4_GO_SUB_DT_MAX;++i)
		{
			ar << (CString)(m_aGO1DT.info[i].desc);
			CString str = (CString)(m_aGO1DT.info[i].desc);
			//strcpy(charBuff,(_bstr_t)str);
			///ar << charBuff;
			//LPSTR lpstr = T2A(str.GetBuffer(1));
			//ar << str;
		}

		//GO��λ��д
		ar <<m_aGO1Tap.bTapCtrl[0];
		ar <<m_aGO1Tap.bTapCtrlNum[0];
		ar <<m_aGO1Tap.bTapPhase[0];
		for(i=0;i<CM4_GO_SUB_TAP_NUM;++i)
		{
			ar <<m_aGO1Tap.goInfo[i].bTapCtrl;
			ar <<m_aGO1Tap.goInfo[i].bTapMul;
			ar <<m_aGO1Tap.goInfo[i].bTapPhase;
			ar <<m_aGO1Tap.goInfo[i].bTapSV;
			ar << (CString)(m_aGO1Tap.goInfo[i].desc);
			CString str = (CString)(m_aGO1Tap.goInfo[i].desc);
			//strcpy(charBuff,(_bstr_t)str);
			///ar << charBuff;
			//LPSTR lpstr = T2A(str.GetBuffer(1));
			//ar << str;
		}


		/* ����ģ���йؼ����ַ��� */

		CM3_AR_S_S(ar,m_docIcd.m_CM3.iedName );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.ipA );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.ipB );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.rptScanRate );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.sclXsd );
	
		CM3_AR_S_S(ar,m_docIcd.m_CM3.ap );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.tit );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.qua );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.PSel );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.SSel );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.TSel );

		CM3_AR_S_S(ar,m_docIcd.m_CM3.sboTimOut );

		//V4.0���Ӵ洢���̲�ͨ���жϸ������Լ�ת�����̲㱨�ĸ���
		CM3_AR_S_S(ar,m_docIcd.m_CM3.nGoComAlm );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.nTransProAlm );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.nTransProEvt );

		//V4.0���Ӵ洢Goose��Goose���������Ϣ�������
		CM3_AR_S_S(ar,m_docIcd.m_CM3.iedNameGO );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.ap2 );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.Mac);
		CM3_AR_S_S(ar,m_docIcd.m_CM3.Vid);
		CM3_AR_S_S(ar,m_docIcd.m_CM3.AppID);
		CM3_AR_S_S(ar,m_docIcd.m_CM3.Priority);
		CM3_AR_S_S(ar,m_docIcd.m_CM3.MinTime);
		CM3_AR_S_S(ar,m_docIcd.m_CM3.MaxTime);
		ar<<m_docIcd.m_CM3.goPubQ;
		ar<<m_docIcd.m_CM3.goPubT;
		ar<<m_docIcd.m_CM3.goSubVirTermn;
		CM3_AR_S_S(ar,m_docIcd.m_CM3.goSubVermDPS);
		ar<<m_docIcd.m_CM3.multiAPInIED;
		CM3_AR_S_S(ar,m_docIcd.m_CM3.numGoSubBay);
		CM3_AR_S_S(ar,m_docIcd.m_CM3.numGoSubPro);
		CM3_AR_S_S(ar,m_docIcd.m_CM3.numSVSubPro);
		ar<<m_docIcd.m_CM3.multiGOSV;
//#ifdef CFGVERSION_0401
		//	if (fileVersion==VERSION_0401)// ��ȡgoose������Ϣ [2/22/2013 qiweihua
		{
			ar << m_aGODO.wRows;
			ar << m_aGODO.bGrps;
			for(int i=0;i<CM4_GO_SUB_CARGRP_NUM;++i)
			{
				pGrp = &(m_aGODO.grp[i]);
				ar << pGrp->bCpuIdx;
				ar << pGrp->bGlbIdx;
				ar << pGrp->bIdx;
				ar << pGrp->bNum;
				ar << pGrp->bType;
				for (j=0;j<pGrp->bNum;++j)
				{
					pInfo = &(pGrp->info[j]);
					
					ar << pInfo->bCpuIdx;
					ar << pInfo->bGlbIdx;
					ar << pInfo->bGrpIdx; 
					ar << pInfo->bIdx;
					ar << pInfo->wNo;
					
					ar << pInfo->bDPI;
					ar << pInfo->bOpen;
					ar << pInfo->bPair; 
					ar << pInfo->bCtrl;
					ar << pInfo->bCtrlObj;
					ar << pInfo->bIsPhase;
					ar << pInfo->bPhase;
					ar << pInfo->bSV;
					ar << pInfo->bBS;
					ar << pInfo->bBreak;
					ar << pInfo->bTAP;
					ar << pInfo->BBak;
					ar << (CString)(pInfo->desc);
					CString str = (CString)(pInfo->desc);
					//strcpy(charBuff,(_bstr_t)str);
					///ar << charBuff;
					//LPSTR lpstr = T2A(str.GetBuffer(1));
					//ar << str;
				}
			}
			
		}
		
		ar << m_bakbak1;
		ar << m_bakbak2;
		ar << m_flagZJGOOSEIN;
		ar << m_flagZJGOOSEOUT;
		ar << m_flagZJSV;
		ar << (CString)(m_bakbak3);
		//�м�̵�������
		{
			ar << m_aMidRel.wRows;
			ar << m_aMidRel.bGrps;
			for (int kk=0;kk<3;kk++)
			{
				ar <<m_aMidRel.bCPUUsed[kk];
				ar <<m_aMidRel.bGrpNum[kk];
				ar <<m_aMidRel.wFstPos[kk];
				ar <<m_aMidRel.bCPUNum[kk];
				ar <<m_aMidRel.wFstRow[kk];
				ar <<m_aMidRel.wFstPos[kk];
				ar <<m_aMidRel.bRows[kk];
			}

			for(int i=0;i<0x15;++i)
			{
				pGrp = &(m_aMidRel.grp[i]);
				ar << pGrp->bCpuIdx;
				ar << pGrp->bGlbIdx;
				ar << pGrp->bIdx;
				ar << pGrp->bNum;
				ar << pGrp->bType;
				for (j=0;j<pGrp->bNum;++j)
				{
					pInfo = &(pGrp->info[j]);
					
					ar << pInfo->bCpuIdx;
					ar << pInfo->bGlbIdx;
					ar << pInfo->bGrpIdx; 
					ar << pInfo->bIdx;
					ar << pInfo->wNo;
					
					ar << pInfo->bDPI;
					ar << pInfo->bOpen;
					ar << pInfo->bPair; 
					ar << pInfo->bCtrl;
					ar << pInfo->bCtrlObj;
					ar << pInfo->bIsPhase;
					ar << pInfo->bPhase;
					ar << pInfo->bSV;
					ar << pInfo->bBS;
					ar << pInfo->bBreak;
					ar << pInfo->bTAP;
					ar << pInfo->BBak;
					ar << (CString)(pInfo->desc);
					CString str = (CString)(pInfo->desc);
					//strcpy(charBuff,(_bstr_t)str);
					///ar << charBuff;
					//LPSTR lpstr = T2A(str.GetBuffer(1));
					//ar << str;
				}
			}
			
		}
//#endif

/*		CM3_AR_S_S(ar,m_docIcd.m_CM3.ldMeas );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.ldCommon );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.ldCtrl );

		CM3_AR_S_S(ar,m_docIcd.m_CM3.dsMeas );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.dsCtrl );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.dsEvt );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.dsEn );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.dsAlm );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.dsDOSoe );

		CM3_AR_S_S(ar,m_docIcd.m_CM3.rcbMeas );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.rcbCtrl );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.rcbEvt );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.rcbEn );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.rcbAlm );
		CM3_AR_S_S(ar,m_docIcd.m_CM3.rcbDOSoe );
*/

/*		ar << m_docIcd.m_CM3.EN.num;

		for (i=0;i<m_docIcd.m_CM3.EN.num;++i)
		{
			ar << m_docIcd.m_CM3.EN.item[i].bNo ;
			CM3_AR_S_S(ar,m_docIcd.m_CM3.EN.item[i].name );
			CM3_AR_S_S(ar,m_docIcd.m_CM3.EN.item[i].desc );
			CM3_AR_S_S(ar,m_docIcd.m_CM3.EN.item[i].descEn );
		}
*/		
/*		ar << m_docIcd.m_CM3.alarm.num;
		
		for (i=0;i<m_docIcd.m_CM3.alarm.num;++i)
		{
			ar << m_docIcd.m_CM3.alarm.item[i].bNo ;
			CM3_AR_S_S(ar,m_docIcd.m_CM3.alarm.item[i].name );
			CM3_AR_S_S(ar,m_docIcd.m_CM3.alarm.item[i].desc );
			CM3_AR_S_S(ar,m_docIcd.m_CM3.alarm.item[i].descEn );
		}

		ar << m_docIcd.m_CM3.sf38.num;
		
		for (i=0;i<m_docIcd.m_CM3.sf38.num;++i)
		{
			ar << m_docIcd.m_CM3.sf38.item[i].bNo ;
			CM3_AR_S_S(ar,m_docIcd.m_CM3.sf38.item[i].name );
			CM3_AR_S_S(ar,m_docIcd.m_CM3.sf38.item[i].desc );
			CM3_AR_S_S(ar,m_docIcd.m_CM3.sf38.item[i].descEn );
		}
		
		ar << m_docIcd.m_CM3.sf37.num;
		
		for (i=0;i<m_docIcd.m_CM3.sf37.num;++i)
		{
			ar << m_docIcd.m_CM3.sf37.item[i].bNo ;
			CM3_AR_S_S(ar,m_docIcd.m_CM3.sf37.item[i].name );
			CM3_AR_S_S(ar,m_docIcd.m_CM3.sf37.item[i].desc );
			CM3_AR_S_S(ar,m_docIcd.m_CM3.sf37.item[i].descEn );
		}
		
		ar << m_docIcd.m_CM3.sf37DO.num;
		
		for (i=0;i<m_docIcd.m_CM3.sf37DO.num;++i)
		{
			ar << m_docIcd.m_CM3.sf37DO.item[i].bNo ;
			CM3_AR_S_S(ar,m_docIcd.m_CM3.sf37DO.item[i].name );
			CM3_AR_S_S(ar,m_docIcd.m_CM3.sf37DO.item[i].desc );
			CM3_AR_S_S(ar,m_docIcd.m_CM3.sf37DO.item[i].descEn );
		}
*/
/*		ar << m_docIcd.m_CM3.set.num;
		
		for (i=0;i<m_docIcd.m_CM3.set.num;++i)
		{
			ar << m_docIcd.m_CM3.set.item[i].wNo ;
			ar << m_docIcd.m_CM3.set.item[i].bType ;
			CM3_AR_S_S(ar,m_docIcd.m_CM3.set.item[i].name );
			CM3_AR_S_S(ar,m_docIcd.m_CM3.set.item[i].desc );
			CM3_AR_S_S(ar,m_docIcd.m_CM3.set.item[i].descEn );
		}
*/
		ar << m_lockDev.bDevNum;
		CM3_AR_S_S(ar,m_lockDev.bGooseFile );

		for (i=0;i<m_lockDev.bDevNum;++i)
		{
			CM3_AR_S_S(ar,m_lockDev.dev[i].iedName );
			ar << m_lockDev.dev[i].bNum;	
			for (j=0;j<m_lockDev.dev[i].bNum;++j)
			{
				ar << m_lockDev.dev[i].bNo[j];
				CM3_AR_S_S(ar,m_lockDev.dev[i].diDesc[j] );
			}
		}

#else
		ar.Write(&(m_docIcd.m_header),sizeof(SCL_HEADER));
		ar.Write(&m_aAI,sizeof(CM3_AI_ALL_INFO));
		ar.Write(&m_aDT,sizeof(CM3_DT_ALL_INFO));
		ar.Write(&m_aDI,sizeof(CM3_DI_GRP_ALL_INFO));
		ar.Write(&m_aRC,sizeof(CM3_RC_LIST));

		ar.Write(&(m_docIcd.m_CM3),sizeof(CSI200E_ICD_INFO));
#endif
	}
	else
	{
		// TODO: add loading code here
		DWORD dwVersion;
		
		ar >> dwVersion;

		ar >> m_strIcdName;

		//v4.0����
		if (dwVersion==VERSION_0400
			||dwVersion==VERSION_0500||dwVersion==VERSION_0501||dwVersion==VERSION_0502)
			ar >> m_strGoIcdName;
		else
			m_strGoIcdName=_T("");

		ar >> m_bNoSync;

#ifdef CM3_AR_MUST

		ar >> m_docIcd.m_header.nItem;

		for (i=0;i<m_docIcd.m_header.nItem;++i)
		{
			CM3_AR_S_L(ar,m_docIcd.m_header.item[i].version);
			CM3_AR_S_L(ar,m_docIcd.m_header.item[i].revision);
			CM3_AR_S_L(ar,m_docIcd.m_header.item[i].when);
			CM3_AR_S_L(ar,m_docIcd.m_header.item[i].who);
			CM3_AR_S_L(ar,m_docIcd.m_header.item[i].what);
			CM3_AR_S_L(ar,m_docIcd.m_header.item[i].why);
		}

		/* 2008-4-23 WZM
		 * ʹ��m_aAI.bSV�洢ȫ��SV����
		 */
		ar >> m_bSVEna/*m_aAI.bSV*/;

		for(i=0;i<CM3_DEV_AI_ALL_MAX;++i)
		{
			ar >> strTmp;
			//CM3_CP(m_aAI.info[i].desc,strTmp);
			TcharCopy(m_aAI.info[i].desc,strTmp);
		}

		/* 2008-4-23 WZM
		 * ֱ����ȡ������m_aDT.bSV
		 * 2008-07-08 WZM
		 * ʹ��m_bHasPrgOp��ʾ�Ƿ�֧��˳��
		 */
		ar >> m_bHasPrgOp;
		//v4.0����
		if (dwVersion==VERSION_0400
			||dwVersion==VERSION_0500||dwVersion==VERSION_0501||dwVersion==VERSION_0502)
		{
			ar >> m_bMidRelayST; 
			ar >> m_transProAlm; 
			ar >> m_transProEvt;  
			ar >> m_proSoftConn; 
			if (dwVersion==VERSION_0400) 
			{// [7/16/2014]4.0��δ��ʼ��
				m_transProAlm = m_transProAlm &3;
				m_transProEvt = 0;
				m_proSoftConn = 0;
			}
			 
		}
		else
		{
			m_bMidRelayST=0;
			m_transProAlm=0;
			m_transProEvt=0;
			m_proSoftConn=0;
		}
		
		for(i=0;i<CM3_DEV_DT_ALL_MAX;++i)
		{
			ar >> strTmp;
			//CM3_CP(m_aDT.info[i].desc,strTmp);
			TcharCopy(m_aDT.info[i].desc,strTmp);
		}

		ar >> m_aDI.bTapCtrl;

		/* 2008-4-23 WZM
		 * ��λ��ȡ�����ڶ��ѹ����λѡ��
		 */
		ar >> m_aDI.bTapSV;
		//����
		for(i=0;i<CM3_DEV_DI_GRP_ALL_MAX;++i)
		{
			pGrp = &(m_aDI.grp[i]);
			for (j=0;j<pGrp->bNum;++j)
			{
				pInfo = &(pGrp->info[j]);
				
				ar >> pInfo->bDPI;
				ar >> pInfo->bOpen;
				ar >> pInfo->bPair;
				ar >> pInfo->bCtrl;
				ar >> pInfo->bCtrlObj;
				ar >> pInfo->bIsPhase;
				ar >> pInfo->bPhase;
				/* 2008-4-23 WZM
				 * DI��ȡ������
				 */
				ar >> pInfo->bSV;
				ar >> pInfo->bBS;
				ar >> pInfo->bBreak;
				if (dwVersion==VERSION_0502)
				{
					ar >> pInfo->BBak;
				}
				ar >> strTmp;
				TcharCopy(pInfo->desc,strTmp);
			}
		}

		ar >> m_aRC.nNoPos;

		for (i=0;i<m_aRC.nNoPos;++i)
		{
			ar >> m_aRC.noPos[i].bObj;
			ar >> strTmp;
			//CM3_CP(m_aRC.noPos[i].name,strTmp);
			TcharCopy(m_aRC.noPos[i].name,strTmp);
		}

		ar.Read(&(m_aDO),sizeof(CM3_DO_CFG));


		if (dwVersion==VERSION_0400
			||dwVersion==VERSION_0500||dwVersion==VERSION_0501||dwVersion==VERSION_0502)
		{
			//Goose�����1
			for(i=0;i<CM4_GO_SUB_CARGRP_NUM;++i)
			{
				pGrp = &(m_aGO1DI1.grp[i]);
				for (j=0;j<pGrp->bNum;++j)
				{
					pInfo = &(pGrp->info[j]);
					
					ar >> pInfo->bDPI;
					ar >> pInfo->bOpen;
					ar >> pInfo->bPair;
					ar >> pInfo->bCtrl;
					ar >> pInfo->bCtrlObj;
					ar >> pInfo->bIsPhase;
					ar >> pInfo->bPhase;
					ar >> pInfo->bSV;
					ar >> pInfo->bBS;
					ar >> pInfo->bBreak;
					ar >> strTmp;
					//CM3_CP(pInfo->desc,strTmp);
					TcharCopy(pInfo->desc,strTmp);
				}
			}
			
			//Goose�����2
			for(i=0;i<CM4_GO_SUB_CARGRP_NUM;++i)
			{
				pGrp = &(m_aGO1DI2.grp[i]);
				for (j=0;j<pGrp->bNum;++j)
				{
					pInfo = &(pGrp->info[j]);
					
					ar >> pInfo->bDPI;
					ar >> pInfo->bOpen;
					ar >> pInfo->bPair;
					ar >> pInfo->bCtrl;
					ar >> pInfo->bCtrlObj;
					ar >> pInfo->bIsPhase;
					ar >> pInfo->bPhase;
					ar >> pInfo->bSV;
					ar >> pInfo->bBS;
					ar >> pInfo->bBreak;
					ar >> strTmp;
					//CM3_CP(pInfo->desc,strTmp);
					TcharCopy(pInfo->desc,strTmp);
				}
			}
			
			//Goose�����3
			for(i=0;i<CM4_GO_SUB_CARGRP_NUM;++i)
			{
				pGrp = &(m_aGO1DI3.grp[i]);
				for (j=0;j<pGrp->bNum;++j)
				{
					pInfo = &(pGrp->info[j]);
					
					ar >> pInfo->bDPI;
					ar >> pInfo->bOpen;
					ar >> pInfo->bPair;
					ar >> pInfo->bCtrl;
					ar >> pInfo->bCtrlObj;
					ar >> pInfo->bIsPhase;
					ar >> pInfo->bPhase;
					ar >> pInfo->bSV;
					ar >> pInfo->bBS;
					ar >> pInfo->bBreak;
					ar >> strTmp;
					//CM3_CP(pInfo->desc,strTmp);
					TcharCopy(pInfo->desc,strTmp);
				}
			}

			//Goֱ����ȡ
			for(i=0;i<CM4_GO_SUB_DT_MAX;++i)
			{
				ar >> strTmp;
				//CM3_CP(m_aGO1DT.info[i].desc,strTmp);
				TcharCopy(m_aGO1DT.info[i].desc,strTmp);
			}

			//GO��λ��д
			ar >>m_aGO1Tap.bTapCtrl[0];
			ar >>m_aGO1Tap.bTapCtrlNum[0];
			ar >>m_aGO1Tap.bTapPhase[0];
			for(i=0;i<CM4_GO_SUB_TAP_NUM;++i)
			{
				ar >>m_aGO1Tap.goInfo[i].bTapCtrl;
				ar >>m_aGO1Tap.goInfo[i].bTapMul;
				ar >>m_aGO1Tap.goInfo[i].bTapPhase;
				ar >>m_aGO1Tap.goInfo[i].bTapSV;
				ar >> strTmp;
				//CM3_CP(m_aGO1Tap.goInfo[i].desc,strTmp);
				TcharCopy(m_aGO1Tap.goInfo[i].desc,strTmp);
			}
		}

		CM3_AR_S_L(ar,m_docIcd.m_CM3.iedName );
		CM3_AR_S_L(ar,m_docIcd.m_CM3.ipA );
		CM3_AR_S_L(ar,m_docIcd.m_CM3.ipB );

		CM3_AR_S_L(ar,m_docIcd.m_CM3.rptScanRate );
		CM3_AR_S_L(ar,m_docIcd.m_CM3.sclXsd );
		
		CM3_AR_S_L(ar,m_docIcd.m_CM3.ap );
		CM3_AR_S_L(ar,m_docIcd.m_CM3.tit );
		CM3_AR_S_L(ar,m_docIcd.m_CM3.qua );
		CM3_AR_S_L(ar,m_docIcd.m_CM3.PSel );
		CM3_AR_S_L(ar,m_docIcd.m_CM3.SSel );
		CM3_AR_S_L(ar,m_docIcd.m_CM3.TSel );

		CM3_AR_S_L(ar,m_docIcd.m_CM3.sboTimOut );

		if (dwVersion==VERSION_0400
			||dwVersion==VERSION_0500||dwVersion==VERSION_0501||dwVersion==VERSION_0502)
		{
			//V4.0���Ӵ洢���̲�ͨ���жϸ������Լ�ת�����̲㱨�ĸ���
			CM3_AR_S_L(ar,m_docIcd.m_CM3.nGoComAlm );//����δʹ��
			CM3_AR_S_L(ar,m_docIcd.m_CM3.nTransProAlm );
			CM3_AR_S_L(ar,m_docIcd.m_CM3.nTransProEvt );

			CM3_AR_S_L(ar,m_docIcd.m_CM3.iedNameGO );
			CM3_AR_S_L(ar,m_docIcd.m_CM3.ap2 );
			CM3_AR_S_L(ar,m_docIcd.m_CM3.Mac);
			CM3_AR_S_L(ar,m_docIcd.m_CM3.Vid );
			CM3_AR_S_L(ar,m_docIcd.m_CM3.AppID );
			CM3_AR_S_L(ar,m_docIcd.m_CM3.Priority );
			CM3_AR_S_L(ar,m_docIcd.m_CM3.MinTime );
			CM3_AR_S_L(ar,m_docIcd.m_CM3.MaxTime );
			ar>>m_docIcd.m_CM3.goPubQ;
			ar>>m_docIcd.m_CM3.goPubT;
			ar>>m_docIcd.m_CM3.goSubVirTermn;
			CM3_AR_S_L(ar,m_docIcd.m_CM3.goSubVermDPS );
			ar>>m_docIcd.m_CM3.multiAPInIED;
			CM3_AR_S_L(ar,m_docIcd.m_CM3.numGoSubBay );
			CM3_AR_S_L(ar,m_docIcd.m_CM3.numGoSubPro );
			CM3_AR_S_L(ar,m_docIcd.m_CM3.numSVSubPro );
			ar>>m_docIcd.m_CM3.multiGOSV;
		}
		else
		{

		}

		if (dwVersion==VERSION_0500||dwVersion==VERSION_0501||dwVersion==VERSION_0502)// ��ȡgoose������Ϣ [2/22/2013]
		{
			ar >> m_aGODO.wRows;
			ar >> m_aGODO.bGrps;
			for(i=0;i<CM4_GO_SUB_CARGRP_NUM;++i)
			{
				pGrp = &(m_aGODO.grp[i]);
				ar >> pGrp->bCpuIdx;
				ar >> pGrp->bGlbIdx;
				ar >> pGrp->bIdx;
				ar >> pGrp->bNum;
				ar >> pGrp->bType;
				for (j=0;j<pGrp->bNum;++j)
				{
					pInfo = &(pGrp->info[j]);
					
					ar >> pInfo->bCpuIdx;
					ar >> pInfo->bGlbIdx;
					ar >> pInfo->bGrpIdx; 
					ar >> pInfo->bIdx;
					ar >> pInfo->wNo;
					
					ar >> pInfo->bDPI;
					ar >> pInfo->bOpen;
					ar >> pInfo->bPair;
					ar >> pInfo->bCtrl;
					ar >> pInfo->bCtrlObj;
					ar >> pInfo->bIsPhase;
					ar >> pInfo->bPhase;
					ar >> pInfo->bSV;
					ar >> pInfo->bBS;
					ar >> pInfo->bBreak;
					ar >> pInfo->bTAP;
					ar >> pInfo->BBak;
					ar >> strTmp;
					//CM3_CP(pInfo->desc,strTmp);
					TcharCopy(pInfo->desc,strTmp);
				}
			}
			ar >> m_bakbak1;
			ar >> m_bakbak2;
			ar >> m_flagZJGOOSEIN;
			ar >> m_flagZJGOOSEOUT;
			ar >> m_flagZJSV;
			ar >> strTmp;
			CM3_CP(m_bakbak3,strTmp);
		}
		if (dwVersion==VERSION_0501||dwVersion==VERSION_0502)// ��ȡ�м�̵��� [8/13/2013]
		{
			ar >> m_aMidRel.wRows;
			ar >> m_aMidRel.bGrps;
			for (int kk=0;kk<3;kk++)
			{
				ar >>m_aMidRel.bCPUUsed[kk];
				ar >>m_aMidRel.bGrpNum[kk];
				ar >>m_aMidRel.wFstPos[kk];
				ar >>m_aMidRel.bCPUNum[kk];
				ar >>m_aMidRel.wFstRow[kk];
				ar >>m_aMidRel.wFstPos[kk];
				ar >>m_aMidRel.bRows[kk];
			}
			for(i=0;i<0x15;++i)
			{
				pGrp = &(m_aMidRel.grp[i]);
				ar >> pGrp->bCpuIdx;
				ar >> pGrp->bGlbIdx;
				ar >> pGrp->bIdx;
				ar >> pGrp->bNum;
				ar >> pGrp->bType;
				for (j=0;j<pGrp->bNum;++j)
				{
					pInfo = &(pGrp->info[j]);
					
					ar >> pInfo->bCpuIdx;
					ar >> pInfo->bGlbIdx;
					ar >> pInfo->bGrpIdx; 
					ar >> pInfo->bIdx;
					ar >> pInfo->wNo;
					
					ar >> pInfo->bDPI;
					ar >> pInfo->bOpen;
					ar >> pInfo->bPair;
					ar >> pInfo->bCtrl;
					ar >> pInfo->bCtrlObj;
					ar >> pInfo->bIsPhase;
					ar >> pInfo->bPhase;
					ar >> pInfo->bSV;
					ar >> pInfo->bBS;
					ar >> pInfo->bBreak;
					ar >> pInfo->bTAP;
					ar >> pInfo->BBak;
					ar >> strTmp;
					//CM3_CP(pInfo->desc,strTmp);
					TcharCopy(pInfo->desc,strTmp);
				}
			}
		}
/*		CM3_AR_S_L(ar,m_docIcd.m_CM3.ldMeas );
		CM3_AR_S_L(ar,m_docIcd.m_CM3.ldCommon );
		CM3_AR_S_L(ar,m_docIcd.m_CM3.ldCtrl );
		
		CM3_AR_S_L(ar,m_docIcd.m_CM3.dsMeas );
		CM3_AR_S_L(ar,m_docIcd.m_CM3.dsCtrl );
		CM3_AR_S_L(ar,m_docIcd.m_CM3.dsEvt );
		CM3_AR_S_L(ar,m_docIcd.m_CM3.dsEn );
		CM3_AR_S_L(ar,m_docIcd.m_CM3.dsAlm );
		CM3_AR_S_L(ar,m_docIcd.m_CM3.dsDOSoe );
		
		CM3_AR_S_L(ar,m_docIcd.m_CM3.rcbMeas );
		CM3_AR_S_L(ar,m_docIcd.m_CM3.rcbCtrl );
		CM3_AR_S_L(ar,m_docIcd.m_CM3.rcbEvt );
		CM3_AR_S_L(ar,m_docIcd.m_CM3.rcbEn );
		CM3_AR_S_L(ar,m_docIcd.m_CM3.rcbAlm );
		CM3_AR_S_L(ar,m_docIcd.m_CM3.rcbDOSoe );

		ar >> m_docIcd.m_CM3.EN.num;
		
		for (i=0;i<m_docIcd.m_CM3.EN.num;++i)
		{
			ar >> m_docIcd.m_CM3.EN.item[i].bNo ;
			CM3_AR_S_L(ar,m_docIcd.m_CM3.EN.item[i].name );
			CM3_AR_S_L(ar,m_docIcd.m_CM3.EN.item[i].desc );
			CM3_AR_S_L(ar,m_docIcd.m_CM3.EN.item[i].descEn );
		}
		
		ar >> m_docIcd.m_CM3.alarm.num;
		
		for (i=0;i<m_docIcd.m_CM3.alarm.num;++i)
		{
			ar >> m_docIcd.m_CM3.alarm.item[i].bNo ;
			CM3_AR_S_L(ar,m_docIcd.m_CM3.alarm.item[i].name );
			CM3_AR_S_L(ar,m_docIcd.m_CM3.alarm.item[i].desc );
			CM3_AR_S_L(ar,m_docIcd.m_CM3.alarm.item[i].descEn );
		}
		
		ar >> m_docIcd.m_CM3.sf38.num;
		
		for (i=0;i<m_docIcd.m_CM3.sf38.num;++i)
		{
			ar >> m_docIcd.m_CM3.sf38.item[i].bNo ;
			CM3_AR_S_L(ar,m_docIcd.m_CM3.sf38.item[i].name );
			CM3_AR_S_L(ar,m_docIcd.m_CM3.sf38.item[i].desc );
			CM3_AR_S_L(ar,m_docIcd.m_CM3.sf38.item[i].descEn );
		}
		
		ar >> m_docIcd.m_CM3.sf37.num;
		
		for (i=0;i<m_docIcd.m_CM3.sf37.num;++i)
		{
			ar >> m_docIcd.m_CM3.sf37.item[i].bNo ;
			CM3_AR_S_L(ar,m_docIcd.m_CM3.sf37.item[i].name );
			CM3_AR_S_L(ar,m_docIcd.m_CM3.sf37.item[i].desc );
			CM3_AR_S_L(ar,m_docIcd.m_CM3.sf37.item[i].descEn );
		}
		
		ar >> m_docIcd.m_CM3.sf37DO.num;
		
		for (i=0;i<m_docIcd.m_CM3.sf37DO.num;++i)
		{
			ar >> m_docIcd.m_CM3.sf37DO.item[i].bNo ;
			CM3_AR_S_L(ar,m_docIcd.m_CM3.sf37DO.item[i].name );
			CM3_AR_S_L(ar,m_docIcd.m_CM3.sf37DO.item[i].desc );
			CM3_AR_S_L(ar,m_docIcd.m_CM3.sf37DO.item[i].descEn );
		}
*/
/*		ar >> m_docIcd.m_CM3.set.num;
		
		for (i=0;i<m_docIcd.m_CM3.set.num;++i)
		{
			ar >> m_docIcd.m_CM3.set.item[i].wNo ;
			ar >> m_docIcd.m_CM3.set.item[i].bType ;
			CM3_AR_S_L(ar,m_docIcd.m_CM3.set.item[i].name );
			CM3_AR_S_L(ar,m_docIcd.m_CM3.set.item[i].desc );
			CM3_AR_S_L(ar,m_docIcd.m_CM3.set.item[i].descEn );
		}
*/
		ar >> m_lockDev.bDevNum;
		CM3_AR_S_L(ar,m_lockDev.bGooseFile );
		
		for (i=0;i<m_lockDev.bDevNum;++i)
		{
			CM3_AR_S_L(ar,m_lockDev.dev[i].iedName );
			ar >> m_lockDev.dev[i].bNum;	
			for (j=0;j<m_lockDev.dev[i].bNum;++j)
			{
				ar >> m_lockDev.dev[i].bNo[j];
				CM3_AR_S_L(ar,m_lockDev.dev[i].diDesc[j] );
			}
		}

#else
		ar.Read(&(m_docIcd.m_header),sizeof(SCL_HEADER));
		ar.Read(&m_aAI,sizeof(CM3_AI_ALL_INFO));
		ar.Read(&m_aDT,sizeof(CM3_DT_ALL_INFO));
		ar.Read(&m_aDI,sizeof(CM3_DI_GRP_ALL_INFO));
		ar.Read(&m_aRC,sizeof(CM3_RC_LIST));

		ar.Read(&(m_docIcd.m_CM3),sizeof(CSI200E_ICD_INFO));
		
#endif
	}
}

CString CAutoModelStrc::GetSAddrMod(int nLD, int nLN)
{
	CString strRet = S_EPT;
	
	strRet.Format(_T("70.%d.%d."),nLD,nLN);
	
	return strRet;
}

CString CAutoModelStrc::GetSAddrBeh(int nLD, int nLN)
{
	CString strRet = S_EPT;
	
	strRet.Format(_T("75.%d.%d."),nLD,nLN);
	
	return strRet;
}

CString CAutoModelStrc::GetSAddrHealth(int nLD, int nLN)
{
	CString strRet = S_EPT;
	
	strRet.Format(_T("80.%d.%d."),nLD,nLN);
	
	return strRet;
}

BOOL CAutoModelStrc::IsTapRegEnable()
{
	return TRUE;
	return (m_aDI.grp[0].bType == 1);
}

BYTE CAutoModelStrc::GetDISetNum()
{
	return 6;
	
	int nNum = m_aDI.bGrps *6;
	if( (m_aDI.bGrps%2) ==1  )
		nNum+=6;

	int nRet=( (nNum%16)!=0 )? 1 : 0 ;

	return (BYTE)(nNum/16+ nRet) ;
}

BYTE CAutoModelStrc::GetDPIGroupNum()
{
	BYTE bRet=0;
	int i;

	for (i=0;i<m_aDI.bGrps;++i)
	{
		if(m_aDI.grp[i].bType==4)
			bRet++;
	}
	
	return bRet;
}

CString CAutoModelStrc::GetSAddrPrgOp(int nIdx, int nSunNo)
{
	CString strRet = S_EPT;
	
	strRet.Format(_T("15.16.%d.%d"),nIdx,nSunNo);
	
	return strRet;
}

void CAutoModelStrc::SetGoConfigDefault(CM3_DI_GRP_ALL_INFO * mGODIGrp,int i,int j,int bCtrlObj)
{
	//v4.20�޸ģ�Goose�����1����ǰ24������Ĭ��˫λ�ã�ǰ8��Ϊ��·��,16��Ϊ��բ,��λ��ǰ
	if (i < 4)//ǰ4�飬24������
	{
		mGODIGrp->grp[i].info[j].bDPIGrp = 0;//���������Ϊ˫λ�ã�����˫λ�����Բ��ɸ���
		mGODIGrp->grp[i].info[j].bDPI = 1;
		mGODIGrp->grp[i].info[j].bBS =1;
		
		if (CM3_DI_IDX_DPI(j))
		{
			mGODIGrp->grp[i].info[j].bPair = 1;							
		}
		else
		{
			mGODIGrp->grp[i].info[j].bOpen = 1;
		}
		
		if(i == 0)
		{						
			mGODIGrp->grp[i].info[j].bBreak = 1;
			if (j < 2)
			{
				mGODIGrp->grp[i].info[j].bCtrl = 1;
				//˫λ�õ���������ң�غ�һ��
				mGODIGrp->grp[i].info[j].bCtrlObj = bCtrlObj;
			}
			else//��·��A�ࡢB�ࡢC��
			{
				
				mGODIGrp->grp[i].info[j].bIsPhase = 1; 
				mGODIGrp->grp[i].info[j].bPhase = j/2;
			}
		}
		else
		{
			mGODIGrp->grp[i].info[j].bCtrl = 1;
			//˫λ�õ���������ң�غ�һ��
			if (CM3_DI_IDX_DPI(j))
			{
				bCtrlObj++;
			}
			mGODIGrp->grp[i].info[j].bCtrlObj = bCtrlObj;
		}
	}

};

