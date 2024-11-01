// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: distributionSystem.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_distributionSystem_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_distributionSystem_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_distributionSystem_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_distributionSystem_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_distributionSystem_2eproto;
namespace DistributionSystem {
class CollectDataRequest;
struct CollectDataRequestDefaultTypeInternal;
extern CollectDataRequestDefaultTypeInternal _CollectDataRequest_default_instance_;
class CollectedData;
struct CollectedDataDefaultTypeInternal;
extern CollectedDataDefaultTypeInternal _CollectedData_default_instance_;
class PingRequest;
struct PingRequestDefaultTypeInternal;
extern PingRequestDefaultTypeInternal _PingRequest_default_instance_;
class PingResponse;
struct PingResponseDefaultTypeInternal;
extern PingResponseDefaultTypeInternal _PingResponse_default_instance_;
}  // namespace DistributionSystem
PROTOBUF_NAMESPACE_OPEN
template<> ::DistributionSystem::CollectDataRequest* Arena::CreateMaybeMessage<::DistributionSystem::CollectDataRequest>(Arena*);
template<> ::DistributionSystem::CollectedData* Arena::CreateMaybeMessage<::DistributionSystem::CollectedData>(Arena*);
template<> ::DistributionSystem::PingRequest* Arena::CreateMaybeMessage<::DistributionSystem::PingRequest>(Arena*);
template<> ::DistributionSystem::PingResponse* Arena::CreateMaybeMessage<::DistributionSystem::PingResponse>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace DistributionSystem {

// ===================================================================

class CollectDataRequest final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:DistributionSystem.CollectDataRequest) */ {
 public:
  inline CollectDataRequest() : CollectDataRequest(nullptr) {}
  ~CollectDataRequest() override;
  explicit PROTOBUF_CONSTEXPR CollectDataRequest(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  CollectDataRequest(const CollectDataRequest& from);
  CollectDataRequest(CollectDataRequest&& from) noexcept
    : CollectDataRequest() {
    *this = ::std::move(from);
  }

  inline CollectDataRequest& operator=(const CollectDataRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline CollectDataRequest& operator=(CollectDataRequest&& from) noexcept {
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
  static const CollectDataRequest& default_instance() {
    return *internal_default_instance();
  }
  static inline const CollectDataRequest* internal_default_instance() {
    return reinterpret_cast<const CollectDataRequest*>(
               &_CollectDataRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(CollectDataRequest& a, CollectDataRequest& b) {
    a.Swap(&b);
  }
  inline void Swap(CollectDataRequest* other) {
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
  void UnsafeArenaSwap(CollectDataRequest* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  CollectDataRequest* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<CollectDataRequest>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const CollectDataRequest& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const CollectDataRequest& from) {
    CollectDataRequest::MergeImpl(*this, from);
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
  void InternalSwap(CollectDataRequest* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "DistributionSystem.CollectDataRequest";
  }
  protected:
  explicit CollectDataRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kToServerFieldNumber = 1,
  };
  // string to_server = 1;
  void clear_to_server();
  const std::string& to_server() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_to_server(ArgT0&& arg0, ArgT... args);
  std::string* mutable_to_server();
  PROTOBUF_NODISCARD std::string* release_to_server();
  void set_allocated_to_server(std::string* to_server);
  private:
  const std::string& _internal_to_server() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_to_server(const std::string& value);
  std::string* _internal_mutable_to_server();
  public:

  // @@protoc_insertion_point(class_scope:DistributionSystem.CollectDataRequest)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr to_server_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_distributionSystem_2eproto;
};
// -------------------------------------------------------------------

class CollectedData final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:DistributionSystem.CollectedData) */ {
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
    1;

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
    return "DistributionSystem.CollectedData";
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
    kServerAddressFieldNumber = 1,
    kCollectedInfoFieldNumber = 2,
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

  // string collected_info = 2;
  void clear_collected_info();
  const std::string& collected_info() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_collected_info(ArgT0&& arg0, ArgT... args);
  std::string* mutable_collected_info();
  PROTOBUF_NODISCARD std::string* release_collected_info();
  void set_allocated_collected_info(std::string* collected_info);
  private:
  const std::string& _internal_collected_info() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_collected_info(const std::string& value);
  std::string* _internal_mutable_collected_info();
  public:

  // @@protoc_insertion_point(class_scope:DistributionSystem.CollectedData)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr server_address_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr collected_info_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_distributionSystem_2eproto;
};
// -------------------------------------------------------------------

class PingRequest final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:DistributionSystem.PingRequest) */ {
 public:
  inline PingRequest() : PingRequest(nullptr) {}
  ~PingRequest() override;
  explicit PROTOBUF_CONSTEXPR PingRequest(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  PingRequest(const PingRequest& from);
  PingRequest(PingRequest&& from) noexcept
    : PingRequest() {
    *this = ::std::move(from);
  }

  inline PingRequest& operator=(const PingRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline PingRequest& operator=(PingRequest&& from) noexcept {
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
  static const PingRequest& default_instance() {
    return *internal_default_instance();
  }
  static inline const PingRequest* internal_default_instance() {
    return reinterpret_cast<const PingRequest*>(
               &_PingRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(PingRequest& a, PingRequest& b) {
    a.Swap(&b);
  }
  inline void Swap(PingRequest* other) {
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
  void UnsafeArenaSwap(PingRequest* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  PingRequest* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<PingRequest>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const PingRequest& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const PingRequest& from) {
    PingRequest::MergeImpl(*this, from);
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
  void InternalSwap(PingRequest* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "DistributionSystem.PingRequest";
  }
  protected:
  explicit PingRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kToServerAddressFieldNumber = 1,
  };
  // string to_server_address = 1;
  void clear_to_server_address();
  const std::string& to_server_address() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_to_server_address(ArgT0&& arg0, ArgT... args);
  std::string* mutable_to_server_address();
  PROTOBUF_NODISCARD std::string* release_to_server_address();
  void set_allocated_to_server_address(std::string* to_server_address);
  private:
  const std::string& _internal_to_server_address() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_to_server_address(const std::string& value);
  std::string* _internal_mutable_to_server_address();
  public:

  // @@protoc_insertion_point(class_scope:DistributionSystem.PingRequest)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr to_server_address_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_distributionSystem_2eproto;
};
// -------------------------------------------------------------------

class PingResponse final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:DistributionSystem.PingResponse) */ {
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
    3;

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
    return "DistributionSystem.PingResponse";
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

  // string is_alive = 2;
  void clear_is_alive();
  const std::string& is_alive() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_is_alive(ArgT0&& arg0, ArgT... args);
  std::string* mutable_is_alive();
  PROTOBUF_NODISCARD std::string* release_is_alive();
  void set_allocated_is_alive(std::string* is_alive);
  private:
  const std::string& _internal_is_alive() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_is_alive(const std::string& value);
  std::string* _internal_mutable_is_alive();
  public:

  // @@protoc_insertion_point(class_scope:DistributionSystem.PingResponse)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr server_address_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr is_alive_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_distributionSystem_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// CollectDataRequest

// string to_server = 1;
inline void CollectDataRequest::clear_to_server() {
  _impl_.to_server_.ClearToEmpty();
}
inline const std::string& CollectDataRequest::to_server() const {
  // @@protoc_insertion_point(field_get:DistributionSystem.CollectDataRequest.to_server)
  return _internal_to_server();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void CollectDataRequest::set_to_server(ArgT0&& arg0, ArgT... args) {
 
 _impl_.to_server_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:DistributionSystem.CollectDataRequest.to_server)
}
inline std::string* CollectDataRequest::mutable_to_server() {
  std::string* _s = _internal_mutable_to_server();
  // @@protoc_insertion_point(field_mutable:DistributionSystem.CollectDataRequest.to_server)
  return _s;
}
inline const std::string& CollectDataRequest::_internal_to_server() const {
  return _impl_.to_server_.Get();
}
inline void CollectDataRequest::_internal_set_to_server(const std::string& value) {
  
  _impl_.to_server_.Set(value, GetArenaForAllocation());
}
inline std::string* CollectDataRequest::_internal_mutable_to_server() {
  
  return _impl_.to_server_.Mutable(GetArenaForAllocation());
}
inline std::string* CollectDataRequest::release_to_server() {
  // @@protoc_insertion_point(field_release:DistributionSystem.CollectDataRequest.to_server)
  return _impl_.to_server_.Release();
}
inline void CollectDataRequest::set_allocated_to_server(std::string* to_server) {
  if (to_server != nullptr) {
    
  } else {
    
  }
  _impl_.to_server_.SetAllocated(to_server, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.to_server_.IsDefault()) {
    _impl_.to_server_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:DistributionSystem.CollectDataRequest.to_server)
}

// -------------------------------------------------------------------

// CollectedData

// string server_address = 1;
inline void CollectedData::clear_server_address() {
  _impl_.server_address_.ClearToEmpty();
}
inline const std::string& CollectedData::server_address() const {
  // @@protoc_insertion_point(field_get:DistributionSystem.CollectedData.server_address)
  return _internal_server_address();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void CollectedData::set_server_address(ArgT0&& arg0, ArgT... args) {
 
 _impl_.server_address_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:DistributionSystem.CollectedData.server_address)
}
inline std::string* CollectedData::mutable_server_address() {
  std::string* _s = _internal_mutable_server_address();
  // @@protoc_insertion_point(field_mutable:DistributionSystem.CollectedData.server_address)
  return _s;
}
inline const std::string& CollectedData::_internal_server_address() const {
  return _impl_.server_address_.Get();
}
inline void CollectedData::_internal_set_server_address(const std::string& value) {
  
  _impl_.server_address_.Set(value, GetArenaForAllocation());
}
inline std::string* CollectedData::_internal_mutable_server_address() {
  
  return _impl_.server_address_.Mutable(GetArenaForAllocation());
}
inline std::string* CollectedData::release_server_address() {
  // @@protoc_insertion_point(field_release:DistributionSystem.CollectedData.server_address)
  return _impl_.server_address_.Release();
}
inline void CollectedData::set_allocated_server_address(std::string* server_address) {
  if (server_address != nullptr) {
    
  } else {
    
  }
  _impl_.server_address_.SetAllocated(server_address, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.server_address_.IsDefault()) {
    _impl_.server_address_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:DistributionSystem.CollectedData.server_address)
}

// string collected_info = 2;
inline void CollectedData::clear_collected_info() {
  _impl_.collected_info_.ClearToEmpty();
}
inline const std::string& CollectedData::collected_info() const {
  // @@protoc_insertion_point(field_get:DistributionSystem.CollectedData.collected_info)
  return _internal_collected_info();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void CollectedData::set_collected_info(ArgT0&& arg0, ArgT... args) {
 
 _impl_.collected_info_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:DistributionSystem.CollectedData.collected_info)
}
inline std::string* CollectedData::mutable_collected_info() {
  std::string* _s = _internal_mutable_collected_info();
  // @@protoc_insertion_point(field_mutable:DistributionSystem.CollectedData.collected_info)
  return _s;
}
inline const std::string& CollectedData::_internal_collected_info() const {
  return _impl_.collected_info_.Get();
}
inline void CollectedData::_internal_set_collected_info(const std::string& value) {
  
  _impl_.collected_info_.Set(value, GetArenaForAllocation());
}
inline std::string* CollectedData::_internal_mutable_collected_info() {
  
  return _impl_.collected_info_.Mutable(GetArenaForAllocation());
}
inline std::string* CollectedData::release_collected_info() {
  // @@protoc_insertion_point(field_release:DistributionSystem.CollectedData.collected_info)
  return _impl_.collected_info_.Release();
}
inline void CollectedData::set_allocated_collected_info(std::string* collected_info) {
  if (collected_info != nullptr) {
    
  } else {
    
  }
  _impl_.collected_info_.SetAllocated(collected_info, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.collected_info_.IsDefault()) {
    _impl_.collected_info_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:DistributionSystem.CollectedData.collected_info)
}

// -------------------------------------------------------------------

// PingRequest

// string to_server_address = 1;
inline void PingRequest::clear_to_server_address() {
  _impl_.to_server_address_.ClearToEmpty();
}
inline const std::string& PingRequest::to_server_address() const {
  // @@protoc_insertion_point(field_get:DistributionSystem.PingRequest.to_server_address)
  return _internal_to_server_address();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void PingRequest::set_to_server_address(ArgT0&& arg0, ArgT... args) {
 
 _impl_.to_server_address_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:DistributionSystem.PingRequest.to_server_address)
}
inline std::string* PingRequest::mutable_to_server_address() {
  std::string* _s = _internal_mutable_to_server_address();
  // @@protoc_insertion_point(field_mutable:DistributionSystem.PingRequest.to_server_address)
  return _s;
}
inline const std::string& PingRequest::_internal_to_server_address() const {
  return _impl_.to_server_address_.Get();
}
inline void PingRequest::_internal_set_to_server_address(const std::string& value) {
  
  _impl_.to_server_address_.Set(value, GetArenaForAllocation());
}
inline std::string* PingRequest::_internal_mutable_to_server_address() {
  
  return _impl_.to_server_address_.Mutable(GetArenaForAllocation());
}
inline std::string* PingRequest::release_to_server_address() {
  // @@protoc_insertion_point(field_release:DistributionSystem.PingRequest.to_server_address)
  return _impl_.to_server_address_.Release();
}
inline void PingRequest::set_allocated_to_server_address(std::string* to_server_address) {
  if (to_server_address != nullptr) {
    
  } else {
    
  }
  _impl_.to_server_address_.SetAllocated(to_server_address, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.to_server_address_.IsDefault()) {
    _impl_.to_server_address_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:DistributionSystem.PingRequest.to_server_address)
}

// -------------------------------------------------------------------

// PingResponse

// string server_address = 1;
inline void PingResponse::clear_server_address() {
  _impl_.server_address_.ClearToEmpty();
}
inline const std::string& PingResponse::server_address() const {
  // @@protoc_insertion_point(field_get:DistributionSystem.PingResponse.server_address)
  return _internal_server_address();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void PingResponse::set_server_address(ArgT0&& arg0, ArgT... args) {
 
 _impl_.server_address_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:DistributionSystem.PingResponse.server_address)
}
inline std::string* PingResponse::mutable_server_address() {
  std::string* _s = _internal_mutable_server_address();
  // @@protoc_insertion_point(field_mutable:DistributionSystem.PingResponse.server_address)
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
  // @@protoc_insertion_point(field_release:DistributionSystem.PingResponse.server_address)
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
  // @@protoc_insertion_point(field_set_allocated:DistributionSystem.PingResponse.server_address)
}

// string is_alive = 2;
inline void PingResponse::clear_is_alive() {
  _impl_.is_alive_.ClearToEmpty();
}
inline const std::string& PingResponse::is_alive() const {
  // @@protoc_insertion_point(field_get:DistributionSystem.PingResponse.is_alive)
  return _internal_is_alive();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void PingResponse::set_is_alive(ArgT0&& arg0, ArgT... args) {
 
 _impl_.is_alive_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:DistributionSystem.PingResponse.is_alive)
}
inline std::string* PingResponse::mutable_is_alive() {
  std::string* _s = _internal_mutable_is_alive();
  // @@protoc_insertion_point(field_mutable:DistributionSystem.PingResponse.is_alive)
  return _s;
}
inline const std::string& PingResponse::_internal_is_alive() const {
  return _impl_.is_alive_.Get();
}
inline void PingResponse::_internal_set_is_alive(const std::string& value) {
  
  _impl_.is_alive_.Set(value, GetArenaForAllocation());
}
inline std::string* PingResponse::_internal_mutable_is_alive() {
  
  return _impl_.is_alive_.Mutable(GetArenaForAllocation());
}
inline std::string* PingResponse::release_is_alive() {
  // @@protoc_insertion_point(field_release:DistributionSystem.PingResponse.is_alive)
  return _impl_.is_alive_.Release();
}
inline void PingResponse::set_allocated_is_alive(std::string* is_alive) {
  if (is_alive != nullptr) {
    
  } else {
    
  }
  _impl_.is_alive_.SetAllocated(is_alive, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.is_alive_.IsDefault()) {
    _impl_.is_alive_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:DistributionSystem.PingResponse.is_alive)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace DistributionSystem

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_distributionSystem_2eproto