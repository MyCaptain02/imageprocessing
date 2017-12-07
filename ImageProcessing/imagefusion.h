#ifndef IMAGEFUSION_H
#define IMAGEFUSION_H

#include <QtWidgets>
#include <QtWidgets/qdialog.h>
#include "ui_imagefusion.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class imageFusion : public QDialog
{
	Q_OBJECT

public:
	imageFusion(QWidget *parent = 0);
	~imageFusion();

	QImage cvMat2QImage( const cv::Mat &mat );
	cv::Mat QImage2cvMat( QImage image );

public slots:
    void loadImage();

	void showSelectedImage(QListWidgetItem *item);

	void toImageFusion();

private:
	Ui::imageFusion ui;

	QString path;

	std::vector<cv::Mat> imageMat;

	cv::Mat mat;
};

#endif // IMAGEFUSION_H
