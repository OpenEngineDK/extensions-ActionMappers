ADD_LIBRARY(Extensions_Actions
  empty.cpp # used to make sure we define a library/target
  Devices/MouseActionMapper.h
)

TARGET_LINK_LIBRARIES(Extensions_Actions
  OpenEngine_Core
  OpenEngine_Devices
)

SUBDIRS(tests)