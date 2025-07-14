//
// RTP header file selector based on compiler
// This file automatically includes the correct RTP implementation
// based on the compiler being used
//

#ifndef RTP_COMPILER_SELECTOR_HPP
#define RTP_COMPILER_SELECTOR_HPP

#if defined(_MSC_VER)
    // MSVC compiler - use version with #pragma pack instead of __attribute__((packed))
    #include "RTP_msvc.hpp"
#else
    // GCC/Clang compiler - use original version with __attribute__((packed))
    #include "RTP.hpp"
#endif

#endif // RTP_COMPILER_SELECTOR_HPP
