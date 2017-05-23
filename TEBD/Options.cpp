#include "stdafx.h"

#include "tebd.h"
#include "Options.h"


Options::Options()
	: 
	bigTicksX(2),
	bigTicksY(2),
	smallTicksX(2),
	smallTicksY(2),
	maxTime(4),
	minY(0.46),
	maxY(0.5),
	chi(10),
	JxStart(1),
	JyStart(0),
	JzStart(0),
	BxStart(0),
	BzStart(10),
	JxEvol(1),
	JyEvol(0),
	JzEvol(0),
	BxEvol(0),
	BzEvol(3),
	StartState(0),
	MeasureOp(1)
{
}


Options::~Options()
{
}


double Options::GetDouble(LPCTSTR param, double defval)
{
	double val = defval;

	UINT sz = 0;
	LPBYTE buf = NULL;

	if (theApp.GetProfileBinary(L"options", param, &buf, &sz))
	{
		if (sizeof(double) == sz) val = *((double*)buf);
		delete[] buf;
	}

	return val;
}

void Options::Load()
{
	bigTicksX = theApp.GetProfileInt(L"options", L"bigTicksX", 2);
	bigTicksY = theApp.GetProfileInt(L"options", L"bigTicksY", 5);
	smallTicksX = theApp.GetProfileInt(L"options", L"smallTicksX", 2);
	smallTicksY = theApp.GetProfileInt(L"options", L"smallTicksY", 2);

	maxTime = GetDouble(L"maxTime", 4);
	minY = GetDouble(L"minY", 0.46);
	maxY = GetDouble(L"maxY", 0.5);

	chi = theApp.GetProfileInt(L"options", L"chi", 15);

	JxStart = GetDouble(L"JxStart", 1);
	JyStart = GetDouble(L"JyStart", 0);
	JzStart = GetDouble(L"JzStart", 0);
	BxStart = GetDouble(L"BxStart", 0);
	BzStart = GetDouble(L"BzStart", 10);

	JxEvol = GetDouble(L"JxEvol", 1);
	JyEvol = GetDouble(L"JyEvol", 0);
	JzEvol = GetDouble(L"JzEvol", 0);
	BxEvol = GetDouble(L"BxEvol", 0);
	BzEvol = GetDouble(L"BzEvol", 3);

	StartState = theApp.GetProfileInt(L"options", L"StartState", 0);
	MeasureOp = theApp.GetProfileInt(L"options", L"MeasureOp", 1);
}

void Options::Save()
{
	theApp.WriteProfileInt(L"options", L"bigTicksX", bigTicksX);
	theApp.WriteProfileInt(L"options", L"bigTicksY", bigTicksY);
	theApp.WriteProfileInt(L"options", L"smallTicksX", smallTicksX);
	theApp.WriteProfileInt(L"options", L"smallTicksY", smallTicksY);

	theApp.WriteProfileBinary(L"options", L"maxTime", (LPBYTE)&maxTime, sizeof(double));
	theApp.WriteProfileBinary(L"options", L"minY", (LPBYTE)&minY, sizeof(double));
	theApp.WriteProfileBinary(L"options", L"maxY", (LPBYTE)&maxY, sizeof(double));

	theApp.WriteProfileInt(L"options", L"chi", chi);

	theApp.WriteProfileBinary(L"options", L"JxStart", (LPBYTE)&JxStart, sizeof(double));
	theApp.WriteProfileBinary(L"options", L"JyStart", (LPBYTE)&JyStart, sizeof(double));
	theApp.WriteProfileBinary(L"options", L"JzStart", (LPBYTE)&JzStart, sizeof(double));
	theApp.WriteProfileBinary(L"options", L"BxStart", (LPBYTE)&BxStart, sizeof(double));
	theApp.WriteProfileBinary(L"options", L"BzStart", (LPBYTE)&BzStart, sizeof(double));
	
	theApp.WriteProfileBinary(L"options", L"JxEvol", (LPBYTE)&JxEvol, sizeof(double));
	theApp.WriteProfileBinary(L"options", L"JyEvol", (LPBYTE)&JyEvol, sizeof(double));
	theApp.WriteProfileBinary(L"options", L"JzEvol", (LPBYTE)&JzEvol, sizeof(double));
	theApp.WriteProfileBinary(L"options", L"BxEvol", (LPBYTE)&BxEvol, sizeof(double));
	theApp.WriteProfileBinary(L"options", L"BzEvol", (LPBYTE)&BzEvol, sizeof(double));

	theApp.WriteProfileInt(L"options", L"StartState", StartState);
	theApp.WriteProfileInt(L"options", L"MeasureOp", MeasureOp);
}
