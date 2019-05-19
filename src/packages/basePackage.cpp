#include "../tokens/values/integerToken.h"
#include "package.h"

namespace base_func {

auto plus = std::make_shared<OperatorToken>("+");
auto minus = std::make_shared<OperatorToken>("-");

}  // namespace base_func

namespace {
using IntegerTP = std::shared_ptr<IntegerToken>;

namespace pats {
auto i{std::ref(IntegerToken::TYPE_INTEGER)};

NumTypePattern int_int{i, i};
}  // namespace pats

namespace ops {
void add__int_int(ValueStack& values) {
    auto b = std::static_pointer_cast<IntegerToken>(values.back());
    values.pop_back();
    auto a = std::static_pointer_cast<IntegerToken>(values.back());
    values.pop_back();

    if (a->VALUE_TYPE == ValueToken::ASSIGNABLE) {
        *a = *a + *b;
        values.push_back(a);
        return;
    }

    if (b->VALUE_TYPE == ValueToken::ASSIGNABLE) {
        *b = *a + *b;
        values.push_back(b);
        return;
    }

    values.push_back(std::make_shared<IntegerToken>(*a + *b));
}

void subtract__int_int(ValueStack& values) {
    auto b = std::static_pointer_cast<IntegerToken>(values.back());
    values.pop_back();
    auto a = std::static_pointer_cast<IntegerToken>(values.back());
    values.pop_back();

    if (a->VALUE_TYPE == ValueToken::ASSIGNABLE) {
        *a = *a - *b;
        values.push_back(a);
        return;
    }

    if (b->VALUE_TYPE == ValueToken::ASSIGNABLE) {
        *b = *a - *b;
        values.push_back(b);
        return;
    }

    values.push_back(std::make_shared<IntegerToken>(*a - *b));
}
}  // namespace ops

void initBasePackage(Package&, const Settings&) {
    base_func::plus->bind(ops::add__int_int, pats::int_int, 4);
    base_func::minus->bind(ops::subtract__int_int, pats::int_int, 4);
}

void preloadBasePackage(Package& p, const Settings&) {
    p.addOperator(base_func::plus);
    p.addOperator(base_func::minus);
}

}  // namespace

Package Package::basePackage{"base", initBasePackage, preloadBasePackage};