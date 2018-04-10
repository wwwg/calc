#pragma once

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>

#include "AST.h"

namespace utils {
	bool isNumber(char);
	bool isGroupStart(char);
	bool isGroupEnd(char);
};