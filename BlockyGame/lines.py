import os

def ReadLines(filepath):
	# open file in read mode
	count  = 0
	comments = 0
	with open(filepath, 'r') as fp:
		for count, line in enumerate(fp):
			if(line.find("//") != -1):
				comments += 1
			pass
	return count + 1, comments

def CountLines():
	path ='app'
	list_of_files = []
	fileCount = 0
	for root, dirs, files in os.walk(path):
		for file in files:
			temp = file.split(".")
			if(temp[1] == "h" or temp[1] == "cpp" or temp[1] == "vert" or temp[1] == "frag"):
				if(files[0] != "FastNoiseLite.h"):
					fileCount += 1
					list_of_files.append(os.path.join(root,file))

	comments = 0
	count = 0
	for filepath in list_of_files:
		values = ReadLines(filepath)
		count += values[0]
		comments += values[1]

	print(f"{count} lines of pain\nin {fileCount} files\nwith {comments} comments\naverage lines per file {round(count / fileCount)}")
	input("");

if(__name__ == "__main__"):
	CountLines()
