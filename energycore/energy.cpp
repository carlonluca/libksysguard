#include <QDebug>

#include <KAuth/KAuth>

#include <climits>

#include "energy.h"

EnergyCore* EnergyCore::m_instance = nullptr;

EnergyCore::EnergyCore(QObject *parent) :
    QObject(parent),
    m_mutex(QMutex::Recursive)
{
    KAuth::Action action(QLatin1String("org.kde.ksysguard.energycorehelper.startmonitoring"));
    action.setHelperId(QStringLiteral("org.kde.ksysguard.energycorehelper"));
    action.setTimeout(std::numeric_limits<int>::max());
    QVariantMap args;
    args[QStringLiteral("filename")] = QStringLiteral("filename");
    action.setArguments(args);
    KAuth::ExecuteJob *job = action.execute();

    connect(job, &KAuth::ExecuteJob::result,
            this, &EnergyCore::actionResult);
    connect(job, &KAuth::ExecuteJob::newData,
             this, &EnergyCore::actionNewData);
    connect(job, &KAuth::ExecuteJob::newData,
            this, &EnergyCore::dataUpdated);
    connect(this, &QObject::destroyed, [job] {
        job->kill(KJob::EmitResult);
        qDebug() << "Stopping";
    });
    job->start();
}

EnergyCore::~EnergyCore()
{
}

double EnergyCore::power(int pid)
{
    QMutexLocker locker(&m_mutex);
    QVariantMap data = m_energyData.value(QString::number(pid)).toMap();
    if (!data.contains(QStringLiteral("value")))
        return -1;
    
    return data.value(QStringLiteral("value")).toDouble();
}

QString EnergyCore::displayPower(int pid)
{
    QMutexLocker locker(&m_mutex);
    QVariantMap data = m_energyData.value(QString::number(pid)).toMap();
    if (!data.contains(QStringLiteral("display")))
        return QString();
    
    return data.value(QStringLiteral("display")).toString();
}

void EnergyCore::actionResult(KJob *kjob)
{
    auto job = qobject_cast<KAuth::ExecuteJob*>(kjob);
    qDebug() << job->error() << job->data();
}

void EnergyCore::actionNewData(const QVariantMap& data)
{
    QMutexLocker locker(&m_mutex);
    qDebug() << "New data:" << data;
    m_energyData = data;
}
