if (WIN32)
    set(system_components_SRCS w32-util.c)
else()
    set(system_components_SRCS posix-util.c posix-io.c)
endif()

if (HAVE_UISERVER)
    set(uiserver_components_SRCS engine-uiserver.c)
endif()

set(gpg_SRCS
    conversion.c
    b64dec.c
    get-env.c
    parsetlv.c
    mbox-util.c
    data.c
    data-fd.c
    data-stream.c
    data-mem.c
    data-user.c
    data-estream.c
    data-compat.c
    data-identify.c
    signers.c
    sig-notation.c
    wait.c
    wait-global.c
    wait-private.c
    wait-user.c
    op-support.c
    encrypt.c
    encrypt-sign.c
    decrypt.c
    decrypt-verify.c
    verify.c
    sign.c
    passphrase.c
    progress.c
    key.c
    keylist.c
    keysign.c
    trust-item.c
    trustlist.c
    tofupolicy.c
    import.c
    export.c
    genkey.c
    delete.c
    edit.c
    getauditlog.c
    opassuan.c
    passwd.c
    spawn.c
    assuan-support.c
    engine.c
    engine-gpg.c
    status-table.c
    engine-gpgsm.c
    engine-assuan.c
    engine-gpgconf.c
    ${uiserver_components_SRCS}
    engine-g13.c
    vfs-mount.c
    vfs-create.c
    engine-spawn.c
    gpgconf.c
    queryswdb.c
    ${system_components_SRCS}
    dirinfo.c
    debug.c
    gpgme.c
    version.c
    error.c
    ath.c
)

parse_lt(LIBGPGME)
math(EXPR MAJOR "${LIBGPGME_LT_CURRENT} - ${LIBGPGME_LT_AGE}")

add_library(gpgme ${gpg_SRCS})
set_target_properties(gpgme PROPERTIES
    VERSION "${MAJOR}.${LIBGPGME_LT_AGE}.${LIBGPGME_LT_REVISION}"
    SOVERSION "${MAJOR}"
)
target_include_directories(gpgme
    PUBLIC ${LIBASSUAN_INCLUDE_DIRS} ${GPG_ERROR_INCLUDE_DIRS}
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)
target_link_libraries(gpgme c ${LIBASSUAN_LIBRARIES} ${GPG_ERROR_LIBRARIES})

if (WIN32)
    add_executable(gpgme-w32spawn gpgme-w32spawn.c)
endif()

set(prefix ${CMAKE_INSTALL_PREFIX})
set(exec_prefix ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR})
set(includedir ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR})
set(libdir ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})
set(GPGME_CONFIG_API_VERSION "1")
set(GPGME_CONFIG_LIBS "-lgpgme")
foreach (lib ${LIBASSUAN_LIBRARIES})
    set(LIBASSUAN_LIBS "${LIBASSUAN_LIBS} -l${lib}")
endforeach()
foreach (lib ${GPG_ERROR_LIBRARIES})
    set(GPG_ERROR_LIBS "${GPG_ERROR_LIBS} -l${lib}")
endforeach()

add_executable(gpgme-json gpgme-json.c argparse.c cJSON.c)
target_include_directories(gpgme-json PRIVATE ${LIBASSUAN_INCLUDE_DIRS})
target_link_libraries(gpgme-json gpgme m ${LIBASSUAN_LIBRARIES})

add_executable(gpgme-tool gpgme-tool.c argparse.c)
target_include_directories(gpgme-tool PRIVATE ${LIBASSUAN_INCLUDE_DIRS})
target_link_libraries(gpgme-tool gpgme ${LIBASSUAN_LIBRARIES})

configure_file(gpgme-config.in ${CMAKE_CURRENT_BINARY_DIR}/gpgme-config @ONLY)

set(GPGME_VERSION ${CMAKE_PROJECT_VERSION})
math(EXPR VERSION_NUMBER "(${PROJECT_VERSION_MAJOR} << 16) + (${PROJECT_VERSION_MINOR} << 8) + ${PROJECT_VERSION_PATCH}" OUTPUT_FORMAT HEXADECIMAL)
configure_file(gpgme.h.in ${CMAKE_CURRENT_BINARY_DIR}/gpgme.h @ONLY)

configure_file(gpgme-glib.pc.in ${CMAKE_CURRENT_BINARY_DIR}/gpgme-glibc.pc)

install(TARGETS gpgme DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS gpgme-json gpgme-tool DESTINATION ${CMAKE_INSTALL_BINDIR})
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/gpgme-config DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${gpgme_HEADERS} ${CMAKE_CURRENT_BINARY_DIR}/gpgme.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/gpgme)
