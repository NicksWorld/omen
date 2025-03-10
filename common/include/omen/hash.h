#include <cstdint>
#include <string_view>

namespace omen::hash {
/// Hashes the given data via a non-cryptographic hash
uint64_t hash_value(const void *data, std::size_t size);

/// Represents a hashed value
///
/// The hash used is non-cryptographic and is intended for use with paths and
/// names. As such, this should not be used to hash sensitive information.
class HashId {
public:
  /// Hash the given string
  explicit HashId(const std::string_view &view)
      : hash(hash_value(view.data(), view.size())) {};
  /// Hash a slice of raw data
  explicit HashId(const void *data, std::size_t size)
      : hash(hash_value(data, size)) {};

  bool operator==(const HashId &other) { return hash == other.hash; }
  bool operator!=(const HashId &other) { return hash != other.hash; }

  /// Get the raw hash value
  uint64_t get() { return hash; }

private:
  uint64_t hash;
};
}
