#-------------------------------------------------
#
# Project created by QtCreator 2017-02-03T22:01:47
#
#-------------------------------------------------

QT       += core gui network charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Electric_Tiger_DAQ
TEMPLATE = app

CONFIG += c++11

CONFIG(debug, debug|release) {
    DEFINES += "DEBUG"
} else {
    DEFINES += "NDEBUG"
}

INCLUDEPATH += ../../../include
LIBS += -L$$OUT_PWD/../../../lib

LIBS += -L/usr/local/lib -L/usr/lib -lboost_iostreams -lboost_system -lboost_filesystem -lboost_thread

INCLUDEPATH +=-I "/usr/local/cuda/include"
LIBS +=-L "/usr/local/cuda/lib64" -lOpenCL

INCLUDEPATH +=-I/usr/local/include
LIBS +=-L/usr/local/lib64 -lclFFT

LIBS +=-lfftw3_threads -lfftw3 -lm

QMAKE_CXXFLAGS+= -fopenmp
#QMAKE_CXXFLAGS+= -O3
QMAKE_LFLAGS +=  -fopenmp

SOURCES += main.cpp\
        mainwindow.cpp \
    ConfigProcessors/config_processor.cpp \
    SocketCommunicators/Arduino/arduino.cpp \
    SocketCommunicators/NetworkAnalyzer/network_analyzer.cpp \
    SocketCommunicators/SignalGenerator/signal_generator.cpp \
    SocketCommunicators/StepperMotor/stepper_motor.cpp \
    SocketCommunicators/Switch/switch.cpp \
    SocketCommunicators/SocketComm/test_socket_comm.cpp \
    SocketCommunicators/SocketComm/q_socket_comm.cpp \
    SocketCommunicators/SocketComm/socketcomm.cpp \
    SpectrumAnalyzer/GraphicObjects/chartscalecontrols.cpp \
    SpectrumAnalyzer/GraphicObjects/frequencycontrols.cpp \
    SpectrumAnalyzer/GraphicObjects/rightclickmenu.cpp \
    SpectrumAnalyzer/spectrumanalyzer.cpp \
    SpectrumAnalyzer/spectrumanalyzer.tpp \
    SocketCommunicators/AbstractSocketCommunicator/abstractsocketcommunictor.cpp \
    ConfigProcessor/configprocessor.cpp \
    Program/Program/program.cpp \
    Program/ProgramCore/programcore.cpp

HEADERS  += mainwindow.h \
    ConfigProcessors/config_processor.h \
    SocketCommunicators/Arduino/arduino.h \
    SocketCommunicators/NetworkAnalyzer/network_analyzer.h \
    SocketCommunicators/SignalGenerator/signal_generator.h \
    SocketCommunicators/StepperMotor/stepper_motor.h \
    SocketCommunicators/Switch/switch.h \
    SocketCommunicators/SocketComm/q_socket_comm.h \
    SocketCommunicators/SocketComm/socketcomm.h \
    SpectrumAnalyzer/GraphicObjects/chartscalecontrols.h \
    SpectrumAnalyzer/GraphicObjects/frequencycontrols.h \
    SpectrumAnalyzer/GraphicObjects/rightclickmenu.h \
    SpectrumAnalyzer/spectrumanalyzer.h \
    SocketCommunicators/AbstractSocketCommunicator/abstractsocketcommunictor.h \
    ConfigProcessor/configprocessor.h \
    Program/Program/program.h \
    Program/ProgramCore/programcore.h

FORMS    += mainwindow.ui \
    SpectrumAnalyzer/GraphicObjects/chartscalecontrols.ui \
    SpectrumAnalyzer/GraphicObjects/frequencycontrols.ui
