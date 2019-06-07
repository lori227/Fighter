print( _VERSION )

require "../Common/class"
require "../Common/table"


_define = require "../Common/define"

local CJson = require "../Common/json"
local CMessage = require "../Common/message"
local CNetClient = require "../Common/netclient"
local CKernel = require "../Common/kernel"
local CLog = require "../Common/log"
local CProtobuf = require "../Common/protobuf"
local CHttpClient = require "../Common/httpclient"
local CProtobuf = require "../Common/protobuf"

_json = CJson.new()
_log = CLog.new()
_kernel = CKernel.new()
_message = CMessage.new()
_protobuf = CProtobuf.new()
_net_client = CNetClient.new()
_http_client = CHttpClient.new()

