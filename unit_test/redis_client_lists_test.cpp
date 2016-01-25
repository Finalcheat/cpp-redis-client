#define BOOST_TEST_MODULE redis_client_lists_test

#include <boost/test/included/unit_test.hpp>
#include <string>
#include "../src/cpp_redis_client.h"
#include "../src/string_reply.h"

BOOST_AUTO_TEST_SUITE(redis_client_lists_test)

CppRedisClient::RedisClient r("localhost");


BOOST_AUTO_TEST_CASE(lindex)
{
    const std::string key = "lindex_test_key";
    r.lpush(key, "Hello");
    r.lpush(key, "World");

    CppRedisClient::StringReply reply = r.lindex(key, 0);
    BOOST_CHECK(reply == "Hello");
    reply = r.lindex(key, -1);
    BOOST_CHECK(reply == "World");
    reply = r.lindex(key, 3);
    BOOST_CHECK(reply.isNull());

    r.del(key);
}

BOOST_AUTO_TEST_CASE(llen)
{
    const std::string key = "llen_test_key";
    r.lpush(key, "Hello");
    r.lpush(key, "World");

    const size_t len = r.llen(key);
    BOOST_CHECK(len == 2);

    r.del(key);
}

BOOST_AUTO_TEST_CASE(lpop)
{
    const std::string key = "lpop_test_key";
    r.rpush(key, "one");
    r.rpush(key, "two");
    r.rpush(key, "three");

    CppRedisClient::StringReply reply = r.lpop(key);
    BOOST_CHECK(reply == "one");
    reply = r.lpop(key);
    BOOST_CHECK(reply == "two");
    reply = r.lpop(key);
    BOOST_CHECK(reply == "three");

    r.del(key);
}

BOOST_AUTO_TEST_CASE(lpush)
{
    const std::string key = "lpush_test_key";

    size_t len = r.lpush(key, "World");
    BOOST_CHECK(len == 1);
    len = r.lpush(key, "Hello");
    BOOST_CHECK(len == 2);

    r.del(key);
}

BOOST_AUTO_TEST_CASE(lpushx)
{
    const std::string key = "lpushx_test_key";
    
    size_t len = r.lpushx(key, "World");
    BOOST_CHECK(len == 1);
    len = r.lpushx(key, "Hello");
    BOOST_CHECK(len == 2);
    len = r.lpushx(key, "Hello");
    BOOST_CHECK(len == 0);

    r.del(key);
}

BOOST_AUTO_TEST_CASE(lrange)
{
    const std::string key = "lrange_test_key";
    r.rpush(key, "one");
    r.rpush(key, "two");

    std::vector<std::string> replys = r.lrange(key, 0, 0);
    // one
    BOOST_REQUIRE(replys.siz() == 1 && replys[0] == "one");
    // one two
    replys = r.lrange(key, -3, 1);
    BOOST_REQUIRE(replys.size() == 2 && replys[0] == "one" && replys[1] == "two");
    // one two
    replys = r.lrange(key, -100, 100);
    BOOST_REQUIRE(replys.size() == 2 && replys[0] == "one" && replys[1] == "two");
    // empty
    replys = r.lrange(key, 90, 100);
    BOOST_CHECK(replys.empty());

    r.del(key);
}

BOOST_AUTO_TEST_CASE(lrem)
{
    const std::string key = "lrem_test_key";
    size_t len = r.rpush(key, "Hello");
    BOOST_REQUIRE(len == 1);
    len = r.rpush(key, "Hello");
    BOOST_REQUIRE(len == 2);
    len = r.rpush(key, "foo");
    BOOST_REQUIRE(len == 3);
    len = r.rpush(key, "Hello");
    BOOST_REQUIRE(len == 4);

    len = r.lrem(key, -2, "Hello");
    BOOST_REQUIRE(len == 2);
    std::vector<std::string> replys = r.lrange(key, 0, -1);
    BOOST_REQUIRE(replys.size() == 2 && replys[0] == "Hello" && replys[1] == "foo");

    r.del(key);
}

BOOST_AUTO_TEST_CASE(lset)
{
    const std::string key = "lset_test_key";
    r.rpush(key, "one");
    r.rpush(key, "two");
    r.rpush(key, "three");

    r.lset(key, 0, "four");
    r.lset(key, -2, "five");
    std::vector<std::string> replys = r.lrange(key, 0, -1);
    BOOST_REQUIRE(replys.size() == 3 && replys[0] == "four" && replys[1] == "five" && replys[2] == "three");

    r.del(key);
}

BOOST_AUTO_TEST_CASE(ltrim)
{
    const std::string key = "ltrim_test_key";
    r.rpush(key, "one");
    r.rpush(key, "two");
    r.rpush(key, "three");

    r.ltrim(key, 1, -1);
    std::vector<std::string> replys = r.lrange(key, 0, -1);
    BOOST_REQUIRE(replys.size() == 2 && replys[0] == "two" && replys[1] == "three");

    r.del(key);
}

BOOST_AUTO_TEST_CASE(rpop)
{
    const std::sting key = "rpop_test_key";
    r.rpush(key, "one");
    r.rpush(key, "two");
    r.rpush(key, "three");

    CppRedisClient::StringReply reply = r.rpop(key);
    BOOST_CHECK(reply == "three");
    std::vector<std::string> replys = r.lrange(key, 0, -1);
    BOOST_REQUIRE(replys.size() == 2 && replys[0] == "one" && replys[1] == "two");
}

BOOST_AUTO_TEST_CASE(rpoplpush)
{
    const std::string key = "rpoplpush_test_key";
    const std::string key_other = "myother_rpoplpush_test_key";
    r.rpush(key, "one");
    r.rpush(key, "two");
    r.rpush(key, "three");

    r.rpoplpush(key, key_other);
    std::vector<std::string> replys = r.lrange(key, 0, -1);
    BOOST_REQUIRE(replys.size() == 2 && replys[0] == "one" && replys[1] == "two");
    replys = r.lrange(key_other, 0, -1);
    BOOST_REQUIRE(replys.size() == 1 && replys[0] == "three");

    r.del(key);
    r.del(key_other);
}

BOOST_AUTO_TEST_CASE(rpush)
{
    const std::string key = "rpush_test_key";
    
    r.rpush(key, "Hello");
    r.rpush(key, "World");
    std::vector<std::string> replys = r.lrange(key, 0, -1);
    BOOST_REQUIRE(replys.size() == 2 && replys[0] == "Hello" && replys[1] == "World");

    r.del(key);
}

BOOST_AUTO_TEST_CASE(rpushx)
{
    const std::string key = "rpushx_test_key";
    const std::string key_other = "other_rpushx_test_key";

    r.rpushx(key, "Hello");
    r.rpushx(key, "World");
    size_t len = r.rpushx(key_other, "Hello");
    BOOST_REQUIRE(len == 0);

    std::vector<std::string> replys = r.lrange(key, 0, -1);
    BOOST_REQUIRE(replys.size() == 2 && replys[0] == "Hello" && replys[1] == "World");
    replys = r.lrange(key_other, 0, -1);
    BOOST_CHECK(replys.empty());

    r.del(key);
    r.del(key_other);
}









BOOST_AUTO_TEST_SUITE_END()
