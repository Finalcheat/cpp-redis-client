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


int main()
{
    typedef void (*ptFn)();
    std::vector<ptFn> fns;
    fns.push_back(del_example);
    fns.push_back(exists_example);
    fns.push_back(expire_example);
    fns.push_back(expireat_example);
    fns.push_back(keys_example);

    for (std::vector<ptFn>::const_iterator it = fns.begin(); it != fns.end(); ++it)
    {
        std::cout << "-------------------------------------------" << std::endl;
        (*it)();
        std::cout << "-------------------------------------------" << std::endl;
    }
    return 0;
}
