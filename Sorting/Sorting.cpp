#include <iostream>
#include <array>
#include <chrono>

#define ArrayAndSize(arr) \
	arr, (sizeof(arr)/sizeof(arr[0]))

bool oppg2 = false;

void RandomizeArray(int *a, int size)
{
	for(auto i= 0; i < size; i++)
	{
		a[i] = rand();
	}
}

void PrintArray(int *a, int size)
{
	for(auto i= 0; i < size; i++)
	{
		std::cout << a[i] << std::endl;
	}
}

int Partition(int arr[], int low, int high)
{
	const int pivot = arr[high];

	int r = 0;
	int l = 1;
	for (;;)
	{
		for (auto i = low; i < high; i++)
		{
			if (arr[i] > pivot)
			{
				l = i;
				break;
			}
		}

		for (auto i = high - 1; i > 0; i--)
		{
			if (arr[i] < pivot)
			{
				r = i;
				break;
			}
		}

		if (l < r)
		{
			std::swap(arr[l], arr[r]);
		}
		else
		{		
			break;
		}
	}

	if (arr[l] > arr[high])
		std::swap(arr[l], arr[high]);
	
	return l;
}


void QuickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		const int p = Partition(arr, low, high);
		QuickSort(arr, low, p - 1);
		QuickSort(arr, p + 1, high);
	}
}

/* C++ implementation of QuickSort */
using namespace std;

// A utility function to swap two elements 
void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition(int arr[], int low, int high)
{
	int pivot = arr[high]; // pivot 
	int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than the pivot 
		if (arr[j] < pivot)
		{
			i++; // increment index of smaller element 
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before 
		// partition and after partition 
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

/* Function to print an array */
void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}


void MergeSort(int a[], int n)
{
	int i, j, k, lower1, lower2, size, upper1, upper2;
	int* hjelp = new int[n];

	size = 1;
	while (size < n)
	{
		lower1 = 0;
		k = 0;
		while (lower1 + size < n)
		{
			upper1 = lower1 + size - 1;
			lower2 = upper1 + 1;
			upper2 = (lower2 + size - 1 < n) ? lower2 + size - 1 : n - 1;
			for (i = lower1, j = lower2; i <= upper1 && j <= upper2; k++)
				if (a[i] < a[j])
					hjelp[k] = a[i++];
				else
					hjelp[k] = a[j++];

			for (; i <= upper1; k++)
				hjelp[k] = a[i++];
			for (; j <= upper2; k++)
				hjelp[k] = a[j++];

			lower1 = upper2 + 1;
		}

		for (i = lower1; k < n; i++)
			hjelp[k++] = a[i];
		
		for (i = 0; i < n; i++)
		{
			a[i] = hjelp[i];
			
			if (oppg2)
				std::cout << a[i] << " ";

		}
		
		if (oppg2)
			std::cout << std::endl;
		
		size = size * 2;

	}
	delete[] hjelp;
}


void InsertSort(int a[], int n)
{
	int i, j, temp;
	for (i = 1; i < n; i++) {
		temp = a[i];
		j = i - 1;

		while (j >= 0 && temp <= a[j])
		{
			a[j + 1] = a[j];
			j = j - 1;
		}
		a[j + 1] = temp;
	}
}

void SampleSort(int* arr, int n)
{
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (arr[i] > arr[j])
				std::swap(arr[i], arr[j]);
}

void BubbleSort(int* arr, int n)
{
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - 1; j++)
			if (arr[j] > arr[j + 1])
				std::swap(arr[j], arr[j + 1]);
}

void QuickSortWrapper(int* a, int n)
{
	quickSort(a, 0, n-1);
}

void TestSort(void sortFunc(int* arr, int n), std::initializer_list<int> nTimes)
{
	int numTimes = 10;
	for (const auto& l : nTimes)
	{
		int* arr = new int[l];
		double avg = 0; 
		for (int i= 0; i< numTimes; i++)
		{
			RandomizeArray(arr, l);
			auto start = std::chrono::steady_clock::now();
			sortFunc(arr, l);
			auto end = std::chrono::steady_clock::now();
			avg += std::chrono::duration<double, std::milli>(end - start).count();
		}
		avg /= numTimes;
		
		std::cout << "For n: " << l << " " << "avg sort time(MS): " << avg << std::endl;
		//PrintArray(arr, l);
		delete[] arr;
	}
}


void Oppgave3AEksamen2018()
{
	std::cout << "Oppgave 1: " << std::endl;
	std::initializer_list<int> n{ 10, 100, 1000, 10000 };
	std::cout << "Running BubbleSort: " << std::endl;
	TestSort(BubbleSort, n);

	std::cout << "Running SampleSort: " << std::endl;
	TestSort(SampleSort, n);
	
	std::cout << "Running InsertSort: " << std::endl;
	TestSort(InsertSort, n);

	std::cout << "Running MergeSort: " << std::endl;
	TestSort(MergeSort, n);

	std::cout << "Running QuickSort: " << std::endl;
	TestSort(QuickSortWrapper, n);

	std::cout << std::endl;
}

void Oppgave2BEksamen2019()
{
	oppg2 = true;
	std::cout << "Oppgave 2: " << std::endl;
	//17,14,5,7,12,1,16,29,13,4,8,18,22,2.
	int arr[] = { 17, 14, 5 ,7, 12 ,1 ,16, 29 , 13, 4,8,18,22,2 };
	MergeSort(arr, _countof(arr));
	oppg2 = false;
}


void Eksamen2017Oppg1()
{
	int arr[50];

	for (int i = 0; i<50; i++)
	{
		arr[i] = rand() % 9 + 1;
	}

	InsertSort(arr, _countof(arr));
	printArray(arr, _countof(arr));
}



int main()
{
	srand(time(nullptr));

	Eksamen2017Oppg1();
	
	//OPPGAVE 1
	// Oppgave3AEksamen2018();

	// OPPGAVE2
	//Oppgave2BEksamen2019();

}
