// Compile Command
// g++ -isystem../rapidcheck/include -I../include -L../rapidcheck -I../include Main.cpp -lrapidcheck

#include <bitset>
#include <rapidcheck.h>
#include "parity.hpp"


template <uint BITS, typename DataType>
DataType
brute_force_even_parity(const DataType& data) {
  DataType parity = 0;
  for (uint8_t i = 0; i < BITS; ++i) {
    if ((data >> i) & 1) {
      parity = 1 - parity;
    }
  }
  return parity;
}

template <uint BITS, typename DataType>
DataType
brute_force_odd_parity(const DataType& data) {
  return 1 - brute_force_even_parity<BITS, DataType>(data);
}


template <uint I>
void check() {
  rc::check(std::to_string(I) + " bit even parity", [](const uint64_t& data) { RC_ASSERT((brute_force_even_parity<I, uint64_t>(data)) == Parity<I>::even(data)); });
  rc::check(std::to_string(I) + " bit odd parity",  [](const uint64_t& data) { RC_ASSERT((brute_force_odd_parity< I, uint64_t>(data)) == Parity<I>::odd(data)); });
}


int main() {
  check<1>();
  check<2>();
  check<8>();
  check<9>();
  check<15>();
  check<16>();
  check<17>();
  check<31>();
  check<32>();
  check<33>();
  check<63>();
  check<64>();
  return 0;
}
