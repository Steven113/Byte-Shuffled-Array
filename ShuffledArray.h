#ifndef SHUFFLED_ARRAY
#define SHUFFLED_ARRAY
#include "Random.h"
#include "Conversion.h"
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
bool debugPrint = false;

template <typename T, typename K>
class ShuffledArray{
	protected:
		
		const int count;
		
		Random::RandomK<K> random;
		
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
		ShuffledArray(T * arr, int lcount, K key, Random::RandomK<K> random) : count(lcount){
			this->arr = arr;
			//this->count = count;
			this->random = random;
			
			/* int numBytesPerObject = sizeof(T);
			
			for (int i = 0; i<count * numBytesPerObject; ++i){
				arr[i];
			} */
			
			ShuffleData(key);
		}
				
		virtual T get(int index, K key){
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
				
		virtual void Set(int index, K key, T item){
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

		virtual void ShuffleData(K key){
			std::cout << "Shuffle array" <<std::endl;
			//get count*2 random ints
			int * shuffleIndexes = random.GetKRandomInt(key, count);
			
			/*
				Clamp the random indexes to the range occupied by the array
			*/
			
			for (int i = 0; i<count; ++i){
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
				temp = arr[shuffleIndexes[i]];
				arr[shuffleIndexes[i]] = arr[i];
				arr[i] = temp;
				//std::cout << i << " i" <<std::endl;
			}
			
			if (debugPrint){
			std::cout << "Shuffled array: ";
			for (int i = 0; i<count; ++i){
				std::cout << arr[i] << " ";
			}
			std::cout << std::endl;
			}
			
			delete [] shuffleIndexes;
		}
				
		virtual void UnShuffleData(K key){
			std::cout << "Unshuffle array" <<std::endl;
			//get random indexes
			int * shuffleIndexes = random.GetKRandomInt(key, count);
			
			/*
				Clamp the random indexes to the range occupied by the array
			*/
			
			for (int i = 0; i<count; ++i){
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
				temp = arr[shuffleIndexes[i]];
				arr[shuffleIndexes[i]] = arr[i];
				arr[i] = temp;
				//std::cout << i << " i" <<std::endl;
			}
			
			if (debugPrint){
			std::cout << "Unshuffled array: ";
			for (int i = 0; i<count; ++i){
				std::cout << arr[i] << " ";
			}
			std::cout << std::endl;
			}
			
			delete [] shuffleIndexes;
		}
		
		/*
			Get item at index by finding where the shuffling process moves it 
			in array
		*/
		virtual int GetShiftedIndex(int index, K key){
			int * shuffleIndexes = random.GetKRandomInt(key, count);
			
			for (int i = 0; i<count; ++i){
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
				if (i == index){
					index = shuffleIndexes[i];
				} else if (shuffleIndexes[i] == index){
					index = i;
				}
			}
			
			delete [] shuffleIndexes;
			
			return index;
		}
};

//list of chars that can be used by ShuffledCharArray.
char randomCharRef[91] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','!','(',')','{','}','?','<','$','#','.',',','\n','\n'};



/*
	A special class for handling shuffled arrays of characters. It adds r (r = 'replication factor') random characters
	for every character in the original string and scrambles the result.
*/
template <typename K>
class ShuffledCharArray{
	protected:
		
		const int count;
		
		const int r;
		
		Random::RandomK<K> random;
		
		//ShuffledCharArray()  : count(){}
	public:
		char * arr;
		
		/*
			arr = data array
			count = num items in array
			key = key used to shuffle and unshuffle array
			random = a instance of the class Random::RandomK (or a derived class)
			which is used for random generation.
		*/
		ShuffledCharArray(char * arr, int lcount, K key, Random::RandomK<K> random, int lr)  : count(lcount), r(lr){
			std::cout << "Special char scrambled instantiated. " << " r = " << r << std::endl;
			this->arr = new char[count *  (r+1)];
			
			int * shuffleIndexes = random.GetKRandomInt(key, count*(r));
			
			for (int i = 0; i<count; ++i){
				for (int j = 0; j<(r+1); ++j){
					if (j == 0){
						this->arr[i*(r+1) + j] = arr[i];
					} else {
						this->arr[i*(r+1) + j] = randomCharRef[(shuffleIndexes[i*r +j-1]%91)];
					}
				}
			}
			
			//this->count = count;
			this->random = random;
			//this->r = r;
			
			delete shuffleIndexes;
			/* int numBytesPerObject = sizeof(T);
			
			for (int i = 0; i<count * numBytesPerObject; ++i){
				arr[i];
			} */
			
			ShuffleData(key);
		}
				
		char get(int index, K key) {
			assert(index >= 0 && index<=count);
			//UnShuffleData(key);
			
			/*
				instead of unshuffling data, just find the index of the
				item in the shuffled array
			*/
			index = GetShiftedIndex(index, key);
			
			char result = arr[index]; 
			//ShuffleData(key);
			
			return result;
		}
				
		virtual void Set(int index, K key, char item){
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

		virtual void ShuffleData(K key){
			std::cout << "Shuffle array" <<std::endl;
			//get count*2 random ints
			int * shuffleIndexes = random.GetKRandomInt(key, count*(r+1));
			
			/*
				Clamp the random indexes to the range occupied by the array
			*/
			
			for (int i = 0; i<count*(r+1); ++i){
				shuffleIndexes[i]%=count*(r+1);
				if (shuffleIndexes[i]<0){
					shuffleIndexes[i] += count*(r+1);
				}
				//std::cout << shuffleIndexes[i] << " ";
			}
			
			/*
				Shuffle data
			*/
			char temp;
			
			for (int i = 0; i<count*(r+1); ++i){
				//std::cout << shuffleIndexes[i*2] << " shuffleIndexes[i*2]" <<std::endl;
				//std::cout << shuffleIndexes[i*2+1] << " shuffleIndexes[i*2+1]" <<std::endl;
				temp = arr[shuffleIndexes[i]];
				arr[shuffleIndexes[i]] = arr[i];
				arr[i] = temp;
				//std::cout << i << " i" <<std::endl;
			}
			
			if (debugPrint){
			std::cout << "Shuffled array: ";
			for (int i = 0; i<count*(r+1); ++i){
				std::cout << arr[i] << " ";
			}
			std::cout << "|" << std::endl;
			}
			
			delete [] shuffleIndexes;
		}
				
		virtual void UnShuffleData(K key){
			std::cout << "Unshuffle array" <<std::endl;
			//get random indexes
			int * shuffleIndexes = random.GetKRandomInt(key, count*(r+1));
			
			/*
				Clamp the random indexes to the range occupied by the array
			*/
			
			for (int i = 0; i<count*(r+1); ++i){
				shuffleIndexes[i]%=count*(r+1);
				if (shuffleIndexes[i]<0){
					shuffleIndexes[i] += count*(r+1);
				}
				//std::cout << shuffleIndexes[i] << " ";
			}
			
			//std::cout << std::endl;
			
			/*
				Shuffle items
			*/
			char temp;
			
			for (int i = count*(r+1) - 1; i>=0; --i){
				//std::cout << shuffleIndexes[i*2] << " shuffleIndexes[i*2]" <<std::endl;
				//std::cout << shuffleIndexes[i*2+1] << " shuffleIndexes[i*2+1]" <<std::endl;
				temp = arr[shuffleIndexes[i]];
				arr[shuffleIndexes[i]] = arr[i];
				arr[i] = temp;
				//std::cout << i << " i" <<std::endl;
			}
			
			if (debugPrint){
			std::cout << "Unshuffled array: ";
			for (int i = 0; i<count*(r+1); ++i){
				std::cout << arr[i] << " ";
			}
			std::cout << "|" << std::endl;
			}
			
			delete [] shuffleIndexes;
		}
		
		/*
			Get item at index by finding where the shuffling process moves it 
			in array
		*/
		virtual int GetShiftedIndex(int index, K key){
			int * shuffleIndexes = random.GetKRandomInt(key, count*(r+1));
			
			for (int i = 0; i<count*(r+1); ++i){
				shuffleIndexes[i]%=count*(r+1);
				if (shuffleIndexes[i]<0){
					shuffleIndexes[i] += count*(r+1);
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
			index = index * (r+1);
			
			for (int i = 0; i<count*(r+1); ++i){
				if (i == index){
					index = shuffleIndexes[i];
				} else if (shuffleIndexes[i] == index){
					index = i;
				}
			}
			
			delete [] shuffleIndexes;
			
			return index;
		}
};
#endif