//
// Created by Neboer on 2023/7/3.
//

#include <QRegularExpressionMatchIterator>
#include "Version.h"

namespace Version {
    void VersionNumber::parseVersion() {
        QRegularExpression regex("\\d+");
        QRegularExpressionMatchIterator matchIterator = regex.globalMatch(ver_str);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            QString numStr = match.captured();
            bool ok;
            int num = numStr.toInt(&ok);
            if (ok) {
                ver_num.append(num);
            }
        }
    }

    VersionNumber::VersionNumber(QString &version_string) {
        ver_str = version_string;
        parseVersion();
    }

    QVector<int> VersionNumber::getVersionNumbers() const {
        return ver_num;
    }

    bool VersionNumber::operator<(const VersionNumber &other) const {
        return ver_num < other.ver_num;
    }

    bool VersionNumber::operator>(const VersionNumber &other) const {
        return ver_num > other.ver_num;
    }

    bool VersionNumber::operator==(const VersionNumber &other) const {
        return ver_num == other.ver_num;
    }

} // Version