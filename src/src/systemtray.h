#pragma once

#include <KStatusNotifierItem>
#include <QObject>


class MainWindow;

class SystemTray : public KStatusNotifierItem
{
    Q_OBJECT

public:
    explicit SystemTray(MainWindow* parent);
    ~SystemTray() override = default;

public Q_SLOTS:
    void update(uint packages_count);

protected:
    void changeStatusToDefault();

private:
    void setup(QWidget* parent);
};

