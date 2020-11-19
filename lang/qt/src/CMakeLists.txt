set(qgpgme_SRCS
    cryptoconfig.cpp
    dataprovider.cpp
    defaultkeygenerationjob.cpp
    dn.cpp
    job.cpp
    multideletejob.cpp
    qgpgmeadduseridjob.cpp
    qgpgmebackend.cpp
    qgpgmechangeexpiryjob.cpp
    qgpgmechangeownertrustjob.cpp
    qgpgmechangepasswdjob.cpp
    qgpgme_debug.cpp
    qgpgmedecryptjob.cpp
    qgpgmedecryptverifyjob.cpp
    qgpgmedeletejob.cpp
    qgpgmedownloadjob.cpp
    qgpgmeencryptjob.cpp
    qgpgmeexportjob.cpp
    qgpgmegpgcardjob.cpp
    qgpgmeimportfromkeyserverjob.cpp
    qgpgmeimportjob.cpp
    qgpgmekeyformailboxjob.cpp
    qgpgmekeygenerationjob.cpp
    qgpgmekeylistjob.cpp
    qgpgmelistallkeysjob.cpp
    qgpgmenewcryptoconfig.cpp
    qgpgmequickjob.cpp
    qgpgmerefreshkeysjob.cpp
    qgpgmesecretkeyexportjob.cpp
    qgpgmesignencryptjob.cpp
    qgpgmesignjob.cpp
    qgpgmesignkeyjob.cpp
    qgpgmetofupolicyjob.cpp
    qgpgmeverifydetachedjob.cpp
    qgpgmeverifyopaquejob.cpp
    qgpgmewkspublishjob.cpp
    threadedjobmixin.cpp
)

set(qgpgme_HEADERS
    abstractimportjob.h
    adduseridjob.h
    changeexpiryjob.h
    changeownertrustjob.h
    changepasswdjob.h
    cryptoconfig.h
    dataprovider.h
    decryptjob.h
    decryptverifyjob.h
    defaultkeygenerationjob.h
    deletejob.h
    dn.h
    downloadjob.h
    encryptjob.h
    exportjob.h
    gpgcardjob.h
    hierarchicalkeylistjob.h
    importfromkeyserverjob.h
    importjob.h
    job.h
    keyformailboxjob.h
    keygenerationjob.h
    keylistjob.h
    listallkeysjob.h
    multideletejob.h
    protocol.h
    qgpgmeadduseridjob.h
    qgpgmebackend.h
    qgpgmechangeexpiryjob.h
    qgpgmechangeownertrustjob.h
    qgpgmechangepasswdjob.h
    qgpgmedecryptjob.h
    qgpgmedecryptverifyjob.h
    qgpgmedeletejob.h
    qgpgmedownloadjob.h
    qgpgmeencryptjob.h
    qgpgme_export.h
    qgpgmeexportjob.h
    qgpgmegpgcardjob.h
    qgpgmeimportfromkeyserverjob.h
    qgpgmeimportjob.h
    qgpgmekeyformailboxjob.h
    qgpgmekeygenerationjob.h
    qgpgmekeylistjob.h
    qgpgmelistallkeysjob.h
    qgpgmenewcryptoconfig.h
    qgpgmequickjob.h
    qgpgmerefreshkeysjob.h
    qgpgmesecretkeyexportjob.h
    qgpgmesignencryptjob.h
    qgpgmesignjob.h
    qgpgmesignkeyjob.h
    qgpgmetofupolicyjob.h
    qgpgmeverifydetachedjob.h
    qgpgmeverifyopaquejob.h
    qgpgmewkspublishjob.h
    quickjob.h
    refreshkeysjob.h
    signencryptjob.h
    signjob.h
    signkeyjob.h
    specialjob.h
    tofupolicyjob.h
    verifydetachedjob.h
    verifyopaquejob.h
    wkspublishjob.h
)

set(qgpgme_CAMELCASE_HEADERS
    AbstractImportJob
    AddUserIDJob
    ChangeExpiryJob
    ChangeOwnerTrustJob
    ChangePasswdJob
    CryptoConfig
    DataProvider
    DecryptJob
    DecryptVerifyJob
    DefaultKeyGenerationJob
    DeleteJob
    DN
    DownloadJob
    EncryptJob
    ExportJob
    GpgCardJob
    HierarchicalKeyListJob
    ImportFromKeyserverJob
    ImportJob
    Job
    KeyForMailboxJob
    KeyGenerationJob
    KeyListJob
    ListAllKeysJob
    MultiDeleteJob
    Protocol
    QuickJob
    RefreshKeysJob
    SignEncryptJob
    SignJob
    SpecialJob
    TofuPolicyJob
    VerifyDetachedJob
    VerifyOpaqueJob
    WKSPublishJob
)

set(qgpgme_MOC)
foreach(header ${qgpgme_HEADERS})
    get_filename_component(absolute_path ${header} ABSOLUTE)
    get_filename_component(file_name ${header} NAME_WLE)

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${file_name}.moc
        COMMAND ${QT_MOC_EXECUTABLE} ${absolute_path} -o ${CMAKE_CURRENT_BINARY_DIR}/${file_name}.moc
    )
    list(APPEND qgpgme_MOC "${CMAKE_CURRENT_BINARY_DIR}/${file_name}.moc")
endforeach()

foreach(header ${qgpgme_CAMELCASE_HEADERS})
    string(TOLOWER ${header} header_lc)
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/QGpgME/${header} "#include \"qgpgme/${header_lc}.h\"")
    list(APPEND qgpgme_HEADERS ${header_lc}.h)
endforeach()

add_definitions(-DBUILDING_QGPGME)

add_library(qgpgme ${qgpgme_MOC} ${qgpgme_SRCS})
set_target_properties(qgpgme PROPERTIES EXPORT_NAME QGpgme)
target_link_libraries(qgpgme PUBLIC gpgmepp ${GPGME_LIBRARIES} Qt5::Core)
target_include_directories(qgpgme
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${GPGME_INCLUDE_DIRS}>
    $<INSTALL_INTERFACE:${GPGME_INCLUDE_DIRS}/qgpgme>
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${GPGME_INCLUDE_DIRS}>
)

parse_lt(LIBQGPGME)
math(EXPR MAJOR "${LIBQGPGME_LT_CURRENT} - ${LIBQGPGME_LT_AGE}")
set_target_properties(qgpgme PROPERTIES
    VERSION "${MAJOR}.${LIBQGPGME_LT_AGE}.${LIBQGPGME_LT_REVISION}"
    SOVERSION "${MAJOR}"
)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/QGpgmeConfigVersion.cmake.in
               ${CMAKE_CURRENT_BINARY_DIR}/QGpgmeConfigVersion.cmake @ONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/qgpgme_version.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/qgpgme_version.h)

install(TARGETS qgpgme DESTINATION
        EXPORT QGpgme
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(EXPORT QGpgme
    FILE QGpgmeConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QGpgme
    )

install(FILES ${qgpgme_HEADERS}
              ${CMAKE_CURRENT_BINARY_DIR}/qgpgme_version.h
              ${CMAKE_CURRENT_SOURCE_DIR}/qgpgme_export.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qgpgme)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/QGpgME
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QGpgmeConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QGpgme
)
