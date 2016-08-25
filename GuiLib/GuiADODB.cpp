/****************************************************************************
 *																			*		 
 *								GuiToolKit  								*	
 *							 (MFC extension)								*			 
 * Created by Francisco Campos G. www.beyondata.com fcampos@beyondata.com	*
 *--------------------------------------------------------------------------*		   
 *																			*
 * This program is free software;so you are free to use it any of your		*
 * applications (Freeware, Shareware, Commercial),but leave this header		*
 * intact.																	*
 *																			*
 * These files are provided "as is" without warranty of any kind.			*
 *																			*
 *			       GuiToolKit is forever FREE CODE !!!!!					*
 *																			*
 *--------------------------------------------------------------------------*
 * Created by: Francisco Campos G.											*
 * Bug Fixes and improvements : (Add your name)								*
 * -Francisco Campos														*				
 * Chenlu Li (wikilee@263.net)																			*	
 ****************************************************************************/



#include "stdafx.h"
#include "guiadodb.h"

//---------------------------------------------------------------------------------------

CString GetError(_com_error &e)
{	
	CString MsgBug;
	_bstr_t Source(e.Source());
	_bstr_t Description(e.Description());
	MsgBug.Format( "Ups!!! \nSource = %s\nDescription= %s\n",(LPCSTR)Source, (LPCSTR)Description );
	#ifdef _DEBUG
		AfxMessageBox( MsgBug, MB_OK | MB_ICONERROR );
	#endif	
	return MsgBug;
}


CString GetTypeVar(_variant_t vt)
{
	switch(vt.vt)
	{
	case VT_EMPTY :
		return _T("VT_EMPTY");
		break;
	case   VT_NULL :
		return _T("VT_NULL");
		break;
	case VT_I2:
		return _T("int");
		break;
	case VT_I4 :
		return _T("long");
		break;
	case  VT_R4 :
		return _T("float");
		break;
	case VT_R8 :
		return _T("double");
		break;
	case VT_CY :
		return _T("currency");
		break;
	case VT_DATE:
		return _T("date");
		break;
	case  VT_BSTR :
		return _T("string");
		break;
	case VT_DISPATCH :
		return _T("dispatch");
		break;
	case  VT_ERROR :
		return _T("error");
		break;
	case VT_BOOL :
		return _T("bool");
		break;
	case VT_VARIANT :
		return _T("variant");
		break;
	case VT_UNKNOWN :
		return _T("unknown");
		break;
	case   VT_DECIMAL :
		return _T("decimal");
		break;
	default:
		return _T("");
	}
}

CGuiConnection::CGuiConnection(void)
{
	::CoInitialize(NULL);
	m_pConn.CreateInstance(__uuidof(Connection));
	
}
CGuiConnection::~CGuiConnection(void)
{
	Close();
	m_pConn.Release();
	m_pConn = NULL;
	
}

BOOL CGuiConnection::Open(LPCTSTR ConnectionString,LPCTSTR UID,LPCTSTR PWD,long Options)
{
 HRESULT re;
 try
	{	
		re = m_pConn->Open(_bstr_t(ConnectionString), _bstr_t(UID), _bstr_t(PWD), Options);
		return re == S_OK;
	}
	catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}
 
}

BOOL CGuiConnection::IsConnect()
{
	return (BOOL) m_pConn->GetState() != adStateClosed;
}



CGuiRecordSet* CGuiConnection::Execute(LPCTSTR CommandText,long Options)
{
	CGuiRecordSet* m_rs= new CGuiRecordSet();
	try{
		m_rs->Open(m_pConn,CommandText,adOpenUnspecified,adLockUnspecified, Options);
	}catch(_com_error &e)
	{
		GetError(e);
		return NULL;
	}
	return m_rs;
}

long CGuiConnection::BeginTrans()
{
	return m_pConn->BeginTrans();
}

void CGuiConnection::RollbackTrans()
{
	m_pConn->RollbackTrans();
}

void CGuiConnection::CommitTrans()
{
	m_pConn->CommitTrans();
}

void CGuiConnection::Cancel()
{
	m_pConn->Cancel();
}

void CGuiConnection::Close()
{
	if (IsConnect())m_pConn->Close();
}

void CGuiConnection::SetConnectionTimeout(long ConnectionTimeout)
{
	m_pConn->ConnectionTimeout=ConnectionTimeout;
}

void CGuiConnection::SetConectionString( LPCTSTR ConnectionString)
{
	m_pConn->ConnectionString=ConnectionString;
}

long CGuiConnection::GetConnectionTimeout()
{
	return m_pConn->ConnectionTimeout;
}

LPCTSTR CGuiConnection::GetConectionString()
{
	return m_pConn->ConnectionString;
}


//***********************************************************************************************
CGuiRecordSet::CGuiRecordSet(void)
{
	::CoInitialize(NULL);
	m_rs.CreateInstance(__uuidof(Recordset));	
	m_Criteria=_T("");
}
CGuiRecordSet::~CGuiRecordSet(void)
{
	Close();
	if (m_rs) m_rs.Release();
	m_rs=NULL;
}
	
void CGuiRecordSet::Attach(_RecordsetPtr m_prs )
{
	m_rs=m_prs;
}

BOOL CGuiRecordSet::Open(_ConnectionPtr ActiveConnection,LPCTSTR Source, CursorTypeEnum CursorType,ADOCG::LockTypeEnum LockType, long Options)
{
	try
	{
		m_rs->Open(Source, _variant_t((IDispatch*)ActiveConnection, TRUE), 
							adOpenStatic, LockType, Options);
	}
	catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}
	return TRUE;
}



BOOL CGuiRecordSet::FindFirst(LPCTSTR Criteria)
{
	MoveFirst();
   	return Find(Criteria,0,adSearchForward,"");
}

void CGuiRecordSet::Move(long NumRecords , _variant_t Start)
{
	m_rs->Move(NumRecords,vtMissing);
}

BOOL CGuiRecordSet::FindNext()
{
	return Find(m_Criteria,1,adSearchForward,vtPointer);
}


BOOL CGuiRecordSet::Find(LPCTSTR Criteria , long SkipRecords , 
						 SearchDirectionEnum SearchDirection,_variant_t Start)
{
	CString szCri=Criteria;

	if (!szCri.IsEmpty())
		m_Criteria=Criteria;
	else
		return FALSE;
	try{
		m_rs->Find(_bstr_t(Criteria),SkipRecords,SearchDirection,Start);
		if (SearchDirection ==adSearchForward)
		{
			if (!IsEof())
			{
				vtPointer= m_rs->Bookmark;
				return TRUE;
			}
		}else if (SearchDirection ==adSearchBackward)
		{
			if (!IsBof())
			{
				vtPointer= m_rs->Bookmark;
				return TRUE;
			}
		}else return FALSE;

	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}
return FALSE;
}



BOOL CGuiRecordSet::SetValue(LPCTSTR lpName,CString szCad)
{
	_variant_t vt;
	if(!szCad.IsEmpty())
	{
		vt.vt = VT_BSTR;
		vt.bstrVal = szCad.AllocSysString();
	}

	return SetFieldValue(lpName, vt);
}

BOOL CGuiRecordSet::SetValue(LPCTSTR lpName,long lVal)
{
	_variant_t vt;
	vt.lVal=lVal;
	vt.vt=VT_I4;	
	return SetFieldValue(lpName, vt);
}

BOOL CGuiRecordSet::SetValue(LPCTSTR lpName,unsigned char usVal)
{
	_variant_t vt;
	vt.bVal=usVal;
	vt.vt=VT_UI1;	
	return SetFieldValue(lpName, vt);
}

BOOL CGuiRecordSet::SetValue(LPCTSTR lpName,short shVal)
{
	_variant_t vt;
	vt.iVal=shVal;
	vt.vt=VT_I2;	
	return SetFieldValue(lpName, vt);
}

BOOL CGuiRecordSet::SetValue(LPCTSTR lpName,float flVal)
{
	_variant_t vt;
	vt.fltVal=flVal;
	vt.vt=VT_R4;	
	return SetFieldValue(lpName, vt);
}

BOOL CGuiRecordSet::SetValue(LPCTSTR lpName,double dblVal)
{
	_variant_t vt;
	vt.dblVal=dblVal;
	vt.vt=VT_R8;	
	return SetFieldValue(lpName, vt);
}

BOOL CGuiRecordSet::SetValue(LPCTSTR lpName,BOOL blVal)
{
	_variant_t vt;
	vt.boolVal=blVal;
	vt.vt=VT_BOOL;	
	return SetFieldValue(lpName, vt);
}

BOOL CGuiRecordSet::SetValue(LPCTSTR lpName,COleDateTime dtVal)
{
	_variant_t vt;
	vt.date=dtVal;
	vt.vt=VT_DATE;	
	return SetFieldValue(lpName, vt);
}

BOOL CGuiRecordSet::SetValue(LPCTSTR lpName,unsigned long ulVal)
{
	_variant_t vt;
	vt.vt = VT_UI4;
	vt.ulVal = ulVal;
	return SetFieldValue(lpName, vt);
}

BOOL CGuiRecordSet::SetValue(LPCTSTR lpName, COleCurrency cuVal)
{
	_variant_t vt;
	vt.vt = VT_CY;
	vt.cyVal = cuVal.m_cur;
	if(cuVal.m_status == COleCurrency::invalid)
		return FALSE;
	return SetFieldValue(lpName, vt);
}

BOOL CGuiRecordSet::SetFieldValue(LPCTSTR lpName, _variant_t vtField)
{
	try
	{
		m_rs->Fields->GetItem(lpName)->Value = vtField; 
		return TRUE;
	}
	catch(_com_error &e)
	{
		GetError(e);
		return FALSE;	
	}
}


CString CGuiRecordSet::GetCollect(LPCTSTR lpField)
{
	try{
	_variant_t vt = m_rs->Fields->GetItem(lpField)->Value;
	 return (CString) vt.bstrVal;
	}
	catch(_com_error &e)
	{
		GetError(e);
		return _T("");
	}
 
}

BOOL CGuiRecordSet::GetCollect(LPCTSTR lpField,int& nValue)
{
	_variant_t vt;
	try
	{
		vt = m_rs->Fields->GetItem(lpField)->Value;
		if (vt.vt==VT_I2)
		{
			nValue=vt.intVal;
			return TRUE;
		}else if (vt.vt==VT_BOOL)
		{
			nValue=vt.boolVal;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}
}
BOOL CGuiRecordSet::GetCollect(LPCTSTR lpField,long& lVal)
{
	_variant_t vt;
	try
	{
		vt = m_rs->Fields->GetItem(lpField)->Value;
		if (vt.vt==VT_I4)
		{
			lVal=vt.lVal;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}

}
BOOL CGuiRecordSet::GetCollect(LPCTSTR lpField,double& dbVal)
{
	_variant_t vt;
	try
	{
		vt = m_rs->Fields->GetItem(lpField)->Value;
		if (vt.vt==VT_R8)
		{
			dbVal=vt.dblVal;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}
}
BOOL CGuiRecordSet::GetCollect(LPCTSTR lpField,CString& strValue)
{
	_variant_t vt;
	try
	{	
		vt = m_rs->Fields->GetItem(lpField)->Value;
		if (vt.vt==VT_BSTR)
		{
			strValue=vt.bstrVal;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}
}


BOOL CGuiRecordSet::GetCollect(LPCTSTR lpField,COleCurrency& cyVal)
{
	_variant_t vt;
	vt = m_rs->Fields->GetItem(lpField)->Value;
	
	try
	{
		if (vt.vt==VT_CY)
		{
			cyVal.m_cur=vt.cyVal;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}

}

BOOL CGuiRecordSet::GetCollect(LPCTSTR lpField,COleDateTime& dtVal)
{
	_variant_t vt;
	try
	{
		vt = m_rs->Fields->GetItem(lpField)->Value;
		if (vt.vt==VT_DATE)
		{
			dtVal=vt.date;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}
}
BOOL CGuiRecordSet::GetCollect(LPCTSTR lpField,float& flVal)
{
	_variant_t vt;
	try
	{
		vt = m_rs->Fields->GetItem(lpField)->Value;
		if (vt.vt==VT_R4)
		{
			flVal=vt.fltVal;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}
}

BOOL CGuiRecordSet::GetCollect(LPCTSTR lpField,_variant_t& vt)
{
	try
	{
		vt = m_rs->Fields->GetItem(lpField)->Value;
		return TRUE;
	}
	catch(_com_error& e)
	{
		GetError(e);
		return FALSE;
	}
}
	
BOOL CGuiRecordSet::GetCollect(int nIndex,int& nValue)
{
	_variant_t vt;
	_variant_t vtn;
	vtn.vt = VT_I2;
	try
	{
		vtn.iVal = nIndex;
		vt = m_rs->Fields->GetItem(vtn)->Value;
		if (vt.vt==VT_I2)
		{
			nValue=vt.intVal;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}

}

BOOL CGuiRecordSet::GetCollect(int nIndex,long& lVal)
{
	_variant_t vt;
	_variant_t vtn;
	vtn.vt = VT_I2;
	try
	{
		vtn.iVal = nIndex;
		vt = m_rs->Fields->GetItem(vtn)->Value;
		if (vt.vt==VT_I4)
		{
			lVal=vt.lVal;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}

}

BOOL CGuiRecordSet::GetCollect(int nIndex,double& dbVal)
{
	_variant_t vt;
	_variant_t vtn;
	vtn.vt = VT_I2;
	try
	{
		vtn.iVal = nIndex;
		vt = m_rs->Fields->GetItem(vtn)->Value;
		if (vt.vt==VT_R8)
		{
			dbVal=vt.dblVal;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}
}

BOOL CGuiRecordSet::GetCollect(int nIndex,CString& strValue)
{
	_variant_t vt;
	_variant_t vtn;
	vtn.vt = VT_I2;
	try
	{	
		vtn.iVal = nIndex;
		vt = m_rs->Fields->GetItem(vtn)->Value;
		if (vt.vt==VT_BSTR)
		{
			strValue=vt.bstrVal;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}
}

BOOL CGuiRecordSet::GetCollect(int nIndex,COleCurrency& cyVal)
{
	_variant_t vt;
	_variant_t vtn;
	vtn.vt = VT_CY;
	try
	{
		vtn.iVal =nIndex;
		vt	= m_rs->Fields->GetItem(vtn)->Value;
		if (vt.vt==VT_CY)
		{
			cyVal.m_cur=vt.cyVal;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}

}

BOOL CGuiRecordSet::GetCollect(int nIndex,COleDateTime& dtVal)
{
	_variant_t vt;
	_variant_t vtn;
	vtn.vt = VT_I2;
	try
	{
		vtn.iVal = nIndex;
		vt = m_rs->Fields->GetItem(vtn)->Value;
		if (vt.vt==VT_DATE)
		{
			dtVal=vt.date;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}
		
}

BOOL CGuiRecordSet::GetFormatDate(LPCTSTR lpField,CString& m_szDate, CString Format)
{
	COleDateTime time;
	if (!GetCollect(lpField,time)) return FALSE;
	CTime ct(time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond()); 
	m_szDate =ct.Format(Format);
	return TRUE;
}

BOOL CGuiRecordSet::GetFormatDate(int nIndex,CString& m_szDate, CString Format)
{
	COleDateTime time;
	if (!GetCollect(nIndex,time)) return FALSE;
	CTime ct(time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond()); 
	m_szDate =ct.Format(Format);
	return TRUE;
}

BOOL CGuiRecordSet::GetCollect(int nIndex,float& flVal)
{
	_variant_t vt;
	_variant_t vtn;
	vtn.vt = VT_I2;
	try
	{
		vtn.iVal = nIndex;
		vt = m_rs->Fields->GetItem(vtn)->Value;
		if (vt.vt==VT_R4)
		{
			flVal=vt.fltVal;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}

}



BOOL CGuiRecordSet::GetCollect(int nIndex,_variant_t& vt)
{

	_variant_t vtn;
	vtn.vt = VT_I2;
	try
	{
		vtn.iVal = nIndex;
		vt = m_rs->Fields->GetItem(vtn)->Value;
		return TRUE;
	}
	catch(_com_error& e)
	{
		GetError(e);
		return FALSE;
	}
}
	



BOOL CGuiRecordSet::SetFilter(LPCTSTR lpFilter)
{
	if (!IsOpen()) return FALSE;
	try
	{
		m_rs->PutFilter(lpFilter);
		return TRUE;
	}
	catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}
}

BOOL CGuiRecordSet::SetSort(LPCTSTR lpSort)
{
	if (!IsOpen()) return FALSE;
	try
	{
		m_rs->PutSort(lpSort);
		return TRUE;
	}
	catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}
}
	

BOOL CGuiRecordSet::IsOpen()
{
	if(m_rs)
		return m_rs-> GetState() != adStateClosed;
	return FALSE;
}

void CGuiRecordSet::Close()
{
	if(IsOpen())
		m_rs->Close();	
	
}


void CGuiRecordSet::MoveFirst()
{
	m_rs->MoveFirst();
}

void CGuiRecordSet::MoveLast()
{
	m_rs->MoveLast();
}

void CGuiRecordSet::MoveNext()
{
	m_rs->MoveNext();
}

void CGuiRecordSet::MovePrevious()
{
	m_rs->MovePrevious();
}

void CGuiRecordSet::Cancel()
{
   m_rs->Cancel();	
}

void CGuiRecordSet::CancelUpdate()
{
  m_rs->CancelUpdate();	
}

BOOL CGuiRecordSet::Delete()
{
	try{
		if(m_rs->Delete(adAffectCurrent)== S_OK)
			if(m_rs->Update() ==S_OK)
			return TRUE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}
	return FALSE;
}


BOOL CGuiRecordSet::IsEof()
{
	return (BOOL)m_rs->EndOfFile;
}
BOOL CGuiRecordSet::IsBof()
{
	return (BOOL)m_rs->BOF;
}

BOOL CGuiRecordSet::Supports( CursorOptionEnum CursorOptions ) 
{
  return (BOOL)m_rs->Supports(CursorOptions);
}

void CGuiRecordSet::CancelBatch(AffectEnum AffectRecords)
{
  m_rs->CancelBatch(AffectRecords);
}


CGuiField CGuiRecordSet::GetField(LPCTSTR lpField)
{
	FieldPtr pField = m_rs->Fields->GetItem(lpField);
	CGuiField Field;
	Field.Attach(pField);
	return Field;
}

CGuiField CGuiRecordSet::GetField(int Index)
{
	_variant_t vtIndex;
	vtIndex.vt = VT_I2;
	vtIndex.iVal = Index;
	FieldPtr pField = m_rs->Fields->GetItem(vtIndex);
	CGuiField Field;
	Field.Attach(pField);
	return Field;
}

CGuiRecordSet*  CGuiRecordSet::Clone(ADOCG::LockTypeEnum LockType)
{
	_RecordsetPtr m_rs1=m_rs->Clone(LockType);
	CGuiRecordSet* m_pRs= new CGuiRecordSet();
	m_pRs->Attach(m_rs1);
	return m_pRs; 
}

CGuiRecordSet* CGuiRecordSet::NextRecordset(long RecordsAffected) 
{
	_RecordsetPtr m_rs1=m_rs->NextRecordset((VARIANT*)RecordsAffected);
	CGuiRecordSet* m_pRs= new CGuiRecordSet();
	m_pRs->Attach(m_rs1);
	return m_pRs; 
}

//***********************************************************************************************************
CGuiField::CGuiField(void)
{
}
CGuiField::~CGuiField(void)
{
}
BOOL CGuiField::SetValue(long lVal)
{
	_variant_t vt;
	vt.lVal=lVal;
	vt.vt=VT_I4;	
	try
	{
		field->Value=vt;
		return TRUE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}

}



BOOL CGuiField::SetValue(float flVal)
{
	_variant_t vt;
	vt.fltVal=flVal;
	vt.vt=VT_R4;	
	try
	{
		field->Value=vt;
		return TRUE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}
}


BOOL CGuiField::SetValue(int nVal)
{
	_variant_t vt;
	vt.intVal=nVal;
	vt.vt=VT_I2;	
	try
	{
		field->Value=vt;
		return TRUE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}

	
}

BOOL CGuiField::SetValue(double dbVal)
{
	_variant_t vt;
	vt.dblVal=dbVal;
	vt.vt=VT_R8;	
	
	try
	{
		field->Value=vt;
		return TRUE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}

}

BOOL CGuiField::SetValue(CString szCad)
{
	_variant_t vt;
	if(!szCad.IsEmpty())
	{
		vt.vt = VT_BSTR;
		vt.bstrVal = szCad.AllocSysString();
	}
	try
	{
		field->Value=vt;
		return TRUE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}


}


BOOL CGuiField::SetValue(bool blVal)
{
	_variant_t vt;
	vt.boolVal=blVal;
	vt.vt=VT_BOOL;	
	try
	{
		field->Value=vt;
		return TRUE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}
}


BOOL CGuiField::SetValue(COleDateTime dtVal)
{
	_variant_t vt;
	vt.date=dtVal;
	vt.vt=VT_DATE;	
	try
	{
		field->Value=vt;
		return TRUE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}

}

BOOL CGuiField::SetValue(_variant_t vt)
{
	try
	{
		field->Value=vt;
		return TRUE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}

}

BOOL CGuiField::GetValue(int& nVal)
{
	_variant_t vt;
	vt = field->Value;
	try
	{
		if (vt.vt==VT_I2)
		{
			nVal=vt.intVal;
			return TRUE;
		}else if (vt.vt==VT_BOOL)
		{
			nVal=vt.boolVal;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}

}

BOOL CGuiField::GetValue(long& lVal)
{
	_variant_t vt;
	vt = field->Value;
	try
	{
		if (vt.vt==VT_I4)
		{
			lVal=vt.lVal;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}

}

BOOL CGuiField::GetValue(double& dbVal)
{
	_variant_t vt;
	vt = field->Value;
	try
	{
		if (vt.vt==VT_R8)
		{
			dbVal=vt.dblVal;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}
}

BOOL CGuiField::GetValue(CString& strValue)
{
	_variant_t vt;
	vt =field->Value;
	
	try
	{
		if (vt.vt==VT_BSTR)
		{
			strValue=vt.bstrVal;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}
}

BOOL CGuiField::GetValue(COleDateTime& dtVal)
{
	_variant_t vt;
	vt = field->Value;
	try
	{
		if (vt.vt==VT_DATE)
		{
			dtVal=vt.date;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}
		
}

BOOL CGuiField::GetValue(float& flVal)
{
	_variant_t vt;
	vt = field->Value;
	try
	{
		if (vt.vt==VT_R4)
		{
			flVal=vt.fltVal;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}

}



BOOL CGuiField::GetValue(_variant_t& vt)
{
	try
	{
		//_variant_t vt = field->Value;
		vt = field->Value;
		return TRUE;
	}
	catch(_com_error& e)
	{
		GetError(e);
		return FALSE;
	}
}
	

//***********************************************************************************************************

CGuiParameter::CGuiParameter()
{
	::CoInitialize(NULL);
	pParam.CreateInstance(__uuidof(Parameter));	
}

CGuiParameter::~CGuiParameter()
{
	pParam->Release();
	pParam=NULL;
}


void CGuiParameter::SetAttributes(long Attributes)
{
	pParam->PutAttributes(Attributes);
}

void CGuiParameter::SetDirection(ADOCG::ParameterDirectionEnum Direction)
{
	pParam->PutDirection(Direction);
}

void CGuiParameter::SetName(LPCTSTR szName)
{
	CString mszname=szName;
	pParam->Name=mszname.AllocSysString();
	
}

void CGuiParameter::SetNumericScale(unsigned char NumericScale)
{
	pParam->PutNumericScale(NumericScale);
}

void CGuiParameter::SetPrecision(unsigned char Precision)
{
	pParam->PutPrecision(Precision);
}

void CGuiParameter::SetSize(long Size)
{
	pParam->PutSize(Size);
}

void CGuiParameter::SetType(ADOCG::DataTypeEnum Type)
{
	pParam->PutType(Type);
}

BOOL CGuiParameter::SetValue(long lVal)
{
	_variant_t vt;
	vt.lVal=lVal;
	vt.vt=VT_I4;	
	try
	{
		pParam->Value=vt;
		return TRUE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}

}



BOOL CGuiParameter::SetValue(float flVal)
{
	_variant_t vt;
	vt.fltVal=flVal;
	vt.vt=VT_R4;	
	try
	{
		pParam->Value=vt;
		return TRUE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}
}


BOOL CGuiParameter::SetValue(int nVal)
{
	_variant_t vt;
	vt.intVal=nVal;
	vt.vt=VT_I2;	
	try
	{
		pParam->Value=vt;
		return TRUE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}

	
}

BOOL CGuiParameter::SetValue(double dbVal)
{
	_variant_t vt;
	vt.dblVal=dbVal;
	vt.vt=VT_R8;	
	
	try
	{
		pParam->Value=vt;
		return TRUE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}

}

BOOL CGuiParameter::SetValue(CString szCad)
{
	_variant_t vt;
	if(!szCad.IsEmpty())
	{
		vt.vt = VT_BSTR;
		vt.bstrVal = szCad.AllocSysString();
	}
	try
	{
		pParam->Value=vt;
		return TRUE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}


}


BOOL CGuiParameter::SetValue(bool blVal)
{
	_variant_t vt;
	vt.boolVal=blVal;
	vt.vt=VT_BOOL;	
	try
	{
		pParam->Value=vt;
		return TRUE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}
}


BOOL CGuiParameter::SetValue(COleDateTime dtVal)
{
	_variant_t vt;
	vt.date=dtVal;
	vt.vt=VT_DATE;	
	try
	{
		pParam->Value=vt;
		return TRUE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}

}

BOOL CGuiParameter::SetValue(_variant_t vt)
{
	try
	{
		pParam->Value=vt;
		return TRUE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}

}

BOOL CGuiParameter::GetValue(int& nVal)
{
	_variant_t vt;
	vt = pParam->Value;
	try
	{
		if (vt.vt==VT_I2)
		{
			nVal=vt.intVal;
			return TRUE;
		}else if (vt.vt==VT_BOOL)
		{
			nVal=vt.boolVal;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}

}

BOOL CGuiParameter::GetValue(long& lVal)
{
	_variant_t vt;
	vt = pParam->Value;
	try
	{
		if (vt.vt==VT_I4)
		{
			lVal=vt.lVal;
			return TRUE;
		}if (vt.vt==VT_BSTR)
		{
			CString cad=vt.bstrVal;
			lVal=atol(cad);
			return TRUE;
		}
		else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}

}

BOOL CGuiParameter::SetValue(COleCurrency cyVal)
{
	_variant_t vt;
	vt.cyVal=cyVal.m_cur;
	vt.vt=VT_CY;	
	try
	{
		pParam->Value=vt;
		return TRUE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}

}

BOOL CGuiParameter::GetValue(double& dbVal)
{
	_variant_t vt;
	vt = pParam->Value;
	try
	{
		if (vt.vt==VT_R8)
		{
			dbVal=vt.dblVal;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}
}

BOOL CGuiParameter::GetValue(CString& strValue)
{
	_variant_t vt;
	vt =pParam->Value;
	
	try
	{
		if (vt.vt==VT_BSTR)
		{
			strValue=vt.bstrVal;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}
}

BOOL CGuiParameter::GetValue(COleDateTime& dtVal)
{
	_variant_t vt;
	vt = pParam->Value;
	try
	{
		if (vt.vt==VT_DATE)
		{
			dtVal=vt.date;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}
		
}

BOOL CGuiParameter::GetValue(COleCurrency& cyVal)
{
	_variant_t vt;
	vt = pParam->Value;
	
	try
	{
		if (vt.vt==VT_CY)
		{
			cyVal.m_cur=vt.cyVal;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}

}


BOOL CGuiParameter::GetFormatDate(CString& m_szDate, CString Format)
{
	COleDateTime time;
	if (!GetValue(time)) return FALSE;
	CTime ct(time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond()); 
	m_szDate =ct.Format(Format);
	return TRUE;
}



BOOL CGuiParameter::GetValue(float& flVal)
{
	_variant_t vt;
	vt = pParam->Value;
	try
	{
		if (vt.vt==VT_R4)
		{
			flVal=vt.fltVal;
			return TRUE;
		}else return FALSE;
	}catch(_com_error &e)
	{
		GetError(e);
		return FALSE;
	}

}



BOOL CGuiParameter::GetValue(_variant_t& vt)
{
	try
	{
		_variant_t vt = pParam->Value;
		return TRUE;
	}
	catch(_com_error& e)
	{
		GetError(e);
		return FALSE;
	}
}
	

//----------------------------------------------------------------------------------------------

CGuiCommand::CGuiCommand()
{
	::CoInitialize(NULL);
	pCommand.CreateInstance(__uuidof(Command));	

}

CGuiCommand::~CGuiCommand()
{
	Cancel();
	pCommand->Release();
	pCommand=NULL;
}


void CGuiCommand::SetActiveConnection(LPCTSTR szconnec)
{
	m_pCon.Open(szconnec);
	ASSERT( m_pCon.IsConnect());
	SetActiveConnection(&m_pCon);
}

void CGuiCommand::SetActiveConnection(CGuiConnection* pCon)
{
	ASSERT(pCon->IsConnect());
	pCommand->ActiveConnection=pCon->GetConecction();
}

void CGuiCommand::Cancel()
{
	pCommand->Cancel();
} 

void CGuiCommand::SetCommandText(LPCTSTR lpCommand,CommandTypeEnum cmdType)
{
	CString szCommand=lpCommand;
	pCommand->CommandText=szCommand.AllocSysString();
	pCommand->PutCommandType(cmdType);
}

void CGuiCommand::SetCommandTimeout(long CommandTimeout)
{
	pCommand->PutCommandTimeout(CommandTimeout);
}

void CGuiCommand::SetPrepared(BOOL prepared)
{
	pCommand->PutPrepared((BOOL) prepared);
}

long CGuiCommand::GetState()
{
	return pCommand->GetState();
}

CGuiRecordSet* CGuiCommand::Execute(VARIANT* param1,VARIANT* param2,long Options)
{
	try
	{
		_RecordsetPtr m_rs = pCommand->Execute(NULL, NULL, Options);
		CGuiRecordSet* m_prs= new CGuiRecordSet();
		m_prs->Attach(m_rs);
		return m_prs;
	}
	catch(_com_error &e)
	{
		GetError(e);
		return NULL;
	}
	
}

CGuiParameter* CGuiCommand::CreateParameter(CString Name ,long Size ,
											ADOCG::DataTypeEnum Type, 
											ADOCG::ParameterDirectionEnum Direction)
{
	_ParameterPtr param=pCommand->CreateParameter(Name.AllocSysString(), Type,Direction, Size);
		
	CGuiParameter* pParam=new CGuiParameter();
	pParam->Attach(param);
	return pParam;
}
	
BOOL CGuiCommand::Append(CGuiParameter* pParam)
{
	try
	{
		pCommand->Parameters->Append(pParam->GetParameter());
		return TRUE;
	}
	catch(_com_error& e)
	{
		GetError(e);
		return FALSE;
	}

}


