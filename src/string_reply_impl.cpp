/**
 * @file string_reply_impl.cpp
 * @brief 
 * @author Finalcheat
 * @version 0.01
 * @date 2016-01-01
 */


#ifndef STRING_REPLY_IMPL
#define STRING_REPLY_IMPL

#include <iostream>
#include <string>


namespace CppRedisClient {

class StringReplyImpl
{
    public:
        explicit StringReplyImpl(const boost::shared_ptr<char>& buf, const int length);
        explicit StringReplyImpl(const std::string& reply);
        ~StringReplyImpl();
        int getLength() const { return _length; }
        int size() const { return _length; }
        char* getBuf() const { return _buf.get(); }
        std::string toString() const;
        bool isNull() const;

    private:
        int _length;
        boost::shared_ptr<char> _buf;
};


bool operator==(const StringReplyImpl& lhs, const std::string& rhs)
{
    int lhsLength = lhs.getLength();
    if (lhsLength == -1)
        return false;

    int rhsLength = rhs.size();
    if (lhsLength != rhsLength)
        return false;

    char* buf = lhs.getBuf();
    for (int i = 0; i < lhsLength; ++i)
    {
        if (buf[i] != rhs[i])
            return false;
    }

    return true;
}


std::ostream& operator<<(std::ostream& os, StringReplyImpl& impl)
{
    const int length = impl.getLength();
    if (length == -1)
    {
        os << "NULL";
        return os;
    }
    char* buf = impl.getBuf();
    char* end = buf + length;
    while (buf != end)
    {
        os << *buf++;
    }
    return os;
}



StringReplyImpl::StringReplyImpl(const boost::shared_ptr<char>& buf, const int length) : 
    _length(length), _buf(buf)
{
}


StringReplyImpl::StringReplyImpl(const std::string& reply) : _length(reply.size()), _buf(new char[reply.size()])
{
    std::copy(reply.begin(), reply.end(), _buf.get());
}


StringReplyImpl::~StringReplyImpl()
{
    // std::cout << "~StringReplyImpl" << std::endl;
}


std::string StringReplyImpl::toString() const
{
    if (_length == -1)
        throw std::runtime_error("Key Is NULL");

    return std::string(_buf.get(), _buf.get() + _length);
}


bool StringReplyImpl::isNull() const
{
    return _length == -1;
}


}


#endif
