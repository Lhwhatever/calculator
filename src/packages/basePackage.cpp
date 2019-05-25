#include "../tokens/values/integerToken.h"
#include "package.h"

namespace base_func {

auto plus =
    std::make_shared<OperatorToken>("+", 2, 4, OperatorToken::LEFT_ASSOC);
auto minus =
    std::make_shared<OperatorToken>("-", 2, 4, OperatorToken::LEFT_ASSOC);
auto times =
    std::make_shared<OperatorToken>("*", 2, 5, OperatorToken::LEFT_ASSOC);

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

void multiply__int_int(ValueStack& values) {
    auto b = std::static_pointer_cast<IntegerToken>(values.back());
    values.pop_back();
    auto a = std::static_pointer_cast<IntegerToken>(values.back());
    values.pop_back();

    if (a->VALUE_TYPE == ValueToken::ASSIGNABLE) {
        *a = *a * *b;
        values.push_back(a);
        return;
    }

    if (b->VALUE_TYPE == ValueToken::ASSIGNABLE) {
        *b = *a * *b;
        values.push_back(b);
        return;
    }

    values.push_back(std::make_shared<IntegerToken>(*a * *b));
}
}  // namespace ops

void initBasePackage(Package&, const Settings&) {
    base_func::plus->bind(pats::int_int, ops::add__int_int);
    base_func::minus->bind(pats::int_int, ops::subtract__int_int);
    base_func::times->bind(pats::int_int, ops::multiply__int_int);
}

void preloadBasePackage(Package& p, const Settings&) {
    p.addOperator(base_func::plus);
    p.addOperator(base_func::minus);
    p.addOperator(base_func::times);
}

}  // namespace

Package Package::basePackage{"base", initBasePackage, preloadBasePackage};