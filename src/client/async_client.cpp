#include "async_client.h"

void async_client::detection_task_execution_call::get_response(bool ok) {
    if (!ok) {
        responder_->Finish(&status, reinterpret_cast<void*>(this));
        delete this;
        return;
    }
    responder_->Read(&image_response, reinterpret_cast<void*>(this));
    std::cout << image_response.filename() << std::endl;
}

void async_client::async_execute_detection_task() {
    auto* call = new detection_task_execution_call(CALL_TYPE::DETECTION_TASK_EXECUTION_CALL);

    call->responder_ = task_execution_stub_->AsyncExecuteDetectionTask(&call->context, &cq_, reinterpret_cast<void*>(call));

    call->image_request.set_filename("First Hello");

    call->responder_->Write(call->image_request, reinterpret_cast<void*>(call));

    call->image_request.set_filename("Second Hello");

    call->responder_->Write(call->image_request, reinterpret_cast<void*>(call));

    call->responder_->WritesDone(reinterpret_cast<void*>(call));
}

void async_client::process_responses() {
    void* got_tag;
    bool ok = false;

    while (cq_.Next(&got_tag, &ok)) {
        // Восстанавливаем объект async_call
        auto* call = static_cast<base_call*>(got_tag);

        call->get_response(ok);

        // delete call;
    }
}
