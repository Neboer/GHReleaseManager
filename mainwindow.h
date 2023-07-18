#pragma once#include <QMainWindow>
#include "ProxyDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void openProxyDialog();
private:
    Ui::MainWindow *ui;
    ProxyDialog* proxyDialog;
};
#endif // MAINWINDOW_H
