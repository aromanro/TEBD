#pragma once
class Options
{
public:
	Options();
	~Options();


	int bigTicksX;
	int bigTicksY;
	int smallTicksX;
	int smallTicksY;

	double maxTime;

	double maxY;
	double minY;

	int chi;

	double JxStart;
	double JyStart;
	double JzStart;

	double BxStart;
	double BzStart;


	double JxEvol;
	double JyEvol;
	double JzEvol;

	double BxEvol;
	double BzEvol;

	int StartState; // 0 - use imaginary time to calculate, 1 - Neel state, 2....

	int MeasureOp; // 0 - sx, 1 - sz, 2...

	void Load();
	void Save();
protected:
	static double GetDouble(LPCTSTR param, double defval);
};

