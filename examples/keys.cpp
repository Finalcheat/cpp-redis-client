#include "../src/cpp_redis_client.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

CppRedisClient::RedisClient redisObj("localhost");

// http://redis.io/commands/del
void del_example()
{
    const std::string key1 = "del_example_key1";
    const std::string key2 = "del_example_key2";
    const std::string key3 = "del_example_key3";
    std::vector<std::string> keys;
    keys.push_back(key1);
    keys.push_back(key2);
    keys.push_back(key3);

    redisObj.del(key2);
    std::cout << "del " << key2 << std::endl;
    redisObj.del(keys);
    std::cout << "del ";
    for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// http://redis.io/commands/exists
void exists_example()
{
    const std::string key = "exists_example_key";
    redisObj.set(key, "Hello");
    std::cout << "set " << key << " Hello" << std::endl;
    int e = redisObj.exists(key);
    std::cout << "exists " << key << std::endl;
    std::cout << e << std::endl;

    redisObj.del(key);
}

// http://redis.io/commands/expire
void expire_example()
{
    const std::string key = "expire_example_key";
    redisObj.set(key, "Hello");
    std::cout << "set " << key << " Hello" << std::endl;
    redisObj.expire(key, 10);
    std::cout << "expire " << key << " 10" << std::endl;

    redisObj.del(key);
}

// http://redis.io/commands/expireat
void expireat_example()
{
    const std::string key = "expireat_example_key";
    redisObj.set(key, "Hello");
    std::cout << "set " << key << " Hello" << std::endl;
    // 2018-01-01 00:00:00
    const size_t millisecondsTimestamp = 1514736000;
    redisObj.expireat(key, millisecondsTimestamp);
    std::cout << "expireat " << key << " " << millisecondsTimestamp << std::endl;

    redisObj.del(key);
}

// http://redis.io/commands/keys
void keys_example()
{
    std::map<std::string, std::string> kvMap;
    kvMap["one"] = "1";
    kvMap["two"] = "2";
    kvMap["three"] = "3";
    kvMap["four"] = "4";

    redisObj.mset(kvMap);
    std::cout << "mset ";
    for (std::map<std::string, std::string>::const_iterator it = kvMap.begin(); it != kvMap.end(); ++it)
    {
        std::cout << it->first << " " << it->second << " ";
    }
    std::cout << std::endl;

    std::string pattern = "*o*";
    std::vector<std::string> keys = redisObj.keys(pattern);
    std::cout << "keys " << pattern << std::endl;
    for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    pattern = "t??";
    keys = redisObj.keys(pattern);
    std::cout << "keys " << pattern << std::endl;
    for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    pattern = "*";
    keys = redisObj.keys(pattern);
    std::cout << "keys " << pattern << std::endl;
    for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    // del keys
    for (std::map<std::string, std::string>::const_iterator it = kvMap.begin(); it != kvMap.end(); ++it)
    {
        redisObj.del(it->first);
    }
}

// http://redis.io/commands/move
void move_example()
{
    const std::string key = "move_example_key";
    redisObj.set(key, "Hello");
    std::cout << "set " << key << " Hello" << std::endl;
    CppRedisClient::StringReply reply = redisObj.get(key);
    std::cout << "0 db get " << key << " is " << reply << std::endl;
    redisObj.select(1);
    reply = redisObj.get(key);
    std::cout << "1 db get " << key << " is " << reply << std::endl;

    redisObj.select(0);
    redisObj.move(key, 1);
    std::cout << "move " << key << " 1" << std::endl;

    reply = redisObj.get(key);
    std::cout << "0 db get " << key << " is " << reply << std::endl;
    redisObj.select(1);
    reply = redisObj.get(key);
    std::cout << "1 db get " << key << " is " << reply << std::endl;

    redisObj.del(key);
    redisObj.select(0);
}

// http://redis.io/commands/object
void object_example()
{
    const std::string key = "object_example_key";
    redisObj.lpush(key, "Hello World");
    std::cout << "lpush " << key << " Hello World" << std::endl;

    CppRedisClient::StringReply result = redisObj.object(CppRedisClient::REFCOUNT, key);
    std::cout << "object refcount " << key << std::endl;
    std::cout << result << std::endl;
    result = redisObj.object(CppRedisClient::ENCODING, key);
    std::cout << "object encoding " << key << std::endl;
    std::cout << result << std::endl;
    result = redisObj.object(CppRedisClient::IDLETIME, key);
    std::cout << "object idletime " << key << std::endl;
    std::cout << result << std::endl;

    redisObj.set(key, "10");
    std::cout << "set " << key << " 10" << std::endl;
    result = redisObj.object(CppRedisClient::ENCODING, key);
    std::cout << "object encoding " << key << std::endl;
    std::cout << result << std::endl;
    redisObj.append(key, "bar");
    std::cout << "get " << key << " is " << redisObj.get(key) << std::endl;
    result = redisObj.object(CppRedisClient::ENCODING, key);
    std::cout << "object encoding " << key << std::endl;
    std::cout << result << std::endl;

    redisObj.del(key);
}


int main()
{
    typedef void (*ptFn)();
    std::vector<ptFn> fns;
    fns.push_back(del_example);
    fns.push_back(exists_example);
    fns.push_back(expire_example);
    fns.push_back(expireat_example);
    fns.push_back(keys_example);
    fns.push_back(move_example);
    fns.push_back(object_example);

    for (std::vector<ptFn>::const_iterator it = fns.begin(); it != fns.end(); ++it)
    {
        std::cout << "-------------------------------------------" << std::endl;
        (*it)();
        std::cout << "-------------------------------------------" << std::endl;
    }
    return 0;
}
