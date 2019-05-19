#ifndef TOKENS__VALUES__VALUE_TOKEN_H_
#define TOKENS__VALUES__VALUE_TOKEN_H_

#include "../token.h"

class ValueToken : public Token {
   public:
    enum class ValueType { CONST, VAR };

    class NumericType : public IOutputtable {
       public:
        const std::string DESCRIPT;

        static const NumericType TYPE_UNDEFINED;

       public:
        NumericType(std::string description) : DESCRIPT{description} {}

       public:
        std::string getDescription() const;
        virtual void outputTo(std::ostream&) const override;

        operator std::string() const;
    };

   public:
    const ValueType VALUE_TYPE;

   public:
    ValueToken(const ValueType valueType = ValueType::CONST);
    virtual const NumericType const& getNumericType() const;

    virtual bool isZero() const = 0;
    virtual bool isUnity() const = 0;
};

#endif