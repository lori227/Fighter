// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: EnumMessage.proto

#ifdef _MSC_VER
	#pragma warning(push)
	#pragma warning(disable : 4125)
	#pragma warning(disable : 4668)
	#pragma warning(disable : 4800)
	#pragma warning(disable : 4647)
#endif

#include "EnumMessage.pb.h"

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
namespace protobuf_EnumMessage_2eproto {
void InitDefaults() {
}

const ::google::protobuf::EnumDescriptor* file_level_enum_descriptors[2];
const ::google::protobuf::uint32 TableStruct::offsets[1] = {};
static const ::google::protobuf::internal::MigrationSchema* schemas = NULL;
static const ::google::protobuf::Message* const* file_default_instances = NULL;

void protobuf_AssignDescriptors() {
  AddDescriptors();
  AssignDescriptors(
      "EnumMessage.proto", schemas, file_default_instances, TableStruct::offsets,
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
      "\n\021EnumMessage.proto\022\005KFMsg*5\n\010CampEnum\022\016"
      "\n\nUnknowCamp\020\000\022\013\n\007RedCamp\020\001\022\014\n\010BlueCamp\020"
      "\002*,\n\022PlayerStatusEnumEx\022\026\n\022UnknowPlayerS"
      "tatus\020\000b\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 135);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "EnumMessage.proto", &protobuf_RegisterTypes);
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
}  // namespace protobuf_EnumMessage_2eproto
namespace KFMsg {
const ::google::protobuf::EnumDescriptor* CampEnum_descriptor() {
  protobuf_EnumMessage_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_EnumMessage_2eproto::file_level_enum_descriptors[0];
}
bool CampEnum_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* PlayerStatusEnumEx_descriptor() {
  protobuf_EnumMessage_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_EnumMessage_2eproto::file_level_enum_descriptors[1];
}
bool PlayerStatusEnumEx_IsValid(int value) {
  switch (value) {
    case 0:
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
