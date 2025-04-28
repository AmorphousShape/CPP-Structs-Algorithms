#include "../datastructs.hpp"

#include <iostream>
#include <cassert>
#include <sstream>

int main() {

    std::string A[10] = {"A", "B", "C", "D", "E", "F", "H", "I", "J", "K"};
	int B[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

	Heap<int> T1, T2(B, 10);
	std::ostringstream testingStream;

	T2.printKeys(testingStream);
	assert(testingStream.str() == "1 2 4 3 6 5 8 10 7 9\n");
	testingStream.str(""); // Clear the stream

	for (int i = 0; i < 10; i++) {
		T1.insert(B[i]);
    }
    
	T1.printKeys(testingStream);
	assert(testingStream.str() == "1 2 5 4 3 9 6 10 7 8\n");
	testingStream.str(""); // Clear the stream

	assert(T2.peekKey() == 1);
	assert(T1.extractMin() == 1);

	T1.printKeys(testingStream);
	assert(testingStream.str() == "2 3 5 4 8 9 6 10 7\n");
	testingStream.str(""); // Clear the stream

	// Test copy constructor
	Heap<int> T3(T2);
	while (T3.size() > 0) {
		testingStream << T3.extractMin();
		if (T3.size() > 0) {
			testingStream << " ";
		}
    }
	assert(testingStream.str() == "1 2 3 4 5 6 7 8 9 10");
	testingStream.str(""); // Clear the stream

	// Test assignment operator
	Heap<int> T4 = T1;
	while (T4.size() > 0) {
		testingStream << T4.extractMin();
		if (T4.size() > 0) {
			testingStream << " ";
		}
    }
	assert(testingStream.str() == "2 3 4 5 6 7 8 9 10");

    return 0;
}