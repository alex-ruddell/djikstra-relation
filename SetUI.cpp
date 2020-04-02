#include "SetUI.h"

SetUI::SetUI()
{
	TopicScreen();
}

// Greet the user and shows the developer name.
void SetUI::TopicScreen()
{
	system("clear");
	cout <<"----------------------------------------------------------------------"<< endl; // Replace the name with yours
	cout <<"\033[1;31mSet Calculator\033[0m\nDeveloper Name: " << "\033[1;34mAlex Ruddelll (arud699, 866097052)\033[0m\n";
	cout <<"To know available commands, please type 'help'" << endl;
	cout <<"---------------------------------------------------------------------"<< endl;
}

// Command to read data from a text file.
bool SetUI::ReadFromFile(string filename, SetOfStrings *ss, StringRelation *sr, bool verbose)
{
	// Instantiate the items to return lines of the text file.
	string line;
	ifstream infile (filename.c_str());

	// Return false if the file line doesn't exist.
	if (!infile.good()) return false;

	// Get the first line to extract nodes.
	getline(infile,line);

	// Print the line if the verbose option is enabled.
	if (verbose) {
		cout << line << endl;
	}

	line.erase(0,2); // Remove '//' in the line

	// Instantiates a string to retrieve data.
	vector<string> element;
	int i = 0;
	size_t found;

	// Finds the nodes from the relevant starting line.
	while((found = line.find(",",i))!=std::string::npos) {
		element.push_back(line.substr(i,found-i));
		string insertString = line.substr(i,found-i);
		// Insert the retrieved node.
		ss->insertElement(insertString);
		i = found+1;	
	}
	// Insert the final piece of data.
	element.push_back(line.substr(i));
	string insertString = line.substr(i);
	ss->insertElement(insertString);

	// Bypasses the second line of irrelevant data.
	getline(infile,line);

	// Read the rest of the file.
	while (getline(infile,line)){
		// Pint the line if the verbose condition is enabled.
		if (verbose) {
			cout << line << endl;
		}

		// Removes all the spaces from the line for you.
		line.erase(remove(line.begin(), line.end(), ' '), line.end());

		// Find } as the finisher for file reading.
		if (line.find("}")!=string::npos) break; 
		// Fetch set and relation in the line.
		if (!getFromLine(ss, sr, line)) return false;

	}
	// Finish reading the file.
	infile.close();
	// Set ss as the sr input.
	sr->setInput(ss);	
	// Returns file read correctly.
	return true;
}

// Tool used to get data from a line of a text file.
bool SetUI::getFromLine(SetOfStrings *ss, StringRelation *sr, string line){
	vector<string> element;
	int i = 0;
	size_t found;
	// Find the position in the line of -> and then go back one space to find the first digit.
	while((found = line.find("->",i))!=std::string::npos) {
		// Add the first digit to element string.
		element.push_back(line.substr(i,found-i));
		i = found+2;
	}
	// Add the second digit to the string.
	element.push_back(line.substr(i,line.find("[",i)-i));

	// Make the relation to add to the file.
	string makeRelation;
	makeRelation.append(element[0]);
	makeRelation.append(",");
	makeRelation.append(element[1]);

	// Find the weight information and store in temp.
	int weightPos = line.find("=", 0);
	weightPos += 2;
	string temp = line.substr(weightPos,1);

	// Element consists of two nubers, xy, and NO COMMA!
	SetOfStrings productString = *ss->product(ss);

	// If the relation isn't a legitimate one.
	if (!productString.isMember(makeRelation)) {
		return false;
	}

	// If the relation is legit, insert the string.
	sr->insertElement(makeRelation);

	// Convert weight to int value and insert into the weight array.
	int weightNum = atoi(temp.c_str());
	sr->addWeight(weightNum);

	// If you make it to here, the line has been read correctly.
	return true;
}

// Tool to print an error based on the reason input.
void SetUI::printError(string reason)
{
	// cout << "  The shortest path distance: " << ColorText(to_string(distance),GREEN) << endl;
	// Print an error message if the wrong reason is input into the function.
	if (reason.compare("command") == 0){
		string print = " Command cannot be understood. Please enter help to see the available commands";
		cout << ColorText(print,RED) << endl;
	}

	// Error message for when incorrect argument is input into a function.
	else if (reason.compare("argument") == 0){
		string print = "  Incorrect command arguments!\n  Please type help to know about the command arguments";
		cout << ColorText(print,RED) << endl;
	}

	// Error message for when an incorrect member is input.
	else if (reason.compare("no member") == 0) {
		string print = "  The requested member does not exist in this set\n  Please type list to know about existing strings";
		cout << ColorText(print,RED) << endl;
	}

	// Error message for when the source and destination inputs to Djikstra are equal.
	else if (reason.compare("source=destination") == 0) {
		string print = "  Djikstra's algorithm cannot handle (source == destination)\n  The shortest path distance: 0";
		cout << ColorText(print,RED) << endl;
	}

	// Error message for when no path is returned.
	else if (reason.compare("no path") == 0) {
		string print = "  Unreachable!";
		cout << ColorText(print,RED) << endl;
	}

	// Error message for when a file is incorrectly read.
	else if (reason.compare("no file") == 0) {
		string print = "  Error occurred while reading the input file. Possible reasons:\n  1. File does not exist\n  2. Contains an invalid graph\n  3. Unreadable data\n  Graph could not be loaded successfully";
		cout << ColorText(print,RED) << endl;
	}

	// Errror message for when a set fails to load.
	else if (reason.compare("no set loaded") == 0) {
		string print = "  There is no set loaded to the program.\n  Please open a file using 'open' command!";
		cout << ColorText(print,RED) << endl;
	}

	// Error message for when an equivalence class error occurs.
	else if (reason.compare("eqclass error") == 0) {
		string print = "  Equivalence class request could not be executed\n  Possibly the string does not exist in the set or there is no equivalence relation";
		cout << ColorText(print,RED) << endl;
	}
}

// Tool to print a message to the user interface, variant of printError for non-error messages.
void SetUI::printMessage(string argument) {
	// Given the input argument, print relevant error message.
	// Djikstra Algortithm prints when the source and destination index are equal in the input stage.
	if (argument.compare("reachable same index") == 0) {
		string print = "  Djikstra's algorithm cannot handle (source == destination)\n  The shortest path distance: ";
		cout << print << ColorText("0",GREEN) << endl;
	}
	// Successful file read message produced to the user.
	else if (argument.compare("file read") == 0) {
		string print = "  File reading was successsful\n  Please type 'list' to view the members and relations defined in the graph\n";
		string print1 = "  If a directory is opened instead of a file, the program will generate incorrect outputs";
		cout << ColorText(print,GREEN) << ColorText(print1,PURPLE) << endl;
	}
	// If two points are reachable as decided by Djikstra.
	else if (argument.compare("reachable") == 0) {
		string print = "  Reachable!";
		cout << ColorText(print,GREEN) << endl;
	}
}

// Tool to retrieve command entered to the user interface by the operator.
string SetUI::GetCommand()
{
	string commandInput;
	cout << ">> ";
	// Retrieves command from the user.
	getline (cin, commandInput);
	return commandInput;
}

// Tool to print the shortest path found by the Djikstra algorithm to the user interface.
void SetUI::printShortestPath(int distance, string path) {
	cout << "  The shortest path distance: " << ColorText(to_string(distance),GREEN) << endl;
	cout << "  The path is: " << ColorText(path, BLUE) << endl;
}

// Tool to change the colour of text for output.
string SetUI::ColorText(string s, COLOR color)
{
	// temp string instantiated to be the return.
	string temp;
	// Switch case used to apply colour.
	switch (color) {
	case RED: temp = "\033[1;31m" + s + "\033[0m"; break;
	case BLUE: temp = "\033[1;34m" + s + "\033[0m"; break;
	case YELLOW: temp = "\033[1;33m" + s + "\033[0m"; break;
	case GREEN: temp = "\033[1;32m" + s + "\033[0m"; break;
	case WHITE: temp = "\033[1;37m" + s + "\033[0m"; break;
	case PURPLE: temp = "\033[1;35m" + s + "\033[0m"; break;
	default: temp = "\033[0m" + s; break;
	}
	// Output string returned.
	return temp;
}

// Tool to print members to the user interface.
void SetUI::ListMembers(SetOfStrings* model)
{
	// Prints opening statement.
	cout << "  The members of the " << ColorText("sets",BLUE) << " are... " << endl << "  => {";
	int i;
	if (model->size() > 0) {
		// Prints all elements.
		for (i = 0; i < model->size()-1; i++) {
			cout << ColorText(model->returnElement(i),BLUE) << ", ";
		}
		// Print final element and closing braces.
		cout << ColorText(model->returnElement(i),BLUE) << "}" << endl;
	}
}

// Tool to print relations to the user interface.
void SetUI::ListRelations(StringRelation* model)
{
	// Prints opening statements.
	cout << "  The members of the " << ColorText("relation",YELLOW) << " are... " << endl << "  => {";
	int i;
	if (model->size() > 0) {
		// Prints all elemnts.
		for (i = 0; i < model->size()-1; i++) {
			cout << "(" << ColorText(model->returnElement(i),YELLOW) << ")" << ", ";
		}
		// Prints final element and closing braces.
		cout << "(" << ColorText(model->returnElement(i),YELLOW) << ")" << "}" << endl;
	}
}

// Tool to print weights to the user interface.
void SetUI::ListWeights(StringRelation* model)
{
	cout << "  The associated " << ColorText("weights",PURPLE) << " are... " << endl << "  => {";
	int i;
	for (i = 0; i < model->size()-1; i++) {
		int weight = model->getWeight(model->returnElement(i));
		cout <<  ColorText(to_string(weight),PURPLE) << ", ";
	}
	int weight = model->getWeight(model->returnElement(i));
	cout << ColorText(to_string(weight),PURPLE) << "}" << endl;
}

// Tool to print relation to the User Interface.
void SetUI::printRelation(char relationType, bool isTrue)
{
	// Use switch case to print the relevant relation type.
	string print;
	switch (relationType) {
	case 'r' :
		print = "reflexive. ";
		break;

	case 't' :
		print = "transitive. ";
		break;

	case 's' :
		print = "symmetric. ";
		break;

	case 'e' :
		print = "equivalent. ";
		break;
	}
	if (isTrue) {
		// For when the relation is true.
		cout << ColorText("  => It is ",GREEN) << ColorText(print,GREEN) << endl;
	} else {
		// If false, print relevant output.
		cout << ColorText("  => This relation is not ",RED) << ColorText(print,RED) << endl;
	}
}

// Prints the equivalence class of given value eqClassVal, error input of value is provided.
void SetUI::printEqClass(int value, SetOfStrings* equivalenceClass, string eqClassVal) {
	if (value == 0 || value == -1) {
		// Values 0 and -1 correspond to internal errors.
		printError("eqclass error");
	} else if (value == 1) {
		// Value 1 corresponds to incorrect argument input.
		printError("argument");
	} else {
		// Else, prints the equivalence class in correct format.
		string classElement = equivalenceClass->returnElement(1);
		// Prints the value for which the equivalence class has been calculated for.
		cout << "  => [" << ColorText(eqClassVal,BLUE) << "] = {";
		int i;
		for (i = 0; i < equivalenceClass->size()-1; i++) {
			classElement = equivalenceClass->returnElement(i);
			cout << ColorText(classElement,YELLOW) << ", ";
		}
		// Prints final element and closingn braces.
		classElement = equivalenceClass->returnElement(i);
		cout << ColorText(classElement,YELLOW) << "}" << endl;
	}
}

// Prints the help data to the User Interface.
void SetUI::Help()
{
	cout << "Currently available commands:\n";
	cout << "Anything inside <> bracket is an optional argument, while [] bracket contains a must argument.\n\n";
	cout << left << setw(45) << ColorText("	help", RED) << left << setw(50) << "Show help." << endl << endl;
	cout << left << setw(45) << ColorText("	ls <path> ", RED) << left << setw(50) << "Identical to the ls shell command. If a path is given, then" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "the program returns all the files in that path." << endl << endl;
	cout << left << setw(45) << ColorText("	clear ", RED) << left << setw(50) << "Identical to the clear shell command. Clear the screen." << endl << endl;
	cout << left << setw(45) << ColorText("	open [file_path] <-v>", RED) << left << setw(50) << "Open a file. If the file does not exist, then program returns" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "an error message. If -v (verbose) option is enabled (e.g., open a.txt -v)," << endl;
	cout << left << setw(41) << "" << left << setw(50) << "then each line in the file is printed on console while reading." << endl << endl;
	cout << left << setw(45) << ColorText("	list", RED) << left << setw(50) << "List all the members of set and relation." << endl << endl;
	cout << left << setw(45) << ColorText("	check [OPTION] ", RED) << left << setw(50) << "Check the relation. The option has to be provided. Options are:" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "-r (reflexive)" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "-s (symmetric)" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "-t (transtivie)" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "-e (equivalence relation)" << endl << endl;
	cout << left << setw(45) << ColorText("	eqclass [VALUE]", RED) << left << setw(50) << "Show equivalence class of the given [VALUE = Set member]." << endl;
	cout << left << setw(41) << "" << left << setw(50) << "If VALUE is not a member of set, then the program returns" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "an error message." << endl << endl;
	cout << left << setw(45) << ColorText("	reachable [VALUE1] [VALUE2]", RED) << left << setw(50) << "This command checks if two given members are connected to each other" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "If any of VALUE1 and VALUE2 is not a member of the set, then it" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "returns an error message." << endl << endl;
	cout << left << setw(45) << ColorText("	path [VALUE1] [VALUE2]", RED) << left << setw(50) << "Apply Dijkstra algorithm to find the shortest path." << endl;
	cout << left << setw(41) << "" << left << setw(50) << "VALUE1 and VALUE2 are members of the set. VALUE1 is the starting node, and VALUE2 is the destination." << endl << endl;
	cout << left << setw(45) << ColorText("	exit", RED) << left << setw(50) << "Terminate the program." << endl;
	cout << "\n\n";
}
