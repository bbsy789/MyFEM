#ifndef ELEMENT_GLOBAL_H
#define ELEMENT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ELEMENT_LIBRARY)
#  define ELEMENT_EXPORT Q_DECL_EXPORT
#else
#  define ELEMENT_EXPORT Q_DECL_IMPORT
#endif

#endif // ELEMENT_GLOBAL_H
