/**
 * @file enum_define.h
 * @brief 各种enum声明，用于RedisClient函数
 * @author Finalcheat
 */

#ifndef ENUM_DEFINE
#define ENUM_DEFINE

namespace CppRedisClient {

    /**
     * @brief object命令subcommand参数
     */
    enum OBJECT_SUBCOMMAND
    {
        REFCOUNT,
        ENCODING,
        IDLETIME,
    };

    /**
     * @brief linsert命令参数
     */
    enum LINSERT
    {
        BEFORE,
        AFTER,
    };

}


#endif
