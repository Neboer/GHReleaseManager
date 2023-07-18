#include "mainwindow.h"
#include "./ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    proxyDialog = new ProxyDialog(this);
    // 连接actionProxy的triggered信号到槽函数
    connect(ui->actionProxy, &QAction::triggered, this, &MainWindow::openProxyDialog);
}
MainWindow::~MainWindow()
{
    delete ui;
}
// 自定义的槽函数，用于打开ProxyDialog对话框
void MainWindow::openProxyDialog()
{
    proxyDialog->exec(); // 打开对话框，使用exec()方法以模态方式显示对话框
}
