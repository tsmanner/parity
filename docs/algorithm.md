---
title: The Algorithm
---

# The Algorithm

Fundamentally, parity calculations count the 1s in a bit-string.  Even parity
makes the total number of 1s in the data + parity an even number, meaning that
even parity over input data with an odd number of 1s yields a 1.  Likewise, odd
parity makes the total odd, so it yields a 1 when the input data has an even
number of 1s.

## Naive Bit Counting

Parity can be calculated by counting 1s in some input data set.  That can be
accomplished with a naive algorithm that iteratively adds the least significant
bit of the input to a counter and shifts the input data to the right by one.

### Example

Naive definition of even parity:

```cpp
uint even_parity(const uint& data, const uint& width) {
  uint counter = 0;
  for (uint i = 0; i < width; ++i) {
    counter += data & 1;
    data >>= 1;
  }
  return counter & 1;
}
```

Odd parity is the inverse of even parity, so inverting the counter before
masking it yields the odd_parity.  Because only the last bit of the counter
is relevant, and it is alternating between 0 and 1 each time the counter is
incremented, another strategy is to simply start the counter at 1.  Another way
to think about this is that 0 is even, and at the start of the algorithm, there
are a total of 0 1s.

```cpp
uint odd_parity(const uint& data, const uint& width) {
  uint counter = 1;
  for (uint i = 0; i < width; ++i) {
    counter += data & 1;
    data >>= 1;
  }
  return counter & 1;
}
```

## Cascading XOR

The naive algorithm above has linear complexity in the number of bits of data.
That's not too bad, but it's a very repetitive algorithm, and there is a way to
calculate multiple intermediate results at once.  Deconstructing the parity
algorithm, there are a couple important things to notice.

First, the LSB toggles each time a 1 comes by, which is the effect that taking
the XOR of the current count's LSB with the current data bit would have

Second, the operation being repeated is a shift right of 1 followed by an XOR
of the new LSB with the current accumulated value.

As a simple example, even parity over 4 bits of data based on these two
properties can be written as `((data[0] XOR data[1]) XOR data[2]) XOR data[3]`.
The XOR operation is associative, so this can be rewritten as
`(data[0] XOR data[1]) XOR (data[2] XOR data[3])`, which is the XOR of the
result of XORing adjacent bits.  Shifting the input data right by one not only
aligns the two LSBs, it also aligns all adjacent bits.  Taking the XOR of data
with itself shifted right by one calculates the parity for all pairs of bits
into the even bits of the result.  This can be continued, XORing that result
with itself shifted to the right by two will calculate the parity for all sets
of four adjacent bits into every fourth bit.  The same is done by iteratively
doubling the shift of the intermediate result, until all the data is processed,
leaving the parity in the LSB of the result.  The complexity of this algorithm
is log<sub>2</sub> in the number of bits of data.

### Example

```cpp
uint even_parity(const uint& data, const uint& width) {
  uint result = data;
  for (uint i = 1; i < width; i <<= 1) {
    result = result ^ (result >> i);
  }
  return result & 1;
}
```

Note that neither example above masks the input data to the width, so the data
they're operating on is not guaranteed to only have data in the declared range.
The naive algorithm will produce the correct result, because it consumes one
bit at a time until it has processed exactly the number of bits required.  The
Cascading XOR function accumulated intermediate results from 2<sup>N</sup> bits
to the left.  That means that parity calculated on data with a width that is
not a power of two, will get polluted by the unused high-order bits.  Input
needs to be masked before being passed in, or a mask needs to be calculated at
the beginning of the function and applied to the input data.

## Compile-time Cascading XOR

This library uses recursive templates, inline and constexpr functions to
generate parity functions with the loop unrolled, and constant data masks to
apply to input data before processing.  Any parity calculation with data
width known at compile time can be described in this way.  There are some other
benefits to using the `Parity` struct, which can be found on the
[Why This Library?](why.md) page.
