// vim:ts=8:noexpandtab
/* This file declares the slrParser class and its methods. */
#ifndef SLR_PARSER_INCLUDED
#define SLR_PARSER_INCLUDED

#include <LexicalAnalyser.h>
#include <LR0Automaton.h>
#include <stack>
#include <ParserFunctions.hpp>

using std::stack;

class SLRParser 
{
	public:
		// Public Data structures
		enum Action { None, Shift, Reduce, Accept};
		struct ActionVal 	// Unable to use Union
		{
			const Item* reduceRule;
			ItemSet* shiftTo;
		};
		typedef pair<Action, ActionVal> ActionArgPair;

		// Constructor
		SLRParser (char * lexFile, char * grammarFile);

		/* Call this function to parse. The output is printed directly.*/
		void parse (ifstream& inputFile);
		
		/* Function to print the canonicalCollection of LR0Automaton */
		void printCanonicalCollection ();
	private:
		// Private variables
		map<ItemTerminalPair, ActionArgPair> ACTION; 
		LR0Automaton lr0automaton;
		ItemSet * startSet;
		LexicalAnalyser lex;
		stack<ItemSet*> parseStack;
		FirstSet firstSet;
		FollowSet followSet;
		
		// Private functions

		/* Function to construct the ACTION table.
		 * This function populates the ACTION variable.
		 */
		void constructActionTable ();

		/* This function finally adds the ACTION to the table. 
		 * This function is also responsible for detecting if the grammar
		 * is not SLR(1). It throws an exception (still TODO).
		 */
		void addToActionTable (ItemSet* curItemSet, const string& Terminal,
					Action action, const Item* reduceRule,
					ItemSet* shiftTo);
};

#endif	// End of file
