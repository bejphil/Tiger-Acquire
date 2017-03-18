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

DEFINES += "DEBUG"

CONFIG(debug, debug|release) {
    DEFINES += "DEBUG"
} else {
    DEFINES += "NDEBUG"
}

INCLUDEPATH +=../ATS9462

LIBS += -L/usr/local/lib \
        -L/usr/lib \
        -lboost_iostreams \
        -lboost_system \
        -lboost_filesystem \
        -lboost_thread

INCLUDEPATH +=/usr/local/cuda/include
LIBS +=-L "/usr/local/cuda/lib64" -lOpenCL

INCLUDEPATH +=/usr/local/include
LIBS +=-L/usr/local/lib64 -lclFFT

LIBS +=-lfftw3f_threads -lfftw3f -lm

# AlazarTech API
LIBS += -lATSApi -L/usr/local/AlazarTech/lib

QMAKE_CXXFLAGS+= -fopenmp
#QMAKE_CXXFLAGS+= -O3
QMAKE_LFLAGS +=  -fopenmp

SOURCES += main.cpp\
        Windows/mainwindow.cpp \
    #ConfigProcessor/configprocessor.cpp \
    SocketCommunicators/Arduino/arduino.cpp \
    SocketCommunicators/NetworkAnalyzer/network_analyzer.cpp \
    SocketCommunicators/SignalGenerator/signal_generator.cpp \
    SocketCommunicators/StepperMotor/stepper_motor.cpp \
    SocketCommunicators/Switch/switch.cpp \
    SocketCommunicators/SocketComm/test_socket_comm.cpp \
    SocketCommunicators/SocketComm/q_socket_comm.cpp \
    SocketCommunicators/SocketComm/socketcomm.cpp \
    Panels/GraphicObjects/chartscalecontrols.cpp \
    Panels/GraphicObjects/frequencycontrols.cpp \
    Panels/GraphicObjects/rightclickmenu.cpp \
    Panels/SpectrumAnalyzer/spectrumanalyzer.cpp \
    Panels/SpectrumAnalyzer/spectrumanalyzer.tpp \
    SocketCommunicators/AbstractSocketCommunicator/abstractsocketcommunictor.cpp \
    ConfigProcessor/configprocessor.cpp \
    Program/ProgramCore/programcore.cpp \
    ConfigProcessor/testconfigprocessor.cpp \
    DataTransformatoions/datatransformations.cpp \
    Panels/InstrumentView/instrumentview.cpp \
    Program/ProgramFrame/programframe.cpp \
    ModeTracker/modetrack.cpp \
    Generics/generics.cpp \
    ModeCharacterization/modecharacterization.cpp \
    Program/Program/program.cpp \
    DataSaver/FlatFileSaver/flatfilesaver.cpp \
    ModeTracker/mode_track_failure.cpp \
    SocketCommunicators/NetworkAnalyzer/test_network_analyzer.cpp \
    SocketCommunicators/SocketComm/qsocketintermitten.cpp \
    SocketCommunicators/AbstractSocketCommunicator/abstractintermittensocket.cpp \
    Algorithm/algorithm.cpp \
    Panels/SpectrumAnalyzer/test_spectrum_analyzer.cpp \
    Panels/InstrumentView/instrumentview.tpp \
    Panels/InstrumentView/test_instrumentview.cpp \
    Panels/testpanels.cpp

HEADERS  += Windows/mainwindow.h \
   # ConfigProcessor/configprocessor.h \
    SocketCommunicators/Arduino/arduino.h \
    SocketCommunicators/NetworkAnalyzer/network_analyzer.h \
    SocketCommunicators/SignalGenerator/signal_generator.h \
    SocketCommunicators/StepperMotor/stepper_motor.h \
    SocketCommunicators/Switch/switch.h \
    SocketCommunicators/SocketComm/q_socket_comm.h \
    SocketCommunicators/SocketComm/socketcomm.h \
    Panels/GraphicObjects/chartscalecontrols.h \
    Panels/GraphicObjects/frequencycontrols.h \
    Panels/GraphicObjects/rightclickmenu.h \
    Panels/SpectrumAnalyzer/spectrumanalyzer.h \
    SocketCommunicators/AbstractSocketCommunicator/abstractsocketcommunictor.h \
    ConfigProcessor/configprocessor.h \
    Program/ProgramCore/programcore.h \
    SocketCommunicators/socketcommunicators.h \
    ConfigProcessor/experiment_parameters.h \
    ConfigProcessor/testconfigprocessor.h \
    DataTransformatoions/datatransformations.h \
    Panels/InstrumentView/instrumentview.h \
    Program/ProgramFrame/programframe.h \
    ModeTracker/modetrack.h \
    Generics/generics.h \
    ModeCharacterization/modecharacterization.h \
    Program/Program/program.h \
    DataSaver/FlatFileSaver/flatfilesaver.h \
    ModeTracker/mode_track_failure.h \
    Program/ProgramCore/daq_failure.h \
    SocketCommunicators/Arduino/test_arduino.h \
    SocketCommunicators/NetworkAnalyzer/test_network_analyzer.h \
    SocketCommunicators/SignalGenerator/test_signal_generator.h \
    SocketCommunicators/SocketComm/qsocketintermitten.h \
    SocketCommunicators/AbstractSocketCommunicator/abstractintermittensocket.h \
    SocketCommunicators/StepperMotor/test_stepper_motor.h \
    SocketCommunicators/Switch/test_switch.h \
    SocketCommunicators/test_socketcommunicators.h \
    Algorithm/algorithm.h \
    ModeCharacterization/test_modecharacterization.h \
    Panels/SpectrumAnalyzer/test_spectrum_analyzer.h \
    Panels/InstrumentView/test_instrumentview.h \
    Panels/testpanels.h

FORMS    += Windows/mainwindow.ui \
    Panels/GraphicObjects/chartscalecontrols.ui \
    Panels/GraphicObjects/frequencycontrols.ui
