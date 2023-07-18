#pragma once#include <QDialog>
#include <QNetworkProxy>
namespace Ui {
    class ProxyDialog;
}
class ProxyDialog : public QDialog
{
Q_OBJECT
public:
    explicit ProxyDialog(QWidget *parent = nullptr);
    ~ProxyDialog();
private slots:
    void on_radioNoProxy_toggled(bool checked);
    void on_radioHTTP_toggled(bool checked);
    void on_radioSocks5_toggled(bool checked);
    void on_radioSystemProxy_toggled(bool checked);
    void on_buttonOK_clicked();
private:
    Ui::ProxyDialog *ui;
    void applyProxySettings();
};
#endif // PROXYDIALOG_H
