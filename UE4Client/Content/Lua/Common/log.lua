local M = {}

local function Log( level, content )
    FLuaBind.Log( level, content )
end

-- info
function M.LogInfo( content )
    Log( 5, content )
end

-- warn
function M.LogWarn( content )
    Log( 3, content )
end

-- error
function M.LogError( content )
    Log( 2, content )
end


return M