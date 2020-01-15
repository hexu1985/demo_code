#! /usr/bin/python3
from pydub import AudioSegment
from sys import argv

sound = AudioSegment.from_mp3(argv[1])
sound.export(argv[2], format="wav")
