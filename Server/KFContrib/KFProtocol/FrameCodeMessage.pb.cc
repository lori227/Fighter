// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: FrameCodeMessage.proto

#ifdef _MSC_VER
	#pragma warning(push)
	#pragma warning(disable : 4125)
	#pragma warning(disable : 4668)
	#pragma warning(disable : 4800)
	#pragma warning(disable : 4647)
#endif

#include "FrameCodeMessage.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)

namespace KFMsg {
}  // namespace KFMsg
namespace protobuf_FrameCodeMessage_2eproto {
void InitDefaults() {
}

const ::google::protobuf::EnumDescriptor* file_level_enum_descriptors[1];
const ::google::protobuf::uint32 TableStruct::offsets[1] = {};
static const ::google::protobuf::internal::MigrationSchema* schemas = NULL;
static const ::google::protobuf::Message* const* file_default_instances = NULL;

void protobuf_AssignDescriptors() {
  AddDescriptors();
  AssignDescriptors(
      "FrameCodeMessage.proto", schemas, file_default_instances, TableStruct::offsets,
      NULL, file_level_enum_descriptors, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\026FrameCodeMessage.proto\022\005KFMsg*\376\037\n\rFram"
      "eCodeEnum\022\t\n\005Error\020\000\022\006\n\002Ok\020\001\022\022\n\rHttpData"
      "Error\020\220N\022\025\n\020AuthDatabaseBusy\020\221N\022\023\n\016AuthS"
      "erverBusy\020\222N\022\023\n\016ZoneServerBusy\020\223N\022\025\n\020Zon"
      "eDatabaseBusy\020\224N\022\025\n\020NameDatabaseBusy\020\225N\022"
      "\023\n\016DataServerBusy\020\226N\022\023\n\016MailServerBusy\020\227"
      "N\022\023\n\016RankServerBusy\020\230N\022\027\n\022PublicDatabase"
      "Busy\020\231N\022\027\n\022RelationServerBusy\020\232N\022\024\n\017Matc"
      "hServerBusy\020\233N\022\026\n\021LoginDatabaseBusy\020\234N\022\025"
      "\n\020PublicServerBusy\020\235N\022\024\n\017LogicServerBusy"
      "\020\236N\022\024\n\017RouteServerBusy\020\237N\022\023\n\016AccountIsEm"
      "pty\020\371U\022\026\n\021ActivationAccount\020\372U\022\032\n\025Invali"
      "dActivationCode\020\373U\022\030\n\023ActivationCodeErro"
      "r\020\374U\022\024\n\017LoginTokenError\020\375U\022\023\n\016BanForbidL"
      "ogin\020\376U\022\026\n\021ChannelNotSupport\020\377U\022\023\n\016Chann"
      "elNotOpen\020\200V\022\021\n\014ChannelError\020\201V\022\020\n\013WeiXi"
      "nError\020\202V\022\024\n\017WeiXinUserError\020\203V\022\025\n\020WeiXi"
      "nTokenError\020\204V\022\024\n\017WeiXinCodeError\020\205V\022\027\n\022"
      "WeiXinTokenTimeout\020\206V\022\017\n\nSteamError\020\207V\022\023"
      "\n\016SteamDataError\020\210V\022\023\n\016SteamAuthError\020\211V"
      "\022\022\n\rIpInBlackList\020\212V\022\027\n\022AccountInBlackLi"
      "st\020\213V\022\030\n\023LoginNotInWhiteList\020\214V\022\032\n\025Login"
      "ServerStopStatus\020\215V\022\034\n\027VersionNotCompati"
      "bility\020\341]\022\021\n\014LoginIsClose\020\342]\022\027\n\022LoginNoL"
      "oginServer\020\343]\022\024\n\017LoginSystemBusy\020\344]\022\031\n\024L"
      "oginWorldSystemBusy\020\345]\022\026\n\021LoginNoGameSer"
      "ver\020\346]\022\030\n\023LoginGameServerBusy\020\347]\022\031\n\024Logi"
      "nBindPlayerError\020\350]\022\030\n\023LoginLoadDataFail"
      "ed\020\351]\022\027\n\022LoginAlreadyOnline\020\352]\022\033\n\026LoginC"
      "reatePlayerError\020\353]\022\026\n\021QueryPlayerFailed"
      "\020\305^\022\025\n\020NameAlreadyExist\020\306^\022\016\n\tNameSetOk\020"
      "\307^\022\024\n\017NameLengthError\020\310^\022\024\n\017NameFilterEr"
      "ror\020\311^\022\016\n\tNameEmpty\020\312^\022\023\n\016NameAlreadySet"
      "\020\313^\022\r\n\010SexSetOK\020\314^\022\022\n\rDataNotEnough\020\315^\022\017"
      "\n\nDataIsFull\020\316^\022\026\n\021ElementParseError\020\317^\022"
      "\023\n\016NameCanNotFind\020\320^\022\021\n\014RoleNotExist\020\321^\022"
      "\026\n\021AchieveCanNotFind\020\250_\022\032\n\025AchieveCanNot"
      "FindData\020\251_\022\023\n\016AchieveNotDone\020\252_\022\033\n\026Achi"
      "eveAlreadyReceived\020\253_\022\025\n\020AchieveReceiveO"
      "k\020\254_\022\032\n\025ConditionSettingError\020\332_\022\025\n\020Drop"
      "SettingError\020\333_\022\023\n\016DropValueError\020\334_\022\023\n\016"
      "TaskCanNotFind\020\214`\022\027\n\022TaskCanNotFindData\020"
      "\215`\022\020\n\013TaskNotDone\020\216`\022\026\n\021TaskAlreadyRewar"
      "d\020\217`\022\021\n\014TaskRewardOk\020\220`\022\022\n\rTaskNotActive"
      "\020\221`\022\027\n\022TaskAlreadyReceive\020\222`\022\030\n\023TaskNotP"
      "reCondition\020\223`\022\026\n\021TaskReceiveFailed\020\224`\022\022"
      "\n\rTaskReceiveOk\020\225`\022\022\n\rTaskAreaError\020\226`\022\035"
      "\n\030TaskChainSettingNotExist\020\240`\022\027\n\022Activit"
      "yCanNotFind\020\360`\022\033\n\026ActivityCanNotFindData"
      "\020\361`\022\034\n\027ActivityAlreadyReceived\020\362`\022\024\n\017Act"
      "ivityNotDone\020\363`\022\025\n\020ActivityRewardOk\020\364`\022\025"
      "\n\020CompoundNotExist\020\324a\022\017\n\nCompoundOk\020\325a\022\030"
      "\n\023ItemSettingNotExist\020\270b\022\025\n\020ItemDataNotE"
      "xist\020\271b\022\030\n\023ItemSplitCountError\020\272b\022\025\n\020Ite"
      "mMergeIdError\020\273b\022\030\n\023ItemOverlayCountMax\020"
      "\274b\022\022\n\rItemCanNotUse\020\275b\022\022\n\rItemUseFailed\020"
      "\276b\022\025\n\020ItemBagNameError\020\277b\022\027\n\022ItemMoveCou"
      "ntError\020\300b\022\020\n\013ItemBagFull\020\301b\022\023\n\016ItemMove"
      "Failed\020\302b\022\024\n\017ItemCanNotStore\020\303b\022\023\n\016ItemI"
      "ndexError\020\304b\022\030\n\023ItemCanNotUseStatus\020\305b\022\016"
      "\n\tItemUseOk\020\306b\022\024\n\017ItemUseToHeroOk\020\307b\022\017\n\n"
      "ItemSortOk\020\310b\022\022\n\rItemBagIsFull\020\311b\022\026\n\021Ite"
      "mBagCanNotMove\020\312b\022\027\n\022ItemBagCanNotClean\020"
      "\313b\022\024\n\017ItemTabNotExist\020\314b\022\023\n\016ItemCanNotSe"
      "ll\020\315b\022\027\n\022ItemSellCountError\020\317b\022\021\n\014SignIn"
      "NotDay\020\234c\022\025\n\020SignInCanNotFind\020\235c\022\030\n\023Sign"
      "InRewardAlready\020\236c\022\023\n\016SignInRewardOk\020\237c\022"
      "\021\n\014MailNotExist\020\200d\022\020\n\013MailTimeOut\020\201d\022\025\n\020"
      "MailDeleteFailed\020\202d\022\030\n\023MailAlreadyReceiv"
      "ed\020\203d\022\026\n\021MailNotHaveReward\020\204d\022\033\n\026StoreGo"
      "odsSettingError\020\344d\022\027\n\022StoreBuyCountError"
      "\020\345d\022\033\n\026StoreGoodsBuyTimeError\020\346d\022\025\n\020Stor"
      "eOutOfLimits\020\347d\022\022\n\rStoreLackCost\020\350d\022\026\n\021S"
      "toreSettingError\020\351d\022\017\n\nStoreBuyOK\020\352d\022\026\n\021"
      "StoreNotHaveGoods\020\353d\022\024\n\017StoreNotRefresh\020"
      "\354d\022\023\n\016StoreStockLack\020\355d\022\032\n\025StoreNotRefre"
      "shManual\020\356d\022\032\n\025StoreRefreshTimeError\020\357d\022"
      "\023\n\016StoreRefreshOk\020\360d\022\032\n\025StoreRefreshType"
      "Error\020\361d\022\032\n\025StoreRefreshCostEmpty\020\362d\022\030\n\023"
      "StoreGoodsRefreshOk\020\363d\022\027\n\022StoreBuyIndexE"
      "rror\020\364d\022\017\n\nPayIdError\020\310e\022\021\n\014PayDataError"
      "\020\311e\022\021\n\014RankNotExist\020\254f\022\027\n\022QueryBasicNotE"
      "xist\020\220g\022\027\n\022MessageFilterError\020\364g\022\024\n\017Rela"
      "tionAlready\020\365g\022\026\n\021RelationSelfLimit\020\366g\022\026"
      "\n\021RelationInviteReq\020\367g\022\035\n\030RelationRefuse"
      "YourInvite\020\370g\022\022\n\rRelationAddOk\020\371g\022\025\n\020Rel"
      "ationNotExist\020\372g\022\022\n\rRelationDelOk\020\373g\022\031\n\024"
      "RelationRefuseInvite\020\374g\022\030\n\023RelationTarge"
      "tLimit\020\375g\022\032\n\025RelationInviteAlready\020\376g\022\030\n"
      "\023RelationInviteLimit\020\377g\022\025\n\020RelationInvit"
      "eOk\020\200h\022\033\n\026RelationInviteNotExist\020\201h\022\031\n\024R"
      "elationSettingError\020\202h\022\026\n\021RelationDataEr"
      "ror\020\203h\022\024\n\017FriendLinessAdd\020\204h\022\022\n\rChatNotF"
      "riend\020\331h\022\030\n\023ChatFriendNotOnline\020\332h\022\032\n\025Ch"
      "atIntervalTimeLimit\020\333h\022\020\n\013TeamAlready\020\275i"
      "\022\023\n\016TeamNameFilter\020\276i\022\023\n\016TeamInfoFilter\020"
      "\277i\022\025\n\020TeamSettingError\020\300i\022\017\n\nTeamJoinOk\020"
      "\301i\022\021\n\014TeamNoInTeam\020\302i\022\024\n\017TeamNoInCaptain"
      "\020\303i\022\026\n\021TeamNotHaveMember\020\304i\022\016\n\tTeamLeave"
      "\020\305i\022\017\n\nTeamBeKick\020\306i\022\021\n\014TeamDissolve\020\307i\022"
      "\017\n\nTeamIsFull\020\310i\022\022\n\rTeamNotOnline\020\311i\022\020\n\013"
      "TeamPlaying\020\312i\022\021\n\014TeamInviteOk\020\313i\022\020\n\013Tea"
      "mApplyOk\020\314i\022\020\n\013TeamIdError\020\315i\022\021\n\014TeamNot"
      "Exist\020\316ib\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 4136);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "FrameCodeMessage.proto", &protobuf_RegisterTypes);
}

void AddDescriptors() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;
}  // namespace protobuf_FrameCodeMessage_2eproto
namespace KFMsg {
const ::google::protobuf::EnumDescriptor* FrameCodeEnum_descriptor() {
  protobuf_FrameCodeMessage_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_FrameCodeMessage_2eproto::file_level_enum_descriptors[0];
}
bool FrameCodeEnum_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 10000:
    case 10001:
    case 10002:
    case 10003:
    case 10004:
    case 10005:
    case 10006:
    case 10007:
    case 10008:
    case 10009:
    case 10010:
    case 10011:
    case 10012:
    case 10013:
    case 10014:
    case 10015:
    case 11001:
    case 11002:
    case 11003:
    case 11004:
    case 11005:
    case 11006:
    case 11007:
    case 11008:
    case 11009:
    case 11010:
    case 11011:
    case 11012:
    case 11013:
    case 11014:
    case 11015:
    case 11016:
    case 11017:
    case 11018:
    case 11019:
    case 11020:
    case 11021:
    case 12001:
    case 12002:
    case 12003:
    case 12004:
    case 12005:
    case 12006:
    case 12007:
    case 12008:
    case 12009:
    case 12010:
    case 12011:
    case 12101:
    case 12102:
    case 12103:
    case 12104:
    case 12105:
    case 12106:
    case 12107:
    case 12108:
    case 12109:
    case 12110:
    case 12111:
    case 12112:
    case 12113:
    case 12200:
    case 12201:
    case 12202:
    case 12203:
    case 12204:
    case 12250:
    case 12251:
    case 12252:
    case 12300:
    case 12301:
    case 12302:
    case 12303:
    case 12304:
    case 12305:
    case 12306:
    case 12307:
    case 12308:
    case 12309:
    case 12310:
    case 12320:
    case 12400:
    case 12401:
    case 12402:
    case 12403:
    case 12404:
    case 12500:
    case 12501:
    case 12600:
    case 12601:
    case 12602:
    case 12603:
    case 12604:
    case 12605:
    case 12606:
    case 12607:
    case 12608:
    case 12609:
    case 12610:
    case 12611:
    case 12612:
    case 12613:
    case 12614:
    case 12615:
    case 12616:
    case 12617:
    case 12618:
    case 12619:
    case 12620:
    case 12621:
    case 12623:
    case 12700:
    case 12701:
    case 12702:
    case 12703:
    case 12800:
    case 12801:
    case 12802:
    case 12803:
    case 12804:
    case 12900:
    case 12901:
    case 12902:
    case 12903:
    case 12904:
    case 12905:
    case 12906:
    case 12907:
    case 12908:
    case 12909:
    case 12910:
    case 12911:
    case 12912:
    case 12913:
    case 12914:
    case 12915:
    case 12916:
    case 13000:
    case 13001:
    case 13100:
    case 13200:
    case 13300:
    case 13301:
    case 13302:
    case 13303:
    case 13304:
    case 13305:
    case 13306:
    case 13307:
    case 13308:
    case 13309:
    case 13310:
    case 13311:
    case 13312:
    case 13313:
    case 13314:
    case 13315:
    case 13316:
    case 13401:
    case 13402:
    case 13403:
    case 13501:
    case 13502:
    case 13503:
    case 13504:
    case 13505:
    case 13506:
    case 13507:
    case 13508:
    case 13509:
    case 13510:
    case 13511:
    case 13512:
    case 13513:
    case 13514:
    case 13515:
    case 13516:
    case 13517:
    case 13518:
      return true;
    default:
      return false;
  }
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace KFMsg
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

#ifdef _MSC_VER
	#pragma warning(  pop  )
#endif

// @@protoc_insertion_point(global_scope)
