#pragma once

#include <cstdlib>
#include <cstdio>
#include <asmjit/asmjit.h>
#include "../AST.h"

using namespace asmjit;
using namespace std;

namespace eval {
    typedef int (*JitFunction)(void);
    class JitEvaluator {
    public:
        JitRuntime* runtime;
        CodeHolder* code;
        X86Assembler* assembler;
        ast::AST* tree;
        JitEvaluator(ast::AST*);
        void generate(void);
        JitFunction getFunction(void);
        // assemble methods
        void assembleExpression(ast::Operator*);
        // todo
        // void assembleExpression(ast::Block*);
        // void assembleExpression(ast::Expression*);
    protected:
        JitFunction fn;
    };
}