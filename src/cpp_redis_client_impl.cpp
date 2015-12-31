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
 * @file cpp_redis_client_impl.cpp
 * @brief 
 * @author Finalcheat
 * @version 0.01
 * @date 2015-12-28
 */

#include <iostream>
#include <boost/asio.hpp>
#include <boost/format.hpp>
#include <string>
#include <vector>
#include <boost/array.hpp>
#include <boost/lexical_cast.hpp>


namespace cpp_redis_client {


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

    public:
        void set(const std::string& key, const std::string& value);
        void setex(const std::string& key, const size_t ttl, const std::string& value);
        int setnx(const std::string& key, const std::string& value);
        std::string get(const std::string &key);
        const size_t append(const std::string& key, const std::string& value);
        int pexpire(const std::string& key, const size_t milliseconds);
        int pexpireat(const std::string& key, const size_t when);
        int expire(const std::string& key, const size_t seconds);
        int expireat(const std::string& key, const size_t when);
        int incr(const std::string& key);
        int incrby(const std::string& key, const int amount);
        int decr(const std::string& key);
        int decrby(const std::string& key, const int amount);
        int ttl(const std::string& key);
        int pttl(const std::string& key);
        int persist(const std::string& key);
        int rename(const std::string& srcKey, const std::string& dstKey);
        int renamenx(const std::string& srcKey, const std::string& dstKey);
        size_t llen(const std::string& key);
        std::string dump(const std::string& key);
        int move(const std::string& key, const size_t db);
        std::string randomkey();
        int exists(const std::string& key);
        std::string type(const std::string& key);
        std::vector<std::string> keys(const std::string& pattern);
        size_t getbit(const std::string& key, const size_t offset);
        std::string getrange(const std::string& key, const int start, const int end);
        std::string getset(const std::string& key, const std::string& value);
        size_t strlen(const std::string& key);
        bool ping();


    private:
        void _redisConnect();
        boost::asio::ip::tcp::socket& _getRedisConnect();
        int handler(const char * response, const size_t len);
        size_t _getNumToStrLength(const int num) const;

        void _sendCommandToRedisServer(const std::string& cmd);
        void _sendCommandToRedisServer(const std::string& cmd, const std::string& key);
        void _sendCommandToRedisServer(const std::string& cmd, const std::string& key, const int value);
        void _sendCommandToRedisServer(const std::string& cmd, const std::string& key, const std::string& value);
        void _sendCommandToRedisServer(const std::string& cmd, const std::string& key, const size_t num,
                const std::string& value);
        void _sendCommandToRedisServer(const std::string& cmd, const std::string& key, const int start,
                const int end);

        void _recvRedisServerResponse(std::string& response, bool& isNull);
        std::string _recvOneLine();
        std::string _test();
        std::string _readBulkResponse(const size_t n);
        std::string _readNBitByResponse(const size_t n);
        char _readResponseBeginByte();
        int _readResponseNum();
        std::string _readResponseStr();
        size_t _getReadStreambufSize();

        // 整型数字，回复的第一个字节将是“:”
        const size_t _getNumResponse();
        
        // 用单行回复，回复的第一个字节将是“+”
        std::string _getOneLineResponse();

        // 批量回复（Bulk replies）
        int _getBulkResponse(std::string& response);

    private:
        std::string _host;
        std::string _port;
        boost::asio::io_service _io_service;
        boost::asio::ip::tcp::socket *_psocket;
        boost::asio::streambuf data;
        boost::asio::streambuf writeBuf;
        boost::asio::streambuf readBuf;

    private:
        static boost::format SET_FORMAT; 
        static boost::format SETEX_FORMAT;
        static boost::format GET_FORMAT;
        static boost::format APPEND_FORMAT;

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


// set
// %1% -- key size
// %2% -- key
// %3% -- value size
// %4% -- value
boost::format RedisClientImpl::SET_FORMAT("*3\r\n$3\r\nSET\r\n$%1%\r\n%2%\r\n$%3%\r\n%4%\r\n");

// setex
boost::format RedisClientImpl::SETEX_FORMAT("*4\r\n$5\r\nSETEX\r\n$%1%\r\n%2%\r\n$%3%\r\n%4%\r\n$%5%\r\n%6%\r\n");

// get
boost::format RedisClientImpl::GET_FORMAT("*2\r\n$3\r\nGET\r\n$%1%\r\n%2%\r\n");

// append
boost::format RedisClientImpl::APPEND_FORMAT("*3\r\n$6\r\nAPPEND\r\n$%1%\r\n%2%\r\n$%3%\r\n%4%\r\n");


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
    std::ostream os(&writeBuf);
    os << f;

    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::write(socket, writeBuf);
}

void RedisClientImpl::_sendCommandToRedisServer(const std::string& cmd, const std::string& key)
{
    boost::format f = RedisClientImpl::ONE_OPER_FORMAT;
    f % cmd.size() % cmd % key.size() % key;
    // const std::string buf = f.str();
    std::ostream os(&writeBuf);
    os << f;

    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::write(socket, writeBuf);
}

void RedisClientImpl::_sendCommandToRedisServer(const std::string& cmd, const std::string& key, 
        const int value)
{
    boost::format f = RedisClientImpl::TWO_OPER_FORMAT;
    const size_t valueLength = _getNumToStrLength(value);
    f % cmd.size() % cmd % key.size() % key % valueLength % value;
    // const std::string buf = f.str();
    // std::cout << buf << std::endl;
    std::ostream os(&writeBuf);
    os << f;

    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::write(socket, writeBuf);
}

void RedisClientImpl::_sendCommandToRedisServer(const std::string& cmd, const std::string& key,
        const std::string& value)
{
    boost::format f = RedisClientImpl::TWO_OPER_FORMAT;
    f % cmd.size() % cmd % key.size() % key % value.size() % value;
    // const std::string buf = f.str();
    std::ostream os(&writeBuf);
    os << f;

    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::write(socket, writeBuf);
}

void RedisClientImpl::_sendCommandToRedisServer(const std::string& cmd, const std::string& key, const size_t num,
        const std::string& value)
{
    boost::format f = RedisClientImpl::THREE_OPER_FORMAT;
    const size_t numLength = _getNumToStrLength(num);
    f % cmd.size() % cmd % key.size() % key % numLength % num % value.size() % value;
    // const std::string buf = f.str();
    std::ostream os(&writeBuf);
    os << f;
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::write(socket, writeBuf);
}

void RedisClientImpl::_sendCommandToRedisServer(const std::string& cmd, const std::string& key, const int start,
        const int end)
{
    boost::format f = RedisClientImpl::THREE_OPER_FORMAT;
    const size_t startLength = _getNumToStrLength(start);
    const size_t endLength = _getNumToStrLength(end);
    f % cmd.size() % cmd % key.size() % key % startLength % start % endLength % end;

    std::ostream os(&writeBuf);
    os << f;
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::write(socket, writeBuf);
}

// std::ostream& operator<<(std::ostream& os, std::vector<char>& v)
// {
    // for (std::vector<char>::iterator it = v.begin(); it != v.end(); ++it)
    // {
        // os << *it;
    // }
    // return os;
// }

std::string RedisClientImpl::_readBulkResponse(const size_t n)
{
    const size_t needReadByte = n + sizeof("\r\n") - 1;
    // std::cout << needReadByte << std::endl;
    std::string response;
    if (_getReadStreambufSize() < needReadByte)
    {
        const size_t remainByte = needReadByte - _getReadStreambufSize();
        boost::asio::ip::tcp::socket& socket = _getRedisConnect();
        boost::asio::read(socket, readBuf, boost::asio::transfer_exactly(remainByte));
    }
    response = make_string(readBuf, n);
    readBuf.consume(needReadByte);
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
    return readBuf.size();
}

std::string RedisClientImpl::_readNBitByResponse(const size_t n)
{
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    // boost::asio::read(socket, data, boost::asio::transfer_exactly(n));
    std::cout << "tt" << std::endl;
    std::cout << readBuf.size() << std::endl;
    std::cout << &readBuf << std::endl;
    return make_string(readBuf);
}

char RedisClientImpl::_readResponseBeginByte()
{
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::read(socket, readBuf, boost::asio::transfer_exactly(1));
    std::istream ifs(&readBuf);
    char c;
    ifs >> c;
    return c;
}

int RedisClientImpl::_readResponseNum()
{
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::read_until(socket, readBuf, "\r\n");
    std::istream ifs(&readBuf);
    std::string response;
    // 读取，默认以\n分隔
    std::getline(ifs, response);
    if (response.size() > 0)
    {
        // 去掉\r
        response.pop_back();
    }

    int num = boost::lexical_cast<int>(response);
    return num;
}

std::string RedisClientImpl::_recvOneLine()
{
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    // size_t len = boost::asio::read_until(socket, data, "\r\n");
    size_t len = boost::asio::read(socket, readBuf, boost::asio::transfer_exactly(4));
    len = boost::asio::read(socket, readBuf, boost::asio::transfer_exactly(3));
    // std::cout << "--------------" << std::endl;
    // std::cout << (&data) << std::endl;
    // std::cout << "--------------" << std::endl;
    std::istream ifs(&readBuf);
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
const size_t RedisClientImpl::_getNumResponse()
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

std::string RedisClientImpl::_readResponseStr()
{
    boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    boost::asio::read_until(socket, readBuf, "\r\n");
    std::istream ifs(&readBuf);
    std::string response;
    std::getline(ifs, response);
    if (response.size() > 0)
    {
        response.pop_back();
    }
    return response;
}

void RedisClientImpl::_recvRedisServerResponse(std::string& response, bool& isNull)
{
    // std::cout << _getReadStreambufSize() << std::endl;
    char c = _readResponseBeginByte();
    // std::cout << "resp : " << c << std::endl;
    int num = 0;
    switch (c)
    {
        case '$':
            // bulk回复
            num = _readResponseNum();
            if (num == -1)
            {
                response = "";
                isNull = true;
            }
            else
            {
                response = _readBulkResponse(num);
                isNull = false;
            }
            break;
        case ':':
            num = _readResponseNum();
            response = boost::lexical_cast<std::string>(num);
            break;
        default:
            break;
    }
    // std::cout << c << std::endl;
    // std::cout << num << std::endl;
    // std::cout << _getReadStreambufSize() << std::endl;
    // std::cout << response << std::endl;
    // std::cout << _getReadStreambufSize() << std::endl;
    // _test();
    // std::string content = _recvOneLine();
    // std::cout << content << std::endl;
}

int RedisClientImpl::pexpire(const std::string& key, const size_t milliseconds)
{
    _sendCommandToRedisServer("PEXPIRE", key, milliseconds);
    int response = _getNumResponse();
    return response;
}

int RedisClientImpl::pexpireat(const std::string& key, const size_t when)
{
    _sendCommandToRedisServer("PEXPIREAT", key, when);
    return 1;
}

int RedisClientImpl::expire(const std::string& key, const size_t seconds)
{
    _sendCommandToRedisServer("EXPIRE", key, seconds);
    int response = _getNumResponse();
    return response;
}

int RedisClientImpl::expireat(const std::string& key, const size_t when)
{
    _sendCommandToRedisServer("EXPIREAT", key, when);
    return 1;
}

int RedisClientImpl::setnx(const std::string& key, const std::string& value)
{
    _sendCommandToRedisServer("SETNX", key, value);
    int response = _getNumResponse();
    return response;
}

int RedisClientImpl::incr(const std::string& key)
{
    _sendCommandToRedisServer("INCR", key);
    int response = _getNumResponse();
    return response;
}

int RedisClientImpl::incrby(const std::string& key, const int amount)
{
    _sendCommandToRedisServer("INCRBY", key, amount);
    int response = _getNumResponse();
    return response;
}

int RedisClientImpl::decr(const std::string& key)
{
    _sendCommandToRedisServer("DECR", key);
    int response = _getNumResponse();
    return response;
}

int RedisClientImpl::decrby(const std::string& key, const int amount)
{
    _sendCommandToRedisServer("DECRBY", key, amount);
    int response = _getNumResponse();
    return response;
}

int RedisClientImpl::ttl(const std::string& key)
{
    _sendCommandToRedisServer("TTL", key);
    int response = _getNumResponse();
    return response;
}

int RedisClientImpl::pttl(const std::string& key)
{
    _sendCommandToRedisServer("PTTL", key);
    int response = _getNumResponse();
    return response;
}

int RedisClientImpl::persist(const std::string& key)
{
    _sendCommandToRedisServer("PERSIST", key);
    int response = _getNumResponse();
    return response;
}

int RedisClientImpl::rename(const std::string& srcKey, const std::string& dstKey)
{
    _sendCommandToRedisServer("RENAME", srcKey, dstKey);
    int response = _getNumResponse();
    return response;
}

int RedisClientImpl::renamenx(const std::string& srcKey, const std::string& dstKey)
{
    _sendCommandToRedisServer("RENAMENX", srcKey, dstKey);
    int response = _getNumResponse();
    return response;
}

size_t RedisClientImpl::llen(const std::string& key)
{
    _sendCommandToRedisServer("LLEN", key);
    size_t response = _getNumResponse();
    return response;
}

std::string RedisClientImpl::dump(const std::string& key)
{
    _sendCommandToRedisServer("DUMP", key);
    return "";
}

int RedisClientImpl::move(const std::string& key, const size_t db)
{
    _sendCommandToRedisServer("MOVE", key, db);
    int response = _getNumResponse();
    return response;
}

std::string RedisClientImpl::randomkey()
{
    _sendCommandToRedisServer("RANDOMKEY");
    return "";
}

int RedisClientImpl::exists(const std::string& key)
{
    _sendCommandToRedisServer("EXISTS", key);
    int response = _getNumResponse();
    return response;
}

std::string RedisClientImpl::type(const std::string& key)
{
    _sendCommandToRedisServer("TYPE", key);
    return "";
}

std::vector<std::string> RedisClientImpl::keys(const std::string& pattern)
{
    _sendCommandToRedisServer("KEYS", pattern);
    return std::vector<std::string>();
}

size_t RedisClientImpl::getbit(const std::string& key, const size_t offset)
{
    _sendCommandToRedisServer("GETBIT", key, offset);
    size_t response = _getNumResponse();
    return response;
}

std::string RedisClientImpl::getset(const std::string& key, const std::string& value)
{
    _sendCommandToRedisServer("GETSET", key, value);
    return "";
}

size_t RedisClientImpl::strlen(const std::string& key)
{
    _sendCommandToRedisServer("STRLEN", key);
    size_t response = _getNumResponse();
    return response;
}

std::string RedisClientImpl::getrange(const std::string& key, const int start, const int end)
{
    _sendCommandToRedisServer("GETRANGE", key, start, end);
    std::string response;
    _getBulkResponse(response);
    return response;
}

bool RedisClientImpl::ping()
{
    _sendCommandToRedisServer("PING");
    std::string response = _getOneLineResponse();
    return response == "PONG";
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

void RedisClientImpl::set(const std::string& key, const std::string& value)
{
    // boost::format f = RedisClientImpl::SET_FORMAT;
    // f % key.size() % key % value.size() % value;
    // std::string buf = f.str();
    // std::cout << "buf:" << std::endl << buf << std::endl;

    // boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    // boost::asio::write(socket, boost::asio::buffer(buf));

    // boost::array<char, 128> response;
    // boost::system::error_code err_code;
    // size_t len = socket.read_some(boost::asio::buffer(response), err_code);
    // // std::cout << "test2" << std::endl;
    // // size_t len = boost::asio::read(socket, boost::asio::buffer(response, 2), err_code);
    // // size_t len = boost::asio::read_until(socket, data_, "\r\n");
    // std::cout << "len : " << len << std::endl;
    // std::cout.write(response.data(), len);
    
    _sendCommandToRedisServer("SET", key, value);
    std::string response = _getOneLineResponse();
    assert(response == "OK");
}

void RedisClientImpl::setex(const std::string& key, const size_t ttl, const std::string& value)
{
    // boost::format f = RedisClientImpl::SETEX_FORMAT;
    // const size_t ttlLength = _getNumToStrLength(ttl);
    // f % key.size() % key % ttlLength % ttl % value.size() % value;
    // std::string buf = f.str();

    // boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    // boost::asio::write(socket, boost::asio::buffer(buf));
    
    _sendCommandToRedisServer("SETEX", key, ttl, value);
    std::string response = _getOneLineResponse();
    assert(response == "OK");
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


const size_t RedisClientImpl::append(const std::string& key, const std::string& value)
{
    // boost::format f = RedisClientImpl::APPEND_FORMAT;
    // f % key.size() % key % value.size() % value;
    // std::string buf = f.str();

    // boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    // boost::asio::write(socket, boost::asio::buffer(buf));

    // send command to redis server
    _sendCommandToRedisServer("APPEND", key, value);
    // receive response
    const size_t num = _getNumResponse();
    return num;
}


std::string RedisClientImpl::get(const std::string& key)
{
    _sendCommandToRedisServer("GET", key);
    std::string response;
    bool isNull = false;
    _recvRedisServerResponse(response, isNull);
    return response;
    // boost::format f = RedisClientImpl::GET_FORMAT;
    // f % key.size() % key;
    // std::string buf = f.str();
    // std::cout << "buf:" << std::endl;
    // std::cout << buf << std::endl;

    // boost::asio::ip::tcp::socket& socket = _getRedisConnect();
    // boost::asio::write(socket, boost::asio::buffer(buf));
    // boost::array<char, 128> response;
    // boost::system::error_code err_code;
    // size_t len = socket.read_some(boost::asio::buffer(response), err_code);
    // size_t len = boost::asio::read(socket, boost::asio::buffer(response, 1), err_code);
    // if (len && response[0] == '$')
    // {
        // len = boost::asio::read(socket, boost::asio::buffer(response, 1));
        // len = boost::asio::read(socket, boost::asio::buffer(response, len + sizeof("\r\n")));
        // std::cout.write(response.data(), len);
    // }
    // boost::asio::streambuf data_;
    // size_t len = boost::asio::read_until(socket, data_, "\r\n");
    // std::istream ifs(&data_);
    // ifs.unsetf(std::ios_base::skipws);
    // char sp1, sp2, cr, lf, t1, t2, t3;
    // std::string result;
    // // ifs >> sp1 >> sp2 >> t3 >> cr >> lf >> result >> t1 >> t2;
    // // std::cout << sp1 << sp2 << cr << lf << std::endl;
    // std::cout << "result : " << result << result.size() << std::endl;
    // std::cout << t1 << t2 << std::endl;
    // std::cout << "len : " << len << std::endl;
    // std::cout.write(response.data(), len);
    // return result;
}

int RedisClientImpl::handler(const char * response, const size_t len)
{
    for (size_t i = 0; i < len; ++i)
    {
        ;
    }
    return 0;
}


}
