#ifndef _DLL_H
#define _DLL_H

#include "../ConsoleApplication1/HRRiskAssessment.h"

extern "C" __declspec(dllexport) int AssessRisk(HRData data[], int count);

#endif
