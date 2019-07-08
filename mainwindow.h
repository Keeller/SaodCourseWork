#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<dict.h>
#include<QPushButton>
#include<QListWidget>
#include<QGroupBox>
#include<QGridLayout>
#include<QFileDialog>
#include<QInputDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    dict* Di;
    //UI Widgets begin................
    QGridLayout* m_grid;
    QPushButton* Button1;
    QPushButton* Button2;
    QPushButton* Button3;
    QPushButton* Button4;
    QPushButton* Button5;
    QListWidget* ListWidget;

    //UI Widgets end..................
    QGroupBox* create_main_panel();

private:
    Ui::MainWindow *ui;

public slots:
    void load_data_to_table(bool b);
    void serarch();
};

#endif // MAINWINDOW_H
