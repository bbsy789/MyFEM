#ifndef LOAD_GLOBAL_H
#define LOAD_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LOAD_LIBRARY)
#  define LOAD_EXPORT Q_DECL_EXPORT
#else
#  define LOAD_EXPORT Q_DECL_IMPORT
#endif

#endif // LOAD_GLOBAL_H
