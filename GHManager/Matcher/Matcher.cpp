//
// Created by Neboer on 2023/6/21.
//
#include "Matcher.h"

#include <utility>

namespace StringMatcher {

    Matcher::Matcher(MatchSetting base_setting) :
    base_match_setting(std::move(base_setting)) {
        re = QRegularExpression(base_match_setting.expression);
    };

    QString Matcher::match(const QString &input) {
        QRegularExpressionMatchIterator it = re.globalMatch(input);

        int currentIndex = 0;
        while (it.hasNext()) {
            QRegularExpressionMatch match = it.next();
            if (currentIndex == base_match_setting.outer_index) {
                QString capturedText = match.captured(base_match_setting.inner_index);
                return capturedText;
            }
            currentIndex++;
        }
        return {}; // no valid result
    }

} // GithubReleaseManager