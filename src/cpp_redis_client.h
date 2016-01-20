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


    // hashs
    public:
        size_t hdel(const std::string& key, const std::string& field);
        size_t hdel(const std::string& key, const std::vector<std::string>& fields);
        size_t hexists(const std::string& key, const std::string& field);
        CppRedisClient::StringReply hget(const std::string& key, const std::string& field);
        std::map<std::string, std::string> hgetall(const std::string& key);
        int hincrby(const std::string& key, const std::string& field, const int amount);
        std::string hincrbyfloat(const std::string& key, const std::string& field, const float amount);
        std::vector<std::string> hkeys(const std::string& key);
        size_t hlen(const std::string& key);
        CppRedisClient::StringReply hmget(const std::string& key, const std::string& field);
        std::vector<CppRedisClient::StringReply> hmget(const std::string& key, const std::vector<std::string>& fields);
        void hmset(const std::string& key, const std::string& field, const std::string& value);
        void hmset(const std::string& key, const std::map<std::string, std::string>& fvMap);
        size_t hset(const std::string& key, const std::string& field, const std::string& value);
        size_t hsetnx(const std::string& key, const std::string& field, const std::string& value);
        std::vector<std::string> hvals(const std::string& key);


    public:
        bool ping();
        size_t llen(const std::string& key);

        // std::string get(const std::string& key) const;

    private:
        RedisClientImpl *impl;
};

}


#endif
