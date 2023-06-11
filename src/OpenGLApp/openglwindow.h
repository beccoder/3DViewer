#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QMainWindow>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QColor>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern "C" {
    #include"file_loader.h"
}

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWindow(QWidget *parent = nullptr);
    virtual ~OpenGLWindow() Q_DECL_OVERRIDE;
    void keyHandle(QKeyEvent * event);
    void setBackGroundColor(const QColor &color);
    void setLineColor(const QColor &color);
    void setOrtho();
    void setPerspective();
    bool openModel(QString path);
    QColor *backColor = new QColor(186, 153, 61);
    QColor *lineColor = new QColor(100, 130, 4);

    QString getVertices();
    QString getEdges();

    void translateModel(int x, int y, int z);
    void rotateModel(int x, int y, int z);
    void scaleModel(int factor);
    bool showVerices = false;
protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    bool event(QEvent *e) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    bool isFirst = true;
    bool paint = false;

    unsigned int i_size;
    unsigned int v_size;
    float *vertices;
    unsigned int *indexList;

    bool orthoProjection = false;

    bool isScribing = false;
    float lastX;
    float lastY;

    float fov = 45.0f;

    float pitch = 0.0f;

    float R = 3.0f;
    float yzAngle = 0.0f;
    float xzAngle = 0.0f;

    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraPos;
    glm::vec3 cameraUp;
    glm::vec3 cameraRight;

    glm::mat4 projection;
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 lastTranslation = glm::vec3(0.0f, 0.0f, 0.0f);;
    float lastXAngle = 0.0f;
    float lastYAngle = 0.0f;
    float lastZAngle = 0.0f;
    int lastScale = 0;

    glm::mat4 view;

    // Wraps an OpenGL VertexArrayObject (VAO)
    QOpenGLVertexArrayObject m_vao;

    // Vertex buffer (positions and colors, interleaved storage mode).
    QOpenGLBuffer m_vertexBufferObject;
    QOpenGLBuffer m_elementBufferObject;

    // Holds the compiled shader programs.
    QOpenGLShaderProgram *m_program;

    void calculateCamera();
    void loadSettings();
};

#endif // OPENGLWINDOW_H
