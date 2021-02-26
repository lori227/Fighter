#include "KFMatchRandRoom.h"
#include "KFMatchQueue.h"

namespace KFrame
{
    KFMatchRandRoom::KFMatchRandRoom()
    {
        _type = KFMatchEnum::RandRoom;
    }

    void KFMatchRandRoom::InitRoom( std::shared_ptr<KFMatchQueue> match_queue, std::shared_ptr<KFMatchPlayer> match_player,
                                    const std::string& title, const std::string& password, bool add_robot )
    {
        KFMatchRoom::InitRoom( match_queue, match_player, title, password, add_robot );
        _next_add_robot_time = KFGlobal::Instance()->_game_time + match_queue->_match_setting->_add_robot_time;
    }

    void KFMatchRandRoom::SaveTo( KFMsg::PBMatchRoom* pb_room, bool is_player_list )
    {
        KFMatchRoom::SaveTo( pb_room, is_player_list );
    }

    bool KFMatchRandRoom::AddPlayer( std::shared_ptr<KFMatchPlayer> match_player )
    {
        KFMatchRoom::AddPlayer( match_player );
        __LOG_DEBUG__( "room=[{}] add player=[{}] count=[{}]!", _id, match_player->_id, _player_list.Size() );

        // 更新匹配玩家数量
        SentMatchCountToClient();
        return CheckFull();
    }

    bool KFMatchRandRoom::IsMatched( std::shared_ptr<KFMatchPlayer> match_player )
    {
        // 上限积分差距
        if ( match_player->_pb_player.grade() > _grade + _match_queue->_match_setting->_upper_grade )
        {
            return false;
        }

        // 下限积分差距
        if ( match_player->_pb_player.grade() + _match_queue->_match_setting->_lower_grade < _grade )
        {
            return false;
        }

        return KFMatchRoom::IsMatched( match_player );
    }

    bool KFMatchRandRoom::AddRobot()
    {
        if ( _next_add_robot_time > KFGlobal::Instance()->_game_time )
        {
            return false;
        }

        _next_add_robot_time = KFGlobal::Instance()->_game_time + _match_queue->_match_setting->_add_robot_time;
        auto add_count = __MIN__( _match_queue->_match_setting->_add_robot_count, _match_queue->_match_setting->_max_count - _player_list.Size() );

        do
        {
            auto robot = CreateMatchRobot();
            _player_list.Insert( robot->_id, robot );
            __LOG_DEBUG__( "room=[{}] add robot=[{}] count=[{}]!", _id, robot->_id, _player_list.Size() );

        } while ( ( --add_count ) > 0 );
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