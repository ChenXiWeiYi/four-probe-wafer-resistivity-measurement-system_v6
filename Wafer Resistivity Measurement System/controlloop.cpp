#include "widget.h"
#include <QDebug>

/**
 * @brief Widget::ControlLoop_Update 控制算法运算核心
 * 这个函数每次收到最新的电流值时就调用一次。
 * @param PV_Current 实际测到的当前电流(A)
 */
void Widget::ControlLoop_Update(double PV_Current)
{
    // 1. 计算当前误差
    double err = Controller_used.SP_Current - PV_Current;
    double output_voltage = 2.5;

    double RE = err/Controller_used.SP_Current*100;
 //   double RE = err*100/Controller_used.SP_Current;
    ui->Label_RE_Current->setText(QString::number(RE));
    AppendValueToFile(Controller_used.SP_Current,VALUE_RESISTANCE);
    AppendValueToFile(PV_Current,VALUE_RESISTANCE);
    AppendValueToFile(err,VALUE_Err);
    AppendValueToFile(RE,VALUE_RESISTANCE);
    AppendValueToFile(Controller_used.SP_Current,VALUE_SP_Current);
 //   if(RE < 0.005 && RE > -0.005){
 //       Controller_used.Last_last_Err = Controller_used.Last_Err;
 //       Controller_used.Last_Err = err;
 //       Timer_ContactMonitor->start(10); // 重新开始轮询
 //       return;
 //   }



    if (Param_used.ControlAlgo == ALGO_NORMAL_PID ||
        Param_used.ControlAlgo == ALGO_LAMBDA_PID)
    {

        // P项
        double P = Controller_used.Kp * (err - Controller_used.Last_Err);
        // I项 (如果有Ti参数)
        double Ki = Controller_used.Kp / Controller_used.Ti;
        double I = Ki * err;
        double Kd = Controller_used.Kp * Controller_used.Td;
        double D = Kd * (err + Controller_used.Last_last_Err - 2 * Controller_used.Last_Err);



        // 计算输出总电压 (PID)
 //       if(RE > 0.01 || RE < -0.01){
 //           output_voltage = Controller_used.Last_uk + P;
  //      }else{
   //         output_voltage = Controller_used.Last_uk + P + I;
  //      }
        output_voltage = Controller_used.Last_uk + P + I + D;

        AppendValueToFile(P+I+D,VALUE_delta_uk);
        AppendValueToFile(Controller_used.Last_uk,VALUE_Last_uk);
        AppendValueToFile(output_voltage,VALUE_uk);
        AppendValueToFile(err,VALUE_Err);


        Controller_used.Last_uk = output_voltage;

        // 更新上次误差
        Controller_used.Last_last_Err = Controller_used.Last_Err;
        Controller_used.Last_Err = err;
        qDebug()<<"控制";
        Command_SendCustomControlVoltage(static_cast<float>(output_voltage));
    }
    // ==============================================================
    // 算法3: 简易模型预测控制 (MPC / 无差拍)
    // ==============================================================
    else if (Param_used.ControlAlgo == ALGO_MPC)
    {
        // ====== 解析法模型预测控制 (Analytical MPC minimizing Cost Function) ======

        // 我们已知模型: I_next = a * I_current + b * U_now
        // 代价函数 J = (I_next - SP_Current)^2 + R_Weight * (U_now - U_last)^2
        // 令 dJ/dU = 0 求导，得到的完美理论公式如下：

        // 为了代码易读，提取变量
        double a = Controller_used.model_a;
        double b = Controller_used.model_b;
        double R = Controller_used.R_Weight;     // 平滑惩罚系数，比如 0.1 ~ 10.0
        double I_k = PV_Current;                 // 当前电流
        double I_ref = Controller_used.SP_Current; // 目标电流
        static double U_last = 0.0;              // 上一次的输出电压

        // 公式核心算式 (真·二次规划的解析解体现)：
        // U_now = [ b*(I_ref - a*I_k) + R*U_last ] / (b^2 + R)
        double U_predict = (b * (I_ref - a * I_k) + R * U_last) / (b * b + R);

        // 保存这次计算的电压，供下一拍参考
        U_last = U_predict;

        // 同理，加入一点点积分项消除建模误差带来的稳态偏置
        Controller_used.MPC_Err_Sum += err * 0.1;
        if(Controller_used.MPC_Err_Sum > 0.5) Controller_used.MPC_Err_Sum = 0.5;
        if(Controller_used.MPC_Err_Sum < -0.5) Controller_used.MPC_Err_Sum = -0.5;

        // 最终输出 = 最优预测值 + 模型补偿
        output_voltage = U_predict + Controller_used.MPC_Err_Sum;
    }

    // 2. 限幅并发送至单片机DAC

}
