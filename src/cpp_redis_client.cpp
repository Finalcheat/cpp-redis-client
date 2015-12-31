/* Copyright (C) 
 * 2016 - Finalcheat
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 */

/**
 * @file cpp_redis_client.cpp
 * @brief cpp redis client
 * @author Finalcheat
 * @version 0.01
 * @date 2015-12-21
 */

#include "cpp_redis_client.h"
#include "cpp_redis_client_impl.cpp"
#include <iostream>


namespace cpp_redis_client {


RedisClient::RedisClient() : impl(0)
{
    std::cout << "RedisClient Init" << std::endl;
}

RedisClient::RedisClient(const std::string& host, const std::string& port)
{
    impl = new RedisClientImpl(host, port);
}

RedisClient::~RedisClient()
{
    // std::cout << "~RedisClient" << std::endl;
    if (impl)
    {
        delete impl;
        impl = 0;
    }
}

void RedisClient::set(const std::string& key, const std::string& value)
{
    if (impl)
    {
        impl->set(key, value);
    }
}

void RedisClient::setex(const std::string& key, const size_t ttl, const std::string& value)
{
    if (impl)
    {
        impl->setex(key, ttl, value);
    }
}

int RedisClient::setnx(const std::string& key, const std::string& value)
{
    if (impl)
    {
        return impl->setnx(key, value);
    }
    return 0;
}


std::string RedisClient::get(const std::string& key) const
{
    if (impl)
    {
        return impl->get(key);
    }
    return "";
}

const size_t RedisClient::append(const std::string& key, const std::string& value)
{
    if (impl)
    {
        return impl->append(key, value);
    }

    return 0;
}

int RedisClient::pexpire(const std::string& key, const size_t milliseconds)
{
    if (impl)
    {
        return impl->pexpire(key, milliseconds);
    }
    return 0;
}

int RedisClient::expire(const std::string& key, const size_t seconds)
{
    if (impl)
    {
        return impl->expire(key, seconds);
    }
    return 0;
}

size_t RedisClient::getbit(const std::string& key, const size_t offset)
{
    if (impl)
    {
        return impl->getbit(key, offset);
    }
    return 0;
}

int RedisClient::incr(const std::string& key)
{
    if (impl)
    {
        return impl->incr(key);
    }
    return 0;
}

std::string RedisClient::getrange(const std::string& key, const int start, const int end)
{
    if (impl)
    {
        return impl->getrange(key, start, end);
    }
    return "";
}

int RedisClient::incrby(const std::string& key, const int amount)
{
    if (impl)
    {
        return impl->incrby(key, amount);
    }
    return 0;
}

int RedisClient::decr(const std::string& key)
{
    if (impl)
    {
        return impl->decr(key);
    }
    return 0;
}

int RedisClient::decrby(const std::string& key, const int amount)
{
    if (impl)
    {
        return impl->decrby(key, amount);
    }
    return 0;
}

size_t RedisClient::strlen(const std::string& key)
{
    if (impl)
    {
        return impl->strlen(key);
    }
    return 0;
}

int RedisClient::ttl(const std::string& key)
{
    if (impl)
    {
        return impl->ttl(key);
    }
    return 0;
}

int RedisClient::pttl(const std::string& key)
{
    if (impl)
    {
        return impl->pttl(key);
    }
    return 0;
}

std::string RedisClient::getset(const std::string& key, const std::string& value)
{
    if (impl)
    {
        return impl->getset(key, value);
    }
    return "";
}


bool RedisClient::ping()
{
    if (impl)
    {
        return impl->ping();
    }

    return false;
}

int RedisClient::persist(const std::string& key)
{
    if (impl)
    {
        return impl->persist(key);
    }
    return 0;
}

int RedisClient::rename(const std::string& srcKey, const std::string& dstKey)
{
    if (impl)
    {
        return impl->rename(srcKey, dstKey);
    }
    return 0;
}

int RedisClient::renamenx(const std::string& srcKey, const std::string& dstKey)
{
    if (impl)
    {
        return impl->renamenx(srcKey, dstKey);
    }
    return 0;
}

size_t RedisClient::llen(const std::string& key)
{
    if (impl)
    {
        return impl->llen(key);
    }
    return 0;
}

int RedisClient::move(const std::string& key, const size_t db)
{
    if (impl)
    {
        return impl->move(key, db);
    }
    return 0;
}

int RedisClient::exists(const std::string& key)
{
    if (impl)
    {
        return impl->exists(key);
    }
    return 0;
}




}

int main()
{
    // cpp_redis_client::RedisClient redis_obj1;
    cpp_redis_client::RedisClient redis_obj2("localhost");
    // redis_obj2.set("f", "c");
    // redis_obj2.set("c", "f");
    // std::cout << redis_obj2.get("b") << std::endl;
    // redis_obj2.setex("ttl_test", 60, "value");
    // redis_obj2.append("ttl_test", "_key");
    // redis_obj2.pexpire("ttl_test", 60 * 60 * 1000);
    std::string str1("ssss"\
            "ttt");
    std::string key = "f";
    // std::string response = redis_obj2.get(key);
    // std::cout << key << " : " << response << std::endl;
    // response = redis_obj2.get("b");
    // std::cout << "b : " << response << std::endl;
    // response = redis_obj2.get("sfsdsdfs");
    // std::cout << "sfsdsdfs : " << response << std::endl;
    // std::cout << "mykey : " << redis_obj2.get("mykey") << std::endl;
    // std::cout << "c : " << redis_obj2.get("c") << std::endl;
    // std::cout << redis_obj2.append("f", "c") << std::endl;
    redis_obj2.setex("xx", 60, "yy");
    redis_obj2.set("yy", "xx");
    int num = redis_obj2.pexpire("yyy", 60 * 1000);
    std::cout << num << std::endl;
    num = redis_obj2.expire("yy", 60);
    std::cout << num << std::endl;
    // std::cout << redis_obj2.persist("yy") << std::endl;
    std::cout << redis_obj2.getbit("f", 1) << std::endl;
    std::cout << redis_obj2.getbit("f", 3) << std::endl;
    std::cout << redis_obj2.incr("num") << std::endl;
    std::cout << redis_obj2.incrby("num", 2) << std::endl;
    std::cout << redis_obj2.decr("num") << std::endl;
    std::cout << redis_obj2.decrby("num", -2) << std::endl;
    // std::cout << redis_obj2.setnx("ffff", "test") << std::endl;
    // std::cout << redis_obj2.setnx("ffff", "1") << std::endl;
    std::cout << redis_obj2.ttl("yy") << std::endl;
    std::cout << redis_obj2.ttl("yyyy") << std::endl;
    std::cout << redis_obj2.ttl("num") << std::endl;
    std::cout << redis_obj2.pttl("yy") << std::endl;
    std::cout << redis_obj2.pttl("yyyy") << std::endl;
    std::cout << redis_obj2.pttl("num") << std::endl;
    std::cout << redis_obj2.strlen("f") << std::endl;
    std::cout << redis_obj2.getrange("f", 1, 6) << std::endl;
    std::cout << redis_obj2.getrange("f", 13, -1) << std::endl;
    try 
    {
        redis_obj2.incr("f");
    } 
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    std::cout << redis_obj2.ping() << std::endl;
    // std::cout << redis_obj2.get("f") << std::endl;
    // redis_obj2.get("mykey");
    // redis_obj2.get("b");
    // std::cout << redis_obj2.get("ff") << std::endl;
    std::string test("sfdskhtuiw\r\narfstfsfsa");
    // std::cin >> test;
    return 0;
}
