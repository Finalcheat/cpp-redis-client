#include "../src/cpp_redis_client.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

CppRedisClient::RedisClient redisObj("localhost");


std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& v)
{
    for (std::vector<std::string>::const_iterator it = v.begin(); it != v.end(); ++it)
    {
        os << *it << std::endl;
    }
    return os;
}


std::ostream& operator<<(std::ostream& os, const std::map<std::string, std::string>& m)
{
    for (std::map<std::string, std::string>::const_iterator it = m.begin(); it != m.end(); ++it)
    {
        os << it->first << " -> " << it->second << std::endl;
    }
    return os;
}


// http://redis.io/commands/hdel
void hdel_example()
{
    const std::string key = "hdel_example_key";
    const std::string field1 = "hdel_example_key_field1";
    const std::string field2 = "hdel_example_key_field2";

    redisObj.hset(key, field1, "foo");
    std::cout << "hset " << key << " " << field1 << " foo" << std::endl;

    size_t num = redisObj.hdel(key, field1); 
    std::cout << "hdel " << key << " " << field1 << std::endl;
    std::cout << num << std::endl;
    num = redisObj.hdel(key, field2);
    std::cout << "hdel " << key << " " << field2 << std::endl;
    std::cout << num << std::endl;

    redisObj.del(key);
}

// http://redis.io/commands/hexists
void hexists_example()
{
    const std::string key = "hexists_example_key";
    const std::string field1 = "hexists_example_key_field1";
    const std::string field2 = "hexists_example_key_field2";

    redisObj.hset(key, field1, "foo");
    std::cout << "hset " << key << " " << field1 << " foo" << std::endl;

    size_t e = redisObj.hexists(key, field1);
    std::cout << "hexists " << key << " " << field1 << std::endl;
    std::cout << e << std::endl;

    e = redisObj.hexists(key, field2);
    std::cout << "hexists " << key << " " << field2 << std::endl;
    std::cout << e << std::endl;

    redisObj.del(key);
}

// http://redis.io/commands/hget
void hget_example()
{
    const std::string key = "hget_example_key";
    const std::string field1 = "hget_example_key_field1";
    const std::string field2 = "hget_example_key_field2";

    redisObj.hset(key, field1, "foo");
    std::cout << "hset " << key << " " << field1 << " foo" << std::endl;

    CppRedisClient::StringReply reply = redisObj.hget(key, field1);
    std::cout << "hget " << key << " " << field1 << std::endl;
    std::cout << reply << std::endl;

    reply = redisObj.hget(key, field2);
    std::cout << "hget " << key << " " << field2 << std::endl;
    std::cout << reply << std::endl;

    redisObj.del(key);
}

// http://redis.io/commands/hgetall
void hgetall_example()
{
    const std::string key = "hgetall_example_key";
    const std::string field1 = "hgetall_example_key_field1";
    const std::string field2 = "hgetall_example_key_field2";

    redisObj.hset(key, field1, "Hello");
    std::cout << "hset " << key << " " << field1 << " Hello" << std::endl;
    redisObj.hset(key, field2, "World");
    std::cout << "hset " << key << " " << field2 << " World" << std::endl;

    std::map<std::string, std::string> fvMap = redisObj.hgetall(key);
    std::cout << "hgetall " << key << std::endl;
    std::cout << fvMap;

    redisObj.del(key);
}

// http://redis.io/commands/hincrby
void hincrby_example()
{
    const std::string key = "hincrby_example_key";
    const std::string field = "hincrby_example_key_field";

    redisObj.hset(key, field, "5");
    std::cout << "hset " << key << " " << field << " 5" << std::endl;

    int num = redisObj.hincrby(key, field, 1);
    std::cout << "hincrby " << key << " " << field << " 1" << std::endl;
    std::cout << num << std::endl;

    num = redisObj.hincrby(key, field, -1);
    std::cout << "hincrby " << key << " " << field << " -1" << std::endl;
    std::cout << num << std::endl;

    num = redisObj.hincrby(key, field, -10);
    std::cout << "hincrby " << key << " " << field << " 10" << std::endl;
    std::cout << num << std::endl;

    redisObj.del(key);
}

// http://redis.io/commands/hkeys
void hkey_example()
{
    const std::string key = "hkey_example_key";
    const std::string field1 = "hkey_example_key_field1";
    const std::string field2 = "hkey_example_key_field2";

    redisObj.hset(key, field1, "Hello");
    std::cout << "hset " << key << " " << field1 << " Hello" << std::endl;
    redisObj.hset(key, field2, "World");
    std::cout << "hset " << key << " " << field2 << " World" << std::endl;

    std::vector<std::string> replys = redisObj.hkeys(key);
    std::cout << "hkeys " << key << std::endl;
    std::cout << replys;

    redisObj.del(key);
}

// http://redis.io/commands/hlen
void hlen_example()
{
    const std::string key = "hlen_example_key";
    const std::string field1 = "hlen_example_key_field1";
    const std::string field2 = "hlen_example_key_field2";

    redisObj.hset(key, field1, "Hello");
    std::cout << "hset " << key << " " << field1 << " Hello" << std::endl;
    redisObj.hset(key, field2, "World");
    std::cout << "hset " << key << " " << field2 << " World" << std::endl;

    const size_t len = redisObj.hlen(key);
    std::cout << "hlen " << key << std::endl;
    std::cout << len << std::endl;

    redisObj.del(key);
}

// http://redis.io/commands/hmget
void hmget_example()
{
    const std::string key = "hmget_example_key";
    const std::string field1 = "hmget_example_key_field1";
    const std::string field2 = "hmget_example_key_field2";
    const std::string field3 = "hmget_example_key_field3";
    std::vector<std::string> fields;
    fields.push_back(field1);
    fields.push_back(field2);
    fields.push_back(field3);

    redisObj.hset(key, field1, "Hello");
    std::cout << "hset " << key << " " << field1 << " Hello" << std::endl;
    redisObj.hset(key, field2, "World");
    std::cout << "hset " << key << " " << field2 << " World" << std::endl;

    std::vector<CppRedisClient::StringReply> replys = redisObj.hmget(key, fields);
    std::cout << "hmget ";
    for (std::vector<std::string>::const_iterator it = fields.begin(); it != fields.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    for (std::vector<CppRedisClient::StringReply>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    redisObj.del(key);
}

// http://redis.io/commands/hmset
void hmset_example()
{
    const std::string key = "hmset_example_key";
    const std::string field1 = "hmset_example_key_field1";
    const std::string field2 = "hmset_example_key_field2";
    std::map<std::string, std::string> fvMap;
    fvMap[field1] = "Hello";
    fvMap[field2] = "World";
    std::vector<std::string> fields;

    redisObj.hmset(key, fvMap);
    std::cout << "hmset " << key << " ";
    for (std::map<std::string, std::string>::const_iterator it = fvMap.begin(); it != fvMap.end(); ++it)
    {
        std::cout << it->first << " " << it->second << " ";
        fields.push_back(it->first);
    }
    std::cout << std::endl;

    std::vector<CppRedisClient::StringReply> replys = redisObj.hmget(key, fields);
    std::cout << "hmget ";
    for (std::vector<std::string>::const_iterator it = fields.begin(); it != fields.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    for (std::vector<CppRedisClient::StringReply>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    redisObj.del(key);
}

// http://redis.io/commands/hset
void hset_example()
{
    const std::string key = "hset_example_key";
    const std::string field = "hset_example_key_field";

    const size_t s = redisObj.hset(key, field, "Hello");
    std::cout << "hset " << key << " " << field << " Hello" << std::endl;
    std::cout << s << std::endl;

    CppRedisClient::StringReply reply = redisObj.hget(key, field);
    std::cout << "hget " << key << " " << field << std::endl;
    std::cout << reply << std::endl;

    redisObj.del(key);
}

// http://redis.io/commands/hsetnx
void hsetnx_example()
{
    const std::string key = "hsetnx_example_key";
    const std::string field = "hsetnx_example_key_field";

    size_t s = redisObj.hsetnx(key, field, "Hello");
    std::cout << "hsetnx " << key << " " << field << " Hello" << std::endl;
    std::cout << s << std::endl;

    s = redisObj.hsetnx(key, field, "World");
    std::cout << "hsetnx " << key << " " << field << " World" << std::endl;
    std::cout << s << std::endl;

    CppRedisClient::StringReply reply = redisObj.hget(key, field);
    std::cout << "hget " << key << " " << field << std::endl;
    std::cout << reply << std::endl;

    redisObj.del(key);
}

// http://redis.io/commands/hstrlen
// version 3.2.0
/*
void hstrlen_example()
{
    const std::string key = "hstrlen_example_key";
    std::map<std::string, std::string> fvMap;
    fvMap["f1"] = "HelloWorld";
    fvMap["f2"] = "99";
    fvMap["f3"] = "-256";

    redisObj.hmset(key, fvMap);
    std::cout << "hmset " << key << " ";
    for (std::map<std::string, std::string>::const_iterator it = fvMap.begin(); it != fvMap.end(); ++it)
    {
        std::cout << it->first << " " << it->second << " ";
    }
    std::cout << std::endl;
}
*/

// http://redis.io/commands/hvals
void hvals_example()
{
    const std::string key = "hvals_example_key";

    redisObj.hset(key, "hvals_example_key_field1", "Hello");
    std::cout << "hset " << key << " hvals_example_key_field1 Hello" << std::endl;
    redisObj.hset(key, "hvals_example_key_field2", "World");
    std::cout << "hset " << key << " hvals_example_key_field2 World" << std::endl;

    std::vector<std::string> replys = redisObj.hvals(key);
    std::cout << "hvals " << key << std::endl;
    std::cout << replys;

    redisObj.del(key);
}


int main()
{
    typedef void (*ptFn)();
    std::vector<ptFn> fns;
    fns.push_back(hdel_example);
    fns.push_back(hexists_example);
    fns.push_back(hget_example);
    fns.push_back(hgetall_example);
    fns.push_back(hincrby_example);
    fns.push_back(hkey_example);
    fns.push_back(hlen_example);
    fns.push_back(hmget_example);
    fns.push_back(hmset_example);
    fns.push_back(hset_example);
    fns.push_back(hsetnx_example);
    // fns.push_back(hstrlen_example);
    fns.push_back(hvals_example);

    for (std::vector<ptFn>::const_iterator it = fns.begin(); it != fns.end(); ++it)
    {
        std::cout << "-------------------------------------------" << std::endl;
        (*it)();
        std::cout << "-------------------------------------------" << std::endl;
    }

    return 0;
}
