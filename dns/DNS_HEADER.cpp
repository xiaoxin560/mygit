#include"DNS_HEADER.h"
#include <iostream>

std::ostream & operator<<(std::ostream &os, const QuestionFiled &q)
{
    return os << q.name << "\t" << q.type_ << "\t" << q.class_;
}
std::ostream & operator<<(std::ostream &os, const ResourceRecord &r)
{
    return os << r.name << "\t" << r.type_ << "\t" << r.data; 
}

