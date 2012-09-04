#ifndef DE_EXPORT_H
#define DE_EXPORT_H

#ifdef DE_EXPORT_DEFINE
#define DE_EXPORT __declspec(dllexport)
#define GLEW_STATIC
#else
#define DE_EXPORT __declspec(dllimport)
#endif

/**

\defgroup Core

\brief Core of the engine

*/


/**

\defgroup Data

\brief Data that live in memory

All data that live in memory before being "used", like mesh before being upload in VBO etc...

*/

#endif