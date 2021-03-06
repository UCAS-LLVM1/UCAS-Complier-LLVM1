# RUN: llvm-mc -triple s390x-linux-gnu -show-encoding %s | FileCheck %s

#CHECK: chsi	0, 0                    # encoding: [0xe5,0x5c,0x00,0x00,0x00,0x00]
#CHECK: chsi	4095, 0                 # encoding: [0xe5,0x5c,0x0f,0xff,0x00,0x00]
#CHECK: chsi	0, -32768               # encoding: [0xe5,0x5c,0x00,0x00,0x80,0x00]
#CHECK: chsi	0, -1                   # encoding: [0xe5,0x5c,0x00,0x00,0xff,0xff]
#CHECK: chsi	0, 0                    # encoding: [0xe5,0x5c,0x00,0x00,0x00,0x00]
#CHECK: chsi	0, 1                    # encoding: [0xe5,0x5c,0x00,0x00,0x00,0x01]
#CHECK: chsi	0, 32767                # encoding: [0xe5,0x5c,0x00,0x00,0x7f,0xff]
#CHECK: chsi	0(%r1), 42              # encoding: [0xe5,0x5c,0x10,0x00,0x00,0x2a]
#CHECK: chsi	0(%r15), 42             # encoding: [0xe5,0x5c,0xf0,0x00,0x00,0x2a]
#CHECK: chsi	4095(%r1), 42           # encoding: [0xe5,0x5c,0x1f,0xff,0x00,0x2a]
#CHECK: chsi	4095(%r15), 42          # encoding: [0xe5,0x5c,0xff,0xff,0x00,0x2a]

	chsi	0, 0
	chsi	4095, 0
	chsi	0, -32768
	chsi	0, -1
	chsi	0, 0
	chsi	0, 1
	chsi	0, 32767
	chsi	0(%r1), 42
	chsi	0(%r15), 42
	chsi	4095(%r1), 42
	chsi	4095(%r15), 42
