#include "parser/Parser.h"
#include "parser/ParserUtils.h"
#include "AST.h"
#include "util/putast.h"
#include "evaluators/eval.h"

int main(int argc, char** argv) {
	if (argc < 2) {
		cout << "invalid arguments:" << endl
		<< "calc \"expression\"" << endl;
		return 1;
	}
	string expression = string(argv[1]);
	ast::AST tree = ast::AST();
	Parser p(expression);
	p.tree = &tree;
	p.parse();
	cout << "Abstract syntax tree:" << endl;
	ast::put(&tree);
	cout << endl;

	//

	return 0;
}