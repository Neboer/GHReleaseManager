#pragma once
#include <QString>
#include <QVector>

namespace Version {

    class VersionNumber {
    private:
        QString ver_str;
        QVector<int> ver_num;
        void parseVersion();
    public:
        explicit VersionNumber(QString &version_string);
        VersionNumber() = default;
        QVector<int> getVersionNumbers() const;
        bool operator<(const VersionNumber &other) const;
        bool operator>(const VersionNumber &other) const;
        bool operator==(const VersionNumber &other) const;
    };

}
