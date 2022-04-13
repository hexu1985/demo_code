
msg="""action=add
devpath=/devices/pci0000:00/0000:00:14.0/usb2/2-3/2-3:1.0/host1/target1:0:0/1:0:0:0/block/sda/sda1
subsystem=block
devname=sda1
devtype=partition"""

print(msg)

lines=msg.split('\n')

print(lines)
for line in lines:
    key, value = line.split('=')
    print(key, value)
