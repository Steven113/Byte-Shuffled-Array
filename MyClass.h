#include <iostream>
class MyClass{
	char a;
	int b;
	char c;
	char d;
	float e;
	public:
		MyClass(){}
	
		MyClass(char a, int b, char c, char d, float e){
			this->a = a;
			this->b = b;
			this->c = c;
			this->d = d;
			this->e = e;
		}
		
		friend std::ostream& operator<<(std::ostream& os, const MyClass& mc);
};

std::ostream& operator<<(std::ostream& os, const MyClass & mc)  
{  
    os << mc.a << " " << mc.b << " " << mc.c << " " << mc.d << " " << mc.e; 
    return os;  
}  