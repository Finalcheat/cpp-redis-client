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
 * @file string_reply.cpp
 * @brief 
 * @author Finalcheat
 * @version 0.01
 * @date 2016-01-01
 */

#include "string_reply.h"
#include "string_reply_impl.cpp"


namespace cpp_redis_client {


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


}
