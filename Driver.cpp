#include "ShuffledArray.h"


int main(){
	int testArr[10] = {1,2,3,4,5,6,7,8,9,10};
	int key = Random::GetRandomInt();
	ShuffledArray<int> testShuffledArray(testArr,10,key);
	
	for (int i = 0; i<10; ++i){
		std::cout << testShuffledArray.get(i,key) << std::endl;
	}
}