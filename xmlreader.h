#ifndef XMLREADER_H
#define XMLREADER_H

#include <QString>



class XMLReader
{
public:
    XMLReader(QString filename);

private:
    QString m_xmlFileName;
};

#endif // XMLREADER_H
