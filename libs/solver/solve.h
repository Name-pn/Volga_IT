//
// Created by Alexandr on 29.03.2022.
//

#ifndef INC_SOLVER_H
#define INC_SOLVER_H

#include "..\matrix\matrix.h"
#include "..\task\fairy_tail.hpp"
#include "vector"
#include "cmath"

enum vars_final{THEY_FIND = 0, THEY_CANT_FIND, LIMIT_EXCEEDED};

matrix<char> solve(int &steps, int &final_type);

#endif //INC_SOLVER_H
