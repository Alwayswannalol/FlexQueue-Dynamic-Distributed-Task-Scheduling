// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: distributionSystem.proto
#ifndef GRPC_distributionSystem_2eproto__INCLUDED
#define GRPC_distributionSystem_2eproto__INCLUDED

#include "distributionSystem.pb.h"

#include <functional>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/proto_utils.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/stub_options.h>
#include <grpcpp/support/sync_stream.h>

namespace DistributionSystem {

// Сервис выполнения задач
class TaskExecutionService final {
 public:
  static constexpr char const* service_full_name() {
    return "DistributionSystem.TaskExecutionService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    std::unique_ptr< ::grpc::ClientReaderWriterInterface< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>> ExecuteDetectionTask(::grpc::ClientContext* context) {
      return std::unique_ptr< ::grpc::ClientReaderWriterInterface< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>>(ExecuteDetectionTaskRaw(context));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>> AsyncExecuteDetectionTask(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>>(AsyncExecuteDetectionTaskRaw(context, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>> PrepareAsyncExecuteDetectionTask(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>>(PrepareAsyncExecuteDetectionTaskRaw(context, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void ExecuteDetectionTask(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::DistributionSystem::ImageRequest,::DistributionSystem::ImageResponse>* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientReaderWriterInterface< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>* ExecuteDetectionTaskRaw(::grpc::ClientContext* context) = 0;
    virtual ::grpc::ClientAsyncReaderWriterInterface< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>* AsyncExecuteDetectionTaskRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) = 0;
    virtual ::grpc::ClientAsyncReaderWriterInterface< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>* PrepareAsyncExecuteDetectionTaskRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    std::unique_ptr< ::grpc::ClientReaderWriter< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>> ExecuteDetectionTask(::grpc::ClientContext* context) {
      return std::unique_ptr< ::grpc::ClientReaderWriter< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>>(ExecuteDetectionTaskRaw(context));
    }
    std::unique_ptr<  ::grpc::ClientAsyncReaderWriter< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>> AsyncExecuteDetectionTask(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriter< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>>(AsyncExecuteDetectionTaskRaw(context, cq, tag));
    }
    std::unique_ptr<  ::grpc::ClientAsyncReaderWriter< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>> PrepareAsyncExecuteDetectionTask(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriter< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>>(PrepareAsyncExecuteDetectionTaskRaw(context, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void ExecuteDetectionTask(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::DistributionSystem::ImageRequest,::DistributionSystem::ImageResponse>* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientReaderWriter< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>* ExecuteDetectionTaskRaw(::grpc::ClientContext* context) override;
    ::grpc::ClientAsyncReaderWriter< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>* AsyncExecuteDetectionTaskRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) override;
    ::grpc::ClientAsyncReaderWriter< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>* PrepareAsyncExecuteDetectionTaskRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_ExecuteDetectionTask_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status ExecuteDetectionTask(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::DistributionSystem::ImageResponse, ::DistributionSystem::ImageRequest>* stream);
  };
  template <class BaseClass>
  class WithAsyncMethod_ExecuteDetectionTask : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_ExecuteDetectionTask() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_ExecuteDetectionTask() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ExecuteDetectionTask(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::DistributionSystem::ImageResponse, ::DistributionSystem::ImageRequest>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestExecuteDetectionTask(::grpc::ServerContext* context, ::grpc::ServerAsyncReaderWriter< ::DistributionSystem::ImageResponse, ::DistributionSystem::ImageRequest>* stream, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncBidiStreaming(0, context, stream, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_ExecuteDetectionTask<Service > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_ExecuteDetectionTask : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_ExecuteDetectionTask() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackBidiHandler< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>(
            [this](
                   ::grpc::CallbackServerContext* context) { return this->ExecuteDetectionTask(context); }));
    }
    ~WithCallbackMethod_ExecuteDetectionTask() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ExecuteDetectionTask(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::DistributionSystem::ImageResponse, ::DistributionSystem::ImageRequest>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerBidiReactor< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>* ExecuteDetectionTask(
      ::grpc::CallbackServerContext* /*context*/)
      { return nullptr; }
  };
  typedef WithCallbackMethod_ExecuteDetectionTask<Service > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_ExecuteDetectionTask : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_ExecuteDetectionTask() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_ExecuteDetectionTask() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ExecuteDetectionTask(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::DistributionSystem::ImageResponse, ::DistributionSystem::ImageRequest>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_ExecuteDetectionTask : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_ExecuteDetectionTask() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_ExecuteDetectionTask() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ExecuteDetectionTask(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::DistributionSystem::ImageResponse, ::DistributionSystem::ImageRequest>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestExecuteDetectionTask(::grpc::ServerContext* context, ::grpc::ServerAsyncReaderWriter< ::grpc::ByteBuffer, ::grpc::ByteBuffer>* stream, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncBidiStreaming(0, context, stream, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_ExecuteDetectionTask : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_ExecuteDetectionTask() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackBidiHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context) { return this->ExecuteDetectionTask(context); }));
    }
    ~WithRawCallbackMethod_ExecuteDetectionTask() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ExecuteDetectionTask(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::DistributionSystem::ImageResponse, ::DistributionSystem::ImageRequest>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerBidiReactor< ::grpc::ByteBuffer, ::grpc::ByteBuffer>* ExecuteDetectionTask(
      ::grpc::CallbackServerContext* /*context*/)
      { return nullptr; }
  };
  typedef Service StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef Service StreamedService;
};

// Сервис для распределения тасок по узлам системы
class DistributionTasksService final {
 public:
  static constexpr char const* service_full_name() {
    return "DistributionSystem.DistributionTasksService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status CollectData(::grpc::ClientContext* context, const ::DistributionSystem::CollectDataRequest& request, ::DistributionSystem::CollectedData* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::DistributionSystem::CollectedData>> AsyncCollectData(::grpc::ClientContext* context, const ::DistributionSystem::CollectDataRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::DistributionSystem::CollectedData>>(AsyncCollectDataRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::DistributionSystem::CollectedData>> PrepareAsyncCollectData(::grpc::ClientContext* context, const ::DistributionSystem::CollectDataRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::DistributionSystem::CollectedData>>(PrepareAsyncCollectDataRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void CollectData(::grpc::ClientContext* context, const ::DistributionSystem::CollectDataRequest* request, ::DistributionSystem::CollectedData* response, std::function<void(::grpc::Status)>) = 0;
      virtual void CollectData(::grpc::ClientContext* context, const ::DistributionSystem::CollectDataRequest* request, ::DistributionSystem::CollectedData* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::DistributionSystem::CollectedData>* AsyncCollectDataRaw(::grpc::ClientContext* context, const ::DistributionSystem::CollectDataRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::DistributionSystem::CollectedData>* PrepareAsyncCollectDataRaw(::grpc::ClientContext* context, const ::DistributionSystem::CollectDataRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status CollectData(::grpc::ClientContext* context, const ::DistributionSystem::CollectDataRequest& request, ::DistributionSystem::CollectedData* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::DistributionSystem::CollectedData>> AsyncCollectData(::grpc::ClientContext* context, const ::DistributionSystem::CollectDataRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::DistributionSystem::CollectedData>>(AsyncCollectDataRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::DistributionSystem::CollectedData>> PrepareAsyncCollectData(::grpc::ClientContext* context, const ::DistributionSystem::CollectDataRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::DistributionSystem::CollectedData>>(PrepareAsyncCollectDataRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void CollectData(::grpc::ClientContext* context, const ::DistributionSystem::CollectDataRequest* request, ::DistributionSystem::CollectedData* response, std::function<void(::grpc::Status)>) override;
      void CollectData(::grpc::ClientContext* context, const ::DistributionSystem::CollectDataRequest* request, ::DistributionSystem::CollectedData* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::DistributionSystem::CollectedData>* AsyncCollectDataRaw(::grpc::ClientContext* context, const ::DistributionSystem::CollectDataRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::DistributionSystem::CollectedData>* PrepareAsyncCollectDataRaw(::grpc::ClientContext* context, const ::DistributionSystem::CollectDataRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_CollectData_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status CollectData(::grpc::ServerContext* context, const ::DistributionSystem::CollectDataRequest* request, ::DistributionSystem::CollectedData* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_CollectData : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_CollectData() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_CollectData() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status CollectData(::grpc::ServerContext* /*context*/, const ::DistributionSystem::CollectDataRequest* /*request*/, ::DistributionSystem::CollectedData* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestCollectData(::grpc::ServerContext* context, ::DistributionSystem::CollectDataRequest* request, ::grpc::ServerAsyncResponseWriter< ::DistributionSystem::CollectedData>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_CollectData<Service > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_CollectData : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_CollectData() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::DistributionSystem::CollectDataRequest, ::DistributionSystem::CollectedData>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::DistributionSystem::CollectDataRequest* request, ::DistributionSystem::CollectedData* response) { return this->CollectData(context, request, response); }));}
    void SetMessageAllocatorFor_CollectData(
        ::grpc::MessageAllocator< ::DistributionSystem::CollectDataRequest, ::DistributionSystem::CollectedData>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::DistributionSystem::CollectDataRequest, ::DistributionSystem::CollectedData>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_CollectData() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status CollectData(::grpc::ServerContext* /*context*/, const ::DistributionSystem::CollectDataRequest* /*request*/, ::DistributionSystem::CollectedData* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* CollectData(
      ::grpc::CallbackServerContext* /*context*/, const ::DistributionSystem::CollectDataRequest* /*request*/, ::DistributionSystem::CollectedData* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_CollectData<Service > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_CollectData : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_CollectData() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_CollectData() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status CollectData(::grpc::ServerContext* /*context*/, const ::DistributionSystem::CollectDataRequest* /*request*/, ::DistributionSystem::CollectedData* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_CollectData : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_CollectData() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_CollectData() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status CollectData(::grpc::ServerContext* /*context*/, const ::DistributionSystem::CollectDataRequest* /*request*/, ::DistributionSystem::CollectedData* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestCollectData(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_CollectData : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_CollectData() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->CollectData(context, request, response); }));
    }
    ~WithRawCallbackMethod_CollectData() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status CollectData(::grpc::ServerContext* /*context*/, const ::DistributionSystem::CollectDataRequest* /*request*/, ::DistributionSystem::CollectedData* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* CollectData(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_CollectData : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_CollectData() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::DistributionSystem::CollectDataRequest, ::DistributionSystem::CollectedData>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::DistributionSystem::CollectDataRequest, ::DistributionSystem::CollectedData>* streamer) {
                       return this->StreamedCollectData(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_CollectData() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status CollectData(::grpc::ServerContext* /*context*/, const ::DistributionSystem::CollectDataRequest* /*request*/, ::DistributionSystem::CollectedData* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedCollectData(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::DistributionSystem::CollectDataRequest,::DistributionSystem::CollectedData>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_CollectData<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_CollectData<Service > StreamedService;
};

// Сервис для достижения отказоустойчивости в системе
class FaultToleranceService final {
 public:
  static constexpr char const* service_full_name() {
    return "DistributionSystem.FaultToleranceService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status Ping(::grpc::ClientContext* context, const ::DistributionSystem::PingRequest& request, ::DistributionSystem::PingResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::DistributionSystem::PingResponse>> AsyncPing(::grpc::ClientContext* context, const ::DistributionSystem::PingRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::DistributionSystem::PingResponse>>(AsyncPingRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::DistributionSystem::PingResponse>> PrepareAsyncPing(::grpc::ClientContext* context, const ::DistributionSystem::PingRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::DistributionSystem::PingResponse>>(PrepareAsyncPingRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void Ping(::grpc::ClientContext* context, const ::DistributionSystem::PingRequest* request, ::DistributionSystem::PingResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void Ping(::grpc::ClientContext* context, const ::DistributionSystem::PingRequest* request, ::DistributionSystem::PingResponse* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::DistributionSystem::PingResponse>* AsyncPingRaw(::grpc::ClientContext* context, const ::DistributionSystem::PingRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::DistributionSystem::PingResponse>* PrepareAsyncPingRaw(::grpc::ClientContext* context, const ::DistributionSystem::PingRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status Ping(::grpc::ClientContext* context, const ::DistributionSystem::PingRequest& request, ::DistributionSystem::PingResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::DistributionSystem::PingResponse>> AsyncPing(::grpc::ClientContext* context, const ::DistributionSystem::PingRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::DistributionSystem::PingResponse>>(AsyncPingRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::DistributionSystem::PingResponse>> PrepareAsyncPing(::grpc::ClientContext* context, const ::DistributionSystem::PingRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::DistributionSystem::PingResponse>>(PrepareAsyncPingRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void Ping(::grpc::ClientContext* context, const ::DistributionSystem::PingRequest* request, ::DistributionSystem::PingResponse* response, std::function<void(::grpc::Status)>) override;
      void Ping(::grpc::ClientContext* context, const ::DistributionSystem::PingRequest* request, ::DistributionSystem::PingResponse* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::DistributionSystem::PingResponse>* AsyncPingRaw(::grpc::ClientContext* context, const ::DistributionSystem::PingRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::DistributionSystem::PingResponse>* PrepareAsyncPingRaw(::grpc::ClientContext* context, const ::DistributionSystem::PingRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_Ping_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status Ping(::grpc::ServerContext* context, const ::DistributionSystem::PingRequest* request, ::DistributionSystem::PingResponse* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_Ping : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_Ping() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_Ping() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Ping(::grpc::ServerContext* /*context*/, const ::DistributionSystem::PingRequest* /*request*/, ::DistributionSystem::PingResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestPing(::grpc::ServerContext* context, ::DistributionSystem::PingRequest* request, ::grpc::ServerAsyncResponseWriter< ::DistributionSystem::PingResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_Ping<Service > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_Ping : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_Ping() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::DistributionSystem::PingRequest, ::DistributionSystem::PingResponse>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::DistributionSystem::PingRequest* request, ::DistributionSystem::PingResponse* response) { return this->Ping(context, request, response); }));}
    void SetMessageAllocatorFor_Ping(
        ::grpc::MessageAllocator< ::DistributionSystem::PingRequest, ::DistributionSystem::PingResponse>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::DistributionSystem::PingRequest, ::DistributionSystem::PingResponse>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_Ping() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Ping(::grpc::ServerContext* /*context*/, const ::DistributionSystem::PingRequest* /*request*/, ::DistributionSystem::PingResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* Ping(
      ::grpc::CallbackServerContext* /*context*/, const ::DistributionSystem::PingRequest* /*request*/, ::DistributionSystem::PingResponse* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_Ping<Service > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_Ping : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_Ping() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_Ping() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Ping(::grpc::ServerContext* /*context*/, const ::DistributionSystem::PingRequest* /*request*/, ::DistributionSystem::PingResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_Ping : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_Ping() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_Ping() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Ping(::grpc::ServerContext* /*context*/, const ::DistributionSystem::PingRequest* /*request*/, ::DistributionSystem::PingResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestPing(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_Ping : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_Ping() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->Ping(context, request, response); }));
    }
    ~WithRawCallbackMethod_Ping() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Ping(::grpc::ServerContext* /*context*/, const ::DistributionSystem::PingRequest* /*request*/, ::DistributionSystem::PingResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* Ping(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_Ping : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_Ping() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::DistributionSystem::PingRequest, ::DistributionSystem::PingResponse>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::DistributionSystem::PingRequest, ::DistributionSystem::PingResponse>* streamer) {
                       return this->StreamedPing(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_Ping() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status Ping(::grpc::ServerContext* /*context*/, const ::DistributionSystem::PingRequest* /*request*/, ::DistributionSystem::PingResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedPing(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::DistributionSystem::PingRequest,::DistributionSystem::PingResponse>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_Ping<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_Ping<Service > StreamedService;
};

}  // namespace DistributionSystem


#endif  // GRPC_distributionSystem_2eproto__INCLUDED
