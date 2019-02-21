#include<iostream>
#include<string>
#include<chrono>

using namespace std;

void gen_random(char *s, const int len, const long& randSeed) 
{
	static const char alphanum[] = "0123456789" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz";
	for (int i = 0; i < len; ++i) 
		s[i] = alphanum[(rand() + randSeed) % (sizeof(alphanum) - 1)];
	s[len] = '\0';
}

int main(int argc, char* argv[])
{
	const auto startPoint = chrono::high_resolution_clock::now();
	char* stringItem = new char[10];
	size_t seed;
	const auto endPoint = chrono::high_resolution_clock::now();
	long count = chrono::duration_cast<chrono::nanoseconds>(endPoint-startPoint).count();
	seed = (rand() + count)/rand();

	for(unsigned int i=0; i<10; ++i)
	{
		gen_random(stringItem, 10, seed);
		cout << stringItem << endl;
	}
	delete[] stringItem;
	return(0);
}

