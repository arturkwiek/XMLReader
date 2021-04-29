#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    QFile *xmlFile;
    QXmlStreamReader *xmlReader;
    xmlFile = new QFile(fileName);
    if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this,"Load XML File Problem",
                              "Couldn't open xmlfile.xml to load settings for download",
                              QMessageBox::Ok);
        return;
    }
    xmlReader = new QXmlStreamReader(xmlFile);


    //Parse the XML until we reach end of it
    while(!xmlReader->atEnd() && !xmlReader->hasError()) {
        // Read next element
        QXmlStreamReader::TokenType token = xmlReader->readNext();
        if(token == QXmlStreamReader::StartElement) {
            if((xmlReader->name().toString() == "NAME") || (xmlReader->name().toString() == "VALUE")) {
                qDebug() << xmlReader->name();
                token = xmlReader->readNext();
                qDebug() << xmlReader->text();
            }
        }

        //----------------------

        if(token == QXmlStreamReader::StartElement) {
            if((xmlReader->name().toString() == "stageType")
                    || (xmlReader->name().toString() == "featureType")
                    || (xmlReader->name().toString() == "boostType")
                    || (xmlReader->name().toString() == "mode")
                    || (xmlReader->name().toString() == "featureType")) {
                qDebug() << xmlReader->name();
                token = xmlReader->readNext();
                qDebug() << xmlReader->text();
            }
        }
        //If token is just StartDocument - go to next
//        if(token == QXmlStreamReader::StartDocument) {
//            continue;
//        }
//        //If token is StartElement - read it
//        if(token == QXmlStreamReader::StartElement) {

//            if(xmlReader->name() == "NAME") {
//                //                qDebug() << "I've got NAME";
//                qDebug() << "name: " << xmlReader->name();
//            }
//            if(xmlReader->name() == "Characters") {
//                //                qDebug() << "I've got NAME";
//                qDebug() << "text: " << xmlReader->tokenString();
//            }

//            if(xmlReader->name() == "id") {
//                qDebug() << "id: " << xmlReader->readElementText();
//            }
//        }
//        if(xmlReader->tokenString() == "Characters")
//            qDebug() << " tokenString: " << xmlReader->tokenString()
//                     << " text: " << xmlReader->text()
//                     << " name: " << xmlReader->name()
//                     << " Comment: " << xmlReader->Comment;

        ui->textEdit->append(QString("name: %1 text: %2 tokenString: %3 Comment: %4").arg(xmlReader->name().toString()).arg(xmlReader->text().toString()).arg(xmlReader->tokenString()).arg(xmlReader->Comment));
    }

    if(xmlReader->hasError()) {
        QMessageBox::critical(this,
                              "xmlFile.xml Parse Error",xmlReader->errorString(),
                              QMessageBox::Ok);
        return;
    }

    //close reader and flush file
    xmlReader->clear();
    xmlFile->close();

}
