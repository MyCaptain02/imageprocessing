#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QtWidgets>
#include "ui_imageprocessing.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

class ImageProcessing : public QMainWindow
{
	Q_OBJECT

public:
	ImageProcessing( QWidget *parent = 0 );
	~ImageProcessing( );

	void saveData( QString path );

	QImage cvMat2QImage( const cv::Mat &mat );
	cv::Mat QImage2cvMat( QImage image );

	void splitShowImage( cv::Mat mat );

signals:
	void showImage( QImage image );

	public slots:
	void openImage( );

	void updateImage( QImage image );

	void chooseSavingPath( );

	void convertToGrayscale( );

	void toBinary( bool tobinary );
	void setThreshold( int value );

	void lowPassFilter( );
	void highPassFilter( );
	void GaussianFilter( );
	void edgeFilter( );

	void splitShow( );
	void toShowRedImage( bool showRed );
	void toShowGreenImage( bool showGreen );
	void toShowBlueImage( bool showBlue );

private:
	Ui::ImageProcessingClass ui;

	QString openPath;
	QPixmap Opixmap;
	QImage image;
	QImage *iGray;
	QImage *fImage;

	int thresholdValue;

	int rhighThreshold;
	int rlowThreshold;
	int ghighThreshold;
	int glowThreshold;
	int bhighThreshold;
	int blowThreshold;

	cv::Mat blueChannel;
	cv::Mat greenChannel;
	cv::Mat redChannel;
};

#endif // IMAGEPROCESSING_H
