#pragma once
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
 *																			*	
 ****************************************************************************/




#import "c:\Program Files\Common Files\System\ADO\msado15.dll" rename_namespace("ADOCG") rename("EOF", "EndOfFile")

using namespace ADOCG;

#include "icrsint.h"
#include "GuiLib.h" 
//---------------------------------------------------------------------------------------


class GUILIBDLLEXPORT CGuiField
{
protected:
	FieldPtr field;
public:
	CGuiField(void);
	~CGuiField(void);
public:

	FieldPtr GetFieldPtr(){return field;};
	void Attach(FieldPtr mField){field=mField;};
	CString GetName(){ CString Name=(LPCTSTR)field->GetName(); return Name; };
	short   GetType(){return field->GetType();};
	long    GetActualSize(){return field->GetActualSize();};
	long    GetDefinedSize(){return field->GetDefinedSize();};
	long    GetAttributes(){return field->GetAttributes();};
	CString GetOriginalVal(){_variant_t vt=field->GetOriginalValue(); return (CString) vt.bstrVal;};
	BOOL	SetValue(long lVal);
	BOOL	SetValue(float flVal);
	BOOL	SetValue(int nVal);
	BOOL	SetValue(double dbVal);
	BOOL	SetValue(CString szValue);
	BOOL	SetValue(bool blVal);
	BOOL	SetValue(COleDateTime dtVal);
	BOOL	SetValue(_variant_t vt);
	BOOL	GetValue(int& nValue);
	BOOL	GetValue(long& lVal);
	BOOL	GetValue(double& dbVal);
	BOOL	GetValue(CString& strValue);
	BOOL	GetValue(COleDateTime& dtVal);
	BOOL	GetValue(float& flVal);
	BOOL	GetValue(_variant_t& vtVal);
	CString GetUnderlyingValue() { _variant_t vt=field->UnderlyingValue; return (CString)vt.bstrVal;};

};

//--------------------------------------------------------------------------------------
class CGuiCommand;
class CGuiConnection;
class GUILIBDLLEXPORT CGuiRecordSet
{
public:
	CGuiRecordSet(void);
	~CGuiRecordSet(void);

protected:
	_RecordsetPtr m_rs;
	CGuiConnection* m_pCon;
public:
	BOOL Open(_ConnectionPtr ActiveConnection,LPCTSTR Source= _T(""), ADOCG::CursorTypeEnum CursorType = adOpenUnspecified,ADOCG::LockTypeEnum LockType= adLockUnspecified, long Options = -1);
	void MoveFirst();
	void MoveLast();
	void MoveNext();
	void MovePrevious();
	void Cancel();
	void CancelUpdate(); 
	void Close();
	BOOL IsEof();
	BOOL IsBof();
	long GetRecordCount(){ return m_rs->RecordCount;}
	long GetAbsolutePage(){return m_rs->GetAbsolutePage();};
	void SetAbsolutePage(int nPage)	{m_rs->PutAbsolutePage((enum PositionEnum)nPage);};
	long GetPageCount()	{return m_rs->GetPageCount();};
	long GetPageSize()	{return m_rs->GetPageSize();};
	void SetPageSize(int nSize)	{m_rs->PutPageSize(nSize);};
	long GetAbsolutePosition()	{return m_rs->GetAbsolutePosition();};
	void SetAbsolutePosition(int nPosition)	{m_rs->PutAbsolutePosition((enum PositionEnum)nPosition);};
	BOOL Find(LPCTSTR Criteria , long SkipRecords=0 , SearchDirectionEnum SearchDirection= adSearchForward,_variant_t Start=vtMissing);
	long GetNumFields()
		{return m_rs->Fields->GetCount();};
	_RecordsetPtr GetAdoRecordSet(){ return m_rs;};
	//void SetBookmark(){m_rs->Bookmark = m_rs->GetBookmark();};

	CString GetCollect(LPCTSTR lpField);
	
	BOOL GetCollect(LPCTSTR lpField,int& nValue);
	BOOL GetCollect(LPCTSTR lpField,long& lVal);
	BOOL GetCollect(LPCTSTR lpField,double& dbVal);
	BOOL GetCollect(LPCTSTR lpField,CString& strValue);
	BOOL GetCollect(LPCTSTR lpField,COleDateTime& dtVal);
	BOOL GetCollect(LPCTSTR lpField,float& flVal);
	BOOL GetCollect(LPCTSTR lpField,bool& blVal);
	BOOL GetCollect(LPCTSTR lpField,_variant_t& vt);
	BOOL GetCollect(LPCTSTR lpField,COleCurrency& cyVal);
	
	BOOL GetCollect(int nIndex,int& nValue);
	BOOL GetCollect(int nIndex,long& lVal);
	BOOL GetCollect(int nIndex,double& dbVal);
	BOOL GetCollect(int nIndex,CString& strValue);
	BOOL GetCollect(int nIndex,COleDateTime& dtVal);
	BOOL GetCollect(int nIndex,float& flVal);
	BOOL GetCollect(int nIndex,bool& blVal);
	BOOL GetCollect(int nIndex,_variant_t& vt);
	BOOL GetCollect(int nIndex,COleCurrency& cyVal);

	BOOL GetFormatDate(int nIndex,CString& m_szDate, CString Format=_T("%d/%m/%Y")); 
	BOOL GetFormatDate(LPCTSTR lpField,CString& m_szDate, CString Format=_T("%d/%m/%Y"));
	CGuiField GetField(LPCTSTR lpField);
	CGuiField GetField(int Index);
	BOOL SetValue(LPCTSTR lpName,CString szCad);
	BOOL SetValue(LPCTSTR lpName,long lVal);
	BOOL SetValue(LPCTSTR lpName,unsigned char usVal);
	BOOL SetValue(LPCTSTR lpName,short shVal);
	BOOL SetValue(LPCTSTR lpName,float flVal);
	BOOL SetValue(LPCTSTR lpName,double dblVal);
	BOOL SetValue(LPCTSTR lpName,BOOL blVal);
	BOOL SetValue(LPCTSTR lpName,COleDateTime dtVal);
	BOOL SetValue(LPCTSTR lpName,unsigned long ulVal);
	BOOL SetValue(LPCTSTR lpName, COleCurrency cuVal);
	
    BOOL SetFieldValue(LPCTSTR lpName, _variant_t vt);
	BOOL Supports( CursorOptionEnum CursorOptions ) ;
	BOOL FindFirst(LPCTSTR Criteria);
	BOOL FindNext();
	void CGuiRecordSet::Move(long NumRecords , _variant_t Start);
	void Attach(_RecordsetPtr m_prs );
	void CancelBatch(AffectEnum AffectRecords= adAffectAll);
	void SetCacheSize(long lSizeCache){m_rs->put_CacheSize(lSizeCache);};
	void GetCacheSize() {m_rs->GetCacheSize();};
	CGuiRecordSet*  Clone(ADOCG::LockTypeEnum LockType= adLockUnspecified);
	CGuiRecordSet* NextRecordset(long RecordsAffected) ;
	BOOL AddNew(){ return m_rs->AddNew() != S_OK;};
	BOOL Update(){ return m_rs->Update() != S_OK;};
	BOOL Delete();
	BOOL IsOpen();
	BOOL SetFilter(LPCTSTR lpFilter);
	BOOL SetSort(LPCTSTR lpSort);
	ADOCG::EditModeEnum GetEditMode(){return m_rs->EditMode;}; 
protected:
	_variant_t vtPointer;
	LPCTSTR m_Criteria;
};


//------------------------------------------------------------------------------------------------
class GUILIBDLLEXPORT CGuiConnection
{
public:
	CGuiConnection(void);
	~CGuiConnection(void);

protected:
	_ConnectionPtr m_pConn;
public:
	BOOL Open(LPCTSTR ConnectionString,LPCTSTR UID=_T(""),LPCTSTR PWD=_T(""),long Options=-1);
	CGuiRecordSet* Execute(LPCTSTR CommandText,long Options=-1 );
	long BeginTrans();
	void RollbackTrans();
	void CommitTrans();
	void Cancel();
	void Close();
	BOOL IsConnect();
	void SetConnectionTimeout(long ConnectionTimeout);
	void SetConectionString( LPCTSTR ConnectionString);
	long GetConnectionTimeout();
	_ConnectionPtr GetConecction(){return m_pConn;};
	LPCTSTR GetConectionString();
	
};

//----------------------------------------------------------------------------------------------

class GUILIBDLLEXPORT CGuiParameter
{
public:
	CGuiParameter();
	~CGuiParameter();
protected:
	_ParameterPtr pParam;
public:
	void SetAttributes(long Attributes);
	void SetDirection(ADOCG::ParameterDirectionEnum Direction=adParamUnknown);
	void SetName(LPCTSTR szName);
	void SetNumericScale(unsigned char NumericScale);
	void SetPrecision(unsigned char Precision);
	void SetSize(long Size);
	void SetType(ADOCG::DataTypeEnum Type);
	BOOL SetValue(long lVal);
	BOOL SetValue(float flVal);
	BOOL SetValue(int nVal);
	BOOL SetValue(double dbVal);
	BOOL SetValue(CString szValue);
	BOOL SetValue(bool blVal);
	BOOL SetValue(COleDateTime dtVal);
	BOOL SetValue(COleCurrency cyVal);
	BOOL SetValue(_variant_t vt);
	BOOL GetValue(int& nValue);
	BOOL GetValue(long& lVal);
	BOOL GetValue(double& dbVal);
	BOOL GetValue(CString& strValue);
	BOOL GetValue(COleDateTime& dtVal);
	BOOL GetValue(float& flVal);
	BOOL GetValue(_variant_t& vtVal);
	BOOL GetValue(COleCurrency& cyVal);
	BOOL GetFormatDate(CString& m_szDate, CString Format=_T("%d/%m/%Y"));
	_ParameterPtr GetParameter(){return pParam;};
	void Attach(_ParameterPtr param) {pParam=param;};

};

//----------------------------------------------------------------------------------------------

class GUILIBDLLEXPORT CGuiCommand
{
public:
	CGuiCommand();
	~CGuiCommand();
protected:
	_CommandPtr	pCommand;
	CGuiConnection m_pCon;
public:
	void SetActiveConnection(CGuiConnection* pCon);
	void SetActiveConnection(LPCTSTR szconnec);
	void Cancel();
	void SetCommandText(LPCTSTR lpCommand,CommandTypeEnum cmdType=adCmdText);
	void SetCommandTimeout(long CommandTimeout);
	void SetPrepared(BOOL prepared);
	long GetState();
	
	CGuiRecordSet* Execute(VARIANT* param1=NULL,VARIANT* param2=NULL,long Options=-1);
	CGuiParameter* CreateParameter(CString Name ,long Size ,ADOCG::DataTypeEnum Type= adEmpty, 
					ADOCG::ParameterDirectionEnum Direction= adParamInput) ;
	BOOL Append(CGuiParameter* pParam);
	_CommandPtr GetCommand(){return pCommand;};
	void Attach(_CommandPtr	Command) {pCommand=Command;};
	
};
