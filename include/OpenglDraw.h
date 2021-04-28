#ifndef OPENGLDRAW_H
#define OPENGLDRAW_H


#include <stdio.h>
#include <stdlib.h>

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#define QUIT(m,v)      { fprintf(stderr, "%s:%s\n", m, v); exit(1); }

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768


class OpenGLdraw {
public:


   void init(int W, int H) {
      unsigned int texture;
      glGenTextures(1, &texture);
      glBindTexture(GL_TEXTURE_2D, texture);
  
      width = W; height = H;
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, W, H, 0,
             GL_RGB, GL_UNSIGNED_BYTE, NULL);
      // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
      glGenFramebuffers(1, &fbo);
      glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
      glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

      glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
   }

   void draw(GLubyte *image, GLuint W=0, GLuint H=0, int atx=0, int aty=0) {
      if(H == 0) H = height;
      if(W == 0) W = width;
      glTexSubImage2D(GL_TEXTURE_2D, 0, atx, aty, W, H, GL_RGB, GL_UNSIGNED_BYTE, image);

      glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
      glBlitFramebuffer(0, 0, W, H, atx, aty, W, H,
                     GL_COLOR_BUFFER_BIT, GL_NEAREST);
      glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

   }
private:
	int width, height;
	GLuint fbo;
};

#endif