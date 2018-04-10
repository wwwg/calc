#include "ParserUtils.h"

bool utils::isNumber(char c) {
	if (
		c == '0' ||
		c == '1' ||
		c == '2' ||
		c == '3' ||
		c == '4' ||
		c == '5' ||
		c == '6' ||
		c == '7' ||
		c == '8' ||
		c == '9' ||
		c == '.'
	) return true;
	return false;
}
bool utils::isGroupStart(char c) {
	if (
		c == '(' ||
		c == '[' ||
		c == '{'
	) return true;
	return false;
}
bool utils::isGroupEnd(char c) {
	if (
		c == ')' ||
		c == ']' ||
		c == '}'
	) return true;
	return false;
}