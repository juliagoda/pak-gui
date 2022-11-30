#pragma once

#include <KStatusNotifierItem>
#include <QObject>


class MainWindow;

class SystemTray : public KStatusNotifierItem
{
    Q_OBJECT

public:
    explicit SystemTray(MainWindow* parent);

public Q_SLOTS:
    void update(int packages_count);

private:
    void setup(QWidget* parent);
};

