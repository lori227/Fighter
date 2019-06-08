local ltn12 = require "ltn12"
local http = require "socket.http"

local CHttpClient = class( "CHttpClient" )

function CHttpClient:ctor()
    self._version = "0.1.1"
end

function HttpRequest( url, method, senddata )
    local length = 0
    if senddata ~= nil then
        length = #senddata
    else
        senddata = ""
    end

    local response = {}
    local body, code, headers, status = http.request {
        method = method,
        url = url,
        headers = 
                {
                    ["Content-Type"] = "application/json; charset=utf-8";
                    ["Content-Length"] = length;
                },
        sink = ltn12.sink.table(response),
        source = ltn12.source.string(senddata),
    }

    local str = response[1]
    _log:LogInfo( "http result=["..str.."]" )
    return str
end

function CHttpClient:PostData( url, senddata )
    return HttpRequest( url, "POST", senddata )
end

function CHttpClient:PostJson( url, sendjson )
    local senddata = _json:encode( sendjson )
    if senddata == nil then
        _log:LogError( "url=["..url.."] json encode failed!" )
        return nil
    end

    local response = self:PostData( url, senddata )
    return _json:decode( response )
end

function CHttpClient:GetData( url, senddata )
    return HttpRequest( url, "GET", senddata )
end

function CHttpClient:GetJson( url, sendjson )
    local senddata = _json:encode( sendjson )
    if senddata == nil then
        _log:LogError( "url=["..url.."] json encode failed!" )
        return nil
    end

    local response = self:GetData( url, senddata )
    return _json:decode( response )
end

return CHttpClient