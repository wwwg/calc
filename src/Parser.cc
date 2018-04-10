#include "Parser.h"

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