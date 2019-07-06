#ifndef CALC__TOKEN_STRINGIFIER_H_
#define CALC__TOKEN_STRINGIFIER_H_

#include <sstream>

#include "calculator/FixedPtStringifier.h"
#include "calculator/Observer.h"
#include "calculator/Settings.h"
#include "calculator/ValueToken.h"

/**
 * @brief Converts tokens into their representative strings.
 *
 */
class TokenStringifier : public Observer<const SettingsImpl&> {
   public:
    /**
     * @brief Constructs an instance with the given settings
     *
     * @param   settings    Settings.
     */
    TokenStringifier(const SettingsImpl& settings);

    /**
     * @brief Updates with the given settings.
     *
     * @param   settings    Settings.
     */
    virtual void onUpdate(const SettingsImpl& settings) override;

    /**
     * @brief Stringifies an `IntegerToken`.
     *
     * @param   token   `IntegerToken` to stringify.
     */
    std::string operator()(const refactor::IntegerToken& token) const;

   private:
    SettingsImpl s;
    FixedPtStringifier fixedPtStringify;
};

#endif