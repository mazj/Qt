#include "xmlmainwnd.h"
#include "ui_xmlmainwnd.h"

#include <QMessageBox>
#include <QDebug>

#include <QFile>
#include <QDomElement>
#include <QDomDocument>

XmlMainWnd::XmlMainWnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::XmlMainWnd)
{
    ui->setupUi(this);
}

XmlMainWnd::~XmlMainWnd()
{
    delete ui;
}

// �� qt �� dom ��ȡxml
void XmlMainWnd::on_pushButtonDomRead_clicked()
{
    //1. ����һ�� QDomDocument��
    QDomDocument doc;
    QString errStr;
    int errLine;
    int errCol;

    QFile file("../LearnQXml/toRead.xml");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("��XML"), tr("���ܶ����ļ�toRead.xml:\n%2.").arg(file.errorString()));
        return;
    }

    // 2. �� QDomDocument �������ݣ�������һ���ļ�
    if (!doc.setContent(&file, &errStr, &errLine, &errCol))
    {
        qWarning() << __FUNCTION__ << ": " << errStr << "at line "
                   << errLine << " column " << errCol;
        return;
    }
    file.close();

    //3. ��ø��ڵ�Ԫ�أ����˸��ڵ�Ϳ��������ֲ�����
    QDomElement root = doc.documentElement();

    //4.���ӣ���ӡ�����ӽڵ�Ԫ������
    QDomNode n = root.firstChild();
     while(!n.isNull()) {
         QDomElement e = n.toElement(); // try to convert the node to an element.
         if(!e.isNull()) {
             qDebug() << qPrintable(e.tagName()) << endl; // the node really is an element.
         }
         n = n.nextSibling();
     }
}

void XmlMainWnd::on_pushButtonDomWrite_clicked()
{
    QDomDocument doc("");
    // 1.���� xml�ļ�ͷ,������
    QDomProcessingInstruction insNode =
            doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"GBK\"");
    doc.appendChild(insNode); //����ͷ

     //2.�����ڵ� Ԫ�صȣ����� Qt�� dom�Ľڵ��ǹ���ģ������������ڵ���Ҫ��
    // QDomDocument�� create���ַ���
    QDomElement root = doc.createElement("MyML");
    doc.appendChild(root);

    QDomElement tag = doc.createElement("Greeting");
    tag.setAttribute(QString("attribute1"), "attributeValue");
    root.appendChild(tag);

    QDomText t = doc.createTextNode("Hello World");
    tag.appendChild(t);

    // 3.������ļ�
    QFile file("test.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate |QIODevice::Text))
        return ;

    QTextStream out(&file);
    doc.save(out,4,QDomNode::EncodingFromDocument);

    file.close();

}
