#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
    DESTDIR_ARG="--root=$DESTDIR"
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/frank/ws_raskar_kinetic/src/ultrasound/rosserial_xbee"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/frank/ws_raskar_kinetic/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/frank/ws_raskar_kinetic/install/lib/python2.7/dist-packages:/home/frank/ws_raskar_kinetic/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/frank/ws_raskar_kinetic/build" \
    "/usr/bin/python2" \
    "/home/frank/ws_raskar_kinetic/src/ultrasound/rosserial_xbee/setup.py" \
    build --build-base "/home/frank/ws_raskar_kinetic/build/ultrasound/rosserial_xbee" \
    install \
    $DESTDIR_ARG \
    --install-layout=deb --prefix="/home/frank/ws_raskar_kinetic/install" --install-scripts="/home/frank/ws_raskar_kinetic/install/bin"
