#pragma once

#include <exception>
#include <cassert>

#define STD_EXCEPTION_WRAPPER(cmd) auto _wrp = [&]() { \
    try { cmd; } \
    catch (const std::exception&) { return true; } \
    return false; \
};

#define ASSERT_STD_EXCEPTION(cmd) { STD_EXCEPTION_WRAPPER(cmd) \
    assert(_wrp()); }

