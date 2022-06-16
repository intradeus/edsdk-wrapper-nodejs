#ifndef CANON_API_TYPES_H
#define CANON_API_TYPES_H

#include <uv.h>
#include <unordered_map>
#include <napi.h>
#include <EDSDK.h>

#define kEdsPropID_CFn               0x00000009
#define kEdsPropID_MyMenu            0x0000000e
#define kEdsPropID_JpegQuality       0x00000101
#define kEdsPropID_FlashCompensation 0x00000408
#define kEdsPropID_DepthOfField      0x0000041b
#define kEdsPropID_EFCompensation    0x0000041e
#define kEdsPropID_Evf_FocusAid      0x00000509

typedef enum {
    kEdsObjectFormat_Unknown = 0x00000000,
    kEdsObjectFormat_JPEG = 0x3801,
    kEdsObjectFormat_CR2 = 0xB103,
    kEdsObjectFormat_MP4 = 0xB982,
    kEdsObjectFormat_CR3 = 0xB108,
    kEdsObjectFormat_HEIF_CODE = 0xB10B
} EdsObjectFormat;

#define sprintf_s(buf, ...) snprintf((buf), sizeof(buf), __VA_ARGS__)

namespace CameraApi {

    typedef std::unordered_map<int, std::string> LabelMap;
}

#endif
