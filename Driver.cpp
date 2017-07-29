#include "ShuffledArray.h"
#include "ByteShuffledArray.h"


int main(){
	int testArr[10] = {1,2,3,4,5,6,7,8,9,10};
	int key = Random::GetRandomInt();
	ShuffledArray<int> testShuffledArray(testArr,10,key);
	
	std::cout << "==================---------------==================" << std::endl;
	std::cout << "=============  Item Level Shuffling  ==============" << std::endl;
	std::cout << "==================---------------==================" << std::endl;
	
	for (int i = 0; i<10; ++i){
		std::cout << testShuffledArray.get(i,key) << std::endl;
	}
	
	std::cout << "==================---------------==================" << std::endl;
	std::cout << "=============  Byte Level Shuffling  ==============" << std::endl;
	std::cout << "==================---------------==================" << std::endl;
	
	int testArr2[10] = {1,2,3,4,5,6,7,8,9,10};
	ByteShuffledArray<int> testByteShuffledArray(testArr2,10,key);
	
	for (int i = 0; i<10; ++i){
		std::cout << testByteShuffledArray.get(i,key) << std::endl;
	}
}