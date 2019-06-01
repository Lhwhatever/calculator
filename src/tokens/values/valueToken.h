#ifndef TOKENS__VALUES__VALUE_TOKEN_H_
#define TOKENS__VALUES__VALUE_TOKEN_H_

#include <string>
#include <vector>

#include "../token.h"

struct ValueToken : public Token {
    enum ValueType : char { ASSIGNABLE, VARIABLE, CONSTANT };

    class NumType;
    using NumTypeR = std::reference_wrapper<const ValueToken::NumType>;

    class NumType final {
        static std::vector<NumTypeR> types;

       public:
        const static NumType TYPE_UNDEFINED;
        const unsigned short ID;
        const std::string NAME;

       public:
        NumType(const std::string& name);

       public:
        NumType(const NumType&) = delete;
        static const NumType& getById(const unsigned short id);

        friend bool operator==(const NumType&, const NumType&);
        NumType& operator=(const NumType&) = delete;
    };

    const ValueType TYPE_VALUE;
    const NumType& TYPE_NUM;

   protected:
    ValueToken(const NumType& numType, const ValueType valueType = ASSIGNABLE);

   public:
    operator ValueType() const;
};

#endif