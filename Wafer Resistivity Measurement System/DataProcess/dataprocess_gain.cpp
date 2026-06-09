#include "widget.h"

/**
 * @brief Widget::Return_DataGain 返回测量值应该除以的数
 * @param MeasureValue 啥测量值
 * @return 增益
 * @author 刘嘉诚
 * @date 2026.06.08
 */
double Widget::Return_DataGain(ValueType_TypeDef ValueType){
    if(ValueType == VALUE_CURRENT){
        switch(static_cast<CurrPos_TypeDef>(Param_used.CurrPos)){
        case(CURRENTPOSITION_auto):
            // 自动,没写,再说
            return 100000000000;
        case(CURRENTPOSITION_100mA):
            return 25;
        case(CURRENTPOSITION_25mA):
            return 100;
        case(CURRENTPOSITION_2P5mA):
            return 1000;
        case(CURRENTPOSITION_250uA):
            return 10000;
        case(CURRENTPOSITION_25uA):
            return 100000;
        case(CURRENTPOSITION_2P5uA):
            return 1000000;
        case(CURRENTPOSITION_250nA):
            return 1000000; // 也是1ohm,电压不一样
        default:
            Popup_Window("错误","没见过的电流增益");
            return 10000000000;
        }
    }else{
        switch(static_cast<VolRange_TypeDef>(Param_used.VolRange)){
        case(VOLTAGERANGE_auto):
            // 自动,没写,再说
            return 100000000;
        case(VOLTAGERANGE_300mV):
            return 8;
        case(VOLTAGERANGE_30mV):
            return 8*16;
        case(VOLTAGERANGE_3mV):
            return 8*16*4;
        default:
            Popup_Window("错误","没见过的电压增益");
            return 100000000;
        }
    }
    Popup_Window("错误","都蹦这个错误了,别写代码了——刘嘉诚");
    return 100000;
}
