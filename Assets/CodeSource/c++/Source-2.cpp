#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cmath>
#include "Eigen/Dense"


//import C norms
extern "C" {

	//create a linear model with values between -1 and 1 
	__declspec(dllexport) double *linear_create_model(int inputDimension, int outputDimension) {
		/*if(inputDimension < 1 || outputDimension < 1) {
			return -1;
		}*/
		double *model = NULL;
		model = new double[(inputDimension + 1)*outputDimension];
		int i = 0;
		for (i; i < (inputDimension + 1)*outputDimension; i++) {
			model[i] = ((float)rand() / (float)RAND_MAX) * 2.0 - 1.0;
		}
		return model;
	}

	//delete the used model
	//reminder : malloc/free, new/delete, new[]/delete[] && don't mix
	__declspec(dllexport) void linear_remove_model(double *model) {
		/*if(model == nullptr) {
			return -1;
		}*/
		delete model;
	}

	//add the bias node to the perceptron layer
	__declspec(dllexport) double* add_bias(double* input, int inputSize) {
		/*if(input == nullptr || inputSize < 1) {
			return -1;
		}*/
		double* input2 = new double[2 + 1];
		input2[0] = 1;
		for (int i = 1; i <= inputSize; i++) {
			input2[i] = input[i - 1];
		}
		return input2;
	}

	//classify a model and return the perceptron's response
	__declspec(dllexport) void linear_classify(double *model, double *input, int inputSize, double* output, int outputSize) {
		/*if(model == nullptr || input == nullptr || inputSize < 1 || output == nullptr || outputSize < 1) {
			return -1;
		}*/
		double sum_w = 0;
		int i = 0;
		int j = 0;
		int k = 0;
		double* bias = add_bias(input, inputSize);

		for (i; i < outputSize; i++) {
			sum_w = 0;
			for (j, k = i; j <= inputSize && k < (inputSize + 1) * outputSize; j++, k += outputSize) {
				sum_w += model[k] * bias[j];
			}
			if (sum_w < 0) {
				output[i] = -1;
			}
			else {
				output[i] = 1;
			}
		}
	}

	//classification according to rosenblatt
	__declspec(dllexport) int linear_fit_classification_rosenblatt(double *model, double *inputs, int inputsSize, int inputSize, double *outputs, int outputsSize, int iterationNumber, double step) {
		/*if(model == nullptr || inputs == nullptr || inputsSize < inputSize || inputSize < 1 || outputs == nullptr || outputsSize < 1 || iterationNumber < 1 || step < 1) {
			//std::cout << "Model does not exist" << std::endl;
			return -1;
		}*/

		int iterationsNum = 0;
		int i = 0;
		int j = 0;
		int k = 0;
		int l = 0;
		int error = 0;

		while (true) {
			if (iterationsNum > iterationNumber) {
				return 1;
			}
			else {
				iterationsNum++;
			}

			double *inputs2 = new double[inputSize];
			double *outputs2 = new double[outputsSize];
			error = 0;

			for (int i = 0, j = 0; j < inputsSize; i += inputSize, j++) {
				for (int k = 0; k < inputSize; k++) {
					inputs2[k] = inputs[i + k];
				}

				linear_classify(model, inputs2, inputSize, outputs2, outputsSize);
				inputs2 = add_bias(inputs2, inputSize);
				bool* outputb = new bool[outputsSize];
				double* outputError = new double[outputsSize];
				bool outputsb = true;

				for (int l = 0; l < outputsSize; l++) {
					outputb[l] = true;
					//if (outputs2[l] != outputs[j*outputsSize + l]) {
						outputb[l] = false;
						if (outputsb) { outputsb = false; }
						outputError[l] = outputs[j*outputsSize + l] - outputs2[l];
					//}
				}
				if (!outputsb) {
					error++;
					for (int l = 0; l < outputsSize; l++) {
						if (!outputb[l]) {
							for (int m = l, j = 0; m < (inputSize + 1)*outputsSize; m += outputsSize, j++) {
								model[m] += step * outputError[l] * inputs2[j];
							}
						}
					}
				}
			}
			if (error == 0) {
				return 0;
			}
		}
	}

	__declspec(dllexport) double* add_bias_regression(double *inputs, int *inputSize, int *inputsSize) {
		/*if(inputs == nullptr || inputSize == nullptr || inputsSize == nullptr) {
			return -1;
		}*/
		int i = *inputSize / *inputsSize;
		int j = 0;
		int k = 0;
		*inputSize += i;
		double* inputs2 = new double[*inputSize + i];

		for (j; j < (*inputSize); j++) {
			if (j % (*inputsSize + 1) == 0) {
				inputs2[j] = 1;
				j++;
			}
			inputs2[j] = inputs[k];
			k++;
		}
		*inputsSize += 1;
		return inputs2;
	}

	// 	Array => MatrixXd
	__declspec(dllexport) void transfoMatrixXd(Eigen::MatrixXd* M, double *input, int row, int col) {
		/*if(M == nullptr || input == nullptr || row < 1 || col < 1) {
			return -1:
		}*/
		int i = 0;
		int j = 0;
		int k = 0;

		for (i; i < row; i++) {
			for (j; j < col; j++) {
				(*M)(i, j) = input[k];
				k++;
			}
		}
	}

	// MatrixXd => Array
	__declspec(dllexport) void transfoArray(Eigen::MatrixXd M, double *input, int row, int col) {
		/*if(M == nullptr || input == nullptr || row < 1 || col < 1) {
			return -1:
		}*/
		int i = 0;
		int j = 0;
		int k = 0;

		for (i; i < row; i++) {
			for (j; j < col; j++) {
				input[k] = M(i, j);
				k++;
			}
		}
	}

	//function to calculate the output of given input
	__declspec(dllexport) void linearPredict(Eigen::MatrixXd* model, double* input, int inputSize, double* output, int outputSize) {
		/*	if(model == nullptr || input == nullptr || inputSize < 1 || output == nullptr || outputSize < 1){
			return -1;
		}
		*/
		int i = 0;
		double* inputs2 = add_bias(input, inputSize);
		Eigen::MatrixXd M(1, inputSize + 1);
		Eigen::MatrixXd N(outputSize, 1);

		for (i; i < inputSize + 1; i++) {
			M(0, i) = inputs2[i];
		}

		N = M * (*model);
		transfoArray(N, output, 1, outputSize);
	}

	// Calculate the pseudo inverse of the given MatrixXd
	__declspec(dllexport) Eigen::MatrixXd pseudoInverse(Eigen::MatrixXd M, Eigen::MatrixXd N) {
		/*if(M == nullptr || N == nullptr) {
			return -1;
		}
		*/
		Eigen::MatrixXd TransposeM = M.transpose();
		return (((TransposeM * M).inverse()) * TransposeM)*N;
	}


	__declspec(dllexport) Eigen::MatrixXd* linear_fit_regression(double *inputs, int inputsSize, int inputSize, double *outputs, int outputsSize) {
		/*if(inputs == nullptr || inputsSize < 1 || inputSize < 1 || outputs == nullptr || outputsSize < 1) {
			return -1:
		}*/
		inputs = add_bias_regression(inputs, &inputsSize, &inputSize);
		int input = inputsSize / inputSize;
		Eigen::MatrixXd X(input, inputSize);
		Eigen::MatrixXd Y(input, outputsSize);

		transfoMatrixXd(&X, inputs, input, inputSize);
		transfoMatrixXd(&Y, outputs, input, outputsSize);

		return new Eigen::MatrixXd(pseudoInverse(X, Y));
	}

	//just a function to test the link between C# and C++ in the project
	__declspec(dllexport) int return42() {
		return 42;
	}

}