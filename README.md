# regeltechniek

Practical project for class Control Systems at the 'Anton de Kom Universiteit van Suriname' where we (group of 5) constructed a cooling system designed to cool down a cellphone which is being used during the online proctoring exams during the period in the covid-19 pandemic (where this protocol was enforced).

## index

- 'Arduino code' contains the file 'PIdrivenFan.ino' which has the main Arduino code used and a folder called 'Tests' which contains the tests/scripts used on the Arduino to run the experiments
- 'Python scripts' has the scripts used to convert the copied input fromt the output of the Arduino on the PC (COM) and pasted in a textfile.
  which is then copied to an Excel file from which the data is turned into a dataframe, using Pandas library, and plotted with Matplotlib
