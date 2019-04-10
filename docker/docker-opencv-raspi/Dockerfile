## Dockerfile to build opencv from sources 
## Creator : Thomas Herbin
## Heavily based on Josip Janzic file
##
## 20 december 2017

FROM raspbian/stretch

ARG https_proxy
ARG http_proxy

########################
###  OPENCV INSTALL  ###
########################

COPY qemu-arm-static /usr/bin

RUN apt-get update && \
        apt-get install -y \
	python-pip \
        build-essential \
        cmake \
        git \
        wget \
        unzip \
        yasm \
        pkg-config \
        libswscale-dev \
        libtbb2 \
        libtbb-dev \
        libjpeg-dev \
        libpng-dev \
        libtiff5-dev \
        libopenblas-dev \
        libtesseract-dev \
        libleptonica-dev \
        libavformat-dev \
        libpq-dev \
	libxine2-dev \
	libglew-dev \
	libtiff5-dev \
	libx264-dev \
	libv4l-dev \
	liblapacke-dev \
	libgtk-3-dev \
	libhdf5-dev \
	zlib1g-dev \
	libjpeg-dev \
	libavcodec-dev \
	libavformat-dev \
	libavutil-dev \
	libpostproc-dev \
	libswscale-dev \
	libeigen3-dev \
	libtbb-dev \
	libssl-dev \
	libgtk2.0-dev \
	libcurl4-openssl-dev \
	pkg-config \
        ##
        ## Python
        python-dev \
        python-numpy \
        python3-dev \
        python3-numpy \
	## VTK
	#libvtk6-dev \
        openssh-server \
        sudo \
	vim \
	libavresample-dev \
	gfortran \
	checkinstall \
    ## Cleanup
    && rm -rf /var/lib/apt/lists/*

#RUN pip install numpy

## Create install directory
## Force success as the only reason for a fail is if it exist
ARG OPENCV_VERSION=4.0.1
ARG OPENCV_SOURCE_PATH=/opt/opencv-src
ARG OPENCV_BUILD_PATH=/opt/opencv-build/$OPENCV_VERSION
ARG OPENCV_INSTALL_PATH=/opt/opencv-install/$OPENCV_VERSION

RUN mkdir -p $OPENCV_SOURCE_PATH; exit 0
RUN mkdir -p $OPENCV_BUILD_PATH; exit 0
RUN mkdir -p $OPENCV_INSTALL_PATH; exit 0

WORKDIR $OPENCV_SOURCE_PATH

## Single command to reduce image size
## Build opencv

RUN wget https://github.com/opencv/opencv/archive/$OPENCV_VERSION.zip \
    && unzip $OPENCV_VERSION.zip \
    && rm $OPENCV_VERSION.zip \
    && wget https://github.com/opencv/opencv_contrib/archive/$OPENCV_VERSION.zip \
    && unzip $OPENCV_VERSION.zip \
    && rm $OPENCV_VERSION.zip 
COPY cvstd_wrapper.hpp opencv-$OPENCV_VERSION/modules/core/include/opencv2/core/cvstd_wrapper.hpp

RUN apt-get update && apt-get -y install vim libavresample-dev
RUN useradd -r -u 1000 -g sudo builduser
RUN chown -R builduser $OPENCV_SOURCE_PATH
RUN chown -R builduser $OPENCV_BUILD_PATH

RUN  cd $OPENCV_BUILD_PATH \
    && cmake -DBUILD_TIFF=ON \
    -DBUILD_DOCS=OFF \
    -DBUILD_EXAMPLES=ON \
    -DBUILD_NEW_PYTHON_SUPPORT=ON \
    -DBUILD_WITH_DEBUG_INFO=OFF \
    -DBUILD_PACKAGE=OFF \
    -DBUILD_opencv_core=ON \
    -DBUILD_opencv_imgproc=ON \
    -DBUILD_opencv_highgui=ON \
    -DBUILD_opencv_video=ON \
    -DBUILD_opencv_apps=ON \
    -DBUILD_opencv_flann=ON \
    -DBUILD_opencv_gpu=ON \
    -DBUILD_opencv_ml=ON \
    -DBUILD_opencv_legacy=OFF \
    -DBUILD_opencv_calib3d=ON \
    -DBUILD_opencv_features2d=ON \
    -DBUILD_opencv_java=OFF \
    -DBUILD_opencv_objdetect=ON \
    -DBUILD_opencv_photo=ON \
    -DBUILD_opencv_nonfree=ON \
    -DBUILD_opencv_ocl=ON \
    -DBUILD_opencv_stitching=OFF \
    -DBUILD_opencv_superres=OFF \
    -DBUILD_opencv_ts=ON \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTS=ON \
    -DBUILD_PERF_TESTS=ON \
    -DBUILD_opencv_contrib=ON \
    -DBUILD_WITH_CAROTENE=OFF \
    -DCMAKE_BUILD_TYPE=RELEASE \
    -DWITH_FFMPEG=ON \
    -DWITH_GSTREAMER=ON \
    -DWITH_OPENGL=ON \
    -DWITH_V4L=ON \
    -DBUILD_PNG=OFF \
    -DBUILD_JPEG=ON \
    -DBUILD_ZLIB=ON \
    -DBUILD_opencv_java=OFF \
    -DENABLE_FAST_MATH=1 \
    -DCPU_DISPATCH=AVX,AVX2 \
    -DENABLE_PRECOMPILED_HEADERS=OFF \
    -DWITH_OPENCL=ON \
    -DWITH_QT=OFF \
    -DWITH_TBB=ON \
    -DFORCE_VTK=ON \
    -DWITH_EIGEN=ON \
    -DWITH_XINE=ON \
    -DWITH_GDAL=ON \
    -DWITH_1394=ON \
    -DBUILD_PROTOBUF=ON \
    -DBUILD_FAT_JAVA_LIB=OFF \
    -DCMAKE_INSTALL_PREFIX:PATH=$OPENCV_INSTALL_PATH \
    -DINSTALL_C_EXAMPLES=ON \
    -DINSTALL_TESTS=ON \
    -DOPENCV_EXTRA_MODULES_PATH=$OPENCV_SOURCE_PATH/opencv_contrib-4.0.1/modules \
    -DCPACK_BINARY_DEB=ON \
    -DCPACK_BINARY_STGZ=OFF \
    -DCPACK_BINARY_TGZ=OFF \
    -DCPACK_BINARY_TZ=OFF \
    -DCPACK_PACKAGE_INSTALL_DIRECTORY=$OPENCV_INSTALL_PATH \
    -DCPACK_PACKAGE_VERSION=$OPENCV_VERSION \
    -DEXTRA_MODULES_VCSVERSION=$OPENCV_VERSION \
    -DOPENCV_VCSVERSION=$OPENCV_VERSION \
    $OPENCV_SOURCE_PATH/opencv-$OPENCV_VERSION
    ##
    ## Add variable to enable make to use all cores
#USER root
#RUN  cd $OPENCV_BUILD_PATH \
#    && export NUMPROC=$(nproc --all) \
#    && make -j$NUMPROC install \
#    && checkinstall --default \
#--type debian --install=no \
#--pkgname opencv4 \
#--pkgversion "${VERSION}" \
#--pkglicense BSD \
#--deldoc --deldesc --delspec \
#--requires "ffmpeg,libjasper1" \
#--pakdir ~ --maintainer "${MAINTAINER}" --provides opencv4 \
#--addso --autodoinst \
#make install
RUN  cd $OPENCV_BUILD_PATH \
    && export NUMPROC=$(nproc --all) \
    && make -j$NUMPROC package
    ## Remove following lines if you need to move openCv
#    && rm $OPENCV_VERSION.zip 
#    && echo rm -r /opencv-$OPENCV_VERSION
## Compress the openCV files so you can extract them from the docker easily 
#RUN tar cvzf opencv-$OPENCV_VERSION.tar.gz --directory=$OPENCV_INSTALL_PATH .
USER builduser
VOLUME ["/opt/opencv"]
ENTRYPOINT ["sleep", "infinity"]

#RUN apt-get update && apt-get install -y openssh-server
#RUN mkdir /var/run/sshd
#RUN echo 'root:THEPASSWORDYOUCREATED' | chpasswd
#RUN sed -i 's/PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

# SSH login fix. Otherwise user is kicked off after login
#RUN sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd

#ENV NOTVISIBLE "in users profile"
#RUN echo "export VISIBLE=now" >> /etc/profile

#EXPOSE 22
#CMD ["/usr/sbin/sshd", "-D"]
