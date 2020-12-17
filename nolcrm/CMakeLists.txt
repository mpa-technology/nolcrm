cmake_minimum_required(VERSION 3.5)
project(nolcrm CXX)

set(CMAKE_CXX_STANDARD 17)
set_target_properties(${TARGET} PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS ON
    )


set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 2)
set(PROJECT_VERSION_PATCH 0)
set(NOLCRM_BUILD_TYPE ${CMAKE_BUILD_TYPE})
set(NOLCRM_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(NOLCRM_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(NOLCRM_VERSION_PATCH ${PROJECT_VERSION_PATCH})


set(SOURCES
    "main.cpp"
    "MainWindow/MainWindow.cpp"
    "DataBase/DataBase.cpp"
    "WidgetAddProduct/WidgetAddProduct.cpp"
    "WidgetAddOrder/WidgetAddOrder.cpp"
    "WidgetShowOrder/WidgetShowOrder.cpp"
    "DataBase/TableProducts.cpp"
    "DataBase/TableOrders.cpp"
    "WidgetProduct/WidgetProduct.cpp"
    "WidgetShowProducts/WidgetShowProducts.cpp"
    "WidgetStorage/WidgetStorage.cpp"
    "DataBase/TableStorage.cpp"
    "Settings/Settings.cpp"
    "DataBase/TableStorageImport.cpp"
    "WidgetNewImport/WidgetNewImport.cpp"
    "WidgetEditProduct/WidgetEditProduct.cpp"
    "LoginWidget/LoginWidget.cpp"
    "ShowImportWidget/ShowImportWidget.cpp"
    "ShowExportWidget/ShowExportWidget.cpp"
    "WidgetNewExport/WidgetNewExport.cpp"
    "Servers/UpdateService.cpp"
    "Servers/ProgramService.cpp"
    "Servers/ProductService.cpp"
    "Servers/ImportService.cpp"
    "Servers/ExportService.cpp"
    "Servers/GlobalService.cpp"
    "DataBase/TableStorageExport.cpp"
    "Tool.cpp"
    )

set(HEADER
    "MainWindow/MainWindow.hpp"
    "WidgetAddProduct/WidgetAddProduct.hpp"
    "DataBase/DataBase.hpp"
    "WidgetAddOrder/WidgetAddOrder.hpp"
    "WidgetShowOrder/WidgetShowOrder.hpp"
    "WidgetProduct/WidgetProduct.hpp"
    "WidgetShowProducts/WidgetShowProducts.hpp"
    "DataBase/TableProducts.hpp"
    "DataBase/TableOrders.hpp"
    "WidgetStorage/WidgetStorage.hpp"
    "DataBase/TableStorage.hpp"
    "Settings/Settings.hpp"
    "DataBase/TableStorageImport.hpp"
    "WidgetNewImport/WidgetNewImport.hpp"
    "WidgetEditProduct/WidgetEditProduct.hpp"
    "LoginWidget/LoginWidget.hpp"
    "ShowImportWidget/ShowImportWidget.hpp"
    "ShowExportWidget/ShowExportWidget.hpp"
    "WidgetNewExport/WidgetNewExport.hpp"
    "main.hpp"
    "Servers/UpdateService.hpp"
    "Servers/ProgramService.hpp"
    "Servers/ProductService.hpp"
    "Servers/ImportService.hpp"
    "Servers/ExportService.hpp"
    "Servers/GlobalService.hpp"
    "DataBase/TableStorageExport.hpp"
    "Tool.hpp"
    )

set(UI
    "MainWindow/MainWindow.ui"
    "WidgetAddProduct/WidgetAddProduct.ui"
    "WidgetAddOrder/WidgetAddOrder.ui"
    "WidgetShowOrder/WidgetShowOrder.ui"
    "WidgetProduct/WidgetProduct.ui"
    "WidgetShowProducts/WidgetShowProducts.ui"
    "WidgetStorage/WidgetStorage.ui"
    "WidgetNewImport/WidgetNewImport.ui"
    "WidgetEditProduct/WidgetEditProduct.ui"
    "LoginWidget/LoginWidget.ui"
    "ShowImportWidget/ShowImportWidget.ui"
    "ShowExportWidget/ShowExportWidget.ui"
    "WidgetNewExport/WidgetNewExport.ui"
    )



configure_file("Servers/cmake_m.in" "Servers/cmake_m.hpp")


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Sql PrintSupport)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADER} ${UI})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Sql Qt5::PrintSupport pthread)
