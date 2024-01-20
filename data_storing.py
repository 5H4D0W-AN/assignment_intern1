import pandas as pd

def writein(f, l):
	for i in range(0, len(l)):
		val = l[i]
		f.write(str(val) + '\n')

def solve(inp_path):
	data = pd.read_excel(inp_path)  #reading data from excel file and storing them in array

	n = data['Employee Name'].values
	it = data['Time'].values
	ot = data['Time Out'].values
	st = data['Timecard Hours (as Time)'].values
	p = data['Position ID'].values

	#for every array, storing them as txt file to work in c++ without additional libraries
	#for empty entries, value will be "nan"
	names = open('names.txt', 'w+')
	writein(names, n)
	names.close()
	in_time = open('in_time.txt', 'w+')
	writein(in_time, it)
	in_time.close()
	out_time = open('out_time.txt', 'w+')
	writein(out_time, ot)
	out_time.close()
	shift_time = open('shift_time.txt', 'w+')
	writein(shift_time, st)
	shift_time.close()
	position = open('position.txt', 'w+')
	writein(position, p)
	position.close()



inp_path = r"Assignment_Timecard.xlsx" #opening excel file in read only mode

solve(inp_path)						   #calling function solve	

