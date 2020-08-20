#ifndef LP3_SIMS_CONFIG_HPP
#define LP3_SIMS_CONFIG_HPP
#pragma once

#if defined(_WIN32)                                                            \
        && (defined(BUILD_SHARED_LIBS) || defined(LP3_SIMS_API_DYNAMIC))
#if defined(LP3_SIMS_API_CREATE)
#define LP3_SIMS_API __declspec(dllexport)
#else
#define LP3_SIMS_API __declspec(dllimport)
#endif
#else
#define LP3_SIMS_API
#endif

#endif
