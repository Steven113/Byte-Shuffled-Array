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
			
			int numBytes = count * sizeof(T);
			int bitOffsets[] = {0,8,16,24};
			for (int i = 0; i< numBytes; i+=4){
				for (int j = 0; j<4; ++j){
					arr[i+j] ^= key << bitOffsets[j];
				}
			}
			
			std::cout << "Shuffled array: ";
			for (int i = 0; i<count; ++i){
				std::cout << *((T*)(arr + i*sizeof(T))) << " ";
			}
			std::cout << std::endl;
		}
				
		virtual void UnShuffleData(int key){
			std::cout << "Unshuffle array" <<std::endl;
			
			int numBytes = count * sizeof(T);
			int bitOffsets[] = {0,8,16,24};
			for (int i = 0; i< numBytes; i+=4){
				for (int j = 0; j<4; ++j){
					arr[i+j] ^= key << bitOffsets[j];
				}
			}
			
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
		
		/* virtual void ShuffleDataItem(int key, int index){
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
			
			int numBytes = sizeof(T);
			int indexes[numBytes];
			int start = index*numBytes;
			indexes[0] = start;
			for (int i = 1; i<numBytes; ++i){
				indexes[i] = indexes[i-1] + 1;
			}
			
			for (int i = 0; i<count; ++i){
				for (int j = 0; j<numBytes; ++j){
					if (indexes[j] == shuffleIndexes[i*2]){
						indexes [j] = shuffleIndexes[i*2+1];
					} else if (indexes[j] == shuffleIndexes[i*2+1]){
						indexes [j] = shuffleIndexes[i*2];
					}
				}
			}
			
			char temp;
			for (int j = 0; j<numBytes; ++j){
				temp = arr[indexes[j]];
				arr[indexes[j]] = arr[start + j];
				arr[start + j] = j;
			}
			
			std::cout << "Shuffled array: ";
			for (int i = 0; i<count; ++i){
				std::cout << *((T*)(arr + i*sizeof(T))) << " ";
			}
			std::cout << std::endl;
		}
				
		virtual void UnShuffleDataItem(int key, int index){
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
			
			int numBytes = sizeof(T);
			int indexes[numBytes];
			int start = index*numBytes;
			indexes[0] = start;
			for (int i = 1; i<numBytes; ++i){
				indexes[i] = indexes[i-1] + 1;
			}
			
			for (int i = 0; i<count; ++i){
				for (int j = 0; j<numBytes; ++j){
					if (indexes[j] == shuffleIndexes[i*2]){
						indexes [j] = shuffleIndexes[i*2+1];
					} else if (indexes[j] == shuffleIndexes[i*2+1]){
						indexes [j] = shuffleIndexes[i*2];
					}
				}
			}
			
			char temp;
			for (int j = 0; j<numBytes; ++j){
				temp = arr[indexes[j]];
				arr[indexes[j]] = arr[start + j];
				arr[start + j] = j;
			}
			
			std::cout << "Unshuffled array: ";
			for (int i = 0; i<count; ++i){
				std::cout << *((T*)(arr + i*sizeof(T))) << " ";
			}
			std::cout << std::endl;
		} */
};