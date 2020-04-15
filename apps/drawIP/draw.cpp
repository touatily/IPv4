#include <iostream>
#include <ipv4>

using namespace std;

int main(int argc, char ** argv) {



	IPv4 ip = IPv4(192, 168, 0, 1);
	cout << "________________________________________" << endl;
	cout << bin << (int) ip.getA() << "|";
	cout << "________________________________________" << endl;



	return 0;
}
