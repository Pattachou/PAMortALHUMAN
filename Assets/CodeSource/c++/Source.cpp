#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

//pour importer les normes a respecter de C
extern "C" {
	
	//pour importer les config de windows 
	__declspec(dllexport) double *linear_create_model(int inputDimension)
	{
		double *model = NULL;
		model = (double*) malloc(sizeof(double) * (inputDimension));
		int i = 0;
		for (i; i < inputDimension; i++) {
			if ((rand() % 2) == 0) {
				model[i] = -1;
			} else {
				model[i] = 1;
			}
		}
		return model;
	}

	__declspec(dllexport) void linear_remove_model(double *model)
	{
		free(model);
	}

	__declspec(dllexport) double linear_classify(double *model, double *input, int inputSize)
	{
		double sum_w = 0;
		int i = 0;
		double tmp = 0;

		for (i; i < inputSize; i++) {
			tmp = model[i] * input[i];
			sum_w += tmp;
		}

		if (sum_w < 0) {
			return -1;
		}
		else {
			return 1;
		}
	}

	__declspec(dllexport) double linear_predict(double *model, double *input, int inputSize)
	{
		double sum_w = 0;
		int i = 0;
		double tmp = 0;

		for (i; i < inputSize; i++) {
			tmp = model[i] * input[i];
			sum_w += tmp;
		}

		return sum_w;
	}

	__declspec(dllexport) int hebb_learning(double *model, double* inputs2, int inputSize, double output, double step)
	{
		int i = 0;
		double tmp = 0;
		double output2 = linear_classify(model, inputs2, inputSize);

		if (output2 != output) {
			for (i; i < inputSize; i++) {
				tmp = step * output * inputs2[i];
				model[i] += tmp;
			}
			return 1;
		}
		else {
			return 0;
		}
	}

	__declspec(dllexport) double rosen_learning(double *model, double *inputs2, int inputSize, double output, double step) {
		int i = 0;
		double tmp = 0;
		double error = 0;
		double output2 = linear_classify(model, inputs2, inputSize);

		if (output2 != output) {
			error = output - output2;

			for (i; i <= inputSize; i++) {
				tmp = step * error * inputs2[i];
				model[i] += tmp;
			}
		}
		return output2;
	}

	__declspec(dllexport) double lr_learning() {
		return 0;
	}


	__declspec(dllexport) int linear_fit_regression(double *model, double *inputs, int inputsSize, int inputSize, double *outputs, int outputsSize) 
	{
		if (model == nullptr) {
			std::cout << "Model does not exist" << std::endl;
			return -1;
		}

		int i = 0;
		int j = 0;
		int o = 0;
		int error = 0;

		double *inputs2 = (double *)malloc(sizeof(double) * inputSize);

		while (true) {
			for (i; i < inputsSize; i += inputSize) {
				for (j; j < inputSize; j++) {
					inputs2[j] = inputs[i + j];
				}
				error += lr_learning();
				o++;
				j = 0;
			}
			if (error == 0) {
				free(inputs2);
				return 0;
			}

			i = 0;
			j = 0;
			o = 0,
				error = 0;
		}

		return 30;
	}

	__declspec(dllexport) int linear_fit_classification_hebb(double *model, double *inputs, int inputsSize, int inputSize, double *outputs,int iterationNumber, double step) 
	{
		if (model == nullptr) {
			std::cout << "Model does not exist" << std::endl;
			return -1;
		}

		int iterationsNum = 0;
		double *inputs2 = (double*)malloc(sizeof(double) * inputSize);
		int i = 0;
		int j = 0;
		int o = 0;
		int error = 0;

		while(true) {
			if (iterationsNum > iterationNumber){
				free(inputs2);
				return -1;
			} else {
				iterationsNum++;
			}

			for(i;i < inputsSize; i += inputSize){
				for (j; j < inputSize; j++){
					inputs2[j] = inputs[i + j];
				}
				error += hebb_learning(model, inputs2, inputSize, outputs[o], step);
				o++;
			}
			if (error == 0) {
				free(inputs2);
				return 0;
			}

			i = 0;
			j = 0;
			o = 0;
			error = 0;
		}

	}

	__declspec(dllexport) int linear_fit_classification_rosenblatt(double *model, double *inputs, int inputsSize, int inputSize, double *outputs, int outputsSize, int iterationNumber, double step) 
	{
		if (model == nullptr) {
			std::cout << "Model does not exist" << std::endl;
			return -1;
		}

		int iterationsNum = 0;
		double *inputs2 = (double*)malloc(sizeof(double) * inputSize);
		int i = 0;
		int j = 0;
		int o = 0;
		int error = 0;

		while (true) {
			if (iterationsNum > iterationNumber) {
				free(inputs2);
				return -1;
			}
			else {
				iterationsNum++;
			}

			for (i; i < inputsSize; i += inputSize) {
				for (j; j < inputSize; j++) {
					inputs2[j] = inputs[i + j];
				}
				error += rosen_learning(model, inputs2, inputSize, outputs[o], step);
				o++;
				j = 0;
			}
			if (error == 0) {
				free(inputs2);
				return 0;
			}

			i = 0;
			j = 0;
			o = 0,
			error = 0;
		}
	}

	

	

	__declspec(dllexport) int return42()
	{
		return 42;
	}
}