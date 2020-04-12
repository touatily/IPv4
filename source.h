#ifndef SOURCE_H_INCLUDED
#define SOURCE_H_INCLUDED

#include <string>
#include <iostream>

enum typeDisplay{
    BIN, DEC, HEX
};
typedef enum typeDisplay typeDisplay;


class IPv4{
    unsigned long ip;
public:
    IPv4();
    IPv4(unsigned long a);
    IPv4(unsigned char A, unsigned char B, unsigned char C, unsigned char D);

    void update(unsigned long a);
    void update(unsigned char A, unsigned char B, unsigned char C, unsigned char D);
    unsigned char getA() const;
    unsigned char getB() const;
    unsigned char getC() const;
    unsigned char getD() const;
    unsigned char getIP() const;

    std::string to_string(typeDisplay t) const;

    char getClass() const ;
    char getClass2() const;

    static unsigned long netmask(short cidr);
    IPv4 getNetworkIP(short cidr) const;

    IPv4 getBroadcastIP(short cidr) const;
    IPv4 getBroadcastIP2(short cidr) const;
    IPv4 getBroadcastIP3(short cidr) const;
    IPv4 getBroadcastIP4(short cidr) const;

    IPv4 getFirstIP(short cidr) const;
    IPv4 getLastIP(short cidr) const;

    static unsigned long long getNumberIP(short cidr);

    bool operator==(const IPv4 & ip2) const;
    bool operator!=(const IPv4 & ip2) const;

    IPv4 & operator++();
    IPv4 operator++(int );
    IPv4 & operator--();
    IPv4 operator--(int );

    static bool inSameNetwork(const IPv4 & ip1, const IPv4 & ip2, short cidr);

    bool isPublic() const;
    bool isPrivate() const;
    bool isReserved() const;

    static int parseIP(std::string str, IPv4 & ip);
    static int parseIPCIDR(std::string str, IPv4 & ip, short & cidr);

};

std::ostream & operator<<(std::ostream & out, const IPv4 & ip);

#endif // SOURCE_H_INCLUDED

