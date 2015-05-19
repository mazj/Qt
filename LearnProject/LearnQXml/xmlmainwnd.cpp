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

// 用 qt 的 dom 读取xml
void XmlMainWnd::on_pushButtonDomRead_clicked()
{
    //1. 定义一个 QDomDocument类
    QDomDocument doc;
    QString errStr;
    int errLine;
    int errCol;

    QFile file("../LearnQXml/toRead.xml");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("打开XML"), tr("不能读入文件toRead.xml:\n%2.").arg(file.errorString()));
        return;
    }

    // 2. 给 QDomDocument 设置内容，这里是一个文件
    if (!doc.setContent(&file, &errStr, &errLine, &errCol))
    {
        qWarning() << __FUNCTION__ << ": " << errStr << "at line "
                   << errLine << " column " << errCol;
        return;
    }
    file.close();

    //3. 获得根节点元素，有了根节点就可以做各种操作了
    QDomElement root = doc.documentElement();

    //4.例子，打印所有子节点元素名称
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
    // 1.创建 xml文件头,并插入
    QDomProcessingInstruction insNode =
            doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"GBK\"");
    doc.appendChild(insNode); //插入头

     //2.创建节点 元素等，由于 Qt的 dom的节点是共享的，想真正创建节点需要用
    // QDomDocument的 create各种方法
    QDomElement root = doc.createElement("MyML");
    doc.appendChild(root);

    QDomElement tag = doc.createElement("Greeting");
    tag.setAttribute(QString("attribute1"), "attributeValue");
    root.appendChild(tag);

    QDomText t = doc.createTextNode("Hello World");
    tag.appendChild(t);

    // 3.保存成文件
    QFile file("test.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate |QIODevice::Text))
        return ;

    QTextStream out(&file);
    doc.save(out,4,QDomNode::EncodingFromDocument);

    file.close();

}
