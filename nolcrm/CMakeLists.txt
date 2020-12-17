cmake_minimum_required(VERSION 3.5)
project(nolcrm CXX)

set(CMAKE_CXX_STANDARD 17)
set_target_properties(${TARGET} PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS ON
            )

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
    "DataBase/Service.cpp"
    "Settings/Settings.cpp"
    "DataBase/TableStorageImport.cpp"
    "WidgetNewImport/WidgetNewImport.cpp"
    "WidgetEditProduct/WidgetEditProduct.cpp"
    "LoginWidget/LoginWidget.cpp"
    "ShowImportWidget/ShowImportWidget.cpp"
    "ShowExportWidget/ShowExportWidget.cpp"
    "WidgetNewExport/WidgetNewExport.cpp"
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
    "DataBase/Service.hpp"
    "Settings/Settings.hpp"
    "DataBase/TableStorageImport.hpp"
    "WidgetNewImport/WidgetNewImport.hpp"
    "WidgetEditProduct/WidgetEditProduct.hpp"
    "LoginWidget/LoginWidget.hpp"
    "ShowImportWidget/ShowImportWidget.hpp"
    "ShowExportWidget/ShowExportWidget.hpp"
    "WidgetNewExport/WidgetNewExport.hpp"
    "main.hpp"
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


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Sql PrintSupport)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADER} ${UI})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Sql Qt5::PrintSupport pthread)
