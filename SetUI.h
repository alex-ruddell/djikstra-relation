#ifndef __SetUI__
#define __SetUI__

#include "StringRelation.h"
#include "SetOfStrings.h"
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;
enum COLOR {RED=0, BLUE, GREEN, WHITE, YELLOW, PURPLE};

class SetUI
{
private:
	//helper function to enable colorful console printouts.
	//COLOR is defined as enum.
	//Takes a string as an input, then return the same string in a different color.
	string ColorText(string s, COLOR color);

	//helper function that takes an input string and split it into parts (e.g., "5->3" becomes '5' and '3').
	//If this relation is a valid binary relation, then add this relation to the 'relation' set.
	//Return true if nothing went wrong, else return false.
	bool getFromLine(SetOfStrings *set, StringRelation *relation, string line);

public:
	//constructor
	SetUI();

	//print function for the top banner message.
	//it should include the developer name (i.e., your name)
	void TopicScreen();

	//all the error messages are predefined in this function so that they can be
	//called by controller whenever an error is detected.
	void printError(string reason);

	//all non error messages printed through here
	//called by controller in a more robust way
	void printMessage(string argument);

	//print help
	void Help();

	//reads the keyboard inputs from user
	string GetCommand();

	//List all the members in the set of strings.
	//Returns 0 if there is nothing in the model.
	void ListMembers(SetOfStrings* model);

	//List all the members in the set of relations.
	//Return 0 if there is nothing in the relation model.
	void ListRelations(StringRelation* model);

	//List all weights relating to the stringrelation indices.
	//Return 0 if there is nothing in the weight vector.
	void ListWeights(StringRelation* model);


	void printEquivalenceClass(string member, SetOfStrings* ss);

	//methods for reading an input text file.
	//Given a filename, it opens the file and reads the graph.
	//Return false if there is an error while reading the file.
	//While reading the file, it stores data in *ss and *sr appropriately.
	//When verbose option is true, it prints ALL the lines in the file.
	bool ReadFromFile(string filename, SetOfStrings *ss, StringRelation *sr, bool verbose);

	// method for printing the result of Dijkstra's algorithm applied to the input graph
	// the distance is the shortest distance to the destination
	// the path is a string which contains the path information in the format "a -> b -> ... -> z"
	void printShortestPath(int distance, string path);

	// relation printing tool for -e, -s, -t, and -r
	// takes relationType of letter and corresponding isTrue boolean input
	// output is a +ve or -ve message based on the relation type give by
	// char: 	e = equivalent
	//			s = symmetric
	// 			t = transitive
	//			r = reflexive
	void printRelation(char relationType, bool isTrue);

	// Print function for equivalence class search
	// For example, when 'eqclass 0' command is entered to the program, then
	// the printout should look like this: e.g., [0] = {1,2,3,4} where 1,2,3,4 are
	// all having equivalence relation with 0.
	void printEqClass(int value, SetOfStrings* equivalenceClass, string eqClassVal);

};

#endif
