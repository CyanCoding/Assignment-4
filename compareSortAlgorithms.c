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
	
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n) {
	
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n) {
	
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
            fscanf(inFile, "%d ", /*ppData[i]*/ *ppData + i);
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
	char* fileNames[] = {"/home/cam/Desktop/Computer Science 1/Assignments/Assignment 4/input1.txt",
                         "/home/cam/Desktop/Computer Science 1/Assignments/Assignment 4/input2.txt",
                         "/home/cam/Desktop/Computer Science 1/Assignments/Assignment 4/input3.txt"};
	
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
		
//		printf("Selection Sort:\n");
//		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
//		extraMemoryAllocated = 0;
//		start = clock();
//		selectionSort(pDataCopy, dataSz);
//		end = clock();
//		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
//		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
//		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
//		printArray(pDataCopy, dataSz);
//
//		printf("Insertion Sort:\n");
//		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
//		extraMemoryAllocated = 0;
//		start = clock();
//		insertionSort(pDataCopy, dataSz);
//		end = clock();
//		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
//		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
//		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
//		printArray(pDataCopy, dataSz);
//
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