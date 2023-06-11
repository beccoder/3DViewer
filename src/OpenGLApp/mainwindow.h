#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "openglwindow.h"
#include <QColorDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void setBackGroundColor(const QColor &color);
    void setLineColor(const QColor &color);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_perspectiveButton_clicked();

    void on_orthographicButton_clicked();

    void on_xTranlation_valueChanged(int arg1);

    void on_yTranslation_valueChanged(int arg1);

    void on_zTranslation_valueChanged(int arg1);

    void on_xRotate_valueChanged(int arg1);

    void on_yRotate_valueChanged(int arg1);

    void on_zRotate_valueChanged(int arg1);

    void on_scaleSpin_valueChanged(int arg1);

    void on_showVertices_stateChanged(int arg1);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    QColorDialog *colorPicker;
    QColorDialog *lineColorPicker;

    OpenGLWindow *glWindow;
    bool event(QEvent *e) override;
    void keyPressEvent( QKeyEvent * event ) override;

    void loadSettings();
};
#endif // MAINWINDOW_H
