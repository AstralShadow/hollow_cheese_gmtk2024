#ifndef INCLUDE_UTILS_TYPES_HPP
#define INCLUDE_UTILS_TYPES_HPP

#include <cstdint>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

#ifndef __EMSCRIPTEN__
    using std::size_t;
#endif

#endif // INCLUDE_UTILS_TYPES_HPP
