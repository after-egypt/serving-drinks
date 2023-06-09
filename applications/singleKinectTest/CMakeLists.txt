cmake_minimum_required(VERSION 2.8)
project(singleKinectTest)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
# set(Python3_DIR "/usr/lib/python3.6/config-3.6m-x86_64-linux-gnu")

#find_package(libkinectwrapper REQUIRED)

message("singleKinectTest.libkinectwrapper_INCLUDE_DIRS:  " ${libkinectwrapper_INCLUDE_DIRS})
# message("source: " ${Python3_DIR})

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Cairo REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(Ceres REQUIRED)
find_package(Boost REQUIRED COMPONENTS program_options)
find_package(PythonLibs 3 REQUIRED)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
# pkg_check_modules(GTK3 REQUIRED gtkglext-1.0)

include_directories(
    ${libkinectwrapper_INCLUDE_DIRS}
    ${GTK3_INCLUDE_DIRS}
    ${CAIRO_INCLUDE_DIRS}
    ${APRIL_TAG_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
    /usr/include/python3.6
    /root/projects/kinect_wrapper/applications/singleKinectTest
)

SET(MULTIKINECT_SRC
    SKPFaceDetector.cpp
    singleKinectTest.cpp
    # SMColorBlob.cpp
    # MaskGenerator.cpp
)

add_executable(singleKinectTest  ${MULTIKINECT_SRC})

target_link_libraries(singleKinectTest kinectwrapper
    k4a
    k4abt
    k4arecord
    pthread
    #vision_geometry
    GL
    GLU
    #glfw
    gthread-2.0
    ${OpenCV_LIBRARIES}
    ${GTK3_LIBRARIES}
    ${CAIRO_LIBRARIES}
    ${CERES_LIBRARIES}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    /usr/lib/python3.6/config-3.6m-x86_64-linux-gnu/libpython3.6.so
)