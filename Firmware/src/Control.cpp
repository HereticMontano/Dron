#include "Control.h"
#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"
#include "services/gap/ble_svc_gap.h"
#include "services/gatt/ble_svc_gatt.h"
#include <cstring>
#include "nvs_flash.h"

void Control::Init()
{
    if (_instance == nullptr)
    {
        _instance = this;
    }

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        nvs_flash_erase();
        nvs_flash_init();
    }

    nimble_port_init();
    ble_hs_cfg.sync_cb = OnBleSync;

    ble_svc_gap_init();
    ble_svc_gatt_init();
    ble_svc_gap_device_name_set("Dron");

    ble_gatts_count_cfg(GATT_SERVICES);
    ble_gatts_add_svcs(GATT_SERVICES);

    nimble_port_freertos_init(BleHostTask);
}

Control::ControlDirection Control::GetDirecction()
{
    return _instance->_direction;
}

int Control::OnControlAccess(uint16_t connHandle, uint16_t attrHandle, struct ble_gatt_access_ctxt *ctxt, void *arg)
{
    if (OS_MBUF_PKTLEN(ctxt->om) != sizeof(ControlDirection))
    {
        return BLE_ATT_ERR_INVALID_ATTR_VALUE_LEN;
    }

    if (_instance != nullptr && ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR)
    {
        ControlDirection received{};

        if (ble_hs_mbuf_to_flat(ctxt->om, &received, sizeof(received), nullptr) != 0)
        {
            return BLE_ATT_ERR_UNLIKELY;
        }

        _instance->_direction = received;
    }
    return 0;
}

void Control::BleHostTask(void *param)
{
    nimble_port_run();
    nimble_port_freertos_deinit();
}

void Control::OnBleSync()
{
    if (_instance != nullptr)
    {
        ble_hs_id_infer_auto(0, &_instance->_ownAddrType);
        StartAdvertising();
    }
}

void Control::StartAdvertising()
{
    struct ble_hs_adv_fields fields = {};
    fields.flags = BLE_HS_ADV_F_DISC_GEN | BLE_HS_ADV_F_BREDR_UNSUP;

    const char *name = ble_svc_gap_device_name();
    fields.name = reinterpret_cast<const uint8_t *>(name);
    fields.name_len = std::strlen(name);
    fields.name_is_complete = 1;

    ble_gap_adv_set_fields(&fields);

    struct ble_gap_adv_params advParam = {};
    advParam.conn_mode = BLE_GAP_CONN_MODE_UND;
    advParam.disc_mode = BLE_GAP_DISC_MODE_GEN;

    ble_gap_adv_start(
        _instance->_ownAddrType,
        nullptr,
        BLE_HS_FOREVER,
        &advParam,
        OnGapEvent,
        nullptr);
}

int Control::OnGapEvent(struct ble_gap_event *event, void *arg)
{
    switch (event->type)
    {
    case BLE_GAP_EVENT_CONNECT:
        if (event->connect.status != 0)
        {
            StartAdvertising();
        }
        break;
    case BLE_GAP_EVENT_DISCONNECT:
        _instance->_direction = {};
        StartAdvertising();
        break;
    case BLE_GAP_EVENT_ADV_COMPLETE:
        StartAdvertising();
        break;
    }

    return 0;
}
