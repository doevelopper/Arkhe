qt5_wrap_ui( UI_HEADERS 
    arkhe/mainwindow.ui 
)


# qt5_add_resources( QRCS 
    # ${PROJECT_SOURCE_DIR}/src/main/resources/Qtrcs/resources.qrc 
# )

QT5_WRAP_CPP(MOC_SRCS
    arkhe/mainwindow.cpp 
)

set(JsonSrcs
                # arkhe/core/json/Array.cpp
                # arkhe/core/json/AtomicInt.cpp
                # arkhe/core/json/Base.cpp
                # arkhe/core/json/Data.cpp
                # arkhe/core/json/Entry.cpp
                # arkhe/core/json/Header.cpp
                # arkhe/core/json/Json.cpp
                # arkhe/core/json/JsonArray.cpp
                # arkhe/core/json/JsonDocument.cpp
                # arkhe/core/json/JsonObject.cpp
                # arkhe/core/json/JsonParseError.cpp
                # arkhe/core/json/JsonValue.cpp
                # arkhe/core/json/JsonValuePtr.cpp
                # arkhe/core/json/JsonValueRef.cpp
                # arkhe/core/json/JsonValueRefPtr.cpp
                # arkhe/core/json/LittleEndianBitfield.cpp
                # arkhe/core/json/LittleEndianSignedBitfield.cpp
                # arkhe/core/logger/LoggingCategory.cpp 
                # arkhe/core/json/Object.cpp
                # arkhe/core/json/Parser.cpp
                # arkhe/core/json/SharedString.cpp
                # arkhe/core/json/String.cpp
                # arkhe/core/json/Value.cpp
)

add_executable( ${PROJECT_NAME} 
                arkhe/main.cpp 
                arkhe/mainwindow.cpp 
                ${MOC_SRCS} 
                ${UI_HEADERS} 
                ${QRCS} 
)

target_link_libraries( ${PROJECT_NAME} Qt5::Widgets )