import time
import subprocess
import numpy as np
import matplotlib.pyplot as plt
import os


from_acc = 0.01
to_acc = 0.3
step = 0.02
input_filename = "Tests/test_generator22.txt"
output_filename = "Tests/test_generator22_out.txt"
inital_sketches = 3
delta = 0.01
maximal_sketches = 20
num_elements = 5000

params_list1 = [input_filename, output_filename, str(inital_sketches)] 
parmas_list2 = [str(delta), str(maximal_sketches), str(num_elements), "true"]
time_list = []
error_list = []
batcmd = "g++ *.cpp countmin/*.cpp countmin/*.cc -o sketchring.exe"
subprocess.check_output(batcmd, shell=True)
for eps in np.arange(from_acc, to_acc, step):
    params_list = params_list1 + [str(eps)] + parmas_list2
    start = time.time()
    batcmd = "sketchring.exe " + " ".join(params_list)
    os.system(batcmd)
    end = time.time()
    f = open("error.txt", "r")
    err = f.read()
    f.close()
    error_list = error_list + [float(err)]
    time_list = time_list + [end-start]
    
#batcmd = "Del /f \"error.txt\""
#subprocess.check_output(batcmd, shell=True)

#create epsilon according to the error plot:
plot1 = plt.figure(1)
plt.plot(np.arange(from_acc, to_acc, step), error_list, 'C1', label = 'epsilon according to the error.')
plt.xlabel('Epsilon')
plt.ylabel('Error')
plt.legend()
img_name = input_filename + "_error" +"_acc" + str(from_acc) + "-" + str(to_acc) + "_delta" + str(delta) + ".png"
plt.savefig(img_name)

#create epsilon according to the time plot:
plot2 = plt.figure(2)
plt.plot(np.arange(from_acc, to_acc, step), time_list, 'C1', label = 'epsilon according to the time.')
plt.xlabel('Epsilon')
plt.ylabel('Time')
plt.legend()
img_name = input_filename + "_time" +"_acc" + str(from_acc) + "-" + str(to_acc) + "_delta" + str(delta) + ".png"
plt.savefig(img_name)
