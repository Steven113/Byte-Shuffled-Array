#define TEST_SHUFFLED_ARRAY(dataname,type,count, init ,random, key) \
	type dataname[count] = init;\
	ShuffledArray<type> testShuffledArraydataname(dataname,counr,key,random);\
	for (int i = 0; i<count; ++i){\
		std::cout << testShuffledArraydataname.get(i,key) << std::endl;\
	}