// GuiAdoTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "GuiAdoTest.h"
#include "GuiAdoTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuiAdoTestApp

BEGIN_MESSAGE_MAP(CGuiAdoTestApp, CWinApp)
	//{{AFX_MSG_MAP(CGuiAdoTestApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiAdoTestApp construction

CGuiAdoTestApp::CGuiAdoTestApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGuiAdoTestApp object

CGuiAdoTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CGuiAdoTestApp initialization

BOOL CGuiAdoTestApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	CString strConnection = _T("Driver={Microsoft Access Driver (*.mdb)};"
						"Dbq=\\guilib1.5\\bin\\config.mdb;Uid=;Pwd=;");              
	m_cn.Open(strConnection);
	if (m_cn.IsConnect()) 
	{
		
		m_rs= m_cn.Execute("SELECT *  FROM JobTable");
		int numFiles=m_rs->GetNumFields();
		while (! m_rs->IsEof())
		{
			//CString time;
			//m_rs->GetFormatDate(7,time);
			AfxMessageBox(m_rs->GetCollect("JobName"));
			m_rs->MoveNext();
		}
		//recorer por campo
		m_rs->MoveFirst();
		for (int i=0; i < numFiles; i++)
		{
			CGuiField field=m_rs->GetField(i);
			//AfxMessageBox(field.GetName());
			CString strValue;
			field.GetValue(strValue);
		//	AfxMessageBox(strValue);
		}

	}


	//---------------------------------------
	/*if (m_rs->FindFirst("Nombre Like \'pet*\'"))
		AfxMessageBox(m_rs->GetCollect("Ename"));
	m_rs->Close();
	*/
	//---------------------------------------------
	/*CGuiCommand* pCommand=new CGuiCommand();
	pCommand->SetActiveConnection(&m_cn);
	pCommand->SetCommandText("Select * from emp");
	CGuiRecordSet* m_rs1=pCommand->Execute();
	AfxMessageBox(m_rs1->GetCollect("Nombre"));
	m_rs1->Close();*/
	//-----------------------------
	/*CGuiRecordSet mr;
	mr.Open(m_cn.GetConecction(),"Select * from emp",adOpenKeyset,adLockOptimistic);
	mr.Delete();
	//--------------------------------
	BOOL res=mr.AddNew();
	mr.SetValue("Nombre","Peter");
	res=mr.Update();
	mr.Close();
	*/
	//--------------------------------------
	//GetEmpName (inEmpno IN NUMBER, outEmpName OUT VARCHAR2)
//	CREATE OR REPLACE procedure DAYPRO.SP_DIAS360_365 (fecha1 in out date, fecha2 in out date, dias in out number,ind in varchar2) IS

/*	_variant_t vt;
	_variant_t vto;
	vto.vt=VT_I2;
	COleDateTime* fecha1= new COleDateTime (2001,12,1,0,0,0);
	COleDateTime* fecha2= new COleDateTime (2002,12,1,0,0,0);
	CString str;
	CGuiCommand* pCommand=new CGuiCommand();
	_variant_t dias;
	dias.vt=VT_R4;

	_variant_t ind;
	ind.vt=VT_BSTR;
	CString szCad="0";
	ind.bstrVal=szCad.AllocSysString();
	pCommand->SetActiveConnection(&m_cn);
	pCommand->SetCommandText("SP_DIAS360_365",adCmdStoredProc);
	CGuiParameter* pParam1=pCommand->CreateParameter(_T("fecha1"),sizeof(DATE),adDBTimeStamp,adParamInputOutput);
	CGuiParameter* pParam2=pCommand->CreateParameter(_T("fecha2"),sizeof(DATE),adDBTimeStamp,adParamInputOutput);
	CGuiParameter* pParam3=pCommand->CreateParameter(_T("dias"),sizeof(long),adInteger,adParamInputOutput);
	CGuiParameter* pParam4=pCommand->CreateParameter(_T("ind"),200,adVarChar,adParamInputOutput);
	pParam1->SetValue(fecha1);
	pParam1->SetValue(fecha2);
	pCommand->Append(pParam1); 
	pCommand->Append(pParam2);
	pCommand->Append(pParam3);
	pCommand->Append(pParam4);
	CGuiRecordSet* m_rs1=pCommand->Execute();
	_variant_t idias;
	long nVal;
	pParam3->GetValue(nVal);
	pParam4->GetValue(szCad);
	int numFiles=m_rs1->GetNumFields();
	m_rs1->MoveFirst();
		for (int i=0; i < numFiles; i++)
		{
			CGuiField field=m_rs1->GetField(i);
			//AfxMessageBox(field.GetName());
			CString strValue;
			field.GetValue(strValue);
		//	AfxMessageBox(strValue);
		}


	CGuiCommand* pCommand=new CGuiCommand();
	_variant_t dias,dias1;

	_variant_t ind;
	ind.vt=VT_BSTR;
	CString szCad="0";
	ind.bstrVal=szCad.AllocSysString();
	pCommand->SetActiveConnection(&m_cn);
	pCommand->SetCommandText("sp_OutputTest",adCmdStoredProc);
	CGuiParameter* pParam1=pCommand->CreateParameter(_T("IN1"),sizeof(int),adInteger,adParamInput);
	CGuiParameter* pParam2=pCommand->CreateParameter(_T("OutInt"),sizeof(int),adInteger,adParamOutput);
	CGuiParameter* pParam3=pCommand->CreateParameter(_T("OutChar"),200,adVarChar,adParamOutput);
	pParam1->SetValue(34);
	//	pCommand->Append(pParam0); 
	pCommand->Append(pParam1); 
	pCommand->Append(pParam2);
	pCommand->Append(pParam3);
	CGuiRecordSet* m_rs1=pCommand->Execute();
	_variant_t idias;
	long nVal;
	pParam3->GetValue(szCad);
	pParam2->GetValue(nVal);
	int numFiles=m_rs1->GetNumFields();
	if (numFiles != 0)
	{
	m_rs1->MoveFirst();
		for (int i=0; i < numFiles; i++)
		{
			CGuiField field=m_rs1->GetField(i);
			//AfxMessageBox(field.GetName());
			CString strValue;
			field.GetValue(strValue);
		//	AfxMessageBox(strValue);
		}
	}
	m_rs1->Close();

*/	//-------------------------------------------------------------------------
	CGuiCommand* pCommand=new CGuiCommand();
	pCommand->SetActiveConnection(&m_cn);
	pCommand->SetCommandText("fcotest",adCmdStoredProc);
	/*
	create or replace procedure fcoTest(fecha1 in date, numero in number,fecha2 out date,resultado out number) IS
	BEGIN
	 fecha2:=fecha1;
	 resultado:=numero*23;
	END fcoTest; 
	*/
	CGuiParameter* pParam1=pCommand->CreateParameter(_T("fecha1"),sizeof(DATE),adDBTimeStamp);
	CGuiParameter* pParam2=pCommand->CreateParameter(_T("numero"),sizeof(long),adNumeric);
	CGuiParameter* pParam3=pCommand->CreateParameter(_T("fecha2"),sizeof(DATE),adDBTimeStamp,adParamOutput);
	CGuiParameter* pParam4=pCommand->CreateParameter(_T("resultado"),sizeof(long),adNumeric,adParamOutput);
	pParam1->SetValue(COleDateTime (2001,12,1,0,0,0));
	//	pCommand->Append(pParam0); 
	pCommand->Append(pParam1); 
	pParam2->SetValue(10);
	pCommand->Append(pParam2);
	
	pCommand->Append(pParam3); 
	pCommand->Append(pParam4);

	CGuiRecordSet* m_rs1=pCommand->Execute();
	CString  fecha1;
	long iVal;
	pParam3->GetFormatDate(fecha1);
	pParam4->GetValue(iVal);
	int numFiles=m_rs1->GetNumFields();
	if (numFiles != 0)
	{
	m_rs1->MoveFirst();
		for (int i=0; i < numFiles; i++)
		{
			CGuiField field=m_rs1->GetField(i);
			//AfxMessageBox(field.GetName());
			CString strValue;
			field.GetValue(strValue);
		//	AfxMessageBox(strValue);
		}
	}
	m_rs1->Close();

	//-------------------------------------------------------------------------

	  CGuiAdoTestDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
