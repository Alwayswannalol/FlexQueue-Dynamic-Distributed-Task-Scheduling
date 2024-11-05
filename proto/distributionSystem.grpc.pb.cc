// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: distributionSystem.proto

#include "distributionSystem.pb.h"
#include "distributionSystem.grpc.pb.h"

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>
namespace DistributionSystem {

static const char* TaskExecutionService_method_names[] = {
  "/DistributionSystem.TaskExecutionService/ExecuteDetectionTask",
};

std::unique_ptr< TaskExecutionService::Stub> TaskExecutionService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< TaskExecutionService::Stub> stub(new TaskExecutionService::Stub(channel, options));
  return stub;
}

TaskExecutionService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_ExecuteDetectionTask_(TaskExecutionService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::BIDI_STREAMING, channel)
  {}

::grpc::ClientReaderWriter< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>* TaskExecutionService::Stub::ExecuteDetectionTaskRaw(::grpc::ClientContext* context) {
  return ::grpc::internal::ClientReaderWriterFactory< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>::Create(channel_.get(), rpcmethod_ExecuteDetectionTask_, context);
}

void TaskExecutionService::Stub::async::ExecuteDetectionTask(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::DistributionSystem::ImageRequest,::DistributionSystem::ImageResponse>* reactor) {
  ::grpc::internal::ClientCallbackReaderWriterFactory< ::DistributionSystem::ImageRequest,::DistributionSystem::ImageResponse>::Create(stub_->channel_.get(), stub_->rpcmethod_ExecuteDetectionTask_, context, reactor);
}

::grpc::ClientAsyncReaderWriter< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>* TaskExecutionService::Stub::AsyncExecuteDetectionTaskRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>::Create(channel_.get(), cq, rpcmethod_ExecuteDetectionTask_, context, true, tag);
}

::grpc::ClientAsyncReaderWriter< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>* TaskExecutionService::Stub::PrepareAsyncExecuteDetectionTaskRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>::Create(channel_.get(), cq, rpcmethod_ExecuteDetectionTask_, context, false, nullptr);
}

TaskExecutionService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      TaskExecutionService_method_names[0],
      ::grpc::internal::RpcMethod::BIDI_STREAMING,
      new ::grpc::internal::BidiStreamingHandler< TaskExecutionService::Service, ::DistributionSystem::ImageRequest, ::DistributionSystem::ImageResponse>(
          [](TaskExecutionService::Service* service,
             ::grpc::ServerContext* ctx,
             ::grpc::ServerReaderWriter<::DistributionSystem::ImageResponse,
             ::DistributionSystem::ImageRequest>* stream) {
               return service->ExecuteDetectionTask(ctx, stream);
             }, this)));
}

TaskExecutionService::Service::~Service() {
}

::grpc::Status TaskExecutionService::Service::ExecuteDetectionTask(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::DistributionSystem::ImageResponse, ::DistributionSystem::ImageRequest>* stream) {
  (void) context;
  (void) stream;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


static const char* DistributionTasksService_method_names[] = {
  "/DistributionSystem.DistributionTasksService/CollectData",
};

std::unique_ptr< DistributionTasksService::Stub> DistributionTasksService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< DistributionTasksService::Stub> stub(new DistributionTasksService::Stub(channel, options));
  return stub;
}

DistributionTasksService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_CollectData_(DistributionTasksService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status DistributionTasksService::Stub::CollectData(::grpc::ClientContext* context, const ::DistributionSystem::CollectDataRequest& request, ::DistributionSystem::CollectedData* response) {
  return ::grpc::internal::BlockingUnaryCall< ::DistributionSystem::CollectDataRequest, ::DistributionSystem::CollectedData, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_CollectData_, context, request, response);
}

void DistributionTasksService::Stub::async::CollectData(::grpc::ClientContext* context, const ::DistributionSystem::CollectDataRequest* request, ::DistributionSystem::CollectedData* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::DistributionSystem::CollectDataRequest, ::DistributionSystem::CollectedData, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CollectData_, context, request, response, std::move(f));
}

void DistributionTasksService::Stub::async::CollectData(::grpc::ClientContext* context, const ::DistributionSystem::CollectDataRequest* request, ::DistributionSystem::CollectedData* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CollectData_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::DistributionSystem::CollectedData>* DistributionTasksService::Stub::PrepareAsyncCollectDataRaw(::grpc::ClientContext* context, const ::DistributionSystem::CollectDataRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::DistributionSystem::CollectedData, ::DistributionSystem::CollectDataRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_CollectData_, context, request);
}

::grpc::ClientAsyncResponseReader< ::DistributionSystem::CollectedData>* DistributionTasksService::Stub::AsyncCollectDataRaw(::grpc::ClientContext* context, const ::DistributionSystem::CollectDataRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncCollectDataRaw(context, request, cq);
  result->StartCall();
  return result;
}

DistributionTasksService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DistributionTasksService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DistributionTasksService::Service, ::DistributionSystem::CollectDataRequest, ::DistributionSystem::CollectedData, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](DistributionTasksService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::DistributionSystem::CollectDataRequest* req,
             ::DistributionSystem::CollectedData* resp) {
               return service->CollectData(ctx, req, resp);
             }, this)));
}

DistributionTasksService::Service::~Service() {
}

::grpc::Status DistributionTasksService::Service::CollectData(::grpc::ServerContext* context, const ::DistributionSystem::CollectDataRequest* request, ::DistributionSystem::CollectedData* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


static const char* FaultToleranceService_method_names[] = {
  "/DistributionSystem.FaultToleranceService/Ping",
};

std::unique_ptr< FaultToleranceService::Stub> FaultToleranceService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< FaultToleranceService::Stub> stub(new FaultToleranceService::Stub(channel, options));
  return stub;
}

FaultToleranceService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_Ping_(FaultToleranceService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status FaultToleranceService::Stub::Ping(::grpc::ClientContext* context, const ::DistributionSystem::PingRequest& request, ::DistributionSystem::PingResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::DistributionSystem::PingRequest, ::DistributionSystem::PingResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_Ping_, context, request, response);
}

void FaultToleranceService::Stub::async::Ping(::grpc::ClientContext* context, const ::DistributionSystem::PingRequest* request, ::DistributionSystem::PingResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::DistributionSystem::PingRequest, ::DistributionSystem::PingResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Ping_, context, request, response, std::move(f));
}

void FaultToleranceService::Stub::async::Ping(::grpc::ClientContext* context, const ::DistributionSystem::PingRequest* request, ::DistributionSystem::PingResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Ping_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::DistributionSystem::PingResponse>* FaultToleranceService::Stub::PrepareAsyncPingRaw(::grpc::ClientContext* context, const ::DistributionSystem::PingRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::DistributionSystem::PingResponse, ::DistributionSystem::PingRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_Ping_, context, request);
}

::grpc::ClientAsyncResponseReader< ::DistributionSystem::PingResponse>* FaultToleranceService::Stub::AsyncPingRaw(::grpc::ClientContext* context, const ::DistributionSystem::PingRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncPingRaw(context, request, cq);
  result->StartCall();
  return result;
}

FaultToleranceService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      FaultToleranceService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< FaultToleranceService::Service, ::DistributionSystem::PingRequest, ::DistributionSystem::PingResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](FaultToleranceService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::DistributionSystem::PingRequest* req,
             ::DistributionSystem::PingResponse* resp) {
               return service->Ping(ctx, req, resp);
             }, this)));
}

FaultToleranceService::Service::~Service() {
}

::grpc::Status FaultToleranceService::Service::Ping(::grpc::ServerContext* context, const ::DistributionSystem::PingRequest* request, ::DistributionSystem::PingResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace DistributionSystem

