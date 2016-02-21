/**
 * @file cpp_redis_client.cpp
 * @brief cpp redis client
 * @author Finalcheat
 * @version 0.01
 * @date 2015-12-21
 */

#include "cpp_redis_client.h"
#include "string_reply.h"
#include "cpp_redis_client_impl.cpp"
#include <iostream>


namespace CppRedisClient {


RedisClient::RedisClient() : impl(0)
{
    std::cout << "RedisClient Init" << std::endl;
}

RedisClient::RedisClient(const std::string& host, const std::string& port)
{
    impl = new RedisClientImpl(host, port);
}

RedisClient::~RedisClient()
{
    // std::cout << "~RedisClient" << std::endl;
    if (impl)
    {
        delete impl;
        impl = 0;
    }
}

bool RedisClient::ping()
{
    if (!impl)
        throw std::runtime_error("RedisClient::ping Error!");

    return impl->ping();
}

// Keys
size_t RedisClient::del(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::del Error!");

    return impl->del(key);
}

size_t RedisClient::del(const std::vector<std::string>& keys)
{
    if (!impl)
        throw std::runtime_error("RedisClient::del Error!");

    return impl->del(keys);
}

CppRedisClient::StringReply RedisClient::dump(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::dump Error!");

    return impl->dump(key);
}

int RedisClient::exists(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::exists Error!");

    return impl->exists(key);
}

int RedisClient::expire(const std::string& key, const size_t seconds)
{
    if (!impl)
        throw std::runtime_error("RedisClient::expire Error!");

    return impl->expire(key, seconds);
}

size_t RedisClient::expireat(const std::string& key, const size_t timestamp)
{
    if (!impl)
        throw std::runtime_error("RedisClient::expireat Error!");

    return impl->expireat(key, timestamp);
}

std::vector<std::string> RedisClient::keys(const std::string& pattern)
{
    if (!impl)
        throw std::runtime_error("RedisClient::keys Error!");

    return impl->keys(pattern);
}

int RedisClient::move(const std::string& key, const size_t db)
{
    if (!impl)
        throw std::runtime_error("RedisClient::move Error!");

    return impl->move(key, db);
}

CppRedisClient::StringReply RedisClient::object(const CppRedisClient::OBJECT_SUBCOMMAND subCommand, 
        const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::object Error!");

    return impl->object(subCommand, key);
}

int RedisClient::persist(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::persist Error!");

    return impl->persist(key);
}

int RedisClient::pexpire(const std::string& key, const int64_t milliseconds)
{
    if (!impl)
        throw std::runtime_error("RedisClient::pexpire Error!");

    return impl->pexpire(key, milliseconds);
}

int RedisClient::pexpireat(const std::string& key, const int64_t millisecondsTimestamp)
{
    if (!impl)
        throw std::runtime_error("RedisClient::pexpireat Error!");

    return impl->pexpireat(key, millisecondsTimestamp);
}

int64_t RedisClient::pttl(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::pttl Error!");

    return impl->pttl(key);
}

CppRedisClient::StringReply RedisClient::randomkey()
{
    if (!impl)
        throw std::runtime_error("RedisClient::randomkey Error!");

    return impl->randomkey();
}

void RedisClient::rename(const std::string& srcKey, const std::string& dstKey)
{
    if (!impl)
        throw std::runtime_error("RedisClient::rename Error!");

    return impl->rename(srcKey, dstKey);
}

int RedisClient::renamenx(const std::string& srcKey, const std::string& dstKey)
{
    if (!impl)
        throw std::runtime_error("RedisClient::renamenx Error!");

    return impl->renamenx(srcKey, dstKey);
}

int RedisClient::ttl(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::ttl Error!");

    return impl->ttl(key);
}

CppRedisClient::StringReply RedisClient::type(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::type Error!");

    return impl->type(key);
}


// String
const size_t RedisClient::append(const std::string& key, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::append Error!");

    return impl->append(key, value);
}

size_t RedisClient::bitcount(const std::string& key, const int start, const int end)
{
    if (!impl)
        throw std::runtime_error("RedisClient::bitcount Error!");

    return impl->bitcount(key, start, end);
}

int RedisClient::decr(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::decr Error!");

    return impl->decr(key);
}

int RedisClient::decrby(const std::string& key, const int amount)
{
    if (!impl)
        throw std::runtime_error("RedisClient::decrby Error!");

    return impl->decrby(key, amount);
}

CppRedisClient::StringReply RedisClient::get(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::get Error!");

    return impl->get(key);
}

size_t RedisClient::getbit(const std::string& key, const size_t offset)
{
    if (!impl)
        throw std::runtime_error("RedisClient::getbit Error!");

    return impl->getbit(key, offset);
}

std::string RedisClient::getrange(const std::string& key, const int start, const int end)
{
    if (!impl)
        throw std::runtime_error("RedisClient::getrange Error!");

    return impl->getrange(key, start, end);
}

CppRedisClient::StringReply RedisClient::getset(const std::string& key, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::getset Error!");

    return impl->getset(key, value);
}

int RedisClient::incr(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::incr Error!");

    return impl->incr(key);
}

int RedisClient::incrby(const std::string& key, const int amount)
{
    if (!impl)
        throw std::runtime_error("RedisClient::incrby Error!");

    return impl->incrby(key, amount);
}

std::string RedisClient::incrbyfloat(const std::string& key, const float amount)
{
    if (!impl)
        throw std::runtime_error("RedisClient::incrbyfloat Error!");

    return impl->incrbyfloat(key, amount);
}

std::vector<CppRedisClient::StringReply> RedisClient::mget(const std::vector<std::string>& keys)
{
    if (!impl)
        throw std::runtime_error("RedisClient::mget Error!");

    return impl->mget(keys);
}

void RedisClient::mset(const std::map<std::string, std::string>& kvMap)
{
    if (!impl)
        throw std::runtime_error("RedisClient::mset Error!");

    return impl->mset(kvMap);
}

int RedisClient::msetnx(const std::map<std::string, std::string>& kvMap)
{
    if (!impl)
        throw std::runtime_error("RedisClient::msetnx Error!");

    return impl->msetnx(kvMap);
}

void RedisClient::psetex(const std::string& key, const int64_t milliseconds, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::psetex Error!");

    return impl->psetex(key, milliseconds, value);
}

void RedisClient::set(const std::string& key, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::set Error!");

    return impl->set(key, value);
}

size_t RedisClient::setbit(const std::string& key, const size_t offset, const size_t value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::setbit Error!");

    return impl->setbit(key, offset, value);
}

void RedisClient::setex(const std::string& key, const size_t ttl, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::setex Error!");

    return impl->setex(key, ttl, value);
}

int RedisClient::setnx(const std::string& key, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::setnx Error!");

    return impl->setnx(key, value);
}

size_t RedisClient::setrange(const std::string& key, const size_t offset, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::setrange Error!");

    return impl->setrange(key, offset, value);
}

size_t RedisClient::strlen(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::strlen Error!");

    return impl->strlen(key);
}


// hashs
size_t RedisClient::hdel(const std::string& key, const std::string& field)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hdel Error!");

    return impl->hdel(key, field);
}

size_t RedisClient::hdel(const std::string& key, const std::vector<std::string>& fields)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hdel Error!");

    return impl->hdel(key, fields);
}

size_t RedisClient::hexists(const std::string& key, const std::string& field)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hexists Error!");

    return impl->hexists(key, field);
}

CppRedisClient::StringReply RedisClient::hget(const std::string& key, const std::string& field)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hget Error!");

    return impl->hget(key, field);
}

std::map<std::string, std::string> RedisClient::hgetall(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hgetall Error!");

    return impl->hgetall(key);
}

int RedisClient::hincrby(const std::string& key, const std::string& field, const int amount)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hincrby Error!");

    return impl->hincrby(key, field, amount);
}

std::string RedisClient::hincrbyfloat(const std::string& key, const std::string& field, const float amount)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hincrbyfloat Error!");

    return impl->hincrbyfloat(key, field, amount);
}

std::vector<std::string> RedisClient::hkeys(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hkeys Error!");

    return impl->hkeys(key);
}

size_t RedisClient::hlen(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hlen Error!");
    
    return impl->hlen(key);
}

CppRedisClient::StringReply RedisClient::hmget(const std::string& key, const std::string& field)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hmget Error!");

    return impl->hmget(key, field);
}

void RedisClient::hmset(const std::string& key, const std::string& field, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hmset Error!");

    return impl->hmset(key, field, value);
}

void RedisClient::hmset(const std::string& key, const std::map<std::string, std::string>& fvMap)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hmset Error!");

    return impl->hmset(key, fvMap);
}

size_t RedisClient::hset(const std::string& key, const std::string& field, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hset Error!");

    return impl->hset(key, field, value);
}

size_t RedisClient::hsetnx(const std::string& key, const std::string& field, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hsetnx Error!");

    return impl->hsetnx(key, field, value);
}

std::vector<std::string> RedisClient::hvals(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hvals Error!");

    return impl->hvals(key);
}


// lists
CppRedisClient::StringReply RedisClient::lindex(const std::string& key, const int index)
{
    if (!impl)
        throw std::runtime_error("RedisClient::lindex Error!");

    return impl->lindex(key, index);
}

int RedisClient::linsert(const std::string& key, const int flag, const std::string& pivot, 
        const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::linsert Error!");

    return 0;
    // return impl->linsert(key, flag, pivot, value);
}

size_t RedisClient::llen(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::llen Error!");

    return impl->llen(key);
}

CppRedisClient::StringReply RedisClient::lpop(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::lpop Error!");

    return impl->lpop(key);
}

size_t RedisClient::lpush(const std::string& key, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::lpush Error!");

    return impl->lpush(key, value);
}

size_t RedisClient::lpush(const std::string& key, const std::vector<std::string>& values)
{
    if (!impl)
        throw std::runtime_error("RedisClient::lpush Error!");

    return impl->lpush(key, values);
}

size_t RedisClient::lpushx(const std::string& key, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::lpushx Error!");

    return impl->lpushx(key, value);
}


std::vector<std::string> RedisClient::lrange(const std::string& key, const int start, const int stop)
{
    if (!impl)
        throw std::runtime_error("RedisClient::lrange Error!");

    return impl->lrange(key, start, stop);
}

size_t RedisClient::lrem(const std::string& key, const int count, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::lrem Error!");

    return impl->lrem(key, count, value);
}

void RedisClient::lset(const std::string& key, const int index, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::lset Error!");

    return impl->lset(key, index, value);
}

void RedisClient::ltrim(const std::string& key, const int start, const int stop)
{
    if (!impl)
        throw std::runtime_error("RedisClient::ltrim Error!");

    return impl->ltrim(key, start, stop);
}

CppRedisClient::StringReply RedisClient::rpop(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::rpop Error!");

    return impl->rpop(key);
}

CppRedisClient::StringReply RedisClient::rpoplpush(const std::string& srcKey, const std::string& dstKey)
{
    if (!impl)
        throw std::runtime_error("RedisClient::rpoplpush Error!");

    return impl->rpoplpush(srcKey, dstKey);
}

size_t RedisClient::rpush(const std::string& key, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::rpush Error!");

    return impl->rpush(key, value);
}

size_t RedisClient::rpush(const std::string& key, const std::vector<std::string>& values)
{
    if (!impl)
        throw std::runtime_error("RedisClient::rpush Error!");

    return impl->rpush(key, values);
}

size_t RedisClient::rpushx(const std::string& key, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::rpushx Error!");

    return impl->rpushx(key, value);
}


// sets
size_t RedisClient::sadd(const std::string& key, const std::string& member)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sadd Error!");

    return impl->sadd(key, member);
}

size_t RedisClient::sadd(const std::string& key, const std::vector<std::string>& members)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sadd Error!");

    return impl->sadd(key, members);
}

size_t RedisClient::sadd(const std::string& key, const std::set<std::string>& members)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sadd Error!");

    return impl->sadd(key, members);
}

size_t RedisClient::scard(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::scard Error!");

    return impl->scard(key);
}

std::string RedisClient::sdiff(const std::string& key1, const std::string& key2)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sdiff Error!");

    return impl->sdiff(key1, key2);
}

std::vector<std::string> RedisClient::sdiff(const std::string& key, const std::vector<std::string>& keys)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sdiff Error!");

    return impl->sdiff(key, keys);
}

size_t RedisClient::sdiffstore(const std::string& dstKey, const std::string& key1, const std::string& key2)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sdiffstore Error!");

    return impl->sdiffstore(dstKey, key1, key2);
}

size_t RedisClient::sdiffstore(const std::string& dstKey, const std::string& key,
        const std::vector<std::string>& keys)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sdiffstore Error!");

    return impl->sdiffstore(dstKey, key, keys);
}

std::string RedisClient::sinter(const std::string& key1, const std::string& key2)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sinter Error!");

    return impl->sinter(key1, key2);
}

std::vector<std::string> RedisClient::sinter(const std::string& key, const std::vector<std::string>& keys)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sinter Error!");

    return impl->sinter(key, keys);
}

size_t RedisClient::sinterstore(const std::string& dstKey, const std::string& key1, const std::string& key2)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sinterstore Error!");

    return impl->sinterstore(dstKey, key1, key2);
}

size_t RedisClient::sinterstore(const std::string& dstKey, const std::string& key, 
        const std::vector<std::string>& keys)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sinterstore Error!");

    return impl->sinterstore(dstKey, key, keys);
}

int RedisClient::sismember(const std::string& key, const std::string& member)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sismember Error!");

    return impl->sismember(key, member);
}

std::vector<std::string> RedisClient::smembers(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::smembers Error!");

    return impl->smembers(key);
}

int RedisClient::smove(const std::string& sourceKey, const std::string& dstKey, const std::string& member)
{
    if (!impl)
        throw std::runtime_error("RedisClient::smove Error!");

    return impl->smove(sourceKey, dstKey, member);
}

CppRedisClient::StringReply RedisClient::spop(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::spop Error!");

    return impl->spop(key);
}

CppRedisClient::StringReply RedisClient::srandmember(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::srandmember Error!");

    return impl->srandmember(key);
}

std::vector<std::string> RedisClient::srandmember(const std::string& key, const int count)
{
    if (!impl)
        throw std::runtime_error("RedisClient::srandmember Error!");

    return impl->srandmember(key, count);
}

size_t RedisClient::srem(const std::string& key, const std::string& member)
{
    if (!impl)
        throw std::runtime_error("RedisClient::srem Error!");

    return impl->srem(key, member);
}

size_t RedisClient::srem(const std::string& key, const std::vector<std::string>& members)
{
    if (!impl)
        throw std::runtime_error("RedisClient::srem Error!");

    return impl->srem(key, members);
}

size_t RedisClient::srem(const std::string& key, const std::set<std::string>& members)
{
    if (!impl)
        throw std::runtime_error("RedisClient::srem Error!");

    return impl->srem(key, members);
}

std::string RedisClient::sunion(const std::string& key1, const std::string& key2)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sunion Error!");

    return impl->sunion(key1, key2);
}

std::vector<std::string> RedisClient::sunion(const std::string& key, const std::vector<std::string>& keys)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sunion Error!");

    return impl->sunion(key, keys);
}

size_t RedisClient::sunionstore(const std::string& dstKey, const std::string& key1, const std::string& key2)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sunionstore Error!");

    return impl->sunionstore(dstKey, key1, key2);
}

size_t RedisClient::sunionstore(const std::string& dstKey, const std::string& key, 
        const std::vector<std::string>& keys)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sunionstore Error!");

    return impl->sunionstore(dstKey, key, keys);
}

// sorted sets
size_t RedisClient::zadd(const std::string& key, const int score, const std::string& member)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zadd Error!");

    return 0;
    // return impl->sadd(key, score, member);
}

size_t RedisClient::zcard(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zcard Error!");

    return impl->scard(key);
}

size_t RedisClient::zcount(const std::string& key, const int min, const int max)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zcount Error!");

    return impl->zcount(key, min, max);
}

std::string RedisClient::zincrby(const std::string& key, const int increment, const std::string& member)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zincrby Error!");

    return impl->zincrby(key, increment, member);
}

std::vector<std::string> RedisClient::zrange(const std::string& key, const int start, const int stop)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zrange Error!");

    return impl->zrange(key, start, stop);
}

std::vector<std::string> RedisClient::zrangebyscore(const std::string& key, const int min, const int max)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zrangebyscore Error!");

    return impl->zrangebyscore(key, min, max);
}

CppRedisClient::StringReply RedisClient::zrank(const std::string& key, const std::string& member)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zrank Error!");

    return impl->zrank(key, member);
}

size_t RedisClient::zrem(const std::string& key, const std::string& member)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zrem Error!");

    return impl->zrem(key, member);
}

size_t RedisClient::zrem(const std::string& key, const std::vector<std::string>& members)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zrem Error!");

    return impl->zrem(key, members);
}

size_t RedisClient::zremrangebyrank(const std::string& key, const int start, const int stop)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zremrangebyrank Error!");

    return impl->zremrangebyrank(key, start, stop);
}

size_t RedisClient::zremrangebyscore(const std::string& key, const int min, const int max)
{
    if (impl)
        throw std::runtime_error("RedisClient::zremrangebyscore Error!");

    return impl->zremrangebyscore(key, min, max);
}

std::vector<std::string> RedisClient::zrevrange(const std::string& key, const int start, const int stop)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zrevrange Error!");

    return impl->zrevrange(key, start, stop);
}

std::vector<std::string> RedisClient::zrevrangebyscore(const std::string& key, const int max, const int min)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zrevrangebyscore Error!");

    return impl->zrevrangebyscore(key, max, min);
}

CppRedisClient::StringReply RedisClient::zrevrank(const std::string& key, const std::string& member)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zrevrank Error!");

    return impl->zrevrank(key, member);
}

CppRedisClient::StringReply RedisClient::zscore(const std::string& key, const std::string& member)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zscore Error!");

    return impl->zscore(key, member);
}

}

int test_main()
{
    CppRedisClient::RedisClient r("localhost");
    {
        CppRedisClient::StringReply re = r.get("f");
        std::cout << "[" << re.getLength() << "]" << re.toString() << std::endl;
        re = r.get("mykey");
        std::cout << "[" << re.getLength() << "]" << re.toString() << std::endl;
        re = r.get("enable");
        try
        {
            std::cout << "[" << re.getLength() << "]" << std::endl;
            std::cout << re.toString() << std::endl;
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
        re = r.get("test");
        std::cout << "[" << re.getLength() << "]" << re.toString() << std::endl;
    }
    // return 0;
    // CppRedisClient::RedisClient redis_obj1;
    CppRedisClient::RedisClient redis_obj2("localhost");
    // redis_obj2.set("f", "c");
    // redis_obj2.set("c", "f");
    // std::cout << redis_obj2.get("b") << std::endl;
    // redis_obj2.setex("ttl_test", 60, "value");
    // redis_obj2.append("ttl_test", "_key");
    // redis_obj2.pexpire("ttl_test", 60 * 60 * 1000);
    std::string str1("ssss"\
            "ttt");
    std::string key = "f";
    // std::string response = redis_obj2.get(key);
    // std::cout << key << " : " << response << std::endl;
    // response = redis_obj2.get("b");
    // std::cout << "b : " << response << std::endl;
    // response = redis_obj2.get("sfsdsdfs");
    // std::cout << "sfsdsdfs : " << response << std::endl;
    // std::cout << "mykey : " << redis_obj2.get("mykey") << std::endl;
    // std::cout << "c : " << redis_obj2.get("c") << std::endl;
    // std::cout << redis_obj2.append("f", "c") << std::endl;
    redis_obj2.setex("xx", 60, "yy");
    redis_obj2.set("yy", "xx");
    int num = redis_obj2.pexpire("yyy", 60 * 1000);
    std::cout << num << std::endl;
    num = redis_obj2.expire("yy", 60);
    std::cout << num << std::endl;
    // std::cout << redis_obj2.persist("yy") << std::endl;
    std::cout << redis_obj2.getbit("f", 1) << std::endl;
    std::cout << redis_obj2.getbit("f", 3) << std::endl;
    std::cout << redis_obj2.incr("num") << std::endl;
    std::cout << redis_obj2.incrby("num", 2) << std::endl;
    std::cout << redis_obj2.decr("num") << std::endl;
    std::cout << redis_obj2.decrby("num", -2) << std::endl;
    // std::cout << redis_obj2.setnx("ffff", "test") << std::endl;
    // std::cout << redis_obj2.setnx("ffff", "1") << std::endl;
    std::cout << redis_obj2.ttl("yy") << std::endl;
    std::cout << redis_obj2.ttl("yyyy") << std::endl;
    std::cout << redis_obj2.ttl("num") << std::endl;
    std::cout << redis_obj2.pttl("yy") << std::endl;
    std::cout << redis_obj2.pttl("yyyy") << std::endl;
    std::cout << redis_obj2.pttl("num") << std::endl;
    std::cout << redis_obj2.strlen("f") << std::endl;
    std::cout << redis_obj2.getrange("f", 1, 6) << std::endl;
    std::cout << redis_obj2.getrange("f", 13, -1) << std::endl;
    try 
    {
        redis_obj2.incr("f");
    } 
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    std::cout << redis_obj2.ping() << std::endl;
    // std::cout << redis_obj2.get("f") << std::endl;
    // redis_obj2.get("mykey");
    // redis_obj2.get("b");
    // std::cout << redis_obj2.get("ff") << std::endl;
    std::string test("sfdskhtuiw\r\narfstfsfsa");
    // std::cin >> test;
    return 0;
}
