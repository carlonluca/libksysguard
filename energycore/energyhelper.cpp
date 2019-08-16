#include <QDebug>
#include <QCoreApplication>

#define CONF_LIB
#include <lib.h>
#undef CONF_LIB

#include "energyhelper.h"

void log_function(const char* format, ...)
{
  va_list a_list;
  va_start(a_list, format);

  QString log_string = QString().vsprintf(format, a_list);
  qDebug(qPrintable(log_string));

  va_end(a_list);
}

void data_ready_cb(vector<power_consumer*> data)
{
  qDebug("Data ready cb");
  QVariantMap map;
  for(size_t i = 0, l = data.size(); i < l; ++i) {
    if (process* p = dynamic_cast<process*>(data[i])) {
      char power[16];
      format_watts(p->Witts(), power, 10);
      qDebug("%s %s %f %s [%d] %s", p->name(), p->type(), p->usage(), power, p->pid, p->desc);
      map.insert(QString::number(p->pid), QVariantMap {
        { QStringLiteral("value"), p->Witts() },
        { QStringLiteral("display"), QString::fromUtf8(power) }
      });
    }
  }

  HelperSupport::progressStep(map);
}

KSysGuardEnergyCoreHelper::KSysGuardEnergyCoreHelper(QObject *parent) :
  QObject(parent)
{
  init_powertop_lib(&log_function, &data_ready_cb);
}

ActionReply KSysGuardEnergyCoreHelper::startmonitoring(const QVariantMap& args)
{
  main_loop(1, reinterpret_cast<char**>(const_cast<char*>("powertop")), []() -> bool {
    bool isStopped = HelperSupport::isStopped();
    qDebug() << "isStopped" << isStopped;
    return isStopped;
  });
  
  qDebug() << "DONE";

  // This helper is supposed to live thoughout the entire life of the caller, so
  // if this action is stopped, assume the app is about to exit and then suicide.
  qApp->quit();

  return ActionReply::SuccessReply();
}

ActionReply KSysGuardEnergyCoreHelper::stopmonitoring()
{
  return ActionReply::SuccessReply();
}

KAUTH_HELPER_MAIN("org.kde.ksysguard.energycorehelper", KSysGuardEnergyCoreHelper)
