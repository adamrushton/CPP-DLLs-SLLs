#include "stdafx.h"
#include "HRRiskAssessment.h"
#include <iostream>
#include <ctime>

using namespace std;

// Generating a random number between 50 and 180.
int Random()
{
	return rand() % (180 - 50 + 1) + 50;
}

int _tmain(int argc, _TCHAR* argv[])
{
	HRData data[MAX_DATA];

	// Change "Debug" to "Release" for release mode
	// Location in my project:
	 char* inputFile = "..\\Debug\\HR.csv";
	// Location for submitting just the DLL, LIB and EXE
	//char* inputFile = "HR.csv"; 
	int count = LoadMeasurements(inputFile, data, MAX_DATA);
	cout << "Measurements loaded:" << count << endl;

	// Uncomment and comment the one you want the listing to use.
	QuickSort(data, 0, count-1, &compare); // Sort the array using quick sort algorithm
	//Sort(data, count, &compare);         // Sort the array using bubble sort algorithm

	for (int i = 0; i < count; i++)
	{	// Outputting the heart rate date
		cout << "Heart Rate: " << data[i].hr << " Date: " << data[i].date << "\n";
	}

	if (count > 0) 
	{
		// Location in my project:
		 int status = CallDLL(L"../Debug/DLL.dll", data, count);
		// Location for submitting just the DLL, LIB and EXE
		//int status = CallDLL(L"DLL.dll", data, count);
		switch (status) 
		{
		case RiskDetected:     cout << "Risk detected!" << endl;
			break;
		case NoRisk:           cout << "No Risk" << endl;
			break;
		case UnknownError:     cout << "Unknown Error or Error inside DLL" << endl;
			break;
		case DllInvalidFormat: cout << "Invalid function parameters" << endl;
			break;
		case DllNotFound:      cout << "DLL Not Found" << endl;
			break;
		}
	}
	// Generating random numbers between 50 and 180
	// Uncomment the below sections to use.

	//const int totalNumbers = 5000;
	//int numbers[totalNumbers];
	// 
	//for (int i = 0; i < totalNumbers; i++)
	//{
	//	numbers[i] = Random();
	//}

	//// Element timing
	//clock_t start, end;
	//start = clock();
	////TimingBubbleSort(numbers, totalNumbers, &compare);
	//TimingQuickSort(numbers, 0, totalNumbers-1, &compare);
	//end = clock();
	//cout << "Time (MS): " << end - start << endl;


	//for (int i = 0; i < totalNumbers; i++)
	//{
	//	cout << numbers[i] << " ";
	//}
	// cout << endl;

	system("pause");
	return Success;
}