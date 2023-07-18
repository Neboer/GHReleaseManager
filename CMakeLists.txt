cmake_minimum_required(VERSION 3.5)
project(GHReleaseManager VERSION 0.1 LANGUAGES CXX)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Network)
set(TS_FILES GHReleaseManager_zh_CN.ts)
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        GHManager/GHManager.cpp
        watchertableview.cpp
        watchertableview.h
        GHManager/GHManager.h
        ${TS_FILES}
        GHManager/GHRProgram.cpp GHManager/GHRProgram.h ProxyDialog.h ProxyDialog.cpp GHManager/Matcher/Matcher.cpp GHManager/Matcher/Matcher.h GHManager/UpdateStatus.cpp GHManager/UpdateStatus.h GHManager/GHAPI/GHRepo.cpp GHManager/GHAPI/GHRepo.h GHManager/GHAPI/GHRelease.cpp GHManager/GHAPI/GHRelease.h GHManager/GHAPI/GHReleaseAssets.cpp GHManager/GHAPI/GHReleaseAssets.h GHManager/GHAPI/GHConnection.cpp GHManager/GHAPI/GHConnection.h GHManager/Version/Version.cpp GHManager/Version/Version.h)
if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GHReleaseManager
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            ProxyDialog.ui
            )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET GHReleaseManager APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else ()
    if (ANDROID)
        add_library(GHReleaseManager SHARED
                ${PROJECT_SOURCES}
                )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else ()
        add_executable(GHReleaseManager
                ${PROJECT_SOURCES}
                )
    endif ()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif ()
set(QCORO_BUILD_EXAMPLES OFF)
set(USE_QT_VERSION 6)
set(QCORO_WITH_QTWEBSOCKETS ON)
set(QCORO_WITH_QTDBUS OFF)
set(QCORO_DISABLE_DEPRECATED_TASK_H ON)
add_subdirectory(qcoro)
qcoro_enable_coroutines()
target_link_libraries(GHReleaseManager PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network QCoro6::Core QCoro6::Network)
set_target_properties(GHReleaseManager PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        )
install(TARGETS GHReleaseManager
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        )
if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GHReleaseManager)
endif ()
