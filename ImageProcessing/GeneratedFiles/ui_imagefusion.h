/********************************************************************************
** Form generated from reading UI file 'imagefusion.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEFUSION_H
#define UI_IMAGEFUSION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_imageFusion
{
public:
    QPushButton *loadImageButton;
    QFrame *frame;
    QLabel *imageListShowlabel;
    QLabel *imageFusionShowlabel;
    QListWidget *listImage;
    QPushButton *imageFusionButton;

    void setupUi(QDialog *imageFusion)
    {
        if (imageFusion->objectName().isEmpty())
            imageFusion->setObjectName(QStringLiteral("imageFusion"));
        imageFusion->resize(1332, 620);
        imageFusion->setSizeGripEnabled(false);
        imageFusion->setModal(false);
        loadImageButton = new QPushButton(imageFusion);
        loadImageButton->setObjectName(QStringLiteral("loadImageButton"));
        loadImageButton->setGeometry(QRect(170, 10, 91, 41));
        frame = new QFrame(imageFusion);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(10, 60, 1311, 481));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        imageListShowlabel = new QLabel(frame);
        imageListShowlabel->setObjectName(QStringLiteral("imageListShowlabel"));
        imageListShowlabel->setGeometry(QRect(0, 0, 640, 480));
        imageFusionShowlabel = new QLabel(frame);
        imageFusionShowlabel->setObjectName(QStringLiteral("imageFusionShowlabel"));
        imageFusionShowlabel->setGeometry(QRect(670, 0, 640, 480));
        listImage = new QListWidget(imageFusion);
        listImage->setObjectName(QStringLiteral("listImage"));
        listImage->setGeometry(QRect(10, 550, 641, 61));
        listImage->setFlow(QListView::LeftToRight);
        imageFusionButton = new QPushButton(imageFusion);
        imageFusionButton->setObjectName(QStringLiteral("imageFusionButton"));
        imageFusionButton->setGeometry(QRect(630, 20, 61, 31));

        retranslateUi(imageFusion);

        QMetaObject::connectSlotsByName(imageFusion);
    } // setupUi

    void retranslateUi(QDialog *imageFusion)
    {
        imageFusion->setWindowTitle(QApplication::translate("imageFusion", "\345\233\276\345\203\217\350\236\215\345\220\210", 0));
        loadImageButton->setText(QApplication::translate("imageFusion", "\350\275\275\345\205\245\345\233\276\347\211\207", 0));
        imageListShowlabel->setText(QApplication::translate("imageFusion", "                                                \346\230\276\347\244\272\345\233\276\347\211\207\351\233\206", 0));
        imageFusionShowlabel->setText(QApplication::translate("imageFusion", "                                                 \346\230\276\347\244\272\345\220\210\346\210\220\345\233\276\345\203\217", 0));
        imageFusionButton->setText(QApplication::translate("imageFusion", "\350\236\215\345\220\210", 0));
    } // retranslateUi

};

namespace Ui {
    class imageFusion: public Ui_imageFusion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEFUSION_H
