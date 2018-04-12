#pragma once

#include <cmath>

#include "../AST.h"

namespace eval {
    // evaluator functions for each component of the AST
    double eval(ast::Block*);
    double eval(ast::Operator*);
    double eval(ast::Constant*);
    
    double eval(ast::Expression*);
    double eval(ast::AST*);
}