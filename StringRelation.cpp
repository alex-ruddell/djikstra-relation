#include "StringRelation.h"
#include <string>

// Will be used for calling the ColourText() method in print() functions
SetOfStrings *S = new SetOfStrings();

// The setInput function sets the input string s as
//		the base node values for the relation.
void StringRelation::setInput(SetOfStrings *s)
{
	set1=s;
}

// addWeight allows for weights to be initalised in the vector.
void StringRelation::addWeight(int s)
{
	weight.push_back(s);
}

// The isValid function tests if the StringRelation is valid.
// Can only contain values from the product of its nodes with
// 		itself.
bool StringRelation::isValid(){
	// Create the product of set1 with itself
	// out= set1 /times set1
	SetOfStrings *out = new SetOfStrings();
	out = set1->product(set1);
	// Overloaded printRelation method used for printing the relation that is
	// equal to the product set
	if(out->subset(this)) return true;
	else return false;
}

//This is one of the main helper function provided as a
//tokenizer to parse relational elements and separate them into components
//This takes a relation element in the form "a,b" and returns
//a string vector containing "a" and "b"
vector<string> StringRelation::makeTokens(string next){
	vector<string> out;
	vector<string>::iterator p;
	char *a = new char [next.length()+1];
	strcpy(a,next.c_str());
	char* token = std::strtok(a,",");
	int index=0;
	while (token != NULL) {
		out.push_back(token);
		token = std::strtok(NULL, ",");
		index++;
	}
	return out;
}

// The createReflexiveElement function creates an output string of
// 		format s,s given input string s.
string StringRelation::createReflexiveElement(string s){
	string next, next1;
	next = s;
	next1=next;
	next.append(",");
	next.append(next1);
	return next;
}


// The computeDual function takes input string os format a,b and
// 		returns one of format b,a.
string StringRelation::computeDual(string s){
	vector<string> tokens=makeTokens(s);
	vector<string>::iterator p;
	p=tokens.begin();
	string other, other1;
	while(p!=tokens.end()-1){
		other=*p;
		other1=*(p+1);
		other1.append(",");
		other1.append(other);
		++p;
	}
	return other1;
}

// The returnSecondComponent function returns the second value b
// 		from input string of format a,b.
string StringRelation::returnSecondComponent(string s){
	vector<string> tokens;
	vector<string>::iterator p;
	tokens=makeTokens(s);
	p=tokens.begin();
	return *(p+1);
}

// The isReflexiveElement function tests if the input string s
// 		is in the format a,a where both values are equal.
bool StringRelation::isReflexiveElement(string s){
	if (s.size() == 3 && s[0] == s[2] && s[1] == ',') {
		// Checks for a comma separating two equal values.
		return true;
	}
	return false;
}

// The isReflexive function tests if the StringRelation it is called on
// 		contains relations s,s for all unique nodes s in the set.
bool StringRelation::isReflexive(){
	// Set 1 contains the individual values.
	// Setv contains edges as the relation is operated on.
	int i;
	string testString;
	// For all members, a reflexive element is created.
	for (i = 0; i < set1->size(); i++) {
		testString.clear();
		testString = createReflexiveElement(set1->returnElement(i));
		// False is returned as soon as one of these is found to not be a member.
		if (!isMember(testString)) {
			return false;
		}
	}
	// If the loop exits without returning, all are members, so true is returned.
	return true;

}

// The isSymmetric function tests if the StringRelation is is called on contains
//		s2,s1 for each s1,s2 value read from the relation.
bool StringRelation::isSymmetric(){
	// A product of set1 with itself.
	SetOfStrings *productSet = new SetOfStrings;
	SetOfStrings *duplicateSet = new SetOfStrings;
	int i, k;
	for (i = 0; i < set1->size(); i++) {
		duplicateSet->insertElement(set1->returnElement(i));
	}
	productSet = duplicateSet->product(set1);
	// For all reflexive elements within productset, if they are also in
	// the StringRelation this function is called on, true is returned.
	for (k = 0; k < productSet->size(); k++) {
		if (!isReflexiveElement(productSet->returnElement(k))) {
			if (!isMember(productSet->returnElement(k)) && isMember(computeDual(productSet->returnElement(k)))) {
				return false;
			}
			if (isMember(productSet->returnElement(k)) && !isMember(computeDual(productSet->returnElement(k)))) {
				return false;
			}
		}
	}
	return true;
}

//The isTransitive function tests if the StringRelation it is called on is
// 		a transitive one, i.e. for all a,b and b,c; a,c is also present.
bool StringRelation::isTransitive(){
	int i, j;
	string currentElement, secondComponent, newEnd;
	for (i = 0; i < this->size(); i++) {
		currentElement = this->returnElement(i);
		secondComponent = returnSecondComponent(this->returnElement(i));
		for (j = 0; j < this->size(); j++) {
			if (j != i) {
				if (isFirstComponent(secondComponent, this->returnElement(j))) {
					newEnd = returnSecondComponent(this->returnElement(j));
					currentElement.replace(2,1,newEnd);
					if (!isMember(currentElement)) {
						return false;
					}
				}
			}
		}
	}
	return true;
}

// The isEquivalence function tests if the StringRelation the function is called on is equivalent or not.
// Equivalence is defined as being simultaneously Transitive, Reflexive, and Symmetric.
bool StringRelation::isEquivalence(){
	if (this->isTransitive() == true && this->isReflexive() == true && this->isSymmetric() == true) {
		// If all of these conditions are true, it is considered equivalent.
		return true;
	}
	return false;
}

//The isFirstComponent function tests if s1, of the form 'a' is the first component of
// s2 which is in the form 'p,q', true is a == p.
bool StringRelation::isFirstComponent(string s1, string s2){
	if (s1[0] == s2[0]) {
		return true;
	}
	return false;
}


// The computeEquivalence class, given a member of set1, determines a class of variables for which the
// 		inserted element directly points to.
SetOfStrings *StringRelation::computeEquivalenceClass(string element){
	// The equivalence class of element n is everything that the input "element" points to.
	SetOfStrings *out = new SetOfStrings();
	int i;
	string currentElement;
	// For each element in the relation, if the input element is the first element;
	// save the second element for output.
	for (i = 0; i < this->size(); i++) {
		currentElement = this->returnElement(i);
		if (isFirstComponent(element, currentElement)) {
			string temp;
			temp = currentElement[2];
			out->insertElement(temp);

		}
	}
	return out;
}

// Dijkstra algorithm implementation
// Input: source node, destination node
// Output: path length (integer)
// Note: the generated path is also stored in "path" variable
int StringRelation::computeShortest(string source, string destination, SetOfStrings* setModel){
	vector<string> vertexSet;			// Set of vertices.
	vector<int> distanceToNode; 		// Set of shortest distance to node.
	vector<string> prevNode;			// Previous node to this one in loop.
	vector<string> isVisited; 			// Contains u or v for un/visited respectively.
	int size = setModel->size();		// Initialise size for all indexing of vectors/arrays.

	// Initialise all arrays and vectors.
	for (int i = 0; i < size; i++) {
		vertexSet.push_back(setModel->returnElement(i));
		distanceToNode.push_back(1000);
		prevNode.push_back("UNDEFINED");
		isVisited.push_back("u");
	}

	// Find the start node and set the distance as zero.
	for (int i = 0; i < size; i++) {
		if (source == setModel->returnElement(i)) {
			distanceToNode.at(i) = 0;
		}
	}

	// Initialise the loop condition that there are still unvisted nodes.
	bool containsUnvisited = true;

	// While there are still unvisited nodes...
	while (containsUnvisited) {
		int minDistanceInQ = 1000;
		int minDistanceIndex;
		// Find the minimum distance index for unvisited nodes.
		for (int i = 0; i < size; i++) {
			if (distanceToNode.at(i) < minDistanceInQ) {
				if (isVisited.at(i) == "u") {
					minDistanceInQ = distanceToNode.at(i); // ye
					minDistanceIndex = i;
				}
			}
		}
		// Make the smallest distance node visited
		isVisited.at(minDistanceIndex) = "v";

		// For each neighbour of this ie. members in the equivalence class...
		SetOfStrings* equivalenceClass = new SetOfStrings();
		equivalenceClass = computeEquivalenceClass(vertexSet.at(minDistanceIndex));
		// Find each neighbour
		for (int i = 0; i < equivalenceClass->size(); i++) {
			// Find neighbours index
			int neighbourIndex = 0;
			for (int j = 0; j < size; j++) {
				if (equivalenceClass->returnElement(i) == vertexSet.at(j)) {
					neighbourIndex = j; // Index of the neighbouring node
				}
			}
			// If the neighbour is unvisited
			if (isVisited.at(neighbourIndex) == "u") {
				string nextRelation = vertexSet.at(minDistanceIndex);
				nextRelation.append(",");
				nextRelation.append(vertexSet.at(neighbourIndex));
				// Find the relation and therefore the weight and calculate the new testing weight.
				int tempNeighbourDistance;
				tempNeighbourDistance = distanceToNode.at(minDistanceIndex) + getWeight(nextRelation);
				if (tempNeighbourDistance < distanceToNode.at(neighbourIndex)) {
					// If this testing weight is less than the previously recorded shortest weight,
					// replace it with this new weight.
					distanceToNode.at(neighbourIndex) = tempNeighbourDistance;
					// Record the node previous to this node for path later on.
					prevNode.at(neighbourIndex) = vertexSet.at(minDistanceIndex);
				}

			}
		}
		// Refresh containsUnvisted, in conjunction with while loop condition
		containsUnvisited = false;
		for (int i = 0; i < size; i++) {
			if (isVisited.at(i) == "u") {
				containsUnvisited = true;
			}
		}
		if (vertexSet.at(minDistanceIndex) == destination) {
			containsUnvisited = false;
		}
	}

	// Find the index of the destination position and extract the weight.
	int endPointIndex = 0;
	int shortestPathWeight = 999;
	for (int i = 0; i < size; i++) {
		if (destination == vertexSet.at(i)) {
			shortestPathWeight = distanceToNode.at(i);
			endPointIndex = i;
		}
	}

	// Assume the weight doesnt equal 1000
	bool isReachable = true;
	if (shortestPathWeight == 1000) {
		isReachable = false;
		// If it does, it was never reached.
	}

	// Only print the next bit if the path is reachable.
	if (isReachable) {
		// Begin string extraction.
		// String extraction will be reversed.
		string shortestPath;
		string point = destination;
		string newPoint = "undefined";
		int pointIndex;
		// Only append points before reaching source node.
		while (point != source) {
			shortestPath.append(point);
			// Find the index of the current node.
			for (int i = 0; i < size; i++) {
				if (point == vertexSet.at(i)) {
					pointIndex = i;
				}
			}
			// Access the prev node to this, setting as the new node.
			newPoint = prevNode.at(pointIndex);
			point = newPoint;
		}
		// Append the source point.
		shortestPath.append(source);

		// Reverse the string to find the non-reversed path.
		string newPath;
		for (int i = shortestPath.size()-1; i > 0; i--) {
			string temp;
			temp = shortestPath[i];
			newPath.append(temp);
			newPath.append(" -> ");
		}
		newPath.append(destination);

		// Set this path as the shortest path and return the weight.
		setPath(newPath);
		return shortestPathWeight;
	} else {
		// 0 is the value for an unreachable condition, to be used for errors.
		return 0;

	}
}

// Function getWeight returns the weight of an edge s.
// Used in Djikstra's shortest algorithm.
int StringRelation::getWeight(string s) {
	for (int i = 0; i < this->size(); i++) {
		if (returnElement(i) == s) {
			return weight.at(i);
		}
	}
	return -1;
}

// Function setPath is a setter for the private variable path.
void StringRelation::setPath(string s) {
	path = s;
}

// Function returnPath is a getter for the private variable path.
string StringRelation::returnPath() {
	return path;
}




