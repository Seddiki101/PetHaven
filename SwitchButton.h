#ifndef SWITCHBUTTH_H
#define SWITCHBUTTH_H

#include <QtWidgets>
#include <QtCore/qeasingcurve.h>

#define cyan500 QColor("#00bcd4")
#define gray50 QColor("#fafafa")
#define black QColor("#000000")
#define gray400 QColor("#bdbdbd")

Q_DECL_IMPORT void qt_blurImage(QPainter *p, QImage &blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0); // src/widgets/effects/qpixmapfilter.cpp

namespace Style {

    using Type = QEasingCurve::Type;

    struct Animation {
        Animation() = default;
        Animation(Type _easing, int _duration) :easing{ _easing }, duration{ _duration } {

        }

        Type easing;
        int duration;
    };

    struct Switch {
        Switch() :
            height{ 36 },
            font{ QFont("Roboto medium", 13) },
            indicatorMargin{ QMargins(8, 8, 8, 8) },
            thumbOnBrush{ cyan500 },
            thumbOnOpacity{ 1 },
            trackOnBrush{ cyan500 },
            trackOnOpacity{ 0.5 },
            thumbOffBrush{ gray50 },
            thumbOffOpacity{ 1 },
            trackOffBrush{ black },
            trackOffOpacity{ 0.38 },
            thumbDisabled{ gray400 },
            thumbDisabledOpacity{ 1 },
            trackDisabled{ black },
            trackDisabledOpacity{ 0.12 },
            textColor{ black },
            disabledTextOpacity{ 0.26 },
            thumbBrushAnimation{ Animation(Type::Linear, 150) },
            trackBrushAnimation{ Animation(Type::Linear, 150) },
            thumbPosAniamtion{ Animation(Type::InOutQuad, 150) } {

        }

        int height;
        QFont font;
        QMargins indicatorMargin;
        QColor thumbOnBrush;
        double thumbOnOpacity;
        QColor trackOnBrush;
        double trackOnOpacity;
        QColor thumbOffBrush;
        double thumbOffOpacity;
        QColor trackOffBrush;
        double trackOffOpacity;
        QColor thumbDisabled;
        double thumbDisabledOpacity;
        QColor trackDisabled;
        double trackDisabledOpacity;
        QColor textColor;
        double disabledTextOpacity;
        Animation thumbBrushAnimation;
        Animation trackBrushAnimation;
        Animation thumbPosAniamtion;
    };

    inline QPixmap drawShadowEllipse(qreal radius, qreal elevation, const QColor& color) {
        auto px = QPixmap(radius * 2, radius * 2);
        px.fill(Qt::transparent);

        { // draw ellipes
            QPainter p(&px);
            p.setBrush(color);
            p.setPen(Qt::NoPen);
            p.setRenderHint(QPainter::Antialiasing, true);
            p.drawEllipse(QRectF(0, 0, px.size().width(), px.size().height()).center(), radius - elevation, radius - elevation);
        }

        QImage tmp(px.size(), QImage::Format_ARGB32_Premultiplied);
        tmp.setDevicePixelRatio(px.devicePixelRatioF());
        tmp.fill(0);
        QPainter tmpPainter(&tmp);
        tmpPainter.setCompositionMode(QPainter::CompositionMode_Source);
        tmpPainter.drawPixmap(QPointF(), px);
        tmpPainter.end();

        // blur the alpha channel
        QImage blurred(tmp.size(), QImage::Format_ARGB32_Premultiplied);
        blurred.setDevicePixelRatio(px.devicePixelRatioF());
        blurred.fill(0);
        {
            QPainter blurPainter(&blurred);
            qt_blurImage(&blurPainter, tmp, elevation * 4., true, false);
        }

        tmp = blurred;

        return QPixmap::fromImage(tmp);
    }

} // namespace Style





class Animator final : public QVariantAnimation {
    Q_OBJECT
    Q_PROPERTY(QObject* targetObject READ targetObject WRITE setTargetObject)

  public:
    Animator(QObject* target, QObject* parent = nullptr);
    ~Animator() override;

    QObject* targetObject() const;
    void setTargetObject(QObject* target);

    inline bool isRunning() const {
        return state() == Running;
    }

  public slots:
    void setup(int duration, QEasingCurve easing = QEasingCurve::Linear);
    void interpolate(const QVariant& start, const QVariant& end);
    void setCurrentValue(const QVariant&);

  protected:
    void updateCurrentValue(const QVariant& value) override final;
    void updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState) override final;

  private:
    QPointer<QObject> target;
};

class SelectionControl : public QAbstractButton {
    Q_OBJECT

  public:
    explicit SelectionControl(QWidget* parent = nullptr);
    ~SelectionControl() override;

    Qt::CheckState checkState() const;

  Q_SIGNALS:
    void stateChanged(int);

  protected:
    void enterEvent(QEvent*) override;
    void checkStateSet() override;
    void nextCheckState() override;
    virtual void toggle(Qt::CheckState state) = 0;
};

class Switch final : public SelectionControl {
    Q_OBJECT

    static constexpr auto CORNER_RADIUS = 8.0;
    static constexpr auto THUMB_RADIUS = 14.5;
    static constexpr auto SHADOW_ELEVATION = 2.0;

  public:
    explicit Switch(QWidget* parent = nullptr);
    Switch(const QString& text, QWidget* parent = nullptr);
    Switch(const QString& text, const QBrush&, QWidget* parent = nullptr);
    ~Switch() override;

    QSize sizeHint() const override final;

  protected:
    void paintEvent(QPaintEvent*) override final;
    void resizeEvent(QResizeEvent*) override final;
    void toggle(Qt::CheckState) override final;

    void init();
    QRect indicatorRect();
    QRect textRect();

    static inline QColor colorFromOpacity(const QColor& c, qreal opacity) {
        return QColor(c.red(), c.green(), c.blue(), qRound(opacity * 255.0));
    }
    static inline bool ltr(QWidget* w) {
        if (nullptr != w)
            return w->layoutDirection() == Qt::LeftToRight;

        return false;
    }

  private:
    Style::Switch style;
    QPixmap shadowPixmap;
    QPointer<Animator> thumbBrushAnimation;
    QPointer<Animator> trackBrushAnimation;
    QPointer<Animator> thumbPosAniamtion;
};




#endif // SWITCHBUTTH_H
