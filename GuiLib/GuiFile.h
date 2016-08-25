/****************************************************************************
 *																			*		 
 *								GuiToolKit  								*	
 *                              (MFC extension)								*			 
 * Created by Francisco Campos G. www.beyondata.com fcampos@beyondata.com	*
 *--------------------------------------------------------------------------*		   
 *																			*
 * This program is free software; so you are free to use it any of your		*
 * applications(Freeware, Shareware, Commercial), but leave this header		*
 * intact.																	*
 *																			*
 * These files are provided "as is" without warranty of any kind.			*
 *																			*
 *			       GuiToolKit is forever FREE CODE !!!!!					*
 *																			*
 *--------------------------------------------------------------------------*
 * Created by: Francisco Campos G.											*
 * Bug Fixes and improvements :(Add your name)								*
 * -Francisco Campos														*				
 *																			*	
 ****************************************************************************/

#if !defined(AFX_GUIFILE_H__314F6DAD_DA53_4E03_B656_E5DF4D4155E9__INCLUDED_)
#define AFX_GUIFILE_H__314F6DAD_DA53_4E03_B656_E5DF4D4155E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class GUILIBDLLEXPORT  CGuiFile  
{
public:
	CGuiFile();
	virtual ~CGuiFile();
	
	
	enum TypeSeek  
	{
		FSEEK_CUR = 1,
		FSEEK_END = 2,
		FSEEK_SET = 0
	};

public:
	char* ReadLine();
	BOOL  WriteLine(char *cadena);
	BOOL  IsOpen();
	BOOL  Open(char *szFile, char* mode);
	BOOL  Seek(long offset, TypeSeek tps);
	char* Read(int Size);
	BOOL  Eof();
	void Close();

protected: 
	FILE* fp;
};

#endif // !defined(AFX_GUIFILE_H__314F6DAD_DA53_4E03_B656_E5DF4D4155E9__INCLUDED_)

