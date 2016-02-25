/**
 * @file cpp_redis_client_impl.cpp
 * @brief 协议实现的类，负责实现Redis协议
 * @author Finalcheat
 */

#include "enum_define.h"
#include <iostream>
#include <boost/asio.hpp>
#include <boost/format.hpp>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <boost/array.hpp>
#include <boost/lexical_cast.hpp>


namespace CppRedisClient {


std::string make_string(boost::asio::streambuf& streambuf)
{
  return std::string(boost::asio::buffers_begin(streambuf.data()), 
            boost::asio::buffers_end(streambuf.data()));
}

std::string make_string(boost::asio::streambuf& streambuf, const size_t n)
{
    boost::asio::streambuf::const_buffers_type data = streambuf.data();
    return std::string(boost::asio::buffers_begin(data), boost::asio::buffers_begin(data) + n);
}


class RedisClientImpl
{
    public:
        RedisClientImpl(const std::string& host, const std::string& port);
        ~RedisClientImpl();

    // Keys
    public:
        size_t del(const std::string& key);
        size_t del(const std::vector<std::string>& keys);
        CppRedisClient::StringReply dump(const std::string& key);
        int exists(const std::string& key);
        int expire(const std::string& key, const size_t seconds);
        size_t expireat(const std::string& key, const size_t when);
        std::vector<std::string> keys(const std::string& pattern);
        // void migrate(const std::string& host, const std::string& port, const std::string& key);
        int move(const std::string& key, const size_t db);
        CppRedisClient::StringReply object(const CppRedisClient::OBJECT_SUBCOMMAND subCommand, 
                const std::string& key);
        int persist(const std::string& key);
        int pexpire(const std::string& key, const uint64_t milliseconds);
        int pexpireat(const std::string& key, const uint64_t when);
        int64_t pttl(const std::string& key);
        CppRedisClient::StringReply randomkey();
        void rename(const std::string& srcKey, const std::string& dstKey);
        int renamenx(const std::string& srcKey, const std::string& dstKey);
        int ttl(const std::string& key);
        std::string type(const std::string& key);


    // Strings
    public:
        size_t append(const std::string& key, const std::string& value);
        size_t bitcount(const std::string& key, const int start, const int end);
        int decr(const std::string& key);
        int decrby(const std::string& key, const int amount);
        CppRedisClient::StringReply get(const std::string& key);
        size_t getbit(const std::string& key, const size_t offset);
        std::string getrange(const std::string& key, const int start, const int end);
        CppRedisClient::StringReply getset(const std::string& key, const std::string& value);
        int incr(const std::string& key);
        int incrby(const std::string& key, const int amount);
        std::string incrbyfloat(const std::string& key, const float amount);
        std::vector<CppRedisClient::StringReply> mget(const std::vector<std::string>& keys);
        void mset(const std::map<std::string, std::string>& kvMap);
        int msetnx(const std::map<std::string, std::string>& kvMap);
        void psetex(const std::string& key, const uint64_t milliseconds, const std::string& value);
        void set(const std::string& key, const std::string& value);
        size_t setbit(const std::string& key, const size_t offset, const size_t value);
        void setex(const std::string& key, const size_t ttl, const std::string& value);
        int setnx(const std::string& key, const std::string& value);
        size_t setrange(const std::string& key, const size_t offset, const std::string& value);
        size_t strlen(const std::string& key);

    // Hashs
    public:
        size_t hdel(const std::string& key, const std::string& field);
        size_t hdel(const std::string& key, const std::vector<std::string>& fields);
        size_t hexists(const std::string& key, const std::string& field);
        CppRedisClient::StringReply hget(const std::string& key, const std::string& field);
        std::map<std::string, std::string> hgetall(const std::string& key);
        int hincrby(const std::string& key, const std::string& field, const int amount);
        std::string hincrbyfloat(const std::string& key, const std::string& field, const float amount);
        std::vector<std::string> hkeys(const std::string& key);
        size_t hlen(const std::string& key);
        CppRedisClient::StringReply hmget(const std::string& key, const std::string& field);
        std::vector<CppRedisClient::StringReply> hmget(const std::string& key, const std::vector<std::string>& fields);
        void hmset(const std::string& key, const std::string& field, const std::string& value);
        void hmset(const std::string& key, const std::map<std::string, std::string>& fvMap);
        size_t hset(const std::string& key, const std::string& field, const std::string& value);
        size_t hsetnx(const std::string& key, const std::string& field, const std::string& value);
        std::vector<std::string> hvals(const std::string& key);

    // Lists
    public:
        CppRedisClient::StringReply lindex(const std::string& key, const int index);
        int linsert(const std::string& key, const CppRedisClient::LINSERT flag, const std::string& pivot,
                const std::string& value);
        size_t llen(const std::string& key);
        CppRedisClient::StringReply lpop(const std::string& key);
        size_t lpush(const std::string& key, const std::string& value);
        size_t lpush(const std::string& key, const std::vector<std::string>& values);
        size_t lpushx(const std::string& key, const std::string& value);
        std::vector<std::string> lrange(const std::string& key, const int start, const int stop);
        size_t lrem(const std::string& key, const int count, const std::string& value);
        void lset(const std::string& key, const int index, const std::string& value);
        void ltrim(const std::string& key, const int start, const int stop);
        CppRedisClient::StringReply rpop(const std::string& key);
        CppRedisClient::StringReply rpoplpush(const std::string& srcKey, const std::string& dstKey);
        size_t rpush(const std::string& key, const std::string& value);
        size_t rpush(const std::string& key, const std::vector<std::string>& values);
        size_t rpushx(const std::string& key, const std::string& value);

    // Sets
    public:
        size_t sadd(const std::string& key, const std::string& member);
        size_t sadd(const std::string& key, const std::vector<std::string>& members);
        size_t sadd(const std::string& key, const std::set<std::string>& members);
        size_t scard(const std::string& key);
        std::string sdiff(const std::string& key1, const std::string& key2);
        std::vector<std::string> sdiff(const std::string& key, const std::vector<std::string>& keys);
        size_t sdiffstore(const std::string& dstKey, const std::string& key1, const std::string& key2);
        size_t sdiffstore(const std::string& dstKey, const std::string& key, 
                const std::vector<std::string>& keys);
        std::string sinter(const std::string& key1, const std::string& key2);
        std::vector<std::string> sinter(const std::string& key, const std::vector<std::string>& keys);
        size_t sinterstore(const std::string& dstKey, const std::string& key1, const std::string& key2);
        size_t sinterstore(const std::string& dstKey, const std::string& key, 
                const std::vector<std::string>& keys);
        int sismember(const std::string& key, const std::string& member);
        std::vector<std::string> smembers(const std::string& key);
        int smove(const std::string& sourceKey, const std::string& dstKey, const std::string& member);
        CppRedisClient::StringReply spop(const std::string& key);
        CppRedisClient::StringReply srandmember(const std::string& key);
        std::vector<std::string> srandmember(const std::string& key, const int count);
        size_t srem(const std::string& key, const std::string& member);
        size_t srem(const std::string& key, const std::vector<std::string>& members);
        size_t srem(const std::string& key, const std::set<std::string>& members);
        std::string sunion(const std::string& key1, const std::string& key2);
        std::vector<std::string> sunion(const std::string& key, const std::vector<std::string>& keys);
        size_t sunionstore(const std::string& dstKey, const std::string& key1, const std::string& key2);
        size_t sunionstore(const std::string& dstKey, const std::string& key, 
                const std::vector<std::string>& keys);

    // Sorted Sets
    public:
        size_t zadd(const std::string& key, const int score, const std::string& member);
        size_t zcard(const std::string& key);
        size_t zcount(const std::string& key, const int min, const int max);
        std::string zincrby(const std::string& key, const int increment, const std::string& member);
        std::vector<std::string> zrange(const std::string& key, const int start, const int stop);
        std::vector<std::string> zrangebyscore(const std::string& key, const int min, const int max);
        CppRedisClient::StringReply zrank(const std::string& key, const std::string& member);
        size_t zrem(const std::string& key, const std::string& member);
        size_t zrem(const std::string& key, const std::vector<std::string>& members);
        size_t zremrangebyrank(const std::string& key, const int start, const int stop);
        size_t zremrangebyscore(const std::string& key, const int min, const int max);
        std::vector<std::string> zrevrange(const std::string& key, const int start, const int stop);
        std::vector<std::string> zrevrangebyscore(const std::string& key, const int max, const int min);
        CppRedisClient::StringReply zrevrank(const std::string& key, const std::string& member);
        CppRedisClient::StringReply zscore(const std::string& key, const std::string& member);

    // Connection
    public:
        bool auth(const std::string& password = "");
        CppRedisClient::StringReply echo(const std::string& message);
        bool ping();
        void quit();
        void select(const size_t index);



    private:
        void _redisConnect();
        boost::asio::ip::tcp::socket& _getRedisConnect();
        int handler(const char * response, const size_t len);
        size_t _getNumToStrLength(const int num) const;

        void _sendCommandToRedisServer(const std::string& cmd);
        void _sendCommandToRedisServer(const std::string& cmd, const size_t index);
        void _sendCommandToRedisServer(const std::string& cmd, const std::string& key);
        void _sendCommandToRedisServer(const std::string& cmd, const std::string& key, const int value);
        void _sendFloatCommandToRedisServer(const std::string& cmd, const std::string& key, const float value);
        void _sendCommandToRedisServer(const std::string& cmd, const std::string& key, const std::string& value);
        void _sendCommandToRedisServer(const std::string& cmd, const std::string& key, const int num,
                const std::string& value);
        void _sendCommandToRedisServer(const std::string& cmd, const std::string& key, const int start,
                const int end);
        void _sendCommandToRedisServer(const std::string& cmd, const std::vector<std::string>& keys);
        void _sendCommandToRedisServer(const std::string& cmd, const std::map<std::string, std::string>& kvMap);
        void _sendCommandToRedisServer(const std::string& cmd, const std::string& key,
                const std::map<std::string, std::string>& fvMap);
        void _sendCommandToRedisServer(const std::string& cmd, const std::string& key, 
                const std::vector<std::string>& fields);
        void _sendCommandToRedisServer(const std::string& cmd, const std::string& dstKey,
                const std::string& key, const std::vector<std::string>& keys);
        void _sendCommandToRedisServer(const std::string& cmd, const std::string& key,
                const std::set<std::string>& members);
        void _sendCommandToRedisServer(const std::string& cmd, const std::string& key, const std::string& field,
                const int amount);
        void _sendFloatCommandToRedisServer(const std::string& cmd, const std::string& key, 
                const std::string& field, const float amount);
        void _sendCommandToRedisServer(const std::string& cmd, const std::string& key, const std::string& field,
                const std::string& value);

        std::string _recvOneLine();
        std::string _test();
        std::string _readBulkResponse(const size_t n);
        boost::shared_ptr<char> _readBulkResponseToChar(const size_t n);
        std::string _readNBitByResponse(const size_t n);
        char _readResponseBeginByte();
        int _readResponseNum();
        int64_t _readResponseInt64_t();
        float _readResponseFloatNum();
        std::string _readResponseStr();
        size_t _getReadStreambufSize();

        // 整型数字，回复的第一个字节将是“:”
        size_t _getNumResponse();
        int64_t _getInt64_t_Response();

        // 浮点数
        float _getFloatNumResponse();
        
        // 用单行回复，回复的第一个字节将是“+”
        std::string _getOneLineResponse();

        // 批量回复（Bulk replies）
        int _getBulkResponse(std::string& response);
        boost::shared_ptr<char> _getBulkResponse(int& length);

        // 多批量回复（Multi-bulk replies）
        void _getMultiBulkResponse(std::vector<CppRedisClient::StringReply>& replys);
        void _getMultiBulkResponse(std::map<std::string, std::string>& replys);
        void _getMultiBulkResponse(std::vector<std::string>& replys);

    private:
        std::string _host;
        std::string _port;
        boost::asio::io_service _io_service;
        boost::asio::ip::tcp::socket *_psocket;
        boost::asio::streambuf data;
        boost::asio::streambuf _writeBuf;
        boost::asio::streambuf _readBuf;

    private:
        static boost::format ZERO_OPER_FORMAT;
        static boost::format ONE_OPER_FORMAT;
        static boost::format TWO_OPER_FORMAT;
        static boost::format THREE_OPER_FORMAT;
};

boost::format RedisClientImpl::ZERO_OPER_FORMAT("*1\r\n"\
        "$%1%\r\n"\
        "%2%\r\n");

boost::format RedisClientImpl::ONE_OPER_FORMAT("*2\r\n"\
        "$%1%\r\n"\
        "%2%\r\n"\
        "$%3%\r\n"\
        "%4%\r\n");

boost::format RedisClientImpl::TWO_OPER_FORMAT("*3\r\n"\
        "$%1%\r\n"\
        "%2%\r\n"\
        "$%3%\r\n"\
        "%4%\r\n"\
        "$%5%\r\n"\
        "%6%\r\n");


boost::format RedisClientImpl::THREE_OPER_FORMAT("*4\r\n"\
        "$%1%\r\n"\
        "%2%\r\n"\
        "$%3%\r\n"\
        "%4%\r\n"\
        "$%5%\r\n"\
        "%6%\r\n"\
        "$%7%\r\n"\
        "%8%\r\n");


RedisClientImpl::RedisClientImpl(const std::string& host, const std::string& port) :
    _host(host), _port(port), _psocket(0)
{
    // std::cout << "host : " << host << std::endl;
    // std::cout << "port : " << port << std::endl;
}

RedisClientImpl::~RedisClientImpl()
{
    // std::cout << "~RedisClientImpl" << std::endl;
    if (_psocket)
    {
        delete _psocket;
        _psocket = 0;
    }
}

void RedisClientImpl::_sendCommandToRedisServer(const std::string& cmd)
{
    boost::format f = RedisClientImpl::ZERO_OPER_FORMAT;
    f % cmd.size() % cmd;
    // const std::string buf = f.str();
    std::ostream os(&_writeBuf);
    os << f;

    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::write(socket, _writeBuf);
}

void RedisClientImpl::_sendCommandToRedisServer(const std::string& cmd, const size_t index)
{
    boost::format f = RedisClientImpl::ONE_OPER_FORMAT;
    const size_t indexLength = _getNumToStrLength(index);
    f % cmd.size() % cmd % indexLength % index;
    std::ostream os(&_writeBuf);
    os << f;
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::write(socket, _writeBuf);
}

void RedisClientImpl::_sendCommandToRedisServer(const std::string& cmd, const std::string& key)
{
    boost::format f = RedisClientImpl::ONE_OPER_FORMAT;
    f % cmd.size() % cmd % key.size() % key;
    // const std::string buf = f.str();
    std::ostream os(&_writeBuf);
    os << f;

    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::write(socket, _writeBuf);
}

void RedisClientImpl::_sendCommandToRedisServer(const std::string& cmd, const std::string& key, 
        const int value)
{
    boost::format f = RedisClientImpl::TWO_OPER_FORMAT;
    const size_t valueLength = _getNumToStrLength(value);
    f % cmd.size() % cmd % key.size() % key % valueLength % value;
    // const std::string buf = f.str();
    // std::cout << buf << std::endl;
    std::ostream os(&_writeBuf);
    os << f;

    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::write(socket, _writeBuf);
}

void RedisClientImpl::_sendFloatCommandToRedisServer(const std::string& cmd, const std::string& key,
        const float value)
{
    boost::format f = RedisClientImpl::TWO_OPER_FORMAT;
    const std::string valueStr = boost::lexical_cast<std::string>(value);
    f % cmd.size() % cmd % key.size() % key % valueStr.size() % valueStr;
    std::ostream os(&_writeBuf);
    os << f;
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::write(socket, _writeBuf);
}

void RedisClientImpl::_sendCommandToRedisServer(const std::string& cmd, const std::string& key,
        const std::string& value)
{
    boost::format f = RedisClientImpl::TWO_OPER_FORMAT;
    f % cmd.size() % cmd % key.size() % key % value.size() % value;
    // const std::string buf = f.str();
    std::ostream os(&_writeBuf);
    os << f;

    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::write(socket, _writeBuf);
}

void RedisClientImpl::_sendCommandToRedisServer(const std::string& cmd, const std::string& key, const int num,
        const std::string& value)
{
    boost::format f = RedisClientImpl::THREE_OPER_FORMAT;
    const size_t numLength = _getNumToStrLength(num);
    f % cmd.size() % cmd % key.size() % key % numLength % num % value.size() % value;
    // const std::string buf = f.str();
    std::ostream os(&_writeBuf);
    os << f;
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::write(socket, _writeBuf);
}

void RedisClientImpl::_sendCommandToRedisServer(const std::string& cmd, const std::string& key,
        const std::string& field, const std::string& value)
{
    boost::format f = RedisClientImpl::THREE_OPER_FORMAT;
    f % cmd.size() % cmd % key.size() % key % field.size() % field % value.size() % value;
    std::ostream os(&_writeBuf);
    os << f;
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::write(socket, _writeBuf);
}

void RedisClientImpl::_sendCommandToRedisServer(const std::string& cmd, const std::string& key, 
        const std::string& field, const int amount)
{
    boost::format f = RedisClientImpl::THREE_OPER_FORMAT;
    const size_t numLength = _getNumToStrLength(amount);
    f % cmd.size() % cmd % key.size() % key % field.size() % field % numLength % amount;
    std::ostream os(&_writeBuf);
    os << f;
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::write(socket, _writeBuf);
}

void RedisClientImpl::_sendFloatCommandToRedisServer(const std::string& cmd, const std::string& key,
        const std::string& field, const float amount)
{
    boost::format f = RedisClientImpl::THREE_OPER_FORMAT;
    std::string amountStr = boost::lexical_cast<std::string>(amount);
    f % cmd.size() % cmd % key.size() % key % field.size() % field % amountStr.size() % amountStr;
    std::ostream os(&_writeBuf);
    os << f;
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::write(socket, _writeBuf);
}

void RedisClientImpl::_sendCommandToRedisServer(const std::string& cmd, const std::string& key, const int start,
        const int end)
{
    boost::format f = RedisClientImpl::THREE_OPER_FORMAT;
    const size_t startLength = _getNumToStrLength(start);
    const size_t endLength = _getNumToStrLength(end);
    f % cmd.size() % cmd % key.size() % key % startLength % start % endLength % end;

    std::ostream os(&_writeBuf);
    os << f;
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::write(socket, _writeBuf);
}

void RedisClientImpl::_sendCommandToRedisServer(const std::string& cmd, const std::map<std::string, std::string>& kvMap)
{
    assert(kvMap.size() > 0);
    // std::string send("*%1%\r\n$%2%\r\n%3%\r\n");
    std::string send = "*" + boost::lexical_cast<std::string>(kvMap.size() * 2 + 1) + "\r\n" + 
        "$" + boost::lexical_cast<std::string>(cmd.size()) + "\r\n" +
        cmd + "\r\n";
    for (std::map<std::string, std::string>::const_iterator it = kvMap.begin(); it != kvMap.end(); ++it)
    {
        const std::string& key = it->first;
        const std::string& value = it->second;
        send += "$" + boost::lexical_cast<std::string>(key.size()) + "\r\n";
        send += key + "\r\n";
        send += "$" + boost::lexical_cast<std::string>(value.size()) + "\r\n";
        send += value + "\r\n";
    }
    // std::cout << send << std::endl;
    std::ostream os(&_writeBuf);
    os << send;
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::write(socket, _writeBuf);
}

void RedisClientImpl::_sendCommandToRedisServer(const std::string& cmd, const std::string& key,
        const std::map<std::string, std::string>& fvMap)
{
    assert(fvMap.size() > 0);
    std::string send = "*" + boost::lexical_cast<std::string>(fvMap.size() * 2 + 2) + "\r\n" +
        "$" + boost::lexical_cast<std::string>(cmd.size()) + "\r\n" +
        cmd + "\r\n" +
        "$" + boost::lexical_cast<std::string>(key.size()) + "\r\n" +
        key + "\r\n";
    for (std::map<std::string, std::string>::const_iterator it = fvMap.begin(); it != fvMap.end(); ++it)
    {
        const std::string& key = it->first;
        const std::string& value = it->second;
        send += "$" + boost::lexical_cast<std::string>(key.size()) + "\r\n";
        send += key + "\r\n";
        send += "$" + boost::lexical_cast<std::string>(value.size()) + "\r\n";
        send += value + "\r\n";
    }
    // std::cout << send << std::endl;
    std::ostream os(&_writeBuf);
    os << send;
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::write(socket, _writeBuf);
}

void RedisClientImpl::_sendCommandToRedisServer(const std::string& cmd, const std::vector<std::string>& keys)
{
    assert(keys.size() > 0);
    // std::string send("*%1%\r\n$%2%\r\n%3%\r\n");
    std::string send = "*" + boost::lexical_cast<std::string>(keys.size() + 1) + "\r\n" +
        "$" + boost::lexical_cast<std::string>(cmd.size()) + "\r\n" +
        cmd + "\r\n";
    for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
    {
        send += "$" + boost::lexical_cast<std::string>(it->size()) + "\r\n";
        send += (*it) + "\r\n";
    }
    // std::cout << send << std::endl;
    std::ostream os(&_writeBuf);
    os << send;
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::write(socket, _writeBuf);
}

void RedisClientImpl::_sendCommandToRedisServer(const std::string& cmd, const std::string& dstKey,
        const std::string& key, const std::vector<std::string>& keys)
{
    std::string send = "*" + boost::lexical_cast<std::string>(keys.size() + 3) + "\r\n" +
        "$" + boost::lexical_cast<std::string>(cmd.size()) + "\r\n" +
        cmd + "\r\n" +
        "$" + boost::lexical_cast<std::string>(dstKey.size()) + "\r\n" +
        dstKey + "\r\n" +
        "$" + boost::lexical_cast<std::string>(key.size()) + "\r\n" +
        key + "\r\n";
    for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
    {
        send += "$" + boost::lexical_cast<std::string>(it->size()) + "\r\n"; 
        send += (*it) + "\r\n";
    }
    std::ostream os(&_writeBuf);
    os << send;
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::write(socket, _writeBuf);
}

void RedisClientImpl::_sendCommandToRedisServer(const std::string& cmd, const std::string& key,
        const std::vector<std::string>& fields)
{
    assert(fields.size() > 0);
    std::string send = "*" + boost::lexical_cast<std::string>(fields.size() + 2) + "\r\n" +
        "$" + boost::lexical_cast<std::string>(cmd.size()) + "\r\n" +
        cmd + "\r\n" +
        "$" + boost::lexical_cast<std::string>(key.size()) + "\r\n" +
        key + "\r\n";
    for (std::vector<std::string>::const_iterator it = fields.begin(); it != fields.end(); ++it)
    {
        send += "$" + boost::lexical_cast<std::string>(it->size()) + "\r\n";
        send += (*it) + "\r\n";
    }
    std::ostream os(&_writeBuf);
    os << send;
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::write(socket, _writeBuf);
}

void RedisClientImpl::_sendCommandToRedisServer(const std::string& cmd, const std::string& key,
        const std::set<std::string>& members)
{
    assert(members.size() > 0);
    std::string send = "*" + boost::lexical_cast<std::string>(members.size() + 2) + "\r\n" +
        "$" + boost::lexical_cast<std::string>(cmd.size()) + "\r\n" +
        cmd + "\r\n" +
        "$" + boost::lexical_cast<std::string>(key.size()) + "\r\n" +
        key + "\r\n";
    for (std::set<std::string>::const_iterator it = members.begin(); it != members.end(); ++it)
    {
        send += "$" + boost::lexical_cast<std::string>(it->size()) + "\r\n";
        send += (*it) + "\r\n";
    }
    std::ostream os(&_writeBuf);
    os << send;
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::write(socket, _writeBuf);
}

void RedisClientImpl::_getMultiBulkResponse(std::vector<CppRedisClient::StringReply>& replys)
{
    const char c = _readResponseBeginByte();
    // std::cout << "c : " << c << std::endl;
    if (c == '*')
    {
        int num = _readResponseNum();
        // std::cout << "num : " << num << std::endl;
        if (num == -1)
            return;
        assert(num > 0);
        replys.resize(num);
        for (int i = 0; i < num; ++i)
        {
            int length = -1;
            boost::shared_ptr<char> buf = _getBulkResponse(length);
            replys[i] = CppRedisClient::StringReply(buf, length);
        }
    }
    else if (c == '-')
    {
        std::string error = _readResponseStr();
        throw std::runtime_error(error);
    }
    else
    {
        // _readBuf.consume(_readBuf.size());
        throw std::runtime_error("RedisClient Error");
    }
}

void RedisClientImpl::_getMultiBulkResponse(std::map<std::string, std::string>& replys)
{
    const char c = _readResponseBeginByte();
    if (c == '*')
    {
        int num = _readResponseNum();
        // std::cout << "num : " << num << std::endl;
        if (num == -1)
            return;
        assert(num > 0);
        for (int i = 0; i < num; i += 2)
        {
            std::string key;
            _getBulkResponse(key);
            std::string value;
            _getBulkResponse(value);
            replys[key] = value;
        }
    }
    else if (c == '-')
    {
        std::string error = _readResponseStr();
        throw std::runtime_error(error);
    }
    else
    {
        // _readBuf.consume(_readBuf.size());
        throw std::runtime_error("RedisClient Error");
    }
}

void RedisClientImpl::_getMultiBulkResponse(std::vector<std::string>& replys)
{
    const char c = _readResponseBeginByte();
    if (c == '*')
    {
        int num = _readResponseNum();
        // std::cout << "num : " << num << std::endl;
        if (num == -1)
            return;
        assert(num >= 0);
        replys.resize(num);
        for (int i = 0; i < num; ++i)
        {
            std::string key;
            _getBulkResponse(key);
            replys[i] = key;
        }
    }
    else if (c == '-')
    {
        std::string error = _readResponseStr();
        throw std::runtime_error(error);
    }
    else
    {
        // _readBuf.consume(_readBuf.size());
        throw std::runtime_error("RedisClient Error");
    }
}

// std::ostream& operator<<(std::ostream& os, std::vector<char>& v)
// {
    // for (std::vector<char>::iterator it = v.begin(); it != v.end(); ++it)
    // {
        // os << *it;
    // }
    // return os;
// }


boost::shared_ptr<char> RedisClientImpl::_readBulkResponseToChar(const size_t n)
{
    const size_t needReadByte = n + sizeof("\r\n") - 1;
    if (_getReadStreambufSize() < needReadByte)
    {
        const size_t remainByte = needReadByte - _getReadStreambufSize();
        boost::asio::ip::tcp::socket& socket = _getRedisConnect();
        boost::asio::read(socket, _readBuf, boost::asio::transfer_exactly(remainByte));
    }
    boost::shared_ptr<char> buf(new char[_getReadStreambufSize()]);
    boost::asio::streambuf::const_buffers_type data = _readBuf.data();
    // unsigned char* output = (unsigned char*)malloc(buf.size());
    std::copy(boost::asio::buffers_begin(data), boost::asio::buffers_end(data), buf.get());
    // memcpy(buf, boost::asio::buffer_cast<const void*>(_readBuf.data()), _readBuf.size());
    _readBuf.consume(needReadByte);
    return buf;
}


std::string RedisClientImpl::_readBulkResponse(const size_t n)
{
    const size_t needReadByte = n + sizeof("\r\n") - 1;
    // std::cout << needReadByte << std::endl;
    std::string response;
    if (_getReadStreambufSize() < needReadByte)
    {
        const size_t remainByte = needReadByte - _getReadStreambufSize();
        boost::asio::ip::tcp::socket& socket = _getRedisConnect();
        boost::asio::read(socket, _readBuf, boost::asio::transfer_exactly(remainByte));
    }
    response = make_string(_readBuf, n);
    _readBuf.consume(needReadByte);
    return response;
    // std::string response = _recvOneLine();
    // if (response.size() > 0)
    // {
        // if (response[0] == '$')
        // {
            // std::string len = response.substr(1, response.size() - 1);
            // const int _len = boost::lexical_cast<int>(len);
            // if (_len == -1)
                // return "";
            // // response = _recvOneLine();
            // response = _readNBitByResponse(_len);
            // std::cout << response << std::endl;
        // }
    // }
    // boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    // // 首先读第一个字节
    // boost::array<char, 128> buf;
    // size_t len = boost::asio::read(socket, boost::asio::buffer(buf, 1));
    // if (len)
    // {
        // if (buf[0] != '$')
        // {
            // std::cout << "error" << std::endl;
        // }
        // std::cout.write(buf.data(), len);
    // }
    // return "";
}

size_t RedisClientImpl::_getReadStreambufSize()
{
    return _readBuf.size();
}

std::string RedisClientImpl::_readNBitByResponse(const size_t n)
{
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    // boost::asio::read(socket, data, boost::asio::transfer_exactly(n));
    std::cout << "tt" << std::endl;
    std::cout << _readBuf.size() << std::endl;
    std::cout << &_readBuf << std::endl;
    return make_string(_readBuf);
}

char RedisClientImpl::_readResponseBeginByte()
{
    if (_readBuf.size() == 0)
    {
        boost::asio::ip::tcp::socket& socket = _getRedisConnect();
        boost::asio::read(socket, _readBuf, boost::asio::transfer_exactly(1));
    }
    std::istream ifs(&_readBuf);
    char c;
    ifs >> c;
    return c;
}

int RedisClientImpl::_readResponseNum()
{
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::read_until(socket, _readBuf, "\r\n");
    std::istream ifs(&_readBuf);
    std::string response;
    // 读取，默认以\n分隔
    std::getline(ifs, response);
    if (response.size() > 0)
    {
        // 去掉\r
        response.pop_back();
    }

    return boost::lexical_cast<int>(response);
}

int64_t RedisClientImpl::_readResponseInt64_t()
{
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::read_until(socket, _readBuf, "\r\n");
    std::istream ifs(&_readBuf);
    std::string response;
    // 读取，默认以\n分隔
    std::getline(ifs, response);
    if (response.size() > 0)
    {
        // 去掉\r
        response.pop_back();
    }

    return boost::lexical_cast<int64_t>(response);
}

float RedisClientImpl::_readResponseFloatNum()
{
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::read_until(socket, _readBuf, "\r\n");
    std::istream ifs(&_readBuf);
    std::string response;
    // 读取，默认以\n分隔
    std::getline(ifs, response);
    if (response.size() > 0)
    {
        // 去掉\r
        response.pop_back();
    }

    float num = boost::lexical_cast<float>(response);
    return num;
}

std::string RedisClientImpl::_recvOneLine()
{
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    // size_t len = boost::asio::read_until(socket, data, "\r\n");
    size_t len = boost::asio::read(socket, _readBuf, boost::asio::transfer_exactly(4));
    len = boost::asio::read(socket, _readBuf, boost::asio::transfer_exactly(3));
    // std::cout << "--------------" << std::endl;
    // std::cout << (&data) << std::endl;
    // std::cout << "--------------" << std::endl;
    std::istream ifs(&_readBuf);
    // ifs.unsetf(std::ios_base::skipws);
    std::string content;
    std::getline(ifs, content);
    content.pop_back();
    // std::cout << data.size() << std::endl;
    // ifs >> content;
    // std::cout << len << std::endl;
    // std::cout << content << std::endl;
    // std::cout << content.size() << std::endl;

    // std::cout << "--------------" << std::endl;
    // std::cout << (&data) << std::endl;
    // std::cout << "--------------" << std::endl;
    // len = boost::asio::read_until(socket, data, "\r\n");
    // std::getline(ifs, content);
    // content.pop_back();
    // // ifs >> content;
    // std::cout << len << std::endl;
    // std::cout << content << std::endl;
    // std::cout << content.size() << std::endl;

    return content;
}

void RedisClientImpl::_redisConnect()
{
    boost::asio::ip::tcp::resolver resolver(_io_service);
    boost::asio::ip::tcp::resolver::query query(_host, _port);
    boost::asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
    boost::asio::ip::tcp::resolver::iterator end;
    // while (iter != end)
    // {
        // boost::asio::ip::tcp::endpoint endpoint = *iter++;
        // std::cout << endpoint << std::endl;
    // }
    _psocket = new boost::asio::ip::tcp::socket(_io_service);
    boost::asio::connect(*_psocket, iter);
}

boost::asio::ip::tcp::socket& RedisClientImpl::_getRedisConnect()
{
    if (_psocket == 0)
        _redisConnect();

    return *_psocket;
}

size_t RedisClientImpl::_getNumToStrLength(const int num) const
{
    int _num = num;
    size_t length = 0;
    if (_num <= 0)
    {
        _num = -_num;
        length = 1;
    }
    while (_num)
    {
        ++length;
        _num = _num / 10;
    }
    return length;
}

std::string RedisClientImpl::_test()
{
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::array<char, 128> response;
    boost::system::error_code err_code;
    size_t len = socket.read_some(boost::asio::buffer(response), err_code);
    std::cout.write(response.data(), len);
    std::cout << len << std::endl;
    return "";
}


// 批量回复（Bulk replies）
boost::shared_ptr<char> RedisClientImpl::_getBulkResponse(int& length)
{
    const char c = _readResponseBeginByte();
    if (c == '$')
    {
        int num = _readResponseNum();
        if (num == -1)
        {
            // NULL
            length = -1;
            return boost::shared_ptr<char>();
        }
        else
        {
            assert(num >= 0);
            length = num;
            return _readBulkResponseToChar(num);
        }
    }
    else if (c == '-')
    {
    }
    else
    {
        throw std::runtime_error("RedisClient Error");
    }
    // boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    // boost::asio::read_until(socket, _readBuf, "\r\n");
    length = -1;
    return boost::shared_ptr<char>();
}


// 批量回复（Bulk replies）
// response和int作为返回的字符串和字符串长度,若如果请求的值不存在，response返回""，int返回-1
int RedisClientImpl::_getBulkResponse(std::string& response)
{
    // 读取第一个字节
    const char c = _readResponseBeginByte();
    std::string error;
    int num = 0;
    switch (c)
    {
        case '$':
            num = _readResponseNum();
            if (num == -1)
            {
                response = "";
                return -1;
            }
            else
            {
                assert(num >= 0);
                response = _readBulkResponse(num);
            }
            break;
        case '-':
            error = _readResponseStr();
            throw std::runtime_error(error);
            break;
        default:
            error = "RedisClient error";
            throw std::runtime_error(error);
            break;
    }
    return response.size();
}

// 单行回复
std::string RedisClientImpl::_getOneLineResponse()
{
    // 读取一个字节
    const char c = _readResponseBeginByte();
    std::string response;
    std::string error;
    // assert(c == '+');
    switch (c)
    {
        case '+':
            response = _readResponseStr();
            break;
        case '-':
            error = _readResponseStr();
            throw std::runtime_error(error);
            break;
        default:
            error = "RedisClient error";
            throw std::runtime_error(error);
            break;
    }
    return response;
}

// 回复的内容是一个整型数字
size_t RedisClientImpl::_getNumResponse()
{
    // 读取一个字节
    const char c = _readResponseBeginByte();
    int num = 0;
    std::string error;
    switch (c)
    {
        case ':':
            // 读取数字直到\r\n
            num = _readResponseNum();
            break;
        case '-':
            // 错误
            error = _readResponseStr();
            throw std::runtime_error(error);
            break;
        default:
            error = "RedisClient error";
            throw std::runtime_error(error);
            break;
    }
    // assert(c == ':');
    return num;
}

// 回复的内容是一个整型数字
int64_t RedisClientImpl::_getInt64_t_Response()
{
    // 读取一个字节
    const char c = _readResponseBeginByte();
    int64_t num = 0;
    std::string error;
    switch (c)
    {
        case ':':
            // 读取数字直到\r\n
            num = _readResponseInt64_t();
            break;
        case '-':
            // 错误
            error = _readResponseStr();
            throw std::runtime_error(error);
            break;
        default:
            error = "RedisClient error";
            throw std::runtime_error(error);
            break;
    }
    // assert(c == ':');
    return num;
}

float RedisClientImpl::_getFloatNumResponse()
{
    const char c = _readResponseBeginByte();
    std::cout << "c : " << c << std::endl;
    float num = 0;
    std::string error;
    switch (c)
    {
        case ':':
            // 读取数字直到\r\n
            num = _readResponseFloatNum();
            break;
        case '-':
            // 错误
            error = _readResponseStr();
            throw std::runtime_error(error);
            break;
        default:
            error = "RedisClient error";
            throw std::runtime_error(error);
            break;
    }
    return num;
}


std::string RedisClientImpl::_readResponseStr()
{
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::read_until(socket, _readBuf, "\r\n");
    std::istream ifs(&_readBuf);
    std::string response;
    std::getline(ifs, response);
    if (response.size() > 0)
    {
        response.pop_back();
    }
    return response;
}


/* Keys ---------------------------------------------------------------------*/

/**
 * @brief 删除key，如果key不存在，则忽略
 *
 * @param key 需要删除的key
 *
 * @return 被删除的key数量
 */
size_t RedisClientImpl::del(const std::string& key)
{
    _sendCommandToRedisServer("DEL", key);
    return _getNumResponse();
}

/**
 * @brief 删除key，如果key不存在，则忽略
 *
 * @param keys 需要删除的keys
 *
 * @return 被删除的key数量
 */
size_t RedisClientImpl::del(const std::vector<std::string>& keys)
{
    _sendCommandToRedisServer("DEL", keys);
    return _getNumResponse();
}

/**
 * @brief 序列化给定key ，如果key不存在，返回的StringReply为NULL
 *
 * @param key 待序列号的key
 *
 * @return 被序列化的值
 */
CppRedisClient::StringReply RedisClientImpl::dump(const std::string& key)
{
    _sendCommandToRedisServer("DUMP", key);
    int length = 0;
    boost::shared_ptr<char> buf = _getBulkResponse(length);
    return CppRedisClient::StringReply(buf, length);
}

/**
 * @brief 判断key是否存在
 *
 * @param key 待判断的key
 *
 * @return 
 *      * 1 key存在 
 *      * 0 key不存在
 */
int RedisClientImpl::exists(const std::string& key)
{
    _sendCommandToRedisServer("EXISTS", key);
    int response = _getNumResponse();
    return response;
}

/**
 * @brief 设置指定key的过期时间
 *
 * @param key 指定的key
 * @param seconds 过期时间(s)
 *
 * @return 
 *      * 1 成功设置过期时间
 *      * 0 设置失败(key不存在或者不允许设置过期时间)
 */
int RedisClientImpl::expire(const std::string& key, const size_t seconds)
{
    _sendCommandToRedisServer("EXPIRE", key, seconds);
    int response = _getNumResponse();
    return response;
}

/**
 * @brief 设置key的过期时间，与expire不同的是，时间参数是unix时间戳
 *
 * @param key 指定的key
 * @param when 过期时间(unix时间戳)
 *
 * @return 
 *      * 1 成功设置过期时间
 *      * 0 设置失败(key不存在或者不允许设置过期时间)
 */
size_t RedisClientImpl::expireat(const std::string& key, const size_t when)
{
    _sendCommandToRedisServer("EXPIREAT", key, when);
    return _getNumResponse();
}

/**
 * @brief 查找符合模式的pattern的keys
 *
 * @param pattern 正则表达式
 *
 * @return 符合条件的keys
 */
std::vector<std::string> RedisClientImpl::keys(const std::string& pattern)
{
    _sendCommandToRedisServer("KEYS", pattern);
    std::vector<std::string> replys;
    _getMultiBulkResponse(replys);
    return replys;
}

/**
 * @brief 移动key到指定的db中
 *
 * @param key 移动的key
 * @param db 指定的db
 *
 * @return 
 *      * 1 移动成功
 *      * 0 移动失败
 */
int RedisClientImpl::move(const std::string& key, const size_t db)
{
    _sendCommandToRedisServer("MOVE", key, db);
    int response = _getNumResponse();
    return response;
}

/**
 * @brief 返回keys的内部对象
 *
 * @param subCommand
 *              * REFCOUNT 返回key对应value被引用的次数
 *              * ENCODING 返回key对应value内部的实现表示
 *              * IDLETIME 返回key对应value被存储之后空闲的时间，以秒为单位(没有读写操作的请求) ，
 *                          这个值返回以10秒为单位的秒级别时间，这一点可能在以后的实现中改善
 * @param key 待返回的key
 *
 * @return 根据subComand的值返回对应的数据
 */
CppRedisClient::StringReply RedisClientImpl::object(const CppRedisClient::OBJECT_SUBCOMMAND subCommand,
        const std::string& key)
{
    // * Subcommands refcount and idletime return integers.
    // * Subcommand encoding returns a bulk reply.
    if (subCommand == ENCODING)
    {
        _sendCommandToRedisServer("OBJECT", "ENCODING", key);
        int length = -1;
        boost::shared_ptr<char> buf = _getBulkResponse(length);
        return CppRedisClient::StringReply(buf, length);
    }
    else if (subCommand == REFCOUNT)
    {
        _sendCommandToRedisServer("OBJECT", "REFCOUNT", key);
        const int num = _getNumResponse();
        // int to string
        return CppRedisClient::StringReply(boost::lexical_cast<std::string>(num));
    }
    else if (subCommand == IDLETIME)
    {
        _sendCommandToRedisServer("OBJECT", "IDLETIME", key);
        const int num = _getNumResponse();
        // int to string
        return CppRedisClient::StringReply(boost::lexical_cast<std::string>(num));
    }
    else
    {
        throw std::runtime_error("CppRedisClient::OBJECT_SUBCOMMAND subCommand args error!");
    }
}

/**
 * @brief 移除key的过期时间
 *
 * @param key 指定的key
 *
 * @return 
 *      * 1 移除成功
 *      * 0 移除失败(key不存在或者key没有设置过期时间)
 */
int RedisClientImpl::persist(const std::string& key)
{
    _sendCommandToRedisServer("PERSIST", key);
    int response = _getNumResponse();
    return response;
}

/**
 * @brief 设置key的过期时间，与expire不同的是，时间以毫秒为单位
 *
 * @param key 指定的key
 * @param milliseconds 过期时间(ms)
 *
 * @return 
 *      * 1 设置成功
 *      * 0 设置失败(key不存在或者不允许设置过期时间)
 */
int RedisClientImpl::pexpire(const std::string& key, const uint64_t milliseconds)
{
    const std::string millisecondsStr = boost::lexical_cast<std::string>(milliseconds);
    _sendCommandToRedisServer("PEXPIRE", key, millisecondsStr);
    int response = _getNumResponse();
    return response;
}

/**
 * @brief 设置key的过期时间，时间是unix时间戳，以毫秒为单位
 *
 * @param key 指定的key
 * @param when unix时间戳(ms)
 *
 * @return 
 *      * 1 设置成功
 *      * 0 设置失败(key不存在或者不允许设置过期时间)
 */
int RedisClientImpl::pexpireat(const std::string& key, const uint64_t when)
{
    const std::string whenStr = boost::lexical_cast<std::string>(when);
    _sendCommandToRedisServer("PEXPIREAT", key, whenStr);
    return _getNumResponse();
}

/**
 * @brief 返回key的过期时间，与ttl类似，不同的是返回的时间单位是毫秒
 *
 * @param key 指定的key
 *
 * @return key的过期时间(ms)
 */
int64_t RedisClientImpl::pttl(const std::string& key)
{
    _sendCommandToRedisServer("PTTL", key);
    int64_t response = _getInt64_t_Response();
    return response;
}

/**
 * @brief 返回随机的key
 *
 * @return 随机的key
 */
CppRedisClient::StringReply RedisClientImpl::randomkey()
{
    _sendCommandToRedisServer("RANDOMKEY");
    int length = 0;
    boost::shared_ptr<char> buf = _getBulkResponse(length);
    return CppRedisClient::StringReply(buf, length);
}

/**
 * @brief 对key重命名
 *
 * @param srcKey 源key
 * @param dstKey 目标key
 */
void RedisClientImpl::rename(const std::string& srcKey, const std::string& dstKey)
{
    _sendCommandToRedisServer("RENAME", srcKey, dstKey);
    _getOneLineResponse();
}

/**
 * @brief 当dstKey不存在时，将srcKey重命名为dstKey，当dstKey存在时，返回错误
 *
 * @param srcKey 源key
 * @param dstKey 目标key
 *
 * @return
 *      * 1 修改成功
 *      * 0 修改失败(dstKey已经存在)
 */
int RedisClientImpl::renamenx(const std::string& srcKey, const std::string& dstKey)
{
    _sendCommandToRedisServer("RENAMENX", srcKey, dstKey);
    int response = _getNumResponse();
    return response;
}

/**
 * @brief 返回key的过期时间，与pttl类似，不同的是返回的时间单位是秒
 *
 * @param key 指定的key
 *
 * @return key的过期时间(s)
 */
int RedisClientImpl::ttl(const std::string& key)
{
    _sendCommandToRedisServer("TTL", key);
    int response = _getNumResponse();
    return response;
}

/**
 * @brief 返回key对应的value数据结构类型
 *
 * @param key 指定的key
 *
 * @return 对应的数据类型
 */
std::string RedisClientImpl::type(const std::string& key)
{
    _sendCommandToRedisServer("TYPE", key);
    return _getOneLineResponse();
}

/* Keys End -----------------------------------------------------------------*/


/* Strings ------------------------------------------------------------------*/

/**
 * @brief 字符串连接，若key不存在，则创建一个"“字符串再执行操作
 *
 * @param key 指定的key
 * @param value 追加的字符串
 *
 * @return 返回append后的字符串长度
 */
size_t RedisClientImpl::append(const std::string& key, const std::string& value)
{
    // send command to redis server
    _sendCommandToRedisServer("APPEND", key, value);
    // receive response
    const size_t num = _getNumResponse();
    return num;
}

/**
 * @brief 获取key对应的value的bit为1数量
 *
 * @param key 指定的key
 * @param start 开始位置
 * @param end 结束位置
 *
 * @return bit为1的数量
 */
size_t RedisClientImpl::bitcount(const std::string& key, const int start, const int end)
{
    _sendCommandToRedisServer("BITCOUNT", key, start, end);
    return _getNumResponse();
}

/**
 * @brief 将key对应的数字减1
 *
 * @param key 指定的key
 *
 * @return 减少之后的value
 */
int RedisClientImpl::decr(const std::string& key)
{
    _sendCommandToRedisServer("DECR", key);
    int response = _getNumResponse();
    return response;
}

/**
 * @brief 将key对应的数字减amount
 *
 * @param key 指定的key
 * @param amount 减少的数
 *
 * @return 减少之后的value
 */
int RedisClientImpl::decrby(const std::string& key, const int amount)
{
    _sendCommandToRedisServer("DECRBY", key, amount);
    int response = _getNumResponse();
    return response;
}

/**
 * @brief 返回key对应的value
 *
 * @param key 指定的key
 *
 * @return key对应的value
 */
CppRedisClient::StringReply RedisClientImpl::get(const std::string& key)
{
    _sendCommandToRedisServer("GET", key);
    int length = -1;
    boost::shared_ptr<char> buf = _getBulkResponse(length);
    return CppRedisClient::StringReply(buf, length);
}

/**
 * @brief 返回key对应的string在offset处的bit值
 *
 * @param key 指定的key
 * @param offset 偏移位置
 *
 * @return 在offset处的bit值
 */
size_t RedisClientImpl::getbit(const std::string& key, const size_t offset)
{
    _sendCommandToRedisServer("GETBIT", key, offset);
    size_t response = _getNumResponse();
    return response;
}

/**
 * @brief 返回key对应的value的子串
 *
 * @param key 指定的key
 * @param start 开始位置
 * @param end 结束位置
 *
 * @return 子字符串
 */
std::string RedisClientImpl::getrange(const std::string& key, const int start, const int end)
{
    _sendCommandToRedisServer("GETRANGE", key, start, end);
    std::string response;
    _getBulkResponse(response);
    return response;
}

/**
 * @brief 设置key的value并且返回旧的value
 *
 * @param key 指定的key
 * @param value 指定的value
 *
 * @return 旧的value
 */
CppRedisClient::StringReply RedisClientImpl::getset(const std::string& key, const std::string& value)
{
    _sendCommandToRedisServer("GETSET", key, value);
    int length = -1;
    boost::shared_ptr<char> buf = _getBulkResponse(length);
    return CppRedisClient::StringReply(buf, length);
}

/**
 * @brief key对应的value加1
 *
 * @param key 指定的key
 *
 * @return 递增后的value
 */
int RedisClientImpl::incr(const std::string& key)
{
    _sendCommandToRedisServer("INCR", key);
    int response = _getNumResponse();
    return response;
}

/**
 * @brief key对应的value加amount
 *
 * @param key 指定的key
 * @param amount 增加的数
 *
 * @return 增加后的value
 */
int RedisClientImpl::incrby(const std::string& key, const int amount)
{
    _sendCommandToRedisServer("INCRBY", key, amount);
    int response = _getNumResponse();
    return response;
}

/**
 * @brief key对应的value加amount
 *
 * @param key 指定的key
 * @param amount 增加的数
 *
 * @return 增加后的value
 */
std::string RedisClientImpl::incrbyfloat(const std::string& key, const float amount)
{
    _sendFloatCommandToRedisServer("INCRBYFLOAT", key, amount);
    std::string response;
    _getBulkResponse(response);
    return response;
}

/**
 * @brief 返回所有指定key对应的value
 *
 * @param keys 指定的keys
 *
 * @return keys对应的values
 */
std::vector<CppRedisClient::StringReply> RedisClientImpl::mget(const std::vector<std::string>& keys)
{
    _sendCommandToRedisServer("MGET", keys);
    std::vector<CppRedisClient::StringReply> replys;
    _getMultiBulkResponse(replys);
    return replys;
}

/**
 * @brief 设置给定的keys对应的values
 *
 * @param kvMap key-value字典
 */
void RedisClientImpl::mset(const std::map<std::string, std::string>& kvMap)
{
    _sendCommandToRedisServer("MSET", kvMap);
    std::string response = _getOneLineResponse();
    assert(response == "OK");
    return; 
}

/**
 * @brief 和mset类似，不同的是msetnx当其中一个(或以上)key已经存在时不执行
 *
 * @param kvMap key-value字典
 *
 * @return 
 *      * 1 设置成功(所有key设置为对应的value)
 *      * 0 设置失败(没有key被设置)
 */
int RedisClientImpl::msetnx(const std::map<std::string, std::string>& kvMap)
{
    _sendCommandToRedisServer("MSETNX", kvMap);
    return _getNumResponse();
}

/**
 * @brief 与setex类似，不同的是过期时间以毫秒为单位
 *
 * @param key 指定的key
 * @param milliseconds 过期时间(ms)
 * @param value 指定的value
 */
void RedisClientImpl::psetex(const std::string& key, const uint64_t milliseconds, const std::string& value)
{
    std::string millisecondsStr = boost::lexical_cast<std::string>(milliseconds);
    _sendCommandToRedisServer("PSETEX", key, millisecondsStr, value);
    std::string response = _getOneLineResponse();
    assert(response == "OK");
    return; 
}

/**
 * @brief 设置key对应的value
 *
 * @param key 指定的key
 * @param value 指定的value
 */
void RedisClientImpl::set(const std::string& key, const std::string& value)
{
    _sendCommandToRedisServer("SET", key, value);
    std::string response = _getOneLineResponse();
    assert(response == "OK");
}

/**
 * @brief 设置key的value在offset处的bit值
 *
 * @param key 指定的key
 * @param offset 偏移位置
 * @param value bit值(0/1)
 *
 * @return 在offset处原来的bit值
 */
size_t RedisClientImpl::setbit(const std::string& key, const size_t offset, const size_t value)
{
    assert(value == 0 || value == 1);
    _sendCommandToRedisServer("SETBIT", key, offset, value);
    return _getNumResponse();
}

/**
 * @brief 设置key对应的value，并且设置过期时间
 *
 * @param key 指定的key
 * @param ttl 过期时间(s)
 * @param value 指定的value
 */
void RedisClientImpl::setex(const std::string& key, const size_t ttl, const std::string& value)
{
    _sendCommandToRedisServer("SETEX", key, ttl, value);
    std::string response = _getOneLineResponse();
    assert(response == "OK");
}

/**
 * @brief 设置key对应的value，当key已经存在时，忽略该操作
 *
 * @param key 指定的key
 * @param value 指定的value
 *
 * @return
 *      * 1 设置成功
 *      * 0 设置失败(key已经存在)
 */
int RedisClientImpl::setnx(const std::string& key, const std::string& value)
{
    _sendCommandToRedisServer("SETNX", key, value);
    int response = _getNumResponse();
    return response;
}

/**
 * @brief 修改key对应的value的子字符串
 *
 * @param key 指定的key
 * @param offset 偏移位置
 * @param value 指定的value
 *
 * @return 修改后的字符串长度
 */
size_t RedisClientImpl::setrange(const std::string& key, const size_t offset, const std::string& value)
{
    _sendCommandToRedisServer("SETRANGE", key, offset, value);
    return _getNumResponse();
}

/**
 * @brief 返回key对应的value(字符串)的长度
 *
 * @param key 指定的key
 *
 * @return 字符串长度
 */
size_t RedisClientImpl::strlen(const std::string& key)
{
    _sendCommandToRedisServer("STRLEN", key);
    size_t response = _getNumResponse();
    return response;
}

/* Strings End ---------------------------------------------------------------*/


/* Hashs ---------------------------------------------------------------------*/

/**
 * @brief 删除key指定的field
 *
 * @param key 指定的key
 * @param field 指定的field
 *
 * @return 删除的field数量
 */
size_t RedisClientImpl::hdel(const std::string& key, const std::string& field)
{
    _sendCommandToRedisServer("HDEL", key, field);
    return _getNumResponse();
}

/**
 * @brief 删除key指定的fields
 *
 * @param key 指定的key
 * @param fields 指定的fields
 *
 * @return 删除的field数量
 */
size_t RedisClientImpl::hdel(const std::string& key, const std::vector<std::string>& fields)
{
    _sendCommandToRedisServer("HDEL", key, fields);
    return _getNumResponse();
}

/**
 * @brief 返回hash里面key是否存在field
 *
 * @param key 指定的key
 * @param field 指定的value
 *
 * @return 
 *      * 1 存在
 *      * 0 不存在
 */
size_t RedisClientImpl::hexists(const std::string& key, const std::string& field)
{
    _sendCommandToRedisServer("HEXISTS", key, field);
    return _getNumResponse();
}

/**
 * @brief 返回key对应field的value
 *
 * @param key 指定的key
 * @param field 指定的field
 *
 * @return 对应的value
 */
CppRedisClient::StringReply RedisClientImpl::hget(const std::string& key, const std::string& field)
{
    _sendCommandToRedisServer("HGET", key, field);
    int length = -1;
    boost::shared_ptr<char> buf = _getBulkResponse(length);
    return CppRedisClient::StringReply(buf, length);
}

/**
 * @brief 返回key对应的所有field-value
 *
 * @param key 指定的key
 *
 * @return key对应的所有field-value
 */
std::map<std::string, std::string> RedisClientImpl::hgetall(const std::string& key)
{
    _sendCommandToRedisServer("HGETALL", key);
    std::map<std::string, std::string> replys;
    _getMultiBulkResponse(replys);
    return replys;
}

/**
 * @brief 增加key-field的值
 *
 * @param key 指定的key
 * @param field 指定的field
 * @param amount 增加的数
 *
 * @return 增加后的值
 */
int RedisClientImpl::hincrby(const std::string& key, const std::string& field, const int amount)
{
    _sendCommandToRedisServer("HINCRBY", key, field, amount);
    return _getNumResponse();
}

/**
 * @brief 增加key-field的值
 *
 * @param key 指定的key
 * @param field 指定的field
 * @param amount 增加的数
 *
 * @return 增加后的值
 */
std::string RedisClientImpl::hincrbyfloat(const std::string& key, const std::string& field, const float amount)
{
    _sendFloatCommandToRedisServer("HINCRBYFLOAT", key, field, amount);
    std::string response;
    _getBulkResponse(response);
    return response;
}

/**
 * @brief 返回指定key的所有fields
 *
 * @param key 指定的key
 *
 * @return 对应的fields
 */
std::vector<std::string> RedisClientImpl::hkeys(const std::string& key)
{
    _sendCommandToRedisServer("HKEYS", key);
    std::vector<std::string> replys;
    _getMultiBulkResponse(replys);
    return replys;
}

/**
 * @brief 返回指定key中field的数量
 *
 * @param key 指定的key
 *
 * @return field的数量
 */
size_t RedisClientImpl::hlen(const std::string& key)
{
    _sendCommandToRedisServer("HLEN", key);
    return _getNumResponse();
}

/**
 * @brief 返回key-field对应的value
 *
 * @param key 指定的key
 * @param field 指定的value
 *
 * @return 对应的value
 */
CppRedisClient::StringReply RedisClientImpl::hmget(const std::string& key, const std::string& field)
{
    _sendCommandToRedisServer("HMGET", key, field);
    // int length = -1;
    // boost::shared_ptr<char> buf = _getBulkResponse(length);
    std::vector<CppRedisClient::StringReply> replys;
    _getMultiBulkResponse(replys);
    assert(replys.size() == 1);
    return replys[0];
}

/**
 * @brief 返回key-field对应的value
 *
 * @param key 指定的key
 * @param fields 指定的fields
 *
 * @return 对应的values
 */
std::vector<CppRedisClient::StringReply> RedisClientImpl::hmget(const std::string& key, 
        const std::vector<std::string>& fields)
{
    _sendCommandToRedisServer("HMGET", key, fields);
    std::vector<CppRedisClient::StringReply> replys;
    _getMultiBulkResponse(replys);
    return replys;
}

/**
 * @brief 设置key-field的value
 *
 * @param key 指定的key
 * @param field 指定的field
 * @param value 指定的value
 */
void RedisClientImpl::hmset(const std::string& key, const std::string& field, const std::string& value)
{
    _sendCommandToRedisServer("HMSET", key, field, value);
    std::string response = _getOneLineResponse();
    assert(response == "OK");
    return; 
}

/**
 * @brief 设置key-field的value
 *
 * @param key 指定的key
 * @param fvMap field-value字典
 */
void RedisClientImpl::hmset(const std::string& key, const std::map<std::string, std::string>& fvMap)
{
    _sendCommandToRedisServer("HMSET", key, fvMap);
    std::string response = _getOneLineResponse();
    assert(response == "OK");
    return; 
}

/**
 * @brief 设置key-field的value
 *
 * @param key 指定的key
 * @param field 指定的field
 * @param value 指定的value
 *
 * @return 
 *      * 1 如果field是一个新的字段
 *      * 0 如果field原来在map里面已经存在
 */
size_t RedisClientImpl::hset(const std::string& key, const std::string& field, const std::string& value)
{
    _sendCommandToRedisServer("HSET", key, field, value);
    return _getNumResponse();
}

/**
 * @brief 设置key-field的value
 *
 * @param key 指定的key
 * @param field 指定的field
 * @param value 指定的value
 *
 * @return 
 *      * 1 如果字段是个新的字段，并成功赋值
 *      * 0 如果哈希集中已存在该字段，没有操作被执行
 */
size_t RedisClientImpl::hsetnx(const std::string& key, const std::string& field, const std::string& value)
{
    _sendCommandToRedisServer("HSETNX", key, field, value);
    return _getNumResponse();
}

/**
 * @brief 返回指定key对应的所有fields的值
 *
 * @param key 指定的key
 *
 * @return 所有的value
 */
std::vector<std::string> RedisClientImpl::hvals(const std::string& key)
{
    _sendCommandToRedisServer("HVALS", key);
    std::vector<std::string> replys;
    _getMultiBulkResponse(replys);
    return replys;
}

/* Hashs End ----------------------------------------------------------------*/


/* Lists --------------------------------------------------------------------*/

/**
 * @brief 返回list中index位置元素的值
 *
 * @param key 指定的key
 * @param index 指定的位置
 *
 * @return 对应元素的值
 */
CppRedisClient::StringReply RedisClientImpl::lindex(const std::string& key, const int index)
{
    _sendCommandToRedisServer("LINDEX", key, index);
    int length = -1;
    boost::shared_ptr<char> buf = _getBulkResponse(length);
    return CppRedisClient::StringReply(buf, length);
}

/**
 * @brief 把value插入存于key的list中在基准值pivot的前面或后面 
 *
 * @param key 指定的key
 * @param flag 指示前面还是后面
 * @param pivot 基准值
 * @param value 插入的值
 *
 * @return 经过插入操作后的list长度，或者当pivot值找不到的时候返回-1
 */
int RedisClientImpl::linsert(const std::string& key, const CppRedisClient::LINSERT flag,
        const std::string& pivot, const std::string& value)
{
    std::string flagStr;
    if (flag == BEFORE)
        flagStr = "BEFORE";
    else if (flag == AFTER)
        flagStr = "AFTER";
    else
        throw std::runtime_error("CppRedisClient::LINSERT flag args error!");

    std::vector<std::string> args;
    args.push_back(key);
    args.push_back(flagStr);
    args.push_back(pivot);
    args.push_back(value);
    _sendCommandToRedisServer("LINSERT", args);
    return _getNumResponse();
}

/**
 * @brief 返回list的长度
 *
 * @param key 指定的key
 *
 * @return list的长度
 */
size_t RedisClientImpl::llen(const std::string& key)
{
    _sendCommandToRedisServer("LLEN", key);
    size_t response = _getNumResponse();
    return response;
}

/**
 * @brief 返回list中的第一个元素
 *
 * @param key 指定的key
 *
 * @return 第一个元素的值
 */
CppRedisClient::StringReply RedisClientImpl::lpop(const std::string& key)
{
    _sendCommandToRedisServer("LPOP", key);
    int length = -1;
    boost::shared_ptr<char> buf = _getBulkResponse(length);
    return CppRedisClient::StringReply(buf, length);
}

/**
 * @brief 将value插入到list的头部
 *
 * @param key 指定的key
 * @param value 指定的value
 *
 * @return 操作后list的长度
 */
size_t RedisClientImpl::lpush(const std::string& key, const std::string& value)
{
    _sendCommandToRedisServer("LPUSH", key, value);
    return _getNumResponse();
}

/**
 * @brief 将values插入到list的头部
 *
 * @param key 指定的key
 * @param values 指定的values
 *
 * @return 操作后list的长度
 */
size_t RedisClientImpl::lpush(const std::string& key, const std::vector<std::string>& values)
{
    _sendCommandToRedisServer("LPUSH", key, values);
    return _getNumResponse();
}

/**
 * @brief 当且仅当key存在时将value插入到list的头部
 *
 * @param key 指定的key
 * @param value 指定的value
 *
 * @return 操作后list的长度
 */
size_t RedisClientImpl::lpushx(const std::string& key, const std::string& value)
{
    _sendCommandToRedisServer("LPUSHX", key, value);
    return _getNumResponse();
}

/**
 * @brief 返回list中对应范围内的元素
 *
 * @param key 指定的key
 * @param start 开始位置
 * @param stop 结束位置
 *
 * @return 范围内的元素值
 */
std::vector<std::string> RedisClientImpl::lrange(const std::string& key, const int start, const int stop)
{
    _sendCommandToRedisServer("LRANGE", key, start, stop);
    std::vector<std::string> replys;
    _getMultiBulkResponse(replys);
    return replys;
}

/**
 * @brief 从存于key的list里移除前count次出现的值为value的元素
 *
 * @param key 指定的key
 * @param count
 *          * count > 0 : 从头往尾移除值为value的元素。
 *          * count < 0 : 从尾往头移除值为value的元素。
 *          * count = 0 : 移除所有值为value的元素。
 * @param value 指定的value
 *
 * @return 被移除的元素个数
 */
size_t RedisClientImpl::lrem(const std::string& key, const int count, const std::string& value)
{
    _sendCommandToRedisServer("LREM", key, count, value);
    return _getNumResponse();
}

/**
 * @brief 设置list中index位置元素的值为value
 *
 * @param key 指定的key
 * @param index 元素位置
 * @param value 指定的value
 */
void RedisClientImpl::lset(const std::string& key, const int index, const std::string& value)
{
    _sendCommandToRedisServer("LSET", key, index, value);
    std::string response = _getOneLineResponse();
    assert(response == "OK");
    return; 
}

/**
 * @brief 修改一个已存在的list的范围
 *
 * @param key 指定的key
 * @param start 开始位置
 * @param stop 结束位置
 */
void RedisClientImpl::ltrim(const std::string& key, const int start, const int stop)
{
    _sendCommandToRedisServer("LTRIM", key, start, stop);
    std::string response = _getOneLineResponse();
    assert(response == "OK");
    return; 
}

/**
 * @brief 移除并返回存于key的list的最后一个元素
 *
 * @param key 指定的key
 *
 * @return list中的最后一个元素
 */
CppRedisClient::StringReply RedisClientImpl::rpop(const std::string& key)
{
    _sendCommandToRedisServer("RPOP", key);
    int length = -1;
    boost::shared_ptr<char> buf = _getBulkResponse(length);
    return CppRedisClient::StringReply(buf, length);
}

/**
 * @brief 将list中最后一个元素移除并插入到另一list头部中
 *
 * @param srcKey 源key
 * @param dstKey 目标key
 *
 * @return 被删除和插入的元素
 */
CppRedisClient::StringReply RedisClientImpl::rpoplpush(const std::string& srcKey, const std::string& dstKey)
{
    _sendCommandToRedisServer("RPOPLPUSH", srcKey, dstKey);
    int length = -1;
    boost::shared_ptr<char> buf = _getBulkResponse(length);
    return CppRedisClient::StringReply(buf, length);
}

/**
 * @brief 从list尾部中插入value元素
 *
 * @param key 指定的key
 * @param value 指定的value
 *
 * @return 操作后list的长度
 */
size_t RedisClientImpl::rpush(const std::string& key, const std::string& value)
{
    _sendCommandToRedisServer("RPUSH", key, value);
    return _getNumResponse();
}

/**
 * @brief 从list尾部中插入values元素
 *
 * @param key 指定的key
 * @param values 指定的values
 *
 * @return 操作后list的长度
 */
size_t RedisClientImpl::rpush(const std::string& key, const std::vector<std::string>& values)
{
    _sendCommandToRedisServer("RPUSH", key, values);
    return _getNumResponse();
}

/**
 * @brief 当且仅当key存在并且是list时将value插入到尾部
 *
 * @param key 指定的key
 * @param value 指定的value
 *
 * @return 操作后list的长度
 */
size_t RedisClientImpl::rpushx(const std::string& key, const std::string& value)
{
    _sendCommandToRedisServer("RPUSHX", key, value);
    return _getNumResponse();
}

/* Lists End ----------------------------------------------------------------*/


/* Sets ---------------------------------------------------------------------*/

/**
 * @brief 添加member元素到集合中
 *
 * @param key 指定的key
 * @param member 指定的member
 *
 * @return 成功添加到集合里元素的数量
 */
size_t RedisClientImpl::sadd(const std::string& key, const std::string& member)
{
    _sendCommandToRedisServer("SADD", key, member);
    return _getNumResponse();
}

/**
 * @brief 添加members元素到集合中
 *
 * @param key 指定的key
 * @param members 指定的members
 *
 * @return 成功添加到集合里元素的数量
 */
size_t RedisClientImpl::sadd(const std::string& key, const std::vector<std::string>& members)
{
    _sendCommandToRedisServer("SADD", key, members);
    return _getNumResponse();
}

/**
 * @brief 添加members元素到集合中
 *
 * @param key 指定的key
 * @param members 指定的members
 *
 * @return 成功添加到集合里元素的数量
 */
size_t RedisClientImpl::sadd(const std::string& key, const std::set<std::string>& members)
{
    _sendCommandToRedisServer("SADD", key, members);
    return _getNumResponse();
}

/**
 * @brief 返回集合中元素的数量
 *
 * @param key 指定的key
 *
 * @return 元素数量
 */
size_t RedisClientImpl::scard(const std::string& key)
{
    _sendCommandToRedisServer("SCARD", key);
    return _getNumResponse();
}

/**
 * @brief 返回一个集合与给定集合的差集的元素，不存在的key认为是空集
 *
 * @param key1 集合1
 * @param key2 集合2
 *
 * @return 差集元素
 */
std::string RedisClientImpl::sdiff(const std::string& key1, const std::string& key2)
{
    _sendCommandToRedisServer("SDIFF", key1, key2);
    std::vector<std::string> replys;
    _getMultiBulkResponse(replys);
    assert(replys.empty() or replys.size() == 1);
    if (replys.empty())
        return std::string();
    else
        return replys[0];
}

/**
 * @brief 返回一个集合与给定集合的差集的元素，不存在的key认为是空集
 *
 * @param key 集合
 * @param keys 集合数组
 *
 * @return 差集元素
 */
std::vector<std::string> RedisClientImpl::sdiff(const std::string& key, const std::vector<std::string>& keys)
{
    _sendCommandToRedisServer("SDIFF", key, keys);
    std::vector<std::string> replys;
    _getMultiBulkResponse(replys);
    return replys;
}

/**
 * @brief 该命令类似于sdiff，不同之处在于该命令不返回结果集，而是将结果存放在dstKey集合中
 *
 * @param dstKey 目标集合
 * @param key1 集合1
 * @param key2 集合2
 *
 * @return 结果集元素的个数
 */
size_t RedisClientImpl::sdiffstore(const std::string& dstKey, const std::string& key1, const std::string& key2)
{
    _sendCommandToRedisServer("SDIFFSTORE", dstKey, key1, key2);
    return _getNumResponse();
}

/**
 * @brief 该命令类似于sdiff，不同之处在于该命令不返回结果集，而是将结果存放在dstKey集合中
 *
 * @param dstKey 目标集合
 * @param key 集合
 * @param keys 集合数组
 *
 * @return 结果集元素的个数
 */
size_t RedisClientImpl::sdiffstore(const std::string& dstKey, const std::string& key, 
        const std::vector<std::string>& keys)
{
    _sendCommandToRedisServer("SDIFFSTORE", dstKey, key, keys);
    return _getNumResponse();
}

/**
 * @brief 返回指定所有的集合的成员的交集
 *
 * @param key1 集合1
 * @param key2 集合2
 *
 * @return 交集
 */
std::string RedisClientImpl::sinter(const std::string& key1, const std::string& key2)
{
    _sendCommandToRedisServer("SINTER", key1, key2);
    std::vector<std::string> replys;
    _getMultiBulkResponse(replys);
    assert(replys.empty() or replys.size() == 1);
    if (replys.empty())
        return std::string();
    else
        return replys[0];
}

/**
 * @brief 返回指定所有的集合的成员的交集
 *
 * @param key 集合
 * @param keys 集合数组
 *
 * @return 交集
 */
std::vector<std::string> RedisClientImpl::sinter(const std::string& key, const std::vector<std::string>& keys)
{
    _sendCommandToRedisServer("SINTER", key, keys);
    std::vector<std::string> replys;
    _getMultiBulkResponse(replys);
    return replys;
}

/**
 * @brief 这个命令与sinter命令类似，但是它并不是直接返回结果集，而是将结果保存在dstKey集合中
 *
 * @param dstKey 目标集合
 * @param key1 集合1
 * @param key2 集合2
 *
 * @return 结果集中成员的个数
 */
size_t RedisClientImpl::sinterstore(const std::string& dstKey, const std::string& key1, const std::string& key2)
{
    _sendCommandToRedisServer("SINTERSTORE", dstKey, key1, key2);
    return _getNumResponse();
}

/**
 * @brief 这个命令与sinter命令类似，但是它并不是直接返回结果集，而是将结果保存在dstKey集合中
 *
 * @param dstKey 目标集合
 * @param key 集合
 * @param keys 集合数组
 *
 * @return 结果集中成员的个数
 */
size_t RedisClientImpl::sinterstore(const std::string& dstKey, const std::string& key, 
        const std::vector<std::string>& keys)
{
    _sendCommandToRedisServer("SINTERSTORE", dstKey, key, keys);
    return _getNumResponse();
}

/**
 * @brief 返回成员member是否是集合的元素
 *
 * @param key 指定的key
 * @param member 指定的value
 *
 * @return 
 *      * 1 如果member元素是集合key的元素
 *      * 0 如果member元素不是集合key的元素
 */
int RedisClientImpl::sismember(const std::string& key, const std::string& member)
{
    _sendCommandToRedisServer("SISMEMBER", key, member);
    return _getNumResponse();
}

/**
 * @brief 返回key集合所有的元素
 *
 * @param key 指定的key
 *
 * @return 集合中的所有元素
 */
std::vector<std::string> RedisClientImpl::smembers(const std::string& key)
{
    _sendCommandToRedisServer("SMEMBERS", key);
    std::vector<std::string> replys;
    _getMultiBulkResponse(replys);
    return replys;
}

/**
 * @brief 将member从sourceKey集合移动到dstKey集合中
 *
 * @param sourceKey 源集合
 * @param dstKey 目标集合
 * @param member 指定的member
 *
 * @return 
 *      * 1 如果该元素成功移除
 *      * 0 如果该元素不是sourceKey集合成员,无任何操作
 */
int RedisClientImpl::smove(const std::string& sourceKey, const std::string& dstKey, const std::string& member)
{
    _sendCommandToRedisServer("SMOVE", sourceKey, dstKey, member);
    return _getNumResponse();
}

/**
 * @brief 移除并返回集合中一个随机元素
 *
 * @param key 指定的key
 *
 * @return 随机元素
 */
CppRedisClient::StringReply RedisClientImpl::spop(const std::string& key)
{
    _sendCommandToRedisServer("SPOP", key);
    std::vector<CppRedisClient::StringReply> replys;
    _getMultiBulkResponse(replys);
    assert(replys.size() == 1);
    return replys[0];
}

/**
 * @brief 返回集合中一个随机元素
 *
 * @param key 指定的key
 *
 * @return 随机元素
 */
CppRedisClient::StringReply RedisClientImpl::srandmember(const std::string& key)
{
    _sendCommandToRedisServer("SRANDMEMBER", key);
    std::vector<CppRedisClient::StringReply> replys;
    _getMultiBulkResponse(replys);
    assert(replys.size() == 1);
    return replys[0];
}

/**
 * @brief 返回集合中count个随机元素
 *
 * @param key 指定的key
 * @param count 元素个数
 *
 * @return 随机元素
 */
std::vector<std::string> RedisClientImpl::srandmember(const std::string& key, const int count)
{
    _sendCommandToRedisServer("SRANDMEMBER", key, count);
    std::vector<std::string> replys;
    _getMultiBulkResponse(replys);
    return replys;
}

/**
 * @brief 移除集合中指定的元素
 *
 * @param key 指定的key
 * @param member 指定的member
 *
 * @return 从集合中移除元素的个数
 */
size_t RedisClientImpl::srem(const std::string& key, const std::string& member)
{
    _sendCommandToRedisServer("SREM", key, member);
    return _getNumResponse();
}

/**
 * @brief 移除集合中指定的元素
 *
 * @param key 指定的key
 * @param members 指定的members
 *
 * @return 从集合中移除元素的个数
 */
size_t RedisClientImpl::srem(const std::string& key, const std::vector<std::string>& members)
{
    _sendCommandToRedisServer("SREM", key, members);
    return _getNumResponse();
}

/**
 * @brief 移除集合中指定的元素
 *
 * @param key 指定的key
 * @param members 指定的members
 *
 * @return 从集合中移除元素的个数
 */
size_t RedisClientImpl::srem(const std::string& key, const std::set<std::string>& members)
{
    _sendCommandToRedisServer("SREM", key, members);
    return _getNumResponse();
}

/**
 * @brief 返回给定的多个集合的并集中的所有元素
 *
 * @param key1 集合1
 * @param key2 集合2
 *
 * @return 并集的元素
 */
std::string RedisClientImpl::sunion(const std::string& key1, const std::string& key2)
{
    _sendCommandToRedisServer("SUNION", key1, key2);
    std::vector<std::string> replys;
    _getMultiBulkResponse(replys);
    assert(replys.empty() or replys.size() == 1);
    if (replys.empty())
        return std::string();
    else
        return replys[0];
}

/**
 * @brief 返回给定的多个集合的并集中的所有元素
 *
 * @param key 集合
 * @param keys 集合数组
 *
 * @return 并集的元素
 */
std::vector<std::string> RedisClientImpl::sunion(const std::string& key, const std::vector<std::string>& keys)
{
    _sendCommandToRedisServer("SUNION", key, keys);
    std::vector<std::string> replys;
    _getMultiBulkResponse(replys);
    return replys;
}

/**
 * @brief 该命令作用类似于sunion命令，不同的是它并不返回结果集，而是将结果存储在dstKey集合中
 *
 * @param dstKey 目标集合
 * @param key1 集合1
 * @param key2 集合2
 *
 * @return 结果集中元素的个数
 */
size_t RedisClientImpl::sunionstore(const std::string& dstKey, const std::string& key1, const std::string& key2)
{
    _sendCommandToRedisServer("SUNIONSTORE", dstKey, key1, key2);
    return _getNumResponse();
}

/**
 * @brief 该命令作用类似于sunion命令，不同的是它并不返回结果集，而是将结果存储在dstKey集合中
 *
 * @param dstKey 目标集合
 * @param key 集合
 * @param keys 集合数组
 *
 * @return 结果集中元素的个数
 */
size_t RedisClientImpl::sunionstore(const std::string& dstKey, const std::string& key, 
        const std::vector<std::string>& keys)
{
    _sendCommandToRedisServer("SUNIONSTORE", dstKey, key, keys);
    return _getNumResponse();
}

/* Sets End -----------------------------------------------------------------*/


/* Sorted Sets --------------------------------------------------------------*/

/**
 * @brief 将一个member元素加入到集合key当中，已经存在的则忽略
 *
 * @param key 指定的key
 * @param score 分值
 * @param member 指定的member
 *
 * @return 添加的元素数量
 */
size_t RedisClientImpl::zadd(const std::string& key, const int score, const std::string& member)
{
    _sendCommandToRedisServer("ZADD", key, score, member);
    return _getNumResponse();
}

/**
 * @brief 返回有序集合key的元素个数
 *
 * @param key 指定的key
 *
 * @return 元素个数
 */
size_t RedisClientImpl::zcard(const std::string& key)
{
    _sendCommandToRedisServer("ZCARD", key);
    return _getNumResponse();
}

/**
 * @brief 返回指定分数范围的元素个数
 *
 * @param key 指定的key
 * @param min 最小分数
 * @param max 最大分数
 *
 * @return 指定分数范围的元素个数
 */
size_t RedisClientImpl::zcount(const std::string& key, const int min, const int max)
{
    _sendCommandToRedisServer("ZCOUNT", key, min, max);
    return _getNumResponse();
}

/**
 * @brief 为有序集合key的成员member的score值加increment
 *
 * @param key 指定的key
 * @param increment 增加的值
 * @param member 指定的member
 *
 * @return member成员的新score值
 */
std::string RedisClientImpl::zincrby(const std::string& key, const int increment, const std::string& member)
{
    _sendCommandToRedisServer("ZINCYBY", key, increment, member);
    std::vector<std::string> replys;
    _getMultiBulkResponse(replys);
    assert(replys.size() == 1);
    return replys[0];
}

/**
 * @brief 返回有序集合key中指定范围的元素
 *
 * @param key 指定的key
 * @param start 区间开始
 * @param stop 区间结束
 *
 * @return 指定范围的元素
 */
std::vector<std::string> RedisClientImpl::zrange(const std::string& key, const int start, const int stop)
{
    _sendCommandToRedisServer("ZRANGE", key, start, stop);
    std::vector<std::string> replys;
    _getMultiBulkResponse(replys);
    return replys;
}

/**
 * @brief 返回指定分数范围内的元素
 *
 * @param key 指定的key
 * @param min 最小分数
 * @param max 最大分数
 *
 * @return 指定范围内的元素
 */
std::vector<std::string> RedisClientImpl::zrangebyscore(const std::string& key, const int min, const int max)
{
    _sendCommandToRedisServer("ZRANGEBYSCORE", key, min, max);
    std::vector<std::string> replys;
    _getMultiBulkResponse(replys);
    return replys;
}

/**
 * @brief 返回有序集合key中成员member的排名
 *
 * @param key 指定的key
 * @param member 指定的member
 *
 * @return member的排名 
 */
CppRedisClient::StringReply RedisClientImpl::zrank(const std::string& key, const std::string& member)
{
    _sendCommandToRedisServer("ZRANK", key, member);
    int length = -1;
    boost::shared_ptr<char> buf = _getBulkResponse(length);
    return CppRedisClient::StringReply(buf, length);
}

/**
 * @brief 删除有序集合key中的member成员
 *
 * @param key 指定的key
 * @param member 指定的member
 *
 * @return 被删除的元素数量
 */
size_t RedisClientImpl::zrem(const std::string& key, const std::string& member)
{
    _sendCommandToRedisServer("ZREM", key, member);
    return _getNumResponse();
}

/**
 * @brief 删除有序集合key中的member成员
 *
 * @param key 指定的key
 * @param members 指定的members
 *
 * @return 被删除的元素数量
 */
size_t RedisClientImpl::zrem(const std::string& key, const std::vector<std::string>& members)
{
    _sendCommandToRedisServer("ZREM", key, members);
    return _getNumResponse();
}

/**
 * @brief 删除有序集合key中指定区间内的元素
 *
 * @param key 指定的key
 * @param start 区间开始
 * @param stop 区间结束
 *
 * @return 被删除的元素数量
 */
size_t RedisClientImpl::zremrangebyrank(const std::string& key, const int start, const int stop)
{
    _sendCommandToRedisServer("ZREMRANGEBYRANK", key, start, stop);
    return _getNumResponse();
}

/**
 * @brief 删除有序集合key中score值位于[min, max]之间的元素
 *
 * @param key 指定的key
 * @param min 最小分数
 * @param max 最大分数
 *
 * @return 被删除的元素数量
 */
size_t RedisClientImpl::zremrangebyscore(const std::string& key, const int min, const int max)
{
    _sendCommandToRedisServer("ZREMRANGEBYSCORE", key, min, max);
    return _getNumResponse();
}

/**
 * @brief 返回有序集合key中，指定区间内的成员(按score值逆序)
 *
 * @param key 指定的key
 * @param start 区间开始
 * @param stop 区间结束
 *
 * @return 指定区间内成员
 */
std::vector<std::string> RedisClientImpl::zrevrange(const std::string& key, const int start, const int stop)
{
    _sendCommandToRedisServer("ZREVRANGE", key, start, stop);
    std::vector<std::string> replys;
    _getMultiBulkResponse(replys);
    return replys;
}

/**
 * @brief 返回有序集合中score值位于[min, max]内的成员(按score值逆序)
 *
 * @param key 指定的key
 * @param max 最大分数
 * @param min 最小分数
 *
 * @return 指定区间内的成员
 */
std::vector<std::string> RedisClientImpl::zrevrangebyscore(const std::string& key, const int max, const int min)
{
    _sendCommandToRedisServer("ZREVRANGEBYSCORE", key, max, min);
    std::vector<std::string> replys;
    _getMultiBulkResponse(replys);
    return replys;
}

/**
 * @brief 返回有序集合key中成员member的排名(按score值逆序)
 *
 * @param key 指定的key
 * @param member 指定的member
 *
 * @return member的排名
 */
CppRedisClient::StringReply RedisClientImpl::zrevrank(const std::string& key, const std::string& member)
{
    _sendCommandToRedisServer("ZREVRANK", key, member);
    int length = -1;
    boost::shared_ptr<char> buf = _getBulkResponse(length);
    return CppRedisClient::StringReply(buf, length);
}

/**
 * @brief 返回有序集合key中成员member的score值
 *
 * @param key 指定的key
 * @param member 指定的member
 *
 * @return member的score值
 */
CppRedisClient::StringReply RedisClientImpl::zscore(const std::string& key, const std::string& member)
{
    _sendCommandToRedisServer("zscore", key, member);
    int length = -1;
    boost::shared_ptr<char> buf = _getBulkResponse(length);
    return CppRedisClient::StringReply(buf, length);
}


/* Sorted Sets End ----------------------------------------------------------*/


/* Connection ---------------------------------------------------------------*/

/**
 * @brief 验证密码
 *
 * @param password 密码
 *
 * @return 验证结果
 */
bool RedisClientImpl::auth(const std::string& password)
{
    _sendCommandToRedisServer("AUTH", password);
    std::string response = _getOneLineResponse();
    return response == "OK";
}

/**
 * @brief 内容回显
 *
 * @param message 内容
 *
 * @return 同内容
 */
CppRedisClient::StringReply RedisClientImpl::echo(const std::string& message)
{
    _sendCommandToRedisServer("ECHO", message);
    int length = -1;
    boost::shared_ptr<char> buf = _getBulkResponse(length);
    return CppRedisClient::StringReply(buf, length);
}

/**
 * @brief 测试连接是否可用
 *
 * @return 是否可用结果
 */
bool RedisClientImpl::ping()
{
    _sendCommandToRedisServer("PING");
    std::string response = _getOneLineResponse();
    return response == "PONG";
}

/**
 * @brief 关闭连接
 */
void RedisClientImpl::quit()
{
    _sendCommandToRedisServer("QUIT");
    std::string response = _getOneLineResponse();
    assert(response == "OK");
    return;
} 

/**
 * @brief 选择数据库
 *
 * @param index 数据库号
 */
void RedisClientImpl::select(const size_t index)
{
    _sendCommandToRedisServer("SELECT", index);
    std::string response = _getOneLineResponse();
    assert(response == "OK");
    return;
}

/* Connection End -----------------------------------------------------------*/


}

