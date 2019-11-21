---
layout: post
title: "std::bitset plus -msse4.2 equals popcnt"
date: 2019-11-20
author: Matthew Andres Moreno # optional, or Anonymous
---

This snippet was pulled from an newer version of our lab's [Empirical C++ library](https://github.com/devosoft/Empirical).

```cpp
    // when compiling with -O3 and -msse4.2,
    // this compiles to a hardware POPCNT instruction
    std::bitset<FIELD_BITS> std_bs(bit_set[i]);
    bit_count += std_bs.count();
```


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

<iframe width="100%" height="600px" src="https://godbolt.org/e?readOnly=true#g:!((g:!((g:!((h:codeEditor,i:(fontScale:14,j:1,lang:c%2B%2B,source:'%23include+%3Cbitset%3E%0A%23include+%3Ciostream%3E%0A%0Asize_t+countbits64(uint64_t+val)+%7B%0A++++std::bitset%3C64%3E+bs(val)%3B%0A++++return+bs.count()%3B%0A%7D%0A%0Asize_t+countbits32(uint32_t+val)+%7B%0A++++std::bitset%3C32%3E+bs(val)%3B%0A++++return+bs.count()%3B%0A%7D%0A%0Aint+main()+%7B%0A++++std::cout%0A++++++++%3C%3C+%22countbits32(42):+%22%0A++++++++%3C%3C+countbits32(42)%0A++++++++%3C%3C+std::endl%3B%0A++++std::cout%0A++++++++%3C%3C+%22countbits64(42):+%22%0A++++++++%3C%3C+countbits64(42)%0A++++++++%3C%3C+std::endl%3B%0A++++return+0%3B%0A%7D'),l:'5',n:'0',o:'C%2B%2B+source+%231',t:'0')),k:50,l:'4',n:'0',o:'',s:0,t:'0'),(g:!((h:compiler,i:(compiler:clang900,filters:(b:'0',binary:'1',commentOnly:'0',demangle:'0',directives:'0',execute:'1',intel:'0',libraryCode:'1',trim:'1'),fontScale:14,lang:c%2B%2B,libs:!(),options:'-O3+-msse4.2',source:1),l:'5',n:'0',o:'x86-64+clang+9.0.0+(Editor+%231,+Compiler+%231)+C%2B%2B',t:'0')),k:50,l:'4',n:'0',o:'',s:0,t:'0')),l:'2',n:'0',o:'',t:'0')),version:4"></iframe>

<iframe width="100%" height="600px" src="https://godbolt.org/e?readOnly=true#g:!((g:!((g:!((h:codeEditor,i:(fontScale:14,j:1,lang:c%2B%2B,source:'%23include+%3Cbitset%3E%0A%23include+%3Ciostream%3E%0A%0Asize_t+countbits64(uint64_t+val)+%7B%0A++++std::bitset%3C64%3E+bs(val)%3B%0A++++return+bs.count()%3B%0A%7D%0A%0Asize_t+countbits32(uint32_t+val)+%7B%0A++++std::bitset%3C32%3E+bs(val)%3B%0A++++return+bs.count()%3B%0A%7D%0A%0Aint+main()+%7B%0A++++std::cout%0A++++++++%3C%3C+%22countbits32(42):+%22%0A++++++++%3C%3C+countbits32(42)%0A++++++++%3C%3C+std::endl%3B%0A++++std::cout%0A++++++++%3C%3C+%22countbits64(42):+%22%0A++++++++%3C%3C+countbits64(42)%0A++++++++%3C%3C+std::endl%3B%0A++++return+0%3B%0A%7D'),l:'5',n:'0',o:'C%2B%2B+source+%231',t:'0')),k:50,l:'4',n:'0',o:'',s:0,t:'0'),(g:!((h:compiler,i:(compiler:g92,filters:(b:'0',binary:'1',commentOnly:'0',demangle:'0',directives:'0',execute:'1',intel:'0',libraryCode:'1',trim:'1'),fontScale:14,lang:c%2B%2B,libs:!(),options:'-O3+-msse4.2',source:1),l:'5',n:'0',o:'x86-64+gcc+9.2+(Editor+%231,+Compiler+%231)+C%2B%2B',t:'0')),k:50,l:'4',n:'0',o:'',s:0,t:'0')),l:'2',n:'0',o:'',t:'0')),version:4"></iframe>

## References

* https://en.cppreference.com/w/cpp/utility/bitset
* https://www.felixcloutier.com/x86/popcnt
* https://en.wikipedia.org/wiki/SSE4

## Let's Chat

Comments? Questions?

I started a twitter thread (right below) so we can chat!! ☎️ ☎️ ☎️

<blockquote class="twitter-tweet"><p lang="en" dir="ltr">nothing to see here, just a placeholder tweet 🐦</p>&mdash; Matthew A Moreno (@MorenoMatthewA) <a href="https://twitter.com/MorenoMatthewA/status/1054071480512843776?ref_src=twsrc%5Etfw">October 21, 2018</a></blockquote> <script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>
