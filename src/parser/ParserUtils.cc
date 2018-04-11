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
		c == '('
	) return true;
	return false;
}
bool utils::isGroupEnd(char c) {
	if (
		c == ')'
	) return true;
	return false;
}
ast::Operation utils::toOp(char c) {
	ast::Operation ret = ast::Operation::Nop;
	if (c == '+') ret = ast::Operation::Add;
	if (c == '-') ret = ast::Operation::Sub;
	if (c == '/') ret = ast::Operation::Div;
	if (c == '*') ret = ast::Operation::Mul;
	if (c == '^') ret = ast::Operation::Pow;
	return ret;
}
bool utils::isOp(char c) {
	if (
		c == '+' ||
		c == '-' ||
		c == '*' ||
		c == '^' ||
		c == '/'
	) return true;
	return false;
}
void utils::putIndent(int id) {
	for (int i = 0; i < id; ++i) cout << " ";
}
void utils::putast(ast::AST* a) {
	/* int indent = 0;
	for (const auto& e : a->base->list) {
	 	//
	} */
	cout << a->base->list.size() << endl;
}