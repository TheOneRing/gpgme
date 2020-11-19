set(gpgmepp_SRCS
    callbacks.cpp
    configuration.cpp
    context.cpp
    data.cpp
    decryptionresult.cpp
    defaultassuantransaction.cpp
    editinteractor.cpp
    encryptionresult.cpp
    engineinfo.cpp
    eventloopinteractor.cpp
    exception.cpp
    gpgadduserideditinteractor.cpp
    gpgagentgetinfoassuantransaction.cpp
    gpggencardkeyinteractor.cpp
    gpgsetexpirytimeeditinteractor.cpp
    gpgsetownertrusteditinteractor.cpp
    gpgsignkeyeditinteractor.cpp
    importresult.cpp
    key.cpp
    keygenerationresult.cpp
    keylistresult.cpp
    scdgetinfoassuantransaction.cpp
    signingresult.cpp
    swdbresult.cpp
    tofuinfo.cpp
    trustitem.cpp
    verificationresult.cpp
    vfsmountresult.cpp
)

set(gpgmepp_HEADERS
    callbacks.h
    configuration.h
    context.h
    data.h
    decryptionresult.h
    defaultassuantransaction.h
    editinteractor.h
    encryptionresult.h
    engineinfo.h
    error.h
    eventloopinteractor.h
    exception.h
    global.h
    gpgadduserideditinteractor.h
    gpgagentgetinfoassuantransaction.h
    gpggencardkeyinteractor.h
    gpgmefw.h
    gpgmepp_export.h
    gpgsetexpirytimeeditinteractor.h
    gpgsetownertrusteditinteractor.h
    gpgsignkeyeditinteractor.h
    importresult.h
    key.h
    keygenerationresult.h
    keylistresult.h
    notation.h
    result.h
    scdgetinfoassuantransaction.h
    signingresult.h
    swdbresult.h
    tofuinfo.h
    trustitem.h
    util.h
    verificationresult.h
    vfsmountresult.h
)

set(gpgmepp_interface_HEADERS
    interfaces/assuantransaction.h
    interfaces/dataprovider.h
    interfaces/passphraseprovider.h
    interfaces/progressprovider.h
)

add_definitions(-DBUILDING_GPGMEPP)

add_library(gpgmepp ${gpgmepp_SRCS})
target_include_directories(gpgmepp
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${GPGME_INCLUDE_DIRS}>
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:${GPGME_INCLUDE_DIRS}>
)
target_link_libraries(gpgmepp ${GPGME_LIBRARIES})

parse_lt(LIBGPGMEPP)
math(EXPR MAJOR "${LIBGPGMEPP_LT_CURRENT}-${LIBGPGMEPP_LT_AGE}")

set_target_properties(gpgmepp PROPERTIES
    VERSION "${MAJOR}.${LIBGPGMEPP_LT_AGE}.${LIBGPGMEPP_LT_REVISION}"
    SOVERSION ${MAJOR}
)

file(COPY ${gpgmepp_HEADERS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/gpgme++/)
file(COPY ${gpgmepp_interface_HEADERS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/gpgme++/interfaces)

set(resolved_includedir "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
set(resolved_libdir "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
set(resolved_bindir "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}")
set(libsuffix  ".dll")

if (WIN32)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/GpgmeppConfig-w32.cmake.in.in
                   ${CMAKE_CURRENT_BINARY_DIR}/GpgmeppConfig.cmake @ONLY)
else()
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/GpgmeppConfig.cmake.in.in
                   ${CMAKE_CURRENT_BINARY_DIR}/GpgmeppConfig.cmake @ONLY)
endif()
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/GpgmeppConfigVersion.cmake.in
               ${CMAKE_CURRENT_BINARY_DIR}/GpgmeppConfigVersion.cmake @ONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/gpgmepp_version.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/gpgmepp_version.h)

install(TARGETS gpgmepp
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/gpgme++
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/gpgmepp_version.h
              ${CMAKE_CURRENT_SOURCE_DIR}/gpgmepp_export.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/gpgme++)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/GpgmeppConfigVersion.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/GpgmeppConfig.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Gpgmepp
)
