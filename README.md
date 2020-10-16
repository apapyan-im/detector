#Dependencies

<br>

#### CUDA Installation Guide
>https://gist.github.com/matheustguimaraes/43e0b65aa534db4df2918f835b9b361d
#### CUDART Install Command
```
sudo apt-get install -y --allow-downgrades \
     libnvinfer5=5.1.2-1+cuda10.0 \
     libnvinfer-dev=5.1.2-1+cuda10.0 && \
     sudo ln -s /usr/local/cuda/lib64/libcudart.so /usr/lib/libcudart.so
```
#### Open CV Build & Install Command
```
cd ~ && wget -O opencv.zip https://github.com/Itseez/opencv/archive/${OPENCV_VERSION}.zip && \
wget -O opencv_contrib.zip https://github.com/Itseez/opencv_contrib/archive/${OPENCV_VERSION}.zip && \
unzip opencv.zip && rm opencv.zip && mv opencv-${OPENCV_VERSION} opencv && \
unzip opencv_contrib.zip && rm opencv_contrib.zip && mv opencv_contrib-${OPENCV_VERSION} opencv_contrib && \
cd ~/opencv && \
mkdir build && \
cd build && \
cmake \
-D WITH_QT=ON \
-D WITH_OPENGL=ON \
-D FORCE_VTK=OFF \
-D WITH_TBB=OFF \
-D WITH_GDAL=OFF \
-D WITH_XINE=OFF \
-D BUILD_EXAMPLES=OFF \
-D ENABLE_PRECOMPILED_HEADERS=OFF \
-D BUILD_DOCS=OFF \
-D BUILD_PERF_TESTS=OFF \
-D BUILD_TESTS=OFF \
-D BUILD_opencv_apps=OFF \
-D WITH_GSTREAMER=OFF \
-D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
-D CMAKE_INSTALL_PREFIX=/usr/local \
-D WITH_CUDA=ON \
-D WITH_CUFFT=ON \
-D WITH_CUBLAS=ON \
-D WITH_CUDNN=ON \
-D ENABLE_FAST_MATH=1 \
-D CUDA_FAST_MATH=1 \
.. && \
make -j$(nproc) && \
sudo make install && \
sudo ldconfig
```

# Build

```
git clone https://github.com/apapyan-im/detector
cd detector/resources
bash download_wights.sh
cd ..
cmake .  
make 
```
# Run 
```
./detector WEBCAM_ID # Default is 0
```
