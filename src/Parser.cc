#include "Parser.h"

Parser::Parser(string _raw) {
	raw = _raw;
	tree = nullptr;
}
bool Parser::parse() {
	return true;
}
string Parser::getError() {
	if (error.length())
		return error;
	else
		return "none";
}