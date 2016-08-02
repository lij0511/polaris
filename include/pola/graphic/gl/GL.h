/*
 * GL.h
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#ifndef POLA_GRAPHIC_GL_H_
#define POLA_GRAPHIC_GL_H_

/* TODO 需要更好的宏 */
#ifdef POLA_GLES
#define OPENGL_ES
#include <GLES2/gl2.h>
#elif defined(POLA_LINUX_X11)
#define OPENGL
#include <GL/glew.h>
#endif

#ifdef OPENGL_ES
#define glClearDepth glClearDepthf
#endif

#endif /* POLA_GRAPHIC_GL_H_ */
