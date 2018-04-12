#include "putast.h"

void ast::indent(int indents) {
    for (int i = 0; i < indents; ++i) cout << " ";
}
void ast::put(Constant* c, int ind) {
    indent(ind);
    cout << "Constant '" << c->value << "'" << endl; 
}
void ast::put(Operator* o, int ind) {
    char op = ' ';
    switch (o->operation) {
        case Operation::Add:
            op = '+';
            break;
        case Operation::Sub:
            op = '-';
            break;
        case Operation::Mul:
            op = '*';
            break;
        case Operation::Div:
            op = '/';
            break;
        case Operation::Pow:
            op = '^';
            break;
    }
    indent(ind);
    cout << "Operator '" << op << "' :" << endl;
    indent(ind + 1);
    cout << "Left:" << endl;
    put(o->left, ind + 2);
    cout << "Right:" << endl;
    put(o->right, ind + 2);
    cout << endl;
}
void ast::put(Block* b, int ind) {
    indent(ind);
    cout << "Block (" << endl;
    for (int i = 0; i < b->list.size(); ++i) {
        Expression* e = b->list.at(i);
        put(e, ind + 1);
    }
    indent(ind);
    cout << ")" << endl;
}
void ast::put(Expression* e, int ind) {
    if (e == nullptr) return;
    if (e->is<Constant>()) {
        put(e->cast<Constant>(), ind);
    } else if (e->is<Operator>()) {
        put(e->cast<Operator>(), ind);
    } else if (e->is<Block>()) {
        put(e->cast<Block>(), ind);
    }
}
void ast::put(Expression* e) {
    put(e, 0);
}
void ast::put(AST* a) {
    put(a->base);
}