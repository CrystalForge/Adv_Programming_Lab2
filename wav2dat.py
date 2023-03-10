#!/usr/bin/env python3

import soundfile as sf
import sys

data, samplerate = sf.read(sys.argv[1])

for s in data :
	print(s)

