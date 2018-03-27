/**
* C++ png library based on lodepng
* @copyright 2018 - Max Bebök
* @author Max Bebök
* @license GNU-GPLv3 - see the "LICENSE" file in the root directory
*/

#include "../include/main_header.h"

napi_value PNG_Encode(napi_env env, napi_callback_info info) 
{
    size_t argc = 3;
    napi_value argv[3];

    if(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok)
    {
        napi_throw_error(env, NULL, "Failed to parse arguments");
        return nullptr;
    }

    s32 imageWidth;
    s32 imageHeight;

    u8* bufferIn = nullptr;
    size_t bufferInSize = 0;

    bool isBuffer;
    if(napi_is_buffer(env, argv[0], &isBuffer) != napi_ok || !isBuffer)
    {
        napi_throw_error(env, NULL, "Argument 1 is not a Buffer");
        return nullptr;
    }

    if(napi_get_buffer_info(env, argv[0], (void**)&bufferIn, &bufferInSize) != napi_ok)
    {
        napi_throw_error(env, NULL, "Invalid Buffer was passed as argument");
        return nullptr;
    }

    if(napi_get_value_int32(env, argv[1], &imageWidth) != napi_ok)
    {
        napi_throw_error(env, NULL, "Can't parse the width parameter");
        return nullptr;
    }

    if(napi_get_value_int32(env, argv[2], &imageHeight) != napi_ok)
    {
        napi_throw_error(env, NULL, "Can't parse the height parameter");
        return nullptr;
    }

    if((int)bufferInSize != (imageWidth * imageHeight * 4))
    {
        napi_throw_error(env, NULL, "Buffer size does not match the width and height");
        return nullptr;
    }

    std::vector<u8> bufferOut = std::vector<u8>();
    unsigned error = lodepng::encode(bufferOut, bufferIn, imageWidth, imageHeight);

    if(error) 
    {
        napi_throw_error(env, NULL, "lodepng error");
            return nullptr;
    }

    napi_value resultBuffer;
    void* createdBuffer;

    if(napi_create_buffer_copy(env, bufferOut.size(), bufferOut.data(), &createdBuffer, &resultBuffer) != napi_ok)
    {
        napi_throw_error(env, NULL, "Unable to create Buffer");
        return nullptr;
    }

    return resultBuffer;
}

napi_value Init(napi_env env, napi_value exports) 
{
    napi_value fnEncode;
    if(napi_create_function(env, NULL, 0, PNG_Encode, NULL, &fnEncode) != napi_ok) 
        napi_throw_error(env, NULL, "Unable to wrap native function");

    if(napi_set_named_property(env, exports, "encode", fnEncode) != napi_ok) 
        napi_throw_error(env, NULL, "Unable to populate exports");

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
