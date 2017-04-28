#ifndef COMBOSTATUSPANEL_H
#define COMBOSTATUSPANEL_H

#include <QDockWidget>

namespace Ui {
class ComboStatusPanel;
}

class ComboStatusPanel : public QDockWidget {
    Q_OBJECT

  public:
    explicit ComboStatusPanel(QWidget *parent = 0);
    ~ComboStatusPanel();

  private:
    Ui::ComboStatusPanel *ui;

  public slots:
    void SetTransmission();
    void SetReflection();
    void SetDigitizer();
    void SetNetworkAnalyzer();
    void SetIterationNumber( uint iteration );
    void SetCavityLength( double current_length );

};

#endif // COMBOSTATUSPANEL_H
