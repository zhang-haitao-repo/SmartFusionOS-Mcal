file(GLOB sf_wrapper_srcs "./sf_wrapper*.c")

set(src_files
    ${sf_wrapper_srcs}
)

set(include_dirs
    sf_wrapper
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
