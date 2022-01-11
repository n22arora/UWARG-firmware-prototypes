import serial

ser = serial.Serial('COM5', 115200)
# ser.baudrate = 115200
# ser.port = "COM5"
# ser.open()
print(ser.name)
# arr = ['$', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\xa3', 's', '~', '\x8a', '\xe3', '8', '&', '@', '.', '\xc9', '\x01', '\xbb', '\x9a', '8','6', '@', 'E', ',', 'b', '\xd8', 'a', '\xaa', '@', '@', '\xb3', '\xc3', '1', 'B', 'V', '4', '^', 'B', '}', 'R', '\x85', 'B', 'a', '\x06', '\x00', '\x08']
arr = [b'\x00', b'\xb8', b'\x1e', b'\x85', b'\xeb', b'Q', b'8', b'&', b'@', b'\xb8', b'\x1e', b'\x85', b'\xeb', b'Q', b'8', b'6',b'$', b'\x01', b'\x01', b'\x01', b'\x00', b'\x00', b'\x00', b'\x00', b'\xb8', b'\x1e', b'\x85', b'\xeb', b'Q', b'8', b'&', b'@', b'\xb8', b'\x1e', b'\x85', b'\xeb', b'Q', b'8', b'6', b'@']
# ser.write(arr[0])

for i in arr:
    ser.write(i)


try: 
    while True:
        # arr.append(ser.read())
        # print(arr)
        print(ser.read())
except KeyboardInterrupt:
    exit()
# print("hello")
# b'\xc5'
# b'\x07'
# b'\x00'
# b'\x08'

# an_int = 5

# a_bytes_big = an_int.to_bytes(2, 'big')
# print(a_bytes_big)
# ptr = int(a_bytes_big)
# print(ptr)
