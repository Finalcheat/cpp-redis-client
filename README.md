# cpp-redis-client
使用C++根据[Redis协议](http://redis.io/topics/protocol)写的客户端，网络部分依赖[Boost.Asio](http://www.boost.org/doc/libs/1_60_0/doc/html/boost_asio.html)。

## 编译
g++ -O2 src/cpp_redis_client.cpp src/string_reply.cpp -I {BOOST_INCLUDE} -lboost_system -L {BOOST_LIB}

## 简单用例
```
CppRedisClient::RedisClient redisObj("localhost");
const std::string key = "cpp_redis_client_test_key";
const std::string value = "cpp_redis_client_test_value";
redisObj.set(key, value);
CppRedisClient::StringReply reply = redisObj.get(key);
std::cout << reply << std::endl;         // cpp_redis_client_test_value
std::string getValue = reply.toString()  // CppRedisClient::StringReply -> std::string
std::cout << getValue << std::endl;      // cpp_redis_client_test_value
redisObj.del(key);
reply = redisObj.get(key);               // null string
std::cout << reply.isNull() << std::endl // isNull() return bool, cout 1
```
