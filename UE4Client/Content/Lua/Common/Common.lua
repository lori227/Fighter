print( _VERSION )

require "../Common/class"
require "../Common/table"

_pbc = require "../Common/pbc"
_define = require "../Common/define"

local CJson = require "../Common/json"
local CMessage = require "../Common/message"
local CNetClient = require "../Common/netclient"
local CKernel = require "../Common/kernel"
local CLog = require "../Common/log"
local CHttpClient = require "../Common/httpclient"

_json = CJson.new()
_log = CLog.new()
_kernel = CKernel.new()
_message = CMessage.new()
_net_client = CNetClient.new()
_http_client = CHttpClient.new()

