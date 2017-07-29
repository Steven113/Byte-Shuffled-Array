#include <stdio.h>  
#include <stdlib.h> 
#include <time.h> 

namespace Random{
/*
	Return value between rangeMin (inclusive) and rangeMax(exclusive)
*/

	int seedOffSet;

	int GetRandomInt(){
		//srand (time(NULL)); //init random generator with time as seed
		//srand (0); //init random generator with time as seed
		
		++seedOffSet;
		
		srand (time(NULL) ^ seedOffSet);
		
		return rand();
	}

	/*
		
	*/
	int * GetKRandomInt(int key, int K){
		srand(key);
		int * result = new int[K];
		
		for (int i = 0; i<K; ++i){
			result[i] = rand();
		}
		
		return result;
	}
	
	/*
		Functor for function GetKRandomInt that returns an array of K integers
		given a seed "key". Note the resulting values depend entirely on the seed.
	*/
	class RandomK{
		public:
			virtual int * GetKRandomInt(int key, int K){
				srand(key);
				int * result = new int[K];
				
				for (int i = 0; i<K; ++i){
					result[i] = rand();
				}
				
				return result;
			}
	};
}
