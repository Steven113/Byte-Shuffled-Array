#include "ShuffledArray.h"

template <typename T>
class ByteShuffledArray{
	protected:
		char * arr;
		int count;
	public:
		ByteShuffledArray(T * arr, int count, int key){
			this->arr = (char *)arr;
			this->count = count;
			ShuffleData(key);
		}
				
		virtual T get(int index, int key){
			assert(index >= 0 && index<=count);
			UnShuffleData(key);
			
			//index = GetShiftedIndex(index, key);
			
			T result = arr[index*sizeof(T)]; 
			ShuffleData(key);
			
			return result;
		}
				
		virtual void Set(int index, int key, T item){
			assert(index >= 0 && index<=count);
			UnShuffleData(key);
			
			//index = GetShiftedIndex(index, key);
			
			arr[index*sizeof(T)] = item;
			ShuffleData(key);
		}

		virtual void ShuffleData(int key){
			std::cout << "Shuffle array" <<std::endl;
			int * shuffleIndexes = Random::GetKRandomInt(key, count*2);
			
			std::cout << "Clamping Indexes: ";
			
			for (int i = 0; i<count*2; ++i){
				shuffleIndexes[i]%=count*sizeof(T);
				if (shuffleIndexes[i]<0){
					shuffleIndexes[i] += count*sizeof(T);
				}
				std::cout << shuffleIndexes[i] << " ";
			}
			
			std::cout << std::endl;
			
			char temp;
			
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
				std::cout << *((T*)(arr + i*sizeof(T))) << " ";
			}
			std::cout << std::endl;
		}
				
		virtual void UnShuffleData(int key){
			std::cout << "Unshuffle array" <<std::endl;
			int * shuffleIndexes = Random::GetKRandomInt(key, count*2);
			
			std::cout << "Clamping Indexes: ";
			
			for (int i = 0; i<count*2; ++i){
				shuffleIndexes[i]%=count*sizeof(T);
				if (shuffleIndexes[i]<0){
					shuffleIndexes[i] += count*sizeof(T);
				}
				std::cout << shuffleIndexes[i] << " ";
			}
			
			std::cout << std::endl;
			
			char temp;
			
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
				std::cout << *((T*)(arr + i*sizeof(T))) << " ";
			}
			std::cout << std::endl;
		}
};