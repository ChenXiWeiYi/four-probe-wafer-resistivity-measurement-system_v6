#include "widget.h"
#include "ui_widget.h"
#include "global_struct_define.h"
#include <QCoreApplication>
#include <QDebug>
#include <QDataStream>
#include <QDir>
#include <QMessageBox>
#include <QFile>
#include <QSettings>
#include <QTextStream>
#include <QMap>
#include <QString>

namespace {
struct ParamDefaultItem
{
    ParamName_TypeDef name;
    const char *value;
};

static const ParamDefaultItem kDefaultParamItems[] = {
    { NAME_SemiType,            "0" },
    { NAME_Temperature,         "18" },
    { NAME_SampleThickness,     "0.551" },
    { NAME_SampleDiameter,      "150" },
    { NAME_ProbeSpacing,        "1.59" },
    { NAME_FspCorrectionFactor, "1.008" },
    { NAME_a,                   "5" },
    { NAME_b,                   "1" },
    { NAME_CurrErrorBound,      "10" },
    { NAME_ControlVoltages,     "0.000000,2.502300,2.498200,2.496600,2.496370,2.496340,2.496300,0.244000" },
    { NAME_PID_Kp,              "750.000000,750.000000,750.000000,750.000000,750.000000,750.000000,750.000000" },
    { NAME_PID_Ti,              "20.000000,20.000000,20.000000,20.000000,20.000000,20.000000,20.000000" },
    { NAME_PID_Td,              "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000" },
    { NAME_PIDControlEnabled,   "0" },
    { NAME_CurrPos,             "3" },
    { NAME_VolRange,            "2" },
    { NAME_MeasureMode,         "0" }
};

/**
 * @brief ParamSettingKey
 * @author 刘嘉诚
 * @date 2026.06.09
 */
QString ParamSettingKey(ParamName_TypeDef ParamName)
{
    switch(ParamName){
    case NAME_SemiType:            return "Sample/SemiType";
    case NAME_Temperature:         return "Sample/Temperature";
    case NAME_SampleThickness:     return "Sample/SampleThickness";
    case NAME_SampleDiameter:      return "Sample/SampleDiameter";
    case NAME_ProbeSpacing:        return "Sample/ProbeSpacing";
    case NAME_FspCorrectionFactor: return "Sample/FspCorrectionFactor";
    case NAME_a:                   return "Sample/a";
    case NAME_b:                   return "Sample/b";
    case NAME_CurrPos:             return "Range/CurrentPosition";
    case NAME_VolRange:            return "Range/VoltageRange";
    case NAME_MeasureMode:         return "Range/MeasureMode";
    case NAME_CurrErrorBound:      return "Factory/CurrentErrorBound";
    case NAME_ControlVoltages:     return "Factory/ControlVoltages";
    case NAME_PID_Kp:              return "Factory/PID_Kp";
    case NAME_PID_Ti:              return "Factory/PID_Ti";
    case NAME_PID_Td:              return "Factory/PID_Td";
    case NAME_PIDControlEnabled:   return "Factory/PIDControlEnabled";
    }
    return QString();
}

/**
 * @brief DefaultParamValue
 * @author 刘嘉诚
 * @date 2026.06.09
 */
QVariant DefaultParamValue(ParamName_TypeDef ParamName)
{
    for(const ParamDefaultItem &item : kDefaultParamItems){
        if(item.name == ParamName){
            return QString(item.value);
        }
    }
    return QVariant();
}

/**
 * @brief ConfigDirPath
 * @author 刘嘉诚
 * @date 2026.06.09
 */
QString ConfigDirPath(void)
{
    return QDir(QCoreApplication::applicationDirPath()).filePath("config");
}

/**
 * @brief ParamIniPath
 * @author 刘嘉诚
 * @date 2026.06.09
 */
QString ParamIniPath(void)
{
    return QDir(ConfigDirPath()).filePath("Param.ini");
}

/**
 * @brief DefaultParamIniPath
 * @author 刘嘉诚
 * @date 2026.06.09
 */
QString DefaultParamIniPath(void)
{
    return QDir(ConfigDirPath()).filePath("default_param.ini");
}

/**
 * @brief PrepareSettings
 * @author 刘嘉诚
 * @date 2026.06.09
 */
void PrepareSettings(QSettings *settings)
{
    settings->setIniCodec("UTF-8");
}

/**
 * @brief WriteDefaultParamValues
 * @author 刘嘉诚
 * @date 2026.06.09
 */
void WriteDefaultParamValues(QSettings *settings)
{
    for(const ParamDefaultItem &item : kDefaultParamItems){
        settings->setValue(ParamSettingKey(item.name), QString(item.value));
    }
}

/**
 * @brief WriteDefaultParamIni
 * @author 刘嘉诚
 * @date 2026.06.09
 */
bool WriteDefaultParamIni(const QString &filePath)
{
    QSettings settings(filePath, QSettings::IniFormat);
    PrepareSettings(&settings);
    settings.clear();
    WriteDefaultParamValues(&settings);
    settings.sync();
    return settings.status() == QSettings::NoError;
}

/**
 * @brief LegacyParamName
 * @author 刘嘉诚
 * @date 2026.06.09
 */
ParamName_TypeDef LegacyParamName(const QString &legacyName, bool *ok)
{
    for(const ParamDefaultItem &item : kDefaultParamItems){
        QString key = Map_ParamName.value(item.name);
        if(key.endsWith(":")){
            key.chop(1);
        }
        if(key == legacyName){
            *ok = true;
            return item.name;
        }
    }
    *ok = false;
    return NAME_Temperature;
}

/**
 * @brief MigrateLegacyParamSetting
 * @author 刘嘉诚
 * @date 2026.06.09
 */
bool MigrateLegacyParamSetting(const QString &legacyPath, const QString &paramPath)
{
    QFile file(legacyPath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return false;
    }

    QSettings settings(paramPath, QSettings::IniFormat);
    PrepareSettings(&settings);
    settings.clear();
    WriteDefaultParamValues(&settings);

    QTextStream in(&file);
    while(!in.atEnd()){
        QString line = in.readLine().trimmed();
        int colonIndex = line.indexOf(":");
        int semicolonIndex = line.indexOf(";");
        if(colonIndex <= 0){
            continue;
        }
        if(semicolonIndex < 0){
            semicolonIndex = line.length();
        }

        QString legacyName = line.left(colonIndex).trimmed();
        QString value = line.mid(colonIndex + 1, semicolonIndex - colonIndex - 1).trimmed();
        bool ok = false;
        ParamName_TypeDef paramName = LegacyParamName(legacyName, &ok);
        if(ok){
            settings.setValue(ParamSettingKey(paramName), value);
        }
    }

    file.close();
    settings.sync();
    return settings.status() == QSettings::NoError;
}

/**
 * @brief FillMissingParamKeys
 * @author 刘嘉诚
 * @date 2026.06.09
 */
bool FillMissingParamKeys(const QString &paramPath, const QString &defaultPath)
{
    QSettings settings(paramPath, QSettings::IniFormat);
    QSettings defaultSettings(defaultPath, QSettings::IniFormat);
    PrepareSettings(&settings);
    PrepareSettings(&defaultSettings);

    bool changed = false;
    for(const ParamDefaultItem &item : kDefaultParamItems){
        QString key = ParamSettingKey(item.name);
        if(!settings.contains(key)){
            settings.setValue(key, defaultSettings.value(key, DefaultParamValue(item.name)));
            changed = true;
        }
    }

    if(changed){
        settings.sync();
    }
    return settings.status() == QSettings::NoError;
}

/**
 * @brief EnsureParamIniReady
 * @author 刘嘉诚
 * @date 2026.06.09
 */
bool EnsureParamIniReady(void)
{
    QDir configDir(ConfigDirPath());
    if(!configDir.exists() && !QDir(QCoreApplication::applicationDirPath()).mkpath("config")){
        return false;
    }

    QString defaultPath = DefaultParamIniPath();
    if(!QFile::exists(defaultPath) && !WriteDefaultParamIni(defaultPath)){
        return false;
    }

    QString paramPath = ParamIniPath();
    if(!QFile::exists(paramPath)){
        QString legacyPath = QDir(QCoreApplication::applicationDirPath()).filePath("Param.Setting");
        if(QFile::exists(legacyPath)){
            if(!MigrateLegacyParamSetting(legacyPath, paramPath)){
                return false;
            }
        }else if(!QFile::copy(defaultPath, paramPath)){
            if(!WriteDefaultParamIni(paramPath)){
                return false;
            }
        }
    }

    return FillMissingParamKeys(paramPath, defaultPath);
}
}



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
    static bool warningShown = false;
    if(!EnsureParamIniReady()){
        if(!warningShown){
            Popup_Window("错误", "参数配置文件初始化失败，请检查软件目录下的config文件夹权限。");
            warningShown = true;
        }
        return false;
    }

    QString key = ParamSettingKey(ParamName);
    if(key.isEmpty()){
        Popup_Window("严重错误", "参数映射表缺失，请检查代码！");
        return false;
    }

    QSettings settings(ParamIniPath(), QSettings::IniFormat);
    PrepareSettings(&settings);
    settings.setValue(key, ParamValue);
    settings.sync();
    return settings.status() == QSettings::NoError;
}


/**
 * @brief Param_Setting_Write
 * @author 刘嘉诚
 * @date 2026.06.08
 */
bool Widget::Param_Setting_Write(ParamName_TypeDef ParamName, int ParamValue)
{
    return Param_Setting_Write(ParamName, QString::number(ParamValue));
}

/**
 * @brief Param_Setting_Write
 * @author 刘嘉诚
 * @date 2026.06.08
 */
bool Widget::Param_Setting_Write(ParamName_TypeDef ParamName, float ParamValue)
{
    return Param_Setting_Write(ParamName, QString::number(ParamValue));
}

/**
 * @brief Param_Setting_Write
 * @author 刘嘉诚
 * @date 2026.06.08
 */
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
    static bool warningShown = false;
    if(!EnsureParamIniReady()){
        if(!warningShown){
            Popup_Window("错误", "读取参数失败，请检查软件目录下的config文件夹权限。");
            warningShown = true;
        }
        return QVariant();
    }

    QString key = ParamSettingKey(ParamName);
    if(key.isEmpty()){
        Popup_Window("严重错误", "参数映射表缺失，请检查代码！");
        return QVariant();
    }

    QSettings settings(ParamIniPath(), QSettings::IniFormat);
    PrepareSettings(&settings);
    if(!settings.contains(key)){
        QVariant defaultValue = DefaultParamValue(ParamName);
        settings.setValue(key, defaultValue);
        settings.sync();
        return defaultValue;
    }
    return settings.value(key);
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
 * @brief VectorToString
 * @author 刘嘉诚
 * @date 2026.06.08
 */
QString Widget::VectorToString(const QVector<double>& vec){
    QStringList list;
    for(double v : vec) {
        list << QString::number(v, 'f', 6);
    }
    return list.join(",");
}

/**
 * @brief CurrentMcuCurrPos
 * @author 刘嘉诚
 * @date 2026.06.08
 */
int Widget::CurrentMcuCurrPos(void) const
{
    return 7 - static_cast<int>(Param_used.CurrPos);
}

/**
 * @brief CurrentPidParamIndex
 * @author 刘嘉诚
 * @date 2026.06.08
 */
int Widget::CurrentPidParamIndex(void) const
{
    if(Param_used.CurrPos == static_cast<int>(CURRENTPOSITION_auto)){
        return -1;
    }

    int mcuCurrPos = CurrentMcuCurrPos();
    int idx = mcuCurrPos - static_cast<int>(CURRENTPOSITION_100mA);
    if(idx < 0 || idx >= Param_used.PID_Kp.size()){
        return -1;
    }
    return idx;
}

/**
 * @brief Load_PIDParamsForCurrentPosition
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::Load_PIDParamsForCurrentPosition(void)
{
    int idx = CurrentPidParamIndex();
    if(idx < 0){
        ui->cin_Kp->setText("---");
        ui->cin_Ti->setText("---");
        ui->cin_Td->setText("---");
        return;
    }

    Controller_used.Kp = Param_used.PID_Kp[idx];
    Controller_used.Ti = Param_used.PID_Ti[idx];
    Controller_used.Td = Param_used.PID_Td[idx];

    ui->cin_Kp->setText(QString::number(Controller_used.Kp));
    ui->cin_Ti->setText(QString::number(Controller_used.Ti));
    ui->cin_Td->setText(QString::number(Controller_used.Td));
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

/**
 * @brief Modify_Param_used
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::Modify_Param_used(ParamName_TypeDef ParamName, int value)
{
    Modify_Param_used(ParamName, static_cast<double>(value));
}
