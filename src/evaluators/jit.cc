#ifdef CALC_JIT

#include "jit.h"

eval::JitEvaluator::JitEvaluator(ast::AST* _tree) {
    tree = _tree;
    runtime = new JitRuntime();
    code = new CodeHolder();
    as = new X86Assembler(code);
    code->init(runtime->getCodeInfo());
}
void eval::JitEvaluator::generate() {
	assembleExpression(tree->base);
    runtime->add(&fn, code);
}
eval::JitFunction eval::JitEvaluator::getFunction(void) {
    return fn;
}
void eval::JitEvaluator::assembleExpression(ast::Operator* o) {
	if (o->left->is<ast::Block>()) {
		// leftmost value is an operator
		// assemble the operator
		assembleExpression(o);
		// the operator was pushed on the stack, pop it back off
		as.pop(x86::ebx);
	} else {
		// leftmost value is a constant
		// Move the leftmost value into ebx
		as.mov(x86::ebx, o->left);
	}
    switch (o->operation) {
    	case ast::Operation::Add:
    		as.add(x86::ebx, o->right);
    		break;
    	case ast::Operation::Sub:
    		as.sub(x86::ebx, o->right);
    		break;
    	case ast::Operation::Mul:
    		as.mul(x86::ebx, o->right);
    		break;
    	case ast::Operation::Div:
    		as.div(x86::ebx, o->right);
    		break;
    	case ast::Operation::Pow:
    		// todo
    		break;
    }
}
void eval::JitEvaluator::assembleExpression(ast::block* o) {
	ast::Operator* inner = o->list.at(0); // Every block has one operator in it
	assembleExpression(inner);
	as.push(x86::ebx);
}

#endif