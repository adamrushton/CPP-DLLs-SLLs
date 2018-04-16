// DLL.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include "Dll.h"
#include <iostream>

using namespace std;

int AssessRisk(HRData data[], int count)
{
	try
	{
		// If none loaded
		if (count <= 0) return InvalidParameters;

		for (int i = 0; i < count; i += 3)
		{
			if (data[i].hr > warningHR)
				if (data[i + 1].hr > warningHR)
					if (data[i + 2].hr > warningHR)
						return RiskDetected;
		}
	}
	catch (exception e)
	{
		return UnknownError;
	}


	return NoRisk;
}

