/**
 * @file cpp_redis_client.cpp
 * @brief RedisClient类的所有方法都是转发到RedisClientImpl类去实现
 * @author Finalcheat
 */

#include "cpp_redis_client.h"
#include "string_reply.h"
#include "cpp_redis_client_impl.cpp"
#include <iostream>


namespace CppRedisClient {


RedisClient::RedisClient() : impl(0)
{
    // std::cout << "RedisClient Init" << std::endl;
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

/* Keys ---------------------------------------------------------------------*/

/**
 * @brief 删除key，如果key不存在，则忽略
 *
 * @param key 需要删除的key
 *
 * @return 被删除的key数量
 */
size_t RedisClient::del(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::del Error!");

    return impl->del(key);
}

/**
 * @brief 删除key，如果key不存在，则忽略
 *
 * @param keys 需要删除的keys
 *
 * @return 被删除的key数量
 */
size_t RedisClient::del(const std::vector<std::string>& keys)
{
    if (!impl)
        throw std::runtime_error("RedisClient::del Error!");

    return impl->del(keys);
}

/**
 * @brief 序列化给定key ，如果key不存在，返回的StringReply为NULL
 *
 * @param key 待序列号的key
 *
 * @return 被序列化的值
 */
CppRedisClient::StringReply RedisClient::dump(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::dump Error!");

    return impl->dump(key);
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
int RedisClient::exists(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::exists Error!");

    return impl->exists(key);
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
int RedisClient::expire(const std::string& key, const size_t seconds)
{
    if (!impl)
        throw std::runtime_error("RedisClient::expire Error!");

    return impl->expire(key, seconds);
}

/**
 * @brief 设置key的过期时间，与expire不同的是，时间参数是unix时间戳
 *
 * @param key 指定的key
 * @param timestamp 过期时间(unix时间戳)
 *
 * @return 
 *      * 1 成功设置过期时间
 *      * 0 设置失败(key不存在或者不允许设置过期时间)
 */
size_t RedisClient::expireat(const std::string& key, const size_t timestamp)
{
    if (!impl)
        throw std::runtime_error("RedisClient::expireat Error!");

    return impl->expireat(key, timestamp);
}

/**
 * @brief 查找符合模式的pattern的keys
 *
 * @param pattern 正则表达式
 *
 * @return 符合条件的keys
 */
std::vector<std::string> RedisClient::keys(const std::string& pattern)
{
    if (!impl)
        throw std::runtime_error("RedisClient::keys Error!");

    return impl->keys(pattern);
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
int RedisClient::move(const std::string& key, const size_t db)
{
    if (!impl)
        throw std::runtime_error("RedisClient::move Error!");

    return impl->move(key, db);
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
CppRedisClient::StringReply RedisClient::object(const CppRedisClient::OBJECT_SUBCOMMAND subCommand, 
        const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::object Error!");

    return impl->object(subCommand, key);
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
int RedisClient::persist(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::persist Error!");

    return impl->persist(key);
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
int RedisClient::pexpire(const std::string& key, const uint64_t milliseconds)
{
    if (!impl)
        throw std::runtime_error("RedisClient::pexpire Error!");

    return impl->pexpire(key, milliseconds);
}

/**
 * @brief 设置key的过期时间，时间是unix时间戳，以毫秒为单位
 *
 * @param key 指定的key
 * @param millisecondsTimestamp unix时间戳(ms)
 *
 * @return 
 *      * 1 设置成功
 *      * 0 设置失败(key不存在或者不允许设置过期时间)
 */
int RedisClient::pexpireat(const std::string& key, const uint64_t millisecondsTimestamp)
{
    if (!impl)
        throw std::runtime_error("RedisClient::pexpireat Error!");

    return impl->pexpireat(key, millisecondsTimestamp);
}

/**
 * @brief 返回key的过期时间，与ttl类似，不同的是返回的时间单位是毫秒
 *
 * @param key 指定的key
 *
 * @return key的过期时间(ms)
 */
int64_t RedisClient::pttl(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::pttl Error!");

    return impl->pttl(key);
}

/**
 * @brief 返回随机的key
 *
 * @return 随机的key
 */
CppRedisClient::StringReply RedisClient::randomkey()
{
    if (!impl)
        throw std::runtime_error("RedisClient::randomkey Error!");

    return impl->randomkey();
}

/**
 * @brief 对key重命名
 *
 * @param srcKey 源key
 * @param dstKey 目标key
 */
void RedisClient::rename(const std::string& srcKey, const std::string& dstKey)
{
    if (!impl)
        throw std::runtime_error("RedisClient::rename Error!");

    return impl->rename(srcKey, dstKey);
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
int RedisClient::renamenx(const std::string& srcKey, const std::string& dstKey)
{
    if (!impl)
        throw std::runtime_error("RedisClient::renamenx Error!");

    return impl->renamenx(srcKey, dstKey);
}

/**
 * @brief 返回key的过期时间，与pttl类似，不同的是返回的时间单位是秒
 *
 * @param key 指定的key
 *
 * @return key的过期时间(s)
 */
int RedisClient::ttl(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::ttl Error!");

    return impl->ttl(key);
}

/**
 * @brief 返回key对应的value数据结构类型
 *
 * @param key 指定的key
 *
 * @return 对应的数据类型
 */
std::string RedisClient::type(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::type Error!");

    return impl->type(key);
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
const size_t RedisClient::append(const std::string& key, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::append Error!");

    return impl->append(key, value);
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
size_t RedisClient::bitcount(const std::string& key, const int start, const int end)
{
    if (!impl)
        throw std::runtime_error("RedisClient::bitcount Error!");

    return impl->bitcount(key, start, end);
}

/**
 * @brief 将key对应的数字减1
 *
 * @param key 指定的key
 *
 * @return 减少之后的value
 */
int RedisClient::decr(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::decr Error!");

    return impl->decr(key);
}

/**
 * @brief 将key对应的数字减amount
 *
 * @param key 指定的key
 * @param amount 减少的数
 *
 * @return 减少之后的value
 */
int RedisClient::decrby(const std::string& key, const int amount)
{
    if (!impl)
        throw std::runtime_error("RedisClient::decrby Error!");

    return impl->decrby(key, amount);
}

/**
 * @brief 返回key对应的value
 *
 * @param key 指定的key
 *
 * @return key对应的value
 */
CppRedisClient::StringReply RedisClient::get(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::get Error!");

    return impl->get(key);
}

/**
 * @brief 返回key对应的string在offset处的bit值
 *
 * @param key 指定的key
 * @param offset 偏移位置
 *
 * @return 在offset处的bit值
 */
size_t RedisClient::getbit(const std::string& key, const size_t offset)
{
    if (!impl)
        throw std::runtime_error("RedisClient::getbit Error!");

    return impl->getbit(key, offset);
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
std::string RedisClient::getrange(const std::string& key, const int start, const int end)
{
    if (!impl)
        throw std::runtime_error("RedisClient::getrange Error!");

    return impl->getrange(key, start, end);
}

/**
 * @brief 设置key的value并且返回旧的value
 *
 * @param key 指定的key
 * @param value 指定的value
 *
 * @return 旧的value
 */
CppRedisClient::StringReply RedisClient::getset(const std::string& key, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::getset Error!");

    return impl->getset(key, value);
}

/**
 * @brief key对应的value加1
 *
 * @param key 指定的key
 *
 * @return 递增后的value
 */
int RedisClient::incr(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::incr Error!");

    return impl->incr(key);
}

/**
 * @brief key对应的value加amount
 *
 * @param key 指定的key
 * @param amount 增加的数
 *
 * @return 增加后的value
 */
int RedisClient::incrby(const std::string& key, const int amount)
{
    if (!impl)
        throw std::runtime_error("RedisClient::incrby Error!");

    return impl->incrby(key, amount);
}

/**
 * @brief key对应的value加amount
 *
 * @param key 指定的key
 * @param amount 增加的数
 *
 * @return 增加后的value
 */
std::string RedisClient::incrbyfloat(const std::string& key, const float amount)
{
    if (!impl)
        throw std::runtime_error("RedisClient::incrbyfloat Error!");

    return impl->incrbyfloat(key, amount);
}

/**
 * @brief 返回所有指定key对应的value
 *
 * @param keys 指定的keys
 *
 * @return keys对应的values
 */
std::vector<CppRedisClient::StringReply> RedisClient::mget(const std::vector<std::string>& keys)
{
    if (!impl)
        throw std::runtime_error("RedisClient::mget Error!");

    return impl->mget(keys);
}

/**
 * @brief 设置给定的keys对应的values
 *
 * @param kvMap key-value字典
 */
void RedisClient::mset(const std::map<std::string, std::string>& kvMap)
{
    if (!impl)
        throw std::runtime_error("RedisClient::mset Error!");

    return impl->mset(kvMap);
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
int RedisClient::msetnx(const std::map<std::string, std::string>& kvMap)
{
    if (!impl)
        throw std::runtime_error("RedisClient::msetnx Error!");

    return impl->msetnx(kvMap);
}

/**
 * @brief 与setex类似，不同的是过期时间以毫秒为单位
 *
 * @param key 指定的key
 * @param milliseconds 过期时间(ms)
 * @param value 指定的value
 */
void RedisClient::psetex(const std::string& key, const uint64_t milliseconds, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::psetex Error!");

    return impl->psetex(key, milliseconds, value);
}

/**
 * @brief 设置key对应的value
 *
 * @param key 指定的key
 * @param value 指定的value
 */
void RedisClient::set(const std::string& key, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::set Error!");

    return impl->set(key, value);
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
size_t RedisClient::setbit(const std::string& key, const size_t offset, const size_t value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::setbit Error!");

    return impl->setbit(key, offset, value);
}

/**
 * @brief 设置key对应的value，并且设置过期时间
 *
 * @param key 指定的key
 * @param ttl 过期时间(s)
 * @param value 指定的value
 */
void RedisClient::setex(const std::string& key, const size_t ttl, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::setex Error!");

    return impl->setex(key, ttl, value);
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
int RedisClient::setnx(const std::string& key, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::setnx Error!");

    return impl->setnx(key, value);
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
size_t RedisClient::setrange(const std::string& key, const size_t offset, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::setrange Error!");

    return impl->setrange(key, offset, value);
}

/**
 * @brief 返回key对应的value(字符串)的长度
 *
 * @param key 指定的key
 *
 * @return 字符串长度
 */
size_t RedisClient::strlen(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::strlen Error!");

    return impl->strlen(key);
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
size_t RedisClient::hdel(const std::string& key, const std::string& field)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hdel Error!");

    return impl->hdel(key, field);
}

/**
 * @brief 删除key指定的fields
 *
 * @param key 指定的key
 * @param fields 指定的fields
 *
 * @return 删除的field数量
 */
size_t RedisClient::hdel(const std::string& key, const std::vector<std::string>& fields)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hdel Error!");

    return impl->hdel(key, fields);
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
size_t RedisClient::hexists(const std::string& key, const std::string& field)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hexists Error!");

    return impl->hexists(key, field);
}

/**
 * @brief 返回key对应field的value
 *
 * @param key 指定的key
 * @param field 指定的field
 *
 * @return 对应的value
 */
CppRedisClient::StringReply RedisClient::hget(const std::string& key, const std::string& field)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hget Error!");

    return impl->hget(key, field);
}

/**
 * @brief 返回key对应的所有field-value
 *
 * @param key 指定的key
 *
 * @return key对应的所有field-value
 */
std::map<std::string, std::string> RedisClient::hgetall(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hgetall Error!");

    return impl->hgetall(key);
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
int RedisClient::hincrby(const std::string& key, const std::string& field, const int amount)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hincrby Error!");

    return impl->hincrby(key, field, amount);
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
std::string RedisClient::hincrbyfloat(const std::string& key, const std::string& field, const float amount)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hincrbyfloat Error!");

    return impl->hincrbyfloat(key, field, amount);
}

/**
 * @brief 返回指定key的所有fields
 *
 * @param key 指定的key
 *
 * @return 对应的fields
 */
std::vector<std::string> RedisClient::hkeys(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hkeys Error!");

    return impl->hkeys(key);
}

/**
 * @brief 返回指定key中field的数量
 *
 * @param key 指定的key
 *
 * @return field的数量
 */
size_t RedisClient::hlen(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hlen Error!");
    
    return impl->hlen(key);
}

/**
 * @brief 返回key-field对应的value
 *
 * @param key 指定的key
 * @param field 指定的value
 *
 * @return 对应的value
 */
CppRedisClient::StringReply RedisClient::hmget(const std::string& key, const std::string& field)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hmget Error!");

    return impl->hmget(key, field);
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
    if (!impl)
        throw std::runtime_error("RedisClient::hmget Error!");

    return impl->hmget(key, fields);
}

/**
 * @brief 设置key-field的value
 *
 * @param key 指定的key
 * @param field 指定的field
 * @param value 指定的value
 */
void RedisClient::hmset(const std::string& key, const std::string& field, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hmset Error!");

    return impl->hmset(key, field, value);
}

/**
 * @brief 设置key-field的value
 *
 * @param key 指定的key
 * @param fvMap field-value字典
 */
void RedisClient::hmset(const std::string& key, const std::map<std::string, std::string>& fvMap)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hmset Error!");

    return impl->hmset(key, fvMap);
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
size_t RedisClient::hset(const std::string& key, const std::string& field, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hset Error!");

    return impl->hset(key, field, value);
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
size_t RedisClient::hsetnx(const std::string& key, const std::string& field, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hsetnx Error!");

    return impl->hsetnx(key, field, value);
}

/**
 * @brief 返回指定key对应的所有fields的值
 *
 * @param key 指定的key
 *
 * @return 所有的value
 */
std::vector<std::string> RedisClient::hvals(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::hvals Error!");

    return impl->hvals(key);
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
CppRedisClient::StringReply RedisClient::lindex(const std::string& key, const int index)
{
    if (!impl)
        throw std::runtime_error("RedisClient::lindex Error!");

    return impl->lindex(key, index);
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
int RedisClient::linsert(const std::string& key, const CppRedisClient::LINSERT flag, const std::string& pivot, 
        const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::linsert Error!");

    return impl->linsert(key, flag, pivot, value);
}

/**
 * @brief 返回list的长度
 *
 * @param key 指定的key
 *
 * @return list的长度
 */
size_t RedisClient::llen(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::llen Error!");

    return impl->llen(key);
}

/**
 * @brief 返回list中的第一个元素
 *
 * @param key 指定的key
 *
 * @return 第一个元素的值
 */
CppRedisClient::StringReply RedisClient::lpop(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::lpop Error!");

    return impl->lpop(key);
}

/**
 * @brief 将value插入到list的头部
 *
 * @param key 指定的key
 * @param value 指定的value
 *
 * @return 操作后list的长度
 */
size_t RedisClient::lpush(const std::string& key, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::lpush Error!");

    return impl->lpush(key, value);
}

/**
 * @brief 将values插入到list的头部
 *
 * @param key 指定的key
 * @param values 指定的values
 *
 * @return 操作后list的长度
 */
size_t RedisClient::lpush(const std::string& key, const std::vector<std::string>& values)
{
    if (!impl)
        throw std::runtime_error("RedisClient::lpush Error!");

    return impl->lpush(key, values);
}

/**
 * @brief 当且仅当key存在时将value插入到list的头部
 *
 * @param key 指定的key
 * @param value 指定的value
 *
 * @return 操作后list的长度
 */
size_t RedisClient::lpushx(const std::string& key, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::lpushx Error!");

    return impl->lpushx(key, value);
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
std::vector<std::string> RedisClient::lrange(const std::string& key, const int start, const int stop)
{
    if (!impl)
        throw std::runtime_error("RedisClient::lrange Error!");

    return impl->lrange(key, start, stop);
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
size_t RedisClient::lrem(const std::string& key, const int count, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::lrem Error!");

    return impl->lrem(key, count, value);
}

/**
 * @brief 设置list中index位置元素的值为value
 *
 * @param key 指定的key
 * @param index 元素位置
 * @param value 指定的value
 */
void RedisClient::lset(const std::string& key, const int index, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::lset Error!");

    return impl->lset(key, index, value);
}

/**
 * @brief 修改一个已存在的list的范围
 *
 * @param key 指定的key
 * @param start 开始位置
 * @param stop 结束位置
 */
void RedisClient::ltrim(const std::string& key, const int start, const int stop)
{
    if (!impl)
        throw std::runtime_error("RedisClient::ltrim Error!");

    return impl->ltrim(key, start, stop);
}

/**
 * @brief 移除并返回存于key的list的最后一个元素
 *
 * @param key 指定的key
 *
 * @return list中的最后一个元素
 */
CppRedisClient::StringReply RedisClient::rpop(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::rpop Error!");

    return impl->rpop(key);
}

/**
 * @brief 将list中最后一个元素移除并插入到另一list头部中
 *
 * @param srcKey 源key
 * @param dstKey 目标key
 *
 * @return 被删除和插入的元素
 */
CppRedisClient::StringReply RedisClient::rpoplpush(const std::string& srcKey, const std::string& dstKey)
{
    if (!impl)
        throw std::runtime_error("RedisClient::rpoplpush Error!");

    return impl->rpoplpush(srcKey, dstKey);
}

/**
 * @brief 从list尾部中插入value元素
 *
 * @param key 指定的key
 * @param value 指定的value
 *
 * @return 操作后list的长度
 */
size_t RedisClient::rpush(const std::string& key, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::rpush Error!");

    return impl->rpush(key, value);
}

/**
 * @brief 从list尾部中插入values元素
 *
 * @param key 指定的key
 * @param values 指定的values
 *
 * @return 操作后list的长度
 */
size_t RedisClient::rpush(const std::string& key, const std::vector<std::string>& values)
{
    if (!impl)
        throw std::runtime_error("RedisClient::rpush Error!");

    return impl->rpush(key, values);
}

/**
 * @brief 当且仅当key存在并且是list时将value插入到尾部
 *
 * @param key 指定的key
 * @param value 指定的value
 *
 * @return 操作后list的长度
 */
size_t RedisClient::rpushx(const std::string& key, const std::string& value)
{
    if (!impl)
        throw std::runtime_error("RedisClient::rpushx Error!");

    return impl->rpushx(key, value);
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
size_t RedisClient::sadd(const std::string& key, const std::string& member)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sadd Error!");

    return impl->sadd(key, member);
}

/**
 * @brief 添加members元素到集合中
 *
 * @param key 指定的key
 * @param members 指定的members
 *
 * @return 成功添加到集合里元素的数量
 */
size_t RedisClient::sadd(const std::string& key, const std::vector<std::string>& members)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sadd Error!");

    return impl->sadd(key, members);
}

/**
 * @brief 添加members元素到集合中
 *
 * @param key 指定的key
 * @param members 指定的members
 *
 * @return 成功添加到集合里元素的数量
 */
size_t RedisClient::sadd(const std::string& key, const std::set<std::string>& members)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sadd Error!");

    return impl->sadd(key, members);
}

/**
 * @brief 返回集合中元素的数量
 *
 * @param key 指定的key
 *
 * @return 元素数量
 */
size_t RedisClient::scard(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::scard Error!");

    return impl->scard(key);
}

/**
 * @brief 返回一个集合与给定集合的差集的元素，不存在的key认为是空集
 *
 * @param key1 集合1
 * @param key2 集合2
 *
 * @return 差集元素
 */
std::string RedisClient::sdiff(const std::string& key1, const std::string& key2)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sdiff Error!");

    return impl->sdiff(key1, key2);
}

/**
 * @brief 返回一个集合与给定集合的差集的元素，不存在的key认为是空集
 *
 * @param key 集合
 * @param keys 集合数组
 *
 * @return 差集元素
 */
std::vector<std::string> RedisClient::sdiff(const std::string& key, const std::vector<std::string>& keys)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sdiff Error!");

    return impl->sdiff(key, keys);
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
size_t RedisClient::sdiffstore(const std::string& dstKey, const std::string& key1, const std::string& key2)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sdiffstore Error!");

    return impl->sdiffstore(dstKey, key1, key2);
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
size_t RedisClient::sdiffstore(const std::string& dstKey, const std::string& key,
        const std::vector<std::string>& keys)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sdiffstore Error!");

    return impl->sdiffstore(dstKey, key, keys);
}

/**
 * @brief 返回指定所有的集合的成员的交集
 *
 * @param key1 集合1
 * @param key2 集合2
 *
 * @return 交集
 */
std::string RedisClient::sinter(const std::string& key1, const std::string& key2)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sinter Error!");

    return impl->sinter(key1, key2);
}

/**
 * @brief 返回指定所有的集合的成员的交集
 *
 * @param key 集合
 * @param keys 集合数组
 *
 * @return 交集
 */
std::vector<std::string> RedisClient::sinter(const std::string& key, const std::vector<std::string>& keys)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sinter Error!");

    return impl->sinter(key, keys);
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
size_t RedisClient::sinterstore(const std::string& dstKey, const std::string& key1, const std::string& key2)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sinterstore Error!");

    return impl->sinterstore(dstKey, key1, key2);
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
size_t RedisClient::sinterstore(const std::string& dstKey, const std::string& key, 
        const std::vector<std::string>& keys)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sinterstore Error!");

    return impl->sinterstore(dstKey, key, keys);
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
int RedisClient::sismember(const std::string& key, const std::string& member)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sismember Error!");

    return impl->sismember(key, member);
}

/**
 * @brief 返回key集合所有的元素
 *
 * @param key 指定的key
 *
 * @return 集合中的所有元素
 */
std::vector<std::string> RedisClient::smembers(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::smembers Error!");

    return impl->smembers(key);
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
int RedisClient::smove(const std::string& sourceKey, const std::string& dstKey, const std::string& member)
{
    if (!impl)
        throw std::runtime_error("RedisClient::smove Error!");

    return impl->smove(sourceKey, dstKey, member);
}

/**
 * @brief 移除并返回集合中一个随机元素
 *
 * @param key 指定的key
 *
 * @return 随机元素
 */
CppRedisClient::StringReply RedisClient::spop(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::spop Error!");

    return impl->spop(key);
}

/**
 * @brief 返回集合中一个随机元素
 *
 * @param key 指定的key
 *
 * @return 随机元素
 */
CppRedisClient::StringReply RedisClient::srandmember(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::srandmember Error!");

    return impl->srandmember(key);
}

/**
 * @brief 返回集合中count个随机元素
 *
 * @param key 指定的key
 * @param count 元素个数
 *
 * @return 随机元素
 */
std::vector<std::string> RedisClient::srandmember(const std::string& key, const int count)
{
    if (!impl)
        throw std::runtime_error("RedisClient::srandmember Error!");

    return impl->srandmember(key, count);
}

/**
 * @brief 移除集合中指定的元素
 *
 * @param key 指定的key
 * @param member 指定的member
 *
 * @return 从集合中移除元素的个数
 */
size_t RedisClient::srem(const std::string& key, const std::string& member)
{
    if (!impl)
        throw std::runtime_error("RedisClient::srem Error!");

    return impl->srem(key, member);
}

/**
 * @brief 移除集合中指定的元素
 *
 * @param key 指定的key
 * @param members 指定的members
 *
 * @return 从集合中移除元素的个数
 */
size_t RedisClient::srem(const std::string& key, const std::vector<std::string>& members)
{
    if (!impl)
        throw std::runtime_error("RedisClient::srem Error!");

    return impl->srem(key, members);
}

/**
 * @brief 移除集合中指定的元素
 *
 * @param key 指定的key
 * @param members 指定的members
 *
 * @return 从集合中移除元素的个数
 */
size_t RedisClient::srem(const std::string& key, const std::set<std::string>& members)
{
    if (!impl)
        throw std::runtime_error("RedisClient::srem Error!");

    return impl->srem(key, members);
}

/**
 * @brief 返回给定的多个集合的并集中的所有元素
 *
 * @param key1 集合1
 * @param key2 集合2
 *
 * @return 并集的元素
 */
std::string RedisClient::sunion(const std::string& key1, const std::string& key2)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sunion Error!");

    return impl->sunion(key1, key2);
}

/**
 * @brief 返回给定的多个集合的并集中的所有元素
 *
 * @param key 集合
 * @param keys 集合数组
 *
 * @return 并集的元素
 */
std::vector<std::string> RedisClient::sunion(const std::string& key, const std::vector<std::string>& keys)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sunion Error!");

    return impl->sunion(key, keys);
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
size_t RedisClient::sunionstore(const std::string& dstKey, const std::string& key1, const std::string& key2)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sunionstore Error!");

    return impl->sunionstore(dstKey, key1, key2);
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
size_t RedisClient::sunionstore(const std::string& dstKey, const std::string& key, 
        const std::vector<std::string>& keys)
{
    if (!impl)
        throw std::runtime_error("RedisClient::sunionstore Error!");

    return impl->sunionstore(dstKey, key, keys);
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
size_t RedisClient::zadd(const std::string& key, const int score, const std::string& member)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zadd Error!");

    return impl->zadd(key, score, member);
}

/**
 * @brief 返回有序集合key的元素个数
 *
 * @param key 指定的key
 *
 * @return 元素个数
 */
size_t RedisClient::zcard(const std::string& key)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zcard Error!");

    return impl->scard(key);
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
size_t RedisClient::zcount(const std::string& key, const int min, const int max)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zcount Error!");

    return impl->zcount(key, min, max);
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
std::string RedisClient::zincrby(const std::string& key, const int increment, const std::string& member)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zincrby Error!");

    return impl->zincrby(key, increment, member);
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
std::vector<std::string> RedisClient::zrange(const std::string& key, const int start, const int stop)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zrange Error!");

    return impl->zrange(key, start, stop);
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
std::vector<std::string> RedisClient::zrangebyscore(const std::string& key, const int min, const int max)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zrangebyscore Error!");

    return impl->zrangebyscore(key, min, max);
}

/**
 * @brief 返回有序集合key中成员member的排名
 *
 * @param key 指定的key
 * @param member 指定的member
 *
 * @return member的排名 
 */
CppRedisClient::StringReply RedisClient::zrank(const std::string& key, const std::string& member)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zrank Error!");

    return impl->zrank(key, member);
}

/**
 * @brief 删除有序集合key中的member成员
 *
 * @param key 指定的key
 * @param member 指定的member
 *
 * @return 被删除的元素数量
 */
size_t RedisClient::zrem(const std::string& key, const std::string& member)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zrem Error!");

    return impl->zrem(key, member);
}

/**
 * @brief 删除有序集合key中的member成员
 *
 * @param key 指定的key
 * @param members 指定的members
 *
 * @return 被删除的元素数量
 */
size_t RedisClient::zrem(const std::string& key, const std::vector<std::string>& members)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zrem Error!");

    return impl->zrem(key, members);
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
size_t RedisClient::zremrangebyrank(const std::string& key, const int start, const int stop)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zremrangebyrank Error!");

    return impl->zremrangebyrank(key, start, stop);
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
size_t RedisClient::zremrangebyscore(const std::string& key, const int min, const int max)
{
    if (impl)
        throw std::runtime_error("RedisClient::zremrangebyscore Error!");

    return impl->zremrangebyscore(key, min, max);
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
std::vector<std::string> RedisClient::zrevrange(const std::string& key, const int start, const int stop)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zrevrange Error!");

    return impl->zrevrange(key, start, stop);
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
std::vector<std::string> RedisClient::zrevrangebyscore(const std::string& key, const int max, const int min)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zrevrangebyscore Error!");

    return impl->zrevrangebyscore(key, max, min);
}

/**
 * @brief 返回有序集合key中成员member的排名(按score值逆序)
 *
 * @param key 指定的key
 * @param member 指定的member
 *
 * @return member的排名
 */
CppRedisClient::StringReply RedisClient::zrevrank(const std::string& key, const std::string& member)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zrevrank Error!");

    return impl->zrevrank(key, member);
}

/**
 * @brief 返回有序集合key中成员member的score值
 *
 * @param key 指定的key
 * @param member 指定的member
 *
 * @return member的score值
 */
CppRedisClient::StringReply RedisClient::zscore(const std::string& key, const std::string& member)
{
    if (!impl)
        throw std::runtime_error("RedisClient::zscore Error!");

    return impl->zscore(key, member);
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
bool RedisClient::auth(const std::string& password)
{
    if (!impl)
        throw std::runtime_error("RedisClient::auth Error!");

    return impl->auth(password);
}

/**
 * @brief 内容回显
 *
 * @param message 内容
 *
 * @return 同内容
 */
CppRedisClient::StringReply RedisClient::echo(const std::string& message)
{
    if (!impl)
        throw std::runtime_error("RedisClient::echo Error!");

    return impl->echo(message);
}

/**
 * @brief 测试连接是否可用
 *
 * @return 是否可用结果
 */
bool RedisClient::ping()
{
    if (!impl)
        throw std::runtime_error("RedisClient::ping Error!");

    return impl->ping();
}

/**
 * @brief 关闭连接
 */
void RedisClient::quit()
{
    if (!impl)
        throw std::runtime_error("RedisClient::quit Error!");

    return impl->quit();
}

/**
 * @brief 选择数据库
 *
 * @param index 数据库号
 */
void RedisClient::select(const size_t index)
{
    if (!impl)
        throw std::runtime_error("RedisClient::select Error!");

    return impl->select(index);
}

/* Connection End -----------------------------------------------------------*/

}

int test_main()
{
    CppRedisClient::RedisClient r("localhost");
    {
        CppRedisClient::StringReply re = r.get("f");
        std::cout << "[" << re.getLength() << "]" << re.toString() << std::endl;
        re = r.get("mykey");
        std::cout << "[" << re.getLength() << "]" << re.toString() << std::endl;
        re = r.get("enable");
        try
        {
            std::cout << "[" << re.getLength() << "]" << std::endl;
            std::cout << re.toString() << std::endl;
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
        re = r.get("test");
        std::cout << "[" << re.getLength() << "]" << re.toString() << std::endl;
    }
    // return 0;
    // CppRedisClient::RedisClient redis_obj1;
    CppRedisClient::RedisClient redis_obj2("localhost");
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
