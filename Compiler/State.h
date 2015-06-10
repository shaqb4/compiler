#ifndef STATE_H
#define STATE_H

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;
using std::vector;
using std::pair;


enum class StateType { START_STATE, INTEGER_STATE, IDENTIFIER_STATE, WHITESPACE_STATE, ERROR_STATE, END_OF_TOKEN_STATE, EOF_STATE, SYMBOL_STATE };

struct TransitionRange
{
	pair<char, char> range;
	StateType state;

	TransitionRange();
	TransitionRange(char start, char end, StateType state);
	TransitionRange(pair<char, char> range, StateType state);
};

/*
* A State in the Lexer DFA
* The name property holds the token type (i.e. "integer", "identifier")
*/
class State
{
public:

	StateType type;
	StateType failState;

	unordered_map<char, StateType> transitions;
	vector<TransitionRange> ranges; //i.e 'a' and 'z' could be a range to check against

	State(StateType type, StateType fail = StateType::END_OF_TOKEN_STATE);

	~State(){}
	
	void addTransitions(string inputs, StateType state);

	void addTransition(char input, StateType state);

	void addRange(TransitionRange& range);

	StateType getTransition(char input);
};

#endif