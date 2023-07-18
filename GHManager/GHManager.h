
#pragma once#include <QVector>
#include "GHRProgram.h"

namespace GithubReleaseManager {

    class GHManager {
    private:
        QVector<GHRProgram> GHRPrograms;
        GitHub::Request Requester;

    public:
        void add_GHRProgram(GHRProgram &ghrProgram);
        void remove_GHRProgram_index(int index);
        void recheck_remote_version();
        void recheck_local_version();
    };

}

