#pragma once

#include <cassert>
#include <vector>
#include <string>
#include <iostream>

#include "../AST.h"
using namespace std;

namespace ast {
    void indent(int);
    void put(Constant*, int);
    void put(Operator*, int);
    void put(Block*, int);
    
    void put(Expression*, int);
    void put(Expression*);
}