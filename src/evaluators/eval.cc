#include "eval.h"

double eval::eval(ast::Constant* c) {
    return c->value;
}
double eval::eval(ast::Operator* o) {
    double left = eval(o->left);
    double right = eval(o->right);
    switch (o->operation) {
        case ast::Operation::Add:
            return left + right;
        case ast::Operation::Sub:
            return left - right;
        case ast::Operation::Mul:
            return left * right;
        case ast::Operation::Div:
            return left / right;
        case ast::Operation::Pow:
            return std::pow(left, right);
        case ast::Operation::Eq:
            if (left == right)
                return 1.0;
            else
                return 0.0;
    }
}
double eval::eval(ast::Block* b) {
    // find the innermost expression
    ast::Expression* inner = (ast::Expression*)b;
    do {
        inner = (inner->cast<ast::Block>())->list.at(0);
    } while (inner->is<ast::Block>());
    // evaluate it
    return eval(inner);
}
double eval::eval(ast::Expression* e) {
    if (e->is<ast::Constant>()) return eval(e->cast<ast::Constant>());
    if (e->is<ast::Operator>()) return eval(e->cast<ast::Operator>());
    if (e->is<ast::Block>()) return eval(e->cast<ast::Block>());
    return 0.0;
}
double eval::eval(ast::AST* tree) {
    return eval(tree->base);
}