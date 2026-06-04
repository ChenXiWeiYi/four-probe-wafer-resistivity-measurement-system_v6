#include "widget.h"
#include "ui_widget.h"

/**
 * @brief Widget::Measure_CheckParam 检查参数是否合理
 * 只检查现在能检查的
 * @return 参数检查结果
 * @author 刘嘉诚
 * @date 2026.02.17
 */
bool Widget::Measure_CheckParam(void){
    Param_used.WS = Param_used.SampleThickness / Param_used.ProbeSpacing;
    Param_used.SD = Param_used.ProbeSpacing / Param_used.SampleDiameter;

    if(Param_used.WS > 4.0){
        Popup_Window("错误","样品厚度与平均探针间距之比大于4");
        return false;
    }
    if(Param_used.SD < 0){
        Popup_Window("错误","平均探针间距与样品直径之比小于0");
        return false;
    }
    if(Param_used.SD > 0.1){
        Popup_Window("错误","平均探针间距与样品直径之比大于0.1");
        return false;
    }
    if(Param_used.Temperature < 18){
        Popup_Window("错误","温度小于18摄氏度");
        return false;
    }
    if(Param_used.Temperature > 28){
        Popup_Window("错误","温度大于28摄氏度");
        return false;
    }
    return true;
}

