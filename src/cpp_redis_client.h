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

#include "string_reply.h"
#include <string>
#include <map>
#include <vector>

namespace CppRedisClient {

class RedisClientImpl;

class RedisClient
{
    public:
        RedisClient();
        RedisClient(const std::string& host, const std::string& port = "6379");
        ~RedisClient();


    // Keys
    public:
        size_t del(const std::string& key);
        CppRedisClient::StringReply dump(const std::string& key);
        int exists(const std::string& key);
        int expire(const std::string& key, const size_t seconds);
        size_t expireat(const std::string& key, const size_t timestamp);
        int move(const std::string& key, const size_t db);
        int persist(const std::string& key);
        int pexpire(const std::string& key, const size_t milliseconds);
        int pexpireat(const std::string& key, const size_t millisecondsTimestamp);
        int pttl(const std::string& key);
        CppRedisClient::StringReply randomkey();
        void rename(const std::string& srcKey, const std::string& dstKey);
        int renamenx(const std::string& srcKey, const std::string& dstKey);
        int ttl(const std::string& key);


    // String
    public:
        const size_t append(const std::string& key, const std::string& value);
        size_t bitcount(const std::string& key, const int start = 0, const int end = -1);
        int decr(const std::string& key);
        int decrby(const std::string& key, const int amount);
        CppRedisClient::StringReply get(const std::string& key);
        size_t getbit(const std::string& key, const size_t offset);
        std::string getrange(const std::string& key, const int start, const int end);
        std::string getset(const std::string& key, const std::string& value);
        int incr(const std::string& key);
        int incrby(const std::string& key, const int amount);
        std::string incrbyfloat(const std::string& key, const float amount);
        std::vector<CppRedisClient::StringReply> mget(const std::vector<std::string>& keys);
        void mset(const std::map<std::string, std::string>& kvMap);
        int msetnx(const std::map<std::string, std::string>& kvMap);
        void psetex(const std::string &key, const size_t milliseconds, const std::string& value);
        void set(const std::string& key, const std::string& value);
        size_t setbit(const std::string& key, const size_t offset, const size_t value);
        void setex(const std::string& key, const size_t ttl, const std::string& value);
        int setnx(const std::string& key, const std::string& value);
        size_t setrange(const std::string& key, const size_t offset, const std::string& value);
        size_t strlen(const std::string& key);


    public:
        bool ping();
        size_t llen(const std::string& key);

        // std::string get(const std::string& key) const;

    private:
        RedisClientImpl *impl;
};

}


#endif
