#ifndef CALC__ABSTRACT_TOKEN_H_
#define CALC__ABSTRACT_TOKEN_H_

class AbstractTokenHandler;

/** @defgroup tokens
 * @brief Represents the smallest unit in an expression.
 *
 */

/** @ingroup tokens
 * @brief Interface that represents a token in an expression.
 *
 */
class AbstractToken {
   public:
    AbstractToken() = default;          /**< Default constructor */
    virtual ~AbstractToken() = default; /**< Default destructor (virtual) */
    AbstractToken(const AbstractToken&) = default; /**< Copy constructor */
    AbstractToken(AbstractToken&&) = default;      /**< Move constructor */
    AbstractToken& operator=(const AbstractToken&) =
        default;                                         /**< Copy assignment */
    AbstractToken& operator=(AbstractToken&&) = default; /**< Move assignment */

    /*
     * @brief Implements the Visitor pattern on tokens.
     *
     * This member function is called when reading tokens from a queue
     * (representing the parsed expression). It is used in selecting the
     * appropriate branch based on the type of token encountered.
     *
     * @param[in]   handler Concrete instance of `AbstractTokenHandler` that
     * implements `visit()` methods for each subclass of `AbstractToken`.
     */
    // virtual void accept(AbstractTokenHandler& handler) const = 0;
};

#endif