/********************************************************************************
** Form generated from reading UI file 'para_wlop.ui'
**
** Created: Wed Oct 4 15:39:25 2017
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARA_WLOP_H
#define UI_PARA_WLOP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_para_wlop
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *radius;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QDoubleSpinBox *mu;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *iter;
    QLabel *label_3;
    QCheckBox *compute_density;
    QCheckBox *compute_pca;
    QPushButton *anisotropic_lop_apply;
    QPushButton *wlop_apply;

    void setupUi(QWidget *para_wlop)
    {
        if (para_wlop->objectName().isEmpty())
            para_wlop->setObjectName(QString::fromUtf8("para_wlop"));
        para_wlop->resize(293, 458);
        layoutWidget = new QWidget(para_wlop);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 271, 191));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        radius = new QDoubleSpinBox(layoutWidget);
        radius->setObjectName(QString::fromUtf8("radius"));
        radius->setDecimals(5);
        radius->setMinimum(1e-05);
        radius->setMaximum(1000);
        radius->setSingleStep(0.01);
        radius->setValue(1);

        horizontalLayout->addWidget(radius);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_3->addWidget(label_4);

        mu = new QDoubleSpinBox(layoutWidget);
        mu->setObjectName(QString::fromUtf8("mu"));
        mu->setDecimals(5);
        mu->setSingleStep(0.1);

        horizontalLayout_3->addWidget(mu);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        iter = new QSpinBox(layoutWidget);
        iter->setObjectName(QString::fromUtf8("iter"));
        iter->setMaximum(1000);
        iter->setValue(1);

        horizontalLayout_2->addWidget(iter);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);


        verticalLayout->addLayout(horizontalLayout_2);

        compute_density = new QCheckBox(layoutWidget);
        compute_density->setObjectName(QString::fromUtf8("compute_density"));

        verticalLayout->addWidget(compute_density);

        compute_pca = new QCheckBox(layoutWidget);
        compute_pca->setObjectName(QString::fromUtf8("compute_pca"));

        verticalLayout->addWidget(compute_pca);

        anisotropic_lop_apply = new QPushButton(para_wlop);
        anisotropic_lop_apply->setObjectName(QString::fromUtf8("anisotropic_lop_apply"));
        anisotropic_lop_apply->setGeometry(QRect(50, 300, 161, 31));
        wlop_apply = new QPushButton(para_wlop);
        wlop_apply->setObjectName(QString::fromUtf8("wlop_apply"));
        wlop_apply->setGeometry(QRect(30, 240, 209, 31));

        retranslateUi(para_wlop);

        QMetaObject::connectSlotsByName(para_wlop);
    } // setupUi

    void retranslateUi(QWidget *para_wlop)
    {
        para_wlop->setWindowTitle(QApplication::translate("para_wlop", "WLOP parameters setting", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("para_wlop", "Radius:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("para_wlop", "Mu", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("para_wlop", "Iterate ", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("para_wlop", "times", 0, QApplication::UnicodeUTF8));
        compute_density->setText(QApplication::translate("para_wlop", "Compute Density", 0, QApplication::UnicodeUTF8));
        compute_pca->setText(QApplication::translate("para_wlop", "Compute PCA Normal Each Iteration", 0, QApplication::UnicodeUTF8));
        anisotropic_lop_apply->setText(QApplication::translate("para_wlop", "Anisotropic LOP(for EAR)", 0, QApplication::UnicodeUTF8));
        wlop_apply->setText(QApplication::translate("para_wlop", "WLOP", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class para_wlop: public Ui_para_wlop {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARA_WLOP_H
