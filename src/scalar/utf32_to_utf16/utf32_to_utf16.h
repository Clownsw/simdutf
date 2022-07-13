#ifndef SIMDUTF_UTF32_TO_UTF16_H
#define SIMDUTF_UTF32_TO_UTF16_H

namespace simdutf {
namespace scalar {
namespace {
namespace utf32_to_utf16 {

inline size_t convert(const char32_t* buf, size_t len, char16_t* utf16_output) {
  const uint32_t *data = reinterpret_cast<const uint32_t *>(buf);
  size_t pos = 0;
  char16_t* start{utf16_output};
  while (pos < len) {
    uint32_t word = data[pos];
    if((word & 0xFFFF0000)==0) {
      if (word >= 0xD800 && word <= 0xDFFF) { return 0; }
      // will not generate a surrogate pair
      *utf16_output++ = char16_t(word);
      pos++;
    } else {
      // will generate a surrogate pair
      if (word > 0x10FFFF) { return 0; }
      word -= 0x10000;
      *utf16_output++ = char16_t(0xD800 + (word >> 10));
      *utf16_output++ = char16_t(0xDC00 + (word & 0x3FF));
      pos++;
    }
  }
  return utf16_output - start;
}

} // utf32_to_utf16 namespace
} // unnamed namespace
} // namespace scalar
} // namespace simdutf

#endif