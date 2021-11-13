#ifndef CHOOSEELEMENTTYPEDIALOG_H
#define CHOOSEELEMENTTYPEDIALOG_H

#include <QDialog>
#include <QMetaEnum>
#include <QDebug>

namespace Ui {
class ChooseElementTypeDialog;
class _ElementEnum;
class _DimensionEnum;
class _ToleranceEnum;
class _ConsideringDeformationEunm;
}

class _ElementEnum : public QObject
{
    Q_OBJECT
public:
    _ElementEnum(QObject *parent = nullptr) : QObject(parent){}
    ~_ElementEnum(){}
    enum _ElementFlag{
        link = 0,
        beam = 1
    };
    Q_ENUM(_ElementFlag)
    Q_DECLARE_FLAGS(ElementFlag, _ElementFlag)
    Q_FLAG(ElementFlag)
};
class _DimensionEnum : public QObject
{
    Q_OBJECT
public:
    _DimensionEnum(QObject *parent = nullptr) : QObject(parent){}
    ~_DimensionEnum(){}
    enum _DimensionFlag{
        twoDimension = 0,
        threeDimension = 1
    };
    Q_ENUM(_DimensionFlag)
    Q_DECLARE_FLAGS(DimensionFlag, _DimensionFlag)
    Q_FLAG(DimensionFlag)
};
class _ToleranceEnum : public QObject
{
    Q_OBJECT
public:
    _ToleranceEnum(QObject *parent = nullptr) : QObject(parent){}
    ~_ToleranceEnum(){}

    enum _ToleranceFlag{
        oneOrder = 0,
        twoOrder = 1,
        threeOrder = 2
    };
    Q_ENUM(_ToleranceFlag)
    Q_DECLARE_FLAGS(ToleranceFlag,_ToleranceFlag)
    Q_FLAG(ToleranceFlag)
};
class _ConsideringDeformationEunm : public QObject
{
    Q_OBJECT

public:
    _ConsideringDeformationEunm(QObject *parent = nullptr) : QObject(parent){}
    ~_ConsideringDeformationEunm(){}
    enum _ConsideringDeformationFlag{
        bend = 0,
        shear = 1,
        both = 2
    };
    Q_ENUM(_ConsideringDeformationFlag)
    Q_DECLARE_FLAGS(ConsideringDeformationFlag,_ConsideringDeformationFlag)
    Q_FLAG(ConsideringDeformationFlag)
};

class ChooseElementTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseElementTypeDialog(QWidget *parent = nullptr);
    ~ChooseElementTypeDialog();

private slots:

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_comboBox_3_currentIndexChanged(int index);

    void on_comboBox_4_currentIndexChanged(int index);

private:
    Ui::ChooseElementTypeDialog *ui;
};

#endif // CHOOSEELEMENTTYPE_H
