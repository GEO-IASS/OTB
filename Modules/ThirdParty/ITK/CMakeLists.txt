project(OTBITK)

set(OTBITK_SYSTEM_INCLUDE_DIRS ${ITK_INCLUDE_DIRS})
set(OTBITK_LIBRARIES "${ITK_LIBRARIES}")
set(OTBITK_EXPORT_CODE_BUILD "find_package(ITK REQUIRED COMPONENTS ${OTBITK_ITK_REQUIRED_MODULE_LIST} HINTS ${ITK_DIR})")
set(OTBITK_EXPORT_CODE_INSTALL ${OTBITK_EXPORT_CODE_BUILD})

otb_module_impl()
