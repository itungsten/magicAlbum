import win32file
import win32pipe
import sys

PIPE_NAME = r'\\.\pipe\AlbumPipe'
# paradigm for name
PIPE_BUFFER_SIZE = 65535

named_pipe = win32pipe.CreateNamedPipe(PIPE_NAME,
                                           win32pipe.PIPE_ACCESS_DUPLEX,
                                           win32pipe.PIPE_TYPE_MESSAGE | win32pipe.PIPE_WAIT | win32pipe.PIPE_READMODE_MESSAGE,
                                           win32pipe.PIPE_UNLIMITED_INSTANCES,
                                           PIPE_BUFFER_SIZE,
                                           PIPE_BUFFER_SIZE, 500, None)
i=0
while True:
    win32pipe.ConnectNamedPipe(named_pipe, None)
    
    i=i+1
    if not i==9:
      win32file.WriteFile(named_pipe,bytes('1',encoding='utf-8'))
    else :
      win32file.WriteFile(named_pipe,bytes('0',encoding='utf-8'))
      break
    data = win32file.ReadFile(named_pipe, PIPE_BUFFER_SIZE, None)

    if data is None or len(data) < 2:
      # one part of data is status code
        continue

    ack=data[1].decode('utf-8')
    print ('receive msg:', ack)

win32pipe.DisconnectNamedPipe(named_pipe)
