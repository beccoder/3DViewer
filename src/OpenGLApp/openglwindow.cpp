#include "openglwindow.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QKeyEvent>
#include <QMessageBox>
#include <QSettings>
#define STB_IMAGE_IMPLEMENTATION

OpenGLWindow::OpenGLWindow(QWidget *parent)
    : QOpenGLWidget{parent},
      m_program(nullptr)
{
    setMinimumSize(600, 400);
    loadSettings();
}

OpenGLWindow::~OpenGLWindow() {
    makeCurrent();

    m_vao.destroy();
    m_vertexBufferObject.destroy();
    delete m_program;
}

void OpenGLWindow::initializeGL() {
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);

//    m_program = new QOpenGLShaderProgram();

//    if (!m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/pass_through.vert"))
//        qDebug() << "Vertex shader errors:\n" << m_program->log();

//    if (!m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag"))
//        qDebug() << "Fragment shader errors:\n" << m_program->log();

//    if (!m_program->link())
//        qDebug() << "Shader linker errors:\n" << m_program->log();

//    char path[] = "/opt/goinfre/sunflowe/Pug.obj";

//    get_data(path, &vertices, &v_size, &indexList, &i_size);

//    for (unsigned int i = 0; i < i_size; i = i + 1) {
//        indexList[i] = indexList[i] - 1;
//    }

//    m_vao.create();

//    m_vertexBufferObject = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
//    m_vertexBufferObject.create();
//    m_vertexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);

//    m_elementBufferObject = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
//    m_elementBufferObject.create();
//    m_elementBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);

//    m_vao.bind();

//    glEnable(GL_PROGRAM_POINT_SIZE);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

//    m_vertexBufferObject.bind();
//    m_vertexBufferObject.allocate(vertices, v_size * sizeof(float));
//    m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 0);
//    m_program->enableAttributeArray(0);

//    m_elementBufferObject.bind();
//    m_elementBufferObject.allocate(indexList, i_size * sizeof(unsigned int));

//    m_program->bind();

//    free(vertices);
//    free(indexList);
}

bool OpenGLWindow::openModel(QString path) {
    makeCurrent();
    QByteArray ba = path.toLocal8Bit();
    char *pathC = ba.data();

    QMessageBox msgBox;

    if (get_data(pathC, &vertices, &v_size, &indexList, &i_size) != 0) {
        msgBox.setText("Something went wrong while parsing a file");
        msgBox.exec();
        return false;
    }

    if (!isFirst) {
        m_vao.destroy();
        m_vertexBufferObject.destroy();
        delete m_program;

        cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        yzAngle = 0.0f;
        xzAngle = 0.0f;
        lastTranslation = glm::vec3(0.0f, 0.0f, 0.0f);;
        lastXAngle = 0.0f;
        lastYAngle = 0.0f;
        lastZAngle = 0.0f;
        lastScale = 0;
    }
    isFirst = false;

    m_program = new QOpenGLShaderProgram();

    if (!m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/pass_through.vert")) {
        msgBox.setText("vertex shader is wrong");
        msgBox.exec();
        return false;
    }

    if (!m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag")) {
        msgBox.setText("fragment shader is wrong");
        msgBox.exec();
        return false;
    }

    if (!m_program->link()) {
        msgBox.setText("cannot link the shaders");
        msgBox.exec();
        return false;
    }

    for (unsigned int i = 0; i < i_size; i = i + 1) {
        indexList[i] = indexList[i] - 1;
    }

    m_vao.create();

    m_vertexBufferObject = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vertexBufferObject.create();
    m_vertexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);

    m_elementBufferObject = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_elementBufferObject.create();
    m_elementBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);

    m_vao.bind();

    glEnable(GL_PROGRAM_POINT_SIZE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    m_vertexBufferObject.bind();
    m_vertexBufferObject.allocate(vertices, v_size * sizeof(float));
    m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 0);
    m_program->enableAttributeArray(0);

    m_elementBufferObject.bind();
    m_elementBufferObject.allocate(indexList, i_size * sizeof(unsigned int));

    m_program->bind();

    free(vertices);
    free(indexList);

    paint = true;
    this->paintGL();

    return true;
}

void OpenGLWindow::paintGL() {
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClearColor(backColor->redF(), backColor->greenF(), backColor->blueF(), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!paint) {
        return;
    }

    calculateCamera();

    m_program->bind();

    unsigned int viewLoc  = m_program->uniformLocation("view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

    if (orthoProjection) {
        projection = glm::ortho(-1.0f * (float)width() / height(), 1.0f * (float)width() / height(), -1.0f, 1.0f, 0.1f, 100.0f);
    } else {
        projection = glm::perspective(glm::radians(fov), (float)width() / height(), 0.1f, 100.0f);
    }

    view = glm::lookAt(cameraPos, cameraTarget, cameraUp);

    unsigned int projLoc  = m_program->uniformLocation("projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);

    unsigned int VCLoc  = m_program->uniformLocation("lineColor");
    glm::vec4 col = glm::vec4(lineColor->redF(), lineColor->greenF(), lineColor->blueF(), 1.0f);
    glUniform4fv(VCLoc, 1, &col[0]);

    m_vao.bind();

    unsigned int modelLoc = m_program->uniformLocation("model");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

    if (showVerices) {
        glDrawArrays(GL_POINTS, 0, v_size / 3);
    }

    glDrawElements(GL_TRIANGLES, i_size, GL_UNSIGNED_INT, nullptr);

    m_vao.release();
}

bool OpenGLWindow::event(QEvent *e) {
    return QWidget::event(e);
}

void OpenGLWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isScribing = true;
        lastX = event->position().x();
        lastY = event->position().y();
    }
}

void OpenGLWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isScribing = false;
    }
}

void OpenGLWindow::wheelEvent(QWheelEvent *event) {
    if (event->angleDelta().y() > 0) {
        model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
    } else {
        model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
    }
    this->update();
}

void OpenGLWindow::mouseMoveEvent(QMouseEvent *event) {
    if (isScribing) {
        float tmpX = event->position().x();
        float tmpY = event->position().y();

        float xoffset = tmpX - lastX;
        float yoffset = lastY - tmpY;

        float sensitivity = 1.0f; // change this value to your liking
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yzAngle += -yoffset;
        yzAngle = yzAngle > 360.0f ? (yzAngle - 360.0f) : yzAngle;
        yzAngle = yzAngle < -360.0f ? (yzAngle + 360.0f) : yzAngle;

        xzAngle += -xoffset;
        xzAngle = xzAngle > 360.0f ? (xzAngle - 360.0f) : xzAngle;
        xzAngle = xzAngle < -360.0f ? (xzAngle + 360.0f) : xzAngle;

        lastX = tmpX;
        lastY = tmpY;

        this->update();
    }
}

void OpenGLWindow::setOrtho() {
    orthoProjection = true;
    this->update();
}

void OpenGLWindow::setPerspective() {
    orthoProjection = false;
    this->update();
}

void OpenGLWindow::keyHandle(QKeyEvent * event) {
    float cameraSpeed = 0.05f;
    switch (event->key()) {
    case Qt::Key_W:
        cameraTarget += cameraSpeed * cameraUp;
        break;
    case Qt::Key_S:
        cameraTarget -= cameraSpeed * cameraUp;
        break;
    case Qt::Key_A:
        cameraTarget -= cameraSpeed * cameraRight;
        break;
    case Qt::Key_D:
        cameraTarget += cameraSpeed * cameraRight;
        break;
    default:
        break;
    }
    this->update();
}

void OpenGLWindow::calculateCamera() {
    float r = R * cos(glm::radians(yzAngle));
    cameraPos   = glm::vec3(cameraTarget.x + r * sin(glm::radians(xzAngle)),
                            cameraTarget.y + R * sin(glm::radians(yzAngle)),
                            cameraTarget.z + r * cos(glm::radians(xzAngle))) + cameraTarget;

    cameraUp    = glm::vec3(-sin(glm::radians(xzAngle)) * sin(glm::radians(yzAngle)),
                            cos(glm::radians(yzAngle)),
                            -cos(glm::radians(xzAngle)) * sin(glm::radians(yzAngle)));
    cameraRight = glm::cross(cameraTarget - cameraPos, cameraUp);
}

void OpenGLWindow::setBackGroundColor(const QColor &color) {
    backColor->setRgb(color.rgb());

    QSettings settings("settings.conf", QSettings::IniFormat);
    settings.setValue("backColor", color);

    this->update();
}

void OpenGLWindow::setLineColor(const QColor &color) {
    lineColor->setRgb(color.rgb());

    QSettings settings("settings.conf", QSettings::IniFormat);
    settings.setValue("lineColor", color);

    this->update();
}

QString OpenGLWindow::getVertices() {
    return QString::number(v_size);
}

QString OpenGLWindow::getEdges() {
    return QString::number(v_size / 3);
}

void OpenGLWindow::translateModel(int x, int y, int z) {
    glm::vec3 tmp = glm::vec3(0.1f * (float)x, 0.1f * (float)y, 0.1f * (float)z) - lastTranslation;
    lastTranslation = glm::vec3(0.1f * (float)x, 0.1f * (float)y, 0.1f * (float)z);
    model = glm::translate(model, tmp);
    this->update();
}

void OpenGLWindow::rotateModel(int x, int y, int z) {
    model = glm::rotate(model, glm::radians((float)x - lastXAngle), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians((float)y - lastYAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians((float)z - lastZAngle), glm::vec3(0.0f, 0.0f, 1.0f));

    lastXAngle = (float)x;
    lastYAngle = (float)y;
    lastZAngle = (float)z;
    this->update();
}

void OpenGLWindow::scaleModel(int factor) {
    for (int i = 0; i < abs(factor - lastScale); i++) {
        if (factor - lastScale > 0) {
            model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
        } else {
            model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
        }
    }
    lastScale = factor;
    this->update();
}

void OpenGLWindow::loadSettings() {
    QSettings settings("settings.conf", QSettings::IniFormat);

    QColor back = settings.value("backColor", QColor(0, 0, 0)).value<QColor>();
    backColor->setRgb(back.rgb());

    QColor line = settings.value("lineColor", QColor(255, 255, 255)).value<QColor>();
    lineColor->setRgb(line.rgb());
}
