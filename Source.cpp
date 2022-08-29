#include <iostream>
#include <string>
#include <vector>

//Finsished
std::vector<std::vector<float>> creation() {
	std::cout << "Dimensions: ";
	float row{ 0 };
	float col{ 0 };
	std::cin >> row;
	std::cin >> col;

	std::vector<std::vector<float>> vect;

	for (int r{ 0 }; r < row; r++) {
		std::vector<float> test;
		for (int c{ 0 }; c < col; c++) {
			float input{ 0 };
			std::cin >> input;
			test.push_back(input);
		}
		vect.push_back(test);
	}

	return vect;
 }
void echelon(std::vector<std::vector<float>>& matrix) {
	//Find Zero Rows
	int zeros{ 0 };
	std::vector<float> zeroRow;
	for (int r{ 0 }; r < matrix.size(); r++) {
		bool allZeros{ true };
		std::vector<float> line;

		for (int c{ 0 }; c < matrix[r].size(); c++) {
			//Check if a nonzero is found
			if (matrix[r][c] != 0) { 
				allZeros = false;
			}
		}

		//Copy the Row of zeros, and remove
		if (allZeros) {
			zeroRow = matrix.at(r);
			zeros++;
			matrix.erase(matrix.begin() + r);
			r--;
		}
	}

	std::vector<std::vector<float>> newMatrix;

	int rows = matrix[0].size();
	for (int c{ 0 }; c < rows; c++) {
		for (int r{ 0 }; r < matrix.size(); r++) {
			if (matrix.size() > 0 && matrix[r][c] != 0) {
				newMatrix.push_back(matrix[r]);
				matrix.erase(matrix.begin() + r);
				r -= 1;
			}
		}
	}

	matrix = newMatrix;

	//Make new Matrix to be returned
	for (int i{ 0 }; i < zeros; i++) {
		matrix.push_back(zeroRow);
	}
}
void print(std::vector<std::vector<float>> matrix) {
	std::cout << "\n";
	for (int r{ 0 }; r < matrix.size(); r++) {
		for (int c{ 0 }; c < matrix[r].size(); c++) {
			std::cout << matrix[r][c] << " ";
		}
		std::cout << "\n";
	}
}
void printRow(std::vector<float> matrix) {
	for (auto x : matrix) {
		std::cout << x << " ";
	}
	std::cout << "\n";
}

//Testing
void fixLeading(std::vector<std::vector<float>>& matrix) {
	float leading = matrix.at(0).at(0);
	float rows = matrix.size();
	bool turn{ matrix.at(0).at(0) != 1 };

	//ADD
	for (int r{ 1 }; (r < rows && turn); r++) {
		if (leading + matrix[r][0] == 1) {
			std::cout << "R1 + R" << r + 1 << " -> R1\n";
			for (int c{ 0 }; c < matrix[0].size(); c++) { matrix[0][c] += matrix[r][c]; }
			turn = false;
		}
	}
	//SUB
	for (int r{ 1 }; r < rows && turn; r++) {
		if (leading - matrix[r][0] == 1) {
			std::cout << "R1 - R" << r + 1 << " -> R1\n";
			for (int c{ 0 }; c < matrix[0].size(); c++) { matrix[0][c] -= matrix[r][c]; }
			turn = false;
		}
	}
	//Self DIV
	if (turn) {
		if (leading < 0) {
			std::cout << "-1/" << leading << "R1 -> R1\n";
			for (float& x : matrix[0]) { x /= -leading; }
		} else {
			std::cout << "1/" << leading << "R1 -> R1\n";
			for (float& x : matrix[0]) { x /= leading; }
		}
	}

}
void fixFollowingRows(std::vector<std::vector<float>>& matrix) {
	float leading = matrix.at(0).at(0);
	float rows = matrix.size();

	for (int r{ 1 }; r < matrix.size(); r++) {
		if (matrix[r][0] != 0) {
			float rowLeading{ matrix[r][0] };
			if (rowLeading < 0) {
				std::cout << "R" << r + 1 << " + " << (rowLeading * -1) << "R1 -> R" << r + 1;
				for (int c{ 0 }; c < matrix[0].size(); c++) { matrix[r][c] += -1 * rowLeading * matrix[0][c]; }

			}
			else {
				std::cout << "R" << r + 1 << " - " << rowLeading << "R1 -> R" << r + 1;
				for (int c{ 0 }; c < matrix[0].size(); c++) { matrix[r][c] -= rowLeading * matrix[0][c]; }
			}
		}
	}
}

void reducedEchelon(std::vector<std::vector<float>>& matrix) {
	std::vector<std::vector<float>> finalMatrix;

	int rows = matrix[0].size();
	for (int c{ 0 }; c < rows; c++) {
		std::vector<std::vector<float>> newMatrix;
		for (int r{ 0 }; r < matrix.size(); r++) {
			if (matrix.size() > 0 && matrix[r][c] != 0) {
				newMatrix.push_back(matrix[r]);
				matrix.erase(matrix.begin() + r);
				r -= 1;
			}
		}

		if (newMatrix.size() != 0) {
			fixLeading(newMatrix);
			if (newMatrix.size() != 1) {
				fixFollowingRows(newMatrix);
			}
		}
		for (std::vector<float> x : newMatrix) {
			finalMatrix.push_back(x);
		}
	}

	matrix = finalMatrix;
}

int main() {
	bool echelonForm{ false };
	bool reducedEchelonForm{ false };
	std::vector<std::vector<float>> matrix = creation();

	echelon(matrix);
	reducedEchelon(matrix);

	print(matrix);

}