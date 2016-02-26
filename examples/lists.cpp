#include "../src/cpp_redis_client.h"
#include <iostream>
#include <string>
#include <vector>

CppRedisClient::RedisClient redisObj("localhost");

// http://redis.io/commands/lindex
void lindex_example()
{
    const std::string key = "lindex_example_key";

    redisObj.lpush(key, "World");
    redisObj.lpush(key, "Hello");
    std::cout << "lpush " << key << " World" << std::endl;
    std::cout << "lpush " << key << " Hello" << std::endl;

    CppRedisClient::StringReply reply = redisObj.lindex(key, 0);
    std::cout << "lindex " << key << " 0" << std::endl;
    std::cout << reply << std::endl;

    reply = redisObj.lindex(key, -1);
    std::cout << "lindex " << key << " -1" << std::endl;
    std::cout << reply << std::endl;

    reply = redisObj.lindex(key, 3);
    std::cout << "lindex " << key << " 3" << std::endl;
    std::cout << reply << std::endl;

    redisObj.del(key);
}

// http://redis.io/commands/linsert
void linsert_example()
{
    const std::string key = "linsert_example_key";

    int len = redisObj.rpush(key, "Hello");
    std::cout << "rpush " << key << " Hello" << std::endl;
    std::cout << len << std::endl;

    len = redisObj.rpush(key, "World");
    std::cout << "rpush " << key << " World" << std::endl;
    std::cout << len << std::endl;

    len = redisObj.linsert(key, CppRedisClient::BEFORE, "World", "There");
    std::cout << "linsert" << key << " BEFORE World There" << std::endl;
    std::cout << len << std::endl;

    std::vector<std::string> replys = redisObj.lrange(key, 0, -1);
    std::cout << "lrange " << key << " 0 -1" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    redisObj.del(key);
}

// http://redis.io/commands/llen
void llen_example()
{
    const std::string key = "llen_example_key";

    int len = redisObj.lpush(key, "World");
    std::cout << "lpush " << key << " World" << std::endl;
    std::cout << len << std::endl;

    len = redisObj.lpush(key, "Hello");
    std::cout << "lpush " << key << " Hello" << std::endl;
    std::cout << len << std::endl;

    len = redisObj.llen(key);
    std::cout << "llen " << key << std::endl;
    std::cout << len << std::endl;

    redisObj.del(key);
}

// http://redis.io/commands/lpop
void lpop_example()
{
    const std::string key = "lpop_example_key";

    redisObj.rpush(key, "one");
    std::cout << "rpush " << key << " one" << std::endl;

    redisObj.rpush(key, "two");
    std::cout << "rpush " << key << " two" << std::endl;

    redisObj.rpush(key, "three");
    std::cout << "rpush " << key << " three" << std::endl;

    CppRedisClient::StringReply reply = redisObj.lpop(key);
    std::cout << "lpop " << key << std::endl;
    std::cout << reply << std::endl;

    std::vector<std::string> replys = redisObj.lrange(key, 0, -1);
    std::cout << "lrange " << key << " 0 -1" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    redisObj.del(key);
}

// http://redis.io/commands/lpush
void lpush_example()
{
    const std::string key = "lpush_example_key";

    int len = redisObj.lpush(key, "World");
    std::cout << "lpush " << key << " World" << std::endl;
    std::cout << len << std::endl;

    len = redisObj.lpush(key, "Hello");
    std::cout << "lpush " << key << " Hello" << std::endl;
    std::cout << len << std::endl;

    std::vector<std::string> replys = redisObj.lrange(key, 0, -1);
    std::cout << "lrange " << key << " 0 -1" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    redisObj.del(key);
}

// http://redis.io/commands/lpushx
void lpushx_example()
{
    const std::string key1 = "lpush_example_key1";
    const std::string key2 = "lpush_example_key2";
    redisObj.del(key1);
    redisObj.del(key2);

    redisObj.lpush(key1, "World");
    std::cout << "lpush " << key1 << " World" << std::endl;

    int len = redisObj.lpushx(key1, "Hello");
    std::cout << "lpushx " << key1 << " Hello" << std::endl;
    std::cout << len << std::endl;

    len = redisObj.lpushx(key2, "Hello");
    std::cout << "lpushx " << key2 << " Hello" << std::endl;
    std::cout << len << std::endl;

    std::vector<std::string> replys = redisObj.lrange(key1, 0, -1);
    std::cout << "lrange " << key1 << " 0 -1" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    replys = redisObj.lrange(key2, 0, -1);
    std::cout << "lrange " << key2 << " 0 -1" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    redisObj.del(key1);
    redisObj.del(key2);
}

// http://redis.io/commands/lrange
void lrange_example()
{
    const std::string key = "lrange_example_key";

    redisObj.rpush(key, "one");
    std::cout << "rpush " << key << " one" << std::endl;

    redisObj.rpush(key, "two");
    std::cout << "rpush " << key << " two" << std::endl;

    redisObj.rpush(key, "three");
    std::cout << "rpush " << key << " three" << std::endl;

    std::vector<std::string> replys = redisObj.lrange(key, 0, 0);
    std::cout << "lrange " << key << " 0 0" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    replys = redisObj.lrange(key, -3, 2);
    std::cout << "lrange " << key << " -3 2" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    replys = redisObj.lrange(key, -100, 100);
    std::cout << "lrange " << key << " -100 100" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    replys = redisObj.lrange(key, 5, 10);
    std::cout << "lrange " << key << " 5 10" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    redisObj.del(key);
}

// http://redis.io/commands/lrem
void lrem_example()
{
    const std::string key = "lrem_example_key";

    redisObj.rpush(key, "Hello");
    std::cout << "rpush " << key << " Hello" << std::endl;
    redisObj.rpush(key, "Hello");
    std::cout << "rpush " << key << " Hello" << std::endl;
    redisObj.rpush(key, "foo");
    std::cout << "rpush " << key << " foo" << std::endl;
    redisObj.rpush(key, "Hello");
    std::cout << "rpush " << key << " Hello" << std::endl;

    const size_t num = redisObj.lrem(key, -2, "Hello");
    std::cout << "lrem " << key << " -2 Hello" << std::endl;
    std::cout << num << std::endl;

    std::vector<std::string> replys = redisObj.lrange(key, 0, -1);
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    redisObj.del(key);
}

// http://redis.io/commands/lset
void lset_example()
{
    const std::string key = "lset_example_key";

    redisObj.rpush(key, "one");
    std::cout << "rpush " << key << " one" << std::endl;
    redisObj.rpush(key, "two");
    std::cout << "rpush " << key << " two" << std::endl;
    redisObj.rpush(key, "three");
    std::cout << "rpush " << key << " three" << std::endl;

    redisObj.lset(key, 0, "four");
    std::cout << "lset " << key << " 0 four" << std::endl;
    redisObj.lset(key, -2, "five");
    std::cout << "lset " << key << " -2 five" << std::endl;

    std::vector<std::string> replys = redisObj.lrange(key, 0, -1);
    std::cout << "lrange " << key << " 0 -1" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    redisObj.del(key);
}

// http://redis.io/commands/ltrim
void ltrim_example()
{
    const std::string key = "ltrim_example_key";

    redisObj.rpush(key, "one");
    std::cout << "rpush " << key << " one" << std::endl;
    redisObj.rpush(key, "two");
    std::cout << "rpush " << key << " two" << std::endl;
    redisObj.rpush(key, "three");
    std::cout << "rpush " << key << " three" << std::endl;

    redisObj.ltrim(key, 1, -1);
    std::cout << "ltrim " << key << " 1 -1" << std::endl;

    std::vector<std::string> replys = redisObj.lrange(key, 0, -1);
    std::cout << "lrange " << key << " 0 -1" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    redisObj.del(key);
}

// http://redis.io/commands/rpop
void rpop_example()
{
    const std::string key = "rpop_example_key";

    redisObj.rpush(key, "one");
    std::cout << "rpush " << key << " one" << std::endl;
    redisObj.rpush(key, "two");
    std::cout << "rpush " << key << " two" << std::endl;
    redisObj.rpush(key, "three");
    std::cout << "rpush " << key << " three" << std::endl;

    redisObj.rpop(key);
    std::cout << "rpop " << key << std::endl;

    std::vector<std::string> replys = redisObj.lrange(key, 0, -1);
    std::cout << "lrange " << key << " 0 -1" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    redisObj.del(key);
}

// http://redis.io/commands/rpoplpush
void rpoplpush_example()
{
    const std::string key1 = "rpoplpush_example_key1";
    const std::string key2 = "rpoplpush_example_key2";

    redisObj.rpush(key1, "one");
    std::cout << "rpush " << key1 << " one" << std::endl;
    redisObj.rpush(key1, "two");
    std::cout << "rpush " << key1 << " two" << std::endl;
    redisObj.rpush(key1, "three");
    std::cout << "rpush " << key1 << " three" << std::endl;

    redisObj.rpoplpush(key1, key2);
    std::cout << "rpoplpush " << key1 << " " << key2 << std::endl;

    std::vector<std::string> replys = redisObj.lrange(key1, 0, -1);
    std::cout << "lrange " << key1 << " 0 -1" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    replys = redisObj.lrange(key2, 0, -1);
    std::cout << "lrange " << key2 << " 0 -1" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    redisObj.del(key1);
    redisObj.del(key2);
}

// http://redis.io/commands/rpush
void rpush_example()
{
    const std::string key = "rpush_example_key";

    int len = redisObj.rpush(key, "Hello");
    std::cout << "rpush " << key << " Hello" << std::endl;
    std::cout << len << std::endl;

    len = redisObj.rpush(key, "World");
    std::cout << "rpush " << key << " World" << std::endl;
    std::cout << len << std::endl;


    std::vector<std::string> replys = redisObj.lrange(key, 0, -1);
    std::cout << "lrange " << key << " 0 -1" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    redisObj.del(key);
}

// http://redis.io/commands/rpushx
void rpushx_example()
{
    const std::string key1 = "rpushx_example_key1";
    const std::string key2 = "rpushx_example_key2";
    redisObj.del(key1);
    redisObj.del(key2);

    int len = redisObj.rpush(key1, "Hello");
    std::cout << "rpush " << key1 << " Hello" << std::endl;
    std::cout << len << std::endl;

    len = redisObj.rpushx(key1, "World");
    std::cout << "rpushx " << key1 << " World" << std::endl;
    std::cout << len << std::endl;

    len = redisObj.rpushx(key2, "World");
    std::cout << "rpushx " << key2 << " World" << std::endl;
    std::cout << len << std::endl;

    std::vector<std::string> replys = redisObj.lrange(key1, 0, -1);
    std::cout << "lrange " << key1 << " 0 -1" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    replys = redisObj.lrange(key2, 0, -1);
    std::cout << "lrange " << key2 << " 0 -1" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    redisObj.del(key1);
    redisObj.del(key2);
}


int main()
{
    typedef void (*ptFn)();
    std::vector<ptFn> fns;
    fns.push_back(lindex_example);
    fns.push_back(linsert_example);
    fns.push_back(llen_example);
    fns.push_back(lpop_example);
    fns.push_back(lpush_example);
    fns.push_back(lpushx_example);
    fns.push_back(lrange_example);
    fns.push_back(lrem_example);
    fns.push_back(lset_example);
    fns.push_back(ltrim_example);
    fns.push_back(rpop_example);
    fns.push_back(rpoplpush_example);
    fns.push_back(rpush_example);
    fns.push_back(rpushx_example);

    for (std::vector<ptFn>::const_iterator it = fns.begin(); it != fns.end(); ++it)
    {
        std::cout << "-------------------------------------------" << std::endl;
        (*it)();
        std::cout << "-------------------------------------------" << std::endl;
    }
    return 0;
}
