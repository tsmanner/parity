---
title: Home
nav_order: 1
---

# Parity

Parity is a modern C++ template library for efficiently calculating bit parity.
It uses cascading XORs to calculate the parity for each parity group, with a
complexity of `ParityGroups * log2(ParityGroupSize)`.  The `Parity` struct
template is specialized by the total number of bits to calculate parity over,
and the size of the parity groups it should be split into.  A compile-time
static assertion error is raised if the parity group size isn't a factor of
the data size.  Two static functions within the `Parity` namespace exist,
`even` and `odd`, which are templated with the data type being operated on.
These two functions will mask input data down to the declared size, so it is
safe to use with variables that might have ones to the left of the payload.


## Example

```cpp
#include <iostream>
#include <parity.hpp>

int main() {
  uint32_t data = 0b01010101010101110101010101010111;
  std::cout << "parity = " << Parity<6>::even(data) << "\n";
  std::cout << "parity = " << Parity<6, 2>::even(data) << "\n";
  std::cout << "parity = " << Parity<32>::even(data) << "\n";
  std::cout << "parity = " << Parity<32, 4>::even(data) << "\n";
  std::cout << "parity = " << Parity<32, 4>::odd(data) << "\n";
  return 0;
}
```

Output:
```
parity = 0
parity = 3
parity = 0
parity = 5
parity = 10
```
