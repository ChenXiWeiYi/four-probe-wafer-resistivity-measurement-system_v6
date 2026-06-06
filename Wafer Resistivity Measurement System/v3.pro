QT += core gui widgets serialport

CONFIG += c++11

TARGET = MyQtProject
TEMPLATE = app

SOURCES += main.cpp \
           widget.cpp \
    widget_slots.cpp \
    widget_common.cpp \
    ctrlc.cpp \
    Measure/measure_warning.cpp \
    Param/param_slots_channel.cpp \
    maps_correctionfactor.cpp \
    maps_global.cpp \
    Measure/measure_paramcheck.cpp \
    Measure/measure_complete.cpp \
    DataProcess/dataprocess_gain.cpp \
    DataProcess/dataprocess_save.cpp \
    DataProcess/dateprocess_process.cpp \
    Param/param_correction.cpp \
    Measure/measure_display.cpp \
    Serial/serial_echoerror.cpp \
    widget_ui_design.cpp \
    Measure/measure_timer.cpp \
    DataProcess/dateprocess_adc.cpp \
    controlloop.cpp \
    Serial/Answer/answer_read_current_only.cpp \
    Serial/Answer/answer_modify_control_voltage.cpp \
    Menu/menu_init.cpp \
    Param/Slots/slot_cin_kp.cpp \
    Param/Slots/slot_cin_ti.cpp \
    Param/Slots/slot_cin_td.cpp
# -----   测量 -----
SOURCES += \
    Measure/measure_start.cpp
# ----- 修正系数 -----
SOURCES +=
# ----- 串口 -----
SOURCES += \
    Serial/serial_readserialdata.cpp \
    Serial/serial_calculate_crc16.cpp \
    Serial/serial_frame.cpp \
    Serial/serial_send_controlbyte.cpp \
    Serial/serial_answer.cpp \
    Serial/serial_command.cpp
# ----- 参数 -----
SOURCES += \
    Param/param_common.cpp \
    Param/param_init.cpp \
    Param/param_slots.cpp

HEADERS += widget.h \
    global_maps.h \
    global_struct_define.h \
    global_enum_define.h

FORMS += \
    widget.ui

RESOURCES +=

DISTFILES += \
    Measure/start_measurement
