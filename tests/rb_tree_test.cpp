#include <iostream>
#include <cassert>
#include <climits>
#include <sstream>
using namespace std;
#include "../datastructs.hpp"

int main(){

	string K[10] = {"A","B","C","D","E","F","G","H","I","K"};
	int V[10] = {10,9,8,7,6,5,4,3,2,1};
	
	RBTree<string,int> T1, T2(K,V,10);
	
	for(int i=0; i<10; i++) T1.insert(K[i],V[i]);
	// T1 and T2 should be identical trees

    assert(*(T2.search("C")) == 8);
    assert(T1.rank("C") == 3);
    assert(T1.select(3) == "C");

	// Reusable ostringstream for testing
    ostringstream testingStream;

    T2.preorder(testingStream);
	assert(testingStream.str() == "D B A C F E H G I K\n");
	testingStream.str(""); // Clear the stream

	T2.inorder(testingStream);
	assert(testingStream.str() == "A B C D E F G H I K\n");
	testingStream.str(""); // Clear the stream

	T2.postorder(testingStream);
	assert(testingStream.str() == "A C B E G K I H F D\n");
	testingStream.str(""); // Clear the stream

	assert(T2.remove("D") == 1);

	T2.preorder(testingStream);
	assert(testingStream.str() == "F C B A E H G I K\n");
	testingStream.str(""); // Clear the stream

	T2.inorder(testingStream);
	assert(testingStream.str() == "A B C E F G H I K\n");
	testingStream.str(""); // Clear the stream

	T2.printk(3, testingStream);
	assert(testingStream.str() == "A B C\n");
	testingStream.str(""); // Clear the stream

	assert(T2.remove("J") == 0);
	assert(T2.rank("G") == 6);
	assert(*(T1.successor("C")) == "D");
	assert(*(T1.predecessor("C")) == "B");

	RBTree<string,int> T3;
	T3 = T2;
	T1 = T3;

	// Clear T2
	for (int i=0; i<10; i++) T2.remove(K[i]);

	// T3 and T1 should be identical trees and not linked to T2

	ostringstream testingStream2;
	T1.preorder(testingStream);
	T3.preorder(testingStream2);
	assert(testingStream.str() == testingStream2.str());
	testingStream.str(""); // Clear the stream
	testingStream2.str(""); // Clear the stream

	T1.inorder(testingStream);
	T3.inorder(testingStream2);
	assert(testingStream.str() == testingStream2.str());
	testingStream.str(""); // Clear the stream
	testingStream2.str(""); // Clear the stream

	T1.postorder(testingStream);
	T3.postorder(testingStream2);
	assert(testingStream.str() == testingStream2.str());
	testingStream.str(""); // Clear the stream
	testingStream2.str(""); // Clear the stream

	return 0;
}
