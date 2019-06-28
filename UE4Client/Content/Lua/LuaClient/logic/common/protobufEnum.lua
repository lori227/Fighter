
local ToStr = function(value)
    if (type(value) == "string") then
        return "\"" .. value .. "\""
    end

    return tostring(value)
end

local SetErrorIndex = function(t)
    setmetatable(t, {
        __index = function(t, k)
            error("Can\'t index not exist key-" .. tostring(t) .. "[" .. ToStr(k) .. "]" .. "\n" .. debug.traceback())
        end,
        __newindex = function(t, k, v)
            error("Can\'t newindex not exist key-" .. tostring(t) .. "[" .. ToStr(k) .. "]" .. "\n" .. debug.traceback())
        end,
    })
end

--protobuf枚舉
ProtobufEnum = 
{
    MSG_FRAME_CLIENT_BEGIN              = 0;        --pb3 需要0

    --display
    MSG_RESULT_DISPLAY                  = 1;        --提示显示
    MSG_COMMAND_REQ                     = 2;        --客户端发送GM指令请求

    --login
    MSG_LOGIN_REQ                       = 100;      --客户端登录验证请求
    MSG_LOGIN_ACK                       = 101;      --客户端登录验证结果
    MSG_LOGOUT_REQ                      = 102;      --客户端请求登出游戏
    MSG_TELL_BE_KICK                    = 103;      --被踢下线了

    MSG_START_MATCH_REQ                 = 3001,     --开始匹配 
    MSG_CANCEL_MATCH_REQ                = 3002,     --取消匹配
    MSG_INFORM_MATCH_RESULT             = 3003,     --通知匹配结果
    MSG_AFFIRM_MATCH_REQ                = 3004,     --请求确认匹配
    MSG_INFORM_BATTLE_REQ               = 3005,     --服务器通知战场信息
    MSG_INFORM_BATTLE_ACK               = 3006,     --客户端确认战场信息
    MSG_FINISH_ROOM_REQ                 = 3007,     --服务器通知战场房间结束
    

    --data
    MSG_SYNC_UPDATE_DATA                = 201;      --同步更新属性
    MSG_SYNC_ADD_DATA                   = 202;      --同步增加属性
    MSG_SYNC_REMOVE_DATA                = 203;      --同步删除属性
    MSG_REMOVE_DATA_REQ                 = 204;      --请求删除属性
    MSG_QUERY_PLAYER_REQ                = 205;      --查询玩家数据
    MSG_QUERY_PLAYER_ACK                = 206;      --查询玩家数据
    MSG_QUERY_BASIC_REQ                 = 207;      --查询玩家基本数据
    MSG_QUERY_BASIC_ACK                 = 208;      --查询基础数据
    MSG_SHOW_ELEMENT                    = 209;      --显示奖励
    MSG_REQUEST_SYNC_REQ                = 210;      --客户端请求同步
    MSG_CANCEL_SYNC_REQ                 = 211;      --客户端取消同步
    
    --attribute
    MSG_SET_NAME_REQ                    = 300;      --设置名字
    MSG_SET_SEX_REQ                     = 301;      --设置性别
    MSG_ACHIEVE_REWARD_REQ              = 302;      --领取成就奖励
    MSG_TASK_REWARD_REQ                 = 303;      --领取任务奖励
    MSG_ACTIVITY_REWARD_REQ             = 304;      --领取活动奖励
    MSG_COMPOUND_REQ                    = 305;      --属性合成请求
    MSG_USE_ITEM_REQ                    = 306;      --使用道具
    MSG_SEVEN_SIGNIN_REWARD_REQ         = 307;      --领取7天签到奖励


    MSG_OPEN_RECRUIT_REQ                = 3101;     --打开招募所
    MSG_REFRESH_RECRUIT_REQ             = 3102;     --刷新招募英雄
    MSG_CHOOSE_DIVISOR_REQ              = 3103;     --选择偏好因子
    MSG_REMOVE_DIVISOR_REQ              = 3104;     --取消偏好因子
    MSG_RECRUIT_HERO_REQ                = 3105;     --招募英雄

}

SetErrorIndex(ProtobufEnum)


