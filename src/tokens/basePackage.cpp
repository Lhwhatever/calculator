#include "package.h"

using ValueStack = std::vector<ValueToken*>;

Package Package::basePackage{"base"};

namespace base_func {

void add(ValueStack& valueStack) {
}

}