#include "jit.h"

eval::JitEvaluator::JitEvaluator(ast::AST* _tree) {
    tree = _tree;
    runtime = new JitRuntime();
    code = new CodeHolder();
    assembler = new X86Assembler(code);
}
void eval::JitEvaluator::generate() {
    runtime->add(&fn, code);
}
eval::JitFunction eval::JitEvaluator::getFunction(void) {
    return fn;
}