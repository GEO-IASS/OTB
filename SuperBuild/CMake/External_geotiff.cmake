if(NOT __EXTERNAL_GEOTIFF__)
set(__EXTERNAL_GEOTIFF__ 1)

if(USE_SYSTEM_GEOTIFF)
  message(STATUS "  Using libgeotiff system version")
else()
  SETUP_SUPERBUILD(PROJECT GEOTIFF)
  message(STATUS "  Using GeoTIFF SuperBuild version")

  # declare dependencies
  ADDTO_DEPENDENCIES_IF_NOT_SYSTEM(GEOTIFF TIFF PROJ JPEG ZLIB)

  set(GEOTIFF_SB_CONFIG)
  ADD_SUPERBUILD_CMAKE_VAR(GEOTIFF TIFF_INCLUDE_DIR)
  ADD_SUPERBUILD_CMAKE_VAR(GEOTIFF TIFF_LIBRARY)
  ADD_SUPERBUILD_CMAKE_VAR(GEOTIFF PROJ4_INCLUDE_DIR)
  ADD_SUPERBUILD_CMAKE_VAR(GEOTIFF PROJ4_LIBRARY)
  ADD_SUPERBUILD_CMAKE_VAR(GEOTIFF ZLIB_INCLUDE_DIR)
  ADD_SUPERBUILD_CMAKE_VAR(GEOTIFF ZLIB_LIBRARY)
  ADD_SUPERBUILD_CMAKE_VAR(GEOTIFF JPEG_INCLUDE_DIR)
  ADD_SUPERBUILD_CMAKE_VAR(GEOTIFF JPEG_LIBRARY)

  #RK: we are forced to use autoconf on osx due to cmake's find_* functions
  #Do we need to use the same of Linux ?
  if(APPLE)
    set(GEOTIFF_SB_CONFIG)
    ADD_SUPERBUILD_CONFIGURE_VAR(GEOTIFF PROJ_ROOT     --with-proj)
    ADD_SUPERBUILD_CONFIGURE_VAR(GEOTIFF TIFF_ROOT     --with-libtiff)
    ADD_SUPERBUILD_CONFIGURE_VAR(GEOTIFF JPEG_ROOT     --with-jpeg)
    ADD_SUPERBUILD_CONFIGURE_VAR(GEOTIFF ZLIB_ROOT     --with-libz)

    ExternalProject_Add(GEOTIFF
      PREFIX GEOTIFF
      URL "http://download.osgeo.org/geotiff/libgeotiff/libgeotiff-1.4.1.tar.gz"
      URL_MD5 48bdf817e6e7a37671cc1f41b01e10fc
      SOURCE_DIR ${GEOTIFF_SB_SRC}
      BINARY_DIR ${GEOTIFF_SB_SRC}
      INSTALL_DIR ${SB_INSTALL_PREFIX}
      DOWNLOAD_DIR ${DOWNLOAD_LOCATION}
      DEPENDS ${GEOTIFF_DEPENDENCIES}
      CONFIGURE_COMMAND
      ${SB_ENV_CONFIGURE_CMD}
      ${GEOTIFF_SB_SRC}/configure
      --prefix=${SB_INSTALL_PREFIX}
      --enable-static=no
      ${GEOTIFF_SB_CONFIG}
      BUILD_COMMAND $(MAKE)
      INSTALL_COMMAND $(MAKE) install)

      SUPERBUILD_PATCH_SOURCE(GEOTIFF)

  else()

    ExternalProject_Add(GEOTIFF
      PREFIX GEOTIFF
      URL "http://download.osgeo.org/geotiff/libgeotiff/libgeotiff-1.4.1.tar.gz"
      URL_MD5 48bdf817e6e7a37671cc1f41b01e10fc
      SOURCE_DIR ${GEOTIFF_SB_SRC}
      BINARY_DIR ${GEOTIFF_SB_BUILD_DIR}
      INSTALL_DIR ${SB_INSTALL_PREFIX}
      DOWNLOAD_DIR ${DOWNLOAD_LOCATION}
      DEPENDS ${GEOTIFF_DEPENDENCIES}
      CMAKE_CACHE_ARGS
      -DCMAKE_INSTALL_PREFIX:STRING=${SB_INSTALL_PREFIX}
      -DCMAKE_BUILD_TYPE:STRING=Release
      -DBUILD_SHARED_LIBS:BOOL=ON
      -DBUILD_TESTING:BOOL=OFF
      -DPROJ4_OSGEO4W_HOME:PATH=${SB_INSTALL_PREFIX}
      ${GEOTIFF_SB_CONFIG}
      CMAKE_COMMAND ${SB_CMAKE_COMMAND}
      )
  endif()

  set(_SB_GEOTIFF_INCLUDE_DIR ${SB_INSTALL_PREFIX}/include)
  if(WIN32)
    set(_SB_GEOTIFF_LIBRARY ${SB_INSTALL_PREFIX}/lib/geotiff_i.lib)
  elseif(UNIX)
    set(_SB_GEOTIFF_LIBRARY ${SB_INSTALL_PREFIX}/lib/libgeotiff${CMAKE_SHARED_LIBRARY_SUFFIX})
  endif()

endif()
endif()
