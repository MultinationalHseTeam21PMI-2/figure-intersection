set(TARGET gui)

set(Sources mainwindow.cpp mainwindow.h mainwindow.ui)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_library(${TARGET} STATIC ${Sources})
target_link_libraries(${TARGET} PRIVATE Qt6::Core Qt6::Widgets)