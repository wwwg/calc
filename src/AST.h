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
		Block,
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
	template<ExpressionId eid>
	class SpecificExpression : public Expression {
	public:
	  enum {
	    SpecificId = eid
	  };
	  SpecificExpression() : Expression(eid) {}
	};
	class Constant : SpecificExpression<ExpressionId::Constant> {
	public:
		double value;
		Constant() { }
	};
	class Operator : SpecificExpression<ExpressionId::Operator> {
	public:
		Expression left;
		Expression right;
		Operator() { }
	};
	class Block : SpecificExpression<ExpressionId::Block> {
	public:
		vector<Expression*> list;
		Block() { }
	};
};