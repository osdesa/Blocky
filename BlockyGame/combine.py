import os

data = []


def ReadLines(filepath):
	# open file in read mode
	count  = 0
	data.append("\n")
	data.append(filepath.split("\\")[-1].title() + "\n")
	with open(filepath, 'r') as fp:
		for count, line in enumerate(fp):
			data.append(line)
	return count + 1

def CountLines():
	path ='app'
	list_of_files = []
	fileCount = 0
	for root, dirs, files in os.walk(path):
		for file in files:
			temp = file.split(".")
			if(temp[1] == "h" or temp[1] == "cpp" or temp[1] == "vert" or temp[1] == "frag" or temp[1] == "cs"):
				if(files[0] != "FastNoiseLite.h"):
					fileCount += 1
					list_of_files.append(os.path.join(root,file))

	count = 0
	for filepath in list_of_files:
		count += ReadLines(filepath)


	with open("output.txt", "w+") as txt_file:
		for line in data:
			txt_file.write("".join(line))

if(__name__ == "__main__"):
	CountLines()
