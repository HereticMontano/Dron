#pragma once
#include "host/ble_hs.h"
class Control
{
private:
    // Identification Dron Service
    static constexpr ble_uuid128_t DRONE_SERVICE_UUID = BLE_UUID128_INIT(
        0x14, 0x12, 0x8A, 0x76, 0x04, 0xD1, 0x6C, 0x4F,
        0x7E, 0x53, 0xF2, 0xE8, 0x00, 0x00, 0xB1, 0x19);

    // Identification control
    static constexpr ble_uuid128_t CONTROL_CHAR_UUID = BLE_UUID128_INIT(
        0x14, 0x12, 0x8A, 0x76, 0x04, 0xD1, 0x6C, 0x4F,
        0x7E, 0x53, 0xF2, 0xE8, 0x01, 0x00, 0xB1, 0x19);

    static int OnControlAccess(uint16_t connHandle, uint16_t attrHandle, struct ble_gatt_access_ctxt *ctxt, void *arg);

    static constexpr struct ble_gatt_chr_def CONTROL_CHARS[] = {
        {
            .uuid = &CONTROL_CHAR_UUID.u,
            .access_cb = OnControlAccess,
            .arg = nullptr,
            .descriptors = nullptr,
            .flags = BLE_GATT_CHR_F_WRITE | BLE_GATT_CHR_F_WRITE_NO_RSP,
            .min_key_size = 0,
            .val_handle = nullptr,
            .cpfd = nullptr,
        },
        {}, // mandatory to nible
    };

    static constexpr struct ble_gatt_svc_def GATT_SERVICES[] = {
        {
            .type = BLE_GATT_SVC_TYPE_PRIMARY,
            .uuid = &DRONE_SERVICE_UUID.u,
            .includes = nullptr,
            .characteristics = CONTROL_CHARS,
        },
        {}, // mandatory to nible
    };

    static inline Control *_instance = nullptr;

public:
    struct ControlDirection
    {
        // Left stick
        int16_t Throttle = 0;
        int16_t Yaw = 0;

        // Right Stick:
        int16_t Pitch = 0;
        int16_t Roll = 0;

        uint8_t Start;
    };

    void Init();
    ControlDirection GetDirecction();

private:
    ControlDirection _direction;
};