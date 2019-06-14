#pragma once

namespace ENetDefine
{
    enum EConstDefine
    {
        // mtu = 1500 , data = 1472
        MaxMessageLength = 1024 * 5,
        MaxReqBuffLength = MaxMessageLength + 100,		// 投递给网络底层的bbuff大小
        MaxRecvBuffLength = 2 * MaxReqBuffLength,		// 接收消息的最大长度

        ConncectTime = 5000,			// 重连定时器
        SerializeBuffLength = 1024 * 1024 * 2 + 100,	// 序列化消息的buff长度

        CUT_MSGCHILDBEGIN = 65535,		// 分割的头消息
        CUT_MSGCHILD = 65534,			// 分割的子消息

        //////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////
        ConnectEvent = 1,		// 连接事件
        DisconnectEvent = 2,	// 关闭事件
        FailedEvent = 3,		// 失败事件
        ErrorEvent = 4,			// 错误事件
        ShutEvent = 5,			// 销毁事件
    };
}
