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
 * @file cpp_redis_client.h
 * @brief 
 * @author Finalcheat
 * @version 0.01
 * @date 2016-01-01
 */


#ifndef CPP_REDIS_CLIENT
#define CPP_REDIS_CLIENT

#include <string>

namespace cpp_redis_client {

class RedisClientImpl;

class RedisClient
{
    public:
        RedisClient();
        RedisClient(const std::string& host, const std::string& port = "6379");
        ~RedisClient();

    public:
        void set(const std::string& key, const std::string& value);
        void setex(const std::string& key, const size_t ttl, const std::string& value);
        int setnx(const std::string& key, const std::string& value);
        const size_t append(const std::string& key, const std::string& value);
        int pexpire(const std::string& key, const size_t milliseconds);
        int expire(const std::string& key, const size_t seconds);
        size_t getbit(const std::string& key, const size_t offset);
        int incr(const std::string& key);
        int incrby(const std::string& key, const int amount);
        int decr(const std::string& key);
        int decrby(const std::string& key, const int amount);
        size_t strlen(const std::string& key);
        int ttl(const std::string& key);
        int pttl(const std::string& key);
        std::string getrange(const std::string& key, const int start, const int end);
        bool ping();
        int persist(const std::string& key);
        int rename(const std::string& srcKey, const std::string& dstKey);
        int renamenx(const std::string& srcKey, const std::string& dstKey);
        size_t llen(const std::string& key);
        int move(const std::string& key, const size_t db);
        int exists(const std::string& key);

        std::string get(const std::string& key) const;
        std::string getset(const std::string& key, const std::string& value);

    private:
        RedisClientImpl *impl;
};

}


#endif
