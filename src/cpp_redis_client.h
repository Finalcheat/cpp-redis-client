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

    // lists
    public:
        CppRedisClient::StringReply lindex(const std::string& key, const int index);
        int linsert(const std::string& key, const int flag, const std::string& pivot, const std::string& value);
        size_t llen(const std::string& key);
        CppRedisClient::StringReply lpop(const std::string& key);
        size_t lpush(const std::string& key, const std::string& value);
        size_t lpush(const std::string& key, const std::vector<std::string>& values);
        size_t lpushx(const std::string& key, const std::string& value);
        std::vector<std::string> lrange(const std::string& key, const int start, const int stop);
        size_t lrem(const std::string& key, const int count, const std::string& value);
        void lset(const std::string& key, const int index, const std::string& value);
        void ltrim(const std::string& key, const int start, const int stop);
        CppRedisClient::StringReply rpop(const std::string& key);
        CppRedisClient::StringReply rpoplpush(const std::string& srcKey, const std::string& dstKey);
        size_t rpush(const std::string& key, const std::string& value);
        size_t rpush(const std::string& key, const std::vector<std::string>& values);
        size_t rpushx(const std::string& key, const std::string& value);

    // sets
    public:
        size_t sadd(const std::string& key, const std::string& member);
        size_t sadd(const std::string& key, const std::vector<std::string>& members);
        size_t sadd(const std::string& key, const std::set<std::string>& members);
        size_t scard(const std::string& key);
        std::string sdiff(const std::string& key1, const std::string& key2);
        std::vector<std::string> sdiff(const std::string& key, const std::vector<std::string>& keys);
        size_t sdiffstore(const std::string& dstKey, const std::string& key1, const std::string& key2);
        size_t sdiffstore(const std::string& dstKey, const std::string& key, 
                const std::vector<std::string>& keys);
        std::string sinter(const std::string& key1, const std::string& key2);
        std::vector<std::string> sinter(const std::string& key, const std::vector<std::string>& keys);
        size_t sinterstore(const std::string& dstKey, const std::string& key1, const std::string& key2);
        size_t sinterstore(const std::string& dstKey, const std::string& key, 
                const std::vector<std::string>& keys);
        int sismember(const std::string& key, const std::string& member);
        std::vector<std::string> smembers(const std::string& key);
        int smove(const std::string& sourceKey, const std::string& dstKey, const std::string& member);
        CppRedisClient::StringReply spop(const std::string& key);
        CppRedisClient::StringReply srandmember(const std::string& key);
        std::vector<std::string> srandmember(const std::string& key, const int count);
        size_t srem(const std::string& key, const std::string& member);
        size_t srem(const std::string& key, const std::vector<std::string>& members);
        size_t srem(const std::string& key, const std::set<std::string>& members);
        std::string sunion(const std::string& key1, const std::string& key2);
        std::vector<std::string> sunion(const std::string& key, const std::vector<std::string>& keys);
        size_t sunionstore(const std::string& dstKey, const std::string& key1, const std::string& key2);
        size_t sunionstore(const std::string& dstKey, const std::string& key, 
                const std::vector<std::string>& keys);


    public:
        bool ping();
        size_t llen(const std::string& key);

        // std::string get(const std::string& key) const;

    private:
        RedisClientImpl *impl;
};

}


#endif
