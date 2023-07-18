#include "GHReleaseAssets.h"

#include <utility>
#include <QFile>
#include <QNetworkReply>

namespace GitHub {

    GHReleaseAssets::GHReleaseAssets(QString name, QString browser_download_url, int assetId, qint64 size) :
            name(std::move(name)), browser_download_url(std::move(browser_download_url)), asset_id(assetId),
            size(size) {}

    QNetworkReply *GHReleaseAssets::download_to(GHConnection *connection, const QString& download_path) const {
        QNetworkReply* download_reply = connection->download_file(browser_download_url);
        auto *dest_file = new QFile(download_path);
        if (!dest_file->open(QIODevice::WriteOnly)) {
            return nullptr;
        }

        QObject::connect(download_reply, &QNetworkReply::readyRead,
                         [download_reply, dest_file]() {
                             dest_file->write(download_reply->readAll());
                         });

        QObject::connect(download_reply, &QNetworkReply::finished, [download_reply, dest_file]() {
            dest_file->write(download_reply->readAll());
            dest_file->close();
        });

        // export network_reply to be connected to more slots.
        return download_reply;
    }
}
