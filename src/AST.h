#pragma once

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;
/*
	Abstract syntax tree: hierchy of expressions
	9 + 3 - 2 + 6 =

			ast
		   /   \
		  +     6
		 / \
		9   -
		   / \
		  3   2
*/
namespace ast {
	enum ExpressionId {
		Constant,
		Group,
		Operator,
		None = 0
	};
	class Expression {
	public:
		ExpressionId id;
		Expression() { }
		Expression(ExpressionId _id) {
			id = _id;
		}
	};
	class Constant : Expression {
	public:
		double value;
		Constant() : Expression(ExpressionId::Constant) { }
	};
};