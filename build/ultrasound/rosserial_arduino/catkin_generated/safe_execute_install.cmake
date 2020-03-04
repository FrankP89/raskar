execute_process(COMMAND "/home/frank/ws_raskar_kinetic/build/ultrasound/rosserial_arduino/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/frank/ws_raskar_kinetic/build/ultrasound/rosserial_arduino/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
