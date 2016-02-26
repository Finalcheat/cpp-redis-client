#include "../src/cpp_redis_client.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>

CppRedisClient::RedisClient redisObj("localhost");

std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& vs)
{
    for (std::vector<std::string>::const_iterator it = vs.begin(); it != vs.end(); ++it)
    {
        os << *it << std::endl;
    }
    return os;
}

// http://redis.io/commands/sadd
void sadd_example()
{
    const std::string key1 = "sadd_example_key1";
    const std::string key2 = "sadd_example_key2";
    const std::string key3 = "sadd_example_key3";
    redisObj.del(key1);
    redisObj.del(key2);
    redisObj.del(key3);

    int num = redisObj.sadd(key1, "Hello");
    std::cout << "sadd " << key1 << " Hello" << std::endl;
    std::cout << num << std::endl;

    num = redisObj.sadd(key1, "World");
    std::cout << "sadd " << key1 << " World" << std::endl;
    std::cout << num << std::endl;

    num = redisObj.sadd(key1, "World");
    std::cout << "sadd " << key1 << " World" << std::endl;
    std::cout << num << std::endl;

    std::vector<std::string> replys = redisObj.smembers(key1);
    std::cout << "smembers " << key1 << std::endl;
    std::cout << replys;

    std::vector<std::string> members;
    members.push_back("one");
    members.push_back("two");
    num = redisObj.sadd(key2, members);
    std::cout << "sadd " << key2 << " ";
    for (std::vector<std::string>::const_iterator it = members.begin(); it != members.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << num << std::endl;
    replys = redisObj.smembers(key2);
    std::cout << "smembers " << key2 << std::endl;
    std::cout << replys;

    members.push_back("three");
    num = redisObj.sadd(key2, members);
    std::cout << "sadd " << key2 << " ";
    for (std::vector<std::string>::const_iterator it = members.begin(); it != members.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << num << std::endl;
    replys = redisObj.smembers(key2);
    std::cout << "smembers " << key2 << std::endl;
    std::cout << replys;

    std::set<std::string> memberSet;
    memberSet.insert("four");
    memberSet.insert("five");
    num = redisObj.sadd(key3, memberSet);
    std::cout << "sadd " << key3 << " ";
    for (std::set<std::string>::const_iterator it = memberSet.begin(); it != memberSet.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << num << std::endl;
    replys = redisObj.smembers(key3);
    std::cout << "smembers " << key3 << std::endl;
    std::cout << replys;

    redisObj.del(key1);
    redisObj.del(key2);
    redisObj.del(key3);
}

// http://redis.io/commands/scard
void scard_example()
{
    const std::string key = "scard_example_key";

    redisObj.sadd(key, "Hello");
    std::cout << "sadd " << key << " Hello" << std::endl;
    redisObj.sadd(key, "World");
    std::cout << "sadd " << key << " World" << std::endl;

    const size_t num = redisObj.scard(key);
    std::cout << "scard " << key << std::endl;
    std::cout << num << std::endl;

    redisObj.del(key);
}

// http://redis.io/commands/sdiff
void sdiff_example()
{
    const std::string key1 = "sdiff_example_key1";
    const std::string key2 = "sdiff_example_key2";

    redisObj.sadd(key1, "a");
    redisObj.sadd(key1, "b");
    redisObj.sadd(key1, "c");
    std::cout << "sadd " << key1 << " a" << std::endl;
    std::cout << "sadd " << key1 << " b" << std::endl;
    std::cout << "sadd " << key1 << " c" << std::endl;

    redisObj.sadd(key2, "c");
    redisObj.sadd(key2, "d");
    redisObj.sadd(key2, "e");
    std::cout << "sadd " << key2 << " c" << std::endl;
    std::cout << "sadd " << key2 << " d" << std::endl;
    std::cout << "sadd " << key2 << " e" << std::endl;

    std::vector<std::string> diff = redisObj.sdiff(key1, key2);
    std::cout << "sdiff " << key1 << " " << key2 << std::endl;
    std::cout << diff;

    redisObj.del(key1);
    redisObj.del(key2);
}

// http://redis.io/commands/sdiffstore
void sdiffstore_example()
{
    const std::string key1 = "sdiffstore_example_key1";
    const std::string key2 = "sdiffstore_example_key2";
    const std::string key3 = "sdiffstore_example_key3";

    redisObj.sadd(key1, "a");
    redisObj.sadd(key1, "b");
    redisObj.sadd(key1, "c");
    std::cout << "sadd " << key1 << " a" << std::endl;
    std::cout << "sadd " << key1 << " b" << std::endl;
    std::cout << "sadd " << key1 << " c" << std::endl;

    redisObj.sadd(key2, "c");
    redisObj.sadd(key2, "d");
    redisObj.sadd(key2, "e");
    std::cout << "sadd " << key2 << " c" << std::endl;
    std::cout << "sadd " << key2 << " d" << std::endl;
    std::cout << "sadd " << key2 << " e" << std::endl;

    const size_t num = redisObj.sdiffstore(key3, key1, key2);
    std::cout << "sdiffstore " << key3 << " " << key1 << " " << key2 << std::endl;
    std::cout << num << std::endl;

    std::vector<std::string> members = redisObj.smembers(key3);
    std::cout << "smembers " << key3 << std::endl;
    std::cout << members;

    redisObj.del(key1);
    redisObj.del(key2);
    redisObj.del(key3);
}

// http://redis.io/commands/sinter
void sinter_example()
{
    const std::string key1 = "sinter_example_key1";
    const std::string key2 = "sinter_example_key2";

    redisObj.sadd(key1, "a");
    redisObj.sadd(key1, "b");
    redisObj.sadd(key1, "c");
    std::cout << "sadd " << key1 << " a" << std::endl;
    std::cout << "sadd " << key1 << " b" << std::endl;
    std::cout << "sadd " << key1 << " c" << std::endl;

    redisObj.sadd(key2, "c");
    redisObj.sadd(key2, "d");
    redisObj.sadd(key2, "e");
    std::cout << "sadd " << key2 << " c" << std::endl;
    std::cout << "sadd " << key2 << " d" << std::endl;
    std::cout << "sadd " << key2 << " e" << std::endl;

    std::vector<std::string> replys = redisObj.sinter(key1, key2);
    std::cout << "sinter " << key1 << " " << key2 << std::endl;
    std::cout << replys;

    redisObj.del(key1);
    redisObj.del(key2);
}

// http://redis.io/commands/sinterstore
void sinterstore_example()
{
    const std::string key1 = "sinterstore_example_key1";
    const std::string key2 = "sinterstore_example_key2";
    const std::string key3 = "sinterstore_example_key3";

    redisObj.sadd(key1, "a");
    redisObj.sadd(key1, "b");
    redisObj.sadd(key1, "c");
    std::cout << "sadd " << key1 << " a" << std::endl;
    std::cout << "sadd " << key1 << " b" << std::endl;
    std::cout << "sadd " << key1 << " c" << std::endl;

    redisObj.sadd(key2, "c");
    redisObj.sadd(key2, "d");
    redisObj.sadd(key2, "e");
    std::cout << "sadd " << key2 << " c" << std::endl;
    std::cout << "sadd " << key2 << " d" << std::endl;
    std::cout << "sadd " << key2 << " e" << std::endl;

    const size_t num = redisObj.sinterstore(key3, key1, key2);
    std::cout << "sinterstore " << key3 << " " << key1 << " " << key2 << std::endl;
    std::cout << num << std::endl;

    std::vector<std::string> members = redisObj.smembers(key3);
    std::cout << "smembers " << key3 << std::endl;
    std::cout << members;

    redisObj.del(key1);
    redisObj.del(key2);
    redisObj.del(key3);
}

// http://redis.io/commands/sismember
void sismember_example()
{
    const std::string key = "sismember_example_key";

    redisObj.sadd(key, "one");
    std::cout << "sadd " << key << " one" << std::endl;

    int b = redisObj.sismember(key, "one");
    std::cout << "sismember " << key << " one" << std::endl;
    std::cout << b << std::endl;

    b = redisObj.sismember(key, "two");
    std::cout << "sismember " << key << " two" << std::endl;
    std::cout << b << std::endl;

    redisObj.del(key);
}

// http://redis.io/commands/smembers
void smembers_example()
{
    const std::string key = "smembers_example_key";

    redisObj.sadd(key, "Hello");
    std::cout << "sadd " << key << " Hello" << std::endl;
    redisObj.sadd(key, "World");
    std::cout << "sadd " << key << " World" << std::endl;

    std::vector<std::string> members = redisObj.smembers(key);
    std::cout << "smembers " << key << std::endl;
    std::cout << members;

    redisObj.del(key);
}

// http://redis.io/commands/smove
void smove_example()
{
    const std::string key1 = "smove_example_key1";
    const std::string key2 = "smove_example_key2";

    redisObj.sadd(key1, "one");
    std::cout << "sadd " << key1 << " one" << std::endl;
    redisObj.sadd(key1, "two");
    std::cout << "sadd " << key1 << " two" << std::endl;

    redisObj.sadd(key2, "three");
    std::cout << "sadd " << key2 << " three" << std::endl;

    int b = redisObj.smove(key1, key2, "two");
    std::cout << "smove " << key1 << " " << key2 << " two" << std::endl;
    std::cout << b << std::endl;

    std::vector<std::string> replys = redisObj.smembers(key1);
    std::cout << "smembers " << key1 << std::endl;
    std::cout << replys;

    replys = redisObj.smembers(key2);
    std::cout << "smembers " << key2 << std::endl;
    std::cout << replys;

    redisObj.del(key1);
    redisObj.del(key2);
}

// http://redis.io/commands/spop
void spop_example()
{
    const std::string key = "spop_example_key";

    redisObj.sadd(key, "one");
    std::cout << "sadd " << key << " one" << std::endl;
    redisObj.sadd(key, "two");
    std::cout << "sadd " << key << " two" << std::endl;
    redisObj.sadd(key, "three");
    std::cout << "sadd " << key << " three" << std::endl;

    CppRedisClient::StringReply reply = redisObj.spop(key);
    std::cout << "spop " << key << std::endl;
    std::cout << reply << std::endl;

    std::vector<std::string> replys = redisObj.smembers(key);
    std::cout << "smembers " << key << std::endl;
    std::cout << replys;

    redisObj.del(key);
}

// http://redis.io/commands/srandmember
void srandmember_example()
{
    const std::string key = "srandmember_example_key";

    redisObj.sadd(key, "one");
    std::cout << "sadd " << key << " one" << std::endl;
    redisObj.sadd(key, "two");
    std::cout << "sadd " << key << " two" << std::endl;
    redisObj.sadd(key, "three");
    std::cout << "sadd " << key << " three" << std::endl;

    CppRedisClient::StringReply reply = redisObj.srandmember(key);
    std::cout << "srandmember " << key << std::endl;
    std::cout << reply << std::endl;

    std::vector<std::string> replys = redisObj.smembers(key);
    std::cout << "smembers " << key << std::endl;
    std::cout << replys;

    redisObj.del(key);
}

// http://redis.io/commands/srem
void srem_example()
{
    const std::string key = "srem_example_key";

    redisObj.sadd(key, "one");
    std::cout << "sadd " << key << " one" << std::endl;
    redisObj.sadd(key, "two");
    std::cout << "sadd " << key << " two" << std::endl;
    redisObj.sadd(key, "three");
    std::cout << "sadd " << key << " three" << std::endl;

    size_t b = redisObj.srem(key, "one");
    std::cout << "srem " << key << " one" << std::endl;
    std::cout << b << std::endl;

    b = redisObj.srem(key, "four");
    std::cout << "srem " << key << " four" << std::endl;
    std::cout << b << std::endl;

    std::vector<std::string> replys = redisObj.smembers(key);
    std::cout << "smembers " << key << std::endl;
    std::cout << replys;

    redisObj.del(key);
}

// http://redis.io/commands/sunion
void sunion_example()
{
    const std::string key1 = "sunion_example_key1";
    const std::string key2 = "sunion_example_key2";

    redisObj.sadd(key1, "a");
    std::cout << "sadd " << key1 << " a" << std::endl;
    redisObj.sadd(key1, "b");
    std::cout << "sadd " << key1 << " b" << std::endl;
    redisObj.sadd(key1, "c");
    std::cout << "sadd " << key1 << " c" << std::endl;

    redisObj.sadd(key2, "c");
    std::cout << "sadd " << key2 << " c" << std::endl;
    redisObj.sadd(key2, "d");
    std::cout << "sadd " << key2 << " d" << std::endl;
    redisObj.sadd(key2, "e");
    std::cout << "sadd " << key2 << " e" << std::endl;

    std::vector<std::string> replys = redisObj.sunion(key1, key2);
    std::cout << "sunion " << key1 << " " << key2 << std::endl;
    std::cout << replys;

    redisObj.del(key1);
    redisObj.del(key2);
}

// http://redis.io/commands/sunionstore
void sunionstore_example()
{
    const std::string key1 = "sunionstore_example_key1";
    const std::string key2 = "sunionstore_example_key2";
    const std::string key3 = "sunionstore_example_key3";

    redisObj.sadd(key1, "a");
    std::cout << "sadd " << key1 << " a" << std::endl;
    redisObj.sadd(key1, "b");
    std::cout << "sadd " << key1 << " b" << std::endl;
    redisObj.sadd(key1, "c");
    std::cout << "sadd " << key1 << " c" << std::endl;

    redisObj.sadd(key2, "c");
    std::cout << "sadd " << key2 << " c" << std::endl;
    redisObj.sadd(key2, "d");
    std::cout << "sadd " << key2 << " d" << std::endl;
    redisObj.sadd(key2, "e");
    std::cout << "sadd " << key2 << " e" << std::endl;

    const size_t num = redisObj.sunionstore(key3, key1, key2);
    std::cout << "sunionstore " << key3 << " " << key1 << " " << key2 << std::endl;
    std::cout << num << std::endl;

    std::vector<std::string> replys = redisObj.smembers(key3);
    std::cout << "smembers " << key3 << std::endl;
    std::cout << replys;

    redisObj.del(key1);
    redisObj.del(key2);
    redisObj.del(key3);
}


int main()
{
    typedef void (*ptFn)();
    std::vector<ptFn> fns;
    fns.push_back(sadd_example);
    fns.push_back(scard_example);
    fns.push_back(sdiff_example);
    fns.push_back(sdiffstore_example);
    fns.push_back(sinter_example);
    fns.push_back(sinterstore_example);
    fns.push_back(sismember_example);
    fns.push_back(smembers_example);
    fns.push_back(smove_example);
    fns.push_back(spop_example);
    fns.push_back(srandmember_example);
    fns.push_back(srem_example);
    fns.push_back(sunion_example);
    fns.push_back(sunionstore_example);

    for (std::vector<ptFn>::const_iterator it = fns.begin(); it != fns.end(); ++it)
    {
        std::cout << "-------------------------------------------" << std::endl;
        (*it)();
        std::cout << "-------------------------------------------" << std::endl;
    }

    return 0;
}
