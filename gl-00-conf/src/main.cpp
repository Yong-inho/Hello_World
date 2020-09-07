#include "gl/glad/glad.h"	// https://github.com/Dav1dde/glad
#define GLFW_INCLUDE_NONE
#include "gl/glfw/glfw3.h"	// http://www.glfw.org
#include <stdio.h>

int main()
{
	printf( "Hello OpenGL!\n\n" );

	// initialization
	if(!glfwInit()){ printf( "[error] failed in glfwInit()\n" ); return 1; }

	// create invisible window for OpenGL context
	glfwWindowHint( GLFW_VISIBLE, GL_FALSE );
#ifdef GL_ES_VERSION_2_0
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 2 );					// minimum requirement for modern OpenGL ES (2)
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );					// minimum requirement for modern OpenGL ES (2.0)
	glfwWindowHint( GLFW_CLIENT_API, GLFW_OPENGL_ES_API );
#else
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );					// minimum requirement for modern OpenGL (3)
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );					// minimum requirement for modern OpenGL (3.3)
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );				// core profile (>=3.3) allow only forward-compatible profile
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );	// create core profile; all legacy deprecated
#endif
	GLFWwindow* window = glfwCreateWindow( 100, 100, "cgconf - Hello OpenGL", nullptr, nullptr );
	if(!window){ printf( "Failed to create GLFW window.\n" ); glfwTerminate(); return 1; }

	// make the current context and load GL extensions
	glfwMakeContextCurrent(window);
#ifdef GL_ES_VERSION_2_0
	if(!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress)){ printf( "Failed in gladLoadGLES2Loader()\n" ); glfwTerminate(); return 1; }
#else
	if(!gladLoadGL()){ printf( "Failed in gladLoadGLLoader()\n" ); glfwTerminate(); return 1; }
#endif

	// check renderer and vendor
	printf( "You are using\n" );
#ifdef GL_ES_VERSION_2_0
	printf( " - %s\n", glGetString(GL_VERSION) );
	printf( " - %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION) );
#else
	printf( " - OpenGL %s\n", glGetString(GL_VERSION) );
	printf( " - OpenGL Shading Language %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION) );
#endif
	printf( " - GPU: %s\n", glGetString(GL_RENDERER) );
	printf( " - Vendor: %s\n", glGetString(GL_VENDOR) );

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

// in-code linking in Visual Studio
#if defined(_MSC_VER) && _MSC_VER>=1920 // static lib for VC2019 or higher
	#if defined _M_IX86
		#pragma comment( lib, "glfw3.x86.lib" )
	#elif defined _M_X64
		#pragma comment( lib, "glfw3.x64.lib" )
	#endif
#elif defined(_MSC_VER) // dynamic lib for other VC version
	#if defined _M_IX86
		#pragma comment( lib, "glfw3dll.x86.lib" )		// static lib for VC2019
	#elif defined _M_X64
		#pragma comment( lib, "glfw3dll.x64.lib" )		// static lib for VC2019
	#endif
#endif
