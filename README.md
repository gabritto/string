# String matching
Implementation of string matching and compression algorithms.

PMT (**P**attern **M**atching **T**ool) is a  tool for exact and approximate pattern matching.
It uses a combination of the following algorithms:  

For exact matching:
- Knuth-Morris-Pratt
- Aho-Corasick
- Boyer-Moore
- Shift-Or 

For approximate matching:
- Wu-Manber (or BitAp)
- Ukkonen [(found here)](https://doi.org/10.1016/0196-6774(85)90023-9)
- Sellers

IPMT (**I**ndexed **P**attern **M**atching **T**ool) is a tool for exact pattern matching.
It constructs the suffix array of an input text and compresses it using the [LZ77](https://en.wikipedia.org/wiki/LZ77_and_LZ78) compression algorithm.
Alternatively, it receives a compressed suffix array of a text and performs exact string matching on such text.


