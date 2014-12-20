# Bitwise Trie

### Basic Description

What I am implementing here is basically an [X-fast trie](https://en.wikipedia.org/wiki/X-fast_trie) without the prefix mechanism. I use `std::bitset<A>` to map the data to its appropriate leaf node on the tree.

A quick rundown on how this is done.

 * Render data into raw bytes
 * Write that to a bitset container
 * Use the bit pattern to traverse to a leaf node

 ######To Use
 Simply include header `#include "bitwisetrie.hxx"`


 #### Disclaimer
 This is more of a learning experience than an attempt to construct something useful. The code will be C++11 \(and if I can get it working, C++14\). Expected to be bewildered. I may also try to hook up google test for some good ol' unit testing if I can ever figure out how to use it in a cygwin environment.

A list of things I still need to do

 - [x] TODO - implement binary container
 - [x] TODO - implement bitwise node
 - [] TODO - implement bitwise trie
 - [] TODO - make separate implementation that is memory-conservative
 - [] TODO - implement store hash (bool)
 - [] TODO - implement option to output trie in dot format


And here's some code!

```c++
bitwiseTrie<int> bwt;
bwt.insert(5);
```


### Some neat links

 * [X-fast trie](https://en.wikipedia.org/wiki/X-fast_trie)
 * [Y-fast trie](https://en.wikipedia.org/wiki/Y-fast_trie)
 * [Some neat tut I found](http://www.mathcs.emory.edu/~cheung/Courses/323/Syllabus/Text/trie01.html)
