#include <iostream>
#include <ipv4>
#include <string>
#include <sstream>

using namespace std;

string usage = "netmask  <CIDR1> [<CIDR2> <CIDR3> ... <CIDRn>] \n"
		"\t <CIDRi> must be an integer between 0 and 32 \n\n";

int main(int argc, char ** argv) {

	if(argc <= 1){
		cout << "Must specify CIDR value!" << endl;
		cout << usage;
		return -1;
	}

	for(int i = 1; i < argc; i++){
		cout << "CIDR " << argv[i] << ":" << endl;
		string arg(argv[i]);
		if(arg.find_first_not_of("0123456789") == std::string::npos){
			stringstream ss;
			ss << arg;
			int cidr;
			ss >> cidr;
			if( (cidr <= 32) && (cidr >= 0) ){
				IPv4 m = IPv4::netmask(cidr);
				cout << '\t' << "netmask: " << m.to_string(DEC) << endl;
			}
			else{
				cout << "\tWrong CIDR value!" << endl;
			}
		}
		else{
			cout << "\tWrong CIDR value!" << endl;
		}
	}


	return 0;
}
