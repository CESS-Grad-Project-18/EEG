import time
import serial
import threading
import serial.tools.list_ports

class EmoSerializer: 
    def __init__(self, port, baudrate=9600, timeout=5): 
        ports = [port[1] for port in serial.tools.list_ports.comports() if port[2] != 'n/a']
        if port == None:
            port = "COM6"
        self.port = serial.Serial(port=port, baudrate=baudrate, 
        timeout=timeout, writeTimeout=timeout) 
        self.running = threading.Event()
        self.running.set()
        self.th = threading.Thread(target=self.read, args=(self.parse, ))
        self.th.start()
 
    def open(self): 
        self.port.open()
 
    def close(self): 
        self.running.clear()
        self.th.join()
        self.port.close() 
     
    def write(self, msg):
        if type(msg) == bytes:
            self.port.write(msg)
        elif type(msg) == str:
            self.port.write(str.encode(msg))
        else:
            self.port.write(str.encode(str(msg)))
 
    def readline(self):
        return self.port.readline()

    def __read(self, buf=b'', callback=None):
        if callback is None:
            callback = print

        # Read enough data for a message
        buf += self.port.read(self.port.inWaiting())
        print(buf)
        while b"R" not in buf or b"r" not in buf:
            buf += self.port.read(self.port.inWaiting())

        #In case multiple messages are received
        while b"R" in buf and b'r' in buf:
            # Find the message
            start = buf.find(b'R')
            buf = buf[start+1:]
            end = buf.find(b'r')
            msg_parts = buf[:end] #.split(",")
            buf = buf[end+1:]

            # Check the checksum to make sure the data is valid
            if msg_parts[-1] == b"checksum":
                callback(msg_parts[:-1])

        return buf
        # return buf.decode()

    def read(self, callback=None):
        buf = b''
        while self.running.is_set():
            buf = self.__read(buf, callback)

    def readim(self):
        return self.port.read(self.port.inWaiting())

    def parse(data):
        # Update UI
        print(data)
