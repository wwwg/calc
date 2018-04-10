#include "Parser.h"
#include "AST.h"
#define EXPRESSION "1+9-3"

int main() {
	ast::AST tree = ast::AST();
	Parser p(EXPRESSION);
	p.tree = &tree;
	return 0;
}