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
		pos = res.pos;
		if (pos >= raw.length()) {
			if (last->is<Operator>()) {
				last->cast<Operator>()->right = res.exp;
				r.exp = last;
				r.pos = pos;
				return r;
			}
		}
		last = res.exp;
		cout << pos << ": " << raw[pos] << endl;
		return parseToExpression(pos);
	} else if (utils::isGroupStart(c)) {
		ast::Block* b = new ast::Block();
		b->last = current;
		if (current->is<ast::Block>()) {
			current->cast<ast::Block>()->list.push_back((ast::Expression*)b);
		}
		current = b;
		++pos;
		r.pos = pos;
		r.exp = current;
		cout << "block start" << endl;
	} else if (utils::isGroupEnd(c)) {
		lastCtx = current->last->last;
		current = current->last;
		++pos;
		r.exp = current;
		r.pos = pos;
		cout << "block end" << endl;
	} else if (utils::isOp(c)) {
		++pos;
		ast::Operator* op = new ast::Operator();
		op->operation = utils::toOp(c);
		op->left = last;
		// right needs to be parsed next
		ParseResult rightParse = parseToExpression(pos);
		op->right = rightParse.exp;
		// append operator to the current block, if inside one
		if (current->is<ast::Block>()) {
			current->cast<ast::Block>()->list.push_back((ast::Expression*)op);
		}
		// return result
		r.pos = pos;
		r.exp = (ast::Expression*)op;
		cout << "operator '" << c << "'" << endl;
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
	cout << "constant " << ret->value << endl;
	return r;
}