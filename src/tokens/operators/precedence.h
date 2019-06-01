#ifndef TOKENS__FUNCTIONAL_PRECEDENCE_H_
#define TOKENS__FUNCTIONAL_PRECEDENCE_H_

struct Precedence {
    enum Associativity : char { ASSOC_L2R = 0, ASSOC_R2L = -1 };

    Associativity assoc;

   private:
    short level;

   public:
    Precedence(short level, Associativity assoc);

   public:
    operator short() const;
    short getLevel() const;
    void setLevel(const short newLevel);

    friend bool operator==(Precedence&, Precedence&);
    friend bool operator!=(Precedence&, Precedence&);
    friend bool operator>(Precedence&, Precedence&);
    friend bool operator<(Precedence&, Precedence&);
    friend bool operator>=(Precedence&, Precedence&);
    friend bool operator<=(Precedence&, Precedence&);
};

#endif