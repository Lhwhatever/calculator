#include "../tokens/values/floatToken.h"
#include "../tokens/values/integerToken.h"
#include "package.h"

namespace base_func {

FuncTokenSP add;
FuncTokenSP subtract;
FuncTokenSP minus;
FuncTokenSP multiply;
FuncTokenSP divide;

}  // namespace base_func

namespace pats {
const ValueToken::NumType& tInt() { return IntegerToken::TYPE_INTEGER; }
const ValueToken::NumType& tFloat() { return FloatToken::TYPE_FLOAT; }

NumTypePattern int1{tInt()};
NumTypePattern float1{tFloat()};

NumTypePattern int_int{tInt(), tInt()};
NumTypePattern int_float{tInt(), tFloat()};
NumTypePattern float_int{tFloat(), tInt()};
NumTypePattern float_float{tFloat(), tFloat()};
}  // namespace pats

namespace {
using IntegerTP = std::shared_ptr<IntegerToken>;

namespace ops {
template <typename T>
void add__(ValueStack& values) {
    auto b = std::static_pointer_cast<T>(values.back());
    values.pop_back();
    auto a = std::static_pointer_cast<T>(values.back());
    values.pop_back();

    if (a->TYPE_VALUE == ValueToken::ASSIGNABLE) {
        *a = *a + *b;
        values.push_back(a);
        return;
    }

    if (b->TYPE_VALUE == ValueToken::ASSIGNABLE) {
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

    if (b->TYPE_VALUE == ValueToken::ASSIGNABLE) {
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

    if (a->TYPE_VALUE == ValueToken::ASSIGNABLE) {
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

    if (a->TYPE_VALUE == ValueToken::ASSIGNABLE) {
        *a = *a - *b;
        values.push_back(a);
        return;
    }

    if (b->TYPE_VALUE == ValueToken::ASSIGNABLE) {
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

    if (b->TYPE_VALUE == ValueToken::ASSIGNABLE) {
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

    if (a->TYPE_VALUE == ValueToken::ASSIGNABLE) {
        *a = *a - *b;
        values.push_back(a);
        return;
    }

    values.push_back(std::make_shared<Tm>(*a - *b));
}

template <typename T>
void minus__(ValueStack& values) {
    auto a = std::static_pointer_cast<T>(values.back());

    if (a->TYPE_VALUE == ValueToken::ASSIGNABLE) {
        *a = -*a;
        values.push_back(a);
        return;
    }

    values.pop_back();
    values.push_back(std::make_shared<T>(-*a));
}

template <typename T>
void multiply__(ValueStack& values) {
    auto b = std::static_pointer_cast<T>(values.back());
    values.pop_back();
    auto a = std::static_pointer_cast<T>(values.back());
    values.pop_back();

    if (a->TYPE_VALUE == ValueToken::ASSIGNABLE) {
        *a = *a * *b;
        values.push_back(a);
        return;
    }

    if (b->TYPE_VALUE == ValueToken::ASSIGNABLE) {
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

    if (b->TYPE_VALUE == ValueToken::ASSIGNABLE) {
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

    if (a->TYPE_VALUE == ValueToken::ASSIGNABLE) {
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

    if (a->TYPE_VALUE == ValueToken::ASSIGNABLE) {
        *a = *a / *b;
        values.push_back(a);
        return;
    }

    if (b->TYPE_VALUE == ValueToken::ASSIGNABLE) {
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

    if (*a % *b) {
        long long valA = *a;
        values.push_back(std::make_shared<FloatToken>((long double)valA / *b));
        return;
    }

    if (a->TYPE_VALUE == ValueToken::ASSIGNABLE) {
        *a = *a / *b;
        values.push_back(a);
        return;
    }

    if (b->TYPE_VALUE == ValueToken::ASSIGNABLE) {
        *b = *a / *b;
        values.push_back(b);
        return;
    }

    values.push_back(std::make_shared<IntegerToken>(*a / *b));
}

template <typename Tl, typename Tm>
void divide__lm(ValueStack& values) {
    auto b = std::static_pointer_cast<Tm>(values.back());
    values.pop_back();
    auto a = std::static_pointer_cast<Tl>(values.back());
    values.pop_back();

    if (b->TYPE_VALUE == ValueToken::ASSIGNABLE) {
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

    if (a->TYPE_VALUE == ValueToken::ASSIGNABLE) {
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

void initBasePackage(Package& p, const Settings&) {
    add = p.createInfixOperator("add", 4, Precedence::ASSOC_L2R, "+");
    subtract = p.createInfixOperator("subtract", 4, Precedence::ASSOC_L2R, "-");
    minus = p.createPrefixOperator("minus", 6, "-", "~");
    multiply = p.createInfixOperator("multiply", 5, Precedence::ASSOC_L2R, "*");
    divide = p.createInfixOperator("divide", 5, Precedence::ASSOC_L2R, "/");
}

void preloadBasePackage(Package&, const Settings&) {
    add->bind(pats::int_int, ops::add__<IntegerToken>);
    add->bind(pats::int_float, ops::add__lm<IntegerToken, FloatToken>);
    add->bind(pats::float_int, ops::add__ml<FloatToken, IntegerToken>);
    add->bind(pats::float_float, ops::add__<FloatToken>);

    subtract->bind(pats::int_int, ops::subtract__<IntegerToken>);
    subtract->bind(pats::int_float,
                   ops::subtract__lm<IntegerToken, FloatToken>);
    subtract->bind(pats::float_int,
                   ops::subtract__ml<FloatToken, IntegerToken>);
    subtract->bind(pats::float_float, ops::subtract__<FloatToken>);

    minus->bind(pats::int1, ops::minus__<IntegerToken>);
    minus->bind(pats::float1, ops::minus__<FloatToken>);

    multiply->bind(pats::int_int, ops::multiply__<IntegerToken>);
    multiply->bind(pats::int_float,
                   ops::multiply__lm<IntegerToken, FloatToken>);
    multiply->bind(pats::float_int,
                   ops::multiply__ml<FloatToken, IntegerToken>);
    multiply->bind(pats::float_float, ops::multiply__<FloatToken>);

    divide->bind(pats::int_int, ops::divide__<IntegerToken>);
    divide->bind(pats::int_float, ops::divide__lm<IntegerToken, FloatToken>);
    divide->bind(pats::float_int, ops::divide__ml<FloatToken, IntegerToken>);
    divide->bind(pats::float_float, ops::divide__<FloatToken>);
}

void loadBasePackage(Package&, const Settings&) {}

void reloadBasePackage(Package&, const Settings&) {}

}  // namespace

Package Package::basePackage{"base", initBasePackage, preloadBasePackage,
                             loadBasePackage, reloadBasePackage};