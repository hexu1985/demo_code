## 查看wav信息
```
$ ffprobe test_48k_s16le_2c.wav
```

## wav -> pcm raw
```
$ ffmpeg -i test_48k_s16le_2c.wav -f s16le -ar 48000 -acodec pcm_s16le test_48k_s16le_2c_pcm.raw
```

## pcm raw -> wav
```
$ ffmpeg -f s16le -ar 48000 -ac 1 -i test_48k_pcm.raw -ar 48000 -ac 1 out.wav
$ ffmpeg -f s16le -ar 48000 -ac 1 -i test_48k_s16le_1c_pcm.raw -ar 48000 -ac 1 test_48k_s16le_1c.wav
```
