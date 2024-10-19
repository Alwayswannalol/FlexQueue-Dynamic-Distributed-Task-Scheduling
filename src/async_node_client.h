#ifndef MASTER_NODE_H
#define MASTER_NODE_H

#include <utility>
#include <memory>
#include <iostream>

#include <grpcpp/grpcpp.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;
using grpc::ClientAsyncResponseReader;

#include "../proto/distributionSystemService.grpc.pb.h"

using distributionSystemService::Empty;
using distributionSystemService::DistributionSystemService;
using distributionSystemService::PingResponse;

class AsyncNodeClient 
{
private:
  std::unique_ptr<DistributionSystemService::Stub> stub_;
  Empty request;
  PingResponse response;
  ClientContext context;
  CompletionQueue cq;
  Status status;
public:
  explicit AsyncNodeClient(std::shared_ptr<Channel> channel)
      : stub_(DistributionSystemService::NewStub(channel)) {}

  bool PingNode()
  {
    std::unique_ptr<ClientAsyncResponseReader<PingResponse>> rpc(stub_->AsyncPing(&context, request, &cq));

    rpc->Finish(&response, &status, (void*)1); // 1 для rpc Ping(), сюда можно передавать и другую сущность, например структуру, 
                                               // которая полностью будет описывать состояние запроса
  }

  void ProcessResponses()
  {
    void* got_tag;
    bool ok;
    while (cq.Next(&got_tag, &ok)) 
    {
      // TODO: стоит еще сделать обработку got_tag, чтобы знать какой запрос обработался
      if(ok)
      {
        std::cout << "Server: " << response.is_alive() << std::endl;
      }
      else
      {
        std::cerr << "Server dead" << std::endl;
      }
    }
  }
};

#endif //MASTER_NODE_H