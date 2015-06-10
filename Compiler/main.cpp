#include<chrono>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include "State.h"

using std::string;
using std::map;
using std::unordered_map;
using std::ifstream;
using std::unique_ptr;
using std::cout;
using std::tr1::unordered_set;

enum class TOKEN {IDENTIFIER, INTEGER, FLOAT, EQ, EQEQ, OPEN_PAREN, CLOSE_PAREN, OPEN_BRACE, CLOSE_BRACE, PLUS, MINUS, TIMES, DIVIDE, IF, ELSE, WHILE, FOR, SEMICOLON, ERROR, 
	WHITESPACE, EOFTOKEN};

class Token
{
public:
	TOKEN tok;
	string type;
	string value;

	void print()
	{
		cout << value << " is a(n) " << type << " of token " << (int)tok << "\n";
	}
};

/*
* The starting state of the DFA. It transitions to the Integer state if given a digit, the Identifier state if given an alphabetic caracter,
* the WhiteSpace state if given a white space character, or the Error state otherwise.
*/
/*class StartState : public State
{
public:
	StartState()
	{
		this->name = "start";

		//digits [0-9]
		transitions['0'] = StateType::INTEGER;
		transitions['1'] = StateType::INTEGER;
		transitions['2'] = StateType::INTEGER;
		transitions['3'] = StateType::INTEGER;
		transitions['4'] = StateType::INTEGER;
		transitions['5'] = StateType::INTEGER;
		transitions['6'] = StateType::INTEGER;
		transitions['7'] = StateType::INTEGER;
		transitions['8'] = StateType::INTEGER;
		transitions['9'] = StateType::INTEGER;

		//alphabet [a-zA-Z] and '_'
		transitions['_'] = StateType::IDENTIFIER;
		transitions['a'] = StateType::IDENTIFIER;
		transitions['b'] = StateType::IDENTIFIER;
		transitions['c'] = StateType::IDENTIFIER;
		transitions['d'] = StateType::IDENTIFIER;
		transitions['e'] = StateType::IDENTIFIER;
		transitions['f'] = StateType::IDENTIFIER;
		transitions['g'] = StateType::IDENTIFIER;
		transitions['h'] = StateType::IDENTIFIER;
		transitions['i'] = StateType::IDENTIFIER;
		transitions['j'] = StateType::IDENTIFIER;
		transitions['k'] = StateType::IDENTIFIER;
		transitions['l'] = StateType::IDENTIFIER;
		transitions['m'] = StateType::IDENTIFIER;
		transitions['n'] = StateType::IDENTIFIER;
		transitions['o'] = StateType::IDENTIFIER;
		transitions['p'] = StateType::IDENTIFIER;
		transitions['q'] = StateType::IDENTIFIER;
		transitions['r'] = StateType::IDENTIFIER;
		transitions['s'] = StateType::IDENTIFIER;
		transitions['t'] = StateType::IDENTIFIER;
		transitions['u'] = StateType::IDENTIFIER;
		transitions['v'] = StateType::IDENTIFIER;
		transitions['w'] = StateType::IDENTIFIER;
		transitions['x'] = StateType::IDENTIFIER;
		transitions['y'] = StateType::IDENTIFIER;
		transitions['z'] = StateType::IDENTIFIER;
		transitions['A'] = StateType::IDENTIFIER;
		transitions['B'] = StateType::IDENTIFIER;
		transitions['C'] = StateType::IDENTIFIER;
		transitions['D'] = StateType::IDENTIFIER;
		transitions['E'] = StateType::IDENTIFIER;
		transitions['F'] = StateType::IDENTIFIER;
		transitions['G'] = StateType::IDENTIFIER;
		transitions['H'] = StateType::IDENTIFIER;
		transitions['I'] = StateType::IDENTIFIER;
		transitions['J'] = StateType::IDENTIFIER;
		transitions['K'] = StateType::IDENTIFIER;
		transitions['L'] = StateType::IDENTIFIER;
		transitions['M'] = StateType::IDENTIFIER;
		transitions['N'] = StateType::IDENTIFIER;
		transitions['O'] = StateType::IDENTIFIER;
		transitions['P'] = StateType::IDENTIFIER;
		transitions['Q'] = StateType::IDENTIFIER;
		transitions['R'] = StateType::IDENTIFIER;
		transitions['S'] = StateType::IDENTIFIER;
		transitions['T'] = StateType::IDENTIFIER;
		transitions['U'] = StateType::IDENTIFIER;
		transitions['V'] = StateType::IDENTIFIER;
		transitions['W'] = StateType::IDENTIFIER;
		transitions['X'] = StateType::IDENTIFIER;
		transitions['Y'] = StateType::IDENTIFIER;
		transitions['Z'] = StateType::IDENTIFIER;

		//spaces ' ', '\n', '\t'
		transitions[' '] = StateType::WHITESPACE;
		transitions['\n'] = StateType::WHITESPACE;
		transitions['\t'] = StateType::WHITESPACE;

		//operators and symbols
		transitions['='] = StateType::SYMBOL;
		transitions['('] = StateType::SYMBOL;
		transitions[')'] = StateType::SYMBOL;
		transitions['{'] = StateType::SYMBOL;
		transitions['}'] = StateType::SYMBOL;
		transitions['+'] = StateType::SYMBOL;
		transitions['-'] = StateType::SYMBOL;
		transitions['*'] = StateType::SYMBOL;
		transitions['/'] = StateType::SYMBOL;
		transitions[';'] = StateType::SYMBOL;

		//EOF
		transitions[EOF] = StateType::EOFTOKEN;
	}

	~StartState(){}

	StateType getTransition(char input)
	{
		unordered_map<char, StateType>::iterator it;
		it = transitions.find(input);
		if (it != transitions.end())
		{
			return it->second;
		}
		else
		{
			return StateType::ERROR;
		}
	}
};*/

/*
* The Symbol state of the DFA. It transitions to the Symbol state if given a valid operator/symbol, or the EndOfToken state otherwise.
*/
/*class SymbolState : public State
{
public:
	SymbolState()
	{
		this->name = "symbol";

		//digits [0-9]
		transitions['='] = StateType::SYMBOL;
		transitions['('] = StateType::SYMBOL;
		transitions[')'] = StateType::SYMBOL;
		transitions['{'] = StateType::SYMBOL;
		transitions['}'] = StateType::SYMBOL;
		transitions['+'] = StateType::SYMBOL;
		transitions['-'] = StateType::SYMBOL;
		transitions['*'] = StateType::SYMBOL;
		transitions['/'] = StateType::SYMBOL;
		transitions[';'] = StateType::SYMBOL;
	}

	~SymbolState(){}
};*/

/*
* The Integer state of the DFA. It transitions to the Integer state if given a digit, or the EndOfToken state otherwise.
*/
/*class IntegerState : public State
{
public:
	IntegerState()
	{
		this->name = "integer";

		//digits [0-9]
		transitions['0'] = StateType::INTEGER;
		transitions['1'] = StateType::INTEGER;
		transitions['2'] = StateType::INTEGER;
		transitions['3'] = StateType::INTEGER;
		transitions['4'] = StateType::INTEGER;
		transitions['5'] = StateType::INTEGER;
		transitions['6'] = StateType::INTEGER;
		transitions['7'] = StateType::INTEGER;
		transitions['8'] = StateType::INTEGER;
		transitions['9'] = StateType::INTEGER;
	}

	~IntegerState(){}
};*/

/*
* The Identifier state of the DFA. It transitions to the Identifier state if given an alphabetic caracter or an underscore ('_'), 
* or the EndOfToken state otherwise.
*/
/*class IdentifierState : public State
{
public:
	IdentifierState()
	{
		this->name = "identifier";

		//digits [0-9]
		transitions['0'] = StateType::IDENTIFIER;
		transitions['1'] = StateType::IDENTIFIER;
		transitions['2'] = StateType::IDENTIFIER;
		transitions['3'] = StateType::IDENTIFIER;
		transitions['4'] = StateType::IDENTIFIER;
		transitions['5'] = StateType::IDENTIFIER;
		transitions['6'] = StateType::IDENTIFIER;
		transitions['7'] = StateType::IDENTIFIER;
		transitions['8'] = StateType::IDENTIFIER;
		transitions['9'] = StateType::IDENTIFIER;

		//alphabet [a-zA-Z] and '_'
		transitions['_'] = StateType::IDENTIFIER;
		transitions['a'] = StateType::IDENTIFIER;
		transitions['b'] = StateType::IDENTIFIER;
		transitions['c'] = StateType::IDENTIFIER;
		transitions['d'] = StateType::IDENTIFIER;
		transitions['e'] = StateType::IDENTIFIER;
		transitions['f'] = StateType::IDENTIFIER;
		transitions['g'] = StateType::IDENTIFIER;
		transitions['h'] = StateType::IDENTIFIER;
		transitions['i'] = StateType::IDENTIFIER;
		transitions['j'] = StateType::IDENTIFIER;
		transitions['k'] = StateType::IDENTIFIER;
		transitions['l'] = StateType::IDENTIFIER;
		transitions['m'] = StateType::IDENTIFIER;
		transitions['n'] = StateType::IDENTIFIER;
		transitions['o'] = StateType::IDENTIFIER;
		transitions['p'] = StateType::IDENTIFIER;
		transitions['q'] = StateType::IDENTIFIER;
		transitions['r'] = StateType::IDENTIFIER;
		transitions['s'] = StateType::IDENTIFIER;
		transitions['t'] = StateType::IDENTIFIER;
		transitions['u'] = StateType::IDENTIFIER;
		transitions['v'] = StateType::IDENTIFIER;
		transitions['w'] = StateType::IDENTIFIER;
		transitions['x'] = StateType::IDENTIFIER;
		transitions['y'] = StateType::IDENTIFIER;
		transitions['z'] = StateType::IDENTIFIER;
		transitions['A'] = StateType::IDENTIFIER;
		transitions['B'] = StateType::IDENTIFIER;
		transitions['C'] = StateType::IDENTIFIER;
		transitions['D'] = StateType::IDENTIFIER;
		transitions['E'] = StateType::IDENTIFIER;
		transitions['F'] = StateType::IDENTIFIER;
		transitions['G'] = StateType::IDENTIFIER;
		transitions['H'] = StateType::IDENTIFIER;
		transitions['I'] = StateType::IDENTIFIER;
		transitions['J'] = StateType::IDENTIFIER;
		transitions['K'] = StateType::IDENTIFIER;
		transitions['L'] = StateType::IDENTIFIER;
		transitions['M'] = StateType::IDENTIFIER;
		transitions['N'] = StateType::IDENTIFIER;
		transitions['O'] = StateType::IDENTIFIER;
		transitions['P'] = StateType::IDENTIFIER;
		transitions['Q'] = StateType::IDENTIFIER;
		transitions['R'] = StateType::IDENTIFIER;
		transitions['S'] = StateType::IDENTIFIER;
		transitions['T'] = StateType::IDENTIFIER;
		transitions['U'] = StateType::IDENTIFIER;
		transitions['V'] = StateType::IDENTIFIER;
		transitions['W'] = StateType::IDENTIFIER;
		transitions['X'] = StateType::IDENTIFIER;
		transitions['Y'] = StateType::IDENTIFIER;
		transitions['Z'] = StateType::IDENTIFIER;
	}

	~IdentifierState(){}
};*/

/*
* The WhiteSpace state of the DFA. It transitions to the Integer state if given a digit, the Identifier state if given an alphabetic caracter,
* the WhiteSpace state if given a white space character, or the or the EndOfToken state otherwise.
*/
/*class WhiteSpaceState : public State
{
public:
	WhiteSpaceState()
	{
		this->name = "whitespace";

		//spaces ' ', '\n', '\t'
		transitions[' '] = StateType::WHITESPACE;
		transitions['\n'] = StateType::WHITESPACE;
		transitions['\t'] = StateType::WHITESPACE;
	}

	~WhiteSpaceState(){}
};*/

/*
* The EndOfToken state of the DFA. It transitions only to the EndOfToken state, but should never have to transition. If this state is reached, the lexer should stop reading
* the token.
*/
/*class EndOfTokenState : public State
{
public:
	EndOfTokenState()
	{
		this->name = "endoftoken";
	}

	~EndOfTokenState(){}

	StateType getTransition(char input)
	{
		return StateType::ENDOFTOKEN;
	}
};*/

/*
* The EOF state of the DFA. It transitions only to the EOF state, but should never have to transition. If this state is reached, the lexer should stop reading
* the token.
*/
/*class EOFState : public State
{
public:
	EOFState()
	{
		this->name = "eof";
	}

	~EOFState(){}

	StateType getTransition(char input)
	{
		return StateType::EOFTOKEN;
	}
};*/

/*
* The Error state of the DFA. It transitions only to the Error state, but should never have to transition. If this state is reached, the lexer should stop reading
* the token
*/
/*class ErrorState : public State
{
public:
	ErrorState()
	{
		this->name = "error";
	}

	~ErrorState(){}

	StateType getTransition(char input)
	{
		return StateType::ERROR;
	}
};*/

class Lexer
{
public:
	StateType currentState, nextState;
	int pos, lineNumber;
	string buffer;

	//Initialize the input character
	char input;

	map<StateType,unique_ptr<State> > states;
	unordered_map<string, TOKEN> keywords, symbols;

	Lexer() : pos(-1), lineNumber(0)
	{
		//Map each possible state to its corresponding State object.
		/*states[StateType::START] = unique_ptr<State>(new StartState);
		states[StateType::INTEGER] = unique_ptr<State>(new IntegerState);
		states[StateType::IDENTIFIER] = unique_ptr<State>(new IdentifierState);
		states[StateType::WHITESPACE] = unique_ptr<State>(new WhiteSpaceState);
		states[StateType::SYMBOL] = unique_ptr<State>(new SymbolState);
		states[StateType::ENDOFTOKEN] = unique_ptr<State>(new EndOfTokenState);
		states[StateType::EOFTOKEN] = unique_ptr<State>(new EOFState);
		states[StateType::ERROR] = unique_ptr<State>(new ErrorState);*/

		keywords["if"] = TOKEN::IF;
		keywords["else"] = TOKEN::ELSE;
		keywords["while"] = TOKEN::WHILE;
		keywords["for"] = TOKEN::FOR;

		symbols["="] = TOKEN::EQ;
		symbols["=="] = TOKEN::EQEQ;
		symbols["("] = TOKEN::OPEN_PAREN;
		symbols[")"] = TOKEN::CLOSE_PAREN;
		symbols["{"] = TOKEN::OPEN_BRACE;
		symbols["}"] = TOKEN::CLOSE_BRACE;
		symbols["+"] = TOKEN::PLUS;
		symbols["-"] = TOKEN::MINUS;
		symbols["*"] = TOKEN::TIMES;
		symbols["/"] = TOKEN::DIVIDE;
		symbols[";"] = TOKEN::SEMICOLON;
	}

	~Lexer()
	{
		
	}

	bool readFile(string path)
	{
		bool successful = true;
		buffer = "";
		ifstream fin(path, std::ios::in | std::ios::binary);
		if (fin)
		{
			fin.seekg(0, std::ios::end);
			buffer.resize(fin.tellg());
			fin.seekg(0, std::ios::beg);

			fin.read(&buffer[0], buffer.size());
			buffer += '\0';

			successful = true;
		}
		else
		{
			successful = false;
		}

		fin.close();

		if (successful && buffer.length() > 0)
		{
			readInput(input);
		}

		return successful;
	}

	void addState(StateType type, StateType fail = StateType::END_OF_TOKEN_STATE)
	{
		
		this->states[type] = std::make_unique<State>(type, fail);
	}

	/*
	* Read the next character from the input string and increment the index. 
	* @return bool True if the character is successfully read, false otherwise.
	*/
	bool readInput(char &input)
	{
		pos++;
		if (pos < buffer.length())
			input = buffer[pos];
		return input != '\0' && pos < buffer.length();
	}

	string readTokenString()
	{
		string token = "";


		//Continue to follow the State transitions until the Error state is reached.
		while (nextState != StateType::ERROR_STATE && nextState != StateType::END_OF_TOKEN_STATE && nextState != StateType::EOF_STATE)
		{
			//Get the next State
			nextState = states[currentState]->getTransition(input);

			switch (nextState)
			{
			case StateType::START_STATE:
			case StateType::INTEGER_STATE:
			case StateType::IDENTIFIER_STATE:
			case StateType::WHITESPACE_STATE:
			case StateType::SYMBOL_STATE:
			case StateType::ERROR_STATE:
				//Append the input char to the token value and update the current state. Then read the next input char.
				token += input;
				currentState = nextState;
				if (!readInput(input))
				{
					//End of file/buffer
				}
				break;
			case StateType::END_OF_TOKEN_STATE:
				//No more input or no transition to make. Do nothing.
				break;
			case StateType::EOF_STATE:
				//The end of file was reached. Can only be reached from StartState
				currentState = nextState;
				break;
			}
		}



		return token;
	}

	Token getToken(string lexeme)
	{
		Token token;
		unordered_map<string, TOKEN>::iterator it;
		switch (currentState)
		{
		case StateType::START_STATE:
		case StateType::ERROR_STATE:
			token.tok = TOKEN::ERROR;
			token.type = "error";
			token.value = lexeme;
			break;
		case StateType::INTEGER_STATE:
			token.tok = TOKEN::INTEGER;
			token.type = "number";
			token.value = lexeme;
			break;
		case StateType::IDENTIFIER_STATE:
			//keywords are a subset of identifiers, so check if the identifier is reserved by language
			it = keywords.find(lexeme);
			if (it != keywords.end())
			{
				token.tok = it->second;
				token.type = "keyword";
				token.value = lexeme;
			}
			else
			{
				token.tok = TOKEN::IDENTIFIER;
				token.type = "identifier";
				token.value = lexeme;
			}
			break;
		case StateType::SYMBOL_STATE:
			//check if it's a valid symbol/operator, so check if the symbol is in the map of symbols
			it = symbols.find(lexeme);
			if (it != symbols.end())
			{
				token.tok = it->second;
				token.type = "symbol";
				token.value = lexeme;
			}
			else
			{
				token.tok = TOKEN::ERROR;
				token.type = "error";
				token.value = lexeme;
			}
			break;
		case StateType::WHITESPACE_STATE:
			token.tok = TOKEN::WHITESPACE;
			token.type = "whitespace";
			token.value = lexeme;
			break;
		case StateType::EOF_STATE:
			//The end of file was reached. Can only be reached from StartState
			token.tok = TOKEN::EOFTOKEN;
			token.type = "eof";
			token.value = EOF;
			break;
		}

		return token;
	}

	/*
	* Read the token by reading the input one character at a time and following the State transitions.
	* @return string The next lexeme/token value from the input string
	*/
	Token getToken()
	{
		//Begin with the Start state.
		currentState = StateType::START_STATE;
		nextState = StateType::START_STATE;

		string lexeme = readTokenString();

		return getToken(lexeme);
	}

};

int main()
{
	//auto begin = std::chrono::high_resolution_clock::now();
	//Create a simple lexer to tokenize a string with integers and identifiers
	TransitionRange alphaLower('a', 'z', StateType::IDENTIFIER_STATE);
	TransitionRange alphaUpper('A', 'Z', StateType::IDENTIFIER_STATE);
	TransitionRange digits('0', '9', StateType::INTEGER_STATE);//for integer state
	TransitionRange idDigits('0', '9', StateType::IDENTIFIER_STATE); //for identifier state

	Lexer scanner;
	scanner.readFile("input.txt");
	cout << scanner.buffer << "\n\n";
	
	scanner.addState(StateType::START_STATE, StateType::ERROR_STATE);
	scanner.states[StateType::START_STATE]->addRange(alphaLower);
	scanner.states[StateType::START_STATE]->addRange(alphaUpper);
	scanner.states[StateType::START_STATE]->addRange(digits);
	scanner.states[StateType::START_STATE]->addTransitions(" \n\t", StateType::WHITESPACE_STATE);
	scanner.states[StateType::START_STATE]->addTransitions("=(){}+-/*;", StateType::SYMBOL_STATE);
	scanner.states[StateType::START_STATE]->addTransition('_', StateType::IDENTIFIER_STATE);
	scanner.states[StateType::START_STATE]->addTransition('\0', StateType::EOF_STATE);

	scanner.addState(StateType::SYMBOL_STATE);
	scanner.states[StateType::SYMBOL_STATE]->addTransitions("=(){}+-/*;", StateType::SYMBOL_STATE);

	scanner.addState(StateType::INTEGER_STATE);
	scanner.states[StateType::INTEGER_STATE]->addRange(digits);

	scanner.addState(StateType::IDENTIFIER_STATE);
	scanner.states[StateType::IDENTIFIER_STATE]->addRange(alphaLower);
	scanner.states[StateType::IDENTIFIER_STATE]->addRange(alphaUpper);
	scanner.states[StateType::IDENTIFIER_STATE]->addRange(idDigits);
	scanner.states[StateType::IDENTIFIER_STATE]->addTransition('_', StateType::IDENTIFIER_STATE);

	scanner.addState(StateType::WHITESPACE_STATE);
	scanner.states[StateType::WHITESPACE_STATE]->addTransitions(" \n\t", StateType::WHITESPACE_STATE);

	scanner.addState(StateType::END_OF_TOKEN_STATE, StateType::END_OF_TOKEN_STATE);

	scanner.addState(StateType::EOF_STATE, StateType::EOF_STATE);

	scanner.addState(StateType::ERROR_STATE, StateType::ERROR_STATE);
	
	
	Token token;
	do
	{
		token = scanner.getToken();
		token.print();
		//cout << token << " is a(n) " << scanner.states[scanner.currentState]->name << "\n";
	} while (scanner.nextState != StateType::EOF_STATE);

	//auto end = std::chrono::high_resolution_clock::now();
	//auto dur = end - begin;
	
	//cout << std::chrono::duration_cast<std::chrono::seconds>(dur).count() << "seconds\n";
	//cout << token << " is a(n) " << scanner.states[scanner.currentState]->name << "\n";
	return 0;
}