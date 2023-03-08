```
// Comparison with std::sort on a vector of 50 million elements:
// Compiled with clang++ with -O3 optimization.
 
Number of elements: 50000000
Type: vector<int8_t>
Contains uniformly distributed values from -128 to 127
Radix sort | Time 0.024303 sec, random element: -107
std::sort  | Time 1.48048 sec, random element: 112
Radix sort is 60.9174 times faster

Type: vector<uint8_t>
Contains uniformly distributed values from 0 to 255
Radix sort | Time 0.023843 sec, random element: 162
std::sort  | Time 1.55529 sec, random element: 74
Radix sort is 65.2304 times faster

Type: vector<int16_t>
Contains uniformly distributed values from -32768 to 32767
Radix sort | Time 0.146134 sec, random element: -22614
std::sort  | Time 2.3654 sec, random element: -1006
Radix sort is 16.1865 times faster

Type: vector<uint16_t>
Contains uniformly distributed values from 0 to 65535
Radix sort | Time 0.143468 sec, random element: 26065
std::sort  | Time 2.45362 sec, random element: 65223
Radix sort is 17.1022 times faster

Type: vector<int32_t>
Contains uniformly distributed values from -2.14748e+09 to 2.14748e+09
Radix sort | Time 0.377694 sec, random element: 1.84842e+09
std::sort  | Time 3.36697 sec, random element: 1.25739e+09
Radix sort is 8.91454 times faster

Type: vector<uint32_t>
Contains uniformly distributed values from 0 to 4.29497e+09
Radix sort | Time 0.334497 sec, random element: 2.16477e+09
std::sort  | Time 3.36967 sec, random element: 4.2159e+07
Radix sort is 10.0738 times faster

Type: vector<int64_t>
Contains uniformly distributed values from -9.22337e+18 to 9.22337e+18
Radix sort | Time 0.951934 sec, random element: 3.08934e+18
std::sort  | Time 3.54066 sec, random element: -8.29357e+18
Radix sort is 3.71944 times faster

Type: vector<uint64_t>
Contains uniformly distributed values from 0 to 1.84467e+19
Radix sort | Time 0.951467 sec, random element: 1.65651e+19
std::sort  | Time 3.43275 sec, random element: 6.45928e+18
Radix sort is 3.60785 times faster

Type: vector<float>
Contains uniformly distributed values from 1.17549e-38 to 3.40282e+38
Radix sort | Time 0.373689 sec, random element: 1.03343e+38
std::sort  | Time 3.72942 sec, random element: 2.74856e+38
Radix sort is 9.98 times faster
```
### Algorithm
Radix sort is a linear time, linear space sorting algorithm.
Unlike most other sorting algorithms, it doesn't use comparisons.
It works with data on the level of individual bytes.
To perform the sort, Radix sort first generates byte frequency tables based on the input data. It then uses these tables to construct offset tables for reordering the elements. Finally, it executes a pass over the data that involves copying and reordering the elements. Typically, one pass is made for each byte of the element type.


The library implements radix sort for most built in
arithmetic types. This implementation sorts, in ascending order,
a contiguous array of elements of the following types:
- 8/16/32/64 bit signed/unsigned integers
- 32 bit floating point numbers.  

For 8 bit types, complexity is O(n) time, O(1) space
For all other types, complexity is O(n) time, O(n) space.

### API:

radix_sort(P, N, M) or radix_sort(P, N), where
P is a raw pointer to data, N is a number of elements,
M is an optional pointer to memory buffer.
The last argument(M) lets you provide memory buffer externally.
There is no requirement for initialization of this memory buffer.
This buffer should have at least the same size as data being sorted
and will be used for copying data during reordering passes.
If you don't provide the buffer(using the radix_sort(P, N) calling interface), 
radix_sort allocates the buffer on its own and frees it afterwards. 
Specializations of radix_sort for 8 bit types don't allocate 
additional memory and don't take buffer as the last argument.
