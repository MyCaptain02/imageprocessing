#ifndef IMAGEFUSION_H
#define IMAGEFUSION_H

#include <QDialog>
#include "ui_imagefusion.h"

class imageFusion : public QDialog
{
	Q_OBJECT

public:
	imageFusion(QWidget *parent = 0);
	~imageFusion();

private:
	Ui::imageFusion ui;
};

#endif // IMAGEFUSION_H
