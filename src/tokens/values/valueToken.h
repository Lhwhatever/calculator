#ifndef TOKENS__VALUES__VALUE_TOKEN_H_
#define TOKENS__VALUES__VALUE_TOKEN_H_

#include "../token.h"

namespace {
using byte = unsigned char;
}

class ValueToken : public Token {
   public:
    enum ValueType { ASSIGNABLE, VARIABLE, CONSTANT };

    class NumType : public IOutputtable {
        static byte nextId;
        const byte ID;

       public:
        const std::string DESCRIPT;

       public:
        NumType(std::string description);

       public:
        std::string getDescription() const;
        unsigned long getId() const;
        virtual void outputTo(std::ostream&) const override;

        operator std::string() const;
    };

   public:
    const ValueType VALUE_TYPE;

   protected:
    ValueToken(const ValueType valueType = ASSIGNABLE);
    virtual ~ValueToken();

   public:
    virtual const NumType& getNumType() const = 0;

    virtual bool isZero() const = 0;
    virtual bool isUnity() const = 0;
};

#endif