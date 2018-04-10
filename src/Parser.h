#pragma once
#include "AST.h"

class Parser {
public:
	AST* tree;
	string raw;
	Parser(string);
};