#include "Parser.h"
#include "AST.h"
#include "ParserUtils.h"

#define EXPRESSION "9+3-2+6"

int main() {
	ast::AST tree = ast::AST();
	Parser p(EXPRESSION);
	p.tree = &tree;
	p.parse();
	utils::putast(&tree);
	return 0;
}