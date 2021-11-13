#ifndef NODE_GLOBAL_H
#define NODE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NODE_LIBRARY)
#  define NODE_EXPORT Q_DECL_EXPORT
#else
#  define NODE_EXPORT Q_DECL_IMPORT
#endif

#endif // NODE_GLOBAL_H
