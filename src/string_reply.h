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
 * @file string_reply.h
 * @brief 
 * @author Finalcheat
 * @version 0.01
 * @date 2016-01-01
 */

#ifndef STRING_REPLY
#define STRING_REPLY

#include <boost/shared_ptr.hpp>

namespace cpp_redis_client {


class StringReplyImpl;

class StringReply
{
    public:
        explicit StringReply(const boost::shared_ptr<char>& buf, const int length);
        std::string toString() const;
        int getLength() const;
        bool isNull() const;

    public:
        // StringReply& operator=(const StringReply& relpy);

    private:
        boost::shared_ptr<StringReplyImpl> impl;
};


}


#endif
