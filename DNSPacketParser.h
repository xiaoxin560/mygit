#ifndef DNSPACKETPARSER_HPP
#define DNSPACKETPARSER_HPP

#include "DNS_HEADER.h"
//#include <arpa/inet.h>
#include <vector>
#include <string>

class DNSPacketParser{
public:
    DNSPacketParser(){};
    DNSPacketParser(const char *pkt, unsigned int pktlen) : pkt(pkt), pktlen(pktlen){ setDNSHeader(); };
    ~DNSPacketParser(){};
    void parse();
    void parse(const char *pkt, unsigned int pktlen);
	std::vector<std::string>getip(){ return recvip; };
    
private:
    const char *pkt;
    unsigned int pktlen;
    const DNSHeader *header; 
    const char *body;
    int questions;
    int answerRRs;
    int authorityRRs;
    int additionalRRs;
	std::vector<QuestionFiled> questionFields;
    std::vector<ResourceRecord> answerFields;
    std::vector<ResourceRecord> authorityFields;
    std::vector<ResourceRecord> additionalFields;
	std::vector<std::string> recvip;

    void clear();
    void setDNSHeader();
    void printPacketHeader();
    void printFields();
    const char *parseQuestion(const char *begin);
    const char *parseResourceRecord(const char *begin, int rrtype);
    bool isptr(unsigned char chr){ return (chr & 0xc0) == 0xc0;};
    unsigned short ptrOffset(unsigned short a){ return (a & 0x3fff); };
    char *parseData(const char *begin, int *data_offset);
    template <typename T> void printVector(const std::vector<T> &v);
};

#endif
