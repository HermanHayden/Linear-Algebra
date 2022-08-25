#include <iostream>
#include <string>
#include <vector>

//Finsished
std::vector<std::vector<int>> creation() {
	std::cout << "Dimensions: ";
	int row{ 0 };
	int col{ 0 };
	std::cin >> row;
	std::cin >> col;

	std::vector<std::vector<int>> vect;

	for (int r{ 0 }; r < row; r++) {
		std::vector<int> test;
		for (int c{ 0 }; c < col; c++) {
			int input{ 0 };
			std::cin >> input;
			test.push_back(input);
		}
		vect.push_back(test);
	}

	return vect;
 }
void moveZeroRows(std::vector<std::vector<int>>& matrix) {
	for (int r{ 0 }; r < matrix.size(); r++) {
		bool allZeros{ true };
		std::vector<int> line;

		for (int c{ 0 }; c < matrix[r].size(); c++) {
			//Check if a nonzero is found
			if (matrix[r][c] != 0) { allZeros = false; }
		}

		//Copy the Row of zeros, and remove
		if (allZeros) {
			std::vector<int> test = matrix.at(r);
			matrix.erase(matrix.begin() + r);
			matrix.push_back(test);
		}
		
	}
}
void print(std::vector<std::vector<int>> matrix) {
	std::cout << "\n";
	for (int r{ 0 }; r < matrix.size(); r++) {
		for (int c{ 0 }; c < matrix[r].size(); c++) {
			std::cout << matrix[r][c] << " ";
		}
		std::cout << "\n";
	}
}

//Testing
//void echelon(std::vector<std::vector<int>>& matrix) {
//	int lowest{ 0 };
//	int row{ -1 };
//	for (int r{ 0 }; r < matrix.size(); r++) {
//		for (int c{ 0 }; c < matrix[r].size(); c++) {
//
//		}
//	}
//}

int main() {
	bool echelonForm{ false };
	bool reducedEchelonForm{ false };
	std::vector<std::vector<int>> matrix = creation();
	moveZeroRows(matrix);

	print(matrix);

}