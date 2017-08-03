# Byte-Shuffled-Array
This project offers c++ arrays of primitive type that are shuffled to  help complicate memory
analysis by attackers.
Note that the shuffling is fairly simple, for the sake of performance, and the key for retrieving
the data is 32-bits. I didn't write this to be **the** memory encryption solution. It's mostly an
experiment. You can provide your own random number generation (via a derived class of Random::RandomK
that overrides GetKRandomInt()) and override the memory shuffling if you want.

Note that the provided classes, ShuffledArray and ByteShuffledArray, do not store any internal 
state about how they were shuffled. This means that someone analyzing the array stored in the 
class can't see any explicit information on the shuffling. However, there is a higher performance
cost for using the class this way.

**Warning**: Do not use these classes to store arrays of objects. There is a strong chance of a
buffer overflow exception. I've been having trouble compensation for the alignment and padding
of objects.

## ShuffledArray
This class provides very simple shuffling. It just moves the data items around. When a value 
is retrieved or set the entire array is not unshuffled. Instead, the getters and setters use
the key to work out where the item was moved and get it from there.

Character arrays are given a different treatment to other types. With a character array
a new array that is four times as large as the original char array is generated. 
For every character in the array three copies of it are added. The resulting array is shuffled.
The special shuffling for character arrays is intended to provide basic interference with
pattern analysis.

## ByteShuffledArray
This class shuffles arrays at the byte level. The array that is passed in is treated as a 
char array with sizeof(type stored in array) * numElements. When a item is retrieved the
class works out which bytes contained the original item and finds where those bytes
were moved to. The data stored in those bytes is retrieved and combined to recreate the 
original item **without unshuffling the array**. Each byte is also XORed with the key.

Internally the ByteShuffledArray uses a ShuffledArray of type char to shuffle the bytes and retrieve
them.

## Performance
Both classes generate K*2 random values for the shuffling. In the case of the ShuffledArray K = num items * 2
whiile for the ByteShuffledArray K = num items * numBytes * 2 in each item.  For the ByteShuffledArray there
is a step where each byte is XORed with the key so that will take another K steps. For both classes the shuffling
and unshuffling involves K swaps. Thus shuffling is O(K) for both classes but in practice the ByteShuffledArray
will be far slower.

Shuffling and unshuffling involve swapping the data in the item slots using temporary variables. Thus the getters
do not actually unshuffle the arrays and instead calculate where the data went. The K random numbers need
to be generated and for every item N the K random numbers must be iterated through to get the data back.
In the case of the ShuffledArray K = 1 because we have one item. In the case of the ByteShuffledArray N = sizeof(T)
in bytes. Thus the getter complexity is O(N*K). N is a constant specific to the type stored in the array. In practice
shuffling and unshuffling the entire array will be slower than retrieving data. Setting data in the ByteShuffledArray
will be as slow as shuffling and unshuffling because the data is unshuffled to ensure the correct bytes are written to.

With getters, no data is actually swapped. Instead the items/bytes are llocated and derefenced to copy what is stored
there.

## Usage

### Demo
The default makefile rule compiles a executable DriverWin.exe using the CL.exe compiler. If you want to do a g++ build 
invoke the makefile rule "DriverGCC.exe". DriverGCC.exe is the g++ build. If you run either program a demo will run
where a int array and a char array is generated and then printed out to confirm the shuffling and unshuffling is working
correctly.

### Your Own Implementation
If deriving from the RandomK class you must ensure that GetKRandomInt(int key, int K) must always return the same sequence of 
random integers given a seed "key". If you call the function with K = 3 the 3 integers you get back must match the first 3 integers you'd get when calling the funciton with K = 5. Thus K cannot be used to calculate the random values.

