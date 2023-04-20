#include <python3.10/Python.h>
#include <opencv2/opencv.hpp>
#include <numpy/arrayobject.h>
#include <iostream>

using namespace std;

// export PYTHONPATH=`pwd`
// g++ -g test.cpp -I/usr/include/python3.10 -I/home/krishagarwal/.local/lib/python3.10/site-packages/numpy/core/include/ -lpython3.10 -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

int main(int argc, char const *argv[]) {
    Py_Initialize();
    import_array();
    PyObject* person_find = PyImport_ImportModule("person_find");
    PyObject* get_encoding = PyObject_GetAttrString(person_find, "get_encoding");
    PyObject* find_person = PyObject_GetAttrString(person_find, "find_person");

    cv::Mat target = cv::imread("leonardo.jpg");
    cv::cvtColor(target, target, cv::COLOR_BGR2RGB);
    npy_intp dims[3] = {target.rows, target.cols, target.channels()};
    PyObject* numpy_array = PyArray_SimpleNewFromData(3, dims, NPY_UINT8, target.data);
    PyObject* target_encoding = PyObject_CallFunctionObjArgs(get_encoding, numpy_array, nullptr);

    cv::Mat scene = cv::imread("leonardo3.jpg");
    cv::cvtColor(scene, scene, cv::COLOR_BGR2RGB);
    npy_intp scene_dims[3] = {scene.rows, scene.cols, scene.channels()};
    PyObject* scene_numpy_array = PyArray_SimpleNewFromData(3, scene_dims, NPY_UINT8, scene.data);
    PyObject* found = PyObject_CallFunctionObjArgs(find_person, scene_numpy_array, target_encoding, nullptr);

    PyObject* first = PyTuple_GetItem(found, 0);
    PyObject* second = PyTuple_GetItem(found, 1);

    long x = PyLong_AS_LONG(first), y = PyLong_AS_LONG(second);
    cout << x << " " << y << endl;

    Py_DECREF(person_find);
    Py_DECREF(get_encoding);
    Py_DECREF(find_person);
    Py_DECREF(numpy_array);
    Py_DECREF(target_encoding);
}
