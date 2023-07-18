#include "watchertableview.h"
#include "qheaderview.h"
#include <QStandardItemModel>


WatcherTableView::WatcherTableView(QWidget *parent):QTableView(parent)
{
    // 添加表头标签
    QStringList headerLabels;
    headerLabels << "仓库名" << "本地版本" << "最新版本" << "安装位置" << "下载目标" << "安装指令";
    this->model = new QStandardItemModel(this);
    this->model->setHorizontalHeaderLabels(headerLabels);
    this->setModel(model);

    // 设置表头自适应列宽
    QHeaderView* header = this->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
}
