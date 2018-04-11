#pragma once
#include "AST.h"

struct ParseResult {
	int pos;
	ast::Expression* exp;
};
class Parser {
public:
	ast::AST* tree;
	string raw;
	int globalPos;
	Parser(string);
	bool parse(void);
	string getError(void);
protected:
	string error;
	ParseResult parseToExpression(int);
	ParseResult parseConstant(int);
	ast::Expression* last;
};