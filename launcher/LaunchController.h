#pragma once
#include <QObject>
#include <BaseInstance.h>
#include <tools/BaseProfiler.h>

#include "minecraft/launch/MinecraftServerTarget.h"
#include "minecraft/auth/MinecraftAccount.h"
#include "AuthServer.h"

class InstanceWindow;
class LaunchController: public Task
{
    Q_OBJECT
public:
    void executeTask() override;

    LaunchController(QObject * parent = nullptr);
    virtual ~LaunchController(){};

    void setInstance(InstancePtr instance) {
        m_instance = instance;
    }

    InstancePtr instance() {
        return m_instance;
    }

    void setOnline(bool online) {
        m_online = online;
    }

    void setProfiler(BaseProfilerFactory *profiler) {
        m_profiler = profiler;
    }

    void setParentWidget(QWidget * widget) {
        m_parentWidget = widget;
    }

    void setServerToJoin(MinecraftServerTargetPtr serverToJoin) {
        m_serverToJoin = std::move(serverToJoin);
    }

    void setAuthserver(std::shared_ptr<AuthServer> authserver) {
        m_authserver = authserver;
    }

    void setAccountToUse(MinecraftAccountPtr accountToUse) {
        m_accountToUse = std::move(accountToUse);
    }

    QString id()
    {
        return m_instance->id();
    }

    bool abort() override;

private:
    void login();
    void launchInstance();
    void decideAccount();

private slots:
    void readyForLaunch();

    void onSucceeded();
    void onFailed(QString reason);
    void onProgressRequested(Task *task);

private:
    BaseProfilerFactory *m_profiler = nullptr;
    bool m_online = true;
    InstancePtr m_instance;
    QWidget * m_parentWidget = nullptr;
    InstanceWindow *m_console = nullptr;
    MinecraftAccountPtr m_accountToUse = nullptr;
    AuthSessionPtr m_session;
    shared_qobject_ptr<LaunchTask> m_launcher;
    MinecraftServerTargetPtr m_serverToJoin;
    std::shared_ptr<AuthServer> m_authserver;
};
