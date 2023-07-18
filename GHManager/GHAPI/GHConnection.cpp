#include "GHConnection.h"
#include <QJsonParseError>
#include <utility>

namespace GitHub {
    GHConnection::GHConnection(QString token, QObject *parent)
            : token(std::move(token)), manager(parent) {
    }

    QCoro::Task<QJsonDocument> GHConnection::api_get(const QString &url_endpoint, QUrlQuery &query_params) {
        QUrl request_url = base_url;
        request_url.setPath(url_endpoint);
        request_url.setQuery(query_params);
        QNetworkRequest request(request_url);
        request.setRawHeader("Authorization", "Bearer " + token.toUtf8());
        request.setRawHeader("Accept", "application/vnd.github+json");
        request.setRawHeader("X-GitHub-Api-Version", "2022-11-28");
        auto *reply = co_await manager.get(request);
        QJsonParseError parseError;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(reply->readAll(), &parseError);
        co_return jsonDocument;
    }

    QNetworkReply* GHConnection::download_file(const QUrl &file_url) {
        QNetworkRequest request(file_url);
        request.setRawHeader("Accept", "application/octet-stream");
        request.setRawHeader("Authorization", "Bearer " + token.toUtf8());
        request.setRawHeader("X-GitHub-Api-Version", "2022-11-28");
        return manager.get(request);
    }
}