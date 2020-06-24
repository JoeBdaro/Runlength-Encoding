
//Joseph Bdaro CS323_34 Project 6

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//run length class
class runLength {
public:
	int numRows;
	int numCols;
	int minVal;
	int maxVal;

	int whichMethod;
	string nameEncodeFile;

	//constructor
	runLength(int numRows, int numCols, int minVal, int maxVal, int whichMethod, string nameEncodeFile) {
		this->numRows = numRows;
		this->numCols = numCols;
		this->minVal = minVal;
		this->maxVal = maxVal;
		this->whichMethod = whichMethod;
		this->nameEncodeFile = nameEncodeFile;
	}

	//method1 for encoding
	void encodeMethod1(ifstream& inFile, ofstream& encodeFile) {
		int row = 0;
		int col = 0;
		int length = 0;
		int colNums = numCols;
		colNums = colNums-1;

		int currVal;
		int nextVal;

		//checks we don't exceed row count
		while (row < numRows) {
			col = 0;
			length = 1;

			//grabs first value and begins the entry for outfile
			inFile >> currVal;
			
			encodeFile << row << " " << col << " " << currVal << " ";
			
			//itteratres through columns 
			while (col < colNums) {
				col++;
				inFile >> nextVal;

				if (nextVal == currVal) {
					length++;
				}
				else {			
					encodeFile << length << endl;
					currVal = nextVal;
					length = 1;
					encodeFile << row << " " << col << " " << currVal << " ";
				}
				
			}
			row++;
			encodeFile << length << endl;
		}	
	}

	void encodeMethod4(ifstream& inFile, ofstream& encodeFile)
	{
		int row = 0;
		int col = -1;
		int length = 1;
		int zeroCount = 0;
		int lastVal = skipZero(inFile, row, col, zeroCount);
		int nextVal;
		encodeFile << row << " " << col << " " << lastVal << " ";


		//checks if end of file
		while (!inFile.eof())
		{
			//grabs the next value
			nextVal = skipZero(inFile, row, col, zeroCount);

			//if there was a zero detected the length printed lastval is changed to new nextVal, length is reset, and new entry is made in outfile 
			if (zeroCount > 0)
			{
				encodeFile << length << endl;
				lastVal = nextVal;
				length = 0;
				encodeFile << row << " " << col << " " << lastVal << " ";

			}
			//increments the length if lastval and nextval are equal
			if (nextVal == lastVal)
			{
				length++;
			}
			//if not then set last val to next and output the length, create a new entry in the outfile for the new bit and reset the length
			else
			{
				
				lastVal = nextVal;
				encodeFile << length << endl;
				encodeFile << row << " " << col << " " << lastVal << " ";
				length = 1;
				
			}
		}

	}

	int skipZero(ifstream& inFile, int& row, int& col, int& zeroCnt) {
		zeroCnt = 0;
		int pixelVal;

		//increments the col as the while loop is about to read a nextbit once (like a start increment)
		col++;
		while (inFile >> pixelVal && pixelVal == 0) {
			
			//if the pixel is a zero then we go up
			if (pixelVal == 0) {
				zeroCnt++;
			}

			// if the pixel val is zero and col is equal to or exceeds num of cols set the col to 0 and incrmeent the rows
			if (col >= numCols) {
				col = 0;
				row++;
			}
			//go up a col now
			col++;
		}

		//if you have reached end of column but the pixel isnt zero
		if (col >= numCols) {
			col = 0;
			row++;
		}
		return pixelVal;
	}
};

//Method used for extract the file name of argv1 without the extenstion
string nameOutFile(string nameEncodeFile) {
	string result;
	for (int i = 0; nameEncodeFile[i] != '.'; i++) {
		result += nameEncodeFile[i];
	}
	return result;
}

int main(int argc, char* argv[])
{
	ifstream inFile;
	inFile.open(argv[1]);
	ofstream outFile1;


	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int whichMethod;
	string nameEncodeFile;

	inFile >> numRows;
	inFile >> numCols;
	inFile >> minVal;
	inFile >> maxVal;
	whichMethod = strtol(argv[2], NULL, 10);


	//used to create the file name pertaining to infile and method choice
	nameEncodeFile = argv[1];
	nameEncodeFile = nameOutFile(nameEncodeFile) + "_EncodeMethod" + to_string(whichMethod) + ".txt";
	
	//newImage object gets created and opens the file based on the name created
	runLength* newImage = new runLength(numRows, numCols, minVal, maxVal, whichMethod, nameEncodeFile);
	outFile1.open(newImage->nameEncodeFile);
	outFile1 << newImage->numRows << " " << newImage->numCols << " " << newImage->minVal << " " <<newImage->maxVal << endl;
	outFile1 << newImage->whichMethod << endl;

	//decides which methods is executed based on argv2 entry
	switch (newImage->whichMethod) {
	case 1:
		newImage->encodeMethod1(inFile, outFile1);
		outFile1.close();
		inFile.close();
	case 4: 
		newImage->encodeMethod4(inFile, outFile1);
		outFile1.close();
		inFile.close();
	}
	





}






