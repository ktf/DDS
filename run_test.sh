#! /usr/bin/env bash


clean_up()
{
 popd
 exit 1
}

trap clean_up SIGHUP SIGINT SIGTERM


exec_test() {

if [ -e "./$1" ]; then
	echo ">>> Processing $1"
	"./$1" $2 || clean_up
	echo
else
	echo "WARNING: can't find $1"
fi

}

# TODO: pass DDS_LOCATION as an argument to the script
eval DDS_LOCATION=$1
if [ -z "${LD_LIBRARY_PATH}" ]; then
   LD_LIBRARY_PATH=$DDS_LOCATION/lib; export LD_LIBRARY_PATH
else
   LD_LIBRARY_PATH=$DDS_LOCATION/lib:$LD_LIBRARY_PATH; export LD_LIBRARY_PATH
fi

# Mac OS X
if [ -z "${DYLD_LIBRARY_PATH}" ]; then
   DYLD_LIBRARY_PATH=$DDS_LOCATION/lib; export DYLD_LIBRARY_PATH   # Mac OS X
else
   DYLD_LIBRARY_PATH=$DDS_LOCATION/lib:$DYLD_LIBRARY_PATH; export DYLD_LIBRARY_PATH
fi


pushd $(pwd)
cd "$1"/tests


echo "Working directory: $(pwd)"
echo

echo "----------------------"
echo "MiscCommon UNIT-TESTs"
echo "----------------------"
exec_test "MiscCommon_test_MiscUtils"
#  we use --catch_system_errors=no here to prevent BOOST catching SIGCHLD
exec_test "MiscCommon_test_Process" "--catch_system_errors=no"
exec_test "MiscCommon_test_SysHelper"
exec_test "MiscCommon_test_FindCfgFile"

echo "----------------------"
echo "dds-topology UNIT-TESTs"
echo "----------------------"
exec_test "dds-topology_tests"

popd

exit 0