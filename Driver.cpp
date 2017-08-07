#include "ShuffledArray.h"
#include "ByteShuffledArray.h"
//#include <string>
#include "TestingMacros.h"
#include "MyClass.h"

int main(){
	//debugPrint = true;
	
	int testArr[10] = {1,2,3,4,5,6,7,8,9,10};
	char testStr11[660] = "Here is the application with my signature. I simply need to type my name in the signature section. \nFor the main project, as opposed to the paper prototyping, you will need to make the request for access to participants. \nThis is done after you get ethics clearance. I will send you the form and process for this in due course.  \nYou can, however, proceed with the paper prototyping. Also, for you main ethics clearance application I think you need \nto provide more detail about the project itself. You can include detail from your proposal. \nYou should also measure other confounding factors, such as age, subject of study, general computer proficiency, etc.";;
	char testStr12[660] = "Here is the application with my signature. I simply need to type my name in the signature section. \nFor the main project, as opposed to the paper prototyping, you will need to make the request for access to participants. \nThis is done after you get ethics clearance. I will send you the form and process for this in due course.  \nYou can, however, proceed with the paper prototyping. Also, for you main ethics clearance application I think you need \nto provide more detail about the project itself. You can include detail from your proposal. \nYou should also measure other confounding factors, such as age, subject of study, general computer proficiency, etc.";;
	char testStr13[660] = "Here is the application with my signature. I simply need to type my name in the signature section. \nFor the main project, as opposed to the paper prototyping, you will need to make the request for access to participants. \nThis is done after you get ethics clearance. I will send you the form and process for this in due course.  \nYou can, however, proceed with the paper prototyping. Also, for you main ethics clearance application I think you need \nto provide more detail about the project itself. You can include detail from your proposal. \nYou should also measure other confounding factors, such as age, subject of study, general computer proficiency, etc.";;
	char testStr14[660] = "Here is the application with my signature. I simply need to type my name in the signature section. \nFor the main project, as opposed to the paper prototyping, you will need to make the request for access to participants. \nThis is done after you get ethics clearance. I will send you the form and process for this in due course.  \nYou can, however, proceed with the paper prototyping. Also, for you main ethics clearance application I think you need \nto provide more detail about the project itself. You can include detail from your proposal. \nYou should also measure other confounding factors, such as age, subject of study, general computer proficiency, etc.";
	MyClass myClasses1[3] = {MyClass('a', 213, 'c', 'd', 1.5f),MyClass('t', 432, 'z', 'm', 0.5f),MyClass('e', 45474574, 'k', 'f', 35345.354534f)};
	
	int key = Random::GetRandomInt();
	Random::RandomK<int> random;
	ShuffledArray<int,int> testShuffledArray(testArr,10,key,random);
	ShuffledArray<MyClass,int> testShuffledArray6(myClasses1,3,key,random);
	ShuffledCharArray<int> testShuffledArray2(testStr11,660,key,random,4);
	ShuffledCharArray<int> testShuffledArray3(testStr12,660,key,random,1);
	ShuffledCharArray<int> testShuffledArray4(testStr13,660,key,random,6);
	ShuffledCharArray<int> testShuffledArray5(testStr14,660,key,random,0);
	
	std::cout << "==================---------------==================" << std::endl;
	std::cout << "=============  Item Level Shuffling  ==============" << std::endl;
	std::cout << "==================---------------==================" << std::endl;
	std::cout << "=============  Int  ==============" << std::endl;
	for (int i = 0; i<10; ++i){
		std::cout << testShuffledArray.get(i,key) << std::endl;
	}
	std::cout << "=============  String  r = 4 ==============" << std::endl;
	for (int i = 0; i<660; ++i){
		std::cout << testShuffledArray2.get(i,key);
	}
	std::cout << "=============  String r = 1  ==============" << std::endl;
	std::cout << std::endl;
	for (int i = 0; i<660; ++i){
		std::cout << testShuffledArray3.get(i,key);
	}
	std::cout << "=============  String r = 6  ==============" << std::endl;
	std::cout << std::endl;
	for (int i = 0; i<660; ++i){
		std::cout << testShuffledArray4.get(i,key);
	}
	std::cout << std::endl;
	std::cout << "=============  String r = 0  ==============" << std::endl;
	std::cout << std::endl;
	for (int i = 0; i<660; ++i){
		std::cout << testShuffledArray5.get(i,key);
	}
	std::cout << std::endl;
	
	std::cout << "=============  MyClass  ==============" << std::endl;
	for (int i = 0; i<3; ++i){
		std::cout << testShuffledArray6.get(i,key) << std::endl;
	}
	
	std::cout << "==================---------------==================" << std::endl;
	std::cout << "=============  Byte Level Shuffling  ==============" << std::endl;
	std::cout << "==================---------------==================" << std::endl;
	std::cout << "=============  Int  ==============" << std::endl;
	int testArr2[10] = {1,2,3,4,5,6,7,8,9,10};
	char testStr21[660] = "Here is the application with my signature. I simply need to type my name in the signature section. \nFor the main project, as opposed to the paper prototyping, you will need to make the request for access to participants. \nThis is done after you get ethics clearance. I will send you the form and process for this in due course.  \nYou can, however, proceed with the paper prototyping. Also, for you main ethics clearance application I think you need \nto provide more detail about the project itself. You can include detail from your proposal. \nYou should also measure other confounding factors, such as age, subject of study, general computer proficiency, etc.";
	char testStr22[660] = "Here is the application with my signature. I simply need to type my name in the signature section. \nFor the main project, as opposed to the paper prototyping, you will need to make the request for access to participants. \nThis is done after you get ethics clearance. I will send you the form and process for this in due course.  \nYou can, however, proceed with the paper prototyping. Also, for you main ethics clearance application I think you need \nto provide more detail about the project itself. You can include detail from your proposal. \nYou should also measure other confounding factors, such as age, subject of study, general computer proficiency, etc.";
	char testStr23[660] = "Here is the application with my signature. I simply need to type my name in the signature section. \nFor the main project, as opposed to the paper prototyping, you will need to make the request for access to participants. \nThis is done after you get ethics clearance. I will send you the form and process for this in due course.  \nYou can, however, proceed with the paper prototyping. Also, for you main ethics clearance application I think you need \nto provide more detail about the project itself. You can include detail from your proposal. \nYou should also measure other confounding factors, such as age, subject of study, general computer proficiency, etc.";
	char testStr24[660] = "Here is the application with my signature. I simply need to type my name in the signature section. \nFor the main project, as opposed to the paper prototyping, you will need to make the request for access to participants. \nThis is done after you get ethics clearance. I will send you the form and process for this in due course.  \nYou can, however, proceed with the paper prototyping. Also, for you main ethics clearance application I think you need \nto provide more detail about the project itself. You can include detail from your proposal. \nYou should also measure other confounding factors, such as age, subject of study, general computer proficiency, etc.";
	MyClass myClasses2[3] = {MyClass('a', 213, 'c', 'd', 1.5f),MyClass('t', 432, 'z', 'm', 0.5f),MyClass('e', 45474574, 'k', 'f', 35345.354534f)};
	
	ByteShuffledArray<int,int> testByteShuffledArray(testArr2,10,key,random);
	ByteShuffledArray<MyClass,int> testByteShuffledArray6(myClasses2,3,key,random);
	ByteShuffledArray<char,int> testByteShuffledArray2(testStr21,660,key,random,4);
	ByteShuffledArray<char,int> testByteShuffledArray3(testStr22,660,key,random,1);
	ByteShuffledArray<char,int> testByteShuffledArray4(testStr23,660,key,random,6);
	ByteShuffledArray<char,int> testByteShuffledArray5(testStr24,660,key,random,0);
	int * rangeArray = testByteShuffledArray.getRange(0,10,key);
	for (int i = 0; i<10; ++i){
		std::cout << testByteShuffledArray.get(i,key) << " ";
	}
	std::cout << std::endl;
	
	for (int i = 0; i<10; ++i){
		std::cout << rangeArray[i] << " ";
	}
	
	std::cout << std::endl;
	
	std::cout << "=============  String r = 4  ==============" << std::endl;
	
	for (int i = 0; i<660; ++i){
		std::cout << testByteShuffledArray2.get(i,key);
	}
	std::cout << std::endl;
	std::cout << "=============  String r = 1  ==============" << std::endl;
	for (int i = 0; i<660; ++i){
		std::cout << testByteShuffledArray3.get(i,key);
	}
	std::cout << std::endl;
	std::cout << "=============  String r = 6  ==============" << std::endl;
	for (int i = 0; i<660; ++i){
		std::cout << testByteShuffledArray4.get(i,key);
	}
	std::cout << std::endl;
	std::cout << "=============  String r = 0  ==============" << std::endl;
	for (int i = 0; i<660; ++i){
		std::cout << testByteShuffledArray5.get(i,key);
	}
	std::cout << std::endl;
	
	std::cout << "=============  MyClass  ==============" << std::endl;
	for (int i = 0; i<3; ++i){
		std::cout << testByteShuffledArray6.get(i,key) << std::endl;
	}
}