#ifndef TOKENS__VALUES__VALUE_TOKEN_H_
#define TOKENS__VALUES__VALUE_TOKEN_H_

#include "../token.h"

class ValueToken : public Token {
   public:
    enum ValueType { ASSIGNABLE, VARIABLE, CONSTANT };

    class NumType : public IOutputtable {
        static unsigned short nextId;
        const unsigned short ID;

       public:
        const std::string DESCRIPT;
        const static NumType TYPE_UNDEFINED;

       public:
        NumType(std::string description);
        NumType(const NumType&) = delete;

       public:
        std::string getDescription() const;
        unsigned short getId() const;
        virtual void outputTo(std::ostream&) const override;

        operator std::string() const;
        friend bool operator==(const NumType&, const NumType&);

        NumType& operator=(const NumType&) = delete;
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