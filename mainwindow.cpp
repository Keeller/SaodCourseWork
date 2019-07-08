#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)//, ui(new Ui::MainWindow)
{
    MainWindow::Di=new dict();
    //ui->setupUi(this);
    m_grid=new QGridLayout();
    m_grid->addWidget(create_main_panel(),0,0);
   // m_grid->itemAt(0)->widget()->setHidden(false);
    setLayout(m_grid);
    setWindowTitle(tr("Тестирование"));
    resize(480, 280);

}

MainWindow::~MainWindow()
{
    //delete ui;
    delete m_grid;
    delete Button1;
    delete Button2;
    delete Button3;
    delete Button4;
    delete Button5;
    delete ListWidget;
}

QGroupBox* MainWindow::create_main_panel()
{
    QGroupBox* gr=new QGroupBox(tr(""));
    Button1=new QPushButton(tr("Составить словарь из текстового файла"));
    Button2=new QPushButton(tr("Загрузить словарь из файла"));
    Button3=new QPushButton(tr("Сохранить словарь"));
    Button4=new QPushButton(tr("Очистить словарь"));
    Button5=new QPushButton(tr("Найти элемент"));
    ListWidget= new QListWidget();
    QVBoxLayout* qgr=new QVBoxLayout();
    qgr->addWidget(Button1);
    qgr->addWidget(Button2);
    qgr->addWidget(Button3);
    qgr->addWidget(Button4);
    qgr->addWidget(Button5);
    qgr->addStretch(1);
    qgr->addWidget(ListWidget);
    gr->setLayout(qgr);
    connect(Button1,SIGNAL(clicked()),Di,SLOT(parce_from_file()));
    connect(Button2,SIGNAL(clicked()),Di,SLOT(load_from_file()));
    connect(Button3,SIGNAL(clicked()),Di,SLOT(save_to_file()));
    connect(Di,SIGNAL(load_data_complit(bool)),this,SLOT(load_data_to_table(bool)));
    connect(Button4,SIGNAL(clicked()),Di,SLOT(clear()));
    connect(Button5,SIGNAL(clicked()),this,SLOT(serarch()));

    return gr;

}

void MainWindow::load_data_to_table(bool b)
{
    if(b)
    {
        QStringList s=Di->get_dict();
        ListWidget->clear();
        ListWidget->addItems(Di->get_dict());

    }
    else
    {
        QMessageBox qms;
        qms.setText("Ошибка загрузки данных");
        qms.exec();
    }
}

void MainWindow::serarch()
{
    bool b=false;
    if(Di->is_empty())
        return;
   QString i=QInputDialog::getText(0,
                                   "Input",
                                   "Name:",
                                   QLineEdit::Normal,
                                   "You Word",
                                   &b );
   if(b)
   {
       i=i.toLower();
       QMessageBox qms;
    if(!Di->in(i))
    {
       qms.setText("Элемента не существует");
       qms.exec();
       return;
    }
    QString str="";
    QTextStream stream(&str);
    stream<<"Searched: "<<(Di->get_el((Di->get_id(i)))).get_word()<<" - "<<QString::number((Di->get_el((Di->get_id(i)))).get_count());
    qms.setText(str);
    qms.exec();
   }
}
