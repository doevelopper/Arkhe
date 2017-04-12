

// .NAME __ARKHE_CTKExport - manage Windows system differences
// .SECTION Description
// The __ARKHE_CTKExport captures some system differences between Unix
// and Windows operating systems. 

#ifndef __ARKHE_CTKExport_h
#define __ARKHE_CTKExport_h

#include <QtGlobal>

#if defined(Q_OS_WIN) || defined(Q_OS_SYMBIAN)
#  if defined(ARKHE_CTK_EXPORTS)
#    define ARKHE_CTK Q_DECL_EXPORT
#  else
#    define ARKHE_CTK Q_DECL_IMPORT
#  endif
#endif

#if !defined(ARKHE_CTK)
//#  if defined(CTK_SHARED)
#    define ARKHE_CTK Q_DECL_EXPORT
//#  else
//#    define ARKHE_CTK
//#  endif
#endif

#endif

