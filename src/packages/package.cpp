#include "package.h"

#include <string.h>
#include <stdexcept>
#include <utility>

Package::Package(std::string name, Runnable onInit, Runnable onLoad)
    : NAME{name}, latexMap{}, plainMap{}, onInit{onInit}, onLoad{onLoad} {}
