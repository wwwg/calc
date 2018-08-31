#include "jit.h"

eval::JitEvaluator::JitEvaluator(ast::AST* _tree) {
    tree = _tree;
    runtime = new JitRuntime();
    code = new CodeHolder();
    as = new X86Assembler(code);
    code->init(runtime->getCodeInfo());
}
void eval::JitEvaluator::generateTo(JitFunction* fn) {
	// Assemble the base of the tree
	assembleExpression(tree->base);
	// After all the assembly has been done, the result will be in ebx
	as->mov(x86::eax, x86::ebx);
	as->ret();
	// Code generation complete
    Error err = runtime->add(&fn, code);
}
void eval::JitEvaluator::assembleExpression(ast::Operator* o) {
	// assemble leftmost value
	if (o->left->is<ast::Block>()) {
		// leftmost value is an operator
		// assemble the operator
		ast::Block* lb = o->left->cast<ast::Block>();
		assembleExpression(lb);
		// the operator was pushed on the stack, pop it back off
		as->pop(x86::ebx);
	} else if (o->left->is<ast::Constant>()) {
		// leftmost value is a constant, mov into edx
		ast::Constant* c = o->left->cast<ast::Constant>();
		as->mov(x86::ebx, (int)c->value);
	} else if (o->left->is<ast::Operator>()) {
		ast::Operator* rop2 = o->left->cast<ast::Operator>();
		assembleExpression(rop2);
		// pop the return value to edx
		as->pop(x86::ebx);
	}
	// assemble rightmost value
	if (o->right->is<ast::Block>()) {
		// rightmost expression is an operator
		ast::Block* rb = o->right->cast<ast::Block>();
		if (o->left->is<ast::Constant>()) {
			// push the constant onto the stack
			as->push(x86::ebx);
			assembleExpression(rb);
			/*
				After the expression has been assembled, the top of the stack looks like this:
				
				[result of block assembly (right)]
				[constant (left)]
			*/
			as->pop(x86::ebx); // left expression
			as->pop(x86::edx); // right expression
		} else {
			// the result of leftmost operator is in ebx, put it on the stack
			as->push(x86::ebx);
			assembleExpression(rb);
			as->pop(x86::edx); // expression result will now be in ebx
			as->pop(x86::ebx); // leftmost operator is now in ebx
		}
	} else if (o->right->is<ast::Constant>()) {
		// rightmost value is a constant, mov into edx
		ast::Constant* c = o->right->cast<ast::Constant>();
		as->mov(x86::edx, (int)c->value);
	} else if (o->right->is<ast::Operator>()) {
		ast::Operator* rop2 = o->right->cast<ast::Operator>();
		assembleExpression(rop2);
		// pop the return value to edx
		as->pop(x86::edx);
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