#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xmlreader.h"

#include <QFile>
#include <QMessageBox>
#include <QXmlStreamReader>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnLoadXML_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"), "/home/aspire7/", tr("XML file (*.xml)"));


    XMLReader xmlFile(fileName);
}
