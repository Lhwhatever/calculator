#include "../tokens/values/floatToken.h"
#include "../tokens/values/integerToken.h"
#include "package.h"

namespace base_func {

auto plus =
    std::make_shared<OperatorToken>("+", 2, 4, OperatorToken::LEFT_ASSOC);
auto minus =
    std::make_shared<OperatorToken>("-", 2, 4, OperatorToken::LEFT_ASSOC);
auto times =
    std::make_shared<OperatorToken>("*", 2, 5, OperatorToken::LEFT_ASSOC);
auto divide =
    std::make_shared<OperatorToken>("/", 2, 5, OperatorToken::LEFT_ASSOC);

}  // namespace base_func

namespace {
using IntegerTP = std::shared_ptr<IntegerToken>;

namespace pats {
auto tint{std::ref(IntegerToken::TYPE_INTEGER)};
auto tfloat{std::ref(FloatToken::TYPE_FLOAT)};

NumTypePattern int_int{tint, tint};
NumTypePattern int_float{tint, tfloat};
NumTypePattern float_int{tfloat, tint};
NumTypePattern float_float{tfloat, tfloat};
}  // namespace pats

namespace ops {
template <typename T>
void add__(ValueStack& values) {
    auto b = std::static_pointer_cast<T>(values.back());
    values.pop_back();
    auto a = std::static_pointer_cast<T>(values.back());
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

    values.push_back(std::make_shared<T>(*a + *b));
}

template <typename Tl, typename Tm>
void add__lm(ValueStack& values) {
    auto b = std::static_pointer_cast<Tm>(values.back());
    values.pop_back();
    auto a = std::static_pointer_cast<Tl>(values.back());
    values.pop_back();

    if (b->VALUE_TYPE == ValueToken::ASSIGNABLE) {
        *b = *a + *b;
        values.push_back(b);
        return;
    }

    values.push_back(std::make_shared<Tm>(*a + *b));
}

template <typename Tm, typename Tl>
void add__ml(ValueStack& values) {
    auto b = std::static_pointer_cast<Tl>(values.back());
    values.pop_back();
    auto a = std::static_pointer_cast<Tm>(values.back());
    values.pop_back();

    if (a->VALUE_TYPE == ValueToken::ASSIGNABLE) {
        *a = *a + *b;
        values.push_back(a);
        return;
    }

    values.push_back(std::make_shared<Tm>(*a + *b));
}

template <typename T>
void subtract__(ValueStack& values) {
    auto b = std::static_pointer_cast<T>(values.back());
    values.pop_back();
    auto a = std::static_pointer_cast<T>(values.back());
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

    values.push_back(std::make_shared<T>(*a - *b));
}

template <typename Tl, typename Tm>
void subtract__lm(ValueStack& values) {
    auto b = std::static_pointer_cast<Tm>(values.back());
    values.pop_back();
    auto a = std::static_pointer_cast<Tl>(values.back());
    values.pop_back();

    if (b->VALUE_TYPE == ValueToken::ASSIGNABLE) {
        *b = *a - *b;
        values.push_back(b);
        return;
    }

    values.push_back(std::make_shared<Tm>(*a - *b));
}

template <typename Tm, typename Tl>
void subtract__ml(ValueStack& values) {
    auto b = std::static_pointer_cast<Tl>(values.back());
    values.pop_back();
    auto a = std::static_pointer_cast<Tm>(values.back());
    values.pop_back();

    if (a->VALUE_TYPE == ValueToken::ASSIGNABLE) {
        *a = *a - *b;
        values.push_back(a);
        return;
    }

    values.push_back(std::make_shared<Tm>(*a - *b));
}

template <typename T>
void multiply__(ValueStack& values) {
    auto b = std::static_pointer_cast<T>(values.back());
    values.pop_back();
    auto a = std::static_pointer_cast<T>(values.back());
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

    values.push_back(std::make_shared<T>(*a * *b));
}

template <typename Tl, typename Tm>
void multiply__lm(ValueStack& values) {
    auto b = std::static_pointer_cast<Tm>(values.back());
    values.pop_back();
    auto a = std::static_pointer_cast<Tl>(values.back());
    values.pop_back();

    if (b->VALUE_TYPE == ValueToken::ASSIGNABLE) {
        *b = *a * *b;
        values.push_back(b);
        return;
    }

    values.push_back(std::make_shared<Tm>(*a * *b));
}

template <typename Tm, typename Tl>
void multiply__ml(ValueStack& values) {
    auto b = std::static_pointer_cast<Tl>(values.back());
    values.pop_back();
    auto a = std::static_pointer_cast<Tm>(values.back());
    values.pop_back();

    if (a->VALUE_TYPE == ValueToken::ASSIGNABLE) {
        *a = *a * *b;
        values.push_back(a);
        return;
    }

    values.push_back(std::make_shared<Tm>(*a * *b));
}

template <typename T>
void divide__(ValueStack& values) {
    auto b = std::static_pointer_cast<T>(values.back());
    values.pop_back();
    auto a = std::static_pointer_cast<T>(values.back());
    values.pop_back();

    if (a->VALUE_TYPE == ValueToken::ASSIGNABLE) {
        *a = *a / *b;
        values.push_back(a);
        return;
    }

    if (b->VALUE_TYPE == ValueToken::ASSIGNABLE) {
        *b = *a / *b;
        values.push_back(b);
        return;
    }

    values.push_back(std::make_shared<T>(*a / *b));
}

template <>
void divide__<IntegerToken>(ValueStack& values) {
    auto b = std::static_pointer_cast<IntegerToken>(values.back());
    values.pop_back();
    auto a = std::static_pointer_cast<IntegerToken>(values.back());
    values.pop_back();

    if (*a % *b == 0) {
        if (a->VALUE_TYPE == ValueToken::ASSIGNABLE) {
            *a = *a / *b;
            values.push_back(a);
            return;
        }

        if (b->VALUE_TYPE == ValueToken::ASSIGNABLE) {
            *b = *a / *b;
            values.push_back(b);
            return;
        }

        values.push_back(std::make_shared<IntegerToken>(*a / *b));
        return;
    }

    long long valA = *a;

    values.push_back(std::make_shared<FloatToken>((long double)valA / *b));
}

template <typename Tl, typename Tm>
void divide__lm(ValueStack& values) {
    auto b = std::static_pointer_cast<Tm>(values.back());
    values.pop_back();
    auto a = std::static_pointer_cast<Tl>(values.back());
    values.pop_back();

    if (b->VALUE_TYPE == ValueToken::ASSIGNABLE) {
        *b = *a / *b;
        values.push_back(b);
        return;
    }

    values.push_back(std::make_shared<Tm>(*a / *b));
}

template <typename Tm, typename Tl>
void divide__ml(ValueStack& values) {
    auto b = std::static_pointer_cast<Tl>(values.back());
    values.pop_back();
    auto a = std::static_pointer_cast<Tm>(values.back());
    values.pop_back();

    if (a->VALUE_TYPE == ValueToken::ASSIGNABLE) {
        *a = *a / *b;
        values.push_back(a);
        return;
    }

    values.push_back(std::make_shared<Tm>(*a / *b));
}
}  // namespace ops

namespace {
using namespace base_func;
}

void initBasePackage(Package&, const Settings&) {
    plus->bind(pats::int_int, ops::add__<IntegerToken>);
    plus->bind(pats::int_float, ops::add__lm<IntegerToken, FloatToken>);
    plus->bind(pats::float_int, ops::add__ml<FloatToken, IntegerToken>);
    plus->bind(pats::float_float, ops::add__<FloatToken>);

    minus->bind(pats::int_int, ops::subtract__<IntegerToken>);
    minus->bind(pats::int_float, ops::subtract__lm<IntegerToken, FloatToken>);
    minus->bind(pats::float_int, ops::subtract__ml<FloatToken, IntegerToken>);
    minus->bind(pats::float_float, ops::subtract__<FloatToken>);

    times->bind(pats::int_int, ops::multiply__<IntegerToken>);
    times->bind(pats::int_float, ops::multiply__lm<IntegerToken, FloatToken>);
    times->bind(pats::float_int, ops::multiply__ml<FloatToken, IntegerToken>);
    times->bind(pats::float_float, ops::multiply__<FloatToken>);

    divide->bind(pats::int_int, ops::divide__<IntegerToken>);
    divide->bind(pats::int_float, ops::divide__lm<IntegerToken, FloatToken>);
    divide->bind(pats::float_int, ops::divide__ml<FloatToken, IntegerToken>);
    divide->bind(pats::float_float, ops::divide__<FloatToken>);
}

void preloadBasePackage(Package& p, const Settings&) {
    p.addOperator(base_func::plus);
    p.addOperator(base_func::minus);
    p.addOperator(base_func::times);
    p.addOperator(base_func::divide);
}

}  // namespace

Package Package::basePackage{"base", initBasePackage, preloadBasePackage};