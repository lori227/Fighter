// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CodeMessage.proto

#include "CodeMessage.pb.h"

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
namespace protobuf_CodeMessage_2eproto {
void InitDefaults() {
}

const ::google::protobuf::EnumDescriptor* file_level_enum_descriptors[1];
const ::google::protobuf::uint32 TableStruct::offsets[1] = {};
static const ::google::protobuf::internal::MigrationSchema* schemas = NULL;
static const ::google::protobuf::Message* const* file_default_instances = NULL;

void protobuf_AssignDescriptors() {
  AddDescriptors();
  AssignDescriptors(
      "CodeMessage.proto", schemas, file_default_instances, TableStruct::offsets,
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
      "\n\021CodeMessage.proto\022\005KFMsg*\204\002\n\017ProjectCo"
      "deEnum\022\016\n\nLogicError\020\000\022\022\n\014HeroNotExist\020\231"
      "\362\001\022\024\n\016MatchRequestOk\020\201\372\001\022\026\n\020MatchAlready"
      "Wait\020\202\372\001\022\021\n\013MatchInRoom\020\203\372\001\022\025\n\017MatchNotI"
      "nMatch\020\204\372\001\022\023\n\rMatchCancelOk\020\205\372\001\022\030\n\022Match"
      "AffirmTimeout\020\207\372\001\022\031\n\023MatchNotFighterHero"
      "\020\210\372\001\022\024\n\016MatchDataError\020\211\372\001\022\025\n\017RoomAllotB"
      "attle\020\345\372\001b\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 297);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "CodeMessage.proto", &protobuf_RegisterTypes);
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
}  // namespace protobuf_CodeMessage_2eproto
namespace KFMsg {
const ::google::protobuf::EnumDescriptor* ProjectCodeEnum_descriptor() {
  protobuf_CodeMessage_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_CodeMessage_2eproto::file_level_enum_descriptors[0];
}
bool ProjectCodeEnum_IsValid(int value) {
  switch (value) {
    case 0:
    case 31001:
    case 32001:
    case 32002:
    case 32003:
    case 32004:
    case 32005:
    case 32007:
    case 32008:
    case 32009:
    case 32101:
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

// @@protoc_insertion_point(global_scope)
