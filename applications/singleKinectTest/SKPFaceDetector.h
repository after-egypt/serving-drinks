#ifndef SKP_FACE_DETECTOR_H
#define SKP_FACE_DETECTOR_H

#include "SKPRecipient.h"
#include "SKWrapper.h"
#include <python3.6/Python.h>
#include <k4a/k4atypes.h>
#include <k4abt.hpp>
#include <vector>

class SKPacket;

const std::chrono::milliseconds TIMEOUT(K4A_WAIT_INFINITE);

class SKPFaceDetector : public SKPRecipient {
public:
    SKPFaceDetector(SKWrapper &skw);
    void receiveFrame(SKPacket &skp);
    void addRecipient(SKPRecipient *skpr);
    void findTargetId(SKPacket& skp);
    void find3DTargetPose(SKPacket& skp);
    void chooseTarget(SKPacket& skp);
    void getTargetEncoding(SKPacket& skp);

protected:
    std::vector<SKPRecipient*> _recipients;
    PyObject* person_find;
    PyObject* get_encoding;
    PyObject* find_person;
    PyObject* target_encoding;
    bool chose_target;
    bool found_target;
    int target_id;
    k4a_float3_t target_pos;
    k4abt::tracker tracker;
};

#endif