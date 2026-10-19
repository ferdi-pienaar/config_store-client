cmake_minimum_required(VERSION 3.16)
project(config_store_client
    VERSION 1.0
    LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(config_store REQUIRED)

# Code generation by custom tool.
# The variables CONFIG_STORE_CODE_GEN and CONFIG_STORE_SCHEMA_DIR are set by config_store.
set(CFG_YAML ${CMAKE_CURRENT_SOURCE_DIR}/config/cfg.yaml)
set(GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated/tlv)
set(CFG_CPP ${GENERATED_DIR}/cfg.cpp)
set(CFG_H   ${GENERATED_DIR}/cfg.h)
set(DEPENDENCY_H   ${CMAKE_CURRENT_SOURCE_DIR}/src/cfg_depend.h)
set(SCHEMA_FILE ${CONFIG_STORE_SCHEMA_DIR}/cfg_schema.yaml)
set(ID_SCHEMA_FILE ${CONFIG_STORE_SCHEMA_DIR}/cfg_id_schema.yaml)

# Command creates subdirectory and generates C++ code.
add_custom_command(
    OUTPUT
        ${CFG_CPP}
        ${CFG_H}
    COMMAND
        ${CMAKE_COMMAND} -E make_directory ${GENERATED_DIR}
    COMMAND
        ${CONFIG_STORE_CODE_GEN}
        ${CFG_YAML}
        "tlv"
        ${CFG_H}
        ${CFG_CPP}
        ${DEPENDENCY_H}
        ${SCHEMA_FILE}
        ${ID_SCHEMA_FILE}
    DEPENDS
        ${CFG_YAML}
        ${CONFIG_STORE_CODE_GEN}
    COMMENT "Generating ${CFG_H} and ${CFG_CPP} from ${CFG_YAML}"
)

add_executable(config_store_client
    src/composition_root.cpp
    src/client.cpp
    src/operator.cpp
    src/my_cfg_fn1.cpp
    ${CFG_CPP}
)

target_include_directories(config_store_client
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${GENERATED_DIR}
)

target_link_libraries(config_store_client
    PRIVATE
        config_store::config_store_tlv
)
