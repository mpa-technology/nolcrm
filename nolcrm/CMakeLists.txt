cmake_minimum_required(VERSION 3.5)
project(nolcrm CXX)

set(CMAKE_CXX_STANDARD 17)
set_target_properties(${TARGET} PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS ON
    )


set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 3)
set(PROJECT_VERSION_PATCH 0)
set(NOLCRM_BUILD_TYPE ${CMAKE_BUILD_TYPE})
set(NOLCRM_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(NOLCRM_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(NOLCRM_VERSION_PATCH ${PROJECT_VERSION_PATCH})

configure_file(${PROJECT_SOURCE_DIR}/Service/cmake_m.in ${PROJECT_SOURCE_DIR}/Service/cmake_m.hpp)

set(SOURCES
    "main.cpp"
    "MainWindow/MainWindow.cpp"
    "DataBase/DataBase.cpp"
    "WidgetAddProduct/WidgetAddProduct.cpp"
    "WidgetAddOrder/WidgetAddOrder.cpp"
    "WidgetShowOrder/WidgetShowOrder.cpp"
    "DataBase/TableProducts.cpp"
    "DataBase/TableOrders.cpp"
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
    "Service/GlobalEmitService.cpp"
    "Service/ProgramService.cpp"
    "Service/ProductService.cpp"
    "Service/ImportService.cpp"
    "Service/ExportService.cpp"
    "Service/GlobalService.cpp"
    "DataBase/TableStorageExport.cpp"
    "Utility/Tool.cpp"
    "Service/OrderService.cpp"
    "ReportWidget/ReportWidget.cpp"
    )

set(HEADER
    "MainWindow/MainWindow.hpp"
    "WidgetAddProduct/WidgetAddProduct.hpp"
    "DataBase/DataBase.hpp"
    "WidgetAddOrder/WidgetAddOrder.hpp"
    "WidgetShowOrder/WidgetShowOrder.hpp"
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
    "Service/GlobalEmitService.hpp"
    "Service/ProgramService.hpp"
    "Service/ProductService.hpp"
    "Service/ImportService.hpp"
    "Service/ExportService.hpp"
    "Service/GlobalService.hpp"
    "DataBase/TableStorageExport.hpp"
    "Utility/Tool.hpp"
    "Service/OrderService.hpp"
    "ReportWidget/ReportWidget.hpp"
    )

set(UI
    "MainWindow/MainWindow.ui"
    "WidgetAddProduct/WidgetAddProduct.ui"
    "WidgetAddOrder/WidgetAddOrder.ui"
    "WidgetShowOrder/WidgetShowOrder.ui"
    "WidgetShowProducts/WidgetShowProducts.ui"
    "WidgetStorage/WidgetStorage.ui"
    "WidgetNewImport/WidgetNewImport.ui"
    "WidgetEditProduct/WidgetEditProduct.ui"
    "LoginWidget/LoginWidget.ui"
    "ShowImportWidget/ShowImportWidget.ui"
    "ShowExportWidget/ShowExportWidget.ui"
    "WidgetNewExport/WidgetNewExport.ui"
    "ReportWidget/ReportWidget.ui"
    )






set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql  Test PrintSupport)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADER} ${UI})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Widgets Qt6::Sql Qt6::PrintSupport  Qt6::Test pthread)
