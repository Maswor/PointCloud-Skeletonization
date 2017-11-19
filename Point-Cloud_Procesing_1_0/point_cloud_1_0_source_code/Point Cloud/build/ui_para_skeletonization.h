/********************************************************************************
** Form generated from reading UI file 'para_skeletonization.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARA_SKELETONIZATION_H
#define UI_PARA_SKELETONIZATION_H

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
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_para_skeleton
{
public:
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QGroupBox *groupBox_5;
    QPushButton *skeleton_initial_sampling;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_69;
    QLabel *label_71;
    QDoubleSpinBox *skeleton_initial_radius;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_12;
    QDoubleSpinBox *skeleton_Radius_Growing_Speed;
    QHBoxLayout *horizontalLayout_70;
    QLabel *label_72;
    QDoubleSpinBox *skeleton_mu;
    QHBoxLayout *horizontalLayout_31;
    QLabel *label_30;
    QDoubleSpinBox *skeleton_downsample_num;
    QPushButton *skeleton_full_auto;
    QWidget *tab_4;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *radius;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_8;
    QDoubleSpinBox *local_density_radius;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_16;
    QDoubleSpinBox *Stop_And_Grow_Error;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_17;
    QDoubleSpinBox *Max_Iterate_Time;
    QCheckBox *compute_density_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *Auto_Wlop_One_Step;
    QSpinBox *iter_click_num;
    QLabel *label_4;
    QPushButton *skeleton_run_until_growth;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_24;
    QDoubleSpinBox *wlop_sigma_knn;
    QHBoxLayout *horizontalLayout_53;
    QLabel *label_51;
    QDoubleSpinBox *PCA_Threshold;
    QHBoxLayout *horizontalLayout_27;
    QLabel *label_26;
    QDoubleSpinBox *wlop_branch_search_sigma;
    QHBoxLayout *horizontalLayout_26;
    QLabel *label_25;
    QDoubleSpinBox *wlop_accept_branch_size;
    QHBoxLayout *horizontalLayout_71;
    QLabel *label_73;
    QDoubleSpinBox *wlop_follow_sample_radius_2;
    QHBoxLayout *horizontalLayout_55;
    QLabel *label_53;
    QDoubleSpinBox *wlop_branch_merge_dist;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_23;
    QDoubleSpinBox *wlop_combine_too_close;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_58;
    QDoubleSpinBox *Fix_original_weight_3;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_61;
    QLabel *label_59;
    QDoubleSpinBox *wlop_segment_length;
    QPushButton *wlop_run_all_segment;
    QCheckBox *need_refinement;
    QPushButton *Step3_Clean_And_Update_Radius;
    QPushButton *Detect_Feature;
    QPushButton *step2_search_branch;
    QWidget *tab_5;
    QWidget *layoutWidget_9;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_22;
    QDoubleSpinBox *wlop_branch_search_max_dist2;
    QWidget *layoutWidget_8;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_21;
    QDoubleSpinBox *wlop_branch_search_max_dist;
    QWidget *layoutWidget_30;
    QHBoxLayout *horizontalLayout_56;
    QLabel *label_54;
    QDoubleSpinBox *wlop_clean_near_branch_dist;
    QWidget *layoutWidget_37;
    QHBoxLayout *horizontalLayout_62;
    QLabel *label_60;
    QDoubleSpinBox *wlop_combine_angle;
    QWidget *layoutWidget_38;
    QHBoxLayout *horizontalLayout_63;
    QLabel *label_61;
    QDoubleSpinBox *wlop_follow_sample_radius;
    QWidget *layoutWidget_41;
    QHBoxLayout *horizontalLayout_66;
    QLabel *label_64;
    QDoubleSpinBox *wlop_follow_sample_angle;
    QWidget *layoutWidget_42;
    QHBoxLayout *horizontalLayout_67;
    QLabel *label_69;
    QDoubleSpinBox *wlop_grow_accept_sigma;
    QWidget *layoutWidget_43;
    QHBoxLayout *horizontalLayout_68;
    QLabel *label_70;
    QDoubleSpinBox *wlop_keep_virtual_angle;

    void setupUi(QWidget *para_skeleton)
    {
        if (para_skeleton->objectName().isEmpty())
            para_skeleton->setObjectName(QString::fromUtf8("para_skeleton"));
        para_skeleton->resize(373, 861);
        tabWidget = new QTabWidget(para_skeleton);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 0, 351, 831));
        QFont font;
        font.setPointSize(9);
        tabWidget->setFont(font);
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        groupBox_5 = new QGroupBox(tab_3);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(20, 10, 311, 191));
        skeleton_initial_sampling = new QPushButton(groupBox_5);
        skeleton_initial_sampling->setObjectName(QString::fromUtf8("skeleton_initial_sampling"));
        skeleton_initial_sampling->setGeometry(QRect(50, 150, 211, 31));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        skeleton_initial_sampling->setFont(font1);
        skeleton_initial_sampling->setAutoDefault(false);
        layoutWidget = new QWidget(groupBox_5);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 291, 131));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_69 = new QHBoxLayout();
        horizontalLayout_69->setObjectName(QString::fromUtf8("horizontalLayout_69"));
        label_71 = new QLabel(layoutWidget);
        label_71->setObjectName(QString::fromUtf8("label_71"));
        label_71->setFrameShape(QFrame::NoFrame);
        label_71->setFrameShadow(QFrame::Plain);
        label_71->setLineWidth(0);
        label_71->setScaledContents(true);
        label_71->setWordWrap(false);

        horizontalLayout_69->addWidget(label_71);

        skeleton_initial_radius = new QDoubleSpinBox(layoutWidget);
        skeleton_initial_radius->setObjectName(QString::fromUtf8("skeleton_initial_radius"));
        skeleton_initial_radius->setDecimals(4);
        skeleton_initial_radius->setMaximum(1000);
        skeleton_initial_radius->setSingleStep(0.1);
        skeleton_initial_radius->setValue(1);

        horizontalLayout_69->addWidget(skeleton_initial_radius);


        verticalLayout_2->addLayout(horizontalLayout_69);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_13->addWidget(label_12);

        skeleton_Radius_Growing_Speed = new QDoubleSpinBox(layoutWidget);
        skeleton_Radius_Growing_Speed->setObjectName(QString::fromUtf8("skeleton_Radius_Growing_Speed"));
        skeleton_Radius_Growing_Speed->setDecimals(4);
        skeleton_Radius_Growing_Speed->setMaximum(1000);
        skeleton_Radius_Growing_Speed->setSingleStep(0.1);
        skeleton_Radius_Growing_Speed->setValue(1);

        horizontalLayout_13->addWidget(skeleton_Radius_Growing_Speed);


        verticalLayout_2->addLayout(horizontalLayout_13);

        horizontalLayout_70 = new QHBoxLayout();
        horizontalLayout_70->setObjectName(QString::fromUtf8("horizontalLayout_70"));
        label_72 = new QLabel(layoutWidget);
        label_72->setObjectName(QString::fromUtf8("label_72"));

        horizontalLayout_70->addWidget(label_72);

        skeleton_mu = new QDoubleSpinBox(layoutWidget);
        skeleton_mu->setObjectName(QString::fromUtf8("skeleton_mu"));
        skeleton_mu->setDecimals(5);
        skeleton_mu->setSingleStep(0.1);

        horizontalLayout_70->addWidget(skeleton_mu);


        verticalLayout_2->addLayout(horizontalLayout_70);

        horizontalLayout_31 = new QHBoxLayout();
        horizontalLayout_31->setObjectName(QString::fromUtf8("horizontalLayout_31"));
        label_30 = new QLabel(layoutWidget);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        horizontalLayout_31->addWidget(label_30);

        skeleton_downsample_num = new QDoubleSpinBox(layoutWidget);
        skeleton_downsample_num->setObjectName(QString::fromUtf8("skeleton_downsample_num"));
        skeleton_downsample_num->setDecimals(4);
        skeleton_downsample_num->setMaximum(10000);
        skeleton_downsample_num->setSingleStep(0.1);
        skeleton_downsample_num->setValue(1);

        horizontalLayout_31->addWidget(skeleton_downsample_num);


        verticalLayout_2->addLayout(horizontalLayout_31);

        skeleton_full_auto = new QPushButton(tab_3);
        skeleton_full_auto->setObjectName(QString::fromUtf8("skeleton_full_auto"));
        skeleton_full_auto->setGeometry(QRect(110, 230, 131, 61));
        QFont font2;
        font2.setPointSize(25);
        font2.setBold(true);
        font2.setWeight(75);
        skeleton_full_auto->setFont(font2);
        skeleton_full_auto->setIconSize(QSize(32, 32));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        layoutWidget1 = new QWidget(tab_4);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 30, 321, 218));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(layoutWidget1);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        radius = new QDoubleSpinBox(layoutWidget1);
        radius->setObjectName(QString::fromUtf8("radius"));
        radius->setDecimals(5);
        radius->setMinimum(1e-05);
        radius->setMaximum(1000);
        radius->setSingleStep(0.01);
        radius->setValue(1);

        horizontalLayout->addWidget(radius);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_8 = new QLabel(layoutWidget1);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_9->addWidget(label_8);

        local_density_radius = new QDoubleSpinBox(layoutWidget1);
        local_density_radius->setObjectName(QString::fromUtf8("local_density_radius"));
        local_density_radius->setDecimals(4);
        local_density_radius->setMaximum(1000);
        local_density_radius->setSingleStep(0.1);
        local_density_radius->setValue(1);

        horizontalLayout_9->addWidget(local_density_radius);


        verticalLayout_3->addLayout(horizontalLayout_9);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        label_16 = new QLabel(layoutWidget1);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        horizontalLayout_17->addWidget(label_16);

        Stop_And_Grow_Error = new QDoubleSpinBox(layoutWidget1);
        Stop_And_Grow_Error->setObjectName(QString::fromUtf8("Stop_And_Grow_Error"));
        Stop_And_Grow_Error->setDecimals(7);
        Stop_And_Grow_Error->setMinimum(1e-06);
        Stop_And_Grow_Error->setMaximum(1000);
        Stop_And_Grow_Error->setSingleStep(0.1);
        Stop_And_Grow_Error->setValue(1e-06);

        horizontalLayout_17->addWidget(Stop_And_Grow_Error);


        verticalLayout_3->addLayout(horizontalLayout_17);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        label_17 = new QLabel(layoutWidget1);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        horizontalLayout_18->addWidget(label_17);

        Max_Iterate_Time = new QDoubleSpinBox(layoutWidget1);
        Max_Iterate_Time->setObjectName(QString::fromUtf8("Max_Iterate_Time"));
        Max_Iterate_Time->setDecimals(4);
        Max_Iterate_Time->setMaximum(1000);
        Max_Iterate_Time->setSingleStep(0.1);
        Max_Iterate_Time->setValue(1);

        horizontalLayout_18->addWidget(Max_Iterate_Time);


        verticalLayout_3->addLayout(horizontalLayout_18);

        compute_density_2 = new QCheckBox(layoutWidget1);
        compute_density_2->setObjectName(QString::fromUtf8("compute_density_2"));

        verticalLayout_3->addWidget(compute_density_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        Auto_Wlop_One_Step = new QPushButton(layoutWidget1);
        Auto_Wlop_One_Step->setObjectName(QString::fromUtf8("Auto_Wlop_One_Step"));

        horizontalLayout_3->addWidget(Auto_Wlop_One_Step);

        iter_click_num = new QSpinBox(layoutWidget1);
        iter_click_num->setObjectName(QString::fromUtf8("iter_click_num"));
        iter_click_num->setMaximum(1000);
        iter_click_num->setValue(1);

        horizontalLayout_3->addWidget(iter_click_num);

        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_3->addWidget(label_4);


        verticalLayout_3->addLayout(horizontalLayout_3);

        skeleton_run_until_growth = new QPushButton(layoutWidget1);
        skeleton_run_until_growth->setObjectName(QString::fromUtf8("skeleton_run_until_growth"));

        verticalLayout_3->addWidget(skeleton_run_until_growth);

        layoutWidget2 = new QWidget(tab_4);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 250, 321, 261));
        verticalLayout_4 = new QVBoxLayout(layoutWidget2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        label_24 = new QLabel(layoutWidget2);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        horizontalLayout_25->addWidget(label_24);

        wlop_sigma_knn = new QDoubleSpinBox(layoutWidget2);
        wlop_sigma_knn->setObjectName(QString::fromUtf8("wlop_sigma_knn"));
        wlop_sigma_knn->setDecimals(4);
        wlop_sigma_knn->setMaximum(1000);
        wlop_sigma_knn->setSingleStep(0.1);
        wlop_sigma_knn->setValue(1);

        horizontalLayout_25->addWidget(wlop_sigma_knn);


        verticalLayout_4->addLayout(horizontalLayout_25);

        horizontalLayout_53 = new QHBoxLayout();
        horizontalLayout_53->setObjectName(QString::fromUtf8("horizontalLayout_53"));
        label_51 = new QLabel(layoutWidget2);
        label_51->setObjectName(QString::fromUtf8("label_51"));

        horizontalLayout_53->addWidget(label_51);

        PCA_Threshold = new QDoubleSpinBox(layoutWidget2);
        PCA_Threshold->setObjectName(QString::fromUtf8("PCA_Threshold"));
        PCA_Threshold->setDecimals(4);
        PCA_Threshold->setMaximum(1000);
        PCA_Threshold->setSingleStep(0.1);
        PCA_Threshold->setValue(1);

        horizontalLayout_53->addWidget(PCA_Threshold);


        verticalLayout_4->addLayout(horizontalLayout_53);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        label_26 = new QLabel(layoutWidget2);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        horizontalLayout_27->addWidget(label_26);

        wlop_branch_search_sigma = new QDoubleSpinBox(layoutWidget2);
        wlop_branch_search_sigma->setObjectName(QString::fromUtf8("wlop_branch_search_sigma"));
        wlop_branch_search_sigma->setDecimals(4);
        wlop_branch_search_sigma->setMaximum(1000);
        wlop_branch_search_sigma->setSingleStep(0.1);
        wlop_branch_search_sigma->setValue(1);

        horizontalLayout_27->addWidget(wlop_branch_search_sigma);


        verticalLayout_4->addLayout(horizontalLayout_27);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        label_25 = new QLabel(layoutWidget2);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        horizontalLayout_26->addWidget(label_25);

        wlop_accept_branch_size = new QDoubleSpinBox(layoutWidget2);
        wlop_accept_branch_size->setObjectName(QString::fromUtf8("wlop_accept_branch_size"));
        wlop_accept_branch_size->setDecimals(4);
        wlop_accept_branch_size->setMaximum(1000);
        wlop_accept_branch_size->setSingleStep(0.1);
        wlop_accept_branch_size->setValue(1);

        horizontalLayout_26->addWidget(wlop_accept_branch_size);


        verticalLayout_4->addLayout(horizontalLayout_26);

        horizontalLayout_71 = new QHBoxLayout();
        horizontalLayout_71->setObjectName(QString::fromUtf8("horizontalLayout_71"));
        label_73 = new QLabel(layoutWidget2);
        label_73->setObjectName(QString::fromUtf8("label_73"));

        horizontalLayout_71->addWidget(label_73);

        wlop_follow_sample_radius_2 = new QDoubleSpinBox(layoutWidget2);
        wlop_follow_sample_radius_2->setObjectName(QString::fromUtf8("wlop_follow_sample_radius_2"));
        wlop_follow_sample_radius_2->setDecimals(4);
        wlop_follow_sample_radius_2->setMaximum(1000);
        wlop_follow_sample_radius_2->setSingleStep(0.1);
        wlop_follow_sample_radius_2->setValue(1);

        horizontalLayout_71->addWidget(wlop_follow_sample_radius_2);


        verticalLayout_4->addLayout(horizontalLayout_71);

        horizontalLayout_55 = new QHBoxLayout();
        horizontalLayout_55->setObjectName(QString::fromUtf8("horizontalLayout_55"));
        label_53 = new QLabel(layoutWidget2);
        label_53->setObjectName(QString::fromUtf8("label_53"));

        horizontalLayout_55->addWidget(label_53);

        wlop_branch_merge_dist = new QDoubleSpinBox(layoutWidget2);
        wlop_branch_merge_dist->setObjectName(QString::fromUtf8("wlop_branch_merge_dist"));
        wlop_branch_merge_dist->setDecimals(4);
        wlop_branch_merge_dist->setMaximum(1000);
        wlop_branch_merge_dist->setSingleStep(0.1);
        wlop_branch_merge_dist->setValue(1);

        horizontalLayout_55->addWidget(wlop_branch_merge_dist);


        verticalLayout_4->addLayout(horizontalLayout_55);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        label_23 = new QLabel(layoutWidget2);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        horizontalLayout_24->addWidget(label_23);

        wlop_combine_too_close = new QDoubleSpinBox(layoutWidget2);
        wlop_combine_too_close->setObjectName(QString::fromUtf8("wlop_combine_too_close"));
        wlop_combine_too_close->setDecimals(4);
        wlop_combine_too_close->setMaximum(1000);
        wlop_combine_too_close->setSingleStep(0.1);
        wlop_combine_too_close->setValue(1);

        horizontalLayout_24->addWidget(wlop_combine_too_close);


        verticalLayout_4->addLayout(horizontalLayout_24);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_58 = new QLabel(layoutWidget2);
        label_58->setObjectName(QString::fromUtf8("label_58"));

        horizontalLayout_6->addWidget(label_58);

        Fix_original_weight_3 = new QDoubleSpinBox(layoutWidget2);
        Fix_original_weight_3->setObjectName(QString::fromUtf8("Fix_original_weight_3"));
        Fix_original_weight_3->setDecimals(4);
        Fix_original_weight_3->setMaximum(1000);
        Fix_original_weight_3->setSingleStep(0.1);
        Fix_original_weight_3->setValue(1);

        horizontalLayout_6->addWidget(Fix_original_weight_3);


        verticalLayout_4->addLayout(horizontalLayout_6);

        layoutWidget3 = new QWidget(tab_4);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 530, 321, 61));
        verticalLayout_5 = new QVBoxLayout(layoutWidget3);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_61 = new QHBoxLayout();
        horizontalLayout_61->setObjectName(QString::fromUtf8("horizontalLayout_61"));
        label_59 = new QLabel(layoutWidget3);
        label_59->setObjectName(QString::fromUtf8("label_59"));

        horizontalLayout_61->addWidget(label_59);

        wlop_segment_length = new QDoubleSpinBox(layoutWidget3);
        wlop_segment_length->setObjectName(QString::fromUtf8("wlop_segment_length"));
        wlop_segment_length->setDecimals(4);
        wlop_segment_length->setMaximum(1000);
        wlop_segment_length->setSingleStep(0.1);
        wlop_segment_length->setValue(1);

        horizontalLayout_61->addWidget(wlop_segment_length);


        verticalLayout_5->addLayout(horizontalLayout_61);

        wlop_run_all_segment = new QPushButton(layoutWidget3);
        wlop_run_all_segment->setObjectName(QString::fromUtf8("wlop_run_all_segment"));

        verticalLayout_5->addWidget(wlop_run_all_segment);

        need_refinement = new QCheckBox(tab_4);
        need_refinement->setObjectName(QString::fromUtf8("need_refinement"));
        need_refinement->setGeometry(QRect(10, 590, 309, 16));
        Step3_Clean_And_Update_Radius = new QPushButton(tab_4);
        Step3_Clean_And_Update_Radius->setObjectName(QString::fromUtf8("Step3_Clean_And_Update_Radius"));
        Step3_Clean_And_Update_Radius->setGeometry(QRect(60, 680, 191, 23));
        Detect_Feature = new QPushButton(tab_4);
        Detect_Feature->setObjectName(QString::fromUtf8("Detect_Feature"));
        Detect_Feature->setGeometry(QRect(60, 620, 191, 23));
        step2_search_branch = new QPushButton(tab_4);
        step2_search_branch->setObjectName(QString::fromUtf8("step2_search_branch"));
        step2_search_branch->setGeometry(QRect(60, 650, 191, 23));
        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        layoutWidget_9 = new QWidget(tab_5);
        layoutWidget_9->setObjectName(QString::fromUtf8("layoutWidget_9"));
        layoutWidget_9->setGeometry(QRect(50, 110, 258, 34));
        horizontalLayout_23 = new QHBoxLayout(layoutWidget_9);
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        horizontalLayout_23->setContentsMargins(0, 0, 0, 0);
        label_22 = new QLabel(layoutWidget_9);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        horizontalLayout_23->addWidget(label_22);

        wlop_branch_search_max_dist2 = new QDoubleSpinBox(layoutWidget_9);
        wlop_branch_search_max_dist2->setObjectName(QString::fromUtf8("wlop_branch_search_max_dist2"));
        wlop_branch_search_max_dist2->setDecimals(4);
        wlop_branch_search_max_dist2->setMaximum(1000);
        wlop_branch_search_max_dist2->setSingleStep(0.1);
        wlop_branch_search_max_dist2->setValue(1);

        horizontalLayout_23->addWidget(wlop_branch_search_max_dist2);

        layoutWidget_8 = new QWidget(tab_5);
        layoutWidget_8->setObjectName(QString::fromUtf8("layoutWidget_8"));
        layoutWidget_8->setGeometry(QRect(50, 180, 258, 34));
        horizontalLayout_22 = new QHBoxLayout(layoutWidget_8);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        horizontalLayout_22->setContentsMargins(0, 0, 0, 0);
        label_21 = new QLabel(layoutWidget_8);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        horizontalLayout_22->addWidget(label_21);

        wlop_branch_search_max_dist = new QDoubleSpinBox(layoutWidget_8);
        wlop_branch_search_max_dist->setObjectName(QString::fromUtf8("wlop_branch_search_max_dist"));
        wlop_branch_search_max_dist->setDecimals(4);
        wlop_branch_search_max_dist->setMaximum(1000);
        wlop_branch_search_max_dist->setSingleStep(0.1);
        wlop_branch_search_max_dist->setValue(1);

        horizontalLayout_22->addWidget(wlop_branch_search_max_dist);

        layoutWidget_30 = new QWidget(tab_5);
        layoutWidget_30->setObjectName(QString::fromUtf8("layoutWidget_30"));
        layoutWidget_30->setGeometry(QRect(50, 140, 274, 34));
        horizontalLayout_56 = new QHBoxLayout(layoutWidget_30);
        horizontalLayout_56->setObjectName(QString::fromUtf8("horizontalLayout_56"));
        horizontalLayout_56->setContentsMargins(0, 0, 0, 0);
        label_54 = new QLabel(layoutWidget_30);
        label_54->setObjectName(QString::fromUtf8("label_54"));

        horizontalLayout_56->addWidget(label_54);

        wlop_clean_near_branch_dist = new QDoubleSpinBox(layoutWidget_30);
        wlop_clean_near_branch_dist->setObjectName(QString::fromUtf8("wlop_clean_near_branch_dist"));
        wlop_clean_near_branch_dist->setDecimals(4);
        wlop_clean_near_branch_dist->setMaximum(1000);
        wlop_clean_near_branch_dist->setSingleStep(0.1);
        wlop_clean_near_branch_dist->setValue(1);

        horizontalLayout_56->addWidget(wlop_clean_near_branch_dist);

        layoutWidget_37 = new QWidget(tab_5);
        layoutWidget_37->setObjectName(QString::fromUtf8("layoutWidget_37"));
        layoutWidget_37->setGeometry(QRect(50, 210, 251, 34));
        horizontalLayout_62 = new QHBoxLayout(layoutWidget_37);
        horizontalLayout_62->setObjectName(QString::fromUtf8("horizontalLayout_62"));
        horizontalLayout_62->setContentsMargins(0, 0, 0, 0);
        label_60 = new QLabel(layoutWidget_37);
        label_60->setObjectName(QString::fromUtf8("label_60"));

        horizontalLayout_62->addWidget(label_60);

        wlop_combine_angle = new QDoubleSpinBox(layoutWidget_37);
        wlop_combine_angle->setObjectName(QString::fromUtf8("wlop_combine_angle"));
        wlop_combine_angle->setDecimals(4);
        wlop_combine_angle->setMaximum(1000);
        wlop_combine_angle->setSingleStep(0.1);
        wlop_combine_angle->setValue(1);

        horizontalLayout_62->addWidget(wlop_combine_angle);

        layoutWidget_38 = new QWidget(tab_5);
        layoutWidget_38->setObjectName(QString::fromUtf8("layoutWidget_38"));
        layoutWidget_38->setGeometry(QRect(50, 240, 266, 34));
        horizontalLayout_63 = new QHBoxLayout(layoutWidget_38);
        horizontalLayout_63->setObjectName(QString::fromUtf8("horizontalLayout_63"));
        horizontalLayout_63->setContentsMargins(0, 0, 0, 0);
        label_61 = new QLabel(layoutWidget_38);
        label_61->setObjectName(QString::fromUtf8("label_61"));

        horizontalLayout_63->addWidget(label_61);

        wlop_follow_sample_radius = new QDoubleSpinBox(layoutWidget_38);
        wlop_follow_sample_radius->setObjectName(QString::fromUtf8("wlop_follow_sample_radius"));
        wlop_follow_sample_radius->setDecimals(4);
        wlop_follow_sample_radius->setMaximum(1000);
        wlop_follow_sample_radius->setSingleStep(0.1);
        wlop_follow_sample_radius->setValue(1);

        horizontalLayout_63->addWidget(wlop_follow_sample_radius);

        layoutWidget_41 = new QWidget(tab_5);
        layoutWidget_41->setObjectName(QString::fromUtf8("layoutWidget_41"));
        layoutWidget_41->setGeometry(QRect(50, 280, 261, 34));
        horizontalLayout_66 = new QHBoxLayout(layoutWidget_41);
        horizontalLayout_66->setObjectName(QString::fromUtf8("horizontalLayout_66"));
        horizontalLayout_66->setContentsMargins(0, 0, 0, 0);
        label_64 = new QLabel(layoutWidget_41);
        label_64->setObjectName(QString::fromUtf8("label_64"));

        horizontalLayout_66->addWidget(label_64);

        wlop_follow_sample_angle = new QDoubleSpinBox(layoutWidget_41);
        wlop_follow_sample_angle->setObjectName(QString::fromUtf8("wlop_follow_sample_angle"));
        wlop_follow_sample_angle->setDecimals(4);
        wlop_follow_sample_angle->setMaximum(1000);
        wlop_follow_sample_angle->setSingleStep(0.1);
        wlop_follow_sample_angle->setValue(1);

        horizontalLayout_66->addWidget(wlop_follow_sample_angle);

        layoutWidget_42 = new QWidget(tab_5);
        layoutWidget_42->setObjectName(QString::fromUtf8("layoutWidget_42"));
        layoutWidget_42->setGeometry(QRect(50, 310, 254, 34));
        horizontalLayout_67 = new QHBoxLayout(layoutWidget_42);
        horizontalLayout_67->setObjectName(QString::fromUtf8("horizontalLayout_67"));
        horizontalLayout_67->setContentsMargins(0, 0, 0, 0);
        label_69 = new QLabel(layoutWidget_42);
        label_69->setObjectName(QString::fromUtf8("label_69"));

        horizontalLayout_67->addWidget(label_69);

        wlop_grow_accept_sigma = new QDoubleSpinBox(layoutWidget_42);
        wlop_grow_accept_sigma->setObjectName(QString::fromUtf8("wlop_grow_accept_sigma"));
        wlop_grow_accept_sigma->setDecimals(4);
        wlop_grow_accept_sigma->setMaximum(1000);
        wlop_grow_accept_sigma->setSingleStep(0.1);
        wlop_grow_accept_sigma->setValue(1);

        horizontalLayout_67->addWidget(wlop_grow_accept_sigma);

        layoutWidget_43 = new QWidget(tab_5);
        layoutWidget_43->setObjectName(QString::fromUtf8("layoutWidget_43"));
        layoutWidget_43->setGeometry(QRect(50, 340, 251, 34));
        horizontalLayout_68 = new QHBoxLayout(layoutWidget_43);
        horizontalLayout_68->setObjectName(QString::fromUtf8("horizontalLayout_68"));
        horizontalLayout_68->setContentsMargins(0, 0, 0, 0);
        label_70 = new QLabel(layoutWidget_43);
        label_70->setObjectName(QString::fromUtf8("label_70"));

        horizontalLayout_68->addWidget(label_70);

        wlop_keep_virtual_angle = new QDoubleSpinBox(layoutWidget_43);
        wlop_keep_virtual_angle->setObjectName(QString::fromUtf8("wlop_keep_virtual_angle"));
        wlop_keep_virtual_angle->setDecimals(4);
        wlop_keep_virtual_angle->setMaximum(1000);
        wlop_keep_virtual_angle->setSingleStep(0.1);
        wlop_keep_virtual_angle->setValue(1);

        horizontalLayout_68->addWidget(wlop_keep_virtual_angle);

        tabWidget->addTab(tab_5, QString());

        retranslateUi(para_skeleton);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(para_skeleton);
    } // setupUi

    void retranslateUi(QWidget *para_skeleton)
    {
        para_skeleton->setWindowTitle(QApplication::translate("para_skeleton", "L_1 Medial Skeleton", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QString());
        skeleton_initial_sampling->setText(QApplication::translate("para_skeleton", "Initial Sampling (stop play)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_71->setToolTip(QApplication::translate("para_skeleton", "dsfafafaf", "ss", QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        label_71->setWhatsThis(QApplication::translate("para_skeleton", "afafafaf", "qqq", QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_ACCESSIBILITY
        label_71->setAccessibleName(QApplication::translate("para_skeleton", "yyyy", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_ACCESSIBILITY
        label_71->setAccessibleDescription(QApplication::translate("para_skeleton", "nnn", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        label_71->setText(QApplication::translate("para_skeleton", "Initial Radius (h0)", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("para_skeleton", "Neighborhood Growth Rate", 0, QApplication::UnicodeUTF8));
        label_72->setText(QApplication::translate("para_skeleton", "Repulsion Mu", 0, QApplication::UnicodeUTF8));
        label_30->setText(QApplication::translate("para_skeleton", "Initial Sampling Number", 0, QApplication::UnicodeUTF8));
        skeleton_full_auto->setText(QApplication::translate("para_skeleton", "Play", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("para_skeleton", "L1 Skeleton", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("para_skeleton", "Current Radius:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("para_skeleton", "Original Density Radius:", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("para_skeleton", "Min Error Before Growth", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("para_skeleton", "Max Iterate Before Growth", 0, QApplication::UnicodeUTF8));
        compute_density_2->setText(QApplication::translate("para_skeleton", "Compute Density Weighting", 0, QApplication::UnicodeUTF8));
        Auto_Wlop_One_Step->setText(QApplication::translate("para_skeleton", "Iterate (Step)", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("para_skeleton", "steps", 0, QApplication::UnicodeUTF8));
        skeleton_run_until_growth->setText(QApplication::translate("para_skeleton", "Iterate Until Neighborhood Growth (Jump)", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("para_skeleton", "Sigma Smoothing KNN", 0, QApplication::UnicodeUTF8));
        label_51->setText(QApplication::translate("para_skeleton", "Branch Identify Sigma", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("para_skeleton", "Branch Tracing Angle", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("para_skeleton", "@Branch Acceptant Size", 0, QApplication::UnicodeUTF8));
        label_73->setText(QApplication::translate("para_skeleton", "Max Bridge Distance", 0, QApplication::UnicodeUTF8));
        label_53->setText(QApplication::translate("para_skeleton", "@Bridge collapse Distance", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("para_skeleton", "Clean Too Close  Distance", 0, QApplication::UnicodeUTF8));
        label_58->setText(QApplication::translate("para_skeleton", "Fix Original Weight", 0, QApplication::UnicodeUTF8));
        label_59->setText(QApplication::translate("para_skeleton", "Branch Segment Length", 0, QApplication::UnicodeUTF8));
        wlop_run_all_segment->setText(QApplication::translate("para_skeleton", "Refinement", 0, QApplication::UnicodeUTF8));
        need_refinement->setText(QApplication::translate("para_skeleton", "Need refinement right away", 0, QApplication::UnicodeUTF8));
        Step3_Clean_And_Update_Radius->setText(QApplication::translate("para_skeleton", "Step3 Update Radius", 0, QApplication::UnicodeUTF8));
        Detect_Feature->setText(QApplication::translate("para_skeleton", "Step1 Detect_Skeleton_Features", 0, QApplication::UnicodeUTF8));
        step2_search_branch->setText(QApplication::translate("para_skeleton", "Step2 Search New Branchs ", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("para_skeleton", "Advance Play", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("para_skeleton", "Branch Search Dist2", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("para_skeleton", "Branch Search Dist1", 0, QApplication::UnicodeUTF8));
        label_54->setText(QApplication::translate("para_skeleton", "Clean NearBranch Dist", 0, QApplication::UnicodeUTF8));
        label_60->setText(QApplication::translate("para_skeleton", "combine_angle", 0, QApplication::UnicodeUTF8));
        label_61->setText(QApplication::translate("para_skeleton", "follow_sample_radius", 0, QApplication::UnicodeUTF8));
        label_64->setText(QApplication::translate("para_skeleton", "follow_sample_angle", 0, QApplication::UnicodeUTF8));
        label_69->setText(QApplication::translate("para_skeleton", "grow_accept_sigma", 0, QApplication::UnicodeUTF8));
        label_70->setText(QApplication::translate("para_skeleton", "keep_virtual_angle", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("para_skeleton", "More parameters", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class para_skeleton: public Ui_para_skeleton {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARA_SKELETONIZATION_H
