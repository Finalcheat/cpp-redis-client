#define BOOST_TEST_MODULE redis_client_keys_test

#include <boost/test/included/unit_test.hpp>
#include <string>
#include "../src/cpp_redis_client.h"
#include "../src/string_reply.h"

BOOST_AUTO_TEST_SUITE(redis_client_keys_test)

CppRedisClient::RedisClient r("localhost");


BOOST_AUTO_TEST_CASE(del)
{
    const std::string key = "del_test_key";
    const std::string value = "del_test_key_value";
    r.set(key, value);

    CppRedisClient::StringReply reply = r.get(key);
    BOOST_CHECK(reply == "del_test_key_value");
    BOOST_CHECK(reply.toString() == value);

    r.del(key);
    reply = r.get(key);
    BOOST_CHECK(reply.isNull());
}


BOOST_AUTO_TEST_CASE(exists)
{
    const std::string key = "exists_test_key";
    const std::string value = "exists_test_key_value";
    r.set(key, value);

    int exists = r.exists(key);
    BOOST_CHECK(exists == 1);
    r.del(key);
    exists = r.exists(key);
    BOOST_CHECK(exists == 0);
}


BOOST_AUTO_TEST_CASE(expire)
{
    const std::string key = "expire_test_key";
    const std::string value = "expire_test_key_value";
    const size_t seconds = 60;
    r.set(key, value);

    int num = r.expire(key, seconds);
    BOOST_CHECK(num == 1);
    int ttl = r.ttl(key);
    BOOST_CHECK(ttl > 0 && ttl <= seconds);
    num = r.expire("expire_test_null_key", seconds);
    BOOST_CHECK(num == 0);

    r.del(key);
}


BOOST_AUTO_TEST_CASE(dump)
{
    const std::string key = "dump_test_key";
    const std::string value = "dump_test_key_value";
    r.set(key, value);

    CppRedisClient::StringReply reply = r.dump(key);
    // std::cout << reply << std::endl;
    // std::cout << reply.size() << std::endl;
    // std::cout << reply.toString()[0] << std::endl;

    r.del(key);
}


BOOST_AUTO_TEST_CASE(persist)
{
    const std::string key = "persist_test_key";
    const std::string value = "persist_test_key_value";
    r.set(key, value);
    r.expire(key, 10);

    int num = r.persist(key);
    BOOST_CHECK(num == 1);
    num = r.persist(key);
    BOOST_CHECK(num == 0);

    r.del(key);
}


BOOST_AUTO_TEST_CASE(pexpire)
{
    const std::string key = "pexpire_test_key";
    const std::string value = "pexpire_test_key_value";
    const size_t milliseconds = 6000;
    r.set(key, value);

    int num = r.pexpire(key, milliseconds);
    BOOST_CHECK(num == 1);
    int ttl = r.ttl(key);
    BOOST_CHECK(ttl > 0 && ttl <= milliseconds / 1000);
    int pttl = r.pttl(key);
    BOOST_CHECK(pttl > 0 && pttl <= milliseconds);

    r.del(key);
}


BOOST_AUTO_TEST_CASE(pttl)
{
    const std::string key = "pttl_test_key";
    const std::string value = "pttl_test_key_value";
    const size_t milliseconds = 10 * 1000;
    r.setex(key, milliseconds / 1000, value);

    int pttl = r.pttl(key);
    BOOST_CHECK(pttl > 0 && pttl <= milliseconds);

    r.del(key);
}


BOOST_AUTO_TEST_CASE(randomkey)
{
    CppRedisClient::StringReply reply = r.randomkey();
    // std::cout << reply << std::endl;
}


BOOST_AUTO_TEST_CASE(rename)
{
    const std::string key = "rename_test_key";
    const std::string value = "rename_test_key_value";
    const std::string renameKey = "rename_test_key_rename";

    r.set(key, value);
    CppRedisClient::StringReply reply = r.get(key);
    BOOST_CHECK(reply == value);
    r.rename(key, renameKey);
    reply = r.get(key);
    BOOST_CHECK(reply.isNull());
    reply = r.get(renameKey);
    BOOST_CHECK(reply == value);

    // r.del(key);
    r.del(renameKey);
}


BOOST_AUTO_TEST_CASE(renamenx)
{
    const std::string key1 = "renamenx_test_key1";
    const std::string value1 = "renamenx_test_key1_value";
    const std::string key2 = "renamenx_test_key2";
    const std::string value2 = "renamenx_test_key2_value";
    const std::string key3 = "renamenx_test_key3";
    r.set(key1, value1);
    r.set(key2, value2);

    int num = r.renamenx(key1, key2);
    BOOST_CHECK(num == 0);
    num = r.renamenx(key1, key3);
    BOOST_CHECK(num == 1);

    r.del(key2);
    r.del(key3);
}


BOOST_AUTO_TEST_CASE(ttl)
{
    const std::string key = "ttl_test_key";
    const std::string value = "ttl_test_key_value";
    const size_t seconds = 60;
    
    int ttl = r.ttl(key);
    BOOST_CHECK(ttl == -2);
    r.set(key, value);
    ttl = r.ttl(key);
    BOOST_CHECK(ttl == -1);
    r.expire(key, seconds);
    ttl = r.ttl(key);
    BOOST_CHECK(ttl > 0 && ttl <= seconds);

    r.del(key);
}



BOOST_AUTO_TEST_SUITE_END()
