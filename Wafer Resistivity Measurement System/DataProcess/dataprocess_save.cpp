#include "widget.h"
#include <QDir>
#include <QTextStream>
#include <QDebug>

/**
 * @brief Widget::AppendValueToFile 将数据追加保存到文本文件，保留历史内容，每行格式为"数据,"
 * @param Value 待保存的double型数据
 * @param FilePath 保存的文件路径,2016.01.26改为在可执行路径下
 * @date  2026.01.26
 */
void Widget::AppendValueToFile(double Value, ValueType_TypeDef ValueType)
{
    QString Dir_App = QCoreApplication::applicationDirPath();   // 获取可执行文件所在目录
    QString Dir_Output = Dir_App + "/Data/";    // 定义子目录
    // 判断目录是否存在,如果不存在,创建目录
    QDir dir;
    if (!dir.exists(Dir_Output)){
        dir.mkpath(Dir_Output);
    }
    QString ValueType_QS = Map_ValueType.value(ValueType);
    QString MeasureDirection;
    if(MeasureState_used.MeasureDirection == MEASUREDIRECTION_FORWARD){
        MeasureDirection = 'f';
    }else{
        MeasureDirection = 'r';
    }
    QString FilePath = Dir_Output+ ValueType_QS+ '_'+ MeasureDirection+ '_'+ MeasureState_used.Time_MeasurementStart + ".txt";   // 构建完整路径

    // 打开文件,判断是否能打开
    QFile file(FilePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "文件打开失败：" << file.errorString() << "路径：" << FilePath;
        return;
    }

    // 写入数据
    QTextStream out(&file);
    out << QString::number(Value) << "\n";
    file.close();
}
