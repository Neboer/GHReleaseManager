#pragma once
#include <QCoro/QCoroTask>
#include <QString>
#include <QRegularExpression>
#include "GHAPI/GHRepo.h"
#include "UpdateStatus.h"
#include "Matcher/Matcher.h"
#include "Version/Version.h"

namespace GithubReleaseManager {

    enum GHRepoReleaseInfoLocation {
        name,
        tag_name,
        body
    };

    class GHRPBaseSetting {
    public:
        QString repo_owner;
        QString repo_name;
        bool use_prerelease;
        StringMatcher::MatchSetting name_matcher_conf; // match GitHub release assets
        // match repo version
        StringMatcher::MatchSetting version_matcher_conf;
        GHRepoReleaseInfoLocation release_version_info_location;

        QString install_script;
    };

    class GHRProgram {
    private:
        GitHub::GHRepo repo;
        GitHub::GHRelease latest_release;
        GitHub::GHReleaseAssets latest_release_asset;
        std::shared_ptr<GitHub::GHConnection> connection;

        StringMatcher::Matcher name_matcher;
        StringMatcher::Matcher version_matcher;

        GHRPBaseSetting base_setting;

        Version::VersionNumber extract_version(GitHub::GHRelease &release);

    public:

        Version::VersionNumber local_version;
        Version::VersionNumber remote_version;
        QDateTime last_check_update_time;
        QDateTime last_update_time;
        UpdateStatus update_status;

        explicit GHRProgram(GHRPBaseSetting &ghrp_base_setting, std::shared_ptr<GitHub::GHConnection> connection);
        QCoro::Task<bool> check_update();
        void set_local_version(Version::VersionNumber &new_version);
        QCoro::Task<void> get_matched_latest_release_asset();
    };

}

