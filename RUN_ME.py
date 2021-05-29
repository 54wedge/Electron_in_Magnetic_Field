import os

## prompt user input
print("choose one type of B-field")
print("[1]constant = 1 [2]sin(t) [3]sin(t)+2 [4]Ohio? [555]Custum")
choose = int(input())

## locate where to put B_field function in Ode.cpp
index = 0
with open("Ode.cpp","r") as f:
	content = f.read().splitlines()
for i in range(len(content)):
	if content[i].startswith("//{Put B_field below}"):
		index = i

## cut out content before "//{Put B_field below}" so that B_field can be replaced
new_content = content[0:index+1]
#for line in new_content:
#	print(line)

## swap B_field function in Ode.cpp
while 1:         ## loop until a valid choice
	if choose == 1:
## The indentation is intented to be like this so that the indentation
## in Ode.cpp looks good. Sorry python. So is the rest of b_f
		b_f = "\
double B_field(double t){\n\
	return 1;\n\
}"
		break

	elif choose == 2:
		b_f = "\
double B_field(double t){\n\
	return sin(t);\n\
}"
		break

	elif choose == 3:
		b_f = "\
double B_field(double t){\n\
	return sin(t)+2;\n\
}"
		break

	elif choose == 4:
		b_f = "\
double B_field(double t){\n\
	if(t<=2*M_PI){\n\
		return -1.0;\n\
	}\n\
	else if(t<=2.525*M_PI && t>2*M_PI){\n\
		return -0.8/6*t;\n\
	}\n\
	else if(t<=2.85*M_PI && t>2.525*M_PI){\n\
		return 0;\n\
	}\n\
	else if(t<=2.9*M_PI && t>2.85*M_PI){\n\
		return 100;\n\
	}\n\
	else if(t<=3.55*M_PI && t>2.9*M_PI){\n\
		return 0;\n\
	}\n\
	else if(t<=3.6*M_PI && t>3.55*M_PI){\n\
		return -100;\n\
	}\n\
	else if(t<=3.9*M_PI && t>3.6*M_PI){\n\
		return 0;\n\
	}\n\
	else if(t<=4.233*M_PI && t>3.9*M_PI){\n\
		return 3;\n\
	}\n\
	else if(t<=4.5*M_PI && t>4.233*M_PI){\n\
		return 0;\n\
	}\n\
	else if(t<=4.6*M_PI && t>4.5*M_PI){\n\
		return -10;\n\
	}\n\
	else if(t<=4.95*M_PI && t>4.6*M_PI){\n\
		return 0;\n\
	}\n\
	else if(t<=5.05*M_PI && t>4.95*M_PI){\n\
		return 50;\n\
	}\n\
	else if(t<=5.4*M_PI && t>5.05*M_PI){\n\
		return 0;\n\
	}\n\
	else if(t<=5.45*M_PI && t>5.4*M_PI){\n\
		return -10;\n\
	}\n\
	else if(t<=5.65*M_PI && t>5.45*M_PI){\n\
		return 0;\n\
	}\n\
	else{\n\
		return -1.7;\n\
	}\n\
}"
		break

	elif choose == 555:
		func = input("Enter the custom function in C++ style: ")
		b_f = "\
double B_field(double t){\n\
	return {customFunc};\n\
}"
		b_f = b_f.replace("{customFunc}", func)
		break

## write the new content to Ode.cpp
new_content.append(b_f)
with open("Ode.cpp", "w+") as f:
	for line in new_content:
		#print(line+"\n")
		f.write(line+"\n")

## complie the whole project and show the result
print("compiling...")
if not os.system("g++ main.cpp Ode.cpp B_system.cpp -o main.x -O2 -std=c++17 -lgsl -lgslcblas"):
	os.system("./main.x")

os.system("gnuplot plot.plt -p")
