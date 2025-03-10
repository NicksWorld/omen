#include "omen/hash.h"

#include <cstddef>
#include <cstdint>

// FNV 64bit hash constants
constexpr uint64_t FNV_OFFSET_BASIS = 14695981039346656037u;
constexpr uint64_t FNV_PRIME = 1099511628211u;

// Calculate the FNV-1a hash
uint64_t omen::hash::hash_value(const void *data, std::size_t len) {
  const uint8_t *data_ptr = static_cast<const uint8_t *>(data);
  uint64_t hash = FNV_OFFSET_BASIS;

  for (; len > 0; --len) {
    hash ^= *(data_ptr++);
    hash *= FNV_PRIME;
  }

  return hash;
}
