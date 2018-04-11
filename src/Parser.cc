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
	current = (ast::Expression*)tree->base;
	ParseResult res = parseToExpression(globalPos);
	tree->base->list.push_back(res.exp);
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
		parseToExpression(res.pos);
	} else if (utils::isGroupStart(c)) {
		ast::Block* b = new ast::Block();
		b->last = current;
		current = b;
	} else if (utils::isGroupEnd(c)) {
		lastCtx = current->last->last;
		current = current->last;
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