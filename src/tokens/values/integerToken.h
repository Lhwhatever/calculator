#ifndef TOKENS__VALUES__INTEGER_TOKEN_H_
#define TOKENS__VALUES__INTEGER_TOKEN_H_

#include "valueToken.h"

class IntegerToken : public ValueToken {
   private:
    long value;

   public:
    static IntegerToken ZERO;
    static IntegerToken ONE;
    static const NumType TYPE_INTEGER;

   public:
    IntegerToken(const long,
                 const ValueToken::ValueType = ValueToken::ValueType::CONST);

   protected:
    virtual void outputTo(std::ostream&) const override;

   public:
    long getValue() const;
    void setValue(const long);

    virtual bool isZero() const override;
    virtual bool isUnity() const override;

    virtual const NumType& getNumType() const override;

    IntegerToken& operator=(const long);
    operator long();
    virtual std::string toString() const;
};

#endif