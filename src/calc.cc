#include "parser/Parser.h"
#include "parser/ParserUtils.h"
#include "AST.h"
#include "util/putast.h"

#define EXPRESSION "9+(3-2)"

int main() {
	ast::AST tree = ast::AST();
	Parser p(EXPRESSION);
	p.tree = &tree;
	p.parse();
	return 0;
}