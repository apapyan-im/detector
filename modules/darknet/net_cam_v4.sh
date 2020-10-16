#rm test_dnn_out.avi

./darknet detector test ./cfg/coco.data ./cfg/yolov4.cfg ./yolov4.weights rtsp://127.0.0.1:1337/test -i 0 -thresh 0.25



