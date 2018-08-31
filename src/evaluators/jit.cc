#ifdef CALC_JIT

#include "jit.h"

eval::JitEvaluator::JitEvaluator(ast::AST* _tree) {
    tree = _tree;
    runtime = new JitRuntime();
    code = new CodeHolder();
    assembler = new X86Assembler(code);
    code->init(runtime->getCodeInfo());
}
void eval::JitEvaluator::generate() {
    runtime->add(&fn, code);
}
eval::JitFunction eval::JitEvaluator::getFunction(void) {
    return fn;
}
void eval::JitEvaluator::assembleExpression(ast::Operator* o) {
    switch (o->operation) {
    	case ast::Operation::Add:
    		break;
    	case ast::Operation::Sub:
    		break;
    	case ast::Operation::Mul:
    		break;
    	case ast::Operation::Div:
    		break;
    	case ast::Operation::Pow:
    		// todo
    		break;
    }
}

#endif