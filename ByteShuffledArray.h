#include "ShuffledArray.h"

/*
	Protects an array of objects of type T in memory
	by keeping it scrambled at the byte level in memory when not getting 
	or setting values. A getter or setter can only get
	the correct data by providing the key used to construct this array.
	
	To prevent the key from being cracked you should occasionally regenerate the
	array with a new key. A instance of the class RandomK or a class derived from 
	it is needed to generate the random values generated for this class to used
	when scambling the memory. Note that the key is used as a seed for the generator.
	
	The scrambler rearranges the bytes in the array and XORs it with the key.
*/
template <typename T>
class ByteShuffledArray{
	protected:
		char * arr;
		int count;
		Random::RandomK random;
	public:
		ByteShuffledArray(T * arr, int count, int key,Random::RandomK random){
			this->arr = (char *)arr;
			this->count = count;
			this->random = random;
			
			/* int numBytesPerObject = sizeof(T);
			
			for (int i = 0; i<count * numBytesPerObject; ++i){
				arr[i];
			} */
			
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
			//std::cout << "Shuffle array" <<std::endl;
			int * shuffleIndexes = random.GetKRandomInt(key, count*2);
			
			//std::cout << "Clamping Indexes: ";
			
			for (int i = 0; i<count*2; ++i){
				shuffleIndexes[i]%=count*sizeof(T);
				if (shuffleIndexes[i]<0){
					shuffleIndexes[i] += count*sizeof(T);
				}
				//std::cout << shuffleIndexes[i] << " ";
			}
			
			//std::cout << std::endl;
			
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
					arr[i+j] ^= key >> bitOffsets[j];
				}
			}
			
			//std::cout << "Shuffled array: ";
			//for (int i = 0; i<count; ++i){
			//	std::cout << *((T*)(arr + i*sizeof(T))) << " ";
			//}
			//std::cout << std::endl;
		}
				
		virtual void UnShuffleData(int key){
			//std::cout << "Unshuffle array" <<std::endl;
			
			int numBytes = count * sizeof(T);
			int bitOffsets[] = {0,8,16,24};
			for (int i = 0; i< numBytes; i+=4){
				for (int j = 0; j<4; ++j){
					arr[i+j] ^= key >> bitOffsets[j];
				}
			}
			
			int * shuffleIndexes = random.GetKRandomInt(key, count*2);
			
			//std::cout << "Clamping Indexes: ";
			
			for (int i = 0; i<count*2; ++i){
				shuffleIndexes[i]%=count*sizeof(T);
				if (shuffleIndexes[i]<0){
					shuffleIndexes[i] += count*sizeof(T);
				}
				//std::cout << shuffleIndexes[i] << " ";
			}
			
			//std::cout << std::endl;
			
			char temp;
			
			for (int i = count - 1; i>=0; --i){
				//std::cout << shuffleIndexes[i*2] << " shuffleIndexes[i*2]" <<std::endl;
				//std::cout << shuffleIndexes[i*2+1] << " shuffleIndexes[i*2+1]" <<std::endl;
				temp = arr[shuffleIndexes[i*2]];
				arr[shuffleIndexes[i*2]] = arr[shuffleIndexes[i*2 + 1]];
				arr[shuffleIndexes[i*2 + 1]] = temp;
				//std::cout << i << " i" <<std::endl;
			}
			
			//std::cout << "Unshuffled array: ";
			//for (int i = 0; i<count; ++i){
			//	std::cout << *((T*)(arr + i*sizeof(T))) << " ";
			//}
			//std::cout << std::endl;
		}
		
/* 		virtual void ShuffleDataItem(int key, int index){
			std::cout << "Shuffle array partial" <<std::endl;
			int * shuffleIndexes = random.GetKRandomInt(key, count*2);
			
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
			int indexes[sizeof(T)];
			int start = index*numBytes;
			indexes[0] = start;
			for (int i = 1; i<numBytes; ++i){
				indexes[i] = start + i;
			}
			
			char temp;
			for (int j = 0; j<numBytes; ++j){
				for (int i = count-1; i>=0; --i){
					if (indexes[j] == shuffleIndexes[i*2]){
						indexes [j] = shuffleIndexes[i*2+1];
					} else if (indexes[j] == shuffleIndexes[i*2+1]){
						indexes [j] = shuffleIndexes[i*2];
					}
				}
				
				temp = arr[indexes[j]];
				arr[indexes[j]] = arr[start + j];
				arr[start + j] = temp;
			}
			
			
			for (int j = 0; j<numBytes; ++j){
				temp = arr[indexes[j]];
				arr[indexes[j]] = arr[start + j];
				arr[start + j] = temp;
			}
			
			numBytes = count * sizeof(T);
			int bitOffsets[] = {0,8,16,24};
			for (int i = 0; i< numBytes; i+=4){
				for (int j = 0; j<4; ++j){
					arr[i+j] ^= key >> bitOffsets[j];
				}
			}
			
			std::cout << "Shuffled array: ";
			for (int i = 0; i<count; ++i){
				std::cout << *((T*)(arr + i*sizeof(T))) << " ";
			}
			std::cout << std::endl;
		}
				
		virtual void UnShuffleDataItem(int key, int index){
			std::cout << "Unshuffle array partial" <<std::endl;
			int * shuffleIndexes = random.GetKRandomInt(key, count*2);
			
			std::cout << "Clamping Indexes: ";
			
			for (int i = 0; i<count*2; ++i){
				shuffleIndexes[i]%=count*sizeof(T);
				if (shuffleIndexes[i]<0){
					shuffleIndexes[i] += count*sizeof(T);
				}
				std::cout << shuffleIndexes[i] << " ";
			}
			
			std::cout << std::endl;
			
			int numBytes = count * sizeof(T);
			int bitOffsets[] = {0,8,16,24};
			for (int i = 0; i< numBytes; i+=4){
				for (int j = 0; j<4; ++j){
					arr[i+j] ^= key >> bitOffsets[j];
				}
			}
			
			numBytes = sizeof(T);
			int indexes[sizeof(T)];
			int start = index*numBytes;
			indexes[0] = start;
			for (int i = 1; i<numBytes; ++i){
				indexes[i] = start + i;
			}
			
			char temp;
			for (int j = 0; j<numBytes; ++j){
				for (int i = 0; i<count; ++i){
					if (indexes[j] == shuffleIndexes[i*2+1]){
						indexes [j] = shuffleIndexes[i*2];
					} else if (indexes[j] == shuffleIndexes[i*2]){
						indexes [j] = shuffleIndexes[i*2+1];
					}
				}
				
				temp = arr[indexes[j]];
				arr[indexes[j]] = arr[start + j];
				arr[start + j] = temp;
			}
			
			
			
			for (int j = 0; j<numBytes; ++j){
				temp = arr[indexes[j]];
				arr[indexes[j]] = arr[start + j];
				arr[start + j] = temp;
			}
			
			std::cout << "Unshuffled array: ";
			for (int i = 0; i<count; ++i){
				std::cout << *((T*)(arr + i*sizeof(T))) << " ";
			}
			std::cout << std::endl;
		} */
};