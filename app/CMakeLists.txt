option(OURPROJECT_ENABLE_QT "Build Qt GUI app when available" ON)

set(OURPROJECT_HAVE_QT OFF)
set(OURPROJECT_QT_LIBS "")

if (OURPROJECT_ENABLE_QT)
    find_package(Qt6 COMPONENTS Widgets Charts QUIET)
    if (Qt6_FOUND)
        set(OURPROJECT_HAVE_QT ON)
        set(OURPROJECT_QT_LIBS Qt6::Widgets Qt6::Charts)
    else()
        find_package(Qt5 COMPONENTS Widgets Charts QUIET)
        if (Qt5_FOUND)
            set(OURPROJECT_HAVE_QT ON)
            set(OURPROJECT_QT_LIBS Qt5::Widgets Qt5::Charts)
        endif()
    endif()
endif()


add_library(app_support_cli
        ${CMAKE_SOURCE_DIR}/src/app/ChartRenderer.cpp)

target_include_directories(app_support_cli
        PUBLIC
        ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(app_support_cli
        PUBLIC
        core
        indicators
        analysis)

add_executable(OurProject_cli
        main_cli.cpp)

target_link_libraries(OurProject_cli
        PRIVATE
        app_support_cli)


if (OURPROJECT_HAVE_QT)
    set(CMAKE_AUTOMOC ON)

    add_library(app_support_gui
            ${CMAKE_SOURCE_DIR}/src/app/MainWindow.cpp
            ${CMAKE_SOURCE_DIR}/src/app/CandleChartView.cpp
            ${CMAKE_SOURCE_DIR}/src/app/AnalysisController.cpp
            ${CMAKE_SOURCE_DIR}/include/app/MainWindow.hpp
            ${CMAKE_SOURCE_DIR}/include/app/CandleChartView.hpp
            ${CMAKE_SOURCE_DIR}/include/app/AnalysisController.hpp)

    target_include_directories(app_support_gui
            PUBLIC
            ${CMAKE_SOURCE_DIR}/include)

    target_link_libraries(app_support_gui
            PUBLIC
            core
            indicators
            analysis
            ${OURPROJECT_QT_LIBS})

    add_executable(OurProject
            main.cpp)

    target_link_libraries(OurProject
            PRIVATE
            app_support_gui)

    message(STATUS "Qt found: building both GUI (OurProject) and CLI (OurProject_cli)")
else()
    message(WARNING "Qt (Widgets+Charts) not found: building CLI app only.")
endif()
