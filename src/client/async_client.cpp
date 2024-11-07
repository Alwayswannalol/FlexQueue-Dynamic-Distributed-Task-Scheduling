#include "async_client.h"

void async_client::detection_task_execution_call::proceed(bool ok) {
    if(call_status_ == PROCESS) {
        if (writing_mode_) {
            if (counter < 2) {
                request_.set_filename(test_str[counter]);
                counter++;
                responder_->Write(request_, (void*)this);
            }
            else {
                responder_->WritesDone((void*)this);
                writing_mode_ = false;
            }
            return;
        }
        else {
            if (!ok) {
                call_status_ = FINISH;
                responder_->Finish(&status, (void*)this);
                return;
            }
            responder_->Read(&response_, (void*)this);
            std::cout << response_.filename() << std::endl;
        }
        return;
    }
    else {
        delete this;
    }
}

void async_client::async_execute_detection_task() {
    auto* call = new detection_task_execution_call(task_execution_stub_, cq_, CALL_TYPE::DETECTION_TASK_EXECUTION_CALL);
}

void async_client::handle_call() {
    void* got_tag;
    bool ok = false;

    while (cq_.Next(&got_tag, &ok)) {
        // Восстанавливаем объект async_call
        auto* call = static_cast<base_call*>(got_tag);
        call->proceed(ok);
    }
}
