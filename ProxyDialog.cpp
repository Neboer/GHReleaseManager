#include "ProxyDialog.h"
#include "ui_ProxyDialog.h"
ProxyDialog::ProxyDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::ProxyDialog)
{
    ui->setupUi(this);
    // Connect the toggled signals of the radio buttons to their respective slots
    connect(ui->radioNoProxy, &QRadioButton::toggled, this, &ProxyDialog::on_radioNoProxy_toggled);
    connect(ui->radioHTTP, &QRadioButton::toggled, this, &ProxyDialog::on_radioHTTP_toggled);
    connect(ui->radioSocks5, &QRadioButton::toggled, this, &ProxyDialog::on_radioSocks5_toggled);
    connect(ui->radioSystemProxy, &QRadioButton::toggled, this, &ProxyDialog::on_radioSystemProxy_toggled);
    // Connect the clicked signal of the OK button to the applyProxySettings() slot
    connect(ui->buttonOK, &QPushButton::clicked, this, &ProxyDialog::on_buttonOK_clicked);
}
ProxyDialog::~ProxyDialog()
{
    delete ui;
}
void ProxyDialog::on_radioNoProxy_toggled(bool checked)
{
    // Disable the widgets related to HTTP Proxy if the radio button is checked
    ui->lineEditHTTP->setEnabled(!checked);
    ui->spinBoxHTTPPort->setEnabled(!checked);
    ui->checkBoxHTTPAuth->setEnabled(!checked);
    ui->lineEditHTTPUsername->setEnabled(!checked && ui->checkBoxHTTPAuth->isChecked());
    ui->lineEditHTTPPassword->setEnabled(!checked && ui->checkBoxHTTPAuth->isChecked());
}
void ProxyDialog::on_radioHTTP_toggled(bool checked)
{
    // Enable the widgets related to HTTP Proxy if the radio button is checked
    ui->lineEditHTTP->setEnabled(checked);
    ui->spinBoxHTTPPort->setEnabled(checked);
    ui->checkBoxHTTPAuth->setEnabled(checked);
    ui->lineEditHTTPUsername->setEnabled(checked && ui->checkBoxHTTPAuth->isChecked());
    ui->lineEditHTTPPassword->setEnabled(checked && ui->checkBoxHTTPAuth->isChecked());
}
void ProxyDialog::on_radioSocks5_toggled(bool checked)
{
    // Enable the widgets related to Socks5 Proxy if the radio button is checked
    ui->lineEditSocks5->setEnabled(checked);
    ui->spinBoxSocks5Port->setEnabled(checked);
    ui->checkBoxSocks5Auth->setEnabled(checked);
    ui->lineEditSocks5Username->setEnabled(checked && ui->checkBoxSocks5Auth->isChecked());
    ui->lineEditSocks5Password->setEnabled(checked && ui->checkBoxSocks5Auth->isChecked());
}
void ProxyDialog::on_radioSystemProxy_toggled(bool checked)
{
    // Disable all the widgets related to Proxy settings
    ui->lineEditHTTP->setEnabled(!checked);
    ui->spinBoxHTTPPort->setEnabled(!checked);
    ui->checkBoxHTTPAuth->setEnabled(!checked);
    ui->lineEditHTTPUsername->setEnabled(!checked && ui->checkBoxHTTPAuth->isChecked());
    ui->lineEditHTTPPassword->setEnabled(!checked && ui->checkBoxHTTPAuth->isChecked());
    ui->lineEditSocks5->setEnabled(!checked);
    ui->spinBoxSocks5Port->setEnabled(!checked);
    ui->checkBoxSocks5Auth->setEnabled(!checked);
    ui->lineEditSocks5Username->setEnabled(!checked && ui->checkBoxSocks5Auth->isChecked());
    ui->lineEditSocks5Password->setEnabled(!checked && ui->checkBoxSocks5Auth->isChecked());
}
void ProxyDialog::on_buttonOK_clicked()
{
    // Apply the proxy settings to the entire Qt application
    applyProxySettings();
    accept();
}
void ProxyDialog::applyProxySettings()
{
    QNetworkProxy proxy;
    if (ui->radioNoProxy->isChecked()) {
        // No Proxy option selected
        proxy.setType(QNetworkProxy::NoProxy);
    } else if (ui->radioHTTP->isChecked()) {
        // HTTP Proxy option selected
        proxy.setType(QNetworkProxy::HttpProxy);
        proxy.setHostName(ui->lineEditHTTP->text());
        proxy.setPort(ui->spinBoxHTTPPort->value());
        if (ui->checkBoxHTTPAuth->isChecked()) {
            // Authentication enabled
            proxy.setUser(ui->lineEditHTTPUsername->text());
            proxy.setPassword(ui->lineEditHTTPPassword->text());
        }
    } else if (ui->radioSocks5->isChecked()) {
        // SOCKS5 Proxy option selected
        proxy.setType(QNetworkProxy::Socks5Proxy);
        proxy.setHostName(ui->lineEditSocks5->text());
        proxy.setPort(ui->spinBoxSocks5Port->value());
        if (ui->checkBoxSocks5Auth->isChecked()) {
            // Authentication enabled
            proxy.setUser(ui->lineEditSocks5Username->text());
            proxy.setPassword(ui->lineEditSocks5Password->text());
        }
    } else if (ui->radioSystemProxy->isChecked()) {
        // System Proxy option selected
        proxy.setType(QNetworkProxy::DefaultProxy);
    }
    // Set the global proxy for the Qt application
    QNetworkProxy::setApplicationProxy(proxy);
}
