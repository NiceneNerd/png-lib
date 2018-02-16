/**
* C++ png library based on lodepng
* @copyright 2018 - Max Bebök
* @author Max Bebök
* @license GNU-GPLv3 - see the "LICENSE" file in the root directory
*/

#include "../include/main_header.h"

void buffer_delete_callback(char* data, void* vector)
{
    delete reinterpret_cast<std::vector<u8> *> (vector);
}

NAN_METHOD(encode)
{
    // check arguments
    if(info.Length() != 3) {
        return Nan::ThrowError(Nan::New("PNG::encode - expected arguments bufferIn, width, height").ToLocalChecked());
    }
/*
    if(!info[0]->IsBuffer()) {
        return Nan::ThrowError(Nan::New("PNG::encode - the first argument must be a buffer").ToLocalChecked());
    }*/

    if(!info[1]->IsNumber() || !info[2]->IsNumber()) {
        return Nan::ThrowError(Nan::New("PNG::encode - the second and third argument must be numbers").ToLocalChecked());
    }

    auto bufferInObj = info[0]->ToObject();
    int width  = info[1]->NumberValue();
    int height = info[2]->NumberValue();

    u8* bufferIn = (u8*)node::Buffer::Data(bufferInObj);
    auto bufferInSize = node::Buffer::Length(bufferInObj);

    std::vector<u8> *bufferOut = new std::vector<u8>();

    unsigned error = lodepng::encode(*bufferOut, bufferIn, width, height);

    //if there's an error, display it
    if(error) 
    {
        return Nan::ThrowError(Nan::New(lodepng_error_text(error)).ToLocalChecked());
        //std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
    }

    info.GetReturnValue().Set(Nan::NewBuffer((char*)bufferOut->data(), bufferOut->size(), buffer_delete_callback, bufferOut).ToLocalChecked());
}

NAN_MODULE_INIT(Initialize)
{
    NAN_EXPORT(target, encode);
}

NODE_MODULE(png, Initialize);
