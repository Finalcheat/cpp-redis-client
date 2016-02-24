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

// http://redis.io/commands/persist
void persist_example()
{
    const std::string key = "persist_example_key";

    redisObj.setex(key, 10, "Hello");
    std::cout << "setex " << key << " 10 Hello" << std::endl;

    int ttl = redisObj.ttl(key);
    std::cout << "ttl " << key << std::endl;
    std::cout << ttl << std::endl;

    redisObj.persist(key);
    std::cout << "persist " << key << std::endl;

    ttl = redisObj.ttl(key);
    std::cout << "ttl " << key << std::endl;
    std::cout << ttl << std::endl;

    redisObj.del(key);
}

// http://redis.io/commands/pexpire
void pexpire_example()
{
    const std::string key = "pexpire_example_key";

    redisObj.set(key, "Hello");
    std::cout << "set " << key << " Hello" << std::endl;
    
    redisObj.pexpire(key, 1499);
    std::cout << "pexpire " << key << " 1499" << std::endl;

    const int ttl = redisObj.ttl(key);
    std::cout << "ttl " << key << std::endl;
    std::cout << ttl << std::endl;

    const int64_t pttl = redisObj.pttl(key);
    std::cout << "pttl " << key << std::endl;
    std::cout << pttl << std::endl;

    redisObj.del(key);
}

// http://redis.io/commands/pexpireat
void pexpireat_example()
{
    const std::string key = "pexpireat_example_key";

    redisObj.set(key, "Hello");
    std::cout << "set " << key << " Hello" << std::endl;

    // 2018-01-01 00:00:00
    const uint64_t millisecondsTimestamp = 1514736000000;
    redisObj.pexpireat(key, millisecondsTimestamp);
    std::cout << "expireat " << key << " " << millisecondsTimestamp << std::endl;

    const int64_t pttl = redisObj.pttl(key);
    std::cout << "pttl " << key << std::endl;
    std::cout << pttl << std::endl;

    redisObj.del(key);
}

// http://redis.io/commands/pttl
void pttl_example()
{
    const std::string key = "pttl_example_key";

    redisObj.setex(key, 1, "Hello");
    std::cout << "setex " << key << " 1 Hello" << std::endl;

    const int64_t pttl = redisObj.pttl(key);
    std::cout << "pttl " << key << std::endl;
    std::cout << pttl << std::endl;

    redisObj.del(key);
}

// http://redis.io/commands/randomkey
void randomkey_example()
{
    CppRedisClient::StringReply key = redisObj.randomkey();
    std::cout << "randomkey" << std::endl;
    std::cout << key << std::endl;
}

// http://redis.io/commands/rename
void rename_example()
{
    const std::string oldKey = "rename_example_old_key";
    const std::string newKey = "rename_example_new_key";

    redisObj.set(oldKey, "Hello");
    std::cout << "set " << oldKey << " Hello" << std::endl;

    redisObj.rename(oldKey, newKey);
    std::cout << "rename " << oldKey << " " << newKey << std::endl;

    std::cout << "get " << newKey << std::endl;
    std::cout << redisObj.get(newKey) << std::endl;

    redisObj.del(newKey);
}

// http://redis.io/commands/renamenx
void renamenx_example()
{
    const std::string key1 = "renamenx_example_key1";
    const std::string key2 = "renamenx_example_key2";

    redisObj.set(key1, "Hello");
    redisObj.set(key2, "World");
    std::cout << "set " << key1 << " Hello" << std::endl;
    std::cout << "set " << key2 << " World" << std::endl;

    redisObj.renamenx(key1, key2);
    std::cout << "renamenx " << key1 << " " << key2 << std::endl;

    std::cout << "get " << key2 << std::endl;
    std::cout << redisObj.get(key2) << std::endl;

    redisObj.del(key1);
    redisObj.del(key2);
}

// http://redis.io/commands/ttl
void ttl_example()
{
    const std::string key = "ttl_example_key";

    redisObj.setex(key, 10, "Hello");
    std::cout << "setex " << key << " 10 Hello" << std::endl;

    const int ttl = redisObj.ttl(key);
    std::cout << "ttl " << key << std::endl;
    std::cout << ttl << std::endl;

    redisObj.del(key);
}

// http://redis.io/commands/type
void type_example()
{
    const std::string key1 = "type_example_key1";
    const std::string key2 = "type_example_key2";
    const std::string key3 = "type_example_key3";
    const std::string key4 = "type_example_key4";

    redisObj.set(key1, "value");
    std::cout << "set " << key1 << " value" << std::endl;
    redisObj.lpush(key2, "value");
    std::cout << "lpush " << key2 << "value" << std::endl;
    redisObj.sadd(key3, "value");
    std::cout << "sadd " << key3 << " value" << std::endl;

    std::string reply = redisObj.type(key1);
    std::cout << "type " << key1 << std::endl;
    std::cout << reply << std::endl;

    reply = redisObj.type(key2);
    std::cout << "type " << key2 << std::endl;
    std::cout << reply << std::endl;

    reply = redisObj.type(key3);
    std::cout << "type " << key3 << std::endl;
    std::cout << reply << std::endl;

    reply = redisObj.type(key4);
    std::cout << "type " << key4 << std::endl;
    std::cout << reply << std::endl;

    redisObj.del(key1);
    redisObj.del(key2);
    redisObj.del(key3);
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
    fns.push_back(persist_example);
    fns.push_back(pexpire_example);
    fns.push_back(pexpireat_example);
    fns.push_back(pttl_example);
    fns.push_back(randomkey_example);
    fns.push_back(rename_example);
    fns.push_back(renamenx_example);
    fns.push_back(ttl_example);
    fns.push_back(type_example);

    for (std::vector<ptFn>::const_iterator it = fns.begin(); it != fns.end(); ++it)
    {
        std::cout << "-------------------------------------------" << std::endl;
        (*it)();
        std::cout << "-------------------------------------------" << std::endl;
    }
    return 0;
}
