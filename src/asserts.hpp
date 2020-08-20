// Internal module for raising asserts

#pragma once
#ifndef FILE_LP3_SIMS_ASSERTS_HPP
#define FILE_LP3_SIMS_ASSERTS_HPP

#include <stdexcept>


namespace lp3::sims {
    class Lp3SimsAssertError : public std::logic_error {
    public:
        Lp3SimsAssertError(const char * msg)
        :   std::logic_error(msg) {}
    };
}


#ifdef LP3_SIMS_DEBUG
    #define LP3_SIMS_ASSERT2(condition, message)  \
            { if (!(condition)) { \
                throw Lp3SimsAssertError(message); \
            } }
    #define LP3_SIMS_ASSERT(condition)  \
            LP3_SIMS_ASSERT2(condition, "Assert error")
#else
    #define LP3_SIMS_ASSERT2(condition, meessage) {}
    #define LP3_SIMS_ASSERT(condition) {}
#endif

#define LP3_SIMS_REQUIRE_ASSERT_FAILURE(code) \
        {   \
            REQUIRE_THROWS_AS(code, ::lp3::sims::Lp3SimsAssertError); \
        }

#endif
