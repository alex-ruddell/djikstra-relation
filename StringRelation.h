#ifndef STRINGRELATION_H_
#define STRINGRELATION_H_
#include "SetOfStrings.h"

class StringRelation : public SetOfStrings{
	private:
		SetOfStrings *set1; // The set over which the relation is created.
	    vector<int> weight; // Vector of integer weights corresponding to each node.
		string path; 		// The return string for storage of Djikstra's path.
    
		// Helper function; splits strings from a,b to a and b stored in separate vector elements.
		vector<string> makeTokens(string input);

		// Helper function; given "a,b", returns "b,a".
		string computeDual(string);

		// Helper function; given string s a reflexive element of "s,s" is returned.
		string createReflexiveElement(string s);

		// Helper function; returns true if string s is in form "a,a".
		bool isReflexiveElement(string s);

		// Helper function, returns true if s1 is first component of s2.
		// Inputs in forms s1 = a and s2 = a,b respectively.
		bool isFirstComponent(string s1, string s2);
		
		// Helper function; returns second component of string s.
		// From format s = a,b to out = b.
		string returnSecondComponent(string s);

	public:
		// setInput takes an input of SetOfStrings and assigns it to the instance object set1.
		void setInput(SetOfStrings *s);

		// isValid tests if the relation instantiated is valid or not, returning a true/false output.
		// A valid relation is one where the relation elements consists only of nodes from set1.
		bool isValid();

		// isReflexive tests if the relation instantiated is reflexive or not, returning a true/false output.
		// A reflexive relation is where for all nodes n in set one, there is a reflexive relation member n,n.
		bool isReflexive();

		// isSymmetric tests if the relation instantiated is symmetric or not, returning a true/false output.
		// A symmetric relation is one where, for each a,b relation member, there is also a b,a member.
		bool isSymmetric();

		// isTransitive tests if the relation instantiated is transitive or not, returning a true/false output.
		// A transitive relation is one where, for each a,b and b,c member, there is also an a,c member.
		bool isTransitive();

		// isEquivalence tests if the relation instantiated is an equivalence relation or not, returning a true/false output.
		// An equivalence relation is one which is simultaneously transitive, symmetric, and reflexive.
		bool isEquivalence();

		// computeEquivalenceClass takes a string input, returning a SetOfStrings output consisting of all
		// 							members within the relation in format a,b, where a is the input argument
		// 							and b is any other node within the relation.
		SetOfStrings *computeEquivalenceClass(string element);
		
		// computeShortest calculates the shortest path between two nodes given inputs source node, destination node,
		//							and all of the nodes within the relation.
		// This algorithm is based on Djikstra's Shortest Path algorithm.
		// The integer output is is the total distance travelled in the shortest path.
		// Path data is stored within the instantiated private member; path.
		int computeShortest(string source, string destination, SetOfStrings* setModel);

		// addWeight stores all the weights of the relation in instantiated relation member weight with index
		//			corresponding to the order in which the relation members were added.
		void addWeight(int s);

		// getWeight returns the weight of an edge based on the input relation member in form a,b.
		// Used as a helper function when running the shortest path algorithm.
		int getWeight(string s);

		// setPath is a helper function used to assign the Djikstra's path to the instantiated object member, 'path'.
		void setPath(string s);

		// returnPath is a getter function for the private object 'path' relating to Djikstra's shortest path alogrithm.
		string returnPath();

};
#endif
