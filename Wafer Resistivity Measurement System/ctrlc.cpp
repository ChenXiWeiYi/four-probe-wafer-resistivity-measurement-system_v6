#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>    // 处理按键
#include <QClipboard>   // 处理剪贴板
#include <QApplication> // 获取全局剪贴板对象

void Widget::keyPressEvent(QKeyEvent *event)
{
    // 监听：如果按下了 Ctrl+C，并且当前焦点在 TableWidget_f 上
    if (event->matches(QKeySequence::Copy) && ui->TableWidget_f == focusWidget())
    {
        QString selectionText;
        // 获取所有选中的格子（乱序的，而且可能包含重复的行列索引）
        QList<QTableWidgetItem*> items = ui->TableWidget_f->selectedItems();
        if (items.isEmpty()) return;

        // --- 第一步：计算选区的矩形范围 ---
        // 我们要找出选中的最小行、最大行、最小列、最大列
        int minRow = items.at(0)->row();
        int maxRow = items.at(0)->row();
        int minCol = items.at(0)->column();
        int maxCol = items.at(0)->column();

        for (const auto *item : items) {
            if (item->row() < minRow) minRow = item->row();
            if (item->row() > maxRow) maxRow = item->row();
            if (item->column() < minCol) minCol = item->column();
            if (item->column() > maxCol) maxCol = item->column();
        }

        // --- 第二步：按行列顺序拼接字符串 ---
        // 按照 Excel 的规则：
        // 列与列之间用制表符 '\t' 分隔
        // 行与行之间用换行符 '\n' 分隔
        for (int r = minRow; r <= maxRow; ++r) {
            for (int c = minCol; c <= maxCol; ++c) {
                QTableWidgetItem *item = ui->TableWidget_f->item(r, c);

                // 如果这个格子确实被选中了，就把它的文字拿出来
                // (因为选区可能不是矩形的，这里做一个安全检查)
                if (item && item->isSelected()) {
                    selectionText += item->text();
                }

                // 如果不是这一行的最后一列，加个制表符
                if (c < maxCol) selectionText += "\t";
            }
            // 这一行结束，加个换行符
            selectionText += "\n";
        }

        // --- 第三步：写入剪贴板 ---
        QApplication::clipboard()->setText(selectionText);

        // 阻止事件继续传播（告诉 Qt 我已经处理完按键了）
        event->accept();
        return;
    }

    if (event->matches(QKeySequence::Copy) && ui->TableWidget_r == focusWidget())
    {
        QString selectionText;
        // 获取所有选中的格子（乱序的，而且可能包含重复的行列索引）
        QList<QTableWidgetItem*> items = ui->TableWidget_r->selectedItems();
        if (items.isEmpty()) return;

        // --- 第一步：计算选区的矩形范围 ---
        // 我们要找出选中的最小行、最大行、最小列、最大列
        int minRow = items.at(0)->row();
        int maxRow = items.at(0)->row();
        int minCol = items.at(0)->column();
        int maxCol = items.at(0)->column();

        for (const auto *item : items) {
            if (item->row() < minRow) minRow = item->row();
            if (item->row() > maxRow) maxRow = item->row();
            if (item->column() < minCol) minCol = item->column();
            if (item->column() > maxCol) maxCol = item->column();
        }

        // --- 第二步：按行列顺序拼接字符串 ---
        // 按照 Excel 的规则：
        // 列与列之间用制表符 '\t' 分隔
        // 行与行之间用换行符 '\n' 分隔
        for (int r = minRow; r <= maxRow; ++r) {
            for (int c = minCol; c <= maxCol; ++c) {
                QTableWidgetItem *item = ui->TableWidget_r->item(r, c);

                // 如果这个格子确实被选中了，就把它的文字拿出来
                // (因为选区可能不是矩形的，这里做一个安全检查)
                if (item && item->isSelected()) {
                    selectionText += item->text();
                }

                // 如果不是这一行的最后一列，加个制表符
                if (c < maxCol) selectionText += "\t";
            }
            // 这一行结束，加个换行符
            selectionText += "\n";
        }

        // --- 第三步：写入剪贴板 ---
        QApplication::clipboard()->setText(selectionText);

        // 阻止事件继续传播（告诉 Qt 我已经处理完按键了）
        event->accept();
        return;
    }



    // 如果按的不是 Ctrl+C，就交给父类按默认方式处理
    QWidget::keyPressEvent(event);
}
