#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

#include <iostream>
#include <vector>
#include <string>

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
		ConstantId,
		GroupId,
		OperatorId,
		NoneId = 0
	};
	class Expression {
	public:
		ExpressionId id;
		Expression() {
			id = NoneId;
		}
		Expression(ExpressionId _id) {
			id = _id;
		}
		template<class T>
		bool is() {
			return int(id) == int(T::SpecificId);
		}
		template<class T>
		T* cast() {
			assert(int(id) == int(T::SpecificId));
			return (T*)this;
		}
	};
	typedef std::vector<Expression*> ExpressionList;
	template<ExpressionId eid>
	class SpecificExpression : public Expression {
	public:
	  enum {
	    SpecificId = eid
	  };
	  SpecificExpression() : Expression(eid) {}
	};
	class Constant : SpecificExpression<ExpressionId::ConstantId> {
	public:
		double value;
		Constant() { }
	};
	class Operator : SpecificExpression<ExpressionId::OperatorId> {
	public:
		Expression left;
		Expression right;
		Operator() { }
	};
	class Block : SpecificExpression<ExpressionId::GroupId> {
	public:
		ExpressionList list;
		Block() { }
	};
	class AST {
	public:
		string raw;
		Block* base;
		AST(string init) {
			raw = init;
			base = new Block();
		}
	};
};