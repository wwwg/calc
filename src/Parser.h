#pragma once
#include "AST.h"

class Parser {
public:
	ast::AST* tree;
	string raw;
	Parser(string);
};