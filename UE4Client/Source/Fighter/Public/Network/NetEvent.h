#pragma once

#include "Headers.h"
#include "NetEvent.generated.h"

// 网络事件
UCLASS()
class UNetEvent : public UObject
{
    GENERATED_UCLASS_BODY()

public:
    // 类型
    uint32 _type = 0u;

    // id
    uint64 _id = 0u;

    // 数据
    void* _data = 0u;

    // 错误码
    int32 _code = 0u;

    // 描述
    FString _describe;
};

// 网络时间函数
typedef std::function< void( const UNetEvent* ) > NetEventFunction;
