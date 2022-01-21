#include <cstdint>
#include <cstddef>

template <typename T> struct dummy {};

template struct dummy<std::uint8_t>;
template struct dummy<std::uint16_t>;
template struct dummy<std::uint32_t>;
template struct dummy<std::uint64_t>;
// If this program compiles, std::size_t is different from all other types above
template struct dummy<std::size_t>;

int main(int, char*[]) {}
