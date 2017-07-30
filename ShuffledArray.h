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
		
		int count;
		
		Random::RandomK random;
		
		ShuffledArray(){}
	public:
		T * arr;
		
		/*
			arr = data array
			count = num items in array
			key = key used to shuffle and unshuffle array
			random = a instance of the class Random::RandomK (or a derived class)
			which is used for random generation.
		*/
		ShuffledArray(T * arr, int count, int key, Random::RandomK random){
			this->arr = arr;
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
			//UnShuffleData(key);
			
			/*
				instead of unshuffling data, just find the index of the
				item in the shuffled array
			*/
			index = GetShiftedIndex(index, key);
			
			T result = arr[index]; 
			//ShuffleData(key);
			
			return result;
		}
				
		virtual void Set(int index, int key, T item){
			assert(index >= 0 && index<=count);
			//UnShuffleData(key);
			
			/*
				instead of unshuffling data, just find the index of the
				item in the shuffled array
			*/
			index = GetShiftedIndex(index, key);
			
			arr[index] = item;
			//ShuffleData(key);
		}

		virtual void ShuffleData(int key){
			std::cout << "Shuffle array" <<std::endl;
			//get count*2 random ints
			int * shuffleIndexes = random.GetKRandomInt(key, count*2);
			
			/*
				Clamp the random indexes to the range occupied by the array
			*/
			
			for (int i = 0; i<count*2; ++i){
				shuffleIndexes[i]%=count;
				if (shuffleIndexes[i]<0){
					shuffleIndexes[i] += count;
				}
				//std::cout << shuffleIndexes[i] << " ";
			}
			
			/*
				Shuffle data
			*/
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
			
			delete [] shuffleIndexes;
		}
				
		virtual void UnShuffleData(int key){
			std::cout << "Unshuffle array" <<std::endl;
			//get random indexes
			int * shuffleIndexes = random.GetKRandomInt(key, count*2);
			
			/*
				Clamp the random indexes to the range occupied by the array
			*/
			
			for (int i = 0; i<count*2; ++i){
				shuffleIndexes[i]%=count;
				if (shuffleIndexes[i]<0){
					shuffleIndexes[i] += count;
				}
				//std::cout << shuffleIndexes[i] << " ";
			}
			
			//std::cout << std::endl;
			
			/*
				Shuffle items
			*/
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
			
			delete [] shuffleIndexes;
		}
		
		/*
			Get item at index by finding where the shuffling process moves it 
			in array
		*/
		virtual int GetShiftedIndex(int index, int key){
			int * shuffleIndexes = random.GetKRandomInt(key, count*2);
			
			for (int i = 0; i<count*2; ++i){
				shuffleIndexes[i]%=count;
				if (shuffleIndexes[i]<0){
					shuffleIndexes[i] += count;
				}
			}
			
			/*
				Goes through the shuffling indexes. When 
				index shuffleIndexes[i*2] needs to be swapped with 
				shuffleIndexes[i*2+1] and index === shuffleIndexes[i*2]
				or shuffleIndexes[i*2+1] == index, index must be 
				assigned to the shuffle index value. For example if we 
				start with index 3 and it is swapped with index 7, 
				we now want to find where index 7 is swapped with another
				index
			*/
			for (int i = 0; i<count; ++i){
				if (shuffleIndexes[i*2] == index){
					index = shuffleIndexes[i*2+1];
				} else if (shuffleIndexes[i*2+1] == index){
					index = shuffleIndexes[i*2];
				}
			}
			
			delete [] shuffleIndexes;
			
			return index;
		}
};
#endif