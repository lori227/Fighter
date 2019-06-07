local CLog = class( "CLog" )

function CLog:ctor()

end

function CLog:Log( level, content )
    FLuaBind.Log( level, content )
end

-- info
function CLog:LogInfo( content )
    self:Log( 5, content )
end

-- warn
function CLog:LogWarn( content )
    self:Log( 3, content )
end

-- error
function CLog:LogError( content )
    self:Log( 2, content )
end

return CLog