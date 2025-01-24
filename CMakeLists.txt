cmake_minimum_required(VERSION 3.19)
project(crypto_exchange LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS
    Core
    Widgets
    Network
    Sql
    Multimedia
)

find_package(OpenCV REQUIRED)

qt_standard_project_setup()

set(SOURCES
    main.cpp
    mainwindow.cpp
    user.cpp
    wallet.cpp
    authmanager.cpp
    apimanager.cpp
    transaction.cpp
    dashboardwindow.cpp
    registrationwindow.cpp
    faceauthmanager.cpp  # اضافه شد
)

set(HEADERS
    mainwindow.h
    user.h
    wallet.h
    authmanager.h
    apimanager.h
    transaction.h
    dashboardwindow.h
    registrationwindow.h
    faceauthmanager.h    # اضافه شد
)

set(UI_FILES
    mainwindow.ui
    # loginwindow.ui و dashboardwindow.ui را فقط اگر وجود دارند اضافه کنید
)

qt_add_executable(crypto_exchange
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
)

target_link_libraries(crypto_exchange PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
    Qt6::Sql
    Qt6::Multimedia
    ${OpenCV_LIBS}
)

include_directories(${OpenCV_INCLUDE_DIRS})

include(GNUInstallDirs)
install(TARGETS crypto_exchange
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET crypto_exchange
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
