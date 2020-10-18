cmake_minimum_required(VERSION 3.5)
project(ShaderCompile C CXX)

set(SRCS 
	ShaderCompile/cfgprocessor.cpp
	ShaderCompile/d3dxfxc.cpp
	ShaderCompile/ShaderCompile.cpp
	ShaderCompile/shaderparser.cpp
	ShaderCompile/utlbuffer.cpp
	ShaderCompile/utlsymbol.cpp )

include_directories(shared/include shared/gsl/include ShaderCompile/include)

add_executable(ShaderCompile ${SRCS})
set_property(TARGET ShaderCompile PROPERTY CXX_STANDARD 20)