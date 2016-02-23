#include "../src/cpp_redis_client.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

const std::string line = "--------------------------------------------";

// 创建Redis连接
CppRedisClient::RedisClient redisObj("localhost");

// http://redis.io/commands/append
void append_example()
{
    std::cout << "append_example" << std::endl;
    std::cout << line << std::endl;
    // key
    const std::string key = "append_example_key";

    // 删除掉key
    redisObj.del(key);

    // append字符串连接，返回连接后字符串长度
    size_t len = redisObj.append(key, "Hello");
    // len = 5
    std::cout << "append \"Hello\", len is " << len << std::endl;

    len = redisObj.append(key, " World");
    // len = 11
    std::cout << "append \" World\", len is " << len << std::endl;

    CppRedisClient::StringReply reply = redisObj.get(key);
    std::cout << "value is " << reply << std::endl;

    redisObj.del(key);

    std::cout << line << std::endl;
}

// http://redis.io/commands/bitcount
void bitcount_example()
{
    std::cout << "bitcount_example" << std::endl;
    std::cout << line << std::endl;

    const std::string key = "bitcount_example_key";
    redisObj.del(key);
    redisObj.set(key, "foobar");

    std::cout << "set " << key << " foobar" << std::endl;

    size_t num = redisObj.bitcount(key);
    std::cout << num << std::endl;
    num = redisObj.bitcount(key, 0, 0);
    std::cout << num << std::endl;
    num = redisObj.bitcount(key, 1, 1);
    std::cout << num << std::endl;

    redisObj.del(key);
    std::cout << line << std::endl;
}

// http://redis.io/commands/decr
void decr_example()
{
    std::cout << "decr_example" << std::endl;
    std::cout << line << std::endl;

    const std::string key = "decr_example_key";
    redisObj.del(key);

    redisObj.set(key, "10");
    std::cout << "set " << key << " 10" << std::endl;

    int num = redisObj.decr(key);
    std::cout << "decr" << std::endl;
    std::cout << "num is " << num << std::endl;

    redisObj.set(key, "234293482390480948029348230948");
    try
    {
        num = redisObj.decr(key);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    redisObj.del(key);

    std::cout << line << std::endl;
}

// http://redis.io/commands/decrby
void decrby_example()
{
    std::cout << "decrby_example" << std::endl;
    std::cout << line << std::endl;

    const std::string key = "decrby_example_key";
    redisObj.del(key);

    redisObj.set(key, "10");
    std::cout << "set " << key << " 10" << std::endl;
    int num = redisObj.decrby(key, 3);
    std::cout << "decrby 3" << std::endl;
    std::cout << num << std::endl;

    redisObj.del(key);

    std::cout << line << std::endl;
}

// http://redis.io/commands/get
void get_example()
{
    std::cout << "get_example" << std::endl;
    std::cout << line << std::endl;

    const std::string key = "get_example_key";
    redisObj.del(key);

    CppRedisClient::StringReply reply = redisObj.get(key);
    if (reply.isNull())
    {
        std::cout << "get " << key << " is NULL" << std::endl;
    }
    
    redisObj.set(key, "Hello");
    std::cout << "set " << key << " Hello" << std::endl;
    reply = redisObj.get(key);
    std::cout << "get " << key << " is " << reply << std::endl;

    redisObj.del(key);

    std::cout << line << std::endl; 
}

// http://redis.io/commands/getbit
void getbit_example()
{
    std::cout << "getbit_example" << std::endl;
    std::cout << line << std::endl;

    const std::string key = "getbit_example_key";
    redisObj.del(key);

    redisObj.setbit(key, 7, 1);
    std::cout << "setbit " << key << " 7 1" << std::endl;

    size_t bit = redisObj.getbit(key, 0);
    std::cout << "getbit " << key << " 0 is " << bit << std::endl;
    bit = redisObj.getbit(key, 7);
    std::cout << "getbit " << key << " 7 is " << bit << std::endl;
    bit = redisObj.getbit(key, 100);
    std::cout << "getbit " << key << " 100 is " << bit << std::endl;

    redisObj.del(key);

    std::cout << line << std::endl; 
}

// http://redis.io/commands/getrange
void getrange_example()
{
    std::cout << "getrange_example" << std::endl;
    std::cout << line << std::endl;

    const std::string key = "getrange_example_key";
    const std::string value = "This is a string";
    redisObj.del(key);
    redisObj.set(key, value);
    std::cout << "set " << key << " " << value << std::endl;

    std::string rangeValue = redisObj.getrange(key, 0, 3);
    std::cout << "getrange " << key << " 0 3 is " << rangeValue << std::endl;
    rangeValue = redisObj.getrange(key, -3, -1);
    std::cout << "getrange " << key << " -3 -1 is " << rangeValue << std::endl;
    rangeValue = redisObj.getrange(key, 0, -1);
    std::cout << "getrange " << key << " 0 -1 is " << rangeValue << std::endl;
    rangeValue = redisObj.getrange(key, 10, 100);
    std::cout << "getrange " << key << " 10 100 is " << rangeValue << std::endl;

    redisObj.del(key);

    std::cout << line << std::endl; 
}

// http://redis.io/commands/getset
void getset_example()
{
    std::cout << "getset_example" << std::endl;
    std::cout << line << std::endl;

    const std::string key = "getset_example_key";
    redisObj.del(key);
    redisObj.incr(key);
    std::cout << "incr " << key << std::endl;

    CppRedisClient::StringReply value = redisObj.getset(key, "0");
    std::cout << "old value is " << value << std::endl;
    value = redisObj.get(key);
    std::cout << "new value is " << value << std::endl;

    redisObj.del(key);

    std::cout << line << std::endl; 
}

// http://redis.io/commands/incr
void incr_example()
{
    std::cout << "incr_example" << std::endl;
    std::cout << line << std::endl;

    const std::string key = "incr_example_key";
    redisObj.del(key);

    redisObj.set(key, "10");
    std::cout << "set " << key << " 10" << std::endl;
    const int num = redisObj.incr(key);
    std::cout << "incr " << key << std::endl;
    std::cout << "num is " << num << std::endl;
    std::string value = redisObj.get(key).toString();
    std::cout << "get " << key << " is " << value << std::endl;

    redisObj.del(key);

    std::cout << line << std::endl;
}

// http://redis.io/commands/incrby
void incrby_example()
{
    std::cout << "incrby_example" << std::endl;
    std::cout << line << std::endl;

    const std::string key = "incrby_example_key";
    redisObj.del(key);

    redisObj.set(key, "10");
    std::cout << "set " << key << " 10" << std::endl;
    int num = redisObj.incrby(key, 5);
    std::cout << "incrby " << key << " 5" << std::endl;
    std::cout << "num is " << num << std::endl;

    redisObj.del(key);

    std::cout << line << std::endl; 
}

// http://redis.io/commands/mget
void mget_example()
{
    std::cout << "mget_example" << std::endl;
    std::cout << line << std::endl;

    const std::string key1 = "mget_example_key1";
    const std::string key2 = "mget_example_key2";
    const std::string key3 = "mget_example_key3";
    std::vector<std::string> keys;
    keys.push_back(key1);
    keys.push_back(key2);
    keys.push_back(key3);
    for (size_t i = 0; i != keys.size(); ++i)
    {
        redisObj.del(keys[i]);
    }

    redisObj.set(key1, "Hello");
    redisObj.set(key2, "World");
    std::cout << "set " << key1 << " Hello" << std::endl;
    std::cout << "set " << key2 << " World" << std::endl;

    std::vector<CppRedisClient::StringReply> replys = redisObj.mget(keys);
    std::cout << "mget:" << std::endl;
    for (std::vector<CppRedisClient::StringReply>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    for (size_t i = 0; i != keys.size(); ++i)
    {
        redisObj.del(keys[i]);
    }

    std::cout << line << std::endl;
}

// http://redis.io/commands/mset
void mset_example()
{
    std::cout << "mset_example" << std::endl;
    std::cout << line << std::endl;

    const std::string key1 = "mset_example_key1";
    const std::string key2 = "mset_example_key2";
    std::map<std::string, std::string> kvMap;
    kvMap[key1] = "Hello";
    kvMap[key2] = "World";
    std::cout << "mset:" << std::endl;
    for (std::map<std::string, std::string>::const_iterator it = kvMap.begin(); it != kvMap.end(); ++it)
    {
        redisObj.del(it->first);
        std::cout << it->first << " -> " << it->second << std::endl;
    }
    redisObj.mset(kvMap);

    CppRedisClient::StringReply reply = redisObj.get(key1);
    std::cout << "get " << key1 << " is " << reply << std::endl;
    reply = redisObj.get(key2);
    std::cout << "get " << key2 << " is " << reply << std::endl;

    for (std::map<std::string, std::string>::const_iterator it = kvMap.begin(); it != kvMap.end(); ++it)
    {
        redisObj.del(it->first);
    }

    std::cout << line << std::endl; 
}

// http://redis.io/commands/msetnx
void msetnx_example()
{
    std::cout << "msetnx_example" << std::endl;
    std::cout << line << std::endl;

    const std::string key1 = "msetnx_example_key1";
    const std::string key2 = "msetnx_example_key2";
    const std::string key3 = "msetnx_example_key3";
    redisObj.del(key1);
    redisObj.del(key2);
    redisObj.del(key3);
    std::vector<std::string> keys;
    keys.push_back(key1);
    keys.push_back(key2);
    keys.push_back(key3);
    std::map<std::string, std::string> kvMap;
    kvMap[key1] = "Hello";
    kvMap[key2] = "there";
    std::cout << "msetnx:" << std::endl;
    for (std::map<std::string, std::string>::const_iterator it = kvMap.begin(); it != kvMap.end(); ++it)
    {
        std::cout << it->first << " -> " << it->second << std::endl;
    }
    redisObj.msetnx(kvMap);

    kvMap.erase(key1);
    kvMap[key3] = "world";
    std::cout << "msetnx:" << std::endl;
    for (std::map<std::string, std::string>::const_iterator it = kvMap.begin(); it != kvMap.end(); ++it)
    {
        std::cout << it->first << " -> " << it->second << std::endl;
    }
    redisObj.msetnx(kvMap);


    std::vector<CppRedisClient::StringReply> replys = redisObj.mget(keys);
    std::cout << "mget:" << std::endl;
    for (std::vector<CppRedisClient::StringReply>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
    {
        redisObj.del(*it);
    }

    std::cout << line << std::endl;
}

// http://redis.io/commands/psetex
void psetex_example()
{
    std::cout << "psetex_example" << std::endl;
    std::cout << line << std::endl;

    const std::string key = "psetex_example_key";
    redisObj.del(key);

    redisObj.psetex(key, 1000, "Hello");
    std::cout << "psetex " << key << " 1000 Hello" << std::endl;
    int64_t ttl = redisObj.pttl(key);
    std::cout << "pttl is " << ttl << std::endl;
    std::cout << redisObj.get(key) << std::endl;

    redisObj.del(key);

    std::cout << line << std::endl;
}

// http://redis.io/commands/set
void set_example()
{
    std::cout << "set_example" << std::endl;
    std::cout << line << std::endl;

    const std::string key = "set_example_key";
    redisObj.del(key);

    redisObj.set(key, "Hello");
    std::cout << "set " << key << " Hello" << std::endl;
    std::cout << "get " << key << " is " << redisObj.get(key) << std::endl;

    redisObj.del(key);

    std::cout << line << std::endl;
}

// http://redis.io/commands/setex
void setex_example()
{
    std::cout << "setex_example" << std::endl;
    std::cout << line << std::endl;

    const std::string key = "setex_example_key";
    redisObj.del(key);

    redisObj.setex(key, 10, "Hello");
    std::cout << "setex " << key << " 10 Hello" << std::endl;
    int ttl = redisObj.ttl(key);
    std::cout << "ttl is " << ttl << std::endl;
    std::cout << "get " << key << " is " << redisObj.get(key) << std::endl;

    redisObj.del(key);

    std::cout << line << std::endl;
}

// http://redis.io/commands/setnx
void setnx_example()
{
    std::cout << "setnx_example" << std::endl;
    std::cout << line << std::endl;
    
    const std::string key = "setnx_example_key";
    redisObj.del(key);

    int value = redisObj.setnx(key, "Hello");
    std::cout << "setnx " << key << " Hello" << std::endl;
    if (value == 1)
        std::cout << "the key was set" << std::endl;

    value = redisObj.setnx(key, "World");
    std::cout << "setnx " << key << " World" << std::endl;
    if (value == 0)
        std::cout << "the key was not set" << std::endl;

    std::cout << "get " << key << " is " << redisObj.get(key) << std::endl;

    redisObj.del(key);

    std::cout << line << std::endl;
}

// http://redis.io/commands/setrange
void setrange_example()
{
    std::cout << "setrange_example" << std::endl;
    std::cout << line << std::endl;

    const std::string key = "setrange_example_key";
    redisObj.del(key);

    redisObj.set(key, "Hello World");
    std::cout << "set " << key << " Hello World" << std::endl;
    const size_t len = redisObj.setrange(key, 6, "Redis");
    std::cout << "setrange " << key << " 6 Redis" << std::endl;
    std::cout << "string length is " << len << std::endl;
    std::cout << "get " << key << " is " << redisObj.get(key) << std::endl;

    redisObj.del(key);
    
    std::cout << line << std::endl;
}

// http://redis.io/commands/strlen
void strlen_example()
{
    std::cout << "strlen_example" << std::endl;
    std::cout << line << std::endl;
    
    const std::string key = "strlen_example_key";
    redisObj.del(key);

    redisObj.set(key, "Hello World");
    std::cout << "set " << key << " Hello World" << std::endl;
    const size_t len = redisObj.strlen(key);
    std::cout << "strlen " << key << " is " << len << std::endl;

    redisObj.del(key);

    std::cout << line << std::endl;
}


int main()
{

    // append
    append_example();

    // bitcount
    bitcount_example();

    // decr
    decr_example();

    // decrby
    decrby_example();

    // get
    get_example();

    // getbit
    getbit_example();

    // getrange
    getrange_example();

    // getset
    getset_example();

    // incr
    incr_example();

    // incrby
    incrby_example();

    // mget
    mget_example();

    // mset
    mset_example();

    // msetnx
    msetnx_example();

    // psetex
    psetex_example();

    // set
    set_example();

    // setex
    setex_example();

    // setnx
    setnx_example();

    // setrange
    setrange_example();

    // strlen
    strlen_example();

    return 0;
}
