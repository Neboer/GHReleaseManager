
//
// Created by Neboer on 2023/6/25.
//

#pragma once

#include <QCoro/QCoroAsyncGenerator>
#include <QDateTime>
#include <QString>
#include "GHReleaseAssets.h"
#include "GHConnection.h"

namespace GitHub {

    class GHRepo;

    class GHRelease {
    public:
        GHRelease(int id, QDateTime created_at, QString name, QString tag_name,
                  QString body, bool prerelease, std::shared_ptr<GHRepo> parent_repo);

        GHRelease() = default;

        QCoro::AsyncGenerator<GHReleaseAssets> get_assets(GHConnection &connection);

        QDateTime created_at = QDateTime();
        QString name = QString();
        QString tag_name = QString();
        QString body = QString();
        int id = 0;
        bool prerelease = false;

    private:
        std::shared_ptr<GHRepo> repo;
    };
}

