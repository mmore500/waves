---
layout: post
title: "std::bitset plus -msse4.2 equals popcnt"
date: 2019-11-20
author: Matthew Andres Moreno # optional, or Anonymous
---

My research group, the [Digital Evolution Lab](https://devosoft.org) at [Michigan State University](https://msu.edu), uses computer programs as a model organism to study evolution (and, also, evolution as tool to create computer programs).
In recent work with the event-driven [SignalGP representation](https://dl.acm.org/citation.cfm?doid=3205455.3205523), we need to wire together an evolving computer program's sub-modules in order to run it.
We figure out what wires together by matching bitstring tags.
Because we calculate the matches between *a lot* of bitstring tags in our experiments, it's important for this operation to be as efficient as possible.

![Gotta go fast!]({{ site.baseurl }}/assets/mmore500/giphy-sonic.gif)

In practice, calculating tag matches involves performing some operation on the two tags (e.g., bitwise xor) and then counting the number of 1's in the resulting bitstring.
Under the hood, we use `uint64_t`'s and `uint_32_t`'s to represent components of our bitstrings.
So, we want to be able to the count 1's in those types quickly.

Luckily, [x86 CPUs](https://en.wikipedia.org/wiki/X86) provide a [`popcnt` machine-level instruction](https://www.felixcloutier.com/x86/popcnt) as part of the [SSE 4.2](https://en.wikipedia.org/wiki/SSE4) instruction set, which does all the work to the count 1's in a register in just one clock cycle.
However, directly writing `popcnt` into our source code was pretty crufty.
Here's an idea of what *that* looks like.

This snippet was pulled from an older version of our lab's [Empirical C++ library](https://github.com/devosoft/Empirical).

```cpp
#include <nmmintrin.h>

...

#ifdef __SSE4_2__
          bit_count += _mm_popcnt_u64(bit_set[i]); // needs CPU with SSE4.2
#else
          // adapted from https://en.wikipedia.org/wiki/Hamming_weight
          uint64_t x = bit_set[i];
          // put count of each 2 bits into those 2 bits
          x -= (x >> 1) & 0x5555555555555555;
          // put count of each 4 bits into those 4 bits
          x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
          //put count of each 8 bits into those 8 bits
          x = (x + (x >> 4)) & 0x0f0f0f0f0f0f0f0f;
          // returns left 8 bits of x + (x<<8) + (x<<16) + (x<<24) + ...
          bit_count += (x * 0x0101010101010101) >> 56;
#endif
```

Up top, we include `<nmmintrin.h>`.
This header isn't part of the C++ standard, so we're potentially setting ourselves up for a big headache if we try to compile on a system where the header isn't available.

Then, we have to use a preprocessor directive (a.k.a. a macro) to separately handle cases where SSE 4.2 instructions are *and* are not available.
This means we have to maintain twice the code!
This is especially annoying because the non-SSE 4.2 code involves some hardcore inscrutable bitmagic.

To boot, macros are increasingly considered harmful [a la `goto`](https://en.wikipedia.org/wiki/Considered_harmful) ([or at least yucky](https://stackoverflow.com/a/14041847)) in modern C++ so we'd rather do without them anyways.

What to do?

## 🐤 Peep the Intermediate Representation

The C++ standard library provides a class called [`std::bitset`](https://en.cppreference.com/w/cpp/utility/bitset) that represents a bit sequence and provides a `count` member function that reports the number of 1's the sequence contains... exactly what we want!
It would be really slick to be able to shove the bits we want to count into a `std::bitset` and then call `count`, but will it go fast?
Will we have to pay overhead to construct a `std::bitset` from a `uint32_t` or a `uint64_t`?
Will `std::bitset`'s `count` method use a `popcnt` machine instruction or rely on a slower method?

Let's find out!

Here's a Compiler Explorer example that shows what wrapping a `uint` in `std::bitset` and then calling `count` compiles down to with Clang.
Note, in particular, the intermediate representation code on the right that corresponds to `countbits32` and `countbits64`.

<iframe width="100%" height="600px" src="https://godbolt.org/e?readOnly=true#g:!((g:!((g:!((h:codeEditor,i:(fontScale:14,j:1,lang:c%2B%2B,source:'%23include+%3Cbitset%3E%0A%23include+%3Ciostream%3E%0A%0Asize_t+countbits64(uint64_t+val)+%7B%0A++++std::bitset%3C64%3E+bs(val)%3B%0A++++return+bs.count()%3B%0A%7D%0A%0Asize_t+countbits32(uint32_t+val)+%7B%0A++++std::bitset%3C32%3E+bs(val)%3B%0A++++return+bs.count()%3B%0A%7D%0A%0Aint+main()+%7B%0A++++std::cout%0A++++++++%3C%3C+%22countbits32(42):+%22%0A++++++++%3C%3C+countbits32(42)%0A++++++++%3C%3C+std::endl%3B%0A++++std::cout%0A++++++++%3C%3C+%22countbits64(42):+%22%0A++++++++%3C%3C+countbits64(42)%0A++++++++%3C%3C+std::endl%3B%0A++++return+0%3B%0A%7D'),l:'5',n:'0',o:'C%2B%2B+source+%231',t:'0')),k:50,l:'4',n:'0',o:'',s:0,t:'0'),(g:!((h:compiler,i:(compiler:clang900,filters:(b:'0',binary:'1',commentOnly:'0',demangle:'0',directives:'0',execute:'1',intel:'0',libraryCode:'1',trim:'1'),fontScale:14,lang:c%2B%2B,libs:!(),options:'-O3+-msse4.2',source:1),l:'5',n:'0',o:'x86-64+clang+9.0.0+(Editor+%231,+Compiler+%231)+C%2B%2B',t:'0')),k:50,l:'4',n:'0',o:'',s:0,t:'0')),l:'2',n:'0',o:'',t:'0')),version:4"></iframe>

There's no overhead with a `uint64_t` (just a plain ol' `popcnt` and then a `return`).
For `uint32_t` we have to execute a single `mov` instruction in addition to the `popcnt`, which isn't too bad at all.
Success!

Here's the same example, but compiled with GCC.
We get similar results.

<iframe width="100%" height="600px" src="https://godbolt.org/e?readOnly=true#g:!((g:!((g:!((h:codeEditor,i:(fontScale:14,j:1,lang:c%2B%2B,source:'%23include+%3Cbitset%3E%0A%23include+%3Ciostream%3E%0A%0Asize_t+countbits64(uint64_t+val)+%7B%0A++++std::bitset%3C64%3E+bs(val)%3B%0A++++return+bs.count()%3B%0A%7D%0A%0Asize_t+countbits32(uint32_t+val)+%7B%0A++++std::bitset%3C32%3E+bs(val)%3B%0A++++return+bs.count()%3B%0A%7D%0A%0Aint+main()+%7B%0A++++std::cout%0A++++++++%3C%3C+%22countbits32(42):+%22%0A++++++++%3C%3C+countbits32(42)%0A++++++++%3C%3C+std::endl%3B%0A++++std::cout%0A++++++++%3C%3C+%22countbits64(42):+%22%0A++++++++%3C%3C+countbits64(42)%0A++++++++%3C%3C+std::endl%3B%0A++++return+0%3B%0A%7D'),l:'5',n:'0',o:'C%2B%2B+source+%231',t:'0')),k:50,l:'4',n:'0',o:'',s:0,t:'0'),(g:!((h:compiler,i:(compiler:g92,filters:(b:'0',binary:'1',commentOnly:'0',demangle:'0',directives:'0',execute:'1',intel:'0',libraryCode:'1',trim:'1'),fontScale:14,lang:c%2B%2B,libs:!(),options:'-O3+-msse4.2',source:1),l:'5',n:'0',o:'x86-64+gcc+9.2+(Editor+%231,+Compiler+%231)+C%2B%2B',t:'0')),k:50,l:'4',n:'0',o:'',s:0,t:'0')),l:'2',n:'0',o:'',t:'0')),version:4"></iframe>

The key, it turns out, to getting `popcnt` from `std::bitset::count` is compiling with the `-mmsse4.2` flag.
Try taking it out of the examples above.
You should be able to see the intermediate representation that the source compiles to balloon up.

Although this code won't be as fast if SSE 4.2 instructions aren't available, we can depend on the standard library implementors to provide a *correct* (as well as reasonably performant) implementation of `std::bitset::count` so our code at least doesn't break.
We wouldn't have been able to use `popcnt` anyways if SSE 4.2 instructions weren't available, so we're not losing much, if anything, in this case.

## ✨ Source Code Transformation ✨

The counterpart to the big, ugly code snippet above *after* we started using `std::bitset` really shows off how much of our source's complexity we were able to hand off to the standard library implementors.

This snippet was pulled from an newer version of our lab's [Empirical C++ library](https://github.com/devosoft/Empirical).

```cpp
    // when compiling with -O3 and -msse4.2,
    // this compiles to a hardware POPCNT instruction
    std::bitset<FIELD_BITS> std_bs(bit_set[i]);
    bit_count += std_bs.count();
```

All without sacrificing performance... nice!

## Shout Out

... to Santiago Rodriguez-Papa [@rodsan0](https://github.com/rodsan0), who suggested the `-msse4.2` compiler flag and has been hard at work maintaining Empirical's `BitSet` and `BitVector`.
Thank you!

## Let's Chat

Comments? Questions?

I started a twitter thread (right below) so we can chat!! ☎️ ☎️ ☎️

<blockquote class="twitter-tweet"><p lang="en" dir="ltr">nothing to see here, just a placeholder tweet 🐦</p>&mdash; Matthew A Moreno (@MorenoMatthewA) <a href="https://twitter.com/MorenoMatthewA/status/1054071480512843776?ref_src=twsrc%5Etfw">October 21, 2018</a></blockquote> <script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>
