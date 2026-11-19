#include "Control.h"

void Control::Init()
{
    ble_gatts_count_cfg(GATT_SERVICES);
    ble_gatts_add_svcs(GATT_SERVICES);

    if (_instance == nullptr)
    {
        _instance = this;
    }
}

Control::ControlDirection Control::GetDirecction()
{

    return _instance->_direction;
}

int Control::OnControlAccess(uint16_t connHandle, uint16_t attrHandle, struct ble_gatt_access_ctxt *ctxt, void *arg)
{
    if (OS_MBUF_PKTLEN(ctxt->om) == sizeof(ControlDirection))
    {
        return BLE_ATT_ERR_INVALID_ATTR_VALUE_LEN;
    }

    if (_instance != nullptr && ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR)
    {
        ControlDirection received{};

        if (ble_hs_mbuf_to_flat(ctxt->om, &received, sizeof(received), nullptr) == BLE_ATT_ERR_UNLIKELY)
        {
            return BLE_ATT_ERR_UNLIKELY;
        }

        _instance->_direction = received;
    }
    return 0;
}