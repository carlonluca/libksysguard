#ifndef ENERGY_CORE_H
#define ENERGY_CORE_H

#include <QObject>
#include <QMutex>
#include <QCoreApplication>

#include <kauthaction.h>

class KJob;

class Q_DECL_EXPORT EnergyCore : public QObject
{
    Q_OBJECT
public:
    static EnergyCore* instance() {
        if (!m_instance)
            m_instance = new EnergyCore;
        return m_instance;
    }

    virtual ~EnergyCore();

    double power(int pid);
    QString displayPower(int pid);

signals:
    void dataUpdated();

private slots:
    void actionResult(KJob *kjob);
    void actionNewData(const QVariantMap &data);

private:
    EnergyCore(QObject* parent = nullptr);

private:
    static EnergyCore* m_instance;
    QMutex m_mutex;
    QVariantMap m_energyData;
};

#endif
