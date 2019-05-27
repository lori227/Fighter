// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Network/NetRecv.h"
#include "Public/Network/NetSocket.h"

UNetRecv::UNetRecv( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
}

UNetRecv::~UNetRecv()
{
    free( _data_buff );
    _data_buff = nullptr;

    _recv_queue.ClearObject();
}

void UNetRecv::StartService( NetSocket* socket, uint32 queuesize )
{
    Init();

    _net_socket = socket;
    _recv_queue.InitQueue( queuesize );
    _data_buff_length = NetDefine::SerializeBuffLength;
    _data_buff = ( int8* )malloc( _data_buff_length );

    _recv_length = 0u;
    StartThread( TEXT( "NetRecv" ), true );

    __LOG_INFO__( LogNetwork, "network recv thread start!" );
}

void UNetRecv::StopService()
{
    EnsureCompletion();

    __LOG_INFO__( LogNetwork, "network send thread stop!" );
}

void UNetRecv::CalcBuffTotalLength( uint32 totallength )
{
    if ( totallength <= _data_buff_length )
    {
        return;
    }

    __LOG_WARN__( LogNetwork, "realloc buff length=[{}]!", totallength );

    _data_buff_length = totallength;
    _data_buff = ( int8* )( realloc( _data_buff, totallength ) );
}

void UNetRecv::ThreadBody()
{
    if ( _net_socket->_is_close || !_net_socket->_is_connect )
    {
        return;
    }

    return;

    uint32 recvsize = 0u;
    auto ok = _net_socket->_socket->HasPendingData( recvsize );
    if ( !ok || recvsize == 0u )
    {
        return;
    }

    int32 readsize = 0;
    _net_socket->_socket->Recv( ( uint8* )_req_buff, NetDefine::MaxReqBuffLength, readsize );
    if ( readsize == 0 )
    {
        return;
    }

    if ( _recv_length + readsize > NetDefine::MaxRecvBuffLength )
    {
        _recv_length = 0u;
    }

    memcpy( _recv_buff + _recv_length, _req_buff, readsize );
    _recv_length += readsize;

    // 处理消息
    ParseBuffToMessage();
}

void UNetRecv::ParseBuffToMessage()
{
    // 长度不足一个消息头
    uint32 nowposition = 0;
    auto nethead = CheckRecvBuffValid( nowposition );
    if ( nethead == nullptr )
    {
        return;
    }

    while ( _recv_length >= ( nowposition + _net_socket->_message_head_length + nethead->_length ) )
    {
        auto recvmessage = NetMessage::Create( nethead->_length );
        memcpy( &recvmessage->_head, nethead, _net_socket->_message_head_length );

        nowposition += _net_socket->_message_head_length;
        if ( nethead->_length > 0 )
        {
            recvmessage->CopyData( _recv_buff + nowposition, nethead->_length );
            nowposition += nethead->_length;
        }

        _recv_queue.PushObject( recvmessage );

        // 检查消息的有效性
        nethead = CheckRecvBuffValid( nowposition );
        if ( nethead == nullptr )
        {
            break;
        }
    }

    // 设置长度
    _recv_length -= __MIN__( _recv_length, nowposition );

    // 移动消息buff
    if ( _recv_length > 0 && nowposition > 0 )
    {
        memmove( _recv_buff, _recv_buff + nowposition, _recv_length );
    }
}

NetHead* UNetRecv::CheckRecvBuffValid( uint32 position )
{
    if ( _recv_length < ( position + _net_socket->_message_head_length ) )
    {
        return nullptr;
    }

    auto nethead = reinterpret_cast< NetHead* >( _recv_buff + position );

    // 收到的消息长度有错误
    if ( nethead->_length > NetDefine::MaxMessageLength )
    {
        _recv_length = 0;

        __LOG_ERROR__( LogNetwork, "recv msgid[{}] length[{}] position[{}] totallength[{}] error",
                       nethead->_msgid, nethead->_length, position, _recv_length );
        return nullptr;
    }

    return nethead;
}

NetMessage* UNetRecv::PopMessage()
{
    auto message = _recv_queue.Front();
    if ( message == nullptr )
    {
        return nullptr;
    }

    NetMessage* retmessage = nullptr;
    switch ( message->_head._msgid )
    {
    case NetDefine::CUT_MSGCHILDBEGIN:	// 子消息头
    {
        // 这里的子消息没有包括消息头
        auto childcount = message->_head._child;
        auto queuesize = _recv_queue.Size();
        if ( queuesize >= ( childcount + 1u ) )
        {
            // 不能强转成NetMessage, headmessage->_data的长度只包括NetHead

            // 重新计算buff大小
            auto temphead = reinterpret_cast< NetHead* >( message->_data );
            auto totallength = temphead->_length + static_cast< uint32 >( sizeof( NetMessage ) );
            CalcBuffTotalLength( totallength );

            // 强转成UNetMessage
            retmessage = reinterpret_cast< NetMessage* >( _data_buff );

            // 先将消息头拷贝过去
            memcpy( &retmessage->_head, message->_data, message->_head._length );
            _recv_queue.PopRemove();

            // 重定向data地址
            retmessage->_data = _data_buff + sizeof( NetMessage );

            // 合并子消息
            auto copylength = 0u;
            auto leftlength = _data_buff_length - sizeof( NetMessage );

            for ( auto i = 0u; i < childcount; ++i )
            {
                auto childmessage = _recv_queue.Front();

                // 不是子消息, 直接返回null
                if ( childmessage == nullptr || childmessage->_head._msgid != NetDefine::CUT_MSGCHILD )
                {
                    return nullptr;
                }

                // 长度不足, 返回null
                if ( leftlength < childmessage->_head._length )
                {
                    _recv_queue.PopRemove();
                    return nullptr;
                }

                memcpy( retmessage->_data + copylength, childmessage->_data, childmessage->_head._length );
                copylength += childmessage->_head._length;
                leftlength -= childmessage->_head._length;

                _recv_queue.PopRemove();
            }
        }
        else
        {
            // 如果超出了最大的队列长度
            if ( childcount >= _recv_queue.Capacity() )
            {
                _recv_queue.PopRemove();
            }
        }
        break;
    }
    case NetDefine::CUT_MSGCHILD:		// 如果取到的是子消息, 直接丢掉
    {
        _recv_queue.PopRemove();
        break;
    }
    default:	// 不是拆包消息, 直接返回
    {
        if ( message->_head._length + sizeof( NetMessage ) <= _data_buff_length )
        {
            // 强转成UNetMessage
            retmessage = reinterpret_cast< NetMessage* >( _data_buff );
            retmessage->_data = _data_buff + sizeof( NetMessage );
            retmessage->CopyFrom( message );
        }

        _recv_queue.PopRemove();
        break;
    }
    }

    return retmessage;
}