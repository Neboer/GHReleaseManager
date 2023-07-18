#pragma once
#include "qstandarditemmodel.h"
#include <QTableView>

class WatcherTableView : public QTableView
{
private:
    QStandardItemModel* model;
public:
    WatcherTableView(QWidget *parent = nullptr);
};

#endif // WATCHERTABLEVIEW_H
