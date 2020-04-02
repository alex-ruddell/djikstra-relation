#ifndef SetOfStrings_SetOfStrings_h
#define SetOfStrings_SetOfStrings_h
#include <iostream>
#include <iostream>
#include <vector>
#include <cstring>
#include <stdio.h>

using namespace std;

class SetOfStrings{
	protected:
		vector<string> setv;		// Set in which all nodes are stored.
		vector<string>::iterator p; // Iterator to navigate setv.
	public:

		// setUnion returns a SetOfStrings consisting of all elements contained in both
		//			the input set1 and the set this function is called on.
		SetOfStrings *setUnion(SetOfStrings *set1);

		// setIntersection returns a SetOfStrings consisting of common elements between
		//					the input set1 and the set this function is called on.
		SetOfStrings *setIntersection(SetOfStrings *set1);

		// product returns a SetOfStrings consisting of every binary relation possible
		//			from elements of set1 and the set this function is called one.
		SetOfStrings *product(SetOfStrings *set1);
		

		// Utility methods

		// isEmpty returns a true/false boolean output based on whether or not the
		// 			instance it is called on is empty or not.
		bool isEmpty();

		// isEqual returns a true/false boolean output based on whether or not the
		//			input SetOfStrings is equal to the instance the function was called on.
		bool isEqual(SetOfStrings *s);

		// isMember returns a true/false boolean output based on whether or not the
		// 			input string s is a member of the SetOfStrings instance the function
		//			was called on.
		bool isMember(string s);

		// subset returns a true/false boolean output based on whether or not all elements of
		// 			the input set s are contained in the SetOfStrings instance this function
		//			is called one.
		bool subset(SetOfStrings *s);

		// size returns the number of elements contained within the SetOfStrings instance
		// 		the function is called on.
		int size();
		
		// Insert and remove

		// insertElement pushes back the string s into the set of strings.
		void insertElement(string s);

		// removeElement removes the string s from the set of strings if
		// 					it is located within it.
		void removeElement(string s); 
		
		// setElement sets the element at a specifed index to the input string s.
		void setElement(int index, string s);

		// returnElement is a getter that returns the element at any given index.
		string returnElement(int index);

};

#endif


