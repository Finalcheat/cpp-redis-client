/* Copyright (C) 
 * 2016 - Finalcheat
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 */

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


namespace cpp_redis_client {

class StringReplyImpl
{
    public:
        explicit StringReplyImpl(const boost::shared_ptr<char>& buf, const int length);
        ~StringReplyImpl();
        int getLength() const { return _length; }
        char* getBuf() { return _buf.get(); }
        std::string toString() const;
        bool isNull() const;

    private:
        int _length;
        boost::shared_ptr<char> _buf;
};


std::ostream& operator<<(std::ostream& os, StringReplyImpl& impl)
{
    char* buf = impl.getBuf();
    // os << (*buf);
    const int length = impl.getLength();
    char* end = buf + length;
    // while (buf != end)
    // {
        // os << *buf++;
    // }
    return os;
}



StringReplyImpl::StringReplyImpl(const boost::shared_ptr<char>& buf, const int length) : 
    _length(length), _buf(buf)
{
}


StringReplyImpl::~StringReplyImpl()
{
    std::cout << "~StringReplyImpl" << std::endl;
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
