
//
// Created by Neboer on 2023/6/25.
//

#pragma once

#include "GHConnection.h"
#include <QCoro/QCoroTask>
#include <QString>

namespace GitHub {

    class GHReleaseAssets {
    public:
        QString name;
        QString browser_download_url;
        int asset_id = 0;
        qint64 size = 0;

        GHReleaseAssets(QString name, QString browser_download_url, int asset_id, qint64 size);
        GHReleaseAssets() = default;

        QNetworkReply* download_to(GHConnection *connection, const QString& download_path) const;
    };
}
