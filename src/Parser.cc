#include "Parser.h"
#include "ParserUtils.h"

Parser::Parser(string _raw) {
	raw = _raw;
	tree = nullptr;
	globalPos = 0;
}
bool Parser::parse() {
	if (tree == nullptr) return false;
	tree->base = new ast::Block();
	currBlock = tree->base;
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
	char c = raw[pos];
	if (utils::isNumber(c)) {
		ParseResult res = parseConstant(pos);
		r = res;
		last = res.exp;
	} else if (utils::isGroupStart(c)) {
		ast::Block* b = new ast::Block();
		lastBlock = currBlock;
		currBlock = b;
	}
	return r;
}
ParseResult Parser::parseConstant(int pos) {
	ParseResult r;
	r.pos = pos;
	r.exp = nullptr;
	if (pos > raw.length()) {
		return r;
	}
	int newPos = pos;
	char c = raw[newPos];
	string constant;
	while (utils::isNumber(c)) {
		constant += c;
		newPos++;
		c = raw[newPos];
	}
	r.pos = newPos;
	ast::Constant* ret = new ast::Constant();
	ret->value = std::stod(constant);
	r.exp = ret->toExpression();
	return r;
}