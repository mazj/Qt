#include <QtGui>
#include <QtWidgets>

class ColorMaker : public QObject
{
    Q_OBJECT
    Q_ENUMS(GenerateAlgorithm)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor timeColor READ timeColor)

public:
    ColorMaker(QObject *parent = 0);
    ~ColorMaker();

    enum GenerateAlgorithm {
            RandomRGB,
            RandomRed,
            RandomGreen,
            RandomBlue,
            LinearIncrease
        };

    QColor color() const;
    void setColor(const QColor& c);

    QColor timeColor() const;

    Q_INVOKABLE GenerateAlgorithm algorithm() const;
    Q_INVOKABLE void setAlgorithm(GenerateAlgorithm algorithm);

signals:
    void colorChanged(const QColor & color);
    void currentTime(const QString &strTime);

public slots:
    void start();
    void stop();

signals:
    void colorChanged( const QColor& c );

private:
    GenerateAlgorithm m_algorithm;
    QColor m_currentColor;
    int m_nColorTimer;
};
