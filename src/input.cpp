#include <iostream>
#include <string>

#include "h/input.h"

std::string getNextExpr() {
    
    std::string next;
    std::cout << GET_INPUT_TOKEN;
    std::getline(std::cin, next);
    return next;
}


