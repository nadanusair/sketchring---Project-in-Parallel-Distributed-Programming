In order to use our project, please write in your cmd the following line:
"sketchring.exe [input filename] [output filename] [inital number of sketches] [epsilon] [delta] [maximal number of sketches] [total number of elements]"
please change the [parameter name] with the value of this parameter.

You can also use the python script named run.py by writing in your cmd "python run.py", you can udjust the parameters in lines 8 to 16, 
from_acc, to_acc and step will let the sketchring.exe run with different accuracies from the value of from_acc to the value of to_acc with a step 
that you choose. input_filename, output_filename for the input and output file names. inital_sketches is the inital number of sketches.
delta is for the delta. maximal_sketches is for the maximal number of sketches. num_elements is for total number of elements in the input file.
You'll get 2 photos that will desrcibe the epsilon according to time, and epsilon according to error.
named: [input_filename]_time_acc_[from_acc]-[to_acc]_delta[delta].png and [input_filename]_error_acc_[from_acc]-[to_acc]_delta[delta].png
You need to download the packages numpy and matplotlib in order to use the python script.
Please write in your cmd:
pip install numpy
pip install matplotlib
