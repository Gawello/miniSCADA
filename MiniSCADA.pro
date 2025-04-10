QT       += core gui network
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ChartEditorDialog.cpp \
    ChartWidget.cpp \
    ClientWindow.cpp \
    DataField.cpp \
    InfoPanel.cpp \
    NumericField.cpp \
    SensorChart.cpp \
    SensorSelectionDialog.cpp \
    SettingsDialog.cpp \
    TcpClient.cpp \
    TextField.cpp \
    main.cpp

HEADERS += \
    ChartEditorDialog.h \
    ChartWidget.h \
    ClientWindow.h \
    DataField.h \
    InfoPanel.h \
    NumericField.h \
    SensorChart.h \
    SensorSelectionDialog.h \
    SettingsDialog.h \
    TcpClient.h \
    TextField.h

TRANSLATIONS += \
    MiniSCADA_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
