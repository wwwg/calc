#ifndef CALC_JIT
#define CALC_JIT

#pragma once

#include <cstdlib>
#include <cstdio>
#include <asmjit/asmjit.h>
#include "../AST.h"

using namespace asmjit;
using namespace std;

namespace eval {
    typedef int (*JitFunction)(void);
    typedef double (*JitFunction_d)(void);
    class JitEvaluator {
    public:
        JitRuntime* runtime;
        CodeHolder* code;
        X86Assembler* as;
        ast::AST* tree;
        JitEvaluator(ast::AST*);
        void generateTo(JitFunction);
        // assemble methods
        void assembleExpression(ast::Operator*);
        void assembleExpression(ast::Block*);
        // void assembleExpression(ast::Expression*);
    };
}

#endif