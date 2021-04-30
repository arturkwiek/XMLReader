#include "xmlreader.h"

#include <QFile>
#include <QMessageBox>
#include <QXmlStreamReader>
#include <QFileDialog>
#include <QDebug>

XMLReader::XMLReader(QString filename)
{
    QFile *xmlFile;
    QXmlStreamReader *xmlFileReader;
    m_xmlFileName = filename;
    xmlFile = new QFile(m_xmlFileName);
    if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(NULL,"Load XML File Problem",
                              "Couldn't open xmlfile.xml to load settings for download",
                              QMessageBox::Ok);
        return;
    }
    xmlFileReader = new QXmlStreamReader(xmlFile);


    //Parse the XML until we reach end of it
    while(!xmlFileReader->atEnd() && !xmlFileReader->hasError()) {
        // Read next element
        QXmlStreamReader::TokenType token = xmlFileReader->readNext();
        if(token == QXmlStreamReader::StartElement) {
            if((xmlFileReader->name().toString() == "NAME")
                    || (xmlFileReader->name().toString() == "VALUE")) {
                qDebug() << xmlFileReader->name();
                token = xmlFileReader->readNext();
                qDebug() << xmlFileReader->text();
            }
        }

        //----------------------

        if(token == QXmlStreamReader::StartElement) {
            if(xmlFileReader->name().toString() == "stageType") {
                token = xmlFileReader->readNext();
                qDebug() << "Stage Type: " + xmlFileReader->text().toString();
            }
            if(xmlFileReader->name().toString() == "featureType") {
                token = xmlFileReader->readNext();
                qDebug() << "Feature Type: " + xmlFileReader->text().toString();
            }
            if(xmlFileReader->name().toString() == "boostType") {
                token = xmlFileReader->readNext();
                qDebug() << "Boost Type: " + xmlFileReader->text().toString();
            }
            if(xmlFileReader->name().toString() == "mode") {
                token = xmlFileReader->readNext();
                qDebug() << "Mode: " + xmlFileReader->text().toString();
            }
        }
        //        ui->textEdit->append(QString("tokenString: %1 name: %2 text: %3 Comment: %4").arg(xmlFileReader->tokenString()).arg(xmlFileReader->name().toString()).arg(xmlFileReader->text().toString()).arg(xmlFileReader->Comment));
    }

    if(xmlFileReader->hasError()) {
        QMessageBox::critical(NULL,
                              "xmlFile.xml Parse Error",xmlFileReader->errorString(),
                              QMessageBox::Ok);
        return;
    }

    //close reader and flush file
    xmlFileReader->clear();
    xmlFile->close();
}
