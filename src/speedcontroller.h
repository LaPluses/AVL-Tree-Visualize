#ifndef SPEEDCONTROLLER_H
#define SPEEDCONTROLLER_H

#include <QObject>
#include <QWidget>
#include <QtMath>

class SpeedController : public QObject
{
    Q_OBJECT

public:
    static SpeedController* getInstance();
    int speed();

public slots:
    void setSpeed(int speed);

private:
    SpeedController();
    static SpeedController *instance;
    int mSpeed;
};

#endif // SPEEDCONTROLLER_H
