## 查看wav信息
```
$ ffprobe test_48k.wav
```

## wav -> pcm raw
```
$ ffmpeg -i test_48k.wav -f s16le -ar 48000 -acodec pcm_s16le test_48k_pcm.raw
```

## pcm raw -> wav
```
$ ffmpeg -f s16le -ar 48000 -ac 2 -i test_48k_pcm.raw -ar 48000 -ac 2 out.wav
$ ffmpeg -f s16le -ar 16000 -ac 2 -i test_16k_pcm.raw -ar 16000 -ac 2 test_16k.wav
```