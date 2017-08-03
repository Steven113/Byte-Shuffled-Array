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
	A getter will not unshuffle the entire array. Instead it will locate the bytes
	that store that item and combine them to regenerate the item.
*/
template <typename T>
class ByteShuffledArray{
	protected:
		ShuffledArray<char> * arr;
		int count;
		Random::RandomK random;
	public:
		/*
			arr = data array
			count = num items in array
			key = key used to shuffle and unshuffle array
			random = a instance of the class Random::RandomK (or a derived class)
			which is used for random generation.
		*/
	
		ByteShuffledArray(T * arr, int count, int key,Random::RandomK random){
			this->arr = new ShuffledArray<char>((char *)arr,count*sizeof(T),key,random);
			this->count = count;
			this->random = random;
			
			/* int numBytesPerObject = sizeof(T);
			
			for (int i = 0; i<count * numBytesPerObject; ++i){
				arr[i];
			} */
			
			ShuffleData(key);
		}
		
		/*
				For a byte b in the item, finds where
				the byte is moved. Combines the bytes
				to create a char array to cast as
				the original object
			*/
		virtual T get(int index, int key){
			assert(index >= 0 && index<=count);
			UnShuffleData(key);
			
			int numBytes = sizeof(T);
			char data[sizeof(T)];
			
			for (int i = 0; i<numBytes; ++i){
				data[i] = arr->get(index*numBytes + i, key);
			}
			
			//index = GetShiftedIndex(index, key);
			
			T result = *((T*)&data); 
			ShuffleData(key);
			
			return result;
		}
		
		/*
				For a byte b in each item, finds where
				the byte is moved. Combines the bytes
				to create a char array to cast as
				the original object
			*/
		virtual T * getRange(int start, int end, int key){
			assert(start >= 0 && end>=start && end<=count);
			UnShuffleData(key);
			
			//index = GetShiftedIndex(index, key);
			
			T * result = new T[end-start];

			for (int i = start; i<end; ++i){
				int numBytes = sizeof(T);
				char data[sizeof(T)];
			for (int j = 0; j<numBytes; ++j){
				data[j] = arr->get(i*numBytes + j, key);
			} 
				
			result[i-start] = *((T*)&data);
			}
			
			ShuffleData(key);
			
			return result;
		}
				
		virtual void Set(int index, int key, T item){
			assert(index >= 0 && index<=count);
			arr->UnShuffleData(key);
			UnShuffleData(key);
			
			//index = GetShiftedIndex(index, key);
			
			arr->arr[index*sizeof(T)] = item;
			
			ShuffleData(key);
			arr->ShuffleData(key);
		}

		//only applies bit shifting
		virtual void ShuffleData(int key){
			
			
			int numBytes = count * sizeof(T);
			int bitOffsets[] = {0,8,16,24};
			for (int i = 0; i< numBytes; i+=4){
				for (int j = 0; j<4; ++j){
					arr->arr[i+j] ^= key >> bitOffsets[j];
				}
			}
		}
		
		//only undoes bit shifting		
		virtual void UnShuffleData(int key){
			
			
			int numBytes = count * sizeof(T);
			int bitOffsets[] = {0,8,16,24};
			for (int i = 0; i< numBytes; i+=4){
				for (int j = 0; j<4; ++j){
					arr->arr[i+j] ^= key >> bitOffsets[j];
				}
			}
			
			
		}
		
		~ByteShuffledArray(){
			delete arr;
		}
};

template <>
class ByteShuffledArray<char>{
	protected:
		ShuffledCharArray * arr;
		int count;
		Random::RandomK random;
	public:
		/*
			arr = data array
			count = num items in array
			key = key used to shuffle and unshuffle array
			random = a instance of the class Random::RandomK (or a derived class)
			which is used for random generation.
		*/
	
		ByteShuffledArray(char * arr, int count, int key,Random::RandomK random){
			this->arr = new ShuffledCharArray((char *)arr,count*sizeof(char),key,random,4);
			this->count = count;
			this->random = random;
			
			/* int numBytesPerObject = sizeof(T);
			
			for (int i = 0; i<count * numBytesPerObject; ++i){
				arr[i];
			} */
			
			ShuffleData(key);
		}
		
		ByteShuffledArray(char * arr, int count, int key,Random::RandomK random, int r){
			this->arr = new ShuffledCharArray((char *)arr,count*sizeof(char),key,random,r);
			this->count = count;
			this->random = random;
			
			/* int numBytesPerObject = sizeof(T);
			
			for (int i = 0; i<count * numBytesPerObject; ++i){
				arr[i];
			} */
			
			ShuffleData(key);
		}
		
		/*
				For a byte b in the item, finds where
				the byte is moved. Combines the bytes
				to create a char array to cast as
				the original object
			*/
		virtual char get(int index, int key){
			assert(index >= 0 && index<=count);
			UnShuffleData(key);
			
			int numBytes = sizeof(char);
			char data[sizeof(char)];
			
			for (int i = 0; i<numBytes; ++i){
				data[i] = arr->get(index*numBytes + i, key);
			}
			
			//index = GetShiftedIndex(index, key);
			
			char result = *((char*)&data); 
			ShuffleData(key);
			
			return result;
		}
		
		/*
				For a byte b in each item, finds where
				the byte is moved. Combines the bytes
				to create a char array to cast as
				the original object
			*/
		virtual char * getRange(int start, int end, int key){
			assert(start >= 0 && end>=start && end<=count);
			UnShuffleData(key);
			
			//index = GetShiftedIndex(index, key);
			
			char * result = new char[end-start];

			for (int i = start; i<end; ++i){
				int numBytes = sizeof(char);
				char data[sizeof(char)];
			for (int j = 0; j<numBytes; ++j){
				data[j] = arr->get(i*numBytes + j, key);
			} 
				
			result[i-start] = *((char*)&data);
			}
			
			ShuffleData(key);
			
			return result;
		}
				
		virtual void Set(int index, int key, char item){
			assert(index >= 0 && index<=count);
			arr->UnShuffleData(key);
			UnShuffleData(key);
			
			//index = GetShiftedIndex(index, key);
			
			arr->arr[index*sizeof(char)] = item;
			
			ShuffleData(key);
			arr->ShuffleData(key);
		}

		//only applies bit shifting
		virtual void ShuffleData(int key){
			
			
			int numBytes = count * sizeof(char);
			int bitOffsets[] = {0,8,16,24};
			for (int i = 0; i< numBytes; i+=4){
				for (int j = 0; j<4; ++j){
					arr->arr[i+j] ^= key >> bitOffsets[j];
				}
			}
		}
		
		//only undoes bit shifting		
		virtual void UnShuffleData(int key){
			
			
			int numBytes = count * sizeof(char);
			int bitOffsets[] = {0,8,16,24};
			for (int i = 0; i< numBytes; i+=4){
				for (int j = 0; j<4; ++j){
					arr->arr[i+j] ^= key >> bitOffsets[j];
				}
			}
			
			
		}
		
		~ByteShuffledArray(){
			delete arr;
		}
};