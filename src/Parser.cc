#include "Parser.h"
#include "ParserUtils.h"

Parser::Parser(string _raw) {
	raw = _raw;
	tree = nullptr;
}
bool Parser::parse() {
	if (tree == nullptr) return false;
	return true;
}
string Parser::getError() {
	if (error.length())
		return error;
	else
		return "none";
}
ParseResult Parser::parseToExpression(int pos) {
	ParseResult r;
	r.pos = pos;
	r.exp = nullptr;
	return r;
}
ParseResult Parser::parseConstant(int pos) {
	ParseResult r;
	r.pos = pos;
	r.exp = nullptr;

	if (pos > raw.length()) {
		return r;
	}
	return r;
}