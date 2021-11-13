#include "ChooseElementTypeDialog.h"
#include "ui_ChooseElementTypeDialog.h"
#include <QCoreApplication>
#include <QDebug>
#include <QMetaEnum>

using namespace std;

ChooseElementTypeDialog::ChooseElementTypeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseElementTypeDialog)
{
    ui->setupUi(this);
}

ChooseElementTypeDialog::~ChooseElementTypeDialog()
{
    delete ui;
}

void ChooseElementTypeDialog::on_comboBox_currentIndexChanged(int index)
{
    QMetaEnum elementFlag_ME = QMetaEnum::fromType<_ElementEnum::ElementFlag>();
    if(elementFlag_ME.isValid())
    {
        qDebug() << "isValid()yes";
        qDebug() << elementFlag_ME.enumName();
        qDebug() << elementFlag_ME.name();
        qDebug() << elementFlag_ME.scope();
        qDebug() << elementFlag_ME.value(index);
        qDebug() << elementFlag_ME.key(index);
        if(elementFlag_ME.isFlag())
        {
            qDebug() << "isFlag()yes";
        }
        else
        {
            qDebug() << "isFlag()no";
        }
    }
    else
    {
        qDebug() << "no";
    }
}

void ChooseElementTypeDialog::on_comboBox_2_currentIndexChanged(int index)
{
    QMetaEnum dimensionFlag_ME = QMetaEnum::fromType<_DimensionEnum::DimensionFlag>();
    if(dimensionFlag_ME.isValid())
    {
        qDebug() << "yes";
        qDebug() << dimensionFlag_ME.enumName();
        qDebug() << dimensionFlag_ME.name();
        qDebug() << dimensionFlag_ME.scope();
        qDebug() << dimensionFlag_ME.value(index);
        qDebug() << dimensionFlag_ME.key(index);
    }
    else
    {
        qDebug() << "no";
    }
}


void ChooseElementTypeDialog::on_comboBox_3_currentIndexChanged(int index)
{
    QMetaEnum ToleranceFlag_ME = QMetaEnum::fromType<_ToleranceEnum::ToleranceFlag>();
    if(ToleranceFlag_ME.isValid())
    {
        qDebug() << "yes";
        qDebug() << ToleranceFlag_ME.enumName();
        qDebug() << ToleranceFlag_ME.name();
        qDebug() << ToleranceFlag_ME.scope();
        qDebug() << ToleranceFlag_ME.value(index);
        qDebug() << ToleranceFlag_ME.key(index);
    }
    else
    {
        qDebug() << "no";
    }
}


void ChooseElementTypeDialog::on_comboBox_4_currentIndexChanged(int index)
{
    QMetaEnum consideringDeforationFlag_ME = QMetaEnum::fromType<_ConsideringDeformationEunm::ConsideringDeformationFlag>();
    if(consideringDeforationFlag_ME.isValid())
    {
        qDebug() << "yes";
        qDebug() << consideringDeforationFlag_ME.enumName();
        qDebug() << consideringDeforationFlag_ME.name();
        qDebug() << consideringDeforationFlag_ME.scope();
        qDebug() << consideringDeforationFlag_ME.value(index);
        qDebug() << consideringDeforationFlag_ME.key(index);
    }
    else
    {
        qDebug() << "no";
    }
}

