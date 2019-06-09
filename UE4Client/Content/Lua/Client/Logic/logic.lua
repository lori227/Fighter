local CDisplay = require "Logic/display"
local CPlayer = require "Logic/player"

_display = CDisplay.new()
_player = CPlayer.new()

-------------------------------------------------------
-------------------------------------------------------
local M = {}

function M.Init()
    
    -- display
    _display:Init()
    _player:Init()
end

return M