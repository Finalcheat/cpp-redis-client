#define BOOST_TEST_MODULE redis_client_string_test

#include <boost/test/included/unit_test.hpp>
#include <string>
#include "../src/cpp_redis_client.h"
#include "../src/string_reply.h"

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE(redis_client_string_test) // name of the test suite is stringtest


CppRedisClient::RedisClient r("localhost");

BOOST_AUTO_TEST_CASE(append)
{
    const std::string key1 = "append_test_key1";
    const std::string value1 = "append";
    const std::string key2 = "append_test_key2";
    const std::string append_value = "append";
    r.set(key1, value1);

    size_t length = r.append(key1, append_value);
    BOOST_CHECK(length == value1.size() + append_value.size());
    length = r.append(key2, append_value);
    BOOST_CHECK(length == append_value.size());

    r.del(key1);
    r.del(key2);
}

BOOST_AUTO_TEST_CASE(bitcount)
{
    const std::string key = "bitcount_test_key";
    r.set(key, "foobar");

    size_t num = r.bitcount(key);
    BOOST_CHECK(num == 26);
    num = r.bitcount(key, 0, 0);
    BOOST_CHECK(num == 4);
    num = r.bitcount(key, 1, 1);
    BOOST_CHECK(num == 6);

    r.del(key);
}


BOOST_AUTO_TEST_CASE(decr)
{
    const std::string key = "decr_test_key";
    const std::string value = "10";
    r.set(key, value);

    for (int i = 1; i <= 10; ++i)
    {
        int num = r.decr(key);
        BOOST_CHECK(num == 10 - i);
    }

    r.del(key);
}


BOOST_AUTO_TEST_CASE(decrby)
{
    const std::string key = "decrby_test_key";
    const std::string value = "5";
    r.set(key, value);

    int num = r.decrby(key, 10);
    BOOST_CHECK(num == -5);
    num = r.decrby(key, -5);
    BOOST_CHECK(num == 0);

    r.del(key);
}


BOOST_AUTO_TEST_CASE(get)
{
    // cpp_redis_client::RedisClient r("localhost");
    const std::string key1 = "get_test_key1";
    const std::string key2 = "get_test_key2";
    const std::string key3 = "test_null_key";
    r.set(key1, "value1");
    r.set(key2, "");

    CppRedisClient::StringReply reply = r.get(key1);
    BOOST_CHECK(reply.toString() == "value1");
    reply = r.get(key2);
    BOOST_CHECK(reply.toString() == "");
    reply = r.get(key3);
    BOOST_CHECK(reply.isNull());

    r.del(key1);
    r.del(key2);
    r.del(key3);
}


BOOST_AUTO_TEST_CASE(getbit)
{
    const std::string key = "getbit_test_key";
    r.setbit(key, 7, 1);

    size_t num = r.getbit(key, 0);
    BOOST_CHECK(num == 0);
    num = r.getbit(key, 7);
    BOOST_CHECK(num == 1);
    num = r.getbit(key, 100);
    BOOST_CHECK(num == 0);

    r.del(key);
}


BOOST_AUTO_TEST_CASE(getrange)
{
    const std::string key = "getrange_test_key";
    const std::string value = "This is a string";
    r.set(key, value);

    std::string response = r.getrange(key, 0, 3);
    BOOST_CHECK(response == "This");
    response = r.getrange(key, -3, -1);
    BOOST_CHECK(response == "ing");
    response = r.getrange(key, 0, -1);
    BOOST_CHECK(response == "This is a string");
    response = r.getrange(key, 10, 100);
    BOOST_CHECK(response == "string");

    r.del(key);
}


BOOST_AUTO_TEST_CASE(getset)
{
    const std::string key = "getset_test_key";
    const std::string value = "getset_ori_value";
    r.set(key, value);

    CppRedisClient::StringReply response = r.getset(key, "value");
    BOOST_CHECK(response == value);
    CppRedisClient::StringReply reply = r.get(key);
    BOOST_CHECK(reply.toString() == "value");

    r.del(key);
}


BOOST_AUTO_TEST_CASE(incr)
{
    const std::string key = "incr_test_key";
    const std::string value = "10";
    r.set(key, value);

    int num = r.incr(key);
    BOOST_CHECK(num == 11);

    r.del(key);
}


BOOST_AUTO_TEST_CASE(incrby)
{
    const std::string key = "incrby_test_key";
    const std::string value = "5";
    r.set(key, value);

    int num = r.incrby(key, 3);
    BOOST_CHECK(num == 8);
    num = r.incrby(key, -10);
    BOOST_CHECK(num == -2);

    r.del(key);
}


BOOST_AUTO_TEST_CASE(incrbyfloat)
{
    const std::string key = "incrbyfloat_test_key";
    const std::string value = "10.50";
    const float amount = 10.5;
    r.set(key, value);

    std::string num = r.incrbyfloat(key, amount);
    // std::cout << num << std::endl;
    BOOST_CHECK(num == "21");

    r.del(key);
}


BOOST_AUTO_TEST_CASE(mget)
{
    const std::string key1 = "mget_test_key1";
    const std::string value1 = "mget_test_key1_value";
    const std::string key2 = "mget_test_key2";
    const std::string value2 = "mget_test_key2_value";
    const std::string key3 = "mget_test_key3";
    r.set(key1, value1);
    r.set(key2, value2);
    std::vector<std::string> keys;
    keys.push_back(key1);
    keys.push_back(key3);
    keys.push_back(key2);

    std::vector<CppRedisClient::StringReply> replys = r.mget(keys);
    BOOST_REQUIRE(replys.size() == keys.size());
    BOOST_REQUIRE(replys[0] == value1);
    BOOST_REQUIRE(replys[1].isNull());
    BOOST_REQUIRE(replys[2] == value2);

    r.del(key1);
    r.del(key2);
}


BOOST_AUTO_TEST_CASE(mset)
{
    const std::string key1 = "mset_test_key1";
    const std::string value1 = "mset_test_key1_value1";
    const std::string key2 = "mset_test_key2";
    const std::string value2 = "mset_test_key2_value2";
    std::map<std::string, std::string> kvMap;
    kvMap[key1] = value1;
    kvMap[key2] = value2;

    r.mset(kvMap);

    CppRedisClient::StringReply reply = r.get(key1);
    BOOST_REQUIRE(reply == value1);
    reply = r.get(key2);
    BOOST_REQUIRE(reply == value2);

    r.del(key1);
    r.del(key2);
}


BOOST_AUTO_TEST_CASE(msetnx)
{
    const std::string key1 = "msetnx_test_key1";
    const std::string value1 = "msetnx_test_key1_value1";
    const std::string key2 = "msetnx_test_key2";
    const std::string value2 = "msetnx_test_key2_value2";
    std::map<std::string, std::string> kvMap;
    kvMap[key1] = value1;
    kvMap[key2] = value2;

    int num = r.msetnx(kvMap);
    BOOST_CHECK(num == 1);
    CppRedisClient::StringReply reply = r.get(key1);
    BOOST_REQUIRE(reply == value1);
    reply = r.get(key2);
    BOOST_REQUIRE(reply == value2); 
    num = r.msetnx(kvMap);
    BOOST_CHECK(num == 0);

    r.del(key1);
    r.del(key2);
}


BOOST_AUTO_TEST_CASE(psetex)
{
    const std::string key = "psetex_test_key";
    const std::string value = "psetex_test_value";
    const size_t milliseconds = 10 * 1000;

    r.psetex(key, milliseconds, value);
    CppRedisClient::StringReply reply = r.get(key);
    BOOST_CHECK(reply.toString() == value);
    int ttl = r.pttl(key);
    BOOST_CHECK(ttl > 0 && ttl <= milliseconds);

    r.del(key);
}

BOOST_AUTO_TEST_CASE(set)
{
    const std::string key1 = "set_test_key1";
    const std::string value1 = "set_test_key1_value";
    const std::string key2 = "set_test_key2";
    const std::string value2 = "set_test_key2_value";

    r.set(key1, value1);
    r.set(key2, value2);
    CppRedisClient::StringReply reply = r.get(key1);
    BOOST_CHECK(reply.toString() == value1);
    reply = r.get(key2);
    BOOST_CHECK(reply.toString() == value2);

    r.del(key1);
    r.del(key2);
}

BOOST_AUTO_TEST_CASE(setbit)
{
    const std::string key = "setbit_test_key";

    size_t bit = r.setbit(key, 7, 1);
    BOOST_CHECK(bit == 0);
    bit = r.setbit(key, 7, 0);
    BOOST_CHECK(bit == 1);
    CppRedisClient::StringReply reply = r.get(key);
    BOOST_CHECK(reply.size() == 1);

    r.del(key);
}

BOOST_AUTO_TEST_CASE(setex)
{
    const std::string key = "setex_test_key";
    const size_t seconds = 10;
    const std::string value = "setex_test_key_value";

    r.setex(key, seconds, value);
    int ttl = r.ttl(key);
    BOOST_CHECK(ttl > 0 & ttl <= seconds);
    CppRedisClient::StringReply reply = r.get(key);
    BOOST_CHECK(reply.toString() == value);

    r.del(key);
}

BOOST_AUTO_TEST_CASE(setnx)
{
    const std::string key = "setnx_test_key";
    const std::string value = "setnx_test_key_value";

    int num = r.setnx(key, value);
    BOOST_CHECK(num == 1);
    num = r.setnx(key, "Hello World");
    BOOST_CHECK(num == 0);
    CppRedisClient::StringReply reply = r.get(key);
    BOOST_CHECK(reply.toString() == value);

    r.del(key);
}

BOOST_AUTO_TEST_CASE(setrange)
{
    const std::string key = "setrange_test_key";
    const std::string value = "Hello World";
    r.set(key, value);

    size_t length = r.setrange(key, 6, "Redis");
    BOOST_CHECK(length == 11);
    CppRedisClient::StringReply reply = r.get(key);
    BOOST_CHECK(reply.toString() == "Hello Redis");

    r.del(key);
}

BOOST_AUTO_TEST_CASE(strlen)
{
    const std::string key1 = "strlen_test_key1";
    const std::string value1 = "Redis";
    const std::string key2 = "strlen_test_key2";
    const std::string value2 = "";
    const std::string key3 = "strlen_test_null_key";
    r.set(key1, value1);
    r.set(key2, value2);

    size_t length = r.strlen(key1);
    BOOST_CHECK(length == value1.size());
    length = r.strlen(key2);
    BOOST_CHECK(length == value2.size());
    length = r.strlen(key3);
    BOOST_CHECK(length == 0);

    r.del(key1);
    r.del(key2);
}


BOOST_AUTO_TEST_SUITE_END( )







