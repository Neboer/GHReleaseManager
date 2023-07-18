#include "GHRelease.h"
#include <utility>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonArray>

#include "GHRepo.h" // include here

constexpr int max_per_page = 100;
namespace GitHub {

    GHRelease::GHRelease(int id, QDateTime created_at, QString name, QString tag_name, QString body,
                         bool prerelease, std::shared_ptr<GHRepo> parent_repo)
            : created_at(std::move(created_at)), name(std::move(name)),
              tag_name(std::move(tag_name)), body(std::move(body)), id(id),
              prerelease(prerelease), repo(std::move(parent_repo)) {
    }

    QCoro::AsyncGenerator<GHReleaseAssets> GHRelease::get_assets(GHConnection &connection) {
        QUrlQuery page_query{};
        page_query.addQueryItem("per_page", QString::number(max_per_page));
        for (int page = 1;; page++) {
            page_query.removeAllQueryItems("page");
            page_query.addQueryItem("page", QString::number(page));
            QJsonDocument releases_assets_list_object = co_await connection.api_get(
                    QString("/repos/%1/%2/releases/%3/assets")
                            .arg(repo->owner, repo->repo, QString::number(id)), page_query);
            QJsonArray releases_assets_list_array = releases_assets_list_object.array();
            for (const QJsonValue release_assets_value: releases_assets_list_array) {
                QString asset_name = release_assets_value["name"].toString();
                auto asset_id = release_assets_value["id"].toInt();
                QString browser_download_url = release_assets_value["browser_download_url"].toString();
                qint64 size = release_assets_value["size"].toInteger(0);
                co_yield GHReleaseAssets(asset_name, browser_download_url, asset_id, size);
            }
            if (releases_assets_list_array.size() < max_per_page) break;
        }
    }
}