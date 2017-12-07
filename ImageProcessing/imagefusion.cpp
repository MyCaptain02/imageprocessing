#include "imagefusion.h"

imageFusion::imageFusion(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect( ui.loadImageButton, &QPushButton::clicked, this, &imageFusion::loadImage );

	connect( ui.listImage, &QListWidget::itemClicked, this, &imageFusion::showSelectedImage );

	connect( ui.imageFusionButton, &QPushButton::clicked, this, &imageFusion::toImageFusion );
}

imageFusion::~imageFusion()
{

}

void imageFusion::loadImage()
{
	path = QFileDialog::getExistingDirectory( this, QStringLiteral( "融合图像选择" ), "." );

	if(path == 0)
		return;

	QDir imageDir( path );
	imageDir.setNameFilters( QStringList() << "*.bmp" );
	QStringList imageList = imageDir.entryList();

	QStringList showList;
	for(auto ele : imageList)
	{
		QString wavelength( ele );
		wavelength.remove( ".bmp" );
		showList.push_back( wavelength );

		cv::Mat image = cv::imread( (path + '/' + ele).toLocal8Bit().toStdString(), cv::IMREAD_ANYDEPTH );

		imageMat.push_back( image );
	}

	if(showList.size() == 0)
	{
		QMessageBox::about( this, QStringLiteral( "提示" ), QStringLiteral( "图片集选择不合理，请重新选择" ) );
		return;
	}
	
	ui.listImage->clear();
	ui.listImage->addItems(showList);

	QImage showImage( path + "/" + "550.bmp", ".bmp" );
	if(showImage.isNull())
		ui.imageListShowlabel->setText( QStringLiteral( "该波长图片缺失" ) );
	else
		ui.imageListShowlabel->setPixmap( QPixmap::fromImage( showImage ) );

	ui.listImage->show();
}

void imageFusion::showSelectedImage(QListWidgetItem *item)
{
	QString wavelength = item->text();
	QPixmap pixmap( path + "/" + wavelength + ".bmp", ".bmp");

	if(pixmap.isNull( ))
		ui.imageListShowlabel->setText( QStringLiteral( "该波长图片缺失" ) );
	else
		ui.imageListShowlabel->setPixmap( pixmap );
}

void imageFusion::toImageFusion()
{

	for(int i = 18; i < 19; i++)
	{
		for(int j = 8; i < 9; j++)
		{
			for(int k = 0; k < 9; k++)
			{
				cv::Mat mat1 = imageMat[i];
				cv::Mat mat2 = imageMat[j];
				cv::Mat mat3 = imageMat[k];

				std::vector<cv::Mat> channel1;
				std::vector<cv::Mat> channel2;
				std::vector<cv::Mat> channel3;

				split( mat1, channel1 );
				split( mat2, channel2 );
				split( mat3, channel3 );

				//imshow( "R", channel1.at( 0 ) );


				mat = cv::Mat( mat1.rows, mat1.cols, CV_8UC3, cv::Scalar( 0, 0, 0 ) );
				std::vector<cv::Mat> channel;

				split( mat, channel );

				channel.at( 0 ) = channel1.at( 0 );
				channel.at( 1 ) = channel2.at( 0 );
				channel.at( 2 ) = channel3.at( 0 );

				merge( channel, mat );

				imshow( "k", mat );

				QImage image = cvMat2QImage( mat );

				ui.imageFusionShowlabel->setPixmap( QPixmap::fromImage( image ) );
			}
		}
	}

	/*
	cv::Mat mat1 = imageMat[28];
	cv::Mat mat2 = imageMat[13];
	cv::Mat mat3 = imageMat[7];

	std::vector<cv::Mat> channel1;
	std::vector<cv::Mat> channel2;
	std::vector<cv::Mat> channel3;

	split( mat1, channel1 );
	split( mat2, channel2 );
	split( mat3, channel3 );

	//imshow( "R", channel1.at( 0 ) );


	mat = cv::Mat( mat1.rows, mat1.cols, CV_8UC3, cv::Scalar( 0, 0, 0 ) );
	std::vector<cv::Mat> channel;

	split( mat, channel );

	channel.at( 0 ) = channel1.at( 0 );
	channel.at( 1 ) = channel2.at( 0 );
	channel.at( 2 ) = channel3.at( 0 );

	merge( channel, mat );

	//imshow( "RGB", mat );

	QImage image = cvMat2QImage( mat );

	ui.imageFusionShowlabel->setPixmap( QPixmap::fromImage( image ) );
	*/
}

QImage imageFusion::cvMat2QImage( const cv::Mat& mat )
{
	// 8-bits unsigned, NO. OF CHANNELS = 1  
	if(mat.type( ) == CV_8UC1)
	{
		QImage image( mat.cols, mat.rows, QImage::Format_Indexed8 );
		// Set the color table (used to translate colour indexes to qRgb values)  
		image.setColorCount( 256 );
		for(int i = 0; i < 256; i++)
		{
			image.setColor( i, qRgb( i, i, i ) );
		}
		// Copy input Mat  
		uchar *pSrc = mat.data;
		for(int row = 0; row < mat.rows; row++)
		{
			uchar *pDest = image.scanLine( row );
			memcpy( pDest, pSrc, mat.cols );
			pSrc += mat.step;
		}
		return image;
	}
	// 8-bits unsigned, NO. OF CHANNELS = 3  
	else if(mat.type( ) == CV_8UC3)
	{
		// Copy input Mat  
		const uchar *pSrc = (const uchar*) mat.data;
		// Create QImage with same dimensions as input Mat  

		QImage image( pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888 );

		return image;
	}
	else if(mat.type( ) == CV_8UC4)
	{
		qDebug( ) << "CV_8UC4";
		// Copy input Mat  
		const uchar *pSrc = (const uchar*) mat.data;
		// Create QImage with same dimensions as input Mat  
		QImage image( pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32 );
		return image.copy( );
	}
	else
	{
		qDebug( ) << "ERROR: Mat could not be converted to QImage.";
		return QImage( );
	}
}

cv::Mat imageFusion::QImage2cvMat( QImage image )
{
	cv::Mat mat;

	switch(image.format( ))
	{
	case QImage::Format_ARGB32:
	case QImage::Format_RGB32:
	case QImage::Format_ARGB32_Premultiplied:

		mat = cv::Mat( image.height( ), image.width( ), CV_8UC4, (void*) image.constBits( ), image.bytesPerLine( ) );

		break;

	case QImage::Format_RGB888:

		mat = cv::Mat( image.height( ), image.width( ), CV_8UC3, (void*) image.constBits( ), image.bytesPerLine( ) );

		//cv::cvtColor ( mat , mat , cv::COLOR_BGR2RGB );

		break;

	case QImage::Format_Indexed8:

		mat = cv::Mat( image.height( ), image.width( ), CV_8UC1, (void*) image.constBits( ), image.bytesPerLine( ) );

		break;
	}

	return mat;
}
