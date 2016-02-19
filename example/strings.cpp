#include "../src/cpp_redis_client.h"
#include <iostream>
#include <string>

const std::string line = "--------------------------------------------";


// http://redis.io/commands/append
void append_example(CppRedisClient::RedisClient& redisObj)
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
void bitcount_example(CppRedisClient::RedisClient& redisObj)
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
void decr_example(CppRedisClient::RedisClient& redisObj)
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
void decrby_example(CppRedisClient::RedisClient& redisObj)
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


int main()
{
    // 创建Redis连接
    CppRedisClient::RedisClient redisObj("localhost");

    // append
    append_example(redisObj);

    // bitcount
    bitcount_example(redisObj);

    // decr
    decr_example(redisObj);

    // decrby
    decrby_example(redisObj);
    
    return 0;
}
