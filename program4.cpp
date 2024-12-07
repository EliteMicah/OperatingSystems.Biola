#include <iostream>
#include <vector>
using namespace std;
// Working Set Window (arbitrary threshold for replacement)
const int WINDOW_SIZE = 400;
// Structure for each page frame node in the WSClock
class PageFrameNode {
public:
	int lastUseTime;
	int referenceBit;
	PageFrameNode(int time, int refBit) : lastUseTime(time), referenceBit(refBit)
	{}
};
void displayWSClock(const vector<PageFrameNode>&, int, int);
void wsClockPageReplacement(vector<PageFrameNode>&, int&);
int main() {
	// Initialize the WSClock with given values (time of last use: reference R bit)
	vector<PageFrameNode> clock = { {1620, 0}, {2032, 1}, {2020, 1}, {2014, 1},
	{1213, 0}, {1980, 1}, {2003, 1}, {2084, 1} };
	int virtualTime = 2204; // Starting virtual time
	// Run WSClock Page Replacement Algorithm
	wsClockPageReplacement(clock, virtualTime);
	cout << "Done!" << endl;
	return 0;
}
// Display the current state of the working set with a pointer or an index
void displayWSClock(const vector<PageFrameNode>& clock, int nodePointer, int
	virtualTime) {
	cout << "Virtual Time: " << virtualTime << endl;
	cout << "Working Set Clock: ";
	// Cycle through the clock
	for (int i = 0; i < clock.size(); i++) {
		// For each clock,
		if (i == nodePointer) {
			cout << "[" << clock[i].lastUseTime << ":" << clock[i].referenceBit <<
				"] ";
		}
		else {
			cout << clock[i].lastUseTime << ":" << clock[i].referenceBit << " ";
		}
	}
	cout << endl << endl;
}
// WSClock Page Replacement Algorithm
void wsClockPageReplacement(vector<PageFrameNode>& clock, int& virtualTime) {
	// Initial pointer to node with last use time 2014
	int nodePointer = 3;
	while (true) {
		// Display the clock
		displayWSClock(clock, nodePointer, virtualTime);
		// If reference bit is 1
		if (clock[nodePointer].referenceBit == 1) {
			// Set the reference to 0
			clock[nodePointer].referenceBit = 0;
			// Then move to the next node
			nodePointer = (nodePointer + 1) % clock.size();
		}
		else { // If reference bit is 0
			// If last use time is outside window
			// Find the time difference and see if it is greater than the window size
				if (virtualTime - clock[nodePointer].lastUseTime > WINDOW_SIZE) {
					cout << "Replacing page at index " << nodePointer << endl;
					// Replace the page
					// Show that the page is being accessed or replaced at the current virtual time
						clock[nodePointer].lastUseTime = virtualTime;
					// Page has been recently used
					clock[nodePointer].referenceBit = 1;
					// Move on to next page
					virtualTime++;
				}
			// Then move to the next node
			nodePointer = (nodePointer + 1) % clock.size();
		}
		// Stop if we have cycled back to the original starting point
		if (nodePointer == 3) {
			break;
		}
	}
}
