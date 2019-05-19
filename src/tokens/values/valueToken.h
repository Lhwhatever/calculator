#ifndef TOKENS__VALUES__VALUE_TOKEN_H_
#define TOKENS__VALUES__VALUE_TOKEN_H_

#include "../token.h"

class ValueToken : public Token {
   public:
    enum class ValueType { CONST, VAR };

    class NumType : public IOutputtable {
       public:
        const std::string DESCRIPT;

       public:
        NumType(std::string description) : DESCRIPT{description} {}

       public:
        std::string getDescription() const;
        virtual void outputTo(std::ostream&) const override;

        operator std::string() const;
    };

   public:
    const ValueType VALUE_TYPE;

   protected:
    ValueToken(const ValueType valueType = ValueType::CONST);
    virtual ~ValueToken();

   public:
    virtual const NumType& getNumType() const = 0;

    virtual bool isZero() const = 0;
    virtual bool isUnity() const = 0;
};

#endif