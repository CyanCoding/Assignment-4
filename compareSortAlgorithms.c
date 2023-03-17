#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// Used by mergeSort()
void merge(int pData[], int l, int mid, int r) {
    int firstHalf = mid - l + 1;
    int secHalf = r - mid;

    // Temporary arrays
    int *left = malloc(firstHalf * sizeof(int));
    int *right = malloc(secHalf * sizeof(int));

    // Move values to temp arrays
    for (int i = 0; i < firstHalf; i++)
        left[i] = pData[i + l];
    for (int i = 0; i < secHalf; i++)
        right[i] = pData[mid + i + 1];

    int leftIterator = 0;
    int rightIterator = 0;
    int mergeIterator = l;

    // We compare and move values back to pData[]
    while (leftIterator < firstHalf && rightIterator < secHalf) {
        if (left[leftIterator] <= right[rightIterator]) {
            pData[mergeIterator] = left[leftIterator];
            leftIterator++;
        }
        else {
            pData[mergeIterator] = right[rightIterator];
            rightIterator++;
        }

        mergeIterator++;
    }

    // Empty any remaining values from left[] or right[] if present
    while (leftIterator < firstHalf) {
        pData[mergeIterator] = left[leftIterator];
        leftIterator++;
        mergeIterator++;
    }
    while (rightIterator < secHalf) {
        pData[mergeIterator] = right[rightIterator];
        rightIterator++;
        mergeIterator++;
    }

    free(left);
    free(right);
}

// Used by most functions when swapping numbers
void swap(int *x, int *y) {
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r) {
    if (l < r) {
        int mid = (l + r) / 2;

        // Sort left and right
        mergeSort(pData, l, mid);
        mergeSort(pData, mid + 1, r);

        merge(pData, l, mid, r);
    }
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n) {
	for (int i = 1; i < n; i++) {
        int val = pData[i];
        int j = i - 1;

        while (j >= 0 && pData[j] > val) {
            pData[j + 1] = pData[j];

            j--;
        }
        pData[j + 1] = val;
    }
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n) {
    // We need to keep sorting until the full array is sorted
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // We compare two values and swap if necessary
            if (pData[j] > pData[j + 1]) {
                swap(&pData[j], &pData[j + 1]);
            }
        }
    }
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n) {
	for (int i = 0; i < n - 1; i++) {
        int savePos = i;

        // Go through the rest of the unsorted list to find the smallest number,
        // then replace with position i.
        for (int j = i + 1; j < n; j++) {
            if (pData[j] < pData[savePos]) {
                savePos = j;
            }
        }

        // Replace if i and savePos are not the same
        if (savePos != i) {
            swap(&pData[i], &pData[savePos]);
        }
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData) {
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
    int data = 0;
	*ppData = NULL;
	
	if (inFile) {
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = malloc(sizeof(int) * dataSz);

		// Implement parse data block
        for (int i = 0; i < dataSz; i++) {
            fscanf(inFile, "%d ", ppData[i]);
        }
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz) {
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i) {
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i) {
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void) {
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt",
                         "input2.txt",
                         "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}