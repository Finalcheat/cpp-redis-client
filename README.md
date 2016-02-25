# cpp-redis-client
使用C++根据[Redis协议](http://redis.io/topics/protocol)写的客户端，网络部分依赖[Boost.Asio](http://www.boost.org/doc/libs/1_60_0/doc/html/boost_asio.html)。

## 编译
g++ -O2 src/cpp_redis_client.cpp src/string_reply.cpp -I {BOOST_INCLUDE} -lboost_system -L {BOOST_LIB}

## 简单用例
```
#include "../src/cpp_redis_client.h"
#include <iostream>
#include <string>

int main()
{
    // 创建Redis连接
    CppRedisClient::RedisClient redisObj("localhost");

    // key string 和 value string
    const std::string key = "cpp_redis_client_test_key";
    const std::string value = "cpp_redis_client_test_value";

    // 设置key-value
    redisObj.set(key, value);

    // 根据key获取value，返回CppRedisClient::StringReply
    CppRedisClient::StringReply reply = redisObj.get(key);

    // CppRedisClient::StringReply重载了<<操作符，输出cpp_redis_client_test_value
    std::cout << reply << std::endl;

    // CppRedisClient::StringReply重载了==操作符，可以直接和std::string进行==比较
    assert(reply == value);

    // toString()返回std::string
    std::string getValue = reply.toString();
    std::cout << getValue << std::endl;

    // 删除key
    redisObj.del(key);

    // 再次获取value，返回null StringReply，可以用isNull()判断当前StringReply是否为null
    reply = redisObj.get(key);
    std::cout << reply.isNull() << std::endl;

    return 0;
}
```
更多用例请看[examples](https://github.com/Finalcheat/cpp-redis-client/tree/master/examples)

## [Doxygen](http://www.stack.nl/~dimitri/doxygen)文档
进入cpp_redis_client目录下执行：
```
> doxygen Doxyfile
```
生成doc目录
