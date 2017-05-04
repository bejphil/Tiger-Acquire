#include "combostatuspanel.h"
#include "ui_combostatuspanel.h"

ComboStatusPanel::ComboStatusPanel(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::ComboStatusPanel) {
    ui->setupUi(this);

}

ComboStatusPanel::~ComboStatusPanel() {
    delete ui;
}

void ComboStatusPanel::SetTransmission() {
    ui->reflectionBox->setChecked( false );
    ui->transmissionBox->setChecked( true );
}

void ComboStatusPanel::SetReflection() {
    ui->reflectionBox->setChecked( true );
    ui->transmissionBox->setChecked( false );
}

void ComboStatusPanel::SetDigitizer() {
    ui->digitizerBox->setChecked( true );
    ui->networkAnalyzerBox->setChecked( false );

}

void ComboStatusPanel::SetNetworkAnalyzer() {
    ui->digitizerBox->setChecked( false );
    ui->networkAnalyzerBox->setChecked( true );
}

void ComboStatusPanel::SetIterationNumber( uint iteration ) {
    ui->iterNumberLCD->display( QString::number(iteration) );
}

void ComboStatusPanel::SetCavityLength( double current_length ) {
    ui->cavLengthLCD->display( QString::number(current_length) );
}

void ComboStatusPanel::SetLOFrequency( double lo_frequency ) {
    ui->LOLCD->display( QString::number(lo_frequency) );
}
