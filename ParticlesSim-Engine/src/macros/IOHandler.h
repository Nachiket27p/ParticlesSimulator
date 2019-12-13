#pragma once

#include <iostream>

#define PRINT_ERROR(err, errcode) {std::cerr << (err) << " : " << (errcode) << std::endl;}

#define PRINT_GL_VERSION(msg) {std::cout << "OpenGL Version: " << (msg) << std::endl;}

#define PRINT_WINDOW_SIZE(w,h) {std::cout << (w) << " x " << (h) << std::endl;}
