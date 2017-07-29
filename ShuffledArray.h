#ifndef SHUFFLED_ARRAY
#define SHUFFLED_ARRAY
#include "Random.h"
#include <iostream>
#include <string>
#include <assert.h>




/*
	Protects an array of objects of type T in memory
	by keeping it scrambled at the object level in memory when not getting 
	or setting values. A getter or setter can only get
	the correct data by providing the key used to construct this array.
	
	To prevent the key from being cracked you should occasionally regenerate the
	array with a new key. A instance of the class RandomK or a class derived from 
	it is needed to generate the random values generated for this class to used
	when scambling the memory. Note that the key is used as a seed for the generator.
*/

template <typename T>
class ShuffledArray{
	protected:
		T * arr;
		int count;
		
		Random::RandomK random;
		
		ShuffledArray(){}
	public:
		ShuffledArray(T * arr, int count, int key, Random::RandomK random){
			this->arr = arr;
			this->count = count;
			this->random = random;
			
			int numBytesPerObject = sizeof(T);
			
			for (int i = 0; i<count * numBytesPerObject; ++i){
				arr[i];
			}
			
			ShuffleData(key);
		}
				
		virtual T get(int index, int key){
			assert(index >= 0 && index<=count);
			//UnShuffleData(key);
			
			index = GetShiftedIndex(index, key);
			
			T result = arr[index]; 
			//ShuffleData(key);
			
			return result;
		}
				
		virtual void Set(int index, int key, T item){
			assert(index >= 0 && index<=count);
			//UnShuffleData(key);
			
			index = GetShiftedIndex(index, key);
			
			arr[index] = item;
			//ShuffleData(key);
		}

		virtual void ShuffleData(int key){
			std::cout << "Shuffle array" <<std::endl;
			int * shuffleIndexes = random.GetKRandomInt(key, count*2);
			
			std::cout << "Clamping Indexes: ";
			
			for (int i = 0; i<count*2; ++i){
				shuffleIndexes[i]%=count;
				if (shuffleIndexes[i]<0){
					shuffleIndexes[i] += count;
				}
				std::cout << shuffleIndexes[i] << " ";
			}
			
			std::cout << std::endl;
			
			T temp;
			
			for (int i = 0; i<count; ++i){
				//std::cout << shuffleIndexes[i*2] << " shuffleIndexes[i*2]" <<std::endl;
				//std::cout << shuffleIndexes[i*2+1] << " shuffleIndexes[i*2+1]" <<std::endl;
				temp = arr[shuffleIndexes[i*2]];
				arr[shuffleIndexes[i*2]] = arr[shuffleIndexes[i*2 + 1]];
				arr[shuffleIndexes[i*2 + 1]] = temp;
				//std::cout << i << " i" <<std::endl;
			}
			
			std::cout << "Shuffled array: ";
			for (int i = 0; i<count; ++i){
				std::cout << arr[i] << " ";
			}
			std::cout << std::endl;
		}
				
		virtual void UnShuffleData(int key){
			std::cout << "Unshuffle array" <<std::endl;
			int * shuffleIndexes = random.GetKRandomInt(key, count*2);
			
			std::cout << "Clamping Indexes: ";
			
			for (int i = 0; i<count*2; ++i){
				shuffleIndexes[i]%=count;
				if (shuffleIndexes[i]<0){
					shuffleIndexes[i] += count;
				}
				std::cout << shuffleIndexes[i] << " ";
			}
			
			std::cout << std::endl;
			
			T temp;
			
			for (int i = count - 1; i>=0; --i){
				//std::cout << shuffleIndexes[i*2] << " shuffleIndexes[i*2]" <<std::endl;
				//std::cout << shuffleIndexes[i*2+1] << " shuffleIndexes[i*2+1]" <<std::endl;
				temp = arr[shuffleIndexes[i*2]];
				arr[shuffleIndexes[i*2]] = arr[shuffleIndexes[i*2 + 1]];
				arr[shuffleIndexes[i*2 + 1]] = temp;
				//std::cout << i << " i" <<std::endl;
			}
			
			std::cout << "Unshuffled array: ";
			for (int i = 0; i<count; ++i){
				std::cout << arr[i] << " ";
			}
			std::cout << std::endl;
		}
		
		virtual int GetShiftedIndex(int index, int key){
			int * shuffleIndexes = random.GetKRandomInt(key, count*2);
			
			for (int i = 0; i<count*2; ++i){
				shuffleIndexes[i]%=count;
				if (shuffleIndexes[i]<0){
					shuffleIndexes[i] += count;
				}
			}
			
			for (int i = 0; i<count; ++i){
				if (shuffleIndexes[i*2] == index){
					index = shuffleIndexes[i*2+1];
				} else if (shuffleIndexes[i*2+1] == index){
					index = shuffleIndexes[i*2];
				}
			}
			
			return index;
		}
};
#endif