#define BOOST_TEST_MODULE redis_client_hashs_test

#include <boost/test/included/unit_test.hpp>
#include <string>
#include "../src/cpp_redis_client.h"
#include "../src/string_reply.h"

BOOST_AUTO_TEST_SUITE(redis_client_hashs_test)

CppRedisClient::RedisClient r("localhost");


BOOST_AUTO_TEST_CASE(hdel)
{
    const std::string key = "hdel_test_key";
    const std::string field = "hdel_test_key_field";
    const std::string value = "hdel_test_key_value";
    r.hset(key, field, value);

    int num = r.hdel(key, field);
    BOOST_REQUIRE(num == 1);
    num = r.hdel(key, field);
    BOOST_REQUIRE(num == 0);
}

BOOST_AUTO_TEST_CASE(hexists)
{
    const std::string& key = "hexists_test_key";
    const std::string& value = "hexists_test_key_value";
    const std::string& field = "hexists_test_key_field";
    const std::string& field2 = "hexists_test_key_field2";
    r.hset(key, field, value);

    int num = r.hexists(key, field);
    BOOST_REQUIRE(num == 1);
    num = r.hexists(key, field2);
    BOOST_REQUIRE(num == 0);

    r.del(key);
}

BOOST_AUTO_TEST_CASE(hget)
{
    const std::string& key = "hget_test_key";
    const std::string& field = "hget_test_key_field";
    const std::string& value = "hget_test_key_value";
    const std::string& field2 = "hget_test_key_field2";
    r.hset(key, field, value);

    CppRedisClient::StringReply reply = r.hget(key, field);
    BOOST_REQUIRE(reply == value);
    reply = r.hget(key, field2);
    BOOST_REQUIRE(reply.isNull());

    r.del(key);
}

BOOST_AUTO_TEST_CASE(hgetall)
{
    std::map<std::string, std::string> fvMap;
    std::string key = "hgetall_test_key";
    for (size_t i = 0; i < 10; ++i)
    {
        std::string indexStr = boost::lexical_cast<std::string>(i);
        std::string field = "hgetall_test_key_field_" + indexStr;
        std::string value = "hgetall_test_key_value_" + indexStr;
        fvMap[field] = value;
        r.hset(key, field, value);
    }

    std::map<std::string, std::string> replys = r.hgetall(key);
    BOOST_REQUIRE(replys.size() == fvMap.size());
    for (std::map<std::string, std::string>::const_iterator it = replys.begin(); it != replys.end(); ++it)
    {
        const std::string& key = it->first;
        // std::cout << key << " : " << it->second << std::endl;
        std::map<std::string, std::string>::const_iterator findIt = fvMap.find(key);
        BOOST_REQUIRE(findIt != fvMap.end());
        BOOST_REQUIRE(findIt->second == it->second);
    }

    r.del(key);
}

BOOST_AUTO_TEST_CASE(hincrby)
{
    const std::string& key = "hincrby_test_key";
    const std::string& field = "hincrby_test_key_field";
    const int initValue = 5;

    int num = r.hincrby(key, field, initValue);
    BOOST_REQUIRE(num == 5);
    num = r.hincrby(key, field, 1);
    BOOST_REQUIRE(num == 6);
    num = r.hincrby(key, field, -1);
    BOOST_REQUIRE(num == 5);
    num = r.hincrby(key, field, -10);
    BOOST_REQUIRE(num == -5);

    r.del(key);
}

BOOST_AUTO_TEST_CASE(hincrbyfloat)
{
    const std::string& key = "hincrbyfloat_test_key";
    const std::string& field = "hincrby_test_key_field";
    r.hset(key, field, "10.50");

    std::string num = r.hincrbyfloat(key, field, 10.5);
    // std::cout << num << std::endl;
    BOOST_CHECK(num == "21");

    r.del(key);
}

BOOST_AUTO_TEST_CASE(hkeys)
{
    const std::string key = "hkeys_test_key";
    const std::string field1 = "hkeys_test_key_field1";
    const std::string field2 = "hkeys_test_key_field2";
    const std::string field3 = "hkeys_test_key_field3";
    r.hset(key, field1, "1");
    r.hset(key, field2, "2");

    std::vector<std::string> replys = r.hkeys(key);
    BOOST_REQUIRE(replys.size() == 2);
    std::vector<std::string>::iterator it = std::find(replys.begin(), replys.end(), field1);
    BOOST_REQUIRE(it != replys.end());
    it = std::find(replys.begin(), replys.end(), field3);
    BOOST_REQUIRE(it == replys.end());
    it = std::find(replys.begin(), replys.end(), field2);
    BOOST_REQUIRE(it != replys.end());

    r.del(key);
}

BOOST_AUTO_TEST_CASE(hlen)
{
    const std::string& key = "hlen_test_key";
    const std::string& field1 = "hlen_test_key_field1";
    const std::string& field2 = "hlen_test_key_field2";
    r.hset(key, field1, "1");
    r.hset(key, field2, "2");

    size_t len = r.hlen(key);
    BOOST_REQUIRE(len == 2);

    r.del(key);
}

BOOST_AUTO_TEST_CASE(hmget)
{
    const std::string& key = "hmget_test_key";
    const std::string& field1 = "hmget_test_key_field1";
    const std::string& value1 = "hmget_test_key_value1";
    const std::string& field2 = "hmget_test_key_field2";
    const std::string& value2 = "hmget_test_key_value2";
    const std::string& field3 = "hmget_test_key_field3";
    r.hset(key, field1, value1);
    r.hset(key, field2, value2);
    
    CppRedisClient::StringReply reply = r.hmget(key, field1);
    BOOST_REQUIRE(reply == value1);
    reply = r.hmget(key, field3);
    BOOST_REQUIRE(reply.isNull());
    reply = r.hmget(key, field2);
    BOOST_REQUIRE(reply == value2);

    r.del(key);
}

BOOST_AUTO_TEST_CASE(hmset)
{
    const std::string& key = "hmset_test_key";
    const std::string& field1 = "hmset_test_key_field1";
    const std::string& value1 = "hmset_test_key_value1";
    const std::string& field2 = "hmset_test_key_field2";
    const std::string& value2 = "hmset_test_key_value2";

    r.hmset(key, field1, value1);
    r.hmset(key, field2, value2);
    CppRedisClient::StringReply reply = r.hmget(key, field1);
    BOOST_REQUIRE(reply == value1);
    reply = r.hmget(key, field2);
    BOOST_REQUIRE(reply == value2);

    r.del(key);
}

BOOST_AUTO_TEST_CASE(hset)
{
    const std::string& key = "hset_test_key";
    const std::string& field = "hset_test_key_field";
    const std::string& value = "hset_test_key_value";
    r.del(key);

    int num = r.hset(key, field, value);
    BOOST_REQUIRE(num == 1);
    num = r.hset(key, field, value);
    BOOST_REQUIRE(num == 0);
    CppRedisClient::StringReply reply = r.hmget(key, field);
    BOOST_REQUIRE(reply == value);

    r.del(key);
}

BOOST_AUTO_TEST_CASE(hsetnx)
{
    const std::string& key = "hsetnx_test_key";
    const std::string& field = "hsetnx_test_key_field";
    r.del(key);

    int num = r.hsetnx(key, field, "Hello");
    BOOST_REQUIRE(num == 1);
    num = r.hsetnx(key, field, "World");
    BOOST_REQUIRE(num == 0);
    CppRedisClient::StringReply reply = r.hmget(key, field);
    BOOST_REQUIRE(reply == "Hello");

    r.del(key);
}

BOOST_AUTO_TEST_CASE(hvals)
{
    const std::string& key = "hvals_test_key";
    const std::string& field1 = "hvals_test_key_field1";
    const std::string& value1 = "hvals_test_key_value1";
    const std::string& field2 = "hvals_test_key_field2";
    const std::string& value2 = "hvals_test_key_value2";
    r.hset(key, field1, value1);
    r.hset(key, field2, value2);

    std::vector<std::string> replys = r.hvals(key);
    BOOST_REQUIRE(replys.size() == 2);
    std::vector<std::string>::iterator it = std::find(replys.begin(), replys.end(), value1);
    BOOST_REQUIRE(it != replys.end());
    it = std::find(replys.begin(), replys.end(), value2);
    BOOST_REQUIRE(it != replys.end());

    r.del(key);
}


BOOST_AUTO_TEST_SUITE_END()
