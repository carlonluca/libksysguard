#include <kauth.h>

using namespace KAuth;

class KSysGuardEnergyCoreHelper : public QObject
{
    Q_OBJECT
public:
    KSysGuardEnergyCoreHelper(QObject* parent = nullptr);

public Q_SLOTS:
    ActionReply startmonitoring(const QVariantMap &args);
    ActionReply stopmonitoring();
};
