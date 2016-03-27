#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>
#include <qcustomplot.h>

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphWindow(QWidget *parent = 0);
    ~GraphWindow();

private slots:

    void on_zoomin_clicked();

    void on_zoomout_clicked();


private:
    Ui::GraphWindow *ui;
};

#endif // GRAPHWINDOW_H
