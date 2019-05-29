// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: DefineMessage.proto

#ifndef PROTOBUF_INCLUDED_DefineMessage_2eproto
#define PROTOBUF_INCLUDED_DefineMessage_2eproto

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
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "FrameDefineMessage.pb.h"
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_DefineMessage_2eproto LIBPROTOC_EXPORT

namespace protobuf_DefineMessage_2eproto {
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
}  // namespace protobuf_DefineMessage_2eproto
namespace KFMsg {
class PBMatchPlayer;
class PBMatchPlayerDefaultTypeInternal;
LIBPROTOC_EXPORT extern PBMatchPlayerDefaultTypeInternal _PBMatchPlayer_default_instance_;
}  // namespace KFMsg
namespace google {
namespace protobuf {
template<> LIBPROTOC_EXPORT ::KFMsg::PBMatchPlayer* Arena::CreateMaybeMessage<::KFMsg::PBMatchPlayer>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace KFMsg {

// ===================================================================

class LIBPROTOC_EXPORT PBMatchPlayer : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:KFMsg.PBMatchPlayer) */ {
 public:
  PBMatchPlayer();
  virtual ~PBMatchPlayer();

  PBMatchPlayer(const PBMatchPlayer& from);

  inline PBMatchPlayer& operator=(const PBMatchPlayer& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  PBMatchPlayer(PBMatchPlayer&& from) noexcept
    : PBMatchPlayer() {
    *this = ::std::move(from);
  }

  inline PBMatchPlayer& operator=(PBMatchPlayer&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const PBMatchPlayer& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const PBMatchPlayer* internal_default_instance() {
    return reinterpret_cast<const PBMatchPlayer*>(
               &_PBMatchPlayer_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(PBMatchPlayer* other);
  friend void swap(PBMatchPlayer& a, PBMatchPlayer& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline PBMatchPlayer* New() const final {
    return CreateMaybeMessage<PBMatchPlayer>(NULL);
  }

  PBMatchPlayer* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<PBMatchPlayer>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const PBMatchPlayer& from);
  void MergeFrom(const PBMatchPlayer& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(PBMatchPlayer* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // bytes name = 2;
  void clear_name();
  static const int kNameFieldNumber = 2;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  #if LANG_CXX11
  void set_name(::std::string&& value);
  #endif
  void set_name(const char* value);
  void set_name(const void* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // uint64 id = 1;
  void clear_id();
  static const int kIdFieldNumber = 1;
  ::google::protobuf::uint64 id() const;
  void set_id(::google::protobuf::uint64 value);

  // uint64 serverid = 3;
  void clear_serverid();
  static const int kServeridFieldNumber = 3;
  ::google::protobuf::uint64 serverid() const;
  void set_serverid(::google::protobuf::uint64 value);

  // bool isrobot = 4;
  void clear_isrobot();
  static const int kIsrobotFieldNumber = 4;
  bool isrobot() const;
  void set_isrobot(bool value);

  // uint32 heroid = 5;
  void clear_heroid();
  static const int kHeroidFieldNumber = 5;
  ::google::protobuf::uint32 heroid() const;
  void set_heroid(::google::protobuf::uint32 value);

  // uint32 grade = 6;
  void clear_grade();
  static const int kGradeFieldNumber = 6;
  ::google::protobuf::uint32 grade() const;
  void set_grade(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:KFMsg.PBMatchPlayer)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::uint64 id_;
  ::google::protobuf::uint64 serverid_;
  bool isrobot_;
  ::google::protobuf::uint32 heroid_;
  ::google::protobuf::uint32 grade_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_DefineMessage_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// PBMatchPlayer

// uint64 id = 1;
inline void PBMatchPlayer::clear_id() {
  id_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 PBMatchPlayer::id() const {
  // @@protoc_insertion_point(field_get:KFMsg.PBMatchPlayer.id)
  return id_;
}
inline void PBMatchPlayer::set_id(::google::protobuf::uint64 value) {
  
  id_ = value;
  // @@protoc_insertion_point(field_set:KFMsg.PBMatchPlayer.id)
}

// bytes name = 2;
inline void PBMatchPlayer::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& PBMatchPlayer::name() const {
  // @@protoc_insertion_point(field_get:KFMsg.PBMatchPlayer.name)
  return name_.GetNoArena();
}
inline void PBMatchPlayer::set_name(const ::std::string& value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:KFMsg.PBMatchPlayer.name)
}
#if LANG_CXX11
inline void PBMatchPlayer::set_name(::std::string&& value) {
  
  name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:KFMsg.PBMatchPlayer.name)
}
#endif
inline void PBMatchPlayer::set_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:KFMsg.PBMatchPlayer.name)
}
inline void PBMatchPlayer::set_name(const void* value, size_t size) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:KFMsg.PBMatchPlayer.name)
}
inline ::std::string* PBMatchPlayer::mutable_name() {
  
  // @@protoc_insertion_point(field_mutable:KFMsg.PBMatchPlayer.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* PBMatchPlayer::release_name() {
  // @@protoc_insertion_point(field_release:KFMsg.PBMatchPlayer.name)
  
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void PBMatchPlayer::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    
  } else {
    
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:KFMsg.PBMatchPlayer.name)
}

// uint64 serverid = 3;
inline void PBMatchPlayer::clear_serverid() {
  serverid_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 PBMatchPlayer::serverid() const {
  // @@protoc_insertion_point(field_get:KFMsg.PBMatchPlayer.serverid)
  return serverid_;
}
inline void PBMatchPlayer::set_serverid(::google::protobuf::uint64 value) {
  
  serverid_ = value;
  // @@protoc_insertion_point(field_set:KFMsg.PBMatchPlayer.serverid)
}

// bool isrobot = 4;
inline void PBMatchPlayer::clear_isrobot() {
  isrobot_ = false;
}
inline bool PBMatchPlayer::isrobot() const {
  // @@protoc_insertion_point(field_get:KFMsg.PBMatchPlayer.isrobot)
  return isrobot_;
}
inline void PBMatchPlayer::set_isrobot(bool value) {
  
  isrobot_ = value;
  // @@protoc_insertion_point(field_set:KFMsg.PBMatchPlayer.isrobot)
}

// uint32 heroid = 5;
inline void PBMatchPlayer::clear_heroid() {
  heroid_ = 0u;
}
inline ::google::protobuf::uint32 PBMatchPlayer::heroid() const {
  // @@protoc_insertion_point(field_get:KFMsg.PBMatchPlayer.heroid)
  return heroid_;
}
inline void PBMatchPlayer::set_heroid(::google::protobuf::uint32 value) {
  
  heroid_ = value;
  // @@protoc_insertion_point(field_set:KFMsg.PBMatchPlayer.heroid)
}

// uint32 grade = 6;
inline void PBMatchPlayer::clear_grade() {
  grade_ = 0u;
}
inline ::google::protobuf::uint32 PBMatchPlayer::grade() const {
  // @@protoc_insertion_point(field_get:KFMsg.PBMatchPlayer.grade)
  return grade_;
}
inline void PBMatchPlayer::set_grade(::google::protobuf::uint32 value) {
  
  grade_ = value;
  // @@protoc_insertion_point(field_set:KFMsg.PBMatchPlayer.grade)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace KFMsg

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_DefineMessage_2eproto
