#ifndef TOKENS__VALUES__INTEGER_TOKEN_H_
#define TOKENS__VALUES__INTEGER_TOKEN_H_

#include "valueToken.h"

class IntegerToken : public ValueToken {
   private:
    long long value;

   public:
    static const IntegerToken ZERO;
    static const IntegerToken ONE;
    static const NumType TYPE_INTEGER;

   public:
    IntegerToken(const long long value,
                 const ValueToken::ValueType = ValueToken::ASSIGNABLE);

   protected:
    virtual void outputTo(std::ostream&) const override;

   public:
    long long getValue() const;
    void setValue(const long long value);

    virtual bool isZero() const override;
    virtual bool isUnity() const override;

    virtual const NumType& getNumType() const override;

    IntegerToken& operator=(const int value);
    IntegerToken& operator=(const long value);
    IntegerToken& operator=(const long long value);
    operator long long();
    virtual std::string toString() const;
};

#endif