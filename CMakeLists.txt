cmake_minimum_required(VERSION 3.0.0)
project(TutorialApp)
set(CMAKE_CXX_STANDARD 17)


find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW glfw3)
find_package(OpenGL)



if(${GLFW_FOUND})
add_executable(
	TutorialApp
	src/Application.cpp
	src/AttributeHelper.cpp
	src/Camera.cpp
	src/Engine.cpp
	src/IndexBuffer.cpp
	src/main.cpp
	src/Math3D.cpp
	src/Pipeline.cpp
	src/RenderingQueue.cpp
	src/RenderPacket.cpp
	src/ResourceManager.cpp
	src/ShadersProgram.cpp
	src/Texture.cpp
	src/UniformHelper.cpp
	src/UniformList.cpp
	src/VertexBuffer.cpp
	src/VertexLayout.cpp
	shaders/shader.fs
	shaders/shader.vs
	include/Application.h
	include/AttributeHelper.h
	include/Camera.h
	include/Engine.h
	include/Indexbuffer.h
	include/Math3D.h
	include/ogldev_types.h
	include/ogldev_util.h
	include/Pipeline.h
	include/Pool.h
	include/RenderingQueue.h
	include/RenderPacket.h
	include/ResourceManager.h
	include/ShadersProgram.h
	include/stb_image.h
	include/Texture.h
	include/UniformHelper.h
	include/UniformList.h
	include/VertexAttribute.h
	include/VertexBuffer.h
	include/VertexLayout.h
)



target_include_directories(TutorialApp PUBLIC
 ${GLFW_INCLUDE_DIRS}
 ${CMAKE_CURRENT_SOURCE_DIR}/include
 ${CMAKE_CURRENT_SOURCE_DIR}/shaders
 )
target_link_directories(TutorialApp PUBLIC ${GLFW_LIBRARY_DIRS})
target_link_libraries(TutorialApp PUBLIC ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} )
target_link_libraries(TutorialApp PUBLIC "-framework OpenGL")

else()
message(FATAL_ERROR "Unable to find glfw3, tests are disabled!")
endif()

 