#ifndef _HRRISKASSESMENT_H
#define _HRRISKASSESMENT_H

#include <Windows.h>
const int RiskDetected = 1; // Heart rate risks being found
const int NoRisk = 0;		// No consecutive heart rates above 160

const int Success = 0;     
const int Failure = -1;
const int DllNotFound = -2;		  // Cannot find DLL in specified file directory
const int DllInvalidFormat = -3;  // Unable to find import function in the dll
const int UnknownError = -4;
const int InvalidParameters = -5; 

const int MAX_DATA = 1000;  // The maximum size of the array for loading data 
const int DATE_SIZE = 19;   // The maximum size of a date as a null-terminated string
const int warningHR = 160;  // Heart rate value that is considered a risk

class HRData {
public:
	char date[DATE_SIZE];
	int hr;
};

// Function pointer declarations
typedef int(*cFtnPtr)(int, int);            
typedef int(*cFtnAccessRisk)(HRData*, int); 

// Function declarations
int LoadMeasurements(char* inputFile, HRData data[], int max_size); 
int CallDLL(WCHAR* dllName, HRData data[], int count);
int Sort(HRData data[], int count, cFtnPtr comparePtr);
void QuickSort(HRData data[], int start, int end, cFtnPtr comparePtr);
int Partition(HRData data[], int start, int end, cFtnPtr comparePtr);
int compare(const int a, const int b);
// Used for getting the optimisation results
int TimingBubbleSort(int numbers[], int count, cFtnPtr comparePtr);
void TimingQuickSort(int numbers[], int start, int end, cFtnPtr comparePtr);
int TimingPartition(int numbers[], int start, int end, cFtnPtr comparePtr);
#endif