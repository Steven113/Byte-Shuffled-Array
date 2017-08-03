#include "ShuffledArray.h"
#include "ByteShuffledArray.h"
//#include <string>

int main(){
	int testArr[10] = {1,2,3,4,5,6,7,8,9,10};
	char testStr[660] = "Here is the application with my signature. I simply need to type my name in the signature section. \nFor the main project, as opposed to the paper prototyping, you will need to make the request for access to participants. \nThis is done after you get ethics clearance. I will send you the form and process for this in due course.  \nYou can, however, proceed with the paper prototyping. Also, for you main ethics clearance application I think you need \nto provide more detail about the project itself. You can include detail from your proposal. \nYou should also measure other confounding factors, such as age, subject of study, general computer proficiency, etc.";;
	int key = Random::GetRandomInt();
	Random::RandomK random;
	ShuffledArray<int> testShuffledArray(testArr,10,key,random);
	ShuffledCharArray testShuffledArray2(testStr,660,key,random);
	
	std::cout << "==================---------------==================" << std::endl;
	std::cout << "=============  Item Level Shuffling  ==============" << std::endl;
	std::cout << "==================---------------==================" << std::endl;
	std::cout << "=============  Int  ==============" << std::endl;
	for (int i = 0; i<10; ++i){
		std::cout << testShuffledArray.get(i,key) << std::endl;
	}
	std::cout << "=============  String  ==============" << std::endl;
	for (int i = 0; i<660; ++i){
		std::cout << testShuffledArray2.get(i,key);
	}
	std::cout << std::endl;
	
	std::cout << "==================---------------==================" << std::endl;
	std::cout << "=============  Byte Level Shuffling  ==============" << std::endl;
	std::cout << "==================---------------==================" << std::endl;
	std::cout << "=============  Int  ==============" << std::endl;
	int testArr2[10] = {1,2,3,4,5,6,7,8,9,10};
	char testStr2[660] = "Here is the application with my signature. I simply need to type my name in the signature section. \nFor the main project, as opposed to the paper prototyping, you will need to make the request for access to participants. \nThis is done after you get ethics clearance. I will send you the form and process for this in due course.  \nYou can, however, proceed with the paper prototyping. Also, for you main ethics clearance application I think you need \nto provide more detail about the project itself. You can include detail from your proposal. \nYou should also measure other confounding factors, such as age, subject of study, general computer proficiency, etc.";
	ByteShuffledArray<int> testByteShuffledArray(testArr2,10,key,random);
	ByteShuffledArray<char> testByteShuffledArray2(testStr2,660,key,random);
	int * rangeArray = testByteShuffledArray.getRange(0,10,key);
	for (int i = 0; i<10; ++i){
		std::cout << testByteShuffledArray.get(i,key) << " ";
	}
	std::cout << std::endl;
	
	for (int i = 0; i<10; ++i){
		std::cout << rangeArray[i] << " ";
	}
	
	std::cout << std::endl;
	
	std::cout << "=============  String  ==============" << std::endl;
	
	for (int i = 0; i<660; ++i){
		std::cout << testByteShuffledArray2.get(i,key);
	}
	std::cout << std::endl;
}