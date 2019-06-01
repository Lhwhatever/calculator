#ifndef CALC__TOKENS__TOKEN__H_
#define CALC__TOKENS__TOKEN__H_

struct Token {
    enum TokenCategory : char { CAT_VALUE, CAT_FUNC };
    const TokenCategory CATEGORY;

   protected:
    Token(const TokenCategory);

   public:
    operator TokenCategory() const;
};

#endif