#include "../src/cpp_redis_client.h"
#include <iostream>
#include <string>
#include <vector>

CppRedisClient::RedisClient redisObj("localhost");


// http://redis.io/commands/zadd
void zadd_example()
{
    const std::string key = "zadd_example_key";

    size_t num = redisObj.zadd(key, 1, "one");
    std::cout << "zadd " << key << " 1 one" << std::endl;
    std::cout << num << std::endl;

    num = redisObj.zadd(key, 1, "uno");
    std::cout << "zadd " << key << " 1 uno" << std::endl;
    std::cout << num << std::endl;

    num = redisObj.zadd(key, 2, "two");
    std::cout << "zadd " << key << " 2 two" << std::endl;
    std::cout << num << std::endl;

    num = redisObj.zadd(key, 3, "three");
    std::cout << "zadd " << key << " 3 three" << std::endl;
    std::cout << num << std::endl;

    std::vector<std::string> replys = redisObj.zrange(key, 0, -1);
    std::cout << "zrange " << key << " 0 -1" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    redisObj.del(key);
}

// http://redis.io/commands/zcard
void zcard_example()
{
    const std::string key = "zcard_example_key";
    redisObj.del(key);

    redisObj.zadd(key, 1, "one");
    std::cout << "zadd " << key << " 1 one" << std::endl;

    redisObj.zadd(key, 2, "two");
    std::cout << "zadd " << key << " 2 two" << std::endl;

    const size_t num = redisObj.zcard(key);
    std::cout << "zcard " << key << std::endl;
    std::cout << num << std::endl;

    redisObj.del(key);
}

// http://redis.io/commands/zcount
void zcount_example()
{
    const std::string key = "zcount_example_key";

    redisObj.zadd(key, 1, "one");
    std::cout << "zadd " << key << " 1 one" << std::endl;

    redisObj.zadd(key, 2, "two");
    std::cout << "zadd " << key << " 2 two" << std::endl;

    redisObj.zadd(key, 3, "three");
    std::cout << "zadd " << key << " 3 three" << std::endl;

    const size_t count = redisObj.zcount(key, 2, 3);
    std::cout << "zcount " << key << " 2 3" << std::endl;
    std::cout << count << std::endl;

    redisObj.del(key);
}

// http://redis.io/commands/zincrby
void zincrby_example()
{
    const std::string key = "zincrby_example_key";

    redisObj.zadd(key, 1, "one");
    std::cout << "zadd " << key << " 1 one" << std::endl;

    redisObj.zadd(key, 2, "two");
    std::cout << "zadd " << key << " 2 two" << std::endl;

    const std::string num = redisObj.zincrby(key, 2, "one");
    std::cout << "zincrby " << key << " 2 one" << std::endl;
    std::cout << num << std::endl;

    // std::vector<std::string> replys = redisObj.zrange(key, 0, -1);
    // std::cout << "zrange " << key << " 0 -1" << std::endl;
    // for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    // {
        // std::cout << *it << std::endl;
    // }

    redisObj.del(key);
}

// http://redis.io/commands/zrange
void zrange_example()
{
    const std::string key = "zrange_example_key";

    redisObj.zadd(key, 1, "one");
    std::cout << "zadd " << key << " 1 one" << std::endl;

    redisObj.zadd(key, 1, "uno");
    std::cout << "zadd " << key << " 1 uno" << std::endl;

    redisObj.zadd(key, 2, "two");
    std::cout << "zadd " << key << " 2 two" << std::endl;

    redisObj.zadd(key, 3, "three");
    std::cout << "zadd " << key << " 3 three" << std::endl;

    std::vector<std::string> replys = redisObj.zrange(key, 0, -1);
    std::cout << "zrange " << key << " 0 -1" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    replys = redisObj.zrange(key, 2, 3);
    std::cout << "zrange " << key << " 2 3" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    replys = redisObj.zrange(key, -2, -1);
    std::cout << "zrange " << key << " -2 -1" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    redisObj.del(key);
}

// http://redis.io/commands/zrangebyscore
void zrangebyscore_example()
{
    const std::string key = "zrangebyscore_example_key";

    redisObj.zadd(key, 1, "uno");
    std::cout << "zadd " << key << " 1 uno" << std::endl;

    redisObj.zadd(key, 2, "two");
    std::cout << "zadd " << key << " 2 two" << std::endl;

    redisObj.zadd(key, 3, "three");
    std::cout << "zadd " << key << " 3 three" << std::endl;

    std::vector<std::string> replys = redisObj.zrangebyscore(key, 1, 2);
    std::cout << "zrangebyscore " << key << " 1 2" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    redisObj.del(key);
}

// http://redis.io/commands/zrank
void zrank_example()
{
    const std::string key = "zrank_example_key";

    redisObj.zadd(key, 1, "one");
    std::cout << "zadd " << key << " 1 one" << std::endl;

    redisObj.zadd(key, 2, "two");
    std::cout << "zadd " << key << " 2 two" << std::endl;

    CppRedisClient::StringReply reply = redisObj.zrank(key, "two");
    std::cout << "zrank " << key << " two" << std::endl;
    std::cout << reply << std::endl;

    reply = redisObj.zrank(key, "three");
    std::cout << "zrank " << key << " three" << std::endl;
    std::cout << reply << std::endl;

    redisObj.del(key);
}

// http://redis.io/commands/zrem
void zrem_example()
{
    const std::string key = "zrem_example_key";

    redisObj.zadd(key, 1, "one");
    std::cout << "zadd " << key << " 1 one" << std::endl;

    redisObj.zadd(key, 2, "two");
    std::cout << "zadd " << key << " 2 two" << std::endl;

    const size_t num = redisObj.zrem(key, "one");
    std::cout << "zrem " << key << " one" << std::endl;
    std::cout << num << std::endl;

    std::vector<std::string> replys = redisObj.zrange(key, 0, -1);
    std::cout << "zrange " << key << " 0 -1" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    redisObj.del(key);
}

// http://redis.io/commands/zremrangebyrank
void zremrangebyrank_example()
{
    const std::string key = "zremrangebyrank_example_key";

    redisObj.zadd(key, 1, "one");
    std::cout << "zadd " << key << " 1 one" << std::endl;

    redisObj.zadd(key, 2, "two");
    std::cout << "zadd " << key << " 2 two" << std::endl;

    redisObj.zadd(key, 3, "three");
    std::cout << "zadd " << key << " 3 three" << std::endl;

    const size_t num = redisObj.zremrangebyrank(key, 0, 1);
    std::cout << "zremrangebyrank " << key << " 0 1" << std::endl;
    std::cout << num << std::endl;

    std::vector<std::string> replys = redisObj.zrange(key, 0, -1);
    std::cout << "zrange " << key << " 0 -1" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    redisObj.del(key);
}

// http://redis.io/commands/zremrangebyscore
void zremrangebyscore_example()
{
    const std::string key = "zremrangebyscore_example_key";

    redisObj.zadd(key, 1, "one");
    std::cout << "zadd " << key << " 1 one" << std::endl;

    redisObj.zadd(key, 2, "two");
    std::cout << "zadd " << key << " 2 two" << std::endl;

    redisObj.zadd(key, 3, "three");
    std::cout << "zadd " << key << " 3 three" << std::endl;

    const size_t num = redisObj.zremrangebyscore(key, 0, 1);
    std::cout << "zremrangebyscore " << key << " 0 1" << std::endl;
    std::cout << num << std::endl;

    std::vector<std::string> replys = redisObj.zrange(key, 0, -1);
    std::cout << "zrange " << key << " 0 -1" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    redisObj.del(key);
}

// http://redis.io/commands/zrevrange
void zrevrange_example()
{
    const std::string key = "zrevrange_example_key";

    redisObj.zadd(key, 1, "one");
    std::cout << "zadd " << key << " 1 one" << std::endl;

    redisObj.zadd(key, 2, "two");
    std::cout << "zadd " << key << " 2 two" << std::endl;

    redisObj.zadd(key, 3, "three");
    std::cout << "zadd " << key << " 3 three" << std::endl;

    std::vector<std::string> replys = redisObj.zrevrange(key, 0, -1);
    std::cout << "zrevrange " << key << " 0 -1" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    replys = redisObj.zrevrange(key, 2, 3);
    std::cout << "zrevrange " << key << " 2 3" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    replys = redisObj.zrevrange(key, -2, -1);
    std::cout << "zrevrange " << key << " -2 -1" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    redisObj.del(key);
}

// http://redis.io/commands/zrevrangebyscore
void zrevrangebyscore_example()
{
    const std::string key = "zrevrangebyscore_example_key";

    redisObj.zadd(key, 1, "one");
    std::cout << "zadd " << key << " 1 one" << std::endl;

    redisObj.zadd(key, 2, "two");
    std::cout << "zadd " << key << " 2 two" << std::endl;

    redisObj.zadd(key, 3, "three");
    std::cout << "zadd " << key << " 3 three" << std::endl;

    std::vector<std::string> replys = redisObj.zrevrangebyscore(key, 2, 1);
    std::cout << "zrevrangebyscore " << key << " 2 1" << std::endl;
    for (std::vector<std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    redisObj.del(key);
}

// http://redis.io/commands/zrevrank
void zrevrank_example()
{
    const std::string key = "zrevrank_example_key";

    redisObj.zadd(key, 1, "one");
    std::cout << "zadd " << key << " 1 one" << std::endl;

    redisObj.zadd(key, 2, "two");
    std::cout << "zadd " << key << " 2 two" << std::endl;

    redisObj.zadd(key, 3, "three");
    std::cout << "zadd " << key << " 3 three" << std::endl;

    CppRedisClient::StringReply reply = redisObj.zrevrank(key, "one");
    std::cout << "zrevrank " << key << " one" << std::endl;
    std::cout << reply << std::endl;

    reply = redisObj.zrevrank(key, "four");
    std::cout << "zrevrank " << key << " four" << std::endl;
    std::cout << reply << std::endl;

    redisObj.del(key);
}

// http://redis.io/commands/zscore
void zscore_example()
{
    const std::string key = "zscore_example_key";

    redisObj.zadd(key, 1, "one");
    std::cout << "zadd " << key << " 1 one" << std::endl;

    CppRedisClient::StringReply reply = redisObj.zscore(key, "one");
    std::cout << "zscore " << key << " one" << std::endl;
    std::cout << reply << std::endl;

    reply = redisObj.zscore(key, "two");
    std::cout << "zscore " << key << " two" << std::endl;
    std::cout << reply << std::endl;

    redisObj.del(key);
}


int main()
{
    typedef void (*ptFn)();
    std::vector<ptFn> fns;
    fns.push_back(zadd_example);
    fns.push_back(zcard_example);
    fns.push_back(zcount_example);
    fns.push_back(zincrby_example);
    fns.push_back(zrange_example);
    fns.push_back(zrangebyscore_example);
    fns.push_back(zrank_example);
    fns.push_back(zrem_example);
    fns.push_back(zremrangebyrank_example);
    fns.push_back(zremrangebyscore_example);
    fns.push_back(zrevrange_example);
    fns.push_back(zrevrangebyscore_example);
    fns.push_back(zrevrank_example);
    fns.push_back(zscore_example);

    for (std::vector<ptFn>::const_iterator it = fns.begin(); it != fns.end(); ++it)
    {
        std::cout << "-------------------------------------------" << std::endl;
        (*it)();
        std::cout << "-------------------------------------------" << std::endl;
    }

    return 0;
}
