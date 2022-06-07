./color_bgr2yuv_i420 ./lena.jpg ./out.yuv
ffplay -f rawvideo -video_size 512x512 out.yuv
