#pragma once

#include <exception>
#include <cassert>

#define STD_EXCEPTION_CHECKER(cmd) auto _wrp = [&]() { \
    try { cmd; } \
    catch (const std::exception&) { return true; } \
    return false; \
};

#define ANY_EXCEPTION_CHECKER(cmd) auto _wrp = [&]() { \
    try { cmd; } \
    catch (...) { return true; } \
    return false; \
};

#define ASSERT_STD_EXCEPTION(cmd) { STD_EXCEPTION_CHECKER(cmd) \
    assert(_wrp()); }

#define ASSERT_NO_EXCEPTION(cmd) { ANY_EXCEPTION_CHECKER(cmd) \
    assert(!_wrp()); }
