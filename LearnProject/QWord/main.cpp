#include "qword.h"
#include <QtGui/QApplication>
#include <QtCore>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QCoreApplication a(argc, argv);
	QTextCodec *codec = QTextCodec::codecForName("GB2312");
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);	
	QWord word;
	word.createNewWord();				
	word.setPageOrientation(1);			//ҳ�����
	word.setWordPageView(3);			//ҳ����ͼ
//	word.insertMoveDown();				//����س�
	word.setFontSize(25);				//�����С	
	word.setParagraphAlignment(0);		//������������
	word.setFontBold(true);				//����Ӵ�
	word.insertText(QString("��ά����Զ��Ѳ��ϵͳ"));//��������
	word.setFontBold(false);			//����Ӵ�
	word.insertMoveDown();				//����س�
	word.setParagraphAlignment(1);		//������������
	word.setFontSize(14);
	word.insertText(QString("Ѳ�쵥λ�����ܱ��վ����ϵͳ�ۺϼ��ƽ̨"));//��������	
	word.insertMoveDown();	
	word.insertText(QString("Ѳ��ƻ���220kV С�ӱ�"));//��������	
	word.insertMoveDown();	
	word.insertText(QString("Ѳ��ʱ�䣺2014-04-21 10:19:41"));//��������	
	word.insertMoveDown();	
	word.insertText(QString("Ѳ �� �ˣ�"));//��������	
	word.insertMoveDown();	
	word.setFontSize(12);
	word.setParagraphAlignment(0);		//������������
	word.insertText(QString("Ѳ����ͳ�Ʊ�"));
	word.insertMoveDown();	
	word.setParagraphAlignment(0);		//����������
//	word.insertText(QString("���    Ѳ���  Ѳ��ʱ��  ����  Ѳ��ͼƬ  ����  �ο�  �˹��ж�  ��ע"));		
	word.intsertTable(4,9);			//���м���table	
//	word.openWord();
	word.setColumnWidth(1,40);
	word.setColumnWidth(2,70);
	word.setColumnWidth(3,80);
	word.setColumnWidth(4,50);
	word.setColumnWidth(5,200);
	word.setColumnWidth(6,70);
	word.setColumnWidth(7,50);
	word.setColumnWidth(8,70);
	word.setCellString(1,1,"���");
	word.setCellString(1,2,"Ѳ���");
	word.setCellString(1,3,"Ѳ��ʱ��");
	word.setCellString(1,4,"����");
	word.setCellString(1,5,"Ѳ��ͼƬ");	
	word.setCellString(1,6,"����");
	word.setCellString(1,7,"�ο�");
	word.setCellString(1,8,"�˹��ж�");
	word.setCellString(1,9,"��ע");
	word.setCellString(2,1,"1");
	word.setCellString(2,2,"�ܽ����1");
	word.setCellString(2,3,"2014-04-21\n10:19:41");
	word.setCellString(2,4,"����");
//	word.setCellString(2,5,"��");
	word.insertCellPic(2,5,"D:\\temp\\223-223.jpg");
	word.setCellString(2,6,"������ʼ");
	word.setCellString(2,7,"�ο�");
	word.setCellString(2,8,"������\n\n���쳣");
	word.setCellString(2,9," ");
	word.setCellString(3,1,"2");
	word.setCellString(3,2,"�ܽ����1");
	word.setCellString(3,3,"2014-04-21\n10:19:41");
	word.setCellString(3,4,"����");
	//word.setCellString(3,5,"��");
	word.insertCellPic(3,5,"D:\\temp\\123.jpg");
	word.setCellString(3,6,"������ʼ");
	word.setCellString(3,7,"�ο�");
	word.setCellString(3,8,"������\n\n���쳣");
	word.setCellString(3,9," ");
	word.setCellString(4,1,"3");
	word.setCellString(4,2,"�ܽ����1");
	word.setCellString(4,3,"2014-04-21\n10:19:41");
	word.setCellString(4,4,"����");
//	word.setCellString(4,5,"��");
	word.insertCellPic(4,5,"D:\\temp\\225-225.jpg");
	word.setCellString(4,6,"������ʼ");
	word.setCellString(4,7,"�ο�");
	word.setCellString(4,8,"������\n\n���쳣");
	word.setCellString(4,9," ");	
	word.deleteSelectColumn(1);
	word.setTableAutoFitBehavior(4);
	word.moveForEnd();	
	word.insertMoveDown();	
	word.insertMoveDown();	
	word.setParagraphAlignment(2);		//������������
	word.setFontSize(14);
	word.insertText("Ѳ����ǩ�֣�_______________");
	word.insertMoveDown();	
	word.insertText("����ʱ�䣺2014-04-22 10:06:38");
	
	word.close();

	return a.exec();
}
