#pragma once

#include <QString>
#include <QRegularExpression>

namespace StringMatcher {


    class MatchSetting {
    public:
        QString expression;
        int outer_index; // the nth match
        int inner_index; // the nth block in the match.
    };

    class Matcher {
    private:
        MatchSetting base_match_setting;
        QRegularExpression re;
    public:
        explicit Matcher(MatchSetting  base_setting);
        QString match(const QString &input);
    };

}

