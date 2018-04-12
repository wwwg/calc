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
			if (last->is<ast::Operator>()) {
				last->cast<ast::Operator>()->right = res.exp;
				r.exp = last;
				r.pos = pos;
				return r;
			}
		}
		last = res.exp;
		return parseToExpression(pos);
	} else if (utils::isGroupStart(c)) {
		ast::Block* b = new ast::Block();
		cout << "block " << c << endl;
		++pos;
		char c2 = '\0';
		while (!utils::isGroupEnd(c2)) {
			// TODO : handle unmatched group ends
			c2 = raw[pos];
			ParseResult res = parseToExpression(pos);
			pos = res.pos;
			if (res.exp != nullptr) b->list.push_back(res.exp);
		}
		cout << "end block " << raw[pos] << endl;
		++pos;
		r.pos = pos;
		r.exp = (ast::Expression*)b;
	} else if (utils::isOp(c)) {
		cout << "operator '" << c << "'" << endl;
		++pos;
		ast::Operator* op = new ast::Operator();
		op->operation = utils::toOp(c);
		op->left = last;
		// right needs to be parsed next
		cout << "parsing right side of operator '" << c << "'" << endl;
		last = (ast::Expression*)op;
		ParseResult rightParse = parseToExpression(pos);
		if (rightParse.exp != nullptr) {
			op->right = rightParse.exp;
		} else {
			op->right = last;
		}
		cout << "done parsing right side of operator '" << c << "'" << endl;
		// return result
		r.pos = pos;
		r.exp = (ast::Expression*)op;
		last = r.exp;
	} else if (utils::isGroupEnd(c)) {
		// ++pos; return parseToExpression(pos);
	} else if (utils::isWhitespace(c)) {
		++pos;
		return parseToExpression(pos);
	} else {
		cout << "recieved unknown token: '" << c << "' at pos " << pos << endl;
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