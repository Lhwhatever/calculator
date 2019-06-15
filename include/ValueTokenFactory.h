#ifndef CALC__VALUE_TOKEN_FACTORY_H_
#define CALC__VALUE_TOKEN_FACTORY_H_

#include <memory>

#include "ValueToken.h"

using TokenPtr = std::shared_ptr<AbstractToken>;

namespace verbose {

template <class T>
class ValueTokenFactory {
    static_assert(ValueTypes<T>::ALLOWED && "This type is not supported"));

   public:
    virtual TokenPtr create(const std::string&) const = 0;
};

}  // namespace verbose

template <class T>
using ValueTokenFactory = verbose::ValueTokenFactory<T::type>;

#endif