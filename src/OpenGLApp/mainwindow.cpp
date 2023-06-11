#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QSettings>
#include <QDir>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    glWindow = this->ui->openGLWidget;

    colorPicker = new QColorDialog(*glWindow->backColor, this);
    connect(colorPicker, &QColorDialog::currentColorChanged, this, &MainWindow::setBackGroundColor);

    lineColorPicker = new QColorDialog(*glWindow->lineColor, this);
    connect(lineColorPicker, &QColorDialog::currentColorChanged, this, &MainWindow::setLineColor);

    ui->objName->setText("No file is loaded");
    ui->infoLabel->setText("No file is loaded");

    loadSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::event(QEvent *e) {
    if (e->type() == QEvent::MouseButtonPress) {
        glWindow->translateModel(ui->xTranlation->value(), ui->yTranslation->value(), ui->zTranslation->value());
        glWindow->rotateModel(ui->xRotate->value(), ui->yRotate->value(), ui->zRotate->value());
        glWindow->scaleModel(ui->scaleSpin->value());
    }
    return QMainWindow::event(e);
}

void MainWindow::keyPressEvent( QKeyEvent * event ) {
    glWindow->keyHandle(event);
}

void MainWindow::on_pushButton_clicked()
{
    QString fileLoc = QFileDialog::getOpenFileName(this,
                                                   "Open a file",
                                                   "",
                                                   tr("Model files (*.obj)"));
    if (glWindow->openModel(fileLoc)) {
        ui->objName->setText(fileLoc);
        QString fileInfo = "Number of indices: ";
        fileInfo += (glWindow->getVertices() + "\n");
        fileInfo += ("Number of edges: " + glWindow->getEdges());
        ui->infoLabel->setText(fileInfo);
    }
}

void MainWindow::setBackGroundColor(const QColor &color) {
    glWindow->setBackGroundColor(color);
}

void MainWindow::setLineColor(const QColor &color) {
    glWindow->setLineColor(color);
}

void MainWindow::on_pushButton_2_clicked() {
    colorPicker->setCurrentColor(*glWindow->backColor);
    colorPicker->show();
}

void MainWindow::on_perspectiveButton_clicked()
{
    glWindow->setPerspective();

    QSettings settings("settings.conf", QSettings::IniFormat);
    settings.setValue("viewType", true);
}

void MainWindow::on_orthographicButton_clicked()
{
    glWindow->setOrtho();

    QSettings settings("settings.conf", QSettings::IniFormat);
    settings.setValue("viewType", false);
}


void MainWindow::on_xTranlation_valueChanged(int arg1)
{
    glWindow->translateModel(ui->xTranlation->value(), ui->yTranslation->value(), ui->zTranslation->value());
}

void MainWindow::on_yTranslation_valueChanged(int arg1)
{
    glWindow->translateModel(ui->xTranlation->value(), ui->yTranslation->value(), ui->zTranslation->value());
}

void MainWindow::on_zTranslation_valueChanged(int arg1)
{
    glWindow->translateModel(ui->xTranlation->value(), ui->yTranslation->value(), ui->zTranslation->value());
}

void MainWindow::on_xRotate_valueChanged(int arg1)
{
    glWindow->rotateModel(ui->xRotate->value(), ui->yRotate->value(), ui->zRotate->value());
}

void MainWindow::on_yRotate_valueChanged(int arg1)
{
    glWindow->rotateModel(ui->xRotate->value(), ui->yRotate->value(), ui->zRotate->value());
}

void MainWindow::on_zRotate_valueChanged(int arg1)
{
    glWindow->rotateModel(ui->xRotate->value(), ui->yRotate->value(), ui->zRotate->value());
}


void MainWindow::on_scaleSpin_valueChanged(int arg1)
{
    glWindow->scaleModel(ui->scaleSpin->value());
}

void MainWindow::on_showVertices_stateChanged(int arg1)
{
    QSettings settings("settings.conf", QSettings::IniFormat);

    if (ui->showVertices->checkState() == Qt::Unchecked) {
        glWindow->showVerices = false;
        settings.setValue("showVert", false);
    } else {
        glWindow->showVerices = true;
        settings.setValue("showVert", true);
    }
    glWindow->update();
}


void MainWindow::on_pushButton_3_clicked()
{
    lineColorPicker->setCurrentColor(*glWindow->lineColor);
    lineColorPicker->show();
}

void MainWindow::loadSettings() {
    QSettings settings("settings.conf", QSettings::IniFormat);

    bool isPerspective = settings.value("viewType", false).toBool();
    if (isPerspective) {
        ui->perspectiveButton->setChecked(true);
        glWindow->setPerspective();
    } else {
        ui->orthographicButton->setChecked(true);
        glWindow->setOrtho();
    }

    bool showVert = settings.value("showVert", false).toBool();
    if (showVert) {
        ui->showVertices->setChecked(true);
        glWindow->showVerices = true;
    } else {
        ui->showVertices->setChecked(false);
        glWindow->showVerices = false;
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    glWindow->grab().save("./" + QDateTime::currentDateTime().toString() + ".jpeg");
    glWindow->grab().save("./" + QDateTime::currentDateTime().toString() + ".bmp");
}
