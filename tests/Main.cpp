// Compile Command
// g++ -isystem../rapidcheck/include -I../include -L../rapidcheck -I../include Main.cpp -lrapidcheck

#include <iomanip>
#include <iostream>
#include <bitset>
#include <rapidcheck.h>
#include "parity.hpp"


template <uint BITS, typename DataType>
DataType
brute_force_even_parity(const DataType& data) {
  DataType result = data;
  for (uint i = 1; i < BITS; i <<= 1) {
    result = result ^ (result >> i);
  }
  return result & 1;
}

template <uint BITS, typename DataType>
DataType
brute_force_odd_parity(const DataType& data) {
  return 1 - brute_force_even_parity<BITS, DataType>(data);
}


template <uint I, uint J=1>
void check() {
  rc::check(std::to_string(I) + " bit even parity", [](const uint64_t& data) { RC_ASSERT((brute_force_even_parity<I, uint64_t>(data & Parity<I>::template DataMask<uint64_t>::value)) == (Parity<I, J>::even(data))); });
  rc::check(std::to_string(I) + " bit odd parity",  [](const uint64_t& data) { RC_ASSERT((brute_force_odd_parity< I, uint64_t>(data & Parity<I>::template DataMask<uint64_t>::value)) == (Parity<I, J>::odd(data))); });
}


int main() {
  check<1>();
  check<2>();
  check<3>();
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
