


########### next target ###############

set(ksgrd_LIB_SRCS
   SensorAgent.cpp
   SensorManager.cpp
   SensorShellAgent.cpp
   SensorSocketAgent.cpp
)

ecm_qt_declare_logging_category(ksgrd_LIB_SRCS HEADER ksgrd_debug.h IDENTIFIER LIBKSYSGUARD_KSGRD CATEGORY_NAME org.kde.libksysguard.ksgrd)
add_definitions(-DTRANSLATION_DOMAIN=\"ksgrd\")

remove_definitions(-DQT_NO_CAST_FROM_ASCII -DQT_STRICT_ITERATORS -DQT_NO_CAST_FROM_BYTEARRAY -DQT_NO_KEYWORDS)

add_library(ksgrd ${ksgrd_LIB_SRCS})
add_library(KF5::SysGuard ALIAS ksgrd)
target_include_directories(ksgrd
    PUBLIC
        "$<BUILD_INTERFACE:${libksysguard_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/ksysguard/>"
)

target_link_libraries(ksgrd
    PUBLIC
        Qt5::Core
        Qt5::Widgets # QWidget in SensorManager.h
        Qt5::Network # QTcpSocket in SensorSocketAgent.h
        KF5::ConfigCore # KConfigGroup in SensorManager.h
    PRIVATE
        KF5::I18n
        KF5::CoreAddons
        KF5::ConfigWidgets
        KF5::ProcessCore
)

set_target_properties(ksgrd PROPERTIES VERSION ${KSYSGUARD_VERSION_STRING} SOVERSION ${KSYSGUARD_SOVERSION} EXPORT_NAME SysGuard)
install(TARGETS ksgrd EXPORT libksysguardLibraryTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} )

install(FILES
    SensorAgent.h
    SensorClient.h
    SensorManager.h
    SensorShellAgent.h
    SensorSocketAgent.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/ksysguard/ksgrd
    COMPONENT Devel
)



