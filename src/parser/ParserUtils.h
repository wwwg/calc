#pragma once

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>

#include "../AST.h"

using namespace std;

namespace utils {
	bool isNumber(char);
	bool isGroupStart(char);
	bool isGroupEnd(char);
	ast::Operation toOp(char);
	bool isOp(char);
	bool isWhitespace(char);
};