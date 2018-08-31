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
	// assemble leftmost value
	if (o->left->is<ast::Block>()) {
		// leftmost value is an operator
		// assemble the operator
		ast::Block lb = o->left->cast<ast::Block>();
		ast::Operator* lop2 = (o->left->cast<ast::Block>()->list.at(0))->cast<ast::Operator>();
		assembleExpression(lop2);
		// the operator was pushed on the stack, pop it back off
		as->pop(x86::ebx);
	} else {
		// leftmost value is a constant
		// Move the leftmost value into ebx
		as->mov(x86::ebx, (int)o->left->cast<ast::Constant>()->value);
	}
	// assemble rightmost value
	if (o->right->is<ast::Block>()) {
		// rightmost expression is an operator
		ast::Block rb = o->right->cast<ast::Block>();
		ast::Operator* rop2 = (rb->list.at(0))->cast<ast::Operator>();
		assembleExpression(rop2);
		// pop the return value to edx
		as->pop(x86::edx);
	} else {
		// rightmost value is a constant, mov into edx
		as->mov(x86::edx, (int)o->right->cast<ast::Constant>()->value);
	}
    switch (o->operation) {
    	case ast::Operation::Add:
    		as->add(x86::ebx, x86::edx);
    		break;
    	case ast::Operation::Sub:
    		as->sub(x86::ebx, x86::edx);
    		break;
    	case ast::Operation::Mul:
    		as->mul(x86::ebx,x86::edx);
    		break;
    	case ast::Operation::Div:
    		as->div(x86::ebx, x86::edx);
    		break;
    	case ast::Operation::Pow:
    		// todo
    		break;
    }
}
void eval::JitEvaluator::assembleExpression(ast::Block* o) {
	ast::Operator* inner = o->list.at(0)->cast<ast::Operator>(); // Every block has one operator in it
	assembleExpression(inner);
	as->push(x86::ebx);
}