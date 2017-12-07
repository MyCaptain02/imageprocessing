/****************************************************************************
** Meta object code from reading C++ file 'imageprocessing.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../imageprocessing.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imageprocessing.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ImageProcessing_t {
    QByteArrayData data[24];
    char stringdata0[275];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageProcessing_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageProcessing_t qt_meta_stringdata_ImageProcessing = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ImageProcessing"
QT_MOC_LITERAL(1, 16, 9), // "showImage"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 5), // "image"
QT_MOC_LITERAL(4, 33, 9), // "openImage"
QT_MOC_LITERAL(5, 43, 11), // "updateImage"
QT_MOC_LITERAL(6, 55, 16), // "chooseSavingPath"
QT_MOC_LITERAL(7, 72, 18), // "convertToGrayscale"
QT_MOC_LITERAL(8, 91, 8), // "toBinary"
QT_MOC_LITERAL(9, 100, 8), // "tobinary"
QT_MOC_LITERAL(10, 109, 12), // "setThreshold"
QT_MOC_LITERAL(11, 122, 5), // "value"
QT_MOC_LITERAL(12, 128, 13), // "lowPassFilter"
QT_MOC_LITERAL(13, 142, 14), // "highPassFilter"
QT_MOC_LITERAL(14, 157, 14), // "GaussianFilter"
QT_MOC_LITERAL(15, 172, 10), // "edgeFilter"
QT_MOC_LITERAL(16, 183, 9), // "splitShow"
QT_MOC_LITERAL(17, 193, 14), // "toShowRedImage"
QT_MOC_LITERAL(18, 208, 7), // "showRed"
QT_MOC_LITERAL(19, 216, 16), // "toShowGreenImage"
QT_MOC_LITERAL(20, 233, 9), // "showGreen"
QT_MOC_LITERAL(21, 243, 15), // "toShowBlueImage"
QT_MOC_LITERAL(22, 259, 8), // "showBlue"
QT_MOC_LITERAL(23, 268, 6) // "fusion"

    },
    "ImageProcessing\0showImage\0\0image\0"
    "openImage\0updateImage\0chooseSavingPath\0"
    "convertToGrayscale\0toBinary\0tobinary\0"
    "setThreshold\0value\0lowPassFilter\0"
    "highPassFilter\0GaussianFilter\0edgeFilter\0"
    "splitShow\0toShowRedImage\0showRed\0"
    "toShowGreenImage\0showGreen\0toShowBlueImage\0"
    "showBlue\0fusion"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageProcessing[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   97,    2, 0x0a /* Public */,
       5,    1,   98,    2, 0x0a /* Public */,
       6,    0,  101,    2, 0x0a /* Public */,
       7,    0,  102,    2, 0x0a /* Public */,
       8,    1,  103,    2, 0x0a /* Public */,
      10,    1,  106,    2, 0x0a /* Public */,
      12,    0,  109,    2, 0x0a /* Public */,
      13,    0,  110,    2, 0x0a /* Public */,
      14,    0,  111,    2, 0x0a /* Public */,
      15,    0,  112,    2, 0x0a /* Public */,
      16,    0,  113,    2, 0x0a /* Public */,
      17,    1,  114,    2, 0x0a /* Public */,
      19,    1,  117,    2, 0x0a /* Public */,
      21,    1,  120,    2, 0x0a /* Public */,
      23,    0,  123,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void,

       0        // eod
};

void ImageProcessing::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ImageProcessing *_t = static_cast<ImageProcessing *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 1: _t->openImage(); break;
        case 2: _t->updateImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 3: _t->chooseSavingPath(); break;
        case 4: _t->convertToGrayscale(); break;
        case 5: _t->toBinary((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->setThreshold((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->lowPassFilter(); break;
        case 8: _t->highPassFilter(); break;
        case 9: _t->GaussianFilter(); break;
        case 10: _t->edgeFilter(); break;
        case 11: _t->splitShow(); break;
        case 12: _t->toShowRedImage((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->toShowGreenImage((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->toShowBlueImage((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->fusion(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ImageProcessing::*_t)(QImage );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ImageProcessing::showImage)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject ImageProcessing::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ImageProcessing.data,
      qt_meta_data_ImageProcessing,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ImageProcessing::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageProcessing::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ImageProcessing.stringdata0))
        return static_cast<void*>(const_cast< ImageProcessing*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ImageProcessing::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void ImageProcessing::showImage(QImage _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
