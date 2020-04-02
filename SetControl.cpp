/* This is the controller part for your program.
 * In this file, students are required to complete the "control" logic.
 * The controller accepts keyboard inputs from the user through View, and manipulate data in Model.
 * Then, the result from Model is sent back to user through View.
 * Think about the design before the actual implementation.
 */
#include "SetControl.h"


SetControl::SetControl()
{
	cout <<"Initializing the calculator, please wait! ... \n" << endl;
	// Instantiation of all members.
	setUI = new SetUI();
}

SetControl::~SetControl()
{
	// Destructor, disposes all members.
	setModel = NULL;
	relationModel = NULL;
	delete setUI;
}

bool SetControl::Run()
{
	// String created to collect the input command.
	string command;
	// Invoke the main user interaction.
	while(true)
	{
		// Retrieves command entered by the user.
		command = setUI->GetCommand();
		// Initialise the size of argc.
		int argc = 0;
		// String tokeniser splits arguments separated with spaces for 'command'.
		// This stores the values in argv array while the number of argument is argc.
		vector<string> argv;
		int i = 0;
		size_t found;
		string temp;
		while((found = command.find(" ",i))!=std::string::npos) {
			argv.push_back(command.substr(i,found-i));
			i = found+1;
		}
		argv.push_back(command.substr(i));
		argc = argv.size();
		// *************************
		// ENTER COMMAND EXECUTION *
		// *************************
		if (argc == 0) continue; // Response of system to a null input.
		// ************************
		// HELP COMMAND EXECUTION *
		// ************************
		if (argv.at(0).compare("help")==0){
			// When command is help, display the help user interface.
			setUI->Help();
		}
		// **********************
		// LS COMMAND EXECUTION *
		// **********************
		else if (argv.at(0).compare("ls")==0){
			// Displays the usual system response to an input command of ls.
			if (!(argc == 1 || argc == 2)){setUI->printError("argument"); continue;}
			if (argc == 2){
				string cmd(argv[1]);
				cmd = "ls " + cmd;
				system(cmd.c_str());		
			}		
			else system("ls");
		}
		// *************************
		// CLEAR COMMAND EXECUTION *
		// *************************
		else if (argv.at(0).compare("clear") == 0) {
			// Given the clear command, the welcomem screen is wiped and redisplayed.
			setUI->TopicScreen();
		}
		// ************************
		// OPEN COMMAND EXECUTION *
		// ************************
		else if (argv.at(0).compare("open")==0){
			// Given the open command
			if (!(argc == 2 || argc == 3)) {setUI->printError("argument"); continue;}
			// Storage objects for set and relation are instantiated.
			SetOfStrings *temps = new SetOfStrings();
			StringRelation *tempr = new StringRelation();
			setModel = temps;
			relationModel = tempr;
			if (argc == 2) {
				// If input scheme consisting of no verbose command is entered, read data.
				setUI->ReadFromFile(argv.at(1), setModel, relationModel, false);
			}
			else {
				// If verbose term included, pass into the function to potentially enable printing.
				if (!setUI->ReadFromFile(argv.at(1), setModel, relationModel, (argv.at(2).compare("-v") == 0) ? true:false)) {

					setUI->printError("file"); //print an error message

					continue;
				}
			}
			if (argc == 3) {
				if (argv.at(2) != "-v") {
					setUI->printError("argument");
				}
			}
			// If the file returns a correct reading, print the affirmative message.
			else if (setUI->ReadFromFile(argv.at(1), setModel, relationModel, false)) {
				setUI->printMessage("file read");
			}
			else {
				// Print an error message if the file is not read properly.
				setUI->printError("no file");
			}
		}
		// ************************
		// EXIT COMMAND EXECUTION *
		// ************************
		else if (argv.at(0).find("exit")!=string::npos){
			// Exit the User Interface instance if the exit command is called.
			exit(0);
		}
		// ************************
		// LIST COMMAND EXECUTION *
		// ************************
		else if (argv.at(0).find("list")!=string::npos){
			// Run functionality for when command list is received.
			if (setModel != NULL) {
				setUI->ListMembers(setModel);
				setUI->ListRelations(relationModel);
				setUI->ListWeights(relationModel);
			} else {
				setUI->printError("no set loaded");
			}
		}
		// *************************
		// CHECK COMMAND EXECUTION *
		// *************************
		else if (command.find("check")!=string::npos) {
			if (setModel != NULL) {
				// If the check command is called.
				if (command.find("-r")!=string::npos) {
					// Checking if the relation is reflexive or not, and sending to print data.
					bool relation = relationModel->isReflexive();
					setUI->printRelation('r', relation);
				}
				else if (command.find("-s")!=string::npos) {
					// Checking if the relation is symmetric or not, and sending to print data.
					bool relation = relationModel->isSymmetric();
					setUI->printRelation('s', relation);

				}
				else if (command.find("-t")!=string::npos) {
					// Checking if the relation is transitive or not, and sending to print data.
					bool relation = relationModel->isTransitive();
					setUI->printRelation('t', relation);

				}
				else if (command.find("-e")!=string::npos) {
					// Checking if the relation is equivalent or not, and sending to print data.
					bool relation = relationModel->isEquivalence();
					setUI->printRelation('e', relation);
				}
				else {
					// Print an error message if an unknown relation testing type is entered.
					setUI->printError("argument");
				}
			} else {
				setUI->printError("no set loaded");
			}
		}
		// ***************************
		// EQCLASS COMMAND EXECUTION *
		// ***************************
		else if (argv.at(0).find("eqclass")!=string::npos) {
			if (setModel != NULL) {
				// Given the eqclass command is input
				// Assume that an incorrect argument was entered for the node at argv.at(1)
				// Value 1 corresponds to an incorrect input
				int value = 1;
				SetOfStrings* equivalenceClass = new SetOfStrings;
				if (argc == 2) {
					// Value 2 refers to an input of correct format.
					value = 2;
					string firstNum = argv.at(1);
					equivalenceClass = relationModel->computeEquivalenceClass(firstNum);
					if (relationModel->isEquivalence() == false) {
						// Value of 0 corresponds to an eqclass in a StringRelation that isn't equivalent.
						value = 0;
					}
					if (!setModel->isMember(firstNum)) {
						// Value of -1 corresponds to failure of input being in the set of nodes.
						value = -1;
					}
					// Run the output call, potential errors are called from this print function.
					setUI->printEqClass(value, equivalenceClass, argv.at(1));
				} else {
					// If the argument input was incorrect, an error is printed.
					setUI->printError("argument");
				}
			} else {
				setUI->printError("no set loaded");
			}
		}
		// ************************
		// PATH COMMAND EXECUTION *
		// ************************
		else if (argv.at(0).find("path")!=string::npos) {
			if (setModel != NULL) {
				// Given the input of the path command;
				if (argc != 3) {
					// Print an error if the wrong number of arguments are entered.
					setUI->printError("argument");
				} else {
					// Else, begin the algorithm.
					// Source and Destination nodes extracted from the input command.
					string source = argv.at(1);
					string destination = argv.at(2);
					if (source == destination) {
						// Djikstra algorithm cannot handle a case where source = destination, print error.
						setUI->printError("source=destination");
					} else if ((!setModel->isMember(source)) || (!setModel->isMember(destination))) {
						// Else, if either of the source or destination are not nodes, print error.
						setUI->printError("no member");
					} else {
						// Continue with the algorithm if correct input is obtained.
						// computeShortest called to calculate the shortest path.
						int pathOut = relationModel->computeShortest(source, destination, setModel);
						if (pathOut == 0) {
							// If a pathOut value is no obtained, print an error.
							setUI->printError("no path");
						} else {
							// If a non zero integer is obtained, print the shortest path.
							setUI->printShortestPath(pathOut, relationModel->returnPath());
						}
					}
				}
			} else {
				setUI->printError("no set loaded");
			}

		}
		// *****************************
		// REACHABLE COMMAND EXECUTION *
		// *****************************
		else if (argv.at(0).find("reachable")!=string::npos) {
			if (setModel != NULL) {
				// Given the input command of reachable.
				if (argc != 3) {
					// Print an error if the wrong number of inputs is entered.
					setUI->printError("argument");
				} else {
					// Else, extract the data for source and destination node.
					string source = argv.at(1);
					string destination = argv.at(2);
					if (source == destination) {
						// If the source node is equal to the destination node, return reachable.
						setUI->printMessage("reachable same index");
					} else if ((!setModel->isMember(argv.at(1))) || (!setModel->isMember(argv.at(2)))) {
						// If either of the source or destination nodes entered are not set members, print an error.
						setUI->printError("no member");
					}
					// If everything is formatted correctly however;
					else {
						// Perform Djikstra's to see if the node is reachable.
						// Reachable functionality performed by Djikstra's algorithm.
						int pathOut = relationModel->computeShortest(source, destination, setModel);
						if (pathOut == 0) {
							// If there was no output path, not reachable.
							setUI->printError("no path");
						} else {
							// Else, print the path is reachable.
							setUI->printMessage("reachable");
						}
					}
				}
			} else {
				setUI->printError("no set loaded");
			}
		}
		// ***************************
		// INVALID COMMAND EXECUTION *
		// ***************************
		else{
			// Print error based on the unknown command.
			setUI->printError("command");
		}
	}
	return true;
}



