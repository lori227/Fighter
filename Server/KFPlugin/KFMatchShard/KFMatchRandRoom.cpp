#include "KFMatchRandRoom.h"
#include "KFMatchQueue.h"

namespace KFrame
{
    void KFMatchRandRoom::InitRoom( KFMatchQueue* kfqueue, uint32 grade, const std::string& version, uint64 battleserverid )
    {
        KFMatchRoom::InitRoom( kfqueue, grade, version, battleserverid );
        _next_add_robot_time = KFGlobal::Instance()->_game_time + kfqueue->_match_setting->_add_robot_time;
    }

    bool KFMatchRandRoom::AddPlayer( KFMatchPlayer* kfplayer )
    {
        KFMatchRoom::AddPlayer( kfplayer );

        // 更新匹配玩家数量
        SentMatchCountToClient();
        return CheckFull();
    }

    bool KFMatchRandRoom::IsMatched( KFMatchPlayer* kfplayer )
    {
        // 上限积分差距
        if ( kfplayer->_pb_player.grade() > _grade + _match_queue->_match_setting->_upper_grade )
        {
            return false;
        }

        // 下限积分差距
        if ( kfplayer->_pb_player.grade() + _match_queue->_match_setting->_lower_grade < _grade )
        {
            return false;
        }

        return KFMatchRoom::IsMatched( kfplayer );
    }

    bool KFMatchRandRoom::AddRobot()
    {
        if ( _next_add_robot_time > KFGlobal::Instance()->_game_time )
        {
            return false;
        }

        _next_add_robot_time = KFGlobal::Instance()->_game_time + _match_queue->_match_setting->_add_robot_time;
        auto addcount = __MIN__( _match_queue->_match_setting->_add_robot_count, _match_queue->_match_setting->_max_count - _player_list.Size() );

        do
        {
            auto kfrobot = CreateMatchRobot();
            _player_list.Insert( kfrobot->_id, kfrobot );
            __LOG_DEBUG__( "room=[{}] add robot=[{}] count=[{}]!", _id, kfrobot->_id, _player_list.Size() );

        } while ( ( --addcount ) > 0 );
        SentMatchCountToClient();

        return CheckFull();
    }

    void KFMatchRandRoom::SentMatchCountToClient()
    {
        KFMsg::MsgTellMatchCount tell;
        tell.set_count( _player_list.Size() );
        SendToRoom( KFMsg::MSG_TELL_MATCH_COUNT, &tell );
    }
}