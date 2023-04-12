import numpy as np
import soundfile as sf
import fir1

np.seterr(all='raise')

# Read the file to clean
with sf.SoundFile('Vibraphone.wav', 'r') as wf: #opens Vibraphone.wav as a Soundfile object named wf
        wet = wf.read() #reads Vibraphone.wav and saves everything in a 2D array named wet
        print(f'Wet file. Samples: {wet.shape[0]}, max/min normalised samples: {max(wet)}, {min(wet)}')

# Read the dry version of the sound to be removed
with sf.SoundFile('Trumpet.wav', 'r') as df: #opens Trumpet.wav as a Soundfile object named df
        dry = df.read() #reads Trumpet.wav and saves everything in a 2D array named dry
        print(f'Dry file. Samples: {dry.shape[0]}, max/min normalised samples: {max(dry)}, {min(dry)}')

sr = 96000

# FIR Length in seconds
fl = 0.3

# Skip for the learning phase to igonre dead time at start of file
ss  = 4.9

# Set the filter learning rate
lrate = 0.002

nc = int(fl * sr)
fir = fir1.Fir1(nc) # Inits all coefficients and the buffer to zero. This is useful for adaptive filters where we start with zero valued coefficients.
fir.setLearningRate(lrate) #Setting the learning rate for the adaptive filter. param _mu The learning rate (i.e. rate of the change by the error signal)
ns = int(sr*ss)
training = dry[ns:] 
src = wet[ns:]
msi = np.mean(np.square(src))
fnum= 1

if len(training) != len(src) :
        raise 'interference and source samples are different lengths'

# Run a couple of seconds through the filter so it's started to learn.
trial = 2*sr

print('Pre-training...')
for i in range(trial if trial < len(src) else len(src)) :
        fir.lms_update(src[i]-fir.filter(training[i])) # fir.lms_update: Every filter coefficient is updated with:. w_k(n+1) = w_k(n) + learning_rate * buffer_k(n) * error(n). 
        #param error Is tsrc[i]-fir.filter(training[i])
# fir.filter: he actual filter function operation: it receives one sample and returns one sample. param input The input sample.
print('Processing')
error = np.zeros(len(training))
for i in range(len(training)) : 
        error[i] = src[i] - fir.filter(training[i]) # fir.filter: he actual filter function operation: it receives one sample and returns one sample. param input The input sample.
        fir.lms_update(error[i])

print(f'Power gain: {np.mean(np.square(error))/msi}')
sf.write(f'lr={lrate};fl={fl}s.wav', error, sr, 'PCM_24')




