## Dockerfile to build opencv from sources with CUDA support
## Creator : Thomas Herbin
## Heavily based on Josip Janzic file
##
## 20 december 2017

FROM nvidia/cuda:10.1-devel-ubuntu18.04

ARG https_proxy
ARG http_proxy

########################
###  OPENCV INSTALL  ###
########################

ENV DEBIAN_FRONTEND noninteractive
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
	curl \
	libxine2 \
	libmosquitto-dev \
	libmosquittopp-dev \
	supervisor \
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
    -DWITH_CUDA=ON \
    -DCUDA_FAST_MATH=1 \
    -DWITH_CUBLAS=1 \
    -DCUDA_ARCH_BIN='6.0 6.1 6.2' \
    -DCUDA_ARCH_PTX="" \
    -DCUDA_TOOLKIT_ROOT_DIR=/usr/local/cuda-10.1 \
    -DWITH_NVCUVID=OFF \
    -DBUILD_opencv_cudacodec=OFF \
    -DWITH_CUBLAS=1 \
    -DWITH_IPP=ON \
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
RUN curl -sL https://deb.nodesource.com/setup_9.x | bash - && apt-get install -y nginx php7.2-cli php7.2-gd php7.2-curl php7.2-mbstring php7.2-dom php7.2-zip php7.2-fpm nodejs 
RUN dpkg -i $OPENCV_BUILD_PATH/*-dev.deb
RUN mkdir -p /root/.ssh
COPY id_rsa.github /root/.ssh/id_rsa.github
COPY sshconfig /root/.ssh/config
RUN chmod 400 /root/.ssh/*


ARG MACHINERY_SRCREV=83e054fba6e748dbf2570ec11ef0b3f214f9f3f5

RUN cd /opt && GIT_SSL_NO_VERIFY=true git clone git@github.com:chpap/machinery.git && cd machinery && git checkout ${MACHINERY_SRCREV} && mkdir /opt/machinery/build && cd /opt/machinery/build && cmake .. && make install
COPY configs/*.xml /etc/opt/kerberosio/config/
RUN  chown -Rf www-data.www-data /etc/opt/kerberosio && \
    chmod -Rf 777 /etc/opt/kerberosio/config

RUN git clone https://github.com/kerberos-io/web /var/www/web && cd /var/www/web && git checkout master && \
chown -Rf www-data.www-data /var/www/web
RUN curl -sS https://getcomposer.org/installer | php -- --install-dir=/usr/local/bin --filename=composer 
RUN cd /var/www/web && \
composer install --prefer-source && \
npm install -g bower && \
cd public && \
nodejs /usr/lib/node_modules/bower/bin/bower --allow-root install

RUN rm /var/www/web/public/capture && \
ln -s /etc/opt/kerberosio/capture/ /var/www/web/public/capture

# Fixes, because we are now combining the two docker images.
# Docker is aware of both web and machinery.
RUN sed -i -e "s/'insideDocker'/'insideDocker' => false,\/\//" /var/www/web/app/Http/Controllers/SystemController.php
# RUN sed -i -e "s/\$output \=/\$output \= '';\/\//" /var/www/web/app/Http/Controllers/SettingsController.php
RUN sed -i -e "s/service kerberosio status/supervisorctl status machinery \| grep \"RUNNING\"';\/\//" /var/www/web/app/Http/Repositories/System/OSSystem.php

###################
# nginx site conf

RUN rm -Rf /etc/nginx/conf.d/* && rm -Rf /etc/nginx/sites-available/default 
ADD ./kerberosio.conf /etc/nginx/sites-available/default

##################################
# Fix PHP-FPM environment variables

RUN sed -i 's/"GPCS"/"EGPCS"/g' /etc/php/7.2/fpm/php.ini
RUN sed -i 's/"--daemonize/"--daemonize --allow-to-run-as-root/g' /etc/init.d/php7.2-fpm
RUN sed -i 's/www-data/root/g' /etc/php/7.2/fpm/pool.d/www.conf
RUN sed -i 's/www-data/root/g' /etc/nginx/nginx.conf

# Merged supervisord config of both web and machinery
ADD ./supervisord.conf /etc/supervisord.conf

# Merge the two run files.
ADD ./run.sh /runny.sh
RUN chmod 755 /runny.sh
RUN sed -i -e 's/\r$//' /runny.sh
##USER builduser
EXPOSE 8889
EXPOSE 80
# Make capture and config directory visible
VOLUME ["/etc/opt/kerberosio/capture"]
VOLUME ["/etc/opt/kerberosio/config"]
VOLUME ["/etc/opt/kerberosio/logs"]

# Make web config directory visible
VOLUME ["/var/www/web/config"]
VOLUME ["/opt/opencv"]
ENTRYPOINT ["sleep", "infinity"]
#CMD ["/bin/bash", "/runny.sh"]

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
