execute_process(COMMAND "/home/frank/Documents/ws_raskar/ws_raskar/build/ultrasound/rosserial_python/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/frank/Documents/ws_raskar/ws_raskar/build/ultrasound/rosserial_python/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
