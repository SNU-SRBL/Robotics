#ifndef INITCIMGPLUGIN_H
#define INITCIMGPLUGIN_H

#include <sofa/config.h>

#define CIMGPLUGIN_HAVE_JPEG 1
#define CIMGPLUGIN_HAVE_TIFF 1
#define CIMGPLUGIN_HAVE_PNG 1
#define CIMGPLUGIN_HAVE_ZLIB 1

#ifdef SOFA_BUILD_CIMGPLUGIN
#define SOFA_TARGET CImgPlugin
#define SOFA_CIMGPLUGIN_API SOFA_EXPORT_DYNAMIC_LIBRARY
#else
#define SOFA_CIMGPLUGIN_API SOFA_IMPORT_DYNAMIC_LIBRARY
#endif


#endif // INITCIMGPLUGIN_H
