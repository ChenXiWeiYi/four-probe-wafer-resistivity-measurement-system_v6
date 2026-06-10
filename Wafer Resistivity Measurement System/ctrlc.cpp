#include "widget.h"
#include "ui_widget.h"
#include <QApplication>
#include <QClipboard>
#include <QKeyEvent>
#include <QTableWidget>

static bool CopySelectedTableCells(QTableWidget *table)
{
    if(!table){
        return false;
    }

    QList<QTableWidgetItem *> items = table->selectedItems();
    if(items.isEmpty()){
        return true;
    }

    int minRow = items.at(0)->row();
    int maxRow = items.at(0)->row();
    int minCol = items.at(0)->column();
    int maxCol = items.at(0)->column();

    for(const QTableWidgetItem *item : items){
        minRow = qMin(minRow, item->row());
        maxRow = qMax(maxRow, item->row());
        minCol = qMin(minCol, item->column());
        maxCol = qMax(maxCol, item->column());
    }

    QString selectionText;
    for(int row = minRow; row <= maxRow; ++row){
        for(int column = minCol; column <= maxCol; ++column){
            QTableWidgetItem *item = table->item(row, column);
            if(item && item->isSelected()){
                selectionText += item->text();
            }
            if(column < maxCol){
                selectionText += "\t";
            }
        }
        selectionText += "\n";
    }

    QApplication::clipboard()->setText(selectionText);
    return true;
}

/**
 * @brief keyPressEvent
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->matches(QKeySequence::Copy)){
        QTableWidget *copyTables[] = {
            ui->TableWidget_f,
            ui->TableWidget_DebugForward,
            ui->TableWidget_DebugReverse
        };

        for(QTableWidget *table : copyTables){
            if(table == focusWidget()){
                CopySelectedTableCells(table);
                event->accept();
                return;
            }
        }
    }

    QWidget::keyPressEvent(event);
}
