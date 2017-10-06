/********************************************************************************
** Form generated from reading UI file 'normal_para.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NORMAL_PARA_H
#define UI_NORMAL_PARA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_normal_paras
{
public:
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *radius;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *KNN;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QDoubleSpinBox *sigma;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpinBox *smooth_normal_interate_num;
    QCheckBox *use_anistropic_PCA;
    QPushButton *normal_smoothing;
    QPushButton *normal_PCA;
    QPushButton *pushButton_reorientate_normal;

    void setupUi(QWidget *normal_paras)
    {
        if (normal_paras->objectName().isEmpty())
            normal_paras->setObjectName(QString::fromUtf8("normal_paras"));
        normal_paras->resize(256, 505);
        groupBox = new QGroupBox(normal_paras);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 231, 171));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        radius = new QDoubleSpinBox(groupBox);
        radius->setObjectName(QString::fromUtf8("radius"));
        radius->setDecimals(5);
        radius->setMinimum(1e-05);
        radius->setMaximum(1000);
        radius->setSingleStep(0.01);
        radius->setValue(1);

        horizontalLayout->addWidget(radius);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        KNN = new QSpinBox(groupBox);
        KNN->setObjectName(QString::fromUtf8("KNN"));
        KNN->setMinimum(1);
        KNN->setMaximum(10000);
        KNN->setValue(6);

        horizontalLayout_2->addWidget(KNN);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        sigma = new QDoubleSpinBox(groupBox);
        sigma->setObjectName(QString::fromUtf8("sigma"));
        sigma->setDecimals(3);
        sigma->setMaximum(180);
        sigma->setValue(20);

        horizontalLayout_3->addWidget(sigma);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        smooth_normal_interate_num = new QSpinBox(groupBox);
        smooth_normal_interate_num->setObjectName(QString::fromUtf8("smooth_normal_interate_num"));
        smooth_normal_interate_num->setMinimum(1);
        smooth_normal_interate_num->setMaximum(100);
        smooth_normal_interate_num->setValue(5);

        horizontalLayout_4->addWidget(smooth_normal_interate_num);


        verticalLayout->addLayout(horizontalLayout_4);

        use_anistropic_PCA = new QCheckBox(groupBox);
        use_anistropic_PCA->setObjectName(QString::fromUtf8("use_anistropic_PCA"));

        verticalLayout->addWidget(use_anistropic_PCA);

        normal_smoothing = new QPushButton(normal_paras);
        normal_smoothing->setObjectName(QString::fromUtf8("normal_smoothing"));
        normal_smoothing->setGeometry(QRect(30, 240, 171, 31));
        normal_PCA = new QPushButton(normal_paras);
        normal_PCA->setObjectName(QString::fromUtf8("normal_PCA"));
        normal_PCA->setGeometry(QRect(30, 190, 171, 31));
        pushButton_reorientate_normal = new QPushButton(normal_paras);
        pushButton_reorientate_normal->setObjectName(QString::fromUtf8("pushButton_reorientate_normal"));
        pushButton_reorientate_normal->setGeometry(QRect(30, 290, 171, 31));

        retranslateUi(normal_paras);

        QMetaObject::connectSlotsByName(normal_paras);
    } // setupUi

    void retranslateUi(QWidget *normal_paras)
    {
        normal_paras->setWindowTitle(QApplication::translate("normal_paras", "normal paras", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("normal_paras", "Smoothing Radius", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("normal_paras", "PCA KNN", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("normal_paras", "Sigma", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("normal_paras", "Iterate Num", 0, QApplication::UnicodeUTF8));
        use_anistropic_PCA->setText(QApplication::translate("normal_paras", " Use Anistropic PCA", 0, QApplication::UnicodeUTF8));
        normal_smoothing->setText(QApplication::translate("normal_paras", "Normal Smoothing", 0, QApplication::UnicodeUTF8));
        normal_PCA->setText(QApplication::translate("normal_paras", "PCA Normal", 0, QApplication::UnicodeUTF8));
        pushButton_reorientate_normal->setText(QApplication::translate("normal_paras", "Reorientate Normal", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class normal_paras: public Ui_normal_paras {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NORMAL_PARA_H
