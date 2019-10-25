#include "sha256.h"
#include <iostream>

using namespace std;

int main()
{
	SHA256 sha256;
	string s="Shayak is awesome";
	cout<<sha256.modGetHashSS(s);
}
