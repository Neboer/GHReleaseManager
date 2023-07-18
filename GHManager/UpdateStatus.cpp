//
// Created by Neboer on 2023/6/22.
//
#include "UpdateStatus.h"
UpdateStatus::UpdateStatus(qint64 total_file_size) {
    total_file_size_bytes = total_file_size;
    is_downloading = true;
}
void UpdateStatus::report_download_bytes(qint64 download_size) {
    download_bytes = download_size;
}
