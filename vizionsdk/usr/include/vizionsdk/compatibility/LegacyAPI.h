#if defined(__unix__) || defined(__unix)
#ifndef LEGACY_API_H
#define LEGACY_API_H

#include <stdint.h>
#include <string>
#include <vector>
#include "../includes/internal/VxInternalTypes.hpp"
#include "../includes/public/VxPublicTypes.hpp"

#if defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__)
#define x64
#endif

// Define deprecation macros
#ifdef __GNUC__
#define VZ_DEPRECATED                                                              \
    __attribute__((                                                                \
        deprecated("This API will be removed in March 2026. Please migrate to Vx " \
                   "API.")))
#elif defined(_MSC_VER)
#define VZ_DEPRECATED \
    __declspec(deprecated("This API will be removed in March 2026. Please migrate to Vx API."))
#else
#define VZ_DEPRECATED
#endif
// Forward declare only the types needed for the public API
// Don't include the original headers at all in public headers

typedef unsigned char BYTE;

typedef enum _USB_DEVICE_SPEED {
    UsbLowSpeed = 0,
    UsbFullSpeed,
    UsbHighSpeed,
    UsbSuperSpeed,
    SuperSpeedPlus
} USB_DEVICE_SPEED;

// Opaque types that match the legacy SDK's types
typedef struct VizionCam_t VizionCam;

struct _GstBuffer;
typedef struct _GstBuffer GstBuffer;

struct _GstVideoInfo;
typedef struct _GstVideoInfo GstVideoInfo;

struct VzFormat {
    uint8_t mediatype_idx = 0;
    uint16_t width;
    uint16_t height;
    uint16_t framerate;
    uint32_t format;
};

struct DeviceListData {
    std::string deviceName;
    std::string hardwareId;
    std::string serialNumber;
};

enum class AE_MODE_STATUS {
    MANUAL_EXP = 0,
    AUTO_GAIN = 0x9,
    AUTO_EXP = 0xC,
};

enum class AWB_MODE_STATUS {
    MANUAL_QXQY_WB = 0,
    MANUAL_TEMPERATURE_WB = 0x7,
    AUTO_WB = 0xF,
};

enum class FLIP_MODE {
    FLIP_NORMAL = 0,
    FLIP_H_MIRROR,
    FLIP_V_MIRROR,
    FLIP_ROTATE_180,
};

enum class EFFECT_MODE {
    NORMAL_MODE = 0x00,
    BLACK_WHITE_MODE = 0x03,
    GRAYSCALE_MODE = 0x06,
    NEGATIVE_MODE = 0x07,
    SKETCH_MODE = 0x0F,
};

enum class FLICK_MODE {
    DISABLE = 0x0000,
    _50HZ = 0x3201,
    _60HZ = 0x3C01,
    AUTO = 0x000E,
};

enum class DZ_MODE_STATUS {
    DZ_IMMEDIATE = 0x8000,
    DZ_SLOW = 0x0040,
    DZ_FAST = 0x0200,
};

enum class VzLogLevel { NONE = 0, ERROR, WARNING, INFO, DEBUG, VERBOSE };

// Create inline namespace for legacy compatibility layer
inline namespace legacy_api {
// Define the public API functions as specified in the list

// Basic device operations
VZ_DEPRECATED VizionCam* VcCreateVizionCamDevice();
VZ_DEPRECATED int VcGetVideoDeviceList(VizionCam* vizion_cam,
                                       std::vector<std::string>& devname_list);
VZ_DEPRECATED int VcOpen(VizionCam* vizion_cam, int list_idx);
VZ_DEPRECATED int VcClose(VizionCam* vizion_cam);
VZ_DEPRECATED int VcReleaseVizionCamDevice(VizionCam* vizion_cam);

// Capture format
VZ_DEPRECATED int VcGetCaptureFormatList(VizionCam* vizion_cam, std::vector<VzFormat>& capformats);
VZ_DEPRECATED int VcSetCaptureFormat(VizionCam* vizion_cam, VzFormat capformat);
VZ_DEPRECATED int VcGetRawImageCapture(VizionCam* vizion_cam,
                                       uint8_t* raw_data,
                                       int* data_size,
                                       uint16_t timeout);

// Device information
VZ_DEPRECATED int VcGetVizionCamDeviceName(VizionCam* vizion_cam, char* devname);
VZ_DEPRECATED int VcGetUSBFirmwareVersion(VizionCam* vizion_cam, char* fw_ver);
VZ_DEPRECATED int VcGetTEVSFirmwareVersion(VizionCam* vizion_cam, char* fw_ver);
VZ_DEPRECATED int VcGetSensorUID(VizionCam* vizion_cam, BYTE* sensor_id);
VZ_DEPRECATED int VcGetUniqueSensorID(VizionCam* vizion_cam, char* sensor_id);

// Camera control - Exposure
VZ_DEPRECATED int VcGetAutoExposureMode(VizionCam* vizion_cam, AE_MODE_STATUS& ae_mode);
VZ_DEPRECATED int VcSetAutoExposureMode(VizionCam* vizion_cam, AE_MODE_STATUS ae_mode);
VZ_DEPRECATED int VcGetExposureTime(VizionCam* vizion_cam, uint32_t& exptime);
VZ_DEPRECATED int VcSetExposureTime(VizionCam* vizion_cam, uint32_t exptime);
VZ_DEPRECATED int VcGetExposureGain(VizionCam* vizion_cam, uint8_t& expgain);
VZ_DEPRECATED int VcSetExposureGain(VizionCam* vizion_cam, uint8_t expgain);
VZ_DEPRECATED int VcGetExposureMinimum(VizionCam* vizion_cam, uint32_t& exptime);
VZ_DEPRECATED int VcSetExposureMinimum(VizionCam* vizion_cam, uint32_t exptime);
VZ_DEPRECATED int VcGetExposureMaximum(VizionCam* vizion_cam, uint32_t& exptime);
VZ_DEPRECATED int VcSetExposureMaximum(VizionCam* vizion_cam, uint32_t exptime);
VZ_DEPRECATED int VcGetCurrentExposureTime(VizionCam* vizion_cam, uint32_t& exptime);
VZ_DEPRECATED int VcGetCurrentExposureGain(VizionCam* vizion_cam, uint8_t& expgain);

// Camera control - FPS
VZ_DEPRECATED int VcGetMaxFPS(VizionCam* vizion_cam, uint8_t& max_fps);
VZ_DEPRECATED int VcSetMaxFPS(VizionCam* vizion_cam, uint8_t max_fps);

// Camera control - White Balance
VZ_DEPRECATED int VcGetAutoWhiteBalanceMode(VizionCam* vizion_cam, AWB_MODE_STATUS& awb_mode);
VZ_DEPRECATED int VcSetAutoWhiteBalanceMode(VizionCam* vizion_cam, AWB_MODE_STATUS awb_mode);
VZ_DEPRECATED int VcGetTemperature(VizionCam* vizion_cam, uint16_t& temp);
VZ_DEPRECATED int VcSetTemperature(VizionCam* vizion_cam, uint16_t temp);

// Camera control - Image manipulation
VZ_DEPRECATED int VcGetFlipMode(VizionCam* vizion_cam, FLIP_MODE& flip);
VZ_DEPRECATED int VcSetFlipMode(VizionCam* vizion_cam, FLIP_MODE flip);
VZ_DEPRECATED int VcGetEffectMode(VizionCam* vizion_cam, EFFECT_MODE& effect);
VZ_DEPRECATED int VcSetEffectMode(VizionCam* vizion_cam, EFFECT_MODE effect);
VZ_DEPRECATED int VcGetFlickMode(VizionCam* vizion_cam, FLICK_MODE& flick);
VZ_DEPRECATED int VcSetFlickMode(VizionCam* vizion_cam, FLICK_MODE flick);

// Camera control - Image quality
VZ_DEPRECATED int VcGetBrightness(VizionCam* vizion_cam, double& brightness);
VZ_DEPRECATED int VcSetBrightness(VizionCam* vizion_cam, double brightness);
VZ_DEPRECATED int VcGetGamma(VizionCam* vizion_cam, double& gamma);
VZ_DEPRECATED int VcSetGamma(VizionCam* vizion_cam, double gamma);
VZ_DEPRECATED int VcGetSaturation(VizionCam* vizion_cam, double& saturation);
VZ_DEPRECATED int VcSetSaturation(VizionCam* vizion_cam, double saturation);
VZ_DEPRECATED int VcGetContrast(VizionCam* vizion_cam, double& contrast);
VZ_DEPRECATED int VcSetContrast(VizionCam* vizion_cam, double contrast);
VZ_DEPRECATED int VcGetSharpening(VizionCam* vizion_cam, double& sharpness);
VZ_DEPRECATED int VcSetSharpening(VizionCam* vizion_cam, double sharpness);
VZ_DEPRECATED int VcGetDenoise(VizionCam* vizion_cam, double& denoise);
VZ_DEPRECATED int VcSetDenoise(VizionCam* vizion_cam, double denoise);
VZ_DEPRECATED int VcGetBacklightCompensation(VizionCam* vizion_cam, double& ae_comp);
VZ_DEPRECATED int VcSetBacklightCompensation(VizionCam* vizion_cam, double ae_comp);

// Camera control - Digital Zoom
VZ_DEPRECATED int VcGetDigitalZoomType(VizionCam* vizion_cam, DZ_MODE_STATUS& zoom_type);
VZ_DEPRECATED int VcSetDigitalZoomType(VizionCam* vizion_cam, DZ_MODE_STATUS zoom_type);
VZ_DEPRECATED int VcGetDigitalZoomTarget(VizionCam* vizion_cam, double& times);
VZ_DEPRECATED int VcSetDigitalZoomTarget(VizionCam* vizion_cam, double times);
VZ_DEPRECATED int VcGetDigitalZoom_CT_X(VizionCam* vizion_cam, double& ct_x);
VZ_DEPRECATED int VcSetDigitalZoom_CT_X(VizionCam* vizion_cam, double ct_x);
VZ_DEPRECATED int VcGetDigitalZoom_CT_Y(VizionCam* vizion_cam, double& ct_y);
VZ_DEPRECATED int VcSetDigitalZoom_CT_Y(VizionCam* vizion_cam, double ct_y);

// Camera control - Other adjustments
VZ_DEPRECATED int VcGetJpegQual(VizionCam* vizion_cam, uint8_t& qual);
VZ_DEPRECATED int VcSetJpegQual(VizionCam* vizion_cam, uint8_t qual);
VZ_DEPRECATED int VcGetThroughPut(VizionCam* vizion_cam, uint16_t& throughput);
VZ_DEPRECATED int VcSetThroughPut(VizionCam* vizion_cam, uint16_t throughput);

// Camera settings - Profile management
VZ_DEPRECATED int VcRecoverDefaultSetting(VizionCam* vizion_cam);
VZ_DEPRECATED int VcLoadProfileSettingFromPath(VizionCam* vizion_cam, const char* profile_path);
VZ_DEPRECATED int VcLoadProfileSetting(VizionCam* vizion_cam, const char* profile_string);
VZ_DEPRECATED int VcSetProfileControlConfig(VizionCam* vizion_cam);
VZ_DEPRECATED int VcGetOSPProfile(VizionCam* vizion_cam, VzSensorProfile* profile);
VZ_DEPRECATED int VcSetOSPProfile(VizionCam* vizion_cam, VzSensorProfile profile);
VZ_DEPRECATED int VcGotoSaveOSPProfile(VizionCam* vizion_cam, uint8_t check);
VZ_DEPRECATED int VcGetOSPProfileConfig(VizionCam* vizion_cam, std::string& profile_str);
VZ_DEPRECATED int VcCheckOSPProfile(VizionCam* vizion_cam);

// Reset and TimeStamp related functions
VZ_DEPRECATED int VcResetUVC(VizionCam* vizion_cam);
VZ_DEPRECATED int VcReadTimeStamp(VizionCam* vizion_cam, uint32_t& frameCount, uint32_t& timeStamp);

// Others functions
VZ_DEPRECATED void VcSetLogLevel(VzLogLevel level);

}  // namespace legacy_api

#endif  // LEGACY_API_H
#endif