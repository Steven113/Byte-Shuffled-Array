#include <assert.h>
#include "Random.h"
#include <iostream>

template <typename T>
class ShuffledArray{
	private:
		T * arr;
		int count;
		int key;
	public:
		ShuffledArray(T * arr, int count, int key){
			this->arr = arr;
			this->count = count;
			this->key = key;
			ShuffleData(key);
		}
				
		T get(int index, int key){
			assert(index >= 0 && index<=count);
			UnShuffleData(key);
			T result = arr[index]; 
			ShuffleData(key);
			
			return result;
		}
				
		void Set(int index, int key, T item){
			assert(index >= 0 && index<=count);
			UnShuffleData(key);
			arr[index] = item;
			ShuffleData(key);
		}

		void ShuffleData(int key){
			std::cout << "Shuffle array" <<std::endl;
			int * shuffleIndexes = Random::GetKRandomInt(key, count*2);
			
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
				
		void UnShuffleData(int key){
			std::cout << "Unshuffle array" <<std::endl;
			int * shuffleIndexes = Random::GetKRandomInt(key, count*2);
			
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
};