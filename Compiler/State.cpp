#include "State.h"

TransitionRange::TransitionRange()
{
	
}

TransitionRange::TransitionRange(char start, char end, StateType state)
{
	this->range.first = start;
	this->range.second = end;
	this->state = state;
}

TransitionRange::TransitionRange(pair<char, char> range, StateType state)
{
	this->range = range;
	this->state = state;
}

/*
* A State in the Lexer DFA
* The name property holds the token type (i.e. "integer", "identifier")
*/

State::State(StateType type, StateType fail)
{
	this->type = type;
	this->failState = fail;
}

void State::addTransitions(string inputs, StateType state)
{
	for (int i = 0; i < inputs.length(); i++)
	{
		transitions[inputs[i]] = state;
	}
}

void State::addTransition(char input, StateType state)
{
	transitions[input] = state;
}

void State::addRange(TransitionRange& range)
{
	ranges.push_back(range);
}

StateType State::getTransition(char input)
{
	//Check if the input char is in one of the ranges such as 'a'-'z' or '0'-'9'
	for (auto &transitionRange : ranges)
	{
		if (transitionRange.range.first <= input && input <= transitionRange.range.second)
		{
			return transitionRange.state;
		}
	}

	//If the input is not in a range, check if the transition exists in the map(transition table)
	//If it does, return the transition, otherwise return the fail state (probably ERROR_STATE, END_OF_TOKEN_STATE, or EOF_STATE)
	unordered_map<char, StateType>::iterator it;
	it = transitions.find(input);
	if (it != transitions.end())
	{
		return it->second;
	}
	else
	{
		return failState;
	}
}
