#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Tcp.h"
#include "TcpServer.h"
QT_BEGIN_NAMESPACE
namespace Ui { class TcpClass; };
QT_END_NAMESPACE

class Tcp : public QMainWindow
{
    Q_OBJECT

public:
    Tcp(QWidget *parent = nullptr);
    ~Tcp();

private:
    Ui::TcpClass *ui;
};
