#include "source.h"
#include <string>
#include <sstream>
#include <bitset>
#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

IPv4::IPv4():ip(0){}
IPv4::IPv4(unsigned long a):ip(a){}
IPv4::IPv4(unsigned char A, unsigned char B,
           unsigned char C, unsigned char D){
    /*
    unsigned long a, b, c, d;
    a = (unsigned long) A << 24;
    b = (unsigned long) B << 16;
    c = (unsigned long) C << 8;
    d = (unsigned long) D;
    ip = a|b|c|d;
    */
    char * ch = (char *) &ip;
    ch[0] = D;
    ch[1] = C;
    ch[2] = B;
    ch[3] = A;
}

void IPv4::update(unsigned long a){
    ip = a;
}

void IPv4::update(unsigned char A, unsigned char B,
                  unsigned char C, unsigned char D){
    char * ch = (char *) &ip;
    ch[0] = D;
    ch[1] = C;
    ch[2] = B;
    ch[3] = A;
}

unsigned char IPv4::getA() const{
    return (unsigned char)((ip & 0xFF000000) >> 24);

    //char * ch = (char *) &ip;
    //return (unsigned char) ch[3];
}
unsigned char IPv4::getB() const{
    //return (unsigned char)((ip & 0x00FF0000) >> 16);
    char * ch = (char *) &ip;
    return (unsigned char) ch[2];
}
unsigned char IPv4::getC() const{
    return (unsigned char)((ip & 0x0000FF00) >> 8);
    //char * ch = (char *) &ip;
    //return (unsigned char) ch[1];
}
unsigned char IPv4::getD() const{
    return (unsigned char)((ip & 0x000000FF));

    //char * ch = (char *) &ip;
    //return (unsigned char) ch[0];
}
unsigned char IPv4::getIP() const{
    return ip;
}

std::string IPv4::to_string(typeDisplay t) const{
    string s;
    stringstream ss;
    bitset<8> bs;
    unsigned char a, b, c, d;
    a = getA(); b = getB(); c = getC(); d = getD();
    switch(t){
    case BIN:
        ss << bitset<8>(a).to_string() << ".";
        ss << bitset<8>(b).to_string() << ".";
        ss << bitset<8>(c).to_string() << ".";
        ss << bitset<8>(d).to_string();
        s = ss.str();
        break;
    case DEC:
        ss << (unsigned int) a << ".";
        ss << (unsigned int) b << ".";
        ss << (unsigned int) c << ".";
        ss << (unsigned int) d;
        s = ss.str();
        break;
    case HEX:
        ss << hex << (unsigned int) a << ".";
        ss << hex << (unsigned int) b << ".";
        ss << hex << (unsigned int) c << ".";
        ss << hex << (unsigned int) d;
        s = ss.str();
        break;
    default:
        s = "";
    }

    return s;
}


char IPv4::getClass() const{
    unsigned char a = getA();
    if( a < 128 )
        return 'A';
    if( a < 192 )
        return 'B';
    if( a < 224 )
        return 'C';
    if( a < 240 )
        return 'D';
    return 'E';
}

char IPv4::getClass2() const{
    unsigned char a = getA();
    if( ! (a & 0b10000000) )
        return 'A';
    if( ! (a & 0b01000000) )
        return 'B';
    if( ! (a & 0b00100000) )
        return 'C';
    if( ! (a & 0b00010000) )
        return 'D';
    return 'E';
}


unsigned long IPv4::netmask(short cidr){
    if(cidr < 0) cidr = 0;
    if(cidr > 32) cidr = 32;

    unsigned long long m = 0xFFFFFFFF;
    m = m << (32 - cidr);
    return (unsigned long) m;
}

IPv4 IPv4::getNetworkIP(short cidr) const{
    IPv4 net;
    unsigned long m = IPv4::netmask(cidr);
    net.update(m & this->ip);
    return net;
}

IPv4 IPv4::getBroadcastIP(short cidr) const{
    // calcul du masque
    unsigned long m = IPv4::netmask(cidr);
    // inversion du masque en faisant un XOR
    unsigned long im = m ^ 0xFFFFFFFF;
    // OU logique entre l'inverse du masque et l'IP
    unsigned long bd = im | this->ip;
    // préparation de l'IP à retrouner
    IPv4 b(bd);
    return b;
}

IPv4 IPv4::getBroadcastIP2(short cidr) const{
    if(cidr < 0) cidr = 0;
    if(cidr > 32) cidr = 32;
    IPv4 r = getNetworkIP(cidr);
    // calcul de 2**(32 - cidr) - 1
    unsigned long m = (((unsigned long long) 1) << (32 - cidr)) - 1;
    //
    r.update(r.ip + m);
    return r;
}

IPv4 IPv4::getBroadcastIP3(short cidr) const{
    if(cidr < 0) cidr = 0;
    if(cidr > 32) cidr = 32;

    IPv4 r = getNetworkIP(cidr);
    // calcul de 2**(32 - cidr) - 1
    // unsigned long m = (((unsigned long long) 1) << (32 - cidr)) - 1;
    unsigned long m = ((long long)0xFFFFFFFF) >> cidr;
    //
    r.update(r.ip + m);
    return r;
}


IPv4 IPv4::getBroadcastIP4(short cidr) const{
    if(cidr < 0) cidr = 0;
    if(cidr > 32) cidr = 32;
    // calcul de l'inverse masque
    unsigned long im = ((long long)0xFFFFFFFF) >> cidr;
    // OU logique entre l'inverse du masque et l'IP
    unsigned long bd = im | this->ip;
    // préparation de l'IP à retrouner
    IPv4 b(bd);
    return b;
}

IPv4 IPv4::getFirstIP(short cidr) const{
    if(cidr < 0) cidr = 0;
    if(cidr > 32) cidr = 32;

    if(cidr >= 31)
        return getNetworkIP(cidr);
    return IPv4(getNetworkIP(cidr).ip + 1);
}

IPv4 IPv4::getLastIP(short cidr) const{
    if(cidr < 0) cidr = 0;
    if(cidr > 32) cidr = 32;

    if(cidr == 32)
        return getNetworkIP(cidr);
    if(cidr == 31)
        return getBroadcastIP(cidr);
    return IPv4(getBroadcastIP(cidr).ip - 1);
}

unsigned long long IPv4::getNumberIP(short cidr){
    if(cidr < 0) cidr = 0;
    if(cidr > 32) cidr = 32;
    unsigned long long n = ((unsigned long long) 1) << (32 - cidr);
    if(cidr < 31) n -= 2;
    return n;
}

bool IPv4::operator==(const IPv4 & ip2) const{
    return this->ip == ip2.ip;
}

bool IPv4::operator!=(const IPv4 & ip2) const{
    return this->ip != ip2.ip;
}

IPv4 & IPv4::operator++(){
    ip++;
    return *this;
}

IPv4 IPv4::operator++(int ){
    IPv4 temp = *this;
    ip++;
    return temp;
}

IPv4 & IPv4::operator--(){
    ip--;
    return *this;
}

IPv4 IPv4::operator--(int ){
    IPv4 temp = *this;
    ip--;
    return temp;
}

bool IPv4::inSameNetwork(const IPv4 & ip1, const IPv4 & ip2, short cidr){
    if(cidr < 0) cidr = 0;
    if(cidr > 32) cidr = 32;

    IPv4 r1 = ip1.getNetworkIP(cidr);
    IPv4 r2 = ip2.getNetworkIP(cidr);
    return r1 == r2;
}

bool IPv4::isPublic() const{
    return !(isPrivate() || isReserved());
}

bool IPv4::isPrivate() const{
    if( (ip <= 0x0AFFFFFF) && (ip >= 0x0A000000) ) return true;
    if( (ip <= 0xAC1FFFFF) && (ip >= 0xAC100000) ) return true;
    if( (ip <= 0xC0A8FFFF) && (ip >= 0xC0A80000) ) return true;
    return false;
}

bool IPv4::isReserved() const{
    char c = getClass();
    return c == 'E';
}

int IPv4::parseIP(std::string str, IPv4 & ip){

    if(count(str.begin(), str.end(), '.') != 3)
        return -1;

    if(count(str.begin(), str.end(), '/') > 1)
        return -1;

    unsigned int pos0 = 0, pos1, pos2, pos3, pos4;
    while(str[pos0] == ' ') pos0++;
    pos1 = str.find('.', pos0);
    pos2 = str.find('.', pos1+1);
    pos3 = str.find('.', pos2+1);
    pos4 = pos3;
    while(str[pos4] != ' ') pos4++;

    string sa = str.substr(pos0, pos1 - pos0),
           sb = str.substr(pos1+1, pos2 - pos1 - 1),
           sc = str.substr(pos2+1, pos3 - pos2 - 1),
           sd = str.substr(pos3+1, pos4 - pos3 - 1);

    int a = 0, b = 0, c = 0, d = 0;

    try{
        std::istringstream ssa (sa), ssb (sb), ssc (sc), ssd (sd);
        if(sa.find_first_not_of("0123456789") != std::string::npos)
            return -1;
        if(sb.find_first_not_of("0123456789") != std::string::npos)
            return -1;
        if(sc.find_first_not_of("0123456789") != std::string::npos)
            return -1;
        if(sd.find_first_not_of("0123456789") != std::string::npos)
            return -1;

        ssa >> a; ssb >> b; ssc >> c; ssd >> d;

        if( (a < 0) || (a > 255) || (b < 0) || (b > 255) ||
            (c < 0) || (c > 255) || (d < 0) || (d > 255) )
                return -1;
        ip.update(a, b, c, d);
    }
    catch (const std::exception& e) {
        return -1;
    }
    return 0;
}

int IPv4::parseIPCIDR(std::string str, IPv4 & ip, short & cidr){
//    if(sa.find_first_not_of("0123456789 /.") != std::string::npos)
//            return -1;
//    if(count(str.begin(), str.end(), '.') != 3)
//        return -1;
//    if(count(str.begin(), str.end(), '/') != 1)
//        return -1;
    return 0;
}

std::ostream & operator<<(std::ostream & out, const IPv4 & ip){
    out << ip.to_string(DEC);
    return out;
}

