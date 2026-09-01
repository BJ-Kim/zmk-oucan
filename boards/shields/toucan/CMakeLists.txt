if(CONFIG_ZMK_BLE AND CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
  zephyr_library_sources(os_profile.c)
endif()
