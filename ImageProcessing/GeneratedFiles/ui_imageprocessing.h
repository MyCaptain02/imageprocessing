/********************************************************************************
** Form generated from reading UI file 'imageprocessing.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEPROCESSING_H
#define UI_IMAGEPROCESSING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageProcessingClass
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QPushButton *openImage;
    QPushButton *pathChoosingButton;
    QPushButton *convertToGrayscale;
    QPushButton *lowPassFilterButton;
    QGroupBox *Binary;
    QRadioButton *toBinary;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QSlider *thresholdSlider;
    QSpinBox *thresholdSpinBox;
    QPushButton *highPassFilterButton;
    QPushButton *GaussianFilter;
    QPushButton *edgeFilterButton;
    QGroupBox *groupBox;
    QRadioButton *redShowButton;
    QRadioButton *greenShowButton;
    QRadioButton *blueShowButton;
    QPushButton *splitButton;
    QPushButton *imageFusionButton;
    QFrame *frame_2;
    QFrame *showOriFrame;
    QLabel *showOriLabel;
    QFrame *showFrame;
    QLabel *showLabel;
    QFrame *frame_3;
    QLabel *oriHistogramShowlabel;
    QFrame *frame_4;
    QLabel *histogramShowlabel;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ImageProcessingClass)
    {
        if (ImageProcessingClass->objectName().isEmpty())
            ImageProcessingClass->setObjectName(QStringLiteral("ImageProcessingClass"));
        ImageProcessingClass->resize(1337, 685);
        centralWidget = new QWidget(ImageProcessingClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(0, 0, 1331, 51));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        openImage = new QPushButton(frame);
        openImage->setObjectName(QStringLiteral("openImage"));
        openImage->setGeometry(QRect(10, 10, 81, 31));
        pathChoosingButton = new QPushButton(frame);
        pathChoosingButton->setObjectName(QStringLiteral("pathChoosingButton"));
        pathChoosingButton->setGeometry(QRect(110, 10, 91, 31));
        convertToGrayscale = new QPushButton(frame);
        convertToGrayscale->setObjectName(QStringLiteral("convertToGrayscale"));
        convertToGrayscale->setGeometry(QRect(220, 10, 51, 31));
        lowPassFilterButton = new QPushButton(frame);
        lowPassFilterButton->setObjectName(QStringLiteral("lowPassFilterButton"));
        lowPassFilterButton->setGeometry(QRect(540, 10, 61, 31));
        Binary = new QGroupBox(frame);
        Binary->setObjectName(QStringLiteral("Binary"));
        Binary->setGeometry(QRect(290, 0, 231, 51));
        toBinary = new QRadioButton(Binary);
        toBinary->setObjectName(QStringLiteral("toBinary"));
        toBinary->setGeometry(QRect(10, 20, 89, 16));
        horizontalLayoutWidget = new QWidget(Binary);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(80, 10, 151, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        thresholdSlider = new QSlider(horizontalLayoutWidget);
        thresholdSlider->setObjectName(QStringLiteral("thresholdSlider"));
        thresholdSlider->setMaximum(255);
        thresholdSlider->setSingleStep(1);
        thresholdSlider->setPageStep(1);
        thresholdSlider->setValue(128);
        thresholdSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(thresholdSlider);

        thresholdSpinBox = new QSpinBox(horizontalLayoutWidget);
        thresholdSpinBox->setObjectName(QStringLiteral("thresholdSpinBox"));
        thresholdSpinBox->setMaximum(255);
        thresholdSpinBox->setSingleStep(1);
        thresholdSpinBox->setValue(128);

        horizontalLayout->addWidget(thresholdSpinBox);

        highPassFilterButton = new QPushButton(frame);
        highPassFilterButton->setObjectName(QStringLiteral("highPassFilterButton"));
        highPassFilterButton->setGeometry(QRect(610, 10, 61, 31));
        GaussianFilter = new QPushButton(frame);
        GaussianFilter->setObjectName(QStringLiteral("GaussianFilter"));
        GaussianFilter->setGeometry(QRect(680, 10, 75, 31));
        edgeFilterButton = new QPushButton(frame);
        edgeFilterButton->setObjectName(QStringLiteral("edgeFilterButton"));
        edgeFilterButton->setGeometry(QRect(770, 10, 61, 31));
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(840, 0, 181, 51));
        redShowButton = new QRadioButton(groupBox);
        redShowButton->setObjectName(QStringLiteral("redShowButton"));
        redShowButton->setGeometry(QRect(60, 20, 31, 16));
        greenShowButton = new QRadioButton(groupBox);
        greenShowButton->setObjectName(QStringLiteral("greenShowButton"));
        greenShowButton->setGeometry(QRect(100, 20, 31, 16));
        blueShowButton = new QRadioButton(groupBox);
        blueShowButton->setObjectName(QStringLiteral("blueShowButton"));
        blueShowButton->setGeometry(QRect(140, 20, 31, 16));
        splitButton = new QPushButton(groupBox);
        splitButton->setObjectName(QStringLiteral("splitButton"));
        splitButton->setGeometry(QRect(10, 20, 41, 23));
        imageFusionButton = new QPushButton(frame);
        imageFusionButton->setObjectName(QStringLiteral("imageFusionButton"));
        imageFusionButton->setGeometry(QRect(1050, 12, 75, 31));
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(0, 59, 1331, 801));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        showOriFrame = new QFrame(frame_2);
        showOriFrame->setObjectName(QStringLiteral("showOriFrame"));
        showOriFrame->setGeometry(QRect(10, 10, 640, 480));
        showOriFrame->setFrameShape(QFrame::StyledPanel);
        showOriFrame->setFrameShadow(QFrame::Raised);
        showOriLabel = new QLabel(showOriFrame);
        showOriLabel->setObjectName(QStringLiteral("showOriLabel"));
        showOriLabel->setGeometry(QRect(0, 0, 640, 480));
        showFrame = new QFrame(frame_2);
        showFrame->setObjectName(QStringLiteral("showFrame"));
        showFrame->setGeometry(QRect(670, 10, 640, 480));
        showFrame->setFrameShape(QFrame::StyledPanel);
        showFrame->setFrameShadow(QFrame::Raised);
        showLabel = new QLabel(showFrame);
        showLabel->setObjectName(QStringLiteral("showLabel"));
        showLabel->setGeometry(QRect(0, 0, 640, 480));
        frame_3 = new QFrame(frame_2);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setGeometry(QRect(10, 490, 641, 101));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        oriHistogramShowlabel = new QLabel(frame_3);
        oriHistogramShowlabel->setObjectName(QStringLiteral("oriHistogramShowlabel"));
        oriHistogramShowlabel->setGeometry(QRect(0, 10, 640, 90));
        frame_4 = new QFrame(frame_2);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setGeometry(QRect(670, 490, 641, 101));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        histogramShowlabel = new QLabel(frame_4);
        histogramShowlabel->setObjectName(QStringLiteral("histogramShowlabel"));
        histogramShowlabel->setGeometry(QRect(0, 10, 640, 90));
        ImageProcessingClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(ImageProcessingClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ImageProcessingClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ImageProcessingClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ImageProcessingClass->setStatusBar(statusBar);

        retranslateUi(ImageProcessingClass);

        QMetaObject::connectSlotsByName(ImageProcessingClass);
    } // setupUi

    void retranslateUi(QMainWindow *ImageProcessingClass)
    {
        ImageProcessingClass->setWindowTitle(QApplication::translate("ImageProcessingClass", "ImageProcessing", 0));
        openImage->setText(QApplication::translate("ImageProcessingClass", "\346\211\223\345\274\200\345\233\276\347\211\207", 0));
        pathChoosingButton->setText(QApplication::translate("ImageProcessingClass", "\351\200\211\346\213\251\344\277\235\345\255\230\350\267\257\345\276\204", 0));
        convertToGrayscale->setText(QApplication::translate("ImageProcessingClass", "\347\201\260\345\272\246\345\233\276", 0));
        lowPassFilterButton->setText(QApplication::translate("ImageProcessingClass", "\344\275\216\351\200\232\346\273\244\346\263\242", 0));
        Binary->setTitle(QApplication::translate("ImageProcessingClass", "\344\272\214\345\200\274\345\214\226", 0));
        toBinary->setText(QApplication::translate("ImageProcessingClass", "\344\272\214\345\200\274\345\214\226", 0));
        highPassFilterButton->setText(QApplication::translate("ImageProcessingClass", "\351\253\230\351\200\232\346\273\244\346\263\242", 0));
        GaussianFilter->setText(QApplication::translate("ImageProcessingClass", "\351\253\230\346\226\257\346\273\244\346\263\242", 0));
        edgeFilterButton->setText(QApplication::translate("ImageProcessingClass", "\350\276\271\347\274\230\346\273\244\346\263\242", 0));
        groupBox->setTitle(QApplication::translate("ImageProcessingClass", "\351\242\234\350\211\262\351\200\232\351\201\223\345\210\206\347\246\273", 0));
        redShowButton->setText(QApplication::translate("ImageProcessingClass", "\347\272\242", 0));
        greenShowButton->setText(QApplication::translate("ImageProcessingClass", "\347\273\277", 0));
        blueShowButton->setText(QApplication::translate("ImageProcessingClass", "\350\223\235", 0));
        splitButton->setText(QApplication::translate("ImageProcessingClass", "\345\210\206\347\246\273", 0));
        imageFusionButton->setText(QApplication::translate("ImageProcessingClass", "\345\233\276\345\203\217\350\236\215\345\220\210", 0));
        showOriLabel->setText(QApplication::translate("ImageProcessingClass", "                                                     \346\230\276\347\244\272", 0));
        showLabel->setText(QApplication::translate("ImageProcessingClass", "                                                     \346\230\276\347\244\272", 0));
        oriHistogramShowlabel->setText(QApplication::translate("ImageProcessingClass", "                                                   \347\233\264\346\226\271\345\233\276", 0));
        histogramShowlabel->setText(QApplication::translate("ImageProcessingClass", "                                                  \347\233\264\346\226\271\345\233\276", 0));
    } // retranslateUi

};

namespace Ui {
    class ImageProcessingClass: public Ui_ImageProcessingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEPROCESSING_H
