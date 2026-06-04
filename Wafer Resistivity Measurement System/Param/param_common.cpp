#include "widget.h"
#include "ui_widget.h"
#include "global_struct_define.h"
#include <QDebug>
#include <QDataStream>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QString>



/**
 * @brief Widget::Param_Setting_Write 修改参数文件
 * @param ParamName 参数名称
 * @param ParamValue 参数值
 * @return 是否成功
 * @author 刘嘉诚
 * @date 2026.02.14
 */
bool Widget::Param_Setting_Write(ParamName_TypeDef ParamName, const QString &ParamValue)
{
    QString Dir_App = QCoreApplication::applicationDirPath();
    QString FilePath = Dir_App + "/Param.Setting";
    QFile file(FilePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        Popup_Window("错误","参数文件打开失败!");
        return false;
    }
    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()){
        lines.append(in.readLine());
    }
    file.close();
    QString ParamName_QS = Map_ParamName.value(ParamName);
    if (ParamName_QS.isEmpty()){
        Popup_Window("严重错误", "参数映射表缺失，请检查代码！");
        return false;
    }
    for(int i = 0; i < lines.size(); ++i){
        if(lines[i].startsWith(ParamName_QS)){
            lines[i] = ParamName_QS + ParamValue + ";";
            break;
        }
    }
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        Popup_Window("错误","参数文件打开失败(无法写入)!");
        return false;
    }
    QTextStream out(&file);
    for (const QString &line : lines){
        out << line << "\n";
    }
    file.close();
    return true;
}


bool Widget::Param_Setting_Write(ParamName_TypeDef ParamName, int ParamValue)
{
    return Param_Setting_Write(ParamName, QString::number(ParamValue));
}

bool Widget::Param_Setting_Write(ParamName_TypeDef ParamName, float ParamValue)
{
    return Param_Setting_Write(ParamName, QString::number(ParamValue));
}

bool Widget::Param_Setting_Write(ParamName_TypeDef ParamName, double ParamValue)
{
    return Param_Setting_Write(ParamName, QString::number(ParamValue));
}

/**
 * @brief Widget::Param_Setting_Read 读取参数文件
 * @param ParamName 参数名
 * @return 参数值
 * @author 刘嘉诚
 * @date 2026.02.14
 */
QVariant Widget::Param_Setting_Read(ParamName_TypeDef ParamName)
{
    QString Dir_App = QCoreApplication::applicationDirPath();
    QString FilePath = Dir_App + "/Param.Setting";
    QFile file(FilePath);
    QString ParamValue_QS;
    QVariant ParamValue_QV;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        Popup_Window("错误","读取参数失败");
        return QVariant();
    }
    QString ParamName_QS = Map_ParamName.value(ParamName);
    if (ParamName_QS.isEmpty()){
        Popup_Window("严重错误", "参数映射表缺失，请检查代码！");
        return QVariant();
    }
    QTextStream in(&file);
    while(!in.atEnd()){
        QString line = in.readLine();
        if (line.startsWith(ParamName_QS)){
            QStringList parts = line.split(":");
            if (parts.size() > 1) {
                ParamValue_QS = parts[1].split(";").first().trimmed();
                ParamValue_QV = ParamValue_QS;
            }
            break;
        }
    }
    file.close();
    return ParamValue_QV;
}

/**
 * @brief Widget::VectorToString QVector<float>转QSTring
 * @param vec 输入的QVector
 * @return 结尾带','的QString
 * @author 刘嘉诚
 * @date 2026.02.17
 */
QString Widget::VectorToString(const QVector<float>& vec){
    QStringList list;
    for(float v : vec) {
        list << QString::number(v, 'f', 6);
    }
    return list.join(",");
}


/**
 * @brief Widget::Return_Param_used 返回正在使用的参数值
 * @param ParamName 参数名
 * @return 参数值
 * @author 刘嘉诚
 * @date 2026.02.14
 */
QVariant Widget::Return_Param_used(ParamName_TypeDef ParamName)
{
    switch(ParamName){
    case NAME_Temperature:          return QVariant(Param_used.Temperature);
    case NAME_SampleThickness:      return QVariant(Param_used.SampleThickness);
    case NAME_SampleDiameter:       return QVariant(Param_used.SampleDiameter);
    case NAME_ProbeSpacing:         return QVariant(Param_used.ProbeSpacing);
    case NAME_FspCorrectionFactor:  return QVariant(Param_used.FspCorrectionFactor);
    case NAME_a:                    return QVariant(Param_used.a);
    case NAME_b:                    return QVariant(Param_used.b);
    case NAME_CurrErrorBound:       return QVariant(Param_used.CurrErrorBound);
    case NAME_CurrPos:              return QVariant(Param_used.CurrPos);
    case NAME_VolRange:             return QVariant(Param_used.VolRange);
    default: return QVariant();
    }
}

/**
 * @brief Widget::Modify_Param_used 修改正在使用的参数值
 * @param ParamName 参数名称
 * @param value 参数值
 * @author 刘嘉诚
 * @date 2026.02.14
 */
void Widget::Modify_Param_used(ParamName_TypeDef ParamName, double value)
{
    switch(ParamName){
    case NAME_Temperature:          Param_used.Temperature = value; break;
    case NAME_SampleThickness:      Param_used.SampleThickness = value; break;
    case NAME_SampleDiameter:       Param_used.SampleDiameter = value; break;
    case NAME_ProbeSpacing:         Param_used.ProbeSpacing = value; break;
    case NAME_FspCorrectionFactor:  Param_used.FspCorrectionFactor = value; break;
    case NAME_a:                    Param_used.a = value; break;
    case NAME_b:                    Param_used.b = value; break;
    case NAME_CurrErrorBound:       Param_used.CurrErrorBound = value; break;
    case NAME_CurrPos:              Param_used.CurrPos = static_cast<int>(value); break;
    case NAME_VolRange:             Param_used.VolRange = static_cast<int>(value); break;
    }
}

void Widget::Modify_Param_used(ParamName_TypeDef ParamName, int value)
{
    Modify_Param_used(ParamName, static_cast<double>(value));
}
