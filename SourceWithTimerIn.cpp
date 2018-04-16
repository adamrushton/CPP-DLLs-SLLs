#include "stdafx.h"
#include "HRRiskAssessment.h"
#include <iostream>
#include <ctime>

using namespace std;

int Random()
{
	return rand() % (180 - 50 + 1) + 50;
}

int Sort(int data[], int count, cFtnPtr comparePtr)
{
	bool swapOccured;             // State of the swap

	try
	{
		for (int i = 0; i < count - 1; i++)
		{
			swapOccured = false; // Keep setting to false before attempting to swap
			for (int j = 0; j < count - i - 1; j++)
			{
				if (comparePtr(data[j + 1], data[j])) // Check if heart rate is larger than the value after it
				{
					swap(data[j], data[j + 1]);
					swapOccured = true; // Swapping has occured
				}
			}

			// Once there is no more swapping to happen, return successful
			if (!swapOccured) return Success;
		}
	}
	catch (exception e)
	{
		return UnknownError;
	}
	return Success;
}

int _tmain(int argc, _TCHAR* argv[])
{
	HRData data[MAX_DATA];

	// Change "Debug" to "Release" for release mode
	char* inputFile = "..\\Debug\\HR.csv";

	int count = LoadMeasurements(inputFile, data, MAX_DATA);
	cout << "Measurements loaded:" << count << endl;

	//QuickSort(data, 0, count-1, &compare); // Sort the array using quick sort algorithm
	//Sort(data, count, &compare);         // Sort the array using bubble sort algorithm

	//for (int i = 0; i < count; i++)
	//{	// Outputting the heart rate date
	//	cout << "Heart Rate: " << data[i].hr << " Date: " << data[i].date << "\n";
	//}

	if (count > 0) 
	{
		int status = CallDLL(L"../Debug/DLL.dll", data, count);

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

	const int totalNumbers = 70000;
	int numbers[totalNumbers];
	// Generating random numbers between 50 and 180
	for (int i = 0; i < totalNumbers; i++)
	{
		numbers[i] = Random();
	}
	
	// Decide on what unit i am measuring time in
	//auto StartTime = chrono::high_resolution_clock::now();
	clock_t start, end;
	start = clock();
	Sort(numbers, totalNumbers, &compare);
	//QuickSort(numbers, 0, totalNumbers-1, &compare);
	end = clock();
	cout << "Time: " << end - start << endl;
	//auto EndTime = chrono::high_resolution_clock::now();

	//auto TimeMicroS = ((float)(EndTime - StartTime)) * 1000000 / totalNumbers;
	
	for (int i = 0; i < totalNumbers; i++)
	{
		cout << numbers[i] << " ";
	}
	cout << endl;
	//cout << "Start Time: " << StartTime << " End Time: " << EndTime << " Time taken(MicroS): " << TimeMicroS << "\n";
	
	system("pause");
	return Success;
}