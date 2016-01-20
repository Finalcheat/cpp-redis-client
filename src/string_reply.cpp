/**
 * @file string_reply.cpp
 * @brief 
 * @author Finalcheat
 * @version 0.01
 * @date 2016-01-01
 */

#ifndef STRING_REPLY_CPP
#define STRING_REPLY_CPP

#include "string_reply.h"
#include "string_reply_impl.cpp"


namespace CppRedisClient {


StringReply::StringReply() : impl(boost::shared_ptr<StringReplyImpl>())
{
}


StringReply::StringReply(const boost::shared_ptr<char>& buf, const int length) : 
    impl(new StringReplyImpl(buf, length))
{
}


std::string StringReply::toString() const
{
    if (impl)
    {
        return impl->toString();
    }
    return "";
}


int StringReply::getLength() const
{
    if (impl)
    {
        return impl->getLength();
    }
    return -1;
}


bool StringReply::isNull() const
{
    if (impl)
    {
        return impl->isNull();
    }
    return true;
}


int StringReply::size() const
{
    if (impl)
    {
        return impl->size();
    }
    return -1;
}

bool StringReply::operator==(const std::string& rhs)
{
    return *impl == rhs;
}

std::ostream& operator<<(std::ostream& os, const StringReply& reply)
{
    return os << *(reply.impl);
}


}

#endif
