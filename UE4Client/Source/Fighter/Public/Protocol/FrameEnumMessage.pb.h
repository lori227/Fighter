// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: FrameEnumMessage.proto

#ifndef PROTOBUF_INCLUDED_FrameEnumMessage_2eproto
#define PROTOBUF_INCLUDED_FrameEnumMessage_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_FrameEnumMessage_2eproto LIBPROTOC_EXPORT

namespace protobuf_FrameEnumMessage_2eproto {
// Internal implementation detail -- do not use these members.
struct LIBPROTOC_EXPORT TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void LIBPROTOC_EXPORT AddDescriptors();
}  // namespace protobuf_FrameEnumMessage_2eproto
namespace KFMsg {
}  // namespace KFMsg
namespace KFMsg {

enum ChannelEnum {
  UnknowChannel = 0,
  Internal = 1,
  WeiXin = 2,
  Steam = 3,
  ChannelEnum_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  ChannelEnum_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
LIBPROTOC_EXPORT bool ChannelEnum_IsValid(int value);
const ChannelEnum ChannelEnum_MIN = UnknowChannel;
const ChannelEnum ChannelEnum_MAX = Steam;
const int ChannelEnum_ARRAYSIZE = ChannelEnum_MAX + 1;

LIBPROTOC_EXPORT const ::google::protobuf::EnumDescriptor* ChannelEnum_descriptor();
inline const ::std::string& ChannelEnum_Name(ChannelEnum value) {
  return ::google::protobuf::internal::NameOfEnum(
    ChannelEnum_descriptor(), value);
}
inline bool ChannelEnum_Parse(
    const ::std::string& name, ChannelEnum* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ChannelEnum>(
    ChannelEnum_descriptor(), name, value);
}
enum KickEnum {
  UnknowKick = 0,
  KickByLogin = 1,
  KickByPlatform = 2,
  KickEnum_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  KickEnum_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
LIBPROTOC_EXPORT bool KickEnum_IsValid(int value);
const KickEnum KickEnum_MIN = UnknowKick;
const KickEnum KickEnum_MAX = KickByPlatform;
const int KickEnum_ARRAYSIZE = KickEnum_MAX + 1;

LIBPROTOC_EXPORT const ::google::protobuf::EnumDescriptor* KickEnum_descriptor();
inline const ::std::string& KickEnum_Name(KickEnum value) {
  return ::google::protobuf::internal::NameOfEnum(
    KickEnum_descriptor(), value);
}
inline bool KickEnum_Parse(
    const ::std::string& name, KickEnum* value) {
  return ::google::protobuf::internal::ParseNamedEnum<KickEnum>(
    KickEnum_descriptor(), name, value);
}
enum StatusEnum {
  InitStatus = 0,
  DoneStatus = 1,
  ReceiveStatus = 2,
  Remove = 3,
  ReceiveRemove = 4,
  StatusEnum_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  StatusEnum_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
LIBPROTOC_EXPORT bool StatusEnum_IsValid(int value);
const StatusEnum StatusEnum_MIN = InitStatus;
const StatusEnum StatusEnum_MAX = ReceiveRemove;
const int StatusEnum_ARRAYSIZE = StatusEnum_MAX + 1;

LIBPROTOC_EXPORT const ::google::protobuf::EnumDescriptor* StatusEnum_descriptor();
inline const ::std::string& StatusEnum_Name(StatusEnum value) {
  return ::google::protobuf::internal::NameOfEnum(
    StatusEnum_descriptor(), value);
}
inline bool StatusEnum_Parse(
    const ::std::string& name, StatusEnum* value) {
  return ::google::protobuf::internal::ParseNamedEnum<StatusEnum>(
    StatusEnum_descriptor(), name, value);
}
enum UUIDEnum {
  UUidLogic = 0,
  UUidAccount = 1,
  UUidPlayer = 2,
  UUidItem = 3,
  UUidHero = 4,
  UUidGroup = 5,
  UUidGuild = 6,
  UUidBattle = 7,
  UUIDEnum_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  UUIDEnum_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
LIBPROTOC_EXPORT bool UUIDEnum_IsValid(int value);
const UUIDEnum UUIDEnum_MIN = UUidLogic;
const UUIDEnum UUIDEnum_MAX = UUidBattle;
const int UUIDEnum_ARRAYSIZE = UUIDEnum_MAX + 1;

LIBPROTOC_EXPORT const ::google::protobuf::EnumDescriptor* UUIDEnum_descriptor();
inline const ::std::string& UUIDEnum_Name(UUIDEnum value) {
  return ::google::protobuf::internal::NameOfEnum(
    UUIDEnum_descriptor(), value);
}
inline bool UUIDEnum_Parse(
    const ::std::string& name, UUIDEnum* value) {
  return ::google::protobuf::internal::ParseNamedEnum<UUIDEnum>(
    UUIDEnum_descriptor(), name, value);
}
enum MailEnum {
  UnknowMail = 0,
  GlobalMail = 1,
  PersonMail = 2,
  MailEnum_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  MailEnum_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
LIBPROTOC_EXPORT bool MailEnum_IsValid(int value);
const MailEnum MailEnum_MIN = UnknowMail;
const MailEnum MailEnum_MAX = PersonMail;
const int MailEnum_ARRAYSIZE = MailEnum_MAX + 1;

LIBPROTOC_EXPORT const ::google::protobuf::EnumDescriptor* MailEnum_descriptor();
inline const ::std::string& MailEnum_Name(MailEnum value) {
  return ::google::protobuf::internal::NameOfEnum(
    MailEnum_descriptor(), value);
}
inline bool MailEnum_Parse(
    const ::std::string& name, MailEnum* value) {
  return ::google::protobuf::internal::ParseNamedEnum<MailEnum>(
    MailEnum_descriptor(), name, value);
}
enum RankEnum {
  UnknowRank = 0,
  TotalRank = 1,
  ZoneRank = 2,
  RankEnum_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  RankEnum_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
LIBPROTOC_EXPORT bool RankEnum_IsValid(int value);
const RankEnum RankEnum_MIN = UnknowRank;
const RankEnum RankEnum_MAX = ZoneRank;
const int RankEnum_ARRAYSIZE = RankEnum_MAX + 1;

LIBPROTOC_EXPORT const ::google::protobuf::EnumDescriptor* RankEnum_descriptor();
inline const ::std::string& RankEnum_Name(RankEnum value) {
  return ::google::protobuf::internal::NameOfEnum(
    RankEnum_descriptor(), value);
}
inline bool RankEnum_Parse(
    const ::std::string& name, RankEnum* value) {
  return ::google::protobuf::internal::ParseNamedEnum<RankEnum>(
    RankEnum_descriptor(), name, value);
}
enum StateEnum {
  UnknowState = 0,
  OnlineState = 1,
  GroupState = 2,
  MatchState = 3,
  PlayingState = 4,
  OfflineState = 5,
  StateEnum_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  StateEnum_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
LIBPROTOC_EXPORT bool StateEnum_IsValid(int value);
const StateEnum StateEnum_MIN = UnknowState;
const StateEnum StateEnum_MAX = OfflineState;
const int StateEnum_ARRAYSIZE = StateEnum_MAX + 1;

LIBPROTOC_EXPORT const ::google::protobuf::EnumDescriptor* StateEnum_descriptor();
inline const ::std::string& StateEnum_Name(StateEnum value) {
  return ::google::protobuf::internal::NameOfEnum(
    StateEnum_descriptor(), value);
}
inline bool StateEnum_Parse(
    const ::std::string& name, StateEnum* value) {
  return ::google::protobuf::internal::ParseNamedEnum<StateEnum>(
    StateEnum_descriptor(), name, value);
}
enum InviteEnum {
  UnknowInvite = 0,
  Consent = 1,
  Refuse = 2,
  Delete = 3,
  RefuseMinute = 4,
  InviteEnum_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  InviteEnum_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
LIBPROTOC_EXPORT bool InviteEnum_IsValid(int value);
const InviteEnum InviteEnum_MIN = UnknowInvite;
const InviteEnum InviteEnum_MAX = RefuseMinute;
const int InviteEnum_ARRAYSIZE = InviteEnum_MAX + 1;

LIBPROTOC_EXPORT const ::google::protobuf::EnumDescriptor* InviteEnum_descriptor();
inline const ::std::string& InviteEnum_Name(InviteEnum value) {
  return ::google::protobuf::internal::NameOfEnum(
    InviteEnum_descriptor(), value);
}
inline bool InviteEnum_Parse(
    const ::std::string& name, InviteEnum* value) {
  return ::google::protobuf::internal::ParseNamedEnum<InviteEnum>(
    InviteEnum_descriptor(), name, value);
}
// ===================================================================


// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace KFMsg

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::KFMsg::ChannelEnum> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::KFMsg::ChannelEnum>() {
  return ::KFMsg::ChannelEnum_descriptor();
}
template <> struct is_proto_enum< ::KFMsg::KickEnum> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::KFMsg::KickEnum>() {
  return ::KFMsg::KickEnum_descriptor();
}
template <> struct is_proto_enum< ::KFMsg::StatusEnum> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::KFMsg::StatusEnum>() {
  return ::KFMsg::StatusEnum_descriptor();
}
template <> struct is_proto_enum< ::KFMsg::UUIDEnum> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::KFMsg::UUIDEnum>() {
  return ::KFMsg::UUIDEnum_descriptor();
}
template <> struct is_proto_enum< ::KFMsg::MailEnum> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::KFMsg::MailEnum>() {
  return ::KFMsg::MailEnum_descriptor();
}
template <> struct is_proto_enum< ::KFMsg::RankEnum> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::KFMsg::RankEnum>() {
  return ::KFMsg::RankEnum_descriptor();
}
template <> struct is_proto_enum< ::KFMsg::StateEnum> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::KFMsg::StateEnum>() {
  return ::KFMsg::StateEnum_descriptor();
}
template <> struct is_proto_enum< ::KFMsg::InviteEnum> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::KFMsg::InviteEnum>() {
  return ::KFMsg::InviteEnum_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_FrameEnumMessage_2eproto
