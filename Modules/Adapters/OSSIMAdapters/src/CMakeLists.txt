set(OTBOSSIMAdapters_SRC
  otbDEMHandler.cxx
  otbImageKeywordlist.cxx
  otbGeometricSarSensorModelAdapter.cxx
  otbSensorModelAdapter.cxx
  otbPlatformPositionAdapter.cxx
  otbDEMConvertAdapter.cxx
  otbRPCSolverAdapter.cxx
  otbDateTimeAdapter.cxx
  otbMapProjectionAdapter.cxx
  otbFilterFunctionValues.cxx
  otbMetaDataKey.cxx
  otbEllipsoidAdapter.cxx
  otbSarSensorModelAdapter.cxx
  )

add_library(OTBOSSIMAdapters ${OTBOSSIMAdapters_SRC})
target_link_libraries(OTBOSSIMAdapters
  ${OTBGDAL_LIBRARIES}
  ${OTBCommon_LIBRARIES}
  ${OTBOssim_LIBRARIES}
  ${OTBOssimPlugins_LIBRARIES}
  ${OTBOpenThreads_LIBRARIES}

  )

otb_module_target(OTBOSSIMAdapters)
