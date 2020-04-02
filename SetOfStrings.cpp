#include "SetOfStrings.h"

using namespace std;

// This function returns a boolean output on whether or not the SetOfStrings it is
// 		called on is empty or not.
bool SetOfStrings::isEmpty()
{
	if(setv.empty()) return true;
	else return false;
}

// The function size returns the number of indices stored in the SetofStrings it
// 		is called on.
int SetOfStrings::size(){
	return (int) setv.size();
}

// The function isMember tests if the input string s is contained within
//		the SetOfStrings it is called on, returning a boolean output.
bool SetOfStrings::isMember(string s)
{
	// Start pointer iteration at start of the set
	p=setv.begin();
	while(p!=setv.end()){
		// Iterate through the set, if current point equals the string, return true.
		if(*p==s)return true;
		++p;
	}
	return false;
}

// The function insertElement is used to append string s to the SetOfStrings it is called on.
void SetOfStrings::insertElement(string s)
{
	if(!isMember(s)){
		setv.push_back(s);
	}
}


// The removeElement function searches through the set and, if an element equivalent
// 		to the input string s is found, that element is erased from the set.
void SetOfStrings::removeElement(string s)
{
	p = setv.begin();
	if (!isMember(s)) {
		// If string s is not a member the function is exited.
		return;
	}
	while (p != setv.end()) {
	  	if (*p == s) {
	  		// When the thing p is pointing to is equal to the string s,
	  		// 		that point is erased from the string.
	  		setv.erase(p);
	  		return;
	   	}
	  	++p;
	}
}

// The setUnion function returns a combination of type SetOfStrings
//		between the input SetOfStrings s and the SetOfStrings this function
//		is called on.
SetOfStrings *SetOfStrings::setUnion(SetOfStrings *s)
{
	// Create an output string to store the union in.
	SetOfStrings *out = new SetOfStrings();
	// Initialise pointers.
    p = setv.begin();
    s->p = s->setv.begin();
    // Insert all elements from both sets to the output array.
    while (p != setv.end()) {
    	out->insertElement(*p);
    	++p;
    }
    while (s->p != s->setv.end()) {
    	out->insertElement(*(s->p));
    	++(s->p);
    }
    // Return the output array.
    return out;
}

// The isEqual function returns a boolean on whether or not
// 		the input SetOfStrings is equal to the SetOfStrings
//		the function is called on.
bool SetOfStrings::isEqual(SetOfStrings *s)
{
	// Equality of sets is defined as each being a subset of each other.
	if (subset(s) && s->subset(this)) {
    	return true;
    }
    return false;
}

// The returnElement function searches through all elements, and returns
// 		the element at the specified index.
string SetOfStrings::returnElement(int index)
{
	if (index < (int)setv.size() && index >= 0)
		return setv.at(index);
	else
		return "\n";
}

// The product function returns a SetOfStrings containing all possible
// 		combinations between elements from the input SetOfStrings s and
//		the SetOfStrings it was called on.
SetOfStrings *SetOfStrings::product(SetOfStrings *s)
{
    SetOfStrings *out = new SetOfStrings();
    p = setv.begin();
    string addString;
    vector<string>::iterator i;

    // Nested loop to create a combination of elements and append to
    // 		the output set.
    while (p != setv.end()) {
    	i = s->setv.begin();
    	while (i != s->setv.end()) {
    		addString.clear();
    		addString.append(*p);
    		addString.append(",");
    		addString.append(*i);
    		out->insertElement(addString);
    		++i;
    	}
    	++p;
    }
    return out;
}

// The subset function tests is all elements within the input
//		SetOfStrings s are within the SetOfStrings the function
// 		was called on, returning a boolean output.
bool SetOfStrings::subset(SetOfStrings *s)
{
    // Testing if s is within the current set.
    s->p = s->setv.begin();
    while (s->p != s->setv.end()) {
    	if (!isMember(*(s->p))) {
    		// If at any point it is not a member,
    		// false is returned and the function exits.
    		return false;
    	}
    	++(s->p);
    }
    return true;
}

// The setElement function sets the element at an input index to
// 		the value of input string s.
void SetOfStrings::setElement(int index, string s) {
	p = setv.begin();
	int i = 0;
	// Function iteration until the index equals the iterated value.
	while (p != setv.end()) {
		if (i == index) {
			// The element is replaced when index reached.
			*p = s;
		}
		++i;
		++p;
	}
}


