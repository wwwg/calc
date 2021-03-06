#pragma once

#include <cassert>
#include <vector>
#include <string>

using namespace std;
/*
	Abstract syntax tree: hierchy of expressions
	9 + 3 - 2 =

	 ast
      |
	  +
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
	enum Operation {
		Add,
		Sub,
		Mul,
		Div,
		Pow,
		Eq,
		Nop = 0
	};
	class Expression {
	public:
		Expression* last;
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
	  Expression* toExpression() {
	  	return (Expression*)this;
	  }
	};
	class Constant : public SpecificExpression<ExpressionId::ConstantId> {
	public:
		double value;
		Constant() { }
	};
	class Operator : public SpecificExpression<ExpressionId::OperatorId> {
	public:
		Operation operation;
		Expression* left;
		Expression* right;
		Operator() { }
	};
	class Block : public SpecificExpression<ExpressionId::GroupId> {
	public:
		ExpressionList list;
		Block() { }
	};
	class AST {
	public:
		Block* base;
		AST() { }
	};
};