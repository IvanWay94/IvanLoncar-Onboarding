#include <iostream>
#include <assert.h>
#include <typeinfo>  
#include <assert.h>
#include <type_traits>
using namespace std;

/*template <typename T>
void bar(T t)
{	
	cout << t;
}*/

void myPrintf(unsigned char* format) // base function
{
	cout << format << flush;
}

template<typename T, typename... Args>
constexpr void myPrintf(unsigned char *inputString,T var, Args... args)// Has to be recursive
{
	//int dummy[] = { 0, ((void)bar(forward<Args>(args)),0)... };
	while (*inputString) {
		if (*inputString != '%')
		{
			cout << *inputString << flush;
			inputString++;
			continue;
		}
		switch (*(inputString + 1))
		{
			case 'd':
			{
				assert(typeid(var)==typeid(int) || typeid(var) == typeid(unsigned int));
				break;
			}
			case 'f':
			{
				assert(typeid(var) == typeid(float) || typeid(var) == typeid(double));
				break;
			}
			case 's':
			{
				assert(typeid(var) == typeid(unsigned char*) || typeid(var) == typeid(char*));
				break;
			}
			default:
				assert(false);
		}
		cout << var << flush;
		myPrintf((inputString + 2), args...);
		return;
	}
}
int main() {
	int whole = 6;
	int whole2 = -324;
	float floatnum = 4.6;
	unsigned char stringval[50] = "String to be writen";
	myPrintf((unsigned char*)"Test whole number: %d, test floating point number: %f, test string: %s\n", whole, floatnum, stringval);
	myPrintf((unsigned char*)"Test whole number: %d test new number: %d \n", whole, whole2);
	return 0;
}