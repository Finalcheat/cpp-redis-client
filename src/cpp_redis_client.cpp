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

void RedisClient::set(const std::string& key, const std::string& value)
{
    if (impl)
    {
        impl->set(key, value);
    }
}

void RedisClient::setex(const std::string& key, const size_t ttl, const std::string& value)
{
    if (impl)
    {
        impl->setex(key, ttl, value);
    }
}

int RedisClient::setnx(const std::string& key, const std::string& value)
{
    if (impl)
    {
        return impl->setnx(key, value);
    }
    return 0;
}


CppRedisClient::StringReply RedisClient::get(const std::string& key)
{
    if (impl)
    {
        return impl->get(key);
    }
    return CppRedisClient::StringReply(boost::shared_ptr<char>(), -1);
}

const size_t RedisClient::append(const std::string& key, const std::string& value)
{
    if (impl)
    {
        return impl->append(key, value);
    }

    return 0;
}

int RedisClient::pexpire(const std::string& key, const size_t milliseconds)
{
    if (impl)
    {
        return impl->pexpire(key, milliseconds);
    }
    return 0;
}

int RedisClient::expire(const std::string& key, const size_t seconds)
{
    if (impl)
    {
        return impl->expire(key, seconds);
    }
    return 0;
}

size_t RedisClient::getbit(const std::string& key, const size_t offset)
{
    if (impl)
    {
        return impl->getbit(key, offset);
    }
    return 0;
}

int RedisClient::incr(const std::string& key)
{
    if (impl)
    {
        return impl->incr(key);
    }
    return 0;
}

std::string RedisClient::getrange(const std::string& key, const int start, const int end)
{
    if (impl)
    {
        return impl->getrange(key, start, end);
    }
    return "";
}

int RedisClient::incrby(const std::string& key, const int amount)
{
    if (impl)
    {
        return impl->incrby(key, amount);
    }
    return 0;
}

int RedisClient::decr(const std::string& key)
{
    if (impl)
    {
        return impl->decr(key);
    }
    return 0;
}

int RedisClient::decrby(const std::string& key, const int amount)
{
    if (impl)
    {
        return impl->decrby(key, amount);
    }
    return 0;
}

size_t RedisClient::strlen(const std::string& key)
{
    if (impl)
    {
        return impl->strlen(key);
    }
    return 0;
}

int RedisClient::ttl(const std::string& key)
{
    if (impl)
    {
        return impl->ttl(key);
    }
    return 0;
}

int RedisClient::pttl(const std::string& key)
{
    if (impl)
    {
        return impl->pttl(key);
    }
    return 0;
}

std::string RedisClient::getset(const std::string& key, const std::string& value)
{
    if (impl)
    {
        return impl->getset(key, value);
    }
    return "";
}


bool RedisClient::ping()
{
    if (impl)
    {
        return impl->ping();
    }

    return false;
}

int RedisClient::persist(const std::string& key)
{
    if (impl)
    {
        return impl->persist(key);
    }
    return 0;
}

void RedisClient::rename(const std::string& srcKey, const std::string& dstKey)
{
    if (impl)
    {
        impl->rename(srcKey, dstKey);
    }
}

int RedisClient::renamenx(const std::string& srcKey, const std::string& dstKey)
{
    if (impl)
    {
        return impl->renamenx(srcKey, dstKey);
    }
    return 0;
}

size_t RedisClient::llen(const std::string& key)
{
    if (impl)
    {
        return impl->llen(key);
    }
    return 0;
}

int RedisClient::move(const std::string& key, const size_t db)
{
    if (impl)
    {
        return impl->move(key, db);
    }
    return 0;
}

int RedisClient::exists(const std::string& key)
{
    if (impl)
    {
        return impl->exists(key);
    }
    return 0;
}


size_t RedisClient::bitcount(const std::string& key, const int start, const int end)
{
    if (impl)
    {
        return impl->bitcount(key, start, end);
    }
    return 0;
}


size_t RedisClient::del(const std::string& key)
{
    if (impl)
    {
        return impl->del(key);
    }
    return 0;
}


size_t RedisClient::setbit(const std::string& key, const size_t offset, const size_t value)
{
    if (impl)
    {
        return impl->setbit(key, offset, value);
    }
    return 0;
}


void RedisClient::psetex(const std::string& key, const size_t milliseconds, const std::string& value)
{
    if (impl)
    {
        impl->psetex(key, milliseconds, value);
    }
}

size_t RedisClient::setrange(const std::string& key, const size_t offset, const std::string& value)
{
    if (impl)
    {
        return impl->setrange(key, offset, value);
    }
    return 0;
}

std::string RedisClient::incrbyfloat(const std::string& key, const float amount)
{
    if (impl)
    {
        return impl->incrbyfloat(key, amount);
    }
    return "";
}

size_t RedisClient::expireat(const std::string& key, const size_t timestamp)
{
    if (impl)
    {
        return impl->expireat(key, timestamp);
    }
    return 0; 
}


CppRedisClient::StringReply RedisClient::dump(const std::string& key)
{
    if (impl)
    {
        return impl->dump(key);
    }
    return CppRedisClient::StringReply(boost::shared_ptr<char>(), -1);
}


int RedisClient::pexpireat(const std::string& key, const size_t millisecondsTimestamp)
{
    if (impl)
    {
        return impl->pexpireat(key, millisecondsTimestamp);
    }
    return 0;
}


CppRedisClient::StringReply RedisClient::randomkey()
{
    if (impl)
    {
        return impl->randomkey();
    }
    return CppRedisClient::StringReply(boost::shared_ptr<char>(), -1);
}


std::vector<CppRedisClient::StringReply> RedisClient::mget(const std::vector<std::string>& keys)
{
    if (impl)
    {
        return impl->mget(keys);
    }
    return std::vector<CppRedisClient::StringReply>();
}

void RedisClient::mset(const std::map<std::string, std::string>& kvMap)
{
    if (impl)
    {
        impl->mset(kvMap);
    }
}

int RedisClient::msetnx(const std::map<std::string, std::string>& kvMap)
{
    if (impl)
    {
        return impl->msetnx(kvMap);
    }
    return 0;
}


size_t RedisClient::hdel(const std::string& key, const std::string& field)
{
    if (impl)
    {
        return impl->hdel(key, field);
    }
    return 0;
}

size_t RedisClient::hdel(const std::string& key, const std::vector<std::string>& fields)
{
    if (impl)
    {
        return impl->hdel(key, fields);
    }
    return 0;
}

size_t RedisClient::hexists(const std::string& key, const std::string& field)
{
    if (impl)
    {
        return impl->hexists(key, field);
    }
    return 0;
}

CppRedisClient::StringReply RedisClient::hget(const std::string& key, const std::string& field)
{
    if (!impl)
        throw std::runtime_error("Error!");

    return impl->hget(key, field);
}

std::map<std::string, std::string> RedisClient::hgetall(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("Error!");

    return impl->hgetall(key);
}

int RedisClient::hincrby(const std::string& key, const std::string& field, const int amount)
{
    if (!impl)
        throw std::runtime_error("Error!");

    return impl->hincrby(key, field, amount);
}

std::string RedisClient::hincrbyfloat(const std::string& key, const std::string& field, const float amount)
{
    if (!impl)
        throw std::runtime_error("Error!");

    return impl->hincrbyfloat(key, field, amount);
}

std::vector<std::string> RedisClient::hkeys(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("Error!");

    return impl->hkeys(key);
}

size_t RedisClient::hlen(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("Error!");
    
    return impl->hlen(key);
}

CppRedisClient::StringReply RedisClient::hmget(const std::string& key, const std::string& field)
{
    if (!impl)
        throw std::runtime_error("Error!");

    return impl->hmget(key, field);
}

void RedisClient::hmset(const std::string& key, const std::string& field, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("Error!");

    return impl->hmset(key, field, value);
}

void RedisClient::hmset(const std::string& key, const std::map<std::string, std::string>& fvMap)
{
    if (!impl)
        throw std::runtime_error("Error!");

    return impl->hmset(key, fvMap);
}

size_t RedisClient::hset(const std::string& key, const std::string& field, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("Error!");

    return impl->hset(key, field, value);
}

size_t RedisClient::hsetnx(const std::string& key, const std::string& field, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("Error!");

    return impl->hsetnx(key, field, value);
}

std::vector<std::string> RedisClient::hvals(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("Error!");

    return impl->hvals(key);
}


// lists
CppRedisClient::StringReply RedisClient::lindex(const std::string& key, const int index)
{
    if (!impl)
        throw std::runtime_error("Error!");

    return impl->lindex(key, index);
}

int RedisClient::linsert(const std::string& key, const int flag, const std::string& pivot, 
        const std::string& value)
{
    if (!impl)
        throw std::runtime_error("Error!");

    return impl->linsert(key, flag, pivot, value);
}

size_t RedisClient::llen(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("Error!");

    return impl->llen(key);
}

CppRedisClient::StringReply RedisClient::lpop(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("Error!");

    return impl->lpop(key);
}

size_t RedisClient::lpush(const std::string& key, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("Error!");

    return impl->lpush(key, value);
}

size_t RedisClient::lpush(const std::string& key, const std::vector<std::string>& values)
{
    if (!impl)
        throw std::runtime_error("Error!");

    return impl->lpush(key, values);
}

size_t RedisClient::lpushx(const std::string& key, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("Error!");

    return impl->lpushx(key, value);
}


std::vector<std::string> RedisClient::lrange(const std::string& key, const int start, const int stop)
{
    if (!impl)
        throw std::runtime_error("Error!");

    return impl->lrange(key, start, stop);
}

size_t RedisClient::lrem(const std::string& key, const int count, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("Error!");

    return impl->lrem(key, count, value);
}

void RedisClient::lset(const std::string& key, const int index, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("Error!");

    return impl->lset(key, index, value);
}

void RedisClient::ltrim(const std::string& key, const int start, const int stop)
{
    if (!impl)
        throw std::runtime_error("Ltrim Error!");

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
