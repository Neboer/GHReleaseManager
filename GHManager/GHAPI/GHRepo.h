
//
// Created by Neboer on 2023/6/25.
//

#pragma once

#include "GHRelease.h"
#include "GHConnection.h"

namespace GitHub {

    class GHRepo : public std::enable_shared_from_this<GHRepo> {
    public:
        QString owner;
        QString repo;

        GHRepo(QString &owner, QString &repo);

        QCoro::AsyncGenerator<GHRelease> get_releases(GHConnection &connection);
    };

} // GitHub

