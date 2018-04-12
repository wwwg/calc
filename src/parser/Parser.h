#pragma once
#include "../AST.h"
#include <unistd.h>

struct ParseResult {
	int pos;
	ast::Expression* exp;
	unsigned char flag = 0;
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
	ast::Expression* current;
	ast::Expression* lastCtx;
	void die(void);
};