#include "windowsvideoitem.h"
#include <QDebug>
#include <QPainter>
#include <QBrush>
#include <QFont>

WindowsVideoItem::WindowsVideoItem(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , m_source("")
    , m_playing(false)
    , m_opacity(1.0)
    , m_updateTimer(new QTimer(this))
    , m_frameCounter(0)
{
    setRenderTarget(QQuickPaintedItem::FramebufferObject);
    setPerformanceHint(QQuickPaintedItem::FastFBOResizing, true);
    
    // Initialize with a default frame
    m_currentFrame = QImage(640, 480, QImage::Format_RGB32);
    m_currentFrame.fill(Qt::black);
    
    // Setup update timer for test animation
    connect(m_updateTimer, &QTimer::timeout, this, &WindowsVideoItem::updateFrame);
    m_updateTimer->setInterval(33); // ~30 FPS
    
    qDebug() << "WindowsVideoItem created";
}

WindowsVideoItem::~WindowsVideoItem()
{
    cleanupVideo();
}

void WindowsVideoItem::paint(QPainter *painter)
{
    QMutexLocker locker(&m_frameMutex);
    
    if (m_currentFrame.isNull()) {
        // Paint a placeholder
        painter->fillRect(boundingRect(), Qt::black);
        painter->setPen(Qt::white);
        painter->setFont(QFont("Arial", 16));
        painter->drawText(boundingRect(), Qt::AlignCenter, "Windows Video\nNo Signal");
        return;
    }
    
    painter->setOpacity(m_opacity);
    painter->drawImage(boundingRect(), m_currentFrame);
}

QString WindowsVideoItem::source() const
{
    return m_source;
}

void WindowsVideoItem::setSource(const QString &source)
{
    if (m_source != source) {
        m_source = source;
        emit sourceChanged();
        
        if (m_playing) {
            initializeVideo();
        }
        
        qDebug() << "WindowsVideoItem source changed to:" << source;
    }
}

bool WindowsVideoItem::playing() const
{
    return m_playing;
}

void WindowsVideoItem::setPlaying(bool playing)
{
    if (m_playing != playing) {
        m_playing = playing;
        emit playingChanged();
        
        if (m_playing) {
            start();
        } else {
            stop();
        }
    }
}

qreal WindowsVideoItem::opacity() const
{
    return m_opacity;
}

void WindowsVideoItem::setOpacity(qreal opacity)
{
    if (qAbs(m_opacity - opacity) > 0.001) {
        m_opacity = opacity;
        emit opacityChanged();
        update();
    }
}

void WindowsVideoItem::start()
{
    qDebug() << "WindowsVideoItem starting playback";
    
    if (!m_updateTimer->isActive()) {
        m_updateTimer->start();
    }
    
    initializeVideo();
}

void WindowsVideoItem::stop()
{
    qDebug() << "WindowsVideoItem stopping playback";
    
    if (m_updateTimer->isActive()) {
        m_updateTimer->stop();
    }
    
    cleanupVideo();
}

void WindowsVideoItem::updateFrame()
{
    generateTestFrame();
    update();
}

void WindowsVideoItem::initializeVideo()
{
    // TODO: Implement actual video initialization based on source
    // For now, just generate test frames
    qDebug() << "WindowsVideoItem initializing video for source:" << m_source;
}

void WindowsVideoItem::cleanupVideo()
{
    // TODO: Implement video cleanup
    qDebug() << "WindowsVideoItem cleaning up video resources";
}

void WindowsVideoItem::generateTestFrame()
{
    QMutexLocker locker(&m_frameMutex);
    
    // Generate a simple test pattern
    m_currentFrame = QImage(640, 480, QImage::Format_RGB32);
    
    QPainter painter(&m_currentFrame);
    
    // Animated background
    int colorShift = (m_frameCounter * 2) % 360;
    QColor bgColor = QColor::fromHsv(colorShift, 100, 80);
    painter.fillRect(m_currentFrame.rect(), bgColor);
    
    // Moving rectangle
    int rectX = (m_frameCounter * 3) % (640 - 100);
    int rectY = (m_frameCounter * 2) % (480 - 50);
    painter.fillRect(rectX, rectY, 100, 50, Qt::white);
    
    // Frame counter text
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 14, QFont::Bold));
    painter.drawText(10, 30, QString("Windows Video Plugin"));
    painter.drawText(10, 50, QString("Frame: %1").arg(m_frameCounter));
    painter.drawText(10, 70, QString("Source: %1").arg(m_source.isEmpty() ? "None" : m_source));
    
    m_frameCounter++;
}
