// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: distributionSystemService.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_distributionSystemService_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_distributionSystemService_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021012 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_distributionSystemService_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_distributionSystemService_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_distributionSystemService_2eproto;
namespace distributionSystemService {
class CollectedData;
struct CollectedDataDefaultTypeInternal;
extern CollectedDataDefaultTypeInternal _CollectedData_default_instance_;
class Empty;
struct EmptyDefaultTypeInternal;
extern EmptyDefaultTypeInternal _Empty_default_instance_;
class PingResponse;
struct PingResponseDefaultTypeInternal;
extern PingResponseDefaultTypeInternal _PingResponse_default_instance_;
}  // namespace distributionSystemService
PROTOBUF_NAMESPACE_OPEN
template<> ::distributionSystemService::CollectedData* Arena::CreateMaybeMessage<::distributionSystemService::CollectedData>(Arena*);
template<> ::distributionSystemService::Empty* Arena::CreateMaybeMessage<::distributionSystemService::Empty>(Arena*);
template<> ::distributionSystemService::PingResponse* Arena::CreateMaybeMessage<::distributionSystemService::PingResponse>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace distributionSystemService {

// ===================================================================

class Empty final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:distributionSystemService.Empty) */ {
 public:
  inline Empty() : Empty(nullptr) {}
  ~Empty() override;
  explicit PROTOBUF_CONSTEXPR Empty(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Empty(const Empty& from);
  Empty(Empty&& from) noexcept
    : Empty() {
    *this = ::std::move(from);
  }

  inline Empty& operator=(const Empty& from) {
    CopyFrom(from);
    return *this;
  }
  inline Empty& operator=(Empty&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Empty& default_instance() {
    return *internal_default_instance();
  }
  static inline const Empty* internal_default_instance() {
    return reinterpret_cast<const Empty*>(
               &_Empty_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Empty& a, Empty& b) {
    a.Swap(&b);
  }
  inline void Swap(Empty* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Empty* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Empty* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Empty>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Empty& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const Empty& from) {
    Empty::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Empty* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "distributionSystemService.Empty";
  }
  protected:
  explicit Empty(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kNumFieldNumber = 1,
  };
  // string num = 1;
  void clear_num();
  const std::string& num() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_num(ArgT0&& arg0, ArgT... args);
  std::string* mutable_num();
  PROTOBUF_NODISCARD std::string* release_num();
  void set_allocated_num(std::string* num);
  private:
  const std::string& _internal_num() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_num(const std::string& value);
  std::string* _internal_mutable_num();
  public:

  // @@protoc_insertion_point(class_scope:distributionSystemService.Empty)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr num_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_distributionSystemService_2eproto;
};
// -------------------------------------------------------------------

class PingResponse final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:distributionSystemService.PingResponse) */ {
 public:
  inline PingResponse() : PingResponse(nullptr) {}
  ~PingResponse() override;
  explicit PROTOBUF_CONSTEXPR PingResponse(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  PingResponse(const PingResponse& from);
  PingResponse(PingResponse&& from) noexcept
    : PingResponse() {
    *this = ::std::move(from);
  }

  inline PingResponse& operator=(const PingResponse& from) {
    CopyFrom(from);
    return *this;
  }
  inline PingResponse& operator=(PingResponse&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const PingResponse& default_instance() {
    return *internal_default_instance();
  }
  static inline const PingResponse* internal_default_instance() {
    return reinterpret_cast<const PingResponse*>(
               &_PingResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(PingResponse& a, PingResponse& b) {
    a.Swap(&b);
  }
  inline void Swap(PingResponse* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(PingResponse* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  PingResponse* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<PingResponse>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const PingResponse& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const PingResponse& from) {
    PingResponse::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(PingResponse* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "distributionSystemService.PingResponse";
  }
  protected:
  explicit PingResponse(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kServerAddressFieldNumber = 1,
    kIsAliveFieldNumber = 2,
  };
  // string server_address = 1;
  void clear_server_address();
  const std::string& server_address() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_server_address(ArgT0&& arg0, ArgT... args);
  std::string* mutable_server_address();
  PROTOBUF_NODISCARD std::string* release_server_address();
  void set_allocated_server_address(std::string* server_address);
  private:
  const std::string& _internal_server_address() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_server_address(const std::string& value);
  std::string* _internal_mutable_server_address();
  public:

  // bool is_alive = 2;
  void clear_is_alive();
  bool is_alive() const;
  void set_is_alive(bool value);
  private:
  bool _internal_is_alive() const;
  void _internal_set_is_alive(bool value);
  public:

  // @@protoc_insertion_point(class_scope:distributionSystemService.PingResponse)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr server_address_;
    bool is_alive_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_distributionSystemService_2eproto;
};
// -------------------------------------------------------------------

class CollectedData final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:distributionSystemService.CollectedData) */ {
 public:
  inline CollectedData() : CollectedData(nullptr) {}
  ~CollectedData() override;
  explicit PROTOBUF_CONSTEXPR CollectedData(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  CollectedData(const CollectedData& from);
  CollectedData(CollectedData&& from) noexcept
    : CollectedData() {
    *this = ::std::move(from);
  }

  inline CollectedData& operator=(const CollectedData& from) {
    CopyFrom(from);
    return *this;
  }
  inline CollectedData& operator=(CollectedData&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const CollectedData& default_instance() {
    return *internal_default_instance();
  }
  static inline const CollectedData* internal_default_instance() {
    return reinterpret_cast<const CollectedData*>(
               &_CollectedData_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(CollectedData& a, CollectedData& b) {
    a.Swap(&b);
  }
  inline void Swap(CollectedData* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(CollectedData* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  CollectedData* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<CollectedData>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const CollectedData& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const CollectedData& from) {
    CollectedData::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(CollectedData* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "distributionSystemService.CollectedData";
  }
  protected:
  explicit CollectedData(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kSomeoneFieldNumber = 1,
  };
  // string someone = 1;
  void clear_someone();
  const std::string& someone() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_someone(ArgT0&& arg0, ArgT... args);
  std::string* mutable_someone();
  PROTOBUF_NODISCARD std::string* release_someone();
  void set_allocated_someone(std::string* someone);
  private:
  const std::string& _internal_someone() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_someone(const std::string& value);
  std::string* _internal_mutable_someone();
  public:

  // @@protoc_insertion_point(class_scope:distributionSystemService.CollectedData)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr someone_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_distributionSystemService_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Empty

// string num = 1;
inline void Empty::clear_num() {
  _impl_.num_.ClearToEmpty();
}
inline const std::string& Empty::num() const {
  // @@protoc_insertion_point(field_get:distributionSystemService.Empty.num)
  return _internal_num();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void Empty::set_num(ArgT0&& arg0, ArgT... args) {
 
 _impl_.num_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:distributionSystemService.Empty.num)
}
inline std::string* Empty::mutable_num() {
  std::string* _s = _internal_mutable_num();
  // @@protoc_insertion_point(field_mutable:distributionSystemService.Empty.num)
  return _s;
}
inline const std::string& Empty::_internal_num() const {
  return _impl_.num_.Get();
}
inline void Empty::_internal_set_num(const std::string& value) {
  
  _impl_.num_.Set(value, GetArenaForAllocation());
}
inline std::string* Empty::_internal_mutable_num() {
  
  return _impl_.num_.Mutable(GetArenaForAllocation());
}
inline std::string* Empty::release_num() {
  // @@protoc_insertion_point(field_release:distributionSystemService.Empty.num)
  return _impl_.num_.Release();
}
inline void Empty::set_allocated_num(std::string* num) {
  if (num != nullptr) {
    
  } else {
    
  }
  _impl_.num_.SetAllocated(num, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.num_.IsDefault()) {
    _impl_.num_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:distributionSystemService.Empty.num)
}

// -------------------------------------------------------------------

// PingResponse

// string server_address = 1;
inline void PingResponse::clear_server_address() {
  _impl_.server_address_.ClearToEmpty();
}
inline const std::string& PingResponse::server_address() const {
  // @@protoc_insertion_point(field_get:distributionSystemService.PingResponse.server_address)
  return _internal_server_address();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void PingResponse::set_server_address(ArgT0&& arg0, ArgT... args) {
 
 _impl_.server_address_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:distributionSystemService.PingResponse.server_address)
}
inline std::string* PingResponse::mutable_server_address() {
  std::string* _s = _internal_mutable_server_address();
  // @@protoc_insertion_point(field_mutable:distributionSystemService.PingResponse.server_address)
  return _s;
}
inline const std::string& PingResponse::_internal_server_address() const {
  return _impl_.server_address_.Get();
}
inline void PingResponse::_internal_set_server_address(const std::string& value) {
  
  _impl_.server_address_.Set(value, GetArenaForAllocation());
}
inline std::string* PingResponse::_internal_mutable_server_address() {
  
  return _impl_.server_address_.Mutable(GetArenaForAllocation());
}
inline std::string* PingResponse::release_server_address() {
  // @@protoc_insertion_point(field_release:distributionSystemService.PingResponse.server_address)
  return _impl_.server_address_.Release();
}
inline void PingResponse::set_allocated_server_address(std::string* server_address) {
  if (server_address != nullptr) {
    
  } else {
    
  }
  _impl_.server_address_.SetAllocated(server_address, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.server_address_.IsDefault()) {
    _impl_.server_address_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:distributionSystemService.PingResponse.server_address)
}

// bool is_alive = 2;
inline void PingResponse::clear_is_alive() {
  _impl_.is_alive_ = false;
}
inline bool PingResponse::_internal_is_alive() const {
  return _impl_.is_alive_;
}
inline bool PingResponse::is_alive() const {
  // @@protoc_insertion_point(field_get:distributionSystemService.PingResponse.is_alive)
  return _internal_is_alive();
}
inline void PingResponse::_internal_set_is_alive(bool value) {
  
  _impl_.is_alive_ = value;
}
inline void PingResponse::set_is_alive(bool value) {
  _internal_set_is_alive(value);
  // @@protoc_insertion_point(field_set:distributionSystemService.PingResponse.is_alive)
}

// -------------------------------------------------------------------

// CollectedData

// string someone = 1;
inline void CollectedData::clear_someone() {
  _impl_.someone_.ClearToEmpty();
}
inline const std::string& CollectedData::someone() const {
  // @@protoc_insertion_point(field_get:distributionSystemService.CollectedData.someone)
  return _internal_someone();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void CollectedData::set_someone(ArgT0&& arg0, ArgT... args) {
 
 _impl_.someone_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:distributionSystemService.CollectedData.someone)
}
inline std::string* CollectedData::mutable_someone() {
  std::string* _s = _internal_mutable_someone();
  // @@protoc_insertion_point(field_mutable:distributionSystemService.CollectedData.someone)
  return _s;
}
inline const std::string& CollectedData::_internal_someone() const {
  return _impl_.someone_.Get();
}
inline void CollectedData::_internal_set_someone(const std::string& value) {
  
  _impl_.someone_.Set(value, GetArenaForAllocation());
}
inline std::string* CollectedData::_internal_mutable_someone() {
  
  return _impl_.someone_.Mutable(GetArenaForAllocation());
}
inline std::string* CollectedData::release_someone() {
  // @@protoc_insertion_point(field_release:distributionSystemService.CollectedData.someone)
  return _impl_.someone_.Release();
}
inline void CollectedData::set_allocated_someone(std::string* someone) {
  if (someone != nullptr) {
    
  } else {
    
  }
  _impl_.someone_.SetAllocated(someone, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.someone_.IsDefault()) {
    _impl_.someone_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:distributionSystemService.CollectedData.someone)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace distributionSystemService

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_distributionSystemService_2eproto
