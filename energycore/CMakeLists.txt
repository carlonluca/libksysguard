add_definitions(-DTRANSLATION_DOMAIN=\"energycore\")

########### next target ###############

set(energycore_LIB_SRCS
    energy.cpp
)
ecm_qt_declare_logging_category(energycore_LIB_SRCS HEADER energycore_debug.h IDENTIFIER LIBKSYSGUARD_ENERGYCORE CATEGORY_NAME org.kde.libksysguard.energycore)
add_library(energycore ${energycore_LIB_SRCS})
add_library(KF5::EnergyCore ALIAS energycore)

# TODO: Can I remove zlib?
target_link_libraries(energycore
   PUBLIC
    Qt5::Core
   PRIVATE
    KF5::I18n
    KF5::Auth
    ${ZLIB_LIBRARIES}
)

target_include_directories(energycore
    PUBLIC
        "$<BUILD_INTERFACE:${libksysguard_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/ksysguard>"
)
set_target_properties(energycore
    PROPERTIES VERSION ${KSYSGUARD_VERSION_STRING}
    SOVERSION ${KSYSGUARD_SOVERSION}
    EXPORT_NAME EnergyCore
)
install(TARGETS energycore EXPORT libksysguardLibraryTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} )

########### install files ###############

install(FILES
    energy.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/ksysguard/energycore
    COMPONENT Devel
)

#------ KAuth stuff
set(ksysguardenergycore_helper_srcs
    energyhelper.cpp
)
add_executable(ksysguardenergycore_helper ${ksysguardenergycore_helper_srcs})
target_link_libraries(ksysguardenergycore_helper Qt5::Core KF5::Auth KF5::I18n)
target_link_libraries(ksysguardenergycore_helper "${CMAKE_CURRENT_SOURCE_DIR}/libpowertop.a")
target_link_libraries(ksysguardenergycore_helper -lpthread -ltinfo -lncurses -lpci -lnl-genl-3 -lnl-3)
include_directories(ksysguardenergycore_helper "${CMAKE_CURRENT_SOURCE_DIR}/powertop/src/lib")
install(TARGETS ksysguardenergycore_helper DESTINATION ${KAUTH_HELPER_INSTALL_DIR})
kauth_install_helper_files(ksysguardenergycore_helper org.kde.ksysguard.energycorehelper root)
kauth_install_actions(org.kde.ksysguard.energycorehelper actions.actions)
set_target_properties(ksysguardenergycore_helper PROPERTIES COMPILE_FLAGS "-Wall -ggdb")
