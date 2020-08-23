// Internal module for raising asserts

#pragma once
#ifndef FILE_LP3_SIMS_ASSERTS_HPP
#define FILE_LP3_SIMS_ASSERTS_HPP

#include <stdexcept>

namespace lp3::sims {
class Lp3SimsAssertError : public std::logic_error {
  public:
    Lp3SimsAssertError(const char * msg) : std::logic_error(msg) {}
};
} // namespace lp3::sims

#ifdef LP3_SIMS_DEBUG
#define LP3_SIMS_ASSERT2(condition, message)                                   \
    {                                                                          \
        if (!(condition)) {                                                    \
            throw Lp3SimsAssertError(message);                                 \
        }                                                                      \
    }
#define LP3_SIMS_ASSERT(condition) LP3_SIMS_ASSERT2(condition, "Assert error")
#else
#define LP3_SIMS_ASSERT2(condition, meessage)                                  \
    {}
#define LP3_SIMS_ASSERT(condition)                                             \
    {}
#endif

#if defined(__EMSCRIPTEN__)
  // On Emscripten exceptions may not be able to be caught correctly
#define LP3_SIMS_REQUIRE_ASSERT_FAILURE(code)                                  \
    {}
#else
#define LP3_SIMS_REQUIRE_ASSERT_FAILURE(code)                                  \
    { REQUIRE_THROWS_AS(code, ::lp3::sims::Lp3SimsAssertError); }
#endif

#endif
