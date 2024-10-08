/**
 * Copyright (c) 2019 Oticon A/S
 *
 * SPDX-License-Identifier: Apache-2.0
 */
/**
 * @brief Service B.3
 *
 *  This code is auto-generated from the Excel Workbook
 *  'GATT_Test_Databases.xlsm' Sheet: 'Large Database 1'
 */
#include <zephyr/sys/byteorder.h>
#include <zephyr/sys/printk.h>

#include <zephyr/bluetooth/gatt.h>

#include "gatt_macs.h"

/**
 *  @brief UUID for the Service B.3
 */
#define BT_UUID_SERVICE_B_3             BT_UUID_DECLARE_16(0xa00b)

/**
 *  @brief UUID for the Value V6 Characteristic
 */
#define BT_UUID_VALUE_V6                BT_UUID_DECLARE_16(0xb006)

static uint8_t   value_v6_value = 0x06;
static bool   value_v6_ntf_active;

/**
 * @brief Attribute read call back for the Value V6 attribute
 *
 * @param conn   The connection that is requesting to read
 * @param attr   The attribute that's being read
 * @param buf    Buffer to place the read result in
 * @param len    Length of data to read
 * @param offset Offset to start reading from
 *
 * @return       Number of bytes read, or in case of an error - BT_GATT_ERR()
 *               with a specific ATT error code.
 */
static ssize_t read_value_v6(struct bt_conn *conn,
			     const struct bt_gatt_attr *attr, void *buf,
			     uint16_t len, uint16_t offset)
{
	const uint8_t *value = attr->user_data;

	return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
				 sizeof(value_v6_value));
}

/**
 * @brief Attribute write call back for the Value V6 attribute
 *
 * @param conn   The connection that is requesting to write
 * @param attr   The attribute that's being written
 * @param buf    Buffer with the data to write
 * @param len    Number of bytes in the buffer
 * @param offset Offset to start writing from
 * @param flags  Flags (BT_GATT_WRITE_*)
 *
 * @return       Number of bytes written, or in case of an error - BT_GATT_ERR()
 *               with a specific ATT error code.
 */
static ssize_t write_value_v6(struct bt_conn *conn,
			      const struct bt_gatt_attr *attr, const void *buf,
			      uint16_t len, uint16_t offset, uint8_t flags)
{
	uint8_t *value = attr->user_data;

	if (offset >= sizeof(value_v6_value)) {
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
	}
	if (offset + len > sizeof(value_v6_value)) {
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_ATTRIBUTE_LEN);
	}

	memcpy(value + offset, buf, len);

	return len;
}

/**
 * @brief Descriptor configuration change call back for the Value V6 attribute
 *
 * @param attr  The attribute whose descriptor configuration has changed
 * @param value The new value of the descriptor configuration
 */
static void value_v6_ccc_cfg_changed(const struct bt_gatt_attr *attr,
				     uint16_t value)
{
	value_v6_ntf_active = value == BT_GATT_CCC_NOTIFY;
}

static struct bt_gatt_attr service_b_3_1_attrs[] = {
	BT_GATT_H_PRIMARY_SERVICE(BT_UUID_SERVICE_B_3, 0x50),
	BT_GATT_H_CHARACTERISTIC(BT_UUID_VALUE_V6,
		BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE_WITHOUT_RESP |
		BT_GATT_CHRC_WRITE | BT_GATT_CHRC_NOTIFY,
		BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
		read_value_v6, write_value_v6, &value_v6_value, 0x51),
	BT_GATT_H_CCC(value_v6_ccc_cfg, value_v6_ccc_cfg_changed, 0x53)
};

static struct bt_gatt_service service_b_3_1_svc =
		    BT_GATT_SERVICE(service_b_3_1_attrs);

/**
 * @brief Register the Service B.3 and all its Characteristics...
 */
void service_b_3_1_init(void)
{
	bt_gatt_service_register(&service_b_3_1_svc);
}

/**
 * @brief Un-Register the Service B.3 and all its Characteristics...
 */
void service_b_3_1_remove(void)
{
	bt_gatt_service_unregister(&service_b_3_1_svc);
}

/**
 * @brief Generate notification for 'Value V6' attribute, if notifications are
 *        enabled.
 */
void service_b_3_1_value_v6_notify(void)
{
	if (!value_v6_ntf_active) {
		return;
	}

	bt_gatt_notify(NULL, &service_b_3_1_attrs[1], &value_v6_value,
		       sizeof(value_v6_value));
}
