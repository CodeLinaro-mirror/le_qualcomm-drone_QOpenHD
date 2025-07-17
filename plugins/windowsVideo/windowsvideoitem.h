#ifndef WINDOWSVIDEOITEM_H
#define WINDOWSVIDEOITEM_H

#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QPainter>
#include <QImage>
#include <QMutex>
#include <QTimer>

class WindowsVideoItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(bool playing READ playing WRITE setPlaying NOTIFY playingChanged)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)

public:
    explicit WindowsVideoItem(QQuickItem *parent = nullptr);
    ~WindowsVideoItem();

    void paint(QPainter *painter) override;

    QString source() const;
    void setSource(const QString &source);

    bool playing() const;
    void setPlaying(bool playing);

    qreal opacity() const;
    void setOpacity(qreal opacity);

public slots:
    void start();
    void stop();
    void updateFrame();

signals:
    void sourceChanged();
    void playingChanged();
    void opacityChanged();

private:
    void initializeVideo();
    void cleanupVideo();
    void generateTestFrame();

    QString m_source;
    bool m_playing;
    qreal m_opacity;
    QImage m_currentFrame;
    QMutex m_frameMutex;
    QTimer *m_updateTimer;
    int m_frameCounter;
};

#endif // WINDOWSVIDEOITEM_H
