
#pragma once

#include <Qcoro/QCoroNetworkReply>
#include <Qcoro/QCoroAsyncGenerator>
#include <QString>


namespace GitHub {

    class GHConnection {
    private:
        QString token;
        QNetworkAccessManager manager;
        QUrl base_url = QUrl("https://api.github.com");

    public:
        explicit GHConnection(QString token, QObject *parent);
        QCoro::Task<QJsonDocument> api_get(const QString &url_endpoint, QUrlQuery &query_params);
        QNetworkReply* download_file(const QUrl &file_url);
    };
}

