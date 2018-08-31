# calc
A mathematical expression evaluator & JIT compiler written in C++
# compiling
- Make sure you have asmjit installed
- run `make` in repository
# how it works
- Given expressions are parsed into Abstract Syntax Trees
- Said trees are then fed into an evaluator (evaluators are located in the `src/evaluators` directory)
- There are currently two avalible evaluators:
    * eval (directly interprets the abstract syntax tree)
    * JitEvaluator (compiles the AST to x86 assembly and excecutes the machine code)