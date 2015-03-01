# Bitwise Trie

### Basic Description

What I am implementing here is basically an [X-fast trie](https://en.wikipedia.org/wiki/X-fast_trie) without the prefix mechanism. I use `std::bitset<A>` to map the data to its appropriate leaf node on the tree.

#### Detailed description for storing any data in `std::bitset<A>`

`std::bitset<A>` is a container of bits. What I did to store arbitrary data into such a container is as follows,
1. Allocate a char pointer, pointing to an array of chars that is as big as the data
 * If A is the type of the data, then `char* ptr = new char[sizeof(A)]`
 * Note that `sizeof(A)` returns the size in bytes
 * I used `unsigned char` since it seemed more appropriate

2. Copy the data over from the data to the pointer
 * This line for me looks like this, `memcpy((void *) ptr, (const void *const) &a, sz)`
 * `ptr` is the char pointer buffer
 * `a` is the data
 * `sz` is the size of a in bytes

3. Iterate through the data, setting the corresponding bit in the `std::bitset<A>` container
 * Mine is,
```c++
for (size_t i = 0; i < sz; ++i) {
    static byte ch;
    ch = ptr[i];
    for (size_t j = 0; j < 8; ++j) {
        static bool bitVal;
        bitVal = binary<A>::getBitFromByte(ch, j);
        this->bits[binary<A>::getBitIdx(i, j)] = bitVal;
    }
}
```

#### Summary
A quick rundown on how this is done.

 * Render data into raw bytes
 * Write that to a bitset container
 * Use the bit pattern to traverse to a leaf node

##### To Use
 Simply include header and unpack the namespace
```c++
#include "bitwisetrie.hxx"

using namespace despairagus;
using namespace bitwisetrieNS;
```

#### Disclaimer
 This is more of a learning experience than an attempt to construct something useful. The code will be C++11 \(and if I can get it working, C++14\). Expect to be bewildered. I may also try to hook up google test for some good ol' unit testing if I can ever figure out how to use it in a cygwin environment. Or Linux.

A list of things I still need to do

 - [x] TODO - implement binary container
 - [x] TODO - implement bitwise node
 - [x] TODO - implement bitwise trie
 - [] TODO - make separate implementation that is memory-conservative
 - [] TODO - implement store hash (bool)
 - [] TODO - implement option to output trie in dot format

### Some neat links

 * [X-fast trie](https://en.wikipedia.org/wiki/X-fast_trie)
 * [Y-fast trie](https://en.wikipedia.org/wiki/Y-fast_trie)
 * [Some neat tut I found](http://www.mathcs.emory.edu/~cheung/Courses/323/Syllabus/Text/trie01.html)
