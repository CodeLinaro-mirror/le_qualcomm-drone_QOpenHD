cmake_minimum_required(VERSION 3.16)
include(cmake/qt.cmake)

project(QOpenHDApp VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/platforms.cmake)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
        Gui
        Quick
        Widgets
        Qml
        QuickControls2)

# Try to find optional components
find_package(Qt6 QUIET COMPONENTS
    QuickLayouts
    QuickControls2Impl
    QuickTemplates2
    QuickControls2Material
    QuickControls2Basic
    QuickControls2Fusion
    QuickControls2Imagine
    QuickControls2Universal
    Labs
    LabsSettings)

if(Qt6QuickLayouts_FOUND)
    message(STATUS "Qt6QuickLayouts found")
else()
    message(WARNING "Qt6QuickLayouts not found")
endif()

if(Qt6QuickControls2Material_FOUND)
    message(STATUS "Qt6QuickControls2Material found")
else()
    message(WARNING "Qt6QuickControls2Material not found")
endif()

qt_standard_project_setup()

set(QOPENHD_SOURCE_FILES_LIST
    app/main.cpp
    #
    app/adsb/adsbvehicle.cpp
    app/adsb/adsbvehiclemanager.cpp
    app/adsb/qmlobjectlistmodel.cpp
    #
    app/util/WorkaroundMessageBox.cpp
    app/util/mousehelper.cpp
    app/util/qopenhd.cpp
    app/util/qrenderstats.cpp
    app/util/restartqopenhdmessagebox.cpp
    #
    app/osd/altitudeladder.cpp
    app/osd/aoagauge.cpp
    app/osd/flightpathvector.cpp
    app/osd/headingladder.cpp
    app/osd/horizonladder.cpp
    app/osd/speedladder.cpp
    #
    app/logging/hudlogmessagesmodel.cpp
    app/logging/logmessagesmodel.cpp
    #
    app/telemetry/MavlinkTelemetry.cpp
    app/telemetry/action/fcaction.cpp
    app/telemetry/action/fcmissionhandler.cpp
    app/telemetry/action/fcmsgintervalhandler.cpp
    app/telemetry/action/ohdaction.cpp
    app/telemetry/action/impl/cmdsender.cpp
    app/telemetry/action/impl/xparam.cpp
    app/telemetry/connection/mavlinkchannel.cpp
    app/telemetry/connection/tcp_connection.cpp
    app/telemetry/connection/udp_connection.cpp
    app/telemetry/models/aohdsystem.cpp
    app/telemetry/models/camerastreammodel.cpp
    app/telemetry/models/fcmapmodel.cpp
    app/telemetry/models/fcmavlinkmissionitemsmodel.cpp
    app/telemetry/models/fcmavlinksystem.cpp
    app/telemetry/models/markermodel.cpp
    app/telemetry/models/rcchannelsmodel.cpp
    app/telemetry/models/wificard.cpp
    app/telemetry/settings/documentedparam.cpp
    app/telemetry/settings/frequencyhelper.cpp
    app/telemetry/settings/improvedintsetting.cpp
    app/telemetry/settings/improvedstringsetting.cpp
    app/telemetry/settings/mavlinksettingsmodel.cpp
    app/telemetry/settings/pollutionhelper.cpp
    app/telemetry/settings/wblinksettingshelper.cpp
    app/telemetry/tutil/geodesi_helper.cpp
    #
    #app/videostreaming/vscommon/custom/rawreceiver.cpp
    #app/videostreaming/vscommon/rtp/rtpreceiver.cpp
    #app/videostreaming/vscommon/rtp/ParseRTP.cpp
    app/videostreaming/vscommon/decodingstatistcs.cpp
    app/videostreaming/vscommon/audio_playback.cpp
    app/videostreaming/vscommon/rtp/ParseRTP.cpp
    app/videostreaming/vscommon/rtp/rtpreceiver.cpp
    app/videostreaming/vscommon/udp/UDPReceiver.cpp
    app/videostreaming/vscommon/decodingstatistcs.cpp

    lib/geographiclib-c-2.0/src/geodesic.c
)

if(QT_VERSION VERSION_LESS 5.15)
    qt5_add_resources(QOPENHD_SOURCE_FILES_LIST qml/qml.qrc)
else()
    qt_add_resources(QOPENHD_SOURCE_FILES_LIST qml/qml.qrc)
endif()

qt_add_executable(${PROJECT_NAME} ${QOPENHD_SOURCE_FILES_LIST})

#qt_add_executable(QOpenHDApp
#    MANUAL_FINALIZATION
#    ${QOPENHD_SOURCE_FILES_LIST}
#    ##
#    lib/geographiclib-c-2.0/src/geodesic.c
#    ##
#    qml/qml.qrc
#    ##
#    androidqt6/AndroidManifest.xml
#)

if(QT_VERSION VERSION_GREATER_EQUAL 6.2)
    qt_add_qml_module(${PROJECT_NAME}
        URI org.openhdfpv
        VERSION 1.0
        RESOURCE_PREFIX "/"
    )
endif()

target_include_directories(${PROJECT_NAME} PUBLIC app)
target_include_directories(${PROJECT_NAME} PUBLIC app/common)
target_include_directories(${PROJECT_NAME} PUBLIC app/adsb)
target_include_directories(${PROJECT_NAME} PUBLIC app/logging)
target_include_directories(${PROJECT_NAME} PUBLIC app/osd)
target_include_directories(${PROJECT_NAME} PUBLIC app/util)
target_include_directories(${PROJECT_NAME} PUBLIC app/telemetry)
target_include_directories(${PROJECT_NAME} PUBLIC app/telemetry/util)

target_include_directories(${PROJECT_NAME} PUBLIC app/videostreaming/vscommon)
target_include_directories(${PROJECT_NAME} PUBLIC app/videostreaming/vscommon/rtp)
target_include_directories(${PROJECT_NAME} PUBLIC lib)
target_include_directories(${PROJECT_NAME} PUBLIC lib/geographiclib-c-2.0/src)

#qt_add_qml_module(QOpenHDApp
#    URI hello
#    VERSION 1.0
#    QML_FILES
#        qml/main.qml
#        qml/ui/AnyParamBusyIndicator.qml
#        qml/ui/HUDOverlayGrid.qml
#        qml/ui/elements/
#        qml/ui/sidebar/
#        qml/ui/widgets/
#)
#qt6_add_resources(qml_QRC
#    PREFIX "/"
#    qml/qml.qrc)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Gui
    Qt6::Widgets
    Qt6::Qml
    Qt6::QuickControls2
    Qt6::QuickLayouts
    Qt6::QuickControls2Impl
    Qt6::QuickTemplates2
    WindowsVideoPlugin
#    Qt6::Labs
#    Qt6::LabsSettings
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
)

if(ANDROID)
    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/androidqt6)
endif()

# Include plugins
add_subdirectory(plugins/windowsVideo)

include(lib/h264/h264.cmake)
#include(app/videostreaming/avcodec/avcodec_video.cmake)
#include(app/videostreaming/android/videostreamingandroid.cmake)
#include(app/videostreaming/gstreamer/gst_video.cmake)

#include(GNUInstallDirs)
#install(TARGETS QOpenHD
#    BUNDLE DESTINATION .
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)

if(Qt6_FOUND)
    qt_import_qml_plugins(${PROJECT_NAME})
endif()

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()

    # Get QT path
    get_target_property(QT_QMAKE_EXECUTABLE Qt6::qmake IMPORTED_LOCATION)
    if(QT_QMAKE_EXECUTABLE)
        get_filename_component(QT_WINDEPLOYQT_EXECUTABLE ${QT_QMAKE_EXECUTABLE} PATH)
        get_filename_component(QT_INSTALL_PATH ${QT_WINDEPLOYQT_EXECUTABLE} PATH)
    else()
        set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
            if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
                set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
            endif ()
        endif ()
    endif()

    # Plugins copy
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()

    # QT6 Dlls copy
    foreach (QT_LIB Core Gui Widgets Quick Qml Network QmlMeta QmlModels OpenGL QmlWorkerScript QuickControls2 QuickLayouts QuickTemplates2 LabsSettings)
        set(QT_DLL_PATH "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll")
        if(EXISTS "${QT_DLL_PATH}")
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_DLL_PATH}"
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
        else()
            message(WARNING "Qt6 DLL not found: ${QT_DLL_PATH}")
        endif()
    endforeach (QT_LIB)

    # Copy QML models
    if(EXISTS "${QT_INSTALL_PATH}/qml")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${QT_INSTALL_PATH}/qml"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/qml")
    endif()

    # Copy Qt plugins
    if(EXISTS "${QT_INSTALL_PATH}/plugins")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${QT_INSTALL_PATH}/plugins"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins")
    endif()

    # Creating qt.conf
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "[Paths]\nPlugins = plugins\nQml2Imports = qml"
            > "$<TARGET_FILE_DIR:${PROJECT_NAME}>/qt.conf")

    # Use windeployqt if available
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS ${QT_INSTALL_PATH}/bin)
    if(WINDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${WINDEPLOYQT_EXECUTABLE} --qmldir ${CMAKE_CURRENT_SOURCE_DIR}/qml "$<TARGET_FILE_DIR:${PROJECT_NAME}>/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
                COMMENT "Deploying Qt libraries using windeployqt")
    endif()
endif ()
