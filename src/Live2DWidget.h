#ifndef LIVE2DWIDGET_H
#define LIVE2DWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>

class Live2DManager;

class Live2DWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    Live2DWidget(QWidget *parent = nullptr);
    ~Live2DWidget();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    QTimer *m_timer;
    Live2DManager *m_manager;
};

#endif // LIVE2DWIDGET_H
