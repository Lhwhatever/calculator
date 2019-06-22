#include <memory>

#include "gtest/gtest.h"

#include "calculator/TokenEmplacerForRpn.h"
#include "calculator/ValueToken.h"

namespace {
template <typename T>
inline T popFromQueue(std::deque<T>& q) {
    T x{std::move(q.front())};
    q.pop_front();
    return x;
}

template <typename T, typename... Args>
inline std::shared_ptr<T> makeTokenPtr(Args&&... args) {
    return std::shared_ptr<T>(new T{std::forward<Args>(args)...});
}

inline TokenEmplacerForRpn makeEmplacer(std::vector<TokenPtr> tokens) {
    TokenEmplacerForRpn emplacer;
    for (auto& token : tokens) emplacer.emplace(std::move(token));
    return emplacer;
}

template <typename T>
inline std::shared_ptr<T> getToken(TokenQueue& queue) {
    return std::dynamic_pointer_cast<T>(popFromQueue(queue));
}
}  // namespace

#define CHECK_VAL_FROM_Q(QUEUE, TYPE, VAL) \
    {                                      \
        auto token{getToken<TYPE>(QUEUE)}; \
        ASSERT_NE(token, nullptr);         \
        EXPECT_EQ(token->value, VAL);      \
    }

TEST(UnitTestForTokenEmplacerForRpn, ReturnsTokensInSequence) {
    EXPECT_EQ(TokenEmplacerForRpn{}.extract().size(), 0);

    {
        auto queue{
            makeEmplacer({makeTokenPtr<refactor::IntegerToken>(5)}).extract()};
        ASSERT_EQ(queue.size(), 1);
        CHECK_VAL_FROM_Q(queue, refactor::IntegerToken, 5);
    }

    {
        auto queue{makeEmplacer({makeTokenPtr<refactor::IntegerToken>(5),
                                 makeTokenPtr<refactor::IntegerToken>(10),
                                 makeTokenPtr<refactor::IntegerToken>(-2),
                                 makeTokenPtr<refactor::IntegerToken>(0)})
                       .extract()};
        ASSERT_EQ(queue.size(), 4);
        CHECK_VAL_FROM_Q(queue, refactor::IntegerToken, 5);
        CHECK_VAL_FROM_Q(queue, refactor::IntegerToken, 10);
        CHECK_VAL_FROM_Q(queue, refactor::IntegerToken, -2);
        CHECK_VAL_FROM_Q(queue, refactor::IntegerToken, 0);
    }
}

TEST(UnitTestForTokenEmplacerForRpn, ClearsTokenOnReset) {
    auto emplacer{makeEmplacer({makeTokenPtr<refactor::IntegerToken>(5)})};
    emplacer.reset();
    EXPECT_EQ(emplacer.extract().size(), 0);
}

TEST(UnitTestForTokenEmplacerForRpn, ClearsTokenOnExtract) {
    auto emplacer{makeEmplacer({makeTokenPtr<refactor::IntegerToken>(5)})};
    emplacer.extract();
    EXPECT_EQ(emplacer.extract().size(), 0);
    emplacer.emplace(makeTokenPtr<refactor::IntegerToken>(5));
    auto queue{emplacer.extract()};
    CHECK_VAL_FROM_Q(queue, refactor::IntegerToken, 5);
}
