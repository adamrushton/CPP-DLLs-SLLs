#include "stdafx.h"
#include "../ConsoleApplication1/HRRiskAssessment.h" 
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Determines the sorting order
int compare(const int a, const int b)
{
	return a < b;
}

int LoadMeasurements(char* inputFile, HRData data[], int max_size)
{
	string date, heartRate, temp; // Store data temporarily from the csv file into seperate strings
	int count = 0;				  // Count the number of lines
	ifstream myFile(inputFile);   // Open file

	if (myFile.fail()) return InvalidParameters; // Cannot find file

	try
	{
		while (!myFile.eof())
		{
			if (count == 0) getline(myFile, temp);    // Ignores the first line
			getline(myFile, date, ',');			      // Gets the dates, storing into "date"
			getline(myFile, heartRate, ',');	      // Gets heart rates, storing into "heartRate"

			if (!date.find("\r\n")) date.erase(0, 2); // Remove \r\n from string

			strcpy(data[count].date, date.c_str());   // Convert from c string to char*
			data[count].hr = atoi(heartRate.c_str()); // Convert from c string to int

			count++;
		}
	} 
	catch (exception e)
	{
		return UnknownError;
	}
	myFile.close(); // Close file once done
	return count-1; // Return number of entries, -1 to ignore first line
}

int CallDLL(WCHAR* dllName, HRData data[], int count)
{
	try
	{
		HMODULE handle = LoadLibraryW(dllName);

		if (handle != NULL)
		{
			cFtnAccessRisk function = (cFtnAccessRisk)GetProcAddress(handle, "AssessRisk");

			if (function != NULL) return function(data, count);
			else                  return DllInvalidFormat;
		}
		else return DllNotFound;
		FreeLibrary(handle); // Free the dll we are done with it
	}
	catch (exception e)
	{
		return UnknownError;
	}
}

// Bubble sort algorithm
int Sort(HRData data[], int count, cFtnPtr comparePtr)
{
	bool swapOccured; // State of the swap

	try
	{
		for (int i = 0; i < count - 1; i++)
		{
			swapOccured = false; // Keep setting to false before attempting to swap
			for (int j = 0; j < count - i - 1; j++)
			{
				if (comparePtr(data[j + 1].hr, data[j].hr)) // Check if heart rate is larger than the value after it
				{
					swap(data[j], data[j + 1]); // Swap
					swapOccured = true;         // Update swap state
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

// Bubble sort algorithm
// Modified version for obtaining results
int TimingBubbleSort(int numbers[], int count, cFtnPtr comparePtr)
{
	bool swapOccured; // State of the swap

	try
	{
		for (int i = 0; i < count - 1; i++)
		{
			swapOccured = false; // Keep setting to false before attempting to swap
			for (int j = 0; j < count - i - 1; j++)
			{
				if (comparePtr(numbers[j + 1], numbers[j])) // Check if heart rate is larger than the value after it
				{
					swap(numbers[j], numbers[j + 1]); // Swap
					swapOccured = true;               // Update swap state
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

// Partitioning for the quick sort algorithm
int Partition(HRData data[], int start, int end, cFtnPtr comparePtr)
{
	int pivot = data[end].hr;  // Set pivot to the last entry in the array
	int pivotIndex = start;    // Store entries that are lower than the pivots value

	for (int i = start; i < end; i++)
	{   // Looping through all heart rate entries 
		if (comparePtr(data[i].hr, pivot))   // Sorting type is determined by the comparison function
		{   // If value is smaller than the pivot
			swap(data[i], data[pivotIndex]); // Swap entry with an entry lower than the pivots value
			pivotIndex++;					 // Increase value
		}
	}

	swap(data[pivotIndex], data[end]); // Swap the heart rate entries around

	return pivotIndex;
}

void QuickSort(HRData data[], int start, int end, cFtnPtr comparePtr)
{
	if (end > start)
	{
		int pivot = Partition(data, start, end, &compare);
		
		QuickSort(data, start, pivot - 1, &compare);
		QuickSort(data, pivot + 1, end, &compare);
	}
}

// Used for generating results
int TimingPartition(int numbers[], int start, int end, cFtnPtr comparePtr)
{
	int pivot = numbers[end];  // Set pivot to the last entry in the array
	int pivotIndex = start;    // Store entries that are lower than the pivots value

	for (int i = start; i < end; i++)
	{   // Looping through all heart rate entries 
		if (comparePtr(numbers[i], pivot))         // Sorting type is determined by the comparison function
		{   // If value is smaller than the pivot
			swap(numbers[i], numbers[pivotIndex]); // Swap entry with an entry lower than the pivots value
			pivotIndex++;					       // Increase value
		}
	}

	swap(numbers[pivotIndex], numbers[end]); // Swap the heart rate entries around

	return pivotIndex;
}

// Used for generating results
void TimingQuickSort(int numbers[], int start, int end, cFtnPtr comparePtr)
{
	if (end > start)
	{
		int pivot = TimingPartition(numbers, start, end, &compare);

		TimingQuickSort(numbers, start, pivot - 1, &compare);
		TimingQuickSort(numbers, pivot + 1, end, &compare);
	}
}