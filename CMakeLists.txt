cmake_minimum_required(VERSION 3.30)

project(QOpenHDApp VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Platform-specific macro definitions
if(WIN32)
    add_compile_definitions(__windows__)
endif()

if(ANDROID)
    add_compile_definitions(__android__)
endif()

if(APPLE)
    if(IOS)
        add_compile_definitions(__ios__)
    else()
        add_compile_definitions(__macos__)
    endif()
endif()

if(UNIX AND NOT ANDROID AND NOT APPLE)
    add_compile_definitions(__desktoplinux__)
endif()

find_package(Qt6 REQUIRED COMPONENTS
        Core
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
qt_standard_project_setup(REQUIRES 6.5)

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
)

qt_add_executable(QOpenHDApp
    MANUAL_FINALIZATION
    ${QOPENHD_SOURCE_FILES_LIST}
    ##
    lib/geographiclib-c-2.0/src/geodesic.c
    ##
    qml/qml.qrc
    ##
    androidqt6/AndroidManifest.xml
)

target_include_directories(QOpenHDApp PUBLIC app)
target_include_directories(QOpenHDApp PUBLIC app/common)
target_include_directories(QOpenHDApp PUBLIC app/adsb)
target_include_directories(QOpenHDApp PUBLIC app/logging)
target_include_directories(QOpenHDApp PUBLIC app/osd)
target_include_directories(QOpenHDApp PUBLIC app/util)
target_include_directories(QOpenHDApp PUBLIC app/telemetry)
target_include_directories(QOpenHDApp PUBLIC app/telemetry/util)

target_include_directories(QOpenHDApp PUBLIC app/videostreaming/vscommon)
target_include_directories(QOpenHDApp PUBLIC app/videostreaming/vscommon/rtp)
target_include_directories(QOpenHDApp PUBLIC lib)
target_include_directories(QOpenHDApp PUBLIC lib/geographiclib-c-2.0/src)

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


target_link_libraries(QOpenHDApp
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
#    Qt6::Labs
#    Qt6::LabsSettings
)

set_target_properties(QOpenHDApp PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
)

set_property(TARGET QOpenHDApp APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
             ${CMAKE_CURRENT_SOURCE_DIR}/androidqt6)

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
