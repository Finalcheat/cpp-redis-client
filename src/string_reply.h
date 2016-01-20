/**
 * @file string_reply.h
 * @brief 
 * @author Finalcheat
 * @version 0.01
 * @date 2016-01-01
 */

#ifndef STRING_REPLY
#define STRING_REPLY

#include <boost/shared_ptr.hpp>

namespace CppRedisClient {


class StringReplyImpl;

class StringReply
{
    friend std::ostream& operator<<(std::ostream& os, const StringReply& reply);

    public:
        explicit StringReply();
        explicit StringReply(const boost::shared_ptr<char>& buf, const int length);
        std::string toString() const;
        int getLength() const;
        int size() const;
        bool isNull() const;
        bool operator==(const std::string& rhs);


    public:
        // StringReply& operator=(const StringReply& relpy);

    private:
        boost::shared_ptr<StringReplyImpl> impl;
};


std::ostream& operator<<(std::ostream& os, const StringReply& reply);


}


#endif
