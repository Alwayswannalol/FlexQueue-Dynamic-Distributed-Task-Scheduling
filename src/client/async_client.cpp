#include "async_client.h"

void async_client::distribute_detection_task_call::proceed(bool ok, std::string& response) {
    if (ok) {
        if (status.ok()) {
            std::cout << client_name_ << ": To node: " << path_response.path() << std::endl;
            response = path_response.path();
        }
    }
    else {
        std::cerr << "Error: CompletionQueue returned ok == false" << std::endl;
    }
}

void async_client::detection_task_execution_call::proceed(bool ok, std::string& response) {
    if (call_status_ == PROCESS_CALL) {
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

            std::cout << client_name_ << ": Getting img: " << response_.filename() << std::endl;

            std::string filename_ = response_.filename();
            if (filename_ != prev_filename_) {
                if (!writing_stream.is_open()) {
                    writing_stream.open(result_dir_ + filename_, std::ios::app);
                }
                else {
                    writing_stream.close();
                    writing_stream.open(result_dir_ + filename_, std::ios::app);
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

void async_client::async_distribute_detection_task(task_info task) {
    auto* call = new distribute_detection_task_call(task_execution_stub_, cq_, CALL_TYPE::DISTRIBUTE_DETECTION_TASK_CALL, task, client_name_);
}

void async_client::async_execute_detection_task(std::vector<std::string> filePaths) {
    auto* call = new detection_task_execution_call(task_execution_stub_, cq_, CALL_TYPE::DETECTION_TASK_EXECUTION_CALL, filePaths, client_name_, result_dir_);
}

void async_client::handle_call(std::atomic<int>& quant_replies, std::condition_variable& cv, std::string& response) {
    void* got_tag;
    bool ok = false;

    while (cq_.Next(&got_tag, &ok)) {
        // Восстанавливаем объект async_call
        auto* call = static_cast<base_call*>(got_tag);

        std::unique_lock<std::mutex> lock(mtx_);

        call->proceed(ok, response);

        quant_replies--;
        if (quant_replies == 0) {
            cv.notify_one(); // Уведомляем основной поток о завершении всех запросов
        }
    }
}
