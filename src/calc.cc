#include "parser/Parser.h"
#include "parser/ParserUtils.h"
#include "AST.h"
#include "util/putast.h"
#include "evaluators/eval.h"
#include "evaluators/jit.h"

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

	eval::JitEvaluator je = eval::JitEvaluator(&tree);
	eval::JitFunction fn;
	je.generateTo(&fn);
	int result = fn(); // call the compiled function
	cout << "JIT compiled result: " << result << endl;

	return 0;
}