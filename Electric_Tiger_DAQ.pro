#-------------------------------------------------
#
# Project created by QtCreator 2017-02-03T22:01:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Electric_Tiger_DAQ
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ConfigProcessors/config_processor.cpp \
    SocketCommunicators/Arduino/arduino.cpp \
    SocketCommunicators/NetworkAnalyzer/network_analyzer.cpp \
    SocketCommunicators/SignalGenerator/signal_generator.cpp \
    SocketCommunicators/StepperMotor/stepper_motor.cpp \
    SocketCommunicators/Switch/switch.cpp

HEADERS  += mainwindow.h \
    ConfigProcessors/config_processor.h \
    SocketCommunicators/Arduino/arduino.h \
    SocketCommunicators/NetworkAnalyzer/network_analyzer.h \
    SocketCommunicators/SignalGenerator/signal_generator.h \
    SocketCommunicators/StepperMotor/stepper_motor.h \
    SocketCommunicators/Switch/switch.h

FORMS    += mainwindow.ui
