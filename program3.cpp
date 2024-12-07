#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
// Global variables
const int MEMORY_SIZE = 32;
// Memory bitmap, 0 means free, 1 means allocated
vector<int> memoryBitmap(MEMORY_SIZE, 0);
// Table to store the process ID and the allocated memory info
unordered_map<int, pair<int, int>> processTable;
void allocateMemory(int, int);
void freeMemory(int);
void displayMemoryBitmap();
int bestFit(int);
// Main function to drive the menu
int main() {
	int choice;
	int allocationBlocks, processID;
	do {
		cout << "\nMemory Management Menu:\n";
		cout << "1. Allocate Memory for a Process\n";
		cout << "2. Free Memory for a Process\n";
		cout << "3. Display Memory Bitmap\n";
		cout << "4. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "Enter Process ID: ";
			cin >> processID;
			cout << "Enter the number of allocation blocks: ";
			cin >> allocationBlocks;
			allocateMemory(processID, allocationBlocks);
			break;
		case 2:
			cout << "Enter Process ID to free memory: ";
			cin >> processID;
			freeMemory(processID);
			break;
		case 3:
			displayMemoryBitmap();
			break;
		case 4:
			cout << "Goodbye!\n";
			break;
		default:
			cout << "Invalid choice. Please try again.\n";
		}
	} while (choice != 4);
	return 0;
}
// Function to allocate memory using Best Fit algorithm
void allocateMemory(int processID, int allocationBlocks) {
	// Grab the index
	int bestFitResult = bestFit(allocationBlocks);
	// Error with memory
	if (bestFitResult == -1) {
		cout << "Error: Not enough memory available to allocate " <<
			allocationBlocks << " blocks for process " << processID << endl;
		return;
	}
	// Marking bits as 1 (allocated) to allocate memory
	for (int i = bestFitResult; i < bestFitResult + allocationBlocks; ++i) {
		memoryBitmap[i] = 1;
	}
	// Store the allocation details with a pair
	processTable[processID] = make_pair(bestFitResult, allocationBlocks);
	int tempResult = bestFitResult + allocationBlocks - 1;
	cout << "Memory allocated to process " << processID << " from index " <<
		bestFitResult << " to " << tempResult << endl;
}
// Function to free memory using Process ID
void freeMemory(int processID) {
	// Process ID not found
	if (processTable.find(processID) == processTable.end()) {
		cout << "Error: Process ID " << processID << " not found." << endl;
		return;
	}
	int tableFirst = processTable[processID].first;
	int tableSize = processTable[processID].second;
	// Mark the allocated blocks as free (0)
	for (int i = tableFirst; i < tableFirst + tableSize; ++i) {
		memoryBitmap[i] = 0;
	}
	// Erasing the processID in the table
	processTable.erase(processID);
	int tempTable = tableFirst + tableSize - 1;
	cout << "Memory for process " << processID << " has been removed from index "
		<< tableFirst << " to " << tempTable << endl;
}
// Function to display the memory bitmap
void displayMemoryBitmap() {
	// Pretty simple, just displaying the bitmap
	cout << "Memory Bitmap: ";
	for (int i = 0; i < MEMORY_SIZE; ++i) {
		cout << memoryBitmap[i] << " ";
	}
	cout << endl;
}
// Function to find the best fit block for memory allocation
int bestFit(int allocationBlocks) {
	// Variables
	// -1 to say no block found yet
	int bestFitResult = -1;
	// Any block found with size less than MEMORY_SIZE + 1 will be considered
	int bestFitSize = MEMORY_SIZE + 1;
	// Starting index of the current free block
	int start = -1;
	// Tracks size of the current free memory block
	int size = 0;
	// Look for the bestfit block in memory
	for (int i = 0; i < MEMORY_SIZE; ++i) {
		if (memoryBitmap[i] == 0) {
			// Found a free block, start or continue counting
			if (start == -1) {
				start = i;
			}
			// Add to the size of the current free memory block
			size++;
		}
		else {
			// Found an allocated block, check if previous free block was a best fit
				if (size >= allocationBlocks && size < bestFitSize) {
					bestFitSize = size;
					bestFitResult = start;
				}
			// Reset variables
			start = -1;
			size = 0;
		}
	}
	// If the last segment is the best fit
	if (size >= allocationBlocks && size < bestFitSize) {
		bestFitResult = start;
	}
	return bestFitResult;
}

/* Submission Notes:
-0.1pts: You can allocate multiple processes of the same ID (the previous process is lost).
*/
