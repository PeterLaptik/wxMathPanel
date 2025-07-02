#/bin/sh

echo "$1"
PACKAGE_VERSION="$1"
if [ -z "$PACKAGE_VERSION" ]; then
   echo Unknown package version
   echo set to 0.9
   PACKAGE_VERSION=0.9
fi

BUILD_DIR=./Build
BUILD_LIB_DIR=./Build/lib
INCLUDE_DIR=./include/
PORT_DIR=$BUILD_DIR/freebsd-port/wxmathpanel-$PACKAGE_VERSION-freebsd-port

PKG_PLIST=pkg-plist

echo Creating port info based on next directories contents: 
echo $BUILD_LIB_DIR
echo $INCLUDE_DIR

if [ ! -d "$BUILD_LIB_DIR" ]; then
  echo "$BUILD_LIB_DIR does not exist."
  exit 1
fi

if [ ! -d "$INCLUDE_DIR" ]; then
  echo "$INCLUDE_DIR does not exist."
  exit 1
fi

# Writing pkg-plist
mkdir -p $PORT_DIR
rm -f -r $PORT_DIR/*
touch $PORT_DIR/$PKG_PLIST

FILES_LIB=`ls $BUILD_DIR/lib`
for i in $FILES_LIB; 
	do 
		echo "lib/$i"; 
		echo "lib/$i" >> $PORT_DIR/$PKG_PLIST
	done;
	
FILES_INC=`ls $INCLUDE_DIR`
for i in $FILES_INC; 
	do 
		echo "include/wxmathpanel/$i"; 
		echo "include/wxmathpanel/$i" >> $PORT_DIR/$PKG_PLIST
	done;

cp ./builds/freebsd-port/pkg-descr $PORT_DIR/pkg-descr
cp ./builds/freebsd-port/Makefile $PORT_DIR/Makefile
sed -i '' "s|VERSION_NUM|$PACKAGE_VERSION|g" $PORT_DIR/Makefile

PORT_TAR_NAME=wxmathpanel-src-$PACKAGE_VERSION
sudo rm -f /usr/ports/distfiles/$PORT_TAR_NAME.tar.gz

command cd $PORT_DIR
make makesum

command cd ..
echo tar czf wxmathpanel-$PACKAGE_VERSION-freebsd-port.tar.gz wxmathpanel-$PACKAGE_VERSION-freebsd-port
tar czf wxmathpanel-$PACKAGE_VERSION-freebsd-port.tar.gz wxmathpanel-$PACKAGE_VERSION-freebsd-port
sudo chmod g+w,a+w wxmathpanel-$PACKAGE_VERSION-freebsd-port.tar.gz

echo rm -r wxmathpanel-$PACKAGE_VERSION-freebsd-port
rm -f -r wxmathpanel-$PACKAGE_VERSION-freebsd-port

command cd ../..




