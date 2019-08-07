/*
 * Copyright 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "shader.h"

namespace ndk_helper {
  
bool shader::CompileShader(GLuint *shader, const GLenum type,
                           const GLchar *source, const GLint iSize) {
  if (source == NULL || iSize <= 0)
    return false;

  *shader = glCreateShader(type);
  glShaderSource(
      *shader, 1, &source,
      &iSize); //Not specifying 3rd parameter (size) could be troublesome..

  glCompileShader(*shader);

  GLint vertex_compiled;
  glGetShaderiv(*shader, GL_COMPILE_STATUS, &vertex_compiled);
  if (vertex_compiled != GL_TRUE)
  {
    GLsizei log_length = 0;
    GLchar message[1024];
    glGetShaderInfoLog(*shader, 1024, &log_length, message);
    printf("%s", message);
    // Write the error to a log
  }
  
#if defined(DEBUG)
  GLint logLength;
  glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
  if (logLength > 0) {
    GLchar *log = (GLchar *)malloc(logLength);
    glGetShaderInfoLog(*shader, logLength, &logLength, log);
    free(log);
  }
#endif

  GLint status;
  glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
  if (status == 0) {
    glDeleteShader(*shader);
    return false;
  }

  return true;
}

bool shader::CompileShader(GLuint *shader, const GLenum type,
                           std::vector<uint8_t> &data) {
  if (!data.size())
    return false;

  const GLchar *source = (GLchar *)&data[0];
  int64_t iSize = data.size();
  return shader::CompileShader(shader, type, source, (GLint)iSize);
}

bool shader::LinkProgram(const GLuint prog) {
  GLint status;

  glLinkProgram(prog);

#if defined(DEBUG)
  GLint logLength;
  glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
  if (logLength > 0) {
    GLchar *log = (GLchar *)malloc(logLength);
    glGetProgramInfoLog(prog, logLength, &logLength, log);
    free(log);
  }
#endif

  glGetProgramiv(prog, GL_LINK_STATUS, &status);
  if (status == 0) {
    return false;
  }

  return true;
}

bool shader::ValidateProgram(const GLuint prog) {
  GLint logLength, status;

  glValidateProgram(prog);
  glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
  if (logLength > 0) {
    GLchar *log = (GLchar *)malloc(logLength);
    glGetProgramInfoLog(prog, logLength, &logLength, log);
    free(log);
  }

  glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
  if (status == 0)
    return false;

  return true;
}

} //namespace ndkHelper
