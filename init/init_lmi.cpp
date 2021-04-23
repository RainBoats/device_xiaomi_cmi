/*
 * Copyright (c) 2021, The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "vendor_init.h"
#include "property_service.h"

void property_override(char const prop[], char const value[]) {
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi) {
        __system_property_update(pi, value, strlen(value));
    } else {
        __system_property_add(prop, strlen(prop), value, strlen(value));
    }
}

void vendor_load_properties() {
    std::string region = android::base::GetProperty("ro.boot.hwc", "");
    std::string product = android::base::GetProperty("ro.boot.product.hardware.sku", "");

    if (region.find("CN") != std::string::npos) {
        if (product.find("pro") != std::string::npos) {
            property_override("ro.product.device", "lmipro");
            property_override("ro.product.model", "Redmi K30 Pro Zoom Edition");
        } else {
            property_override("ro.product.model", "Redmi K30 Pro");
        }
    } else if (region.find("GLOBAL") != std::string::npos) {
        property_override("ro.product.brand", "POCO");
        property_override("ro.product.model", "POCO F2 Pro");
    }
}
