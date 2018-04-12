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
    // todo
}