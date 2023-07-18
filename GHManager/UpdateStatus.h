#pragma once

#include <QFile>

class UpdateStatus {
public:
    bool is_downloading = false;
    bool is_installing = false;

    qint64 download_bytes = 0;
    qint64 total_file_size_bytes = 0;

    QString install_log = "";

    explicit UpdateStatus(qint64 total_file_size);
    UpdateStatus() = default;
    void report_download_bytes(qint64 download_size);
    void report_install_output(QString extra_log);
};
