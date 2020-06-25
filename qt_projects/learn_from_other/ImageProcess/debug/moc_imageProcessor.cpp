/****************************************************************************
** Meta object code from reading C++ file 'imageProcessor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../imageProcessor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imageProcessor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ImageProcessor_t {
    QByteArrayData data[20];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageProcessor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageProcessor_t qt_meta_stringdata_ImageProcessor = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ImageProcessor"
QT_MOC_LITERAL(1, 15, 8), // "finished"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 7), // "newFile"
QT_MOC_LITERAL(4, 33, 8), // "progress"
QT_MOC_LITERAL(5, 42, 5), // "value"
QT_MOC_LITERAL(6, 48, 7), // "process"
QT_MOC_LITERAL(7, 56, 4), // "file"
QT_MOC_LITERAL(8, 61, 14), // "ImageAlgorithm"
QT_MOC_LITERAL(9, 76, 9), // "algorithm"
QT_MOC_LITERAL(10, 86, 5), // "abort"
QT_MOC_LITERAL(11, 92, 8), // "abortAll"
QT_MOC_LITERAL(12, 101, 10), // "sourceFile"
QT_MOC_LITERAL(13, 112, 4), // "Gray"
QT_MOC_LITERAL(14, 117, 8), // "Binarize"
QT_MOC_LITERAL(15, 126, 8), // "Negative"
QT_MOC_LITERAL(16, 135, 6), // "Emboss"
QT_MOC_LITERAL(17, 142, 7), // "Sharpen"
QT_MOC_LITERAL(18, 150, 6), // "Soften"
QT_MOC_LITERAL(19, 157, 14) // "AlgorithmCount"

    },
    "ImageProcessor\0finished\0\0newFile\0"
    "progress\0value\0process\0file\0ImageAlgorithm\0"
    "algorithm\0abort\0abortAll\0sourceFile\0"
    "Gray\0Binarize\0Negative\0Emboss\0Sharpen\0"
    "Soften\0AlgorithmCount"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageProcessor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       2,   56, // properties
       1,   62, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   45,    2, 0x0a /* Public */,
      10,    2,   50,    2, 0x0a /* Public */,
      11,    0,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 8,    7,    9,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 8,    7,    9,
    QMetaType::Void,

 // properties: name, type, flags
      12, QMetaType::QString, 0x00095001,
       9, 0x80000000 | 8, 0x00095009,

 // enums: name, alias, flags, count, data
       8,    8, 0x0,    7,   67,

 // enum data: key, value
      13, uint(ImageProcessor::Gray),
      14, uint(ImageProcessor::Binarize),
      15, uint(ImageProcessor::Negative),
      16, uint(ImageProcessor::Emboss),
      17, uint(ImageProcessor::Sharpen),
      18, uint(ImageProcessor::Soften),
      19, uint(ImageProcessor::AlgorithmCount),

       0        // eod
};

void ImageProcessor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ImageProcessor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finished((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->progress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->process((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< ImageAlgorithm(*)>(_a[2]))); break;
        case 3: _t->abort((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< ImageAlgorithm(*)>(_a[2]))); break;
        case 4: _t->abortAll(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ImageProcessor::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ImageProcessor::finished)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ImageProcessor::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ImageProcessor::progress)) {
                *result = 1;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ImageProcessor *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->sourceFile(); break;
        case 1: *reinterpret_cast< ImageAlgorithm*>(_v) = _t->algorithm(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject ImageProcessor::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ImageProcessor.data,
    qt_meta_data_ImageProcessor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ImageProcessor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageProcessor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ImageProcessor.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ImageProcessor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ImageProcessor::finished(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ImageProcessor::progress(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
