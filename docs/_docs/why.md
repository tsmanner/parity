---
title: Why This Library?
---
# Why This Library?

Parity is a form of redundancy, used for error detection and correction.  Some
uses of parity are:

- data storage hardware, to detect when the contents have been corrupted
- computing hardware, to detect computation failures
- network packets to detect dropped or corrupted data by the receiver

Manual parity calculations aren't very expressive, and their efficiency is
dependent on the programmer writing them.  They can be made more expressive by
putting them in a function, and their efficiency can always be improved with a
little research and effort.  This library provides an expressive API and
delegates many of the computations to the compiler, including the iteration.
The templated nature of it also makes it easy to calculate multiple parity bits
at once, by splitting the input data into a number of equally sized parity
groups.  An example of this would be calculating byte parity over data returned
by a storage device to compare with the parity bits returned from it.  64-bit
blocks could be checked easily with `Parity<64, 8>::even(uint64_t(data))`.
