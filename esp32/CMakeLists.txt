file(GLOB esp32_drv_srcs "./esp32_drv*.cc")
file(GLOB esp32_wrapper_srcs "./esp32_wrapper*.cc")

set(src_files
    ${esp32_drv_srcs}
    ${esp32_wrapper_srcs}
)

set(include_dirs    
    esp32_drv
    esp32_wrapper
)

set(requires
    driver
    esp_timer
    esp_wifi
    nvs_flash
    sdmmc
)

set(priv_requires

)

idf_component_register(SRCS ${src_files}
            INCLUDE_DIRS ${include_dirs}
            EMBED_TXTFILES ${embed_files}
            REQUIRES ${requires}
            PRIV_REQUIRES ${priv_requires}
)
