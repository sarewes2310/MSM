#include <stdio.h>
#include <iostream>
#include <cstdint>

using namespace std;

bool testing_output_while()
{
	cout << "test gan" << endl;
	return 1;
}

int main(int argc, char const *argv[])
{
	string test = "UJI COBA GAN";
	for (int i = 0; i < test.length(); ++i)
	{
		if(test[i] != '\t')cout << test[i] << endl;
		else cout << "SPASI" << endl;
	}
	while(!testing_output_while());
	return 0;
}