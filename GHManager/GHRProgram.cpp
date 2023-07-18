//
// Created by Neboer on 2023/6/20.
//
#include "GHRProgram.h"
#include <utility>

namespace GithubReleaseManager {

    GHRProgram::GHRProgram(GHRPBaseSetting &ghrp_base_setting, std::shared_ptr<GitHub::GHConnection> connection) :
            base_setting(ghrp_base_setting),
            repo(ghrp_base_setting.repo_owner, ghrp_base_setting.repo_name),
            connection(std::move(connection)),
            name_matcher(ghrp_base_setting.name_matcher_conf),
            version_matcher(ghrp_base_setting.version_matcher_conf),
            latest_release(), latest_release_asset() {}

    // first, check update. this fills the latest_release/remote_version/last_check_update_time value.
    QCoro::Task<bool> GHRProgram::check_update() {
        auto gh_releases_generator = repo.get_releases(*connection);
        QCORO_FOREACH(GitHub::GHRelease &current_release, gh_releases_generator) {
                    if ((!base_setting.use_prerelease && !current_release.prerelease) || base_setting.use_prerelease) {
                        latest_release = std::move(current_release);
                        last_check_update_time = QDateTime::currentDateTime();
                        remote_version = extract_version(latest_release);
                        break;
                    }
                }
        co_return remote_version > local_version;
    }

    // third, after the installation completed, set local version to new version.
    void GHRProgram::set_local_version(Version::VersionNumber &new_version) {
        local_version = new_version;
    }

    // second, get asset.
    QCoro::Task<void> GHRProgram::get_matched_latest_release_asset() {
        auto latest_release_assets_generator = latest_release.get_assets(*connection);
        QCORO_FOREACH(GitHub::GHReleaseAssets &asset, latest_release_assets_generator) {
                    if (!name_matcher.match(asset.name).isEmpty()) {
                        latest_release_asset = std::move(asset);
                        break;
                    }
                }
    }

    Version::VersionNumber GHRProgram::extract_version(GitHub::GHRelease &release) {
        QString version_info_str = "";
        switch (base_setting.release_version_info_location) {

            case name:
                version_info_str = release.name;
                break;
            case tag_name:
                version_info_str = release.tag_name;
                break;
            case body:
                version_info_str = release.body;
                break;
        }

        QString match_result = version_matcher.match(version_info_str);
        return Version::VersionNumber(match_result);
    }
}