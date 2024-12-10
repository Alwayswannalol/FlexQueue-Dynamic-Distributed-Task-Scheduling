#include "async_client.h"

void async_client::detection_task_execution_call::proceed(bool ok) {
    if(call_status_ == PROCESS_CALL) {
        if (writing_mode_) {
            char data_for_server[CHUNK_SIZE];
            if (counter_ < filePaths_.size()) {
                std::string filepath_ = filePaths_[counter_];
                if (filepath_ != prev_filepath_) {
                    size = files_info::get_size(filepath_);
                    num_of_chunk = 1;
                    if (!reading_stream.is_open()) {
                        reading_stream.open(filepath_);
                    }
                    else {
                        reading_stream.close();
                        reading_stream.open(filepath_);
                    }
                    prev_filepath_ = filepath_;
                }
                if (num_of_chunk * CHUNK_SIZE <= size) {
                    reading_stream.read(data_for_server, sizeof(data_for_server));

                    request_.set_client_name(client_name_);
                    request_.set_filename(filepath_);
                    request_.set_data(data_for_server, reading_stream.gcount());
                    request_.set_last_packet(false);

                    num_of_chunk++;
                }
                else {
                    reading_stream.read(data_for_server, sizeof(data_for_server));

                    request_.set_client_name(client_name_);
                    request_.set_filename(filepath_);
                    request_.set_data(data_for_server, reading_stream.gcount());
                    request_.set_last_packet(false);

                    reading_stream.close();

                    counter_++;
                    if (counter_ == filePaths_.size()) {
                        request_.set_last_packet(true);
                    }
                }
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
                call_status_ = FINISH_CALL;
                responder_->Finish(&status, (void*)this);
                return;
            }

            responder_->Read(&response_, (void*)this);

            std::string filename_ = response_.filename();
            if (filename_ != prev_filename_) {
                if (!writing_stream.is_open()) {
                    writing_stream.open("tmp/results/" + filename_, std::ios::app);
                }
                else {
                    writing_stream.close();
                    writing_stream.open("tmp/results/" + filename_, std::ios::app);
                }
                prev_filename_ = filename_;
            }

            writing_stream.write(response_.data().c_str(), response_.data().length());
        }
        return;
    }
    else {
        if (writing_stream.is_open()) {
            writing_stream.close();
        }

        if (reading_stream.is_open()) {
            reading_stream.close();
        }

        delete this;
    }
}

void async_client::async_execute_detection_task(std::vector<std::string> filePaths) {
    auto* call = new detection_task_execution_call(task_execution_stub_, cq_, CALL_TYPE::DETECTION_TASK_EXECUTION_CALL, filePaths, client_name_);
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
