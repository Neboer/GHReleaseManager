//
// Created by Neboer on 2023/6/25.
//
#include <QUrlQuery>
#include <QJsonArray>
#include <QJsonDocument>
#include "GHRepo.h"
constexpr int max_per_page = 100;
namespace GitHub {
    QCoro::AsyncGenerator<GHRelease> GHRepo::get_releases(GHConnection &connection) {
        QUrlQuery page_query{};
        page_query.addQueryItem("per_page", QString::number(max_per_page));
        for (int page = 1;; page++) {
            page_query.removeAllQueryItems("page");
            page_query.addQueryItem("page", QString::number(page));
            QJsonDocument releases_list_object = co_await connection.api_get(
                    "/repos/" + this->owner + "/" + this->repo + "/releases", page_query);
            QJsonArray releases_list_array = releases_list_object.array();
            for (const QJsonValue value: releases_list_array) {
                int id = value["id"].toInt();
                QDateTime created_at = QDateTime::fromString(value["created_at"].toString(), Qt::ISODate);
                QString name = value["name"].toString();
                QString body = value["body"].toString();
                QString tag_name = value["tag_name"].toString();
                bool prerelease = value["prerelease"].toBool();
                co_yield GHRelease(id, created_at, name, tag_name, body, prerelease, shared_from_this());
            }
            if (releases_list_array.size() < max_per_page) break;
        }
    }
    GHRepo::GHRepo(QString &owner, QString &repo) : owner(owner), repo(repo) {
    }
}