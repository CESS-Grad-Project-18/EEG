import os
import sys
import threading
import pygame as pg
from Queue import Queue

class EmoMusicPlayer: 
    def __init__(self, freq=44100, bitsize=-16, channels=2, buffer=2048):
        self.q = Queue()
        self.freq = freq
        self.bitsize = bitsize
        self.channels = channels
        self.buffer = buffer
        pg.mixer.init(freq, bitsize, channels, buffer)
        self.clock = pg.time.Clock()
        self.playing = threading.Event()
        self.playing.set()
        self.th = threading.Thread(target=self.play, args=(, ))
        self.th.start()

 
    def __load(music_file):
        try:
            pg.mixer.music.load(music_file)
            print("{} loaded successfully".format(music_file))
        except pygame.error:
            print("File {} not found! {}".format(music_file, pg.get_error()))
            return
 
    def __play():
        result = self.q.get()
        if result == 0:
            self.__load() # Sad, not sleepy
        elif result == 1:
            self.__load() # Sad, sleepy
        elif result == 2:
            self.__load() # Happy, not sleepy
        elif result == 3:
            self.__load() # Happy, sleepy 
        else:
            pass
        pg.mixer.music.play()
        self.playing = True
        while pg.mixer.music.get_busy():
        try:
            clock.tick(30)
        except KeyboardInterrupt:
            pg.mixer.music.fadeout(1000)
            pg.mixer.music.stop()
            return -1

    def play():
        while self.playing.is_set():
            e_code = self.__play()


    
    def stop():
        pg.mixer.music.fadeout(1000)
        pg.mixer.music.stop()
        self.playing.clear()

 
