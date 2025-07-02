#/bin/sh

echo "$1"
PACKAGE_VERSION="$1"
if [ -z "$PACKAGE_VERSION" ]; then
   echo Unknown package version
   echo set to 0.9
   PACKAGE_VERSION=0.9
fi

BUILD_DIR=./Build
PORT_DIR=$BUILD_DIR/freebsd-port

PKG_PLIST=pkg-plist

echo Creating src archive based on next directories contents... 
echo Output: $PORT_DIR

if [ ! -d "$PORT_DIR" ]; then
  echo "$PORT_DIR does not exist."
  exit 1
fi

PORT_TAR_NAME=wxmathpanel-src-$PACKAGE_VERSION
rm -r -f $PORT_DIR/*
mkdir $PORT_DIR/$PORT_TAR_NAME

cp -r ./include $PORT_DIR/$PORT_TAR_NAME/
cp -r ./src $PORT_DIR/$PORT_TAR_NAME/
cp -r ./samples $PORT_DIR/$PORT_TAR_NAME/
cp -r ./builds $PORT_DIR/$PORT_TAR_NAME/
cp ./Makefile.in $PORT_DIR/$PORT_TAR_NAME/
cp ./configure $PORT_DIR/$PORT_TAR_NAME/
cp ./configure.ac $PORT_DIR/$PORT_TAR_NAME/
cp ./LICENCE.txt $PORT_DIR/$PORT_TAR_NAME/


command cd $PORT_DIR
tar czf $PORT_TAR_NAME.tar.gz $PORT_TAR_NAME
rm -r -f $PORT_TAR_NAME

command cd ../..




