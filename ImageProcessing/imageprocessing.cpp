#include "imageprocessing.h"
#include "qdebug.h"
#include <stdio.h>
#include <iostream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

ImageProcessing::ImageProcessing( QWidget *parent )
: QMainWindow( parent ),
thresholdValue( 128 )
{
	ui.setupUi( this );

	connect( ui.openImage, &QPushButton::clicked, this, &ImageProcessing::openImage );

	connect( this, SIGNAL( showImage( QImage ) ), this, SLOT( updateImage( QImage ) ) );

	connect( ui.pathChoosingButton, &QPushButton::clicked, this, &ImageProcessing::chooseSavingPath );

	connect( ui.convertToGrayscale, &QPushButton::clicked, this, &ImageProcessing::convertToGrayscale );

	connect( ui.toBinary, &QRadioButton::toggled, this, &ImageProcessing::toBinary );
	connect( ui.thresholdSlider, &QSlider::valueChanged, this, &ImageProcessing::setThreshold );
	connect( ui.thresholdSlider, &QSlider::valueChanged, ui.thresholdSpinBox, &QSpinBox::setValue );
	connect( ui.thresholdSpinBox, static_cast< void (QSpinBox:: *)(int) >(&QSpinBox::valueChanged), ui.thresholdSlider, &QSlider::setValue );

	connect( ui.lowPassFilterButton, &QPushButton::clicked, this, &ImageProcessing::lowPassFilter );
	connect( ui.highPassFilterButton, &QPushButton::clicked, this, &ImageProcessing::highPassFilter );
	connect( ui.GaussianFilter, &QPushButton::clicked, this, &ImageProcessing::GaussianFilter );
	connect( ui.edgeFilterButton, &QPushButton::clicked, this, &ImageProcessing::edgeFilter );

	connect( ui.splitButton, &QPushButton::clicked, this, &ImageProcessing::splitShow );
	connect( ui.redShowButton, &QRadioButton::toggled, this, &ImageProcessing::toShowRedImage );
	connect( ui.greenShowButton, &QRadioButton::toggled, this, &ImageProcessing::toShowGreenImage );
	connect( ui.blueShowButton, &QRadioButton::toggled, this, &ImageProcessing::toShowBlueImage );
}

ImageProcessing::~ImageProcessing( )
{

}

void ImageProcessing::openImage( )
{
	QString filename = QFileDialog::getOpenFileName( this, tr( "Open Image" ), openPath, tr( "Image File(*.bmp)" ) );
	Opixmap = QPixmap( filename );

	ui.showOriLabel->setPixmap( Opixmap );
	//Opixmap = QPixmap ( filename );

	image = QImage( filename, Q_NULLPTR );     //

	int width = image.width( );
	int height = image.height( );
	int size = width*height;

	int *rPixelCount = new int[256];
	int *gPixelCount = new int[256];
	int *bPixelCount = new int[256];

	//int rMaxValue = 0;
	//int gMaxValue = 0;
	//int bMaxValue = 0;
	int rgbMaxValue = 0;

	for(int k = 0; k < 256; k++)     //像素值统计初始化
	{
		rPixelCount[k] = 0;
		gPixelCount[k] = 0;
		bPixelCount[k] = 0;
	}

	//uchar *data = image.bits ( );         //无效指针，why?

	//QRgb color = image.pixel ( 200 , 200 );    //显示特定像素颜色，有一串数字，意思？

	//QPixelFormat p = image.pixelFormat ( );     //像素格式，怎么表示？？

	//Opixmap = QPixmap::fromImage ( image );

	//cv::Mat const qImage = cv::imread ( filename.toStdString() );
	//image = QImage ( qImage.data , 640 , 480 , qImage.step , QImage::Format_RGB888 );  //8-8-8位RGB格式
	//Opixmap = QPixmap::fromImage ( image );

	for(int i = 0; i < width; i++)          //像素值统计
	{
		for(int j = 0; j < height; j++)
		{
			QRgb pixel = image.pixel( i, j );
			int redValue = qRed( pixel );
			int greenValue = qGreen( pixel );
			int blueValue = qBlue( pixel );

			rPixelCount[redValue]++;
			gPixelCount[greenValue]++;
			bPixelCount[blueValue]++;

		}
	}

	int kr = 0;
	int kg = 0;
	int kb = 0;

	int rnumCount = 0;
	int gnumCount = 0;
	int bnumCount = 0;

	while(rnumCount < 0.7 * size && kr <= 255)
	{
		rnumCount += rPixelCount[kr];
		kr++;
	}

	while(gnumCount < 0.7 * size && kg <= 255)
	{
		gnumCount += gPixelCount[kg];
		kg++;
	}

	while(bnumCount < 0.7 * size && kb <= 255)
	{
		bnumCount += bPixelCount[kb];
		kb++;
	}

	rhighThreshold = kr - 1;            //自适应阈值
	rlowThreshold = 0.55*kr;
	ghighThreshold = kg - 1;
	glowThreshold = 0.55*kg;
	bhighThreshold = kb - 1;
	blowThreshold = 0.55*kb;

	for(int k = 0; k < 256; k++)       //最大像素值数目
	{
		if(rPixelCount[k] > rgbMaxValue)
		{
			rgbMaxValue = rPixelCount[k];
		}

		if(gPixelCount[k] > rgbMaxValue)
		{
			rgbMaxValue = gPixelCount[k];
		}

		if(bPixelCount[k] > rgbMaxValue)
		{
			rgbMaxValue = bPixelCount[k];
		}
	}

	cv::Mat hisImage = cv::Mat::zeros( 90, 640, CV_8UC3 );

	for(int i = 0; i < 256; i++)
	{
		int rValue = rPixelCount[i] * 90 * 0.9 / rgbMaxValue;
		int gValue = gPixelCount[i] * 90 * 0.9 / rgbMaxValue;
		int bValue = bPixelCount[i] * 90 * 0.9 / rgbMaxValue;

		line( hisImage, cvPoint( 2 * i, hisImage.rows - 1 ), cvPoint( 2 * i, hisImage.rows - 1 - rValue ), cvScalar( 255, 0, 0 ), 1, 8, 0 );
		line( hisImage, cvPoint( 2 * i, hisImage.rows - 1 ), cvPoint( 2 * i, hisImage.rows - 1 - gValue ), cvScalar( 0, 255, 0 ), 1, 8, 0 );
		line( hisImage, cvPoint( 2 * i, hisImage.rows - 1 ), cvPoint( 2 * i, hisImage.rows - 1 - bValue ), cvScalar( 0, 0, 255 ), 1, 8, 0 );

	}


	//imshow ( "【原图直方图】" , hisImage );        //cv::Mat图像显示

	//double g_dHistMaxValue;          //直方图像素的最大个数
	//minMaxLoc ( hisImage , 0 , &g_dHistMaxValue , 0 , 0 );

	//size_t size = hisImage.total ( );

	/*
	std::vector<cv::Mat> channels;     //cv::Mat空间默认BGR格式，与QImage格式的R,B通道互换
	split( hisImage, channels );
	cv::Mat redchannel = channels.at( 2 );
	channels.at( 2 ) = channels.at( 0 );
	channels.at( 0 ) = redchannel;
	merge( channels, hisImage );
	*/

	QImage hImage = cvMat2QImage( hisImage );

	//int h = hImage.height();
	//int w = hImage.width();

	ui.oriHistogramShowlabel->setPixmap( QPixmap::fromImage( hImage ) );

	//int lineNum = 0;
	//uchar **rdata = nullptr;
	//uchar **gdata = nullptr;
	//uchar **bdata = nullptr;


	/*
	for ( int i = 0; i < h; i++ )
	{
	lineNum = i*w * 4;

	for ( int j = 0; j < w; j++ )
	{
	rdata[i][j] = data[lineNum + 4 * j + 2];
	gdata[i][j] = data[lineNum + 4 * j + 1];
	bdata[i][j] = data[lineNum + 4 * j ];
	}
	}
	*/

	//int imageWidth = pixmap.width ( );
	//int imageHeight = pixmap.height ( );
	//ui.showLabel->setFixedSize ( QSize ( imageWidth , imageHeight ) );
}

void ImageProcessing::chooseSavingPath( )
{
	QString path = QFileDialog::getExistingDirectory( this, QStringLiteral( "存储路径选择" ), "." );

	if(path == " ")
		path = ".";

	saveData( path );
}

void ImageProcessing::saveData( QString path )
{
	QTime time = QTime::currentTime( );
	QString str = time.toString( "hhmmsszzz" );

	//iGray->save ( path + "\\" + str + ".bmp" );
	fImage->save( path + "\\" + str + ".bmp" );
}

void ImageProcessing::updateImage( QImage image )
{
	QPixmap pixmap = QPixmap::fromImage( image );
	ui.showLabel->setPixmap( pixmap );


	int width = image.width( );
	int height = image.height( );
	int size = width*height;

	int *rPixelCount = new int[256];
	int *gPixelCount = new int[256];
	int *bPixelCount = new int[256];

	int rMaxValue = 0;
	int gMaxValue = 0;
	int bMaxValue = 0;

	for(int k = 0; k < 256; k++)
	{
		rPixelCount[k] = 0;
		gPixelCount[k] = 0;
		bPixelCount[k] = 0;
	}

	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			QRgb pixel = image.pixel( i, j );
			int redValue = qRed( pixel );
			int greenValue = qGreen( pixel );
			int blueValue = qBlue( pixel );

			rPixelCount[redValue]++;
			gPixelCount[greenValue]++;
			bPixelCount[blueValue]++;

		}
	}

	for(int k = 0; k < 256; k++)
	{
		if(rPixelCount[k] > rMaxValue)
		{
			rMaxValue = rPixelCount[k];
		}

		if(gPixelCount[k] > gMaxValue)
		{
			gMaxValue = gPixelCount[k];
		}

		if(bPixelCount[k] > bMaxValue)
		{
			bMaxValue = bPixelCount[k];
		}
	}


	cv::Mat hisImage = cv::Mat::zeros( 90, 640, CV_8UC3 );

	for(int i = 0; i < 256; i++)
	{
		int rValue = rPixelCount[i] * 90 * 0.9 / rMaxValue;
		int gValue = gPixelCount[i] * 90 * 0.9 / gMaxValue;
		int bValue = bPixelCount[i] * 90 * 0.9 / bMaxValue;

		line( hisImage, cvPoint( 2 * i, hisImage.rows - 1 ), cvPoint( 2 * i, hisImage.rows - 1 - rValue ), cvScalar( 255, 0, 0 ), 1, 8, 0 );
		line( hisImage, cvPoint( 2 * i, hisImage.rows - 1 ), cvPoint( 2 * i, hisImage.rows - 1 - gValue ), cvScalar( 0, 255, 0 ), 1, 8, 0 );
		line( hisImage, cvPoint( 2 * i, hisImage.rows - 1 ), cvPoint( 2 * i, hisImage.rows - 1 - bValue ), cvScalar( 0, 0, 255 ), 1, 8, 0 );

	}

	QImage hImage = cvMat2QImage( hisImage );


	ui.histogramShowlabel->setPixmap( QPixmap::fromImage( hImage ) );
}

void ImageProcessing::convertToGrayscale( )
{
	//const uchar *pData = image.constBits ( );

	//int m = image.colorCount ( );
	//std::cout << m;

	//int t = Opixmap.isNull ( );
	//QSize l = Opixmap.size ( );
	int width = image.width( );
	int height = image.height( );
	//int d = Opixmap.depth ( );

	fImage = new QImage( width, height, QImage::Format_Indexed8 );
	resize( 640, 480 );

	QVector<QRgb> grayTable;
	for(int i = 0; i < 256; i++)
	{
		grayTable.push_back( qRgb( i, i, i ) );
	}
	fImage->setColorTable( grayTable );    //qt中仅有按照索引的8位位图，需要添加ColorTable

	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			QRgb pixel = image.pixel( i, j );
			int Red = qRed( pixel );
			int Green = qGreen( pixel );
			int Blue = qBlue( pixel );


			int grayscale = 0.3*Red + 0.59*Green + 0.11*Blue;
			//int grayscale = (Red + Green + Blue)/3;

			//QRgb rgbPix = qRgb ( Red , Green , Blue );

			//iGray->setPixel ( i , j , qGray ( Blue , Blue , Blue ) );
			fImage->setPixel( i, j, grayscale );

		}
	}

	//QPixmap pixmap = QPixmap::fromImage ( *fImage );
	//ui.showLabel->setPixmap ( pixmap );
	emit showImage( *fImage );
}

void ImageProcessing::setThreshold( int value )
{
	thresholdValue = value;
}


void ImageProcessing::toBinary( bool tobinary )
{
	if(tobinary)
	{
		int width = fImage->width( );
		int height = fImage->height( );

		for(int i = 0; i < width; i++)
		{
			for(int j = 0; j < height; j++)
			{

				QRgb pixel = fImage->pixel( i, j );
				int grayscaleValue = qRed( pixel );

				if(grayscaleValue < thresholdValue)
				{
					grayscaleValue = 0;
				}
				else{
					grayscaleValue = 255;
				}

				fImage->setPixel( i, j, grayscaleValue );
			}
		}

		QPixmap pixmap = QPixmap::fromImage( *fImage );
		ui.showOriLabel->setPixmap( pixmap );
	}
	else{
		ui.showOriLabel->setPixmap( Opixmap );
	}
}


void ImageProcessing::lowPassFilter( )
{
	int width = image.width( );
	int height = image.height( );

	fImage = new QImage( width, height, QImage::Format_ARGB32 );
	resize( 640, 480 );

	for(int i = 1; i < width - 1; i++)
	{
		for(int j = 1; j < height - 1; j++)
		{
			QRgb pixel1 = image.pixel( i - 1, j - 1 );
			int red1 = qRed( pixel1 );
			int green1 = qGreen( pixel1 );
			int blue1 = qBlue( pixel1 );

			QRgb pixel2 = image.pixel( i - 1, j );
			int red2 = qRed( pixel2 );
			int green2 = qGreen( pixel2 );
			int blue2 = qBlue( pixel2 );

			QRgb pixel3 = image.pixel( i - 1, j + 1 );
			int red3 = qRed( pixel3 );
			int green3 = qGreen( pixel3 );
			int blue3 = qBlue( pixel3 );

			QRgb pixel4 = image.pixel( i, j - 1 );
			int red4 = qRed( pixel4 );
			int green4 = qGreen( pixel4 );
			int blue4 = qBlue( pixel4 );

			QRgb pixel5 = image.pixel( i, j );
			int red5 = qRed( pixel5 );
			int green5 = qGreen( pixel5 );
			int blue5 = qBlue( pixel5 );

			QRgb pixel6 = image.pixel( i, j + 1 );
			int red6 = qRed( pixel6 );
			int green6 = qGreen( pixel6 );
			int blue6 = qBlue( pixel6 );

			QRgb pixel7 = image.pixel( i + 1, j - 1 );
			int red7 = qRed( pixel7 );
			int green7 = qGreen( pixel7 );
			int blue7 = qBlue( pixel7 );

			QRgb pixel8 = image.pixel( i + 1, j );
			int red8 = qRed( pixel8 );
			int green8 = qGreen( pixel8 );
			int blue8 = qBlue( pixel8 );

			QRgb pixel9 = image.pixel( i + 1, j + 1 );
			int red9 = qRed( pixel9 );
			int green9 = qGreen( pixel9 );
			int blue9 = qBlue( pixel9 );

			//LPF3 、 GPF1
			int red = (red1 + 2 * red2 + red3 + 2 * red4 + 4 * red5 + 2 * red6 + red7 + 2 * red8 + red9) / 16;
			int green = (green1 + 2 * green2 + green3 + 2 * green4 + 4 * green5 + 2 * green6 + green7 + 2 * green8 + green9) / 16;
			int blue = (blue1 + 2 * blue2 + blue3 + 2 * blue4 + 4 * blue5 + 2 * blue6 + blue7 + 2 * blue8 + blue9) / 16;


			fImage->setPixel( i, j, qRgb( red, green, blue ) );
		}
	}

	//QPixmap pixmap = QPixmap::fromImage ( *fImage );
	//ui.showLabel->setPixmap ( pixmap );
	emit showImage( *fImage );
}

void ImageProcessing::highPassFilter( )
{
	int width = image.width( );
	int height = image.height( );

	fImage = new QImage( width, height, QImage::Format_ARGB32 );
	resize( 640, 480 );

	for(int i = 1; i < width - 1; i++)
	{
		for(int j = 1; j < height - 1; j++)
		{
			QRgb pixel1 = image.pixel( i - 1, j - 1 );
			int red1 = qRed( pixel1 );
			int green1 = qGreen( pixel1 );
			int blue1 = qBlue( pixel1 );

			QRgb pixel2 = image.pixel( i - 1, j );
			int red2 = qRed( pixel2 );
			int green2 = qGreen( pixel2 );
			int blue2 = qBlue( pixel2 );

			QRgb pixel3 = image.pixel( i - 1, j + 1 );
			int red3 = qRed( pixel3 );
			int green3 = qGreen( pixel3 );
			int blue3 = qBlue( pixel3 );

			QRgb pixel4 = image.pixel( i, j - 1 );
			int red4 = qRed( pixel4 );
			int green4 = qGreen( pixel4 );
			int blue4 = qBlue( pixel4 );

			QRgb pixel5 = image.pixel( i, j );
			int red5 = qRed( pixel5 );
			int green5 = qGreen( pixel5 );
			int blue5 = qBlue( pixel5 );

			QRgb pixel6 = image.pixel( i, j + 1 );
			int red6 = qRed( pixel6 );
			int green6 = qGreen( pixel6 );
			int blue6 = qBlue( pixel6 );

			QRgb pixel7 = image.pixel( i + 1, j - 1 );
			int red7 = qRed( pixel7 );
			int green7 = qGreen( pixel7 );
			int blue7 = qBlue( pixel7 );

			QRgb pixel8 = image.pixel( i + 1, j );
			int red8 = qRed( pixel8 );
			int green8 = qGreen( pixel8 );
			int blue8 = qBlue( pixel8 );

			QRgb pixel9 = image.pixel( i + 1, j + 1 );
			int red9 = qRed( pixel9 );
			int green9 = qGreen( pixel9 );
			int blue9 = qBlue( pixel9 );

			/*        //HPF1
			int red = -1 * red1 - red2 - red3 - red4 + 9 * red5 - red6 - red7 -red8 - red9;
			int green = -1 * green1 - green2 - green3 - green4 + 9 * green5 - green6 - green7 - green8 - green9 ;
			int blue = -1 * blue1 - blue2 - blue3 - blue4 + 9 * blue5 - blue6 - blue7 - blue8 - blue9;
			*/

			//HPF2
			int red = -1 * red2 - red4 + 5 * red5 - red6 - red8;
			int green = -1 * green2 - green4 + 5 * green5 - green6 - green8;
			int blue = -1 * blue2 - blue4 + 5 * blue5 - blue6 - blue8;

			/*
			//HPF3
			int red = red1 - 2* red2 + red3 - 2 * red4 + 5 * red5 - 2 * red6 + red7 - 2 * red8 + red9;
			int green = green1 - 2 * green2 + green3 - 2 * green4 + 5 * green5 - 2 * green6 + green7 - 2 * green8 + green9;
			int blue = blue1 - 2 * blue2 + blue3 - 2 * blue4 + 5 * blue5 - 2 * blue6 + blue7 - 2 * blue8 + blue9;
			*/

			fImage->setPixel( i, j, qRgb( red, green, blue ) );
		}
	}

	//QPixmap pixmap = QPixmap::fromImage ( *fImage );
	//ui.showLabel->setPixmap ( pixmap );
	emit showImage( *fImage );
}

void ImageProcessing::edgeFilter( )
{
	int width = image.width( );
	int height = image.height( );

	//int lowThreshold = 30;     //自适应阈值由前面直方图处理过程确定
	//int highThreshold = 60;

	fImage = new QImage( width, height, QImage::Format_ARGB32 );
	resize( 640, 480 );

	double *pointRDrection = new double[(width - 2)*(height - 2)];
	double *pointGDrection = new double[(width - 2)*(height - 2)];
	double *pointBDrection = new double[(width - 2)*(height - 2)];
	int k = 0;

	for(int i = 0; i < width; i++)                        //Sobel算子，计算梯度图像
	{
		for(int j = 0; j < height; j++)
		{
			int red = 0;
			int green = 0;
			int blue = 0;

			if(i == 0 || i == width - 1 || j == 0 || j == height - 1)
			{
				red = 0;
				green = 0;
				blue = 0;
			}
			else{
				QRgb pixel1 = image.pixel( i - 1, j - 1 );
				int red1 = qRed( pixel1 );
				int green1 = qGreen( pixel1 );
				int blue1 = qBlue( pixel1 );

				QRgb pixel2 = image.pixel( i - 1, j );
				int red2 = qRed( pixel2 );
				int green2 = qGreen( pixel2 );
				int blue2 = qBlue( pixel2 );

				QRgb pixel3 = image.pixel( i - 1, j + 1 );
				int red3 = qRed( pixel3 );
				int green3 = qGreen( pixel3 );
				int blue3 = qBlue( pixel3 );

				QRgb pixel4 = image.pixel( i, j - 1 );
				int red4 = qRed( pixel4 );
				int green4 = qGreen( pixel4 );
				int blue4 = qBlue( pixel4 );

				QRgb pixel5 = image.pixel( i, j );
				int red5 = qRed( pixel5 );
				int green5 = qGreen( pixel5 );
				int blue5 = qBlue( pixel5 );

				QRgb pixel6 = image.pixel( i, j + 1 );
				int red6 = qRed( pixel6 );
				int green6 = qGreen( pixel6 );
				int blue6 = qBlue( pixel6 );

				QRgb pixel7 = image.pixel( i + 1, j - 1 );
				int red7 = qRed( pixel7 );
				int green7 = qGreen( pixel7 );
				int blue7 = qBlue( pixel7 );

				QRgb pixel8 = image.pixel( i + 1, j );
				int red8 = qRed( pixel8 );
				int green8 = qGreen( pixel8 );
				int blue8 = qBlue( pixel8 );

				QRgb pixel9 = image.pixel( i + 1, j + 1 );
				int red9 = qRed( pixel9 );
				int green9 = qGreen( pixel9 );
				int blue9 = qBlue( pixel9 );

				/*         //一阶微分滤波
				//MH1
				int redh = red1 + 2 * red2 + red3 - red7 - 2 * red8 - red9;
				int greenh = green1 + 2 * green2 + green3 - green7 - 2 * green8 - green9;
				int blueh = blue1 + 2 * blue2 + blue3 - blue7 - 2 * blue8 - blue9;

				//MV1
				int redv = red1 - red3 + 2 * red4 - 2 * red6 + red7 - red9;
				int greenv = green1 - green3 + 2 * green4 - 2 * green6 + green7 - green9;
				int bluev = blue1 - blue3 + 2 * blue4 - 2 * blue6 + blue7 - blue9;
				*/

				//MH2
				int redh = red1 + red2 + red3 - red7 - red8 - red9;
				int greenh = green1 + green2 + green3 - green7 - green8 - green9;
				int blueh = blue1 + blue2 + blue3 - blue7 - blue8 - blue9;

				//MV2
				int redv = red1 - red3 + red4 - red6 + red7 - red9;
				int greenv = green1 - green3 + green4 - green6 + green7 - green9;
				int bluev = blue1 - blue3 + blue4 - blue6 + blue7 - blue9;

				red = sqrt( redv * redv + redh * redh );                  //梯度值
				green = sqrt( greenv * greenv + greenh * greenh );
				blue = sqrt( bluev * bluev + blueh * blueh );



				if(redv != 0)                                               //梯度方向值
				{
					pointRDrection[k] = atan( redh / redv ) * 57.3 + 90;
				}
				else{
					pointRDrection[k] = 180;
				}
				if(greenv != 0)
				{
					pointGDrection[k] = atan( greenh / greenv ) * 57.3 + 90;
				}
				else{
					pointGDrection[k] = 180;
				}
				if(bluev != 0)
				{
					pointBDrection[k] = atan( blueh / bluev )*57.3 + 90;
				}
				else{
					pointBDrection[k] = 180;
				}

				k++;

			}
			//二阶微分滤波
			/*
			//ML1
			int red = -1 * red2 - red4 + 4 * red5 - red6 - red8;
			int green = -1 * green2 - green4 + 4 * green5 - green6 - green8;
			int blue = -1 * blue2 - blue4 + 4 * blue5 - blue6 - blue8;
			*/
			/*
			//ML2
			int red = red1 - 2 * red2 + red3 - 2 * red4 + 4 * red5 - 2 * red6 + red7 - 2 * red8 + red9;
			int green = green1 - 2 * green2 + green3 - 2 * green4 + 4 * green5 - 2 * green6 + green7 - 2 * green8 + green9;
			int blue = blue1 - 2 * blue2 + blue3 - 2 * blue4 + 4 * blue5 - 2 * blue6 + blue7 - 2 * blue8 + blue9;
			*/
			/*
			//ML2
			int red = -1 * red1 - red2 - red3 - red4 + 8 * red5 - red6 - red7 - red8 - red9;
			int green = -1 * green1 - green2 - green3 - green4 + 8 * green5 - green6 - green7 - green8 - green9;
			int blue = -1 * blue1 - blue2 - blue3 - blue4 + 8 * blue5 - blue6 - blue7 - blue8 - blue9;
			*/

			fImage->setPixel( i, j, qRgb( red, green, blue ) );
		}
	}

	k = 0;

	for(int i = 1; i < fImage->width( ) - 1; i++)          //非极大值抑制
	{
		for(int j = 1; j < fImage->height( ) - 1; j++)
		{

			int valueR00 = qRed( fImage->pixel( (i - 1), j - 1 ) );
			int valueR01 = qRed( fImage->pixel( (i - 1), j ) );
			int valueR02 = qRed( fImage->pixel( (i - 1), j + 1 ) );
			int valueR10 = qRed( fImage->pixel( (i), j - 1 ) );
			int valueR11 = qRed( fImage->pixel( (i), j ) );
			int valueR12 = qRed( fImage->pixel( (i), j + 1 ) );
			int valueR20 = qRed( fImage->pixel( (i + 1), j - 1 ) );
			int valueR21 = qRed( fImage->pixel( (i + 1), j ) );
			int valueR22 = qRed( fImage->pixel( (i + 1), j + 1 ) );

			int valueG00 = qGreen( fImage->pixel( (i - 1), j - 1 ) );
			int valueG01 = qGreen( fImage->pixel( (i - 1), j ) );
			int valueG02 = qGreen( fImage->pixel( (i - 1), j + 1 ) );
			int valueG10 = qGreen( fImage->pixel( (i), j - 1 ) );
			int valueG11 = qGreen( fImage->pixel( (i), j ) );
			int valueG12 = qGreen( fImage->pixel( (i), j + 1 ) );
			int valueG20 = qGreen( fImage->pixel( (i + 1), j - 1 ) );
			int valueG21 = qGreen( fImage->pixel( (i + 1), j ) );
			int valueG22 = qGreen( fImage->pixel( (i + 1), j + 1 ) );

			int valueB00 = qBlue( fImage->pixel( (i - 1), j - 1 ) );
			int valueB01 = qBlue( fImage->pixel( (i - 1), j ) );
			int valueB02 = qBlue( fImage->pixel( (i - 1), j + 1 ) );
			int valueB10 = qBlue( fImage->pixel( (i), j - 1 ) );
			int valueB11 = qBlue( fImage->pixel( (i), j ) );
			int valueB12 = qBlue( fImage->pixel( (i), j + 1 ) );
			int valueB20 = qBlue( fImage->pixel( (i + 1), j - 1 ) );
			int valueB21 = qBlue( fImage->pixel( (i + 1), j ) );
			int valueB22 = qBlue( fImage->pixel( (i + 1), j + 1 ) );

			if(pointRDrection[k]>0 && pointRDrection[k] <= 45)    //R通道
			{
				if(valueR11 <= (valueR12 + (valueR02 - valueR12)*tan( pointRDrection[k] )) || (valueR11 <= (valueR10 + (valueR20 - valueR10)*tan( pointRDrection[k] ))))
				{
					valueR11 = 0;
				}
			}
			if(pointRDrection[k]>45 && pointRDrection[k] <= 90)

			{
				if(valueR11 <= (valueR01 + (valueR02 - valueR01) / tan( pointRDrection[k] )) || valueR11 <= (valueR21 + (valueR20 - valueR21) / tan( pointRDrection[k] )))
				{
					valueR11 = 0;

				}
			}
			if(pointRDrection[k]>90 && pointRDrection[k] <= 135)
			{
				if(valueR11 <= (valueR01 + (valueR00 - valueR01) / tan( 180 - pointRDrection[k] )) || valueR11 <= (valueR21 + (valueR22 - valueR21) / tan( 180 - pointRDrection[k] )))
				{
					valueR11 = 0;
				}
			}
			if(pointRDrection[k]>135 && pointRDrection[k] <= 180)
			{
				if(valueR11 <= (valueR10 + (valueR00 - valueR10)*tan( 180 - pointRDrection[k] )) || valueR11 <= (valueR12 + (valueR22 - valueR11)*tan( 180 - pointRDrection[k] )))
				{
					valueR11 = 0;
				}
			}

			if(pointGDrection[k]>0 && pointGDrection[k] <= 45)       //G通道
			{
				if(valueG11 <= (valueG12 + (valueG02 - valueG12)*tan( pointGDrection[k] )) || (valueG11 <= (valueG10 + (valueG20 - valueG10)*tan( pointGDrection[k] ))))
				{
					valueG11 = 0;
				}
			}
			if(pointRDrection[k]>45 && pointRDrection[k] <= 90)

			{
				if(valueG11 <= (valueG01 + (valueG02 - valueG01) / tan( pointGDrection[k] )) || valueG11 <= (valueG21 + (valueG20 - valueG21) / tan( pointGDrection[k] )))
				{
					valueG11 = 0;

				}
			}
			if(pointGDrection[k]>90 && pointGDrection[k] <= 135)
			{
				if(valueG11 <= (valueG01 + (valueG00 - valueG01) / tan( 180 - pointGDrection[k] )) || valueG11 <= (valueG21 + (valueG22 - valueG21) / tan( 180 - pointGDrection[k] )))
				{
					valueG11 = 0;
				}
			}
			if(pointGDrection[k]>135 && pointGDrection[k] <= 180)
			{
				if(valueG11 <= (valueG10 + (valueG00 - valueG10)*tan( 180 - pointGDrection[k] )) || valueG11 <= (valueG12 + (valueG22 - valueG11)*tan( 180 - pointGDrection[k] )))
				{
					valueG11 = 0;
				}
			}

			if(pointBDrection[k]>0 && pointBDrection[k] <= 45)        //B通道
			{
				if(valueB11 <= (valueB12 + (valueB02 - valueB12)*tan( pointBDrection[k] )) || (valueB11 <= (valueB10 + (valueB20 - valueB10)*tan( pointBDrection[k] ))))
				{
					valueB11 = 0;
				}
			}
			if(pointBDrection[k]>45 && pointBDrection[k] <= 90)

			{
				if(valueB11 <= (valueB01 + (valueB02 - valueB01) / tan( pointBDrection[k] )) || valueB11 <= (valueB21 + (valueB20 - valueB21) / tan( pointBDrection[k] )))
				{
					valueB11 = 0;

				}
			}
			if(pointBDrection[k]>90 && pointBDrection[k] <= 135)
			{
				if(valueB11 <= (valueB01 + (valueB00 - valueB01) / tan( 180 - pointBDrection[k] )) || valueB11 <= (valueB21 + (valueB22 - valueB21) / tan( 180 - pointBDrection[k] )))
				{
					valueB11 = 0;
				}
			}
			if(pointBDrection[k]>135 && pointBDrection[k] <= 180)
			{
				if(valueB11 <= (valueB10 + (valueB00 - valueB10)*tan( 180 - pointBDrection[k] )) || valueB11 <= (valueB12 + (valueB22 - valueB11)*tan( 180 - pointBDrection[k] )))
				{
					valueB11 = 0;
				}
			}

			fImage->setPixel( i, j, qRgb( valueR11, valueG11, valueB11 ) );

			k++;
		}
	}

	for(int i = 1; i < fImage->width( ) - 1; i++)          //双阈值处理
	{
		for(int j = 1; j < fImage->height( ) - 1; j++)
		{

			int valueR00 = qRed( fImage->pixel( (i - 1), j - 1 ) );
			int valueR01 = qRed( fImage->pixel( (i - 1), j ) );
			int valueR02 = qRed( fImage->pixel( (i - 1), j + 1 ) );
			int valueR10 = qRed( fImage->pixel( (i), j - 1 ) );
			int valueR11 = qRed( fImage->pixel( (i), j ) );
			int valueR12 = qRed( fImage->pixel( (i), j + 1 ) );
			int valueR20 = qRed( fImage->pixel( (i + 1), j - 1 ) );
			int valueR21 = qRed( fImage->pixel( (i + 1), j ) );
			int valueR22 = qRed( fImage->pixel( (i + 1), j + 1 ) );

			int valueG00 = qGreen( fImage->pixel( (i - 1), j - 1 ) );
			int valueG01 = qGreen( fImage->pixel( (i - 1), j ) );
			int valueG02 = qGreen( fImage->pixel( (i - 1), j + 1 ) );
			int valueG10 = qGreen( fImage->pixel( (i), j - 1 ) );
			int valueG11 = qGreen( fImage->pixel( (i), j ) );
			int valueG12 = qGreen( fImage->pixel( (i), j + 1 ) );
			int valueG20 = qGreen( fImage->pixel( (i + 1), j - 1 ) );
			int valueG21 = qGreen( fImage->pixel( (i + 1), j ) );
			int valueG22 = qGreen( fImage->pixel( (i + 1), j + 1 ) );

			int valueB00 = qBlue( fImage->pixel( (i - 1), j - 1 ) );
			int valueB01 = qBlue( fImage->pixel( (i - 1), j ) );
			int valueB02 = qBlue( fImage->pixel( (i - 1), j + 1 ) );
			int valueB10 = qBlue( fImage->pixel( (i), j - 1 ) );
			int valueB11 = qBlue( fImage->pixel( (i), j ) );
			int valueB12 = qBlue( fImage->pixel( (i), j + 1 ) );
			int valueB20 = qBlue( fImage->pixel( (i + 1), j - 1 ) );
			int valueB21 = qBlue( fImage->pixel( (i + 1), j ) );
			int valueB22 = qBlue( fImage->pixel( (i + 1), j + 1 ) );

			if(valueR11 > rhighThreshold)
			{
				valueR11 = 255;
			}
			else if(valueR11 < rlowThreshold){
				valueR11 = 0;
			}
			else{
				//if ( valueR00 == 255 || valueR01 == 255 || valueR02 == 255 || valueR10 == 255 || valueR12 == 255 || valueR20 == 255 || valueR21 == 255 || valueR22 == 255 )
				if(valueR00 > rhighThreshold || valueR01 > rhighThreshold || valueR02 > rhighThreshold || valueR10 > rhighThreshold || valueR12 > rhighThreshold || valueR20 > rhighThreshold || valueR21 > rhighThreshold || valueR22 > rhighThreshold)
					//if ( valueR00 > 0 || valueR01 > 0 || valueR02 > 0 || valueR10 > 0 || valueR12 > 0 || valueR20 > 0 || valueR21 > 0 || valueR22 > 0 )
				{
					valueR11 = 255;
				}
				else{
					valueR11 = 0;
				}
			}

			if(valueG11 > ghighThreshold)
			{
				valueG11 = 255;
			}
			else if(valueG11 < glowThreshold){
				valueG11 = 0;
			}
			else{
				//if ( valueG00 == 255 || valueG01 == 255 || valueG02 == 255 || valueG10 == 255 || valueG12 == 255 || valueG20 == 255 || valueG21 == 255 || valueG22 == 255 )
				if(valueG00 > ghighThreshold || valueG01 > ghighThreshold || valueG02 > ghighThreshold || valueG10 > ghighThreshold || valueG12 > ghighThreshold || valueG20 > ghighThreshold || valueG21 > ghighThreshold || valueG22 > ghighThreshold)
					//if ( valueG00 > 0 || valueG01 > 0 || valueG02 > 0 || valueG10 > 0 || valueG12 > 0 || valueG20 > 0 || valueG21 > 0 || valueG22 > 0 )

				{
					valueG11 = 255;
				}
				else{
					valueG11 = 0;
				}
			}

			if(valueB11 > bhighThreshold)
			{
				valueB11 = 255;
			}
			else if(valueB11 < blowThreshold){
				valueB11 = 0;
			}
			else{
				//if ( valueB00 == 255 || valueB01 == 255 || valueB02 == 255 || valueB10 == 255 || valueB12 == 255 || valueB20 == 255 || valueB21 == 255 || valueB22 == 255 )
				if(valueB00 > bhighThreshold || valueB01 > bhighThreshold || valueB02 > bhighThreshold || valueB10 > bhighThreshold || valueB12 > bhighThreshold || valueB20 > bhighThreshold || valueB21 > bhighThreshold || valueB22 > bhighThreshold)
					//if ( valueB00 > 0 || valueB01 > 0 || valueB02 > 0 || valueB10 > 0 || valueB12 > 0 || valueB20 > 0 || valueB21 > 0 || valueB22 > 0 )
				{
					valueB11 = 255;
				}
				else{
					valueB11 = 0;
				}
			}

			fImage->setPixel( i, j, qRgb( valueR11, valueG11, valueB11 ) );
		}
	}

	//QPixmap pixmap = QPixmap::fromImage ( *fImage );
	//ui.showLabel->setPixmap ( pixmap );
	emit showImage( *fImage );
}

void ImageProcessing::GaussianFilter( )
{
	int width = image.width( );
	int height = image.height( );

	fImage = new QImage( width, height, QImage::Format_ARGB32 );
	resize( 640, 480 );

	for(int i = 2; i < width - 2; i++)
	{
		for(int j = 2; j < height - 2; j++)
		{
			QRgb pixel1 = image.pixel( i - 2, j - 2 );
			int red1 = qRed( pixel1 );
			int green1 = qGreen( pixel1 );
			int blue1 = qBlue( pixel1 );

			QRgb pixel2 = image.pixel( i - 2, j - 1 );
			int red2 = qRed( pixel2 );
			int green2 = qGreen( pixel2 );
			int blue2 = qBlue( pixel2 );

			QRgb pixel3 = image.pixel( i - 2, j );
			int red3 = qRed( pixel3 );
			int green3 = qGreen( pixel3 );
			int blue3 = qBlue( pixel3 );

			QRgb pixel4 = image.pixel( i - 2, j + 1 );
			int red4 = qRed( pixel4 );
			int green4 = qGreen( pixel4 );
			int blue4 = qBlue( pixel4 );

			QRgb pixel5 = image.pixel( i - 2, j + 2 );
			int red5 = qRed( pixel5 );
			int green5 = qGreen( pixel5 );
			int blue5 = qBlue( pixel5 );

			QRgb pixel6 = image.pixel( i - 1, j - 2 );
			int red6 = qRed( pixel6 );
			int green6 = qGreen( pixel6 );
			int blue6 = qBlue( pixel6 );

			QRgb pixel7 = image.pixel( i - 1, j - 1 );
			int red7 = qRed( pixel7 );
			int green7 = qGreen( pixel7 );
			int blue7 = qBlue( pixel7 );

			QRgb pixel8 = image.pixel( i - 1, j );
			int red8 = qRed( pixel8 );
			int green8 = qGreen( pixel8 );
			int blue8 = qBlue( pixel8 );

			QRgb pixel9 = image.pixel( i - 1, j + 1 );
			int red9 = qRed( pixel9 );
			int green9 = qGreen( pixel9 );
			int blue9 = qBlue( pixel9 );

			QRgb pixel10 = image.pixel( i - 1, j + 2 );
			int red10 = qRed( pixel10 );
			int green10 = qGreen( pixel10 );
			int blue10 = qBlue( pixel10 );

			QRgb pixel11 = image.pixel( i, j - 2 );
			int red11 = qRed( pixel11 );
			int green11 = qGreen( pixel11 );
			int blue11 = qBlue( pixel11 );

			QRgb pixel12 = image.pixel( i, j - 1 );
			int red12 = qRed( pixel12 );
			int green12 = qGreen( pixel12 );
			int blue12 = qBlue( pixel12 );

			QRgb pixel13 = image.pixel( i, j );
			int red13 = qRed( pixel13 );
			int green13 = qGreen( pixel13 );
			int blue13 = qBlue( pixel13 );

			QRgb pixel14 = image.pixel( i, j + 1 );
			int red14 = qRed( pixel14 );
			int green14 = qGreen( pixel14 );
			int blue14 = qBlue( pixel14 );

			QRgb pixel15 = image.pixel( i, j + 2 );
			int red15 = qRed( pixel15 );
			int green15 = qGreen( pixel15 );
			int blue15 = qBlue( pixel15 );

			QRgb pixel16 = image.pixel( i + 1, j - 2 );
			int red16 = qRed( pixel16 );
			int green16 = qGreen( pixel16 );
			int blue16 = qBlue( pixel16 );

			QRgb pixel17 = image.pixel( i + 1, j - 1 );
			int red17 = qRed( pixel17 );
			int green17 = qGreen( pixel17 );
			int blue17 = qBlue( pixel17 );

			QRgb pixel18 = image.pixel( i + 1, j );
			int red18 = qRed( pixel18 );
			int green18 = qGreen( pixel18 );
			int blue18 = qBlue( pixel18 );

			QRgb pixel19 = image.pixel( i + 1, j + 1 );
			int red19 = qRed( pixel19 );
			int green19 = qGreen( pixel19 );
			int blue19 = qBlue( pixel19 );

			QRgb pixel20 = image.pixel( i + 1, j + 2 );
			int red20 = qRed( pixel20 );
			int green20 = qGreen( pixel20 );
			int blue20 = qBlue( pixel20 );

			QRgb pixel21 = image.pixel( i + 2, j - 2 );
			int red21 = qRed( pixel21 );
			int green21 = qGreen( pixel21 );
			int blue21 = qBlue( pixel21 );

			QRgb pixel22 = image.pixel( i + 2, j - 1 );
			int red22 = qRed( pixel22 );
			int green22 = qGreen( pixel22 );
			int blue22 = qBlue( pixel22 );

			QRgb pixel23 = image.pixel( i + 2, j );
			int red23 = qRed( pixel23 );
			int green23 = qGreen( pixel23 );
			int blue23 = qBlue( pixel23 );

			QRgb pixel24 = image.pixel( i + 2, j + 1 );
			int red24 = qRed( pixel24 );
			int green24 = qGreen( pixel24 );
			int blue24 = qBlue( pixel24 );

			QRgb pixel25 = image.pixel( i + 2, j + 2 );
			int red25 = qRed( pixel25 );
			int green25 = qGreen( pixel25 );
			int blue25 = qBlue( pixel25 );


			//GPF2
			int red = (red1 + red2 + 2 * red3 + red4 + red5 + red6 + 2 * red7 + 4 * red8 + 2 * red9 + red10 + 2 * red11 + 4 * red12 + 8 * red13 + 4 * red14 + 2 * red15 + red16 + 2 * red17 + 4 * red18 + 2 * red19 + red20 + red21 + red22 + 2 * red23 + red24 + red25) / 52;
			int green = (green1 + green2 + 2 * green3 + green4 + green5 + green6 + 2 * green7 + 4 * green8 + 2 * green9 + green10 + 2 * green11 + 4 * green12 + 8 * green13 + 4 * green14 + 2 * green15 + green16 + 2 * green17 + 4 * green18 + 2 * green19 + green20 + green21 + green22 + 2 * green23 + green24 + green25) / 52;
			int blue = (blue1 + blue2 + 2 * blue3 + blue4 + blue5 + blue6 + 2 * blue7 + 4 * blue8 + 2 * blue9 + blue10 + 2 * blue11 + 4 * blue12 + 8 * blue13 + 4 * blue14 + 2 * blue15 + blue16 + 2 * blue17 + 4 * blue18 + 2 * blue19 + blue20 + blue21 + blue22 + 2 * blue23 + blue24 + blue25) / 52;

			/*
			//HPF4
			int red = -1 * ( red1 + red2 + red3 + red4 + red5 + red6 + red7 + red8 + red9 + red10 + red11 + red12 - 25 * red13 + red14 + red15 + red16 + red17 + red18 + red19 + red20 + red21 + red22 + red23 + red24 + red25 );
			int green = -1 * ( green1 + green2 + green3 + green4 + green5 + green6 + green7 + green8 + green9 + green10 + green11 + green12 - 25 * green13 + green14 + green15 + green16 + green17 + green18 +  green19 + green20 + green21 + green22 + green23 + green24 + green25 );
			int blue = -1 * ( blue1 + blue2 + blue3 + blue4 + blue5 + blue6 + blue7 + blue8 + blue9 + blue10 + blue11 + blue12 - 25 * blue13 + blue14 + blue15 + blue16 + blue17 + blue18 + blue19 + blue20 + blue21 + blue22 + blue23 + blue24 + blue25 ) ;
			*/

			fImage->setPixel( i, j, qRgb( red, green, blue ) );
		}
	}

	//QPixmap pixmap = QPixmap::fromImage ( *fImage );
	//ui.showLabel->setPixmap ( pixmap );
	emit showImage( *fImage );
}

QImage ImageProcessing::cvMat2QImage( const cv::Mat& mat )
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

cv::Mat ImageProcessing::QImage2cvMat( QImage image )
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


void ImageProcessing::splitShow( )
{
	cv::Mat mat = QImage2cvMat( image );

	std::vector<cv::Mat> channels;

	split( mat, channels );

	blueChannel = channels.at( 0 );
	//imshow("b", blueChannel );
	greenChannel = channels.at( 1 );
	//imshow( "g", greenChannel );
	redChannel = channels.at( 2 );
	//imshow( "r", redChannel );
	//imshow("B", blueChannel);
}

void ImageProcessing::toShowRedImage( bool showRed )
{
	if(showRed)
	{
		//cv::Mat rChannel = zeros( redChannel.rows, redChannel.cols, redChannel.type );
		//cv::Mat gChannel = rChannel.clear();
		//cv::Mat bChannel = rChannel.clear( );
		cv::Mat mat( redChannel.rows, redChannel.cols, CV_8UC3, cv::Scalar( 0, 0, 0 ) );
		std::vector<cv::Mat> channels;
		split( mat, channels );
		channels.at( 0 ) = redChannel;
		//imshow( "red", channels.at( 2 ) );
		merge( channels, mat );
		//imshow( "redf", mat );

		splitShowImage( mat );
	}
}

void ImageProcessing::toShowGreenImage( bool showGreen )
{
	if(showGreen)
	{
		cv::Mat mat( greenChannel.rows, greenChannel.cols, CV_8UC3, cv::Scalar( 0, 0, 0 ) );
		std::vector<cv::Mat> channels;
		split( mat, channels );
		channels.at( 1 ) = greenChannel;
		//imshow( "green", channels.at( 1 ) );
		merge( channels, mat );
		//imshow( "greenf", mat );
		splitShowImage( mat );
	}
}

void ImageProcessing::toShowBlueImage( bool showBlue )
{
	if(showBlue)
	{
		cv::Mat mat( blueChannel.rows, blueChannel.cols, CV_8UC3, cv::Scalar( 0, 0, 0 ) );
		std::vector<cv::Mat> channels;
		split( mat, channels );
		channels.at( 2 ) = blueChannel;
		//imshow( "blue", channels.at( 0 ) );
		merge( channels, mat );
		//imshow( "bluef", mat );
		splitShowImage( mat );
	}
}

void ImageProcessing::splitShowImage( cv::Mat mat )
{

	QImage image = cvMat2QImage( mat );

	//ui.showLabel->setPixmap( QPixmap::fromImage( image ) );

	emit showImage( image );

}